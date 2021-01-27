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
/// @file  RBAZoneMaker.cpp
/// @brief Zone object generator class

#include <iostream>
#include "RBAZoneMaker.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAZoneMaker::RBAZoneMaker()
  : RBARuleObjectMaker{"zones"},
    RBAAllocatableMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAZoneMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAZoneImpl>(name);
}

RBAModelElement*
RBAZoneMaker::setProperty(RBAModelElement* element,
                          const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner)
{
  element = RBAAllocatableMaker::setProperty(element, jsonElem, model, owner);
  if(element == nullptr) {
    return nullptr;
  }

  RBAZoneImpl* const zone {dynamic_cast<RBAZoneImpl*>(element)};

  return zone;
}

}
