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

/* 
 * ContentValue class definition 
 */

#include <string>
#include "RBAContentValue.hpp"
#include "RBAAllocatable.hpp"
#include "RBAContentState.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAContentValue::accept(RBAExpressionVisitor& visitor)
{
  // RBA SceneAllocatableCollector which is only existing vistor at this time 
  // does not accept the value of the content state.
  // So this code doesn't work. 
  //
  // But, leave this because another visitor may accept it in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAContentValue::getModelElementType() const
{
  return RBAModelElementType::ContentValue;
}

std::int32_t
RBAContentValue::getValueCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const
{
  std::int32_t result { -99 };
  const auto leftInfo = info->getChild(0U);
  const auto r = getLhsOperand()->getReferenceObject(leftInfo, arb);
  const RBAContentState* cs { nullptr };
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (r != nullptr) {
      const auto a = dynamic_cast<const RBAAllocatable*>(r->getRawObject());
      if (a != nullptr) {
        if (r->isPrevious()) {
          cs = arb->getResult()->getDirectPreContentState(a);
          if (cs != nullptr) {
            result = cs->getContentStatePriority();
          }
        } else {
          info->addOperandAllocatable(a);
          if (a->isChecked()) {
            cs = a->getState();
            if (cs != nullptr) {
              result = cs->getContentStatePriority();
            }
          } else {
            // Throw an Exception if arbitration is not over
            info->setExceptionBeforeArbitrate(true);
          }
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string pre;
  std::string aName = "NULL";
  std::string resultText = "no Content skip";
  if (r != nullptr) {
    aName = r->getElementName();
    pre = getPreMsg(r->isPrevious());
  }
  if (info->isExceptionBeforeArbitrate()) {
    resultText = "before arbitrate skip";
  } else {
    if (cs != nullptr) {
      resultText = cs->getOwner()->getElementName() + "::" + cs->getElementName() + " : " + cs->getPriorityString();
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      "
      + pre
      + "Allocatable["
      + aName
      + "] has Content Priority ["
      + resultText
      + "]");
  #endif
  return result;
}
#ifdef RBA_USE_LOG
const std::string
RBAContentValue::getSymbol() const
{
  return ".contentValue()";
}
#endif
}
