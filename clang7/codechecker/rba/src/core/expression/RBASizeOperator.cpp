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

//
// SizeOperator class definition
//

#include "RBASizeOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBALogManager.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContentSet.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBASizeOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}
RBAModelElementType RBASizeOperator::getModelElementType() const
{
  return RBAModelElementType::SizeOperator;
}
std::int32_t RBASizeOperator::getValueCore(RBAConstraintInfo* info,
                                           RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  std::int32_t returnValue {-99};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const lhsObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                    arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (lhsObj != nullptr) {
    if (dynamic_cast<const RBAAllocatableSet*>(lhsObj) != nullptr) {
      returnValue = static_cast<std::int32_t>(dynamic_cast<const RBAAllocatableSet*>(lhsObj)
          ->getLeafAllocatable().size());
    } else {
      returnValue = static_cast<std::int32_t>(dynamic_cast<const RBAContentSet*>(lhsObj)->getLeafContent()
          .size());
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  LOG_arbitrateConstraintLogicLogLine(
      "      " + LOG_getExpressionText() + " is " + std::to_string(returnValue));
#endif
  LOG_removeHierarchy();
  return returnValue;
}

#ifdef RBA_USE_LOG
const std::string RBASizeOperator::getSymbol() const
{
  return ".size()";
}
const std::string RBASizeOperator::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}
const std::string RBASizeOperator::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText() + getSymbol();
}
#endif

} /* namespace rba */
