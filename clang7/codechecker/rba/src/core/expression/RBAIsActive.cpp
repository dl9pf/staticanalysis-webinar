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
 * IsActive class definition
 */

#include "RBAIsActive.hpp"
#include "RBAContent.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAIsActive::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsActive::getModelElementType() const
{
  return RBAModelElementType::IsActive;
}

bool
RBAIsActive::executeCore(RBAConstraintInfo* info,
                             RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if (leftInfo->isExceptionBeforeArbitrate() == true) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr) {
    const RBAContent* const content {dynamic_cast<const RBAContent*>(ruleObj->getRawObject())};
    if (ruleObj->isPrevious()) {
      isPassed = arb->getResult()->isPreActive(content);
    } else {
      isPassed = arb->getResult()->isActive(content);
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
    LOG_arbitrateConstraintLogicLogLine(
        "      Content[NULL] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (ruleObj != nullptr) {
    const RBAContent* content = dynamic_cast<const RBAContent*>(ruleObj
        ->getRawObject());
    if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
              + content->getElementName() + "] is Active");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
              + content->getElementName() + "] is not Active");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    LOG_arbitrateConstraintLogicLogLine("      Content[NULL] is not Active");
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
RBAIsActive::getSymbol() const
{
  return ".isActive()";
}

RBAExpressionType
RBAIsActive::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
