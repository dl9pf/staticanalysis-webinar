/**
 * Copyright (c) 2019 DENSO CORPORATION.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// @file  RBAModelFactory.cpp
/// @brief Model Factory class definition file

#include <algorithm>
#include "RBAModelFactory.hpp"
#include "RBAModelImpl.hpp"
#include "RBAJsonElement.hpp"
#include "RBAAbstractMakerTable.hpp"
#include "RBAConstraintImpl.hpp"

namespace rba
{

RBAModelFactory::RBAModelFactory(RBAModelImpl* const model)
  : model_{nullptr},
    exception_{false}
{
  if(model != nullptr) {
    model_ = model;
  }
  else {
    // @Deviation (A18-5-2)
    //  [Contents that deviate from the rules]
    //   Operators new and delete shall not be called explicitly.
    //  [Explain that it is okay to deviate from the rules]
    //   model_ is not owned by RBAModelFacotry.
    //   Therefore, it is not managed by the smart pointer.
    //   There is no problem because it is managed by 
    //   the user side of RBAModelFactory.
    model_ = new RBAModelImpl();
  }
}

RBAModelFactory::~RBAModelFactory() noexcept
{
}

RBAModel* const
RBAModelFactory::getModel() const
{
  return model_;
}

void
RBAModelFactory::deleteModel()
{
    // @Deviation (A18-5-2)
    //  [Contents that deviate from the rules]
    //   Operators new and delete shall not be called explicitly.
    //  [Explain that it is okay to deviate from the rules]
    //   Since it is managed by the user side of RBAModelFactory, 
    //   there is no problem even if it is deleted from the outside.
  delete model_;
  model_ = nullptr;
}

void
RBAModelFactory::addMakerTable(const RBAAbstractMakerTable& makerTable)
{
  for(auto& maker : makerTable.getMakers()) {
    maker->setFactory(this);
    const std::string label {maker->getLabel()};
    nameToMaker_[label] = maker.get();
    makers_.push_back(std::move(maker));
  }
  for(auto& tag : makerTable.getTags()) {
    if (std::find(tags_.begin(), tags_.end(), tag) == tags_.end()) {
      tags_.push_back(tag);
    }
  }
}

void
RBAModelFactory::addMaker(const std::string label,
                          std::unique_ptr<RBAModelElementMaker> maker)
{
  maker->setFactory(this);
  nameToMaker_[label] = maker.get();
  makers_.push_back(std::move(maker));
}

bool
RBAModelFactory::hasMaker() const
{
  return !nameToMaker_.empty();
}

const std::list<std::string>&
RBAModelFactory::getTags() const
{
  return tags_;
}

RBAModelElement*
RBAModelFactory::createElement(const std::string& className,
                               const RBAJsonElement* const jsonElement,
                               RBAModelElement* const owner)
{
  auto it = nameToMaker_.find(className);
  if(it == nameToMaker_.end()) {
    const RBAJsonElement* const classElement {jsonElement->findChildren("class")};
    if(classElement != nullptr) {
      it = nameToMaker_.find(classElement->getString());
      if(it == nameToMaker_.end()) {
        return nullptr;
      }
    }
    else {
      return nullptr;
    }
  }

  return it->second->create(jsonElement, model_, owner);
}

void
RBAModelFactory::setAllocatableConstraint(const std::string& allocatableName,
                                          const std::string& constraintName,
                                          const RBAConstraintMap& kind)
{
  // Get allocatable
  RBAAllocatable* const allocatable
    {const_cast<RBAAllocatable*>(model_->findAllocatable(allocatableName))};
  // Get constraint 
  RBAConstraintImpl* const constraint {model_->findConstraintImpl(constraintName)};
  if ((allocatable != nullptr) && (constraint != nullptr)) {
    allocatable->addConstraint(constraint, kind);
  }
}

// Variable can be defined with the same name in different scopes,
// but here we are registering the Variable defined in the scope 
// that is being created
void
RBAModelFactory::pushVariable(const RBAVariable* const var)
{
  currentVariables_.push_back(var);
}

// Variables can be defined with the same name in different scopes,
// but when you leave the scope with a definition, Variable is deleted.
void
RBAModelFactory::popVariable()
{
  if(!currentVariables_.empty()) {
    currentVariables_.pop_back();
  }
}

const RBAVariable*
RBAModelFactory::getVariable(const std::string& varName)
{
  const auto itr =
      std::find_if(currentVariables_.rbegin(), currentVariables_.rend(),
                   [&varName](const RBAVariable* element) -> bool {
                     return element->getElementName() == varName;
                   });

  if (itr != currentVariables_.rend())
  {
    return *itr;
  }

  return nullptr;
}

void
RBAModelFactory::resetException()
{
  exception_ = false;
}

void
RBAModelFactory::setException()
{
  exception_ = true;
}

bool
RBAModelFactory::isException() const
{
  return exception_;
}

}
