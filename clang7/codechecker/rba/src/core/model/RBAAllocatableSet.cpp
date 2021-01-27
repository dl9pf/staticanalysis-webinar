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
 * AllocatableSet class implementation
 */

#include "RBAAllocatableSet.hpp"
#include "RBAAllocatable.hpp"

namespace rba
{

RBAAllocatableSet::RBAAllocatableSet(const std::string& name)
  : RBARuleObject{name},
    RBAAbstractAllocatable{name}
{
}

void
RBAAllocatableSet::addTarget(const RBAAllocatable* alloc)
{
  leafAllocatable_.push_back(alloc);
#ifdef RBA_USE_LOG
  std::string newName = "[";
  for (auto& a : leafAllocatable_) {
    newName += a->getElementName() + ",";
  }
  if (newName.size() != 1U) {
    newName.erase(newName.end() - 1);  // Remove the trailing ",".
  }
  newName += "]";
  setDynamicName(newName);
#endif
}

void
RBAAllocatableSet::clear()
{
  leafAllocatable_.clear();
#ifdef RBA_USE_LOG
  setDynamicName("[]");
#endif
}

const std::list<const RBAAllocatable*>&
RBAAllocatableSet::getLeafAllocatable() const
{
  return leafAllocatable_;
}

}
