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
 * OrOperator class definition
 */

#include "RBAOrOperator.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAOrOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAOrOperator::getModelElementType() const
{
  return RBAModelElementType::OrOperator;
}

bool
RBAOrOperator::executeCore(RBAConstraintInfo* info,
                           RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  std::uint32_t index {0U};
  for (const RBAExpression* const ope : getOperand()) {
    RBAConstraintInfo* const childInfo {info->getChild(index)};
    // Add count to Constraint hierarchy for coverage
    LOG_addHierarchy("#" + std::to_string(index));
    const bool res {ope->execute(childInfo, arb)};
    // Remove count from Constraint hierarchy for coverage
    LOG_removeHierarchy();
    if (childInfo->isExceptionBeforeArbitrate() == true) {
      info->setExceptionBeforeArbitrate(true);
    } else if (res == true) {
      isPassed = true;
    } else {
      ;
    }
    ++index;
  }
  if (isPassed == true) {
    info->setExceptionBeforeArbitrate(false);
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
  // Remove count from Constraint hierarchy for coverage
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAOrOperator::getSymbol() const
{
  return "OR";
}
#endif

}
