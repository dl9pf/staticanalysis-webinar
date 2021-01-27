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
 * activeState definition
 */

#include "RBAActiveState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBALogManager.hpp"

namespace rba
{

void RBAActiveState::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}
RBAModelElementType RBAActiveState::getModelElementType() const
{
  return RBAModelElementType::ActiveState;
}
const RBARuleObject* RBAActiveState::getReferenceObjectCore(
    RBAConstraintInfo* info, RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  const RBARuleObject* returnObj {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr) {
    const RBAContent* const c {
        dynamic_cast<const RBAContent*>(ruleObj->getRawObject())};
    if (ruleObj->isPrevious()) {
      returnObj = arb->getResult()->getPreActiveState(c);
    } else {
      returnObj = arb->getResult()->getActiveState(c);
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  std::string str;
  if (info->isExceptionBeforeArbitrate()) {
    str = " is before arbitrate skip";
  } else if (ruleObj == nullptr) {
    str = " no Content";
  } else if (returnObj == nullptr) {
    str = " has no Active State";
  } else {
    str = " is " + returnObj->getElementName();
  }
  LOG_arbitrateConstraintLogicLogLine("      " + getExpressionText() + str);
#endif
  LOG_removeHierarchy();
  return returnObj;
}
#ifdef RBA_USE_LOG
const std::string RBAActiveState::getSymbol() const
{
  return ".activeState()";
}
#endif
} /* namespace rba */
