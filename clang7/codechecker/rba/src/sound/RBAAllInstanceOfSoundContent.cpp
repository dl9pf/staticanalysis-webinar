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
 * AllInstanceOfSoundContent class
 */

#include "RBAAllInstanceOfSoundContent.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfSoundContent::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector, the only existing visitor at this time,
  // does not accept this set of "For-All", "Exists", so it does not pass 
  // this path. 
  // It is implemented because another visitor may accept it in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfSoundContent::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfSoundContent;
}

const RBARuleObject*
RBAAllInstanceOfSoundContent::getReferenceObjectCore(RBAConstraintInfo* info,
                                                     RBAArbitratorImpl* arb) const
{
  return &allSoundContentSet_;
}

void
RBAAllInstanceOfSoundContent::setContents(const std::list<const RBASoundContentImpl*>& contents)
{
  for(auto& cont : contents) {
    allSoundContentSet_.addTarget(cont);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfSoundContent::getExpressionText() const
{
  return "ALL_SOUNDCONTENTS";
}

const std::string
RBAAllInstanceOfSoundContent::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}
