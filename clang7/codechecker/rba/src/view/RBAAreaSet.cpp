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
 * AreaSet class
 */

#include "RBAAreaSet.hpp"
#include "RBAArea.hpp"
#include "RBAAllocatable.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAAreaSet::RBAAreaSet(const std::string& name)
  : RBARuleObject{name},
    RBAAllocatableSet{name}
{
}

const std::list<const RBAArea*>&
RBAAreaSet::getTargets() const
{
  return externAreas_;
}

void
RBAAreaSet::addTarget(const RBAAllocatable* alloc)
{
  RBAAllocatableSet::addTarget(alloc);
  externAreas_.push_back(dynamic_cast<const RBAArea*>(alloc));
}

void
RBAAreaSet::clear()
{
  RBAAllocatableSet::clear();
  externAreas_.clear();
}

RBAModelElementType
RBAAreaSet::getModelElementType() const
{
  return RBAModelElementType::AreaSet;
}

}
