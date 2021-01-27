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
 * AND operator class definition
 */

#include "RBAAndOperator.hpp"

#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAAndOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAAndOperator::getModelElementType() const
{
  return RBAModelElementType::AndOperator;
}

bool
RBAAndOperator::executeCore(RBAConstraintInfo* info,
                            RBAArbitratorImpl * arb) const
{
  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  
  std::uint32_t falseCount {0U};
  std::uint32_t exceptionCount {0U};
  std::uint32_t index {0U};
  for(const auto& ope : getOperand()) {
    // Add count to constraint hierarchy for coverage
    LOG_addHierarchy("#" + std::to_string(index));

    RBAConstraintInfo* const childInfo {info->getChild(index)};
    const bool res {ope->execute(childInfo, arb)};
    if(childInfo->isExceptionBeforeArbitrate()) {
      exceptionCount++;
    } else if(!res) {
      falseCount++;
    } else {
      ;
    }

    // Remove count to constraint hierarchy for coverage
    LOG_removeHierarchy();
    index++;
  }

  // with fail
  if (falseCount > 0U) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
    // Rmove count to constraint hierarchy for coverage
    LOG_removeHierarchy();
    return false;
  }

  // exception
  if (exceptionCount > 0U) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
    // Rmove count to constraint hierarchy for coverage
    LOG_removeHierarchy();
    info->setExceptionBeforeArbitrate(true);
    return false;
  }

  LOG_arbitrateConstraintLogicLogLine(
      "      [" + LOG_getExpressionText() + "] true");
  LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                      RBAExecuteResult::TRUE);
  // Rmove count to constraint hierarchy for coverage
  LOG_removeHierarchy();

  return true;
}

#ifdef RBA_USE_LOG
const std::string
RBAAndOperator::getSymbol() const
{
  return "AND";
}
#endif

}
