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
/// @file  RBAZoneSetMaker.cpp
/// @brief ZoneSet object generator class

#include "RBAZoneSetMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAZoneSet.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAZoneSetMaker::RBAZoneSetMaker()
  : RBARuleObjectMaker{"zonesets"},
    RBAAllocatableSetMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAZoneSetMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAZoneSet>(name);
}

RBAModelElement*
RBAZoneSetMaker::setProperty(RBAModelElement* element,
                             const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  static_cast<void>(RBAAllocatableSetMaker::setProperty(element, jsonElem, model, owner));

  RBAZoneSet* const zoneSet {dynamic_cast<RBAZoneSet*>(element)};

  model->addZoneSet(zoneSet);

  return zoneSet;
}

}
