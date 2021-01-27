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
 * OutputtingSound class implementation
 */

#include "RBAOutputtingSound.hpp"
#include "RBAAllocatable.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAResultImpl.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAOutputtingSound::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector, the only existing visitor at this time,
  // does not accept expression that returns RBARuleObject, so it does not pass 
  // this path. 
  // It is implemented because another visitor may accept it in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAOutputtingSound::getModelElementType() const
{
  return RBAModelElementType::OutputtingSound;
}

const RBARuleObject*
RBAOutputtingSound::getReferenceObjectCore(RBAConstraintInfo* info,
                                           RBAArbitratorImpl* arb) const
{
  const RBARuleObject* object {nullptr};
  const auto leftInfo = info->getChild(0U);
  const auto ruleObj = getLhsOperand()->getReferenceObject(leftInfo, arb);
  if (!leftInfo->isExceptionBeforeArbitrate()) {
    if (ruleObj != nullptr) {
      const RBAAllocatable* const alloc {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
      if (ruleObj->isPrevious()) {
        if (!arb->getResult()->isPreHidden(alloc)) {
          const auto contentState = arb->getResult()->getDirectPreContentState(alloc);
          if (contentState != nullptr) {
            object = contentState->getOwner();
          }
        }
      } else {
        if (!alloc->isChecked()) {
          info->setExceptionBeforeArbitrate(true);
        }
        // When "Hidden" judgment is not executed, or when "Hidden" is already 
        // judged and "Hidden" is false, contentState assigned to allocatable 
        // is acquired.
        else if (!alloc->isHiddenChecked() || !alloc->isHidden()) {
          const auto contentState = alloc->getState();
          if (contentState != nullptr) {
            object = contentState->getOwner();
          }
          // At this point, it is unknown whether the constraint expression 
          // will be False or True, so put it in both.
          info->addFalseAllocatable(alloc);
          info->addTrueAllocatable(alloc);
        } else {
          ;
        }
      }
    }
  } else {
      info->setExceptionBeforeArbitrate(true);
  }
#ifdef RBA_USE_LOG
  bool pre = false;
  std::string operandName;
  std::string resultText;
  if (ruleObj == nullptr) {
    operandName = "NULL";
  } else {
    pre = ruleObj->isPrevious();
    operandName = ruleObj->getElementName();
  }
  if (leftInfo->isExceptionBeforeArbitrate()) {
    resultText = "is before arbitrate skip";
  } else if (object == nullptr) {
    if((ruleObj != nullptr) && dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())->isChecked()) {
      resultText = "has no Outputted Content";
    } else {
      resultText = "is before arbitrate skip";
    }
  } else {
    resultText = "has Outputted Content[" + object->getElementName() + "]";
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      " + getPreMsg(pre) + "Zone[" + operandName + "] " + resultText);
#endif
  return object;
}

#ifdef RBA_USE_LOG
const std::string
RBAOutputtingSound::getSymbol() const
{
  return ".outputtingSound()";
}

void
RBAOutputtingSound::createHierarchy()
{
  getLhsOperand()->createHierarchy();
}

RBAExpressionType
RBAOutputtingSound::getUnderlyingType() const
{
  return RBAExpressionType::SOUND;
}
#endif

}
