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
 * AffectInfo class definition
 */

#include "RBAAffectInfo.hpp"

namespace rba
{

/**
 * @brief Returns whether the allocable already affects the target allocable
 * @param allocatable Influential Allocatable
 * @param affectAllocatable Affected Allocatable
 * @return bool
 */
bool
RBAAffectInfo::alreadyKnowsThatFormerHasAffectedToLatter(const RBAAllocatable* const allocatable,
        const RBAAllocatable* const affectAllocatable) const
{
  for(const auto& alloc : reaffected_[allocatable]) {
    if(alloc == affectAllocatable) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Register Affect information
 * @param allocatable Influential Allocatable
 * @param affectAllocatable Affected Allocatable
 */
void
RBAAffectInfo::addInfoThatFormerAffectedToLatter(const RBAAllocatable* const allocatable,
						 const RBAAllocatable* const affectAllocatable)
{
  static_cast<void>(reaffected_[allocatable].insert(affectAllocatable));
}

/**
 * @brief Deletes the Affect information of "allocatable" registered by 
 *               other allocatables registered by arbitration of the specified 
 *               recursion hierarchy of the specified "allocatable".
 * @param affectAllocatable
 */
void RBAAffectInfo::removeAffectInfo(const RBAAllocatable* const affectAllocatable)
{
  static_cast<void>(reaffected_.erase(affectAllocatable));
}

}
