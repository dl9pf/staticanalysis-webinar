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
 * AllInstanceOfViewContent implementation class definition file
 */

#include "RBAAllInstanceOfViewContent.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfViewContent::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector, the only existing visitor at this time,
  // does not accept this set of For-All, Exists, so it does not pass this path.
  // It is left because another visitor may accept it in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfViewContent::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfViewContent;
}

const RBARuleObject*
RBAAllInstanceOfViewContent::getReferenceObjectCore(RBAConstraintInfo* info,
                                                    RBAArbitratorImpl* arb) const
{
  return &allViewContentSet_;
}

void
RBAAllInstanceOfViewContent::setContents(const std::list<const RBAViewContentImpl*>& contents)
{
  for (auto& content : contents) {
    allViewContentSet_.addTarget(content);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfViewContent::getExpressionText() const
{
  return "ALL_VIEWCONTENTS";
}

const std::string
RBAAllInstanceOfViewContent::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}
