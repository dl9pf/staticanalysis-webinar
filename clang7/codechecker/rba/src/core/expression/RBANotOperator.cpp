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
 * RBANotOperator class definition
 */

#include "RBANotOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBANotOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBANotOperator::getModelElementType() const
{
  return RBAModelElementType::NotOperator;
}

bool
RBANotOperator::executeCore(RBAConstraintInfo* info,
                            RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const childInfo {info->getChild(0U)};
  const bool isChildPassed {getLhsOperand()->execute(childInfo, arb)};
  if (childInfo->isExceptionBeforeArbitrate() == true) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    isPassed = !isChildPassed;
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
RBANotOperator::getSymbol() const
{
  return "!";
}

const std::string
RBANotOperator::getExpressionText() const
{
  return getSymbol() + getLhsOperand()->getExpressionText();
}

const std::string
RBANotOperator::getCoverageExpressionText() const
{
  return getSymbol() + getLhsOperand()->getCoverageExpressionText();
}
#endif

}
