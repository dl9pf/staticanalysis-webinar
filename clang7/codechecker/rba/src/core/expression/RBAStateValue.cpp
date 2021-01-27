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

 /// StateValue class denition

#include <string>
#include "RBAStateValue.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void RBAStateValue::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector which is the only existing vistor
  // does not pass this path because it does not accept 
  // the expression that returns Value.  But, in the future,
  // another visitor may accept, so implement this.
  visitor.visit(*this);
}

RBAModelElementType
RBAStateValue::getModelElementType() const
{
  return RBAModelElementType::StateValue;
}

std::int32_t
RBAStateValue::getValueCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const
{
  std::int32_t result { -99 };
  const auto leftInfo = info->getChild(0U);
  const auto r = getLhsOperand()->getReferenceObject(leftInfo, arb);
  const RBAContent* c { nullptr };
  const RBAContentState* cs { nullptr };
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (r != nullptr) {
      c = dynamic_cast<const RBAContent*>(r->getRawObject());
      if (c != nullptr) {
        if (r->isPrevious()) {
          cs = arb->getResult()->getPreActiveState(c);
        } else {
          cs = arb->getResult()->getActiveState(c);
        }
        if (cs != nullptr) {
          result = cs->getContentStatePriority();
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string pre;
  std::string cName { "NULL" };
  std::string resultText{ "no Content skip" };
  if (r != nullptr) {
    cName = r->getElementName();
    pre = getPreMsg(r->isPrevious());
  }
  if (info->isExceptionBeforeArbitrate()) {
    resultText = "before arbitrate skip";
  } else {
    if (cs != nullptr) {
      resultText = cs->getElementName() + " : " + std::to_string(result);
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      "
      + pre
      + "Content["
      + cName
      + "] state value ["
      + resultText
      + "]");
#endif
  return result;
}

#ifdef RBA_USE_LOG
const std::string
RBAStateValue::getSymbol() const
{
  return ".stateValue()";
}
#endif

}
