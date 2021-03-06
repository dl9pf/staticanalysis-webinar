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

/// IsEqualToOperator class definitino file

#include "RBAIsEqualToOperator.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIsEqualToOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsEqualToOperator::getModelElementType() const
{
  return RBAModelElementType::IsEqualToOperator;
}

bool
RBAIsEqualToOperator::executeCore(RBAConstraintInfo* info,
                                  RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());

  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  const std::int32_t lhsVal {getLhsOperand()->getValue(leftInfo, arb)};
  const std::int32_t rhsVal {getRhsOperand()->getValue(rightInfo, arb)};
  if ((leftInfo->isExceptionBeforeArbitrate() == true)
      || (rightInfo->isExceptionBeforeArbitrate() == true)
      || (lhsVal == -99)
      || (rhsVal == -99)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (lhsVal == rhsVal) {
      isPassed = true;
      info->addTrueAllocatableFromOperand();
    } else {
      info->addFalseAllocatableFromOperand();
    }
  }

#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (lhsVal == rhsVal) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] true");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
  }
#endif
  // Remove itself from Constraint hierarchy for coverage
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsEqualToOperator::getSymbol() const
{
  return "=";
}

RBAExpressionType
RBAIsEqualToOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
