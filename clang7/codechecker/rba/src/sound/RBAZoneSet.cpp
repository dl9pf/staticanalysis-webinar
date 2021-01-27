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
 * ZoneSet class
 */

#include "RBAZoneSet.hpp"
#include "RBAZone.hpp"
#include "RBAAllocatable.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAZoneSet::RBAZoneSet(const std::string& name)
  : RBARuleObject{name},
    RBAAllocatableSet{name}
{
}

const std::list<const RBAZone*>&
RBAZoneSet::getTargets() const
{
  return externZones_;
}

void
RBAZoneSet::addTarget(const RBAAllocatable* alloc)
{
  RBAAllocatableSet::addTarget(alloc);
  externZones_.push_back(dynamic_cast<const RBAZone*>(alloc));
}

void
RBAZoneSet::clear()
{
  RBAAllocatableSet::clear();
  externZones_.clear();
}

RBAModelElementType
RBAZoneSet::getModelElementType() const
{
  return RBAModelElementType::ZoneSet;
}

}
