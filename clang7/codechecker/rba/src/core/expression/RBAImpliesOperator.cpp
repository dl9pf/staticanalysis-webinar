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
 * implication operator class defintion file
 */

#include "RBAImpliesOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAImpliesOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAImpliesOperator::getModelElementType() const
{
  return RBAModelElementType::ImpliesOperator;
}

bool
RBAImpliesOperator::executeCore(RBAConstraintInfo* info,
                                RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  // Add "left-hand side formula" to the constraint hierarchy for coverage
  LOG_addHierarchy("#left"); 
  const bool lhsRes {getLhsOperand()->execute(leftInfo, arb)};
  // Remove "left-hand side formula" from the constraint hierarchy for coverage
  LOG_removeHierarchy();

  if (leftInfo->isExceptionBeforeArbitrate() == false) {
    if (lhsRes == false) {
      isPassed = true;
    } else {
      RBAConstraintInfo* const rightInfo {info->getChild(1U)};
      // Add "right-hand side formula" to the constraint hierarchy for coverage
      LOG_addHierarchy("#right");
      const bool rhsRes {getRhsOperand()->execute(rightInfo, arb)};
      // Remove "right-hand side formula"
      // from the constraint hierarchy for coverage
      LOG_removeHierarchy();
      if (rightInfo->isExceptionBeforeArbitrate() == true) {
        info->setExceptionBeforeArbitrate(true);
      } else if (rhsRes == true) {
        isPassed = true;
      } else {
        ;
      }
    }
  } else {
    info->setExceptionBeforeArbitrate(true);
    // Evaluate the right-hand side fromula
    // to get the right side allocatable of arbitration target
    RBAConstraintInfo* const rightInfo {info->getChild(1U)};
    // Add "right-hand side formula" to the constraint hierarchy for coverage
    LOG_addHierarchy("#right");
    static_cast<void>(getRhsOperand()->execute(rightInfo, arb));
    // Remove "right-hand side formula" to the constraint hierarchy for coverage
    LOG_removeHierarchy();
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate()) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
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
  // Remove itself from the constraint hierarchy for coverage
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAImpliesOperator::getSymbol() const
{
  return "->";
}

void
RBAImpliesOperator::createHierarchy()
{
  RBAExpression* exprLhs = getLhsOperand();
  RBAExpression* exprRhs = getRhsOperand();

  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  // Add "left-hand side formula" to the constraint hierarchy for coverage
  LOG_addHierarchy("#left");
  exprLhs->createHierarchy();
  // Remove "left-hand side formula" from
  //  the constraint hierarchy for coverage
  LOG_removeHierarchy();

  // Add "right-hand side formula" to the constraint hierarchy for coverage
  LOG_addHierarchy("#right");
  exprRhs->createHierarchy();
  // Remove "right-hand side formula" from
  //  the constraint hierarchy for coverage
  LOG_removeHierarchy();

  // Remove itself from the constraint hierarchy for coverage
  LOG_removeHierarchy();
}
#endif

}
