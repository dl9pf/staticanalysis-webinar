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
/// @file  RBAModelElementMaker.cpp
/// @brief ModelElement object genartor abstract class

#include "RBAModelElementMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBAModelImpl.hpp"

namespace rba
{

std::unordered_map<std::string, std::unique_ptr<RBAModelElementMaker>> RBAModelElementMaker::makerMap_;

RBAModelElementMaker::RBAModelElementMaker(const std::string& label)
  : factory_{nullptr},
    label_{label}
{
}

void
RBAModelElementMaker::setFactory(RBAModelFactory* const factory)
{
  factory_ = factory;
}

RBAModelFactory* RBAModelElementMaker::getFactory() const
{
  return factory_;
}

const std::string&
RBAModelElementMaker::getLabel() const
{
  return label_;
}

RBAModelElement*
RBAModelElementMaker::create(const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  const auto nameElement = jsonElem->findChildren("name");

  RBAModelElement* element {nullptr};
  if (nameElement != nullptr) {
    element = getInstance(model, nameElement->getString(), owner);
  } else {
    element = getInstance(model, "", owner);
  }

  return setProperty(element, jsonElem, model, owner);
}

RBAModelElement*
RBAModelElementMaker::getInstance(RBAModelImpl* model,
                                  const std::string& name,
                                  RBAModelElement* owner)
{
  RBAModelElement* ret {nullptr};

  // If there is a class name, delete the class name
  std::string fullName {name};
  while (fullName.find(':') != std::string::npos) {
    const auto start = fullName.find(':');
    const auto end = fullName.find('/', start);
    static_cast<void>(fullName.erase(start, end - start));
  }

  // In case of Elemetn with name
    if(fullName != "") {
    const auto elem = model->findModelElement(fullName);
    // exists in model
    if(elem != nullptr) {
      ret = const_cast<RBAModelElement*>(elem);
    }
    // not exists in model
    else {
      std::unique_ptr<RBAModelElement> inst {createInstance(fullName)};
      ret = model->addNamedElement(std::move(inst));
    }
  }
  // In case of Elemetn without name
  else {
    std::unique_ptr<RBAModelElement> inst {createInstance()};
    ret = model->addModelElement(std::move(inst));
  }
  
  return ret;
}

void
RBAModelElementMaker::addMaker(const std::string& typeName, std::unique_ptr<RBAModelElementMaker> maker)
{
  makerMap_[typeName] = std::move(maker);
}

RBAModelElementMaker*
RBAModelElementMaker::getMaker(const std::string& typeName)
{
  if (makerMap_.find(typeName) == makerMap_.end()) {
    return nullptr;
  }
  return makerMap_[typeName].get();
}

}
