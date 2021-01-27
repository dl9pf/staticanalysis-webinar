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
 * .hasBeenDisplayed() definition
 **/

#include "RBAHasBeenDisplayed.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"

namespace rba
{

void RBAHasBeenDisplayed::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType RBAHasBeenDisplayed::getModelElementType() const
{
  return RBAModelElementType::HasBeenDisplayed;
}

bool RBAHasBeenDisplayed::executeCore(RBAConstraintInfo* info,
                                      RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr) {
    const RBAContent* const c {
        dynamic_cast<const RBAContent*>(ruleObj->getRawObject())};
    if (!ruleObj->isPrevious()) {
      isPassed = arb->getResult()->hasBeenDisplayed(c);
    } else {
      isPassed = arb->getResult()->hasBeenPreDisplayed(c);
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  RBAExecuteResult r;
  std::string cname;
  std::string resultStr;
  if (ruleObj != nullptr) {
    cname = ruleObj->getRawObject()->getElementName();
  } else {
    cname = "NULL";
  }
  if (info->isExceptionBeforeArbitrate()) {
    resultStr = " before arbitrate skip";
    r = RBAExecuteResult::SKIP;
  } else if (isPassed) {
    resultStr = " true";
    r = RBAExecuteResult::TRUE;
  } else {
    resultStr = " false";
    r = RBAExecuteResult::FALSE;
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      Content[" + cname + "]" + getSymbol() + resultStr);
  LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(), r);
#endif
  LOG_removeHierarchy();
  return isPassed;
}

// Log
#ifdef RBA_USE_LOG
const std::string RBAHasBeenDisplayed::getSymbol() const
{
  return ".hasBeenDisplayed()";
}
RBAExpressionType RBAHasBeenDisplayed::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif
} /* namespace rba */
