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
/**
 * Scene implementation class
 */

#include "RBASceneImpl.hpp"
#include "RBAModelElementType.hpp"
#include "RBAAbstractProperty.hpp"
#include "RBAIntegerProperty.hpp"

namespace rba
{

RBASceneImpl::RBASceneImpl(const std::string& name)
  : RBAScene(),
    RBARuleObject{name}
{
}

std::string
RBASceneImpl::getName() const
{
  return RBARuleObject::getElementName();
}

RBAModelElementType
RBASceneImpl::getModelElementType() const
{
  return RBAModelElementType::Scene;
}

bool
RBASceneImpl::isGlobal() const
{
  return global_;
}

const std::list<std::string>&
RBASceneImpl::getPropertyNames() const
{
  return propertyNames_;
}

std::int32_t
RBASceneImpl::getPropertyValue(const std::string& propertyName) const
{
  const RBAAbstractProperty* const prop {getProperty(propertyName)};
  if(prop == nullptr) {
    // Returns "-1" if the property is not registered
    return -1;
  }

  // Returns default value
  return prop->getValue();
}

const RBARuleObject* RBASceneImpl::getMember(const std::string& memberName) const
{
  return getProperty(memberName);
}

const RBAAbstractProperty*
RBASceneImpl::getProperty(const std::string& propertyName) const
{
  auto p = nameToProperty_.find(propertyName);
  if(p == nameToProperty_.end()) {
    // Returns nullptr if the property is not registered
    return nullptr;
  }

  return p->second;
}

void
RBASceneImpl::setGlobal(const bool newGlobal)
{
  global_ = newGlobal;
}

const RBAAbstractProperty*
RBASceneImpl::addProperty(const std::string& newName, std::int32_t newValue)
{
  auto p = nameToProperty_.find(newName);
  if(p != nameToProperty_.end()) {
    // No operation if the property is registered
    return p->second;
  }

  // Registration
  properties_.push_back(std::make_unique<RBAIntegerProperty>(this,
                                                             newName,
                                                             newValue));
  propertyNames_.push_back(newName);
  nameToProperty_[newName] = properties_.back().get();

  return properties_.back().get();
}

}
