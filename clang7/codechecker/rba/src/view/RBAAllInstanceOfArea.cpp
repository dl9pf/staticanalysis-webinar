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
 * AllInstanceOfArea implementation class definition file
 */

#include "RBAAllInstanceOfArea.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAllInstanceOfArea::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector, the only existing visitor at this time,
  // does not accept this set of For-All, Exists, so it does not pass this path.
  // It is left because another visitor may accept it in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAAllInstanceOfArea::getModelElementType() const
{
  return RBAModelElementType::AllInstanceOfArea;
}

const RBARuleObject*
RBAAllInstanceOfArea::getReferenceObjectCore(RBAConstraintInfo* info,
                                             RBAArbitratorImpl* arb) const
{
  return &allAreaSet_;
}

void
RBAAllInstanceOfArea::setAreas(const std::list<const RBAAreaImpl*>& areas)
{
  for (auto& a : areas) {
    allAreaSet_.addTarget(a);
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAAllInstanceOfArea::getExpressionText() const
{
  return "ALL_AREAS";
}

const std::string
RBAAllInstanceOfArea::getCoverageExpressionText() const
{
  return getExpressionText();
}
#endif

}
