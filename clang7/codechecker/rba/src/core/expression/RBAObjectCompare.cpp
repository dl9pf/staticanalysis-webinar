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
 * ObjectCompare calss defintion
 */

#include "RBAObjectCompare.hpp"
#include "RBAAllocatable.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"

namespace rba
{

void
RBAObjectCompare::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAObjectCompare::getModelElementType() const
{
  return RBAModelElementType::ObjectCompare;
}

bool
RBAObjectCompare::executeCore(RBAConstraintInfo* info,
                              RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBAExpression* const lhs {getLhsOperand()};
  // Add left hand side expression to Constraint hierarchy for coverage
  LOG_addHierarchy("#left");
  const RBARuleObject* const lhobj {lhs->getReferenceObject(leftInfo, arb)};
  // Remove left hand side expression from Constraint hierarchy for coverage
  LOG_removeHierarchy();
  // Throw if one of the pre-arbitration exceptions appears in the reference
  if (leftInfo->isExceptionBeforeArbitrate() == true) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    RBAConstraintInfo* const rightInfo {info->getChild(1U)};
    const RBAExpression* const rhs {getRhsOperand()};
    // Add right hand side expression to Constraint hierarchy for coverage
    LOG_addHierarchy("#right");
    const RBARuleObject* const rhobj {rhs->getReferenceObject(rightInfo, arb)};
    // Remove right hand side expression to Constraint hierarchy for coverage
    LOG_removeHierarchy();
    // Throw if one of the pre-arbitration exceptions appears in the reference
    if (rightInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
    } else {
      // False if both objects cannot be got
      if ((lhobj != nullptr) && (rhobj != nullptr)) {
        if (lhobj->getRawObject() == rhobj->getRawObject()) {
          isPassed = true;
                    // Even if re-arbitration is performed for "ObjectCompare" that uses 
          // "ObjectRefrence" as an operand, the evaluation result does not  
          // change from false to True, so it is not necessary to add  
          // "FalseAllocatable" or "TrueAllocatabe" for re-arbitration.
          // When "Expression" such as "AllocatedContent" is used as an operand,
          // "FalseAllocatable" and "TrueAllocatabe" are added in the operand,
          // so it is not necessary to add in ObjectCompare.
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
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
  // Remove itself from Constraint hierarchy for coverage
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAObjectCompare::getSymbol() const
{
  return "==";
}

const std::string
RBAObjectCompare::getExpressionText() const
{
  return getLhsOperand()->getExpressionText()
    + " " + getSymbol() + " " + getRhsOperand()->getExpressionText();
}

const std::string
RBAObjectCompare::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText()
    + " " + getSymbol() + " " + getRhsOperand()->getCoverageExpressionText();
}

void
RBAObjectCompare::createHierarchy()
{
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  RBAExpression*  expr0 = getLhsOperand();
  RBAExpression*  expr1 = getRhsOperand();

  // Add left hand side expression to Constraint hierarchy for coverage
  LOG_addHierarchy("#left");
  expr0->createHierarchy();
  // Remove left hand side expression from Constraint hierarchy for coverage
  LOG_removeHierarchy();

  // Add right hand side expression to Constraint hierarchy for coverage
  LOG_addHierarchy("#right");
  expr1->createHierarchy();
  // Remove right hand side expression from Constraint hierarchy for coverage
  LOG_removeHierarchy();

  // Remove itself from Constraint hierarchy for coverage
  LOG_removeHierarchy();
}

RBAExpressionType
RBAObjectCompare::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
