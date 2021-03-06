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
/// IsVisible class

#include "RBAAllocatable.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBAExecuteResult.hpp"
#include "RBAExpressionType.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAIsVisible.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAResultImpl.hpp"

namespace rba
{

void RBAIsVisible::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsVisible::getModelElementType() const
{
  return RBAModelElementType::IsVisible;
}

bool
RBAIsVisible::executeCore(RBAConstraintInfo* info,
                          RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to the constraint hierarchy for coverage.
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAContent* content {nullptr};
  if (ruleObj != nullptr) {
    content = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }
  if (leftInfo->isExceptionBeforeArbitrate() || (content == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj->isPrevious() == false) {
    const RBAContentState* const contentState
      {arb->getResult()->getActiveState(content)};
    if (contentState != nullptr) {
      for(const RBAAllocatable* const allocatable : content->getAllocatables()) {
        info->addOperandAllocatable(allocatable);
        const RBAContentState* const allocateContentState {allocatable->getState()};
        if (allocatable->isChecked() == true) {
          if (contentState == allocateContentState) {
            if ((allocatable->isHiddenChecked() == true)
                && (allocatable->isHidden() == true)) {
              info->addFalseAllocatable(allocatable);
            } else {
              info->setExceptionBeforeArbitrate(false);
              info->clearFalseAllocatable();
              info->addTrueAllocatable(allocatable);
              isPassed = true;
              break;
            }
          } else {
            info->addFalseAllocatable(allocatable);
          }
        } else {
          info->setExceptionBeforeArbitrate(true);
        }
      }
    } else {
      for (auto& a : content->getAllocatables()) {
        info->addFalseAllocatable(a);
      }
    }
  } else {
    const RBAContentState* const contentState {arb->getResult()->getPreActiveState(content)};
    if (contentState != nullptr) {
      for(const RBAAllocatable* const allocatable : content->getAllocatables()) {
        info->addOperandAllocatable(allocatable);
        const RBAContentState* const allocateContentState {arb->getResult()->getPreAllocatedContentState(allocatable)};
        if ((contentState == allocateContentState)
            && (arb->getResult()->isPreHidden(allocatable) == false)) {
          isPassed = true;
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (info->isExceptionBeforeArbitrate() == true) {
    if(content == nullptr) {
      LOG_arbitrateConstraintLogicLogLine(
          "      Content[NULL] is not Visible");
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
          + content->getElementName() + "] is before arbitrate skip");
    }
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
    const RBAContentState* contentState;
    if (ruleObj->isPrevious() == true) {
      contentState = arb->getResult()->getPreActiveState(content);
    } else {
      contentState = arb->getResult()->getActiveState(content);
    }
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
        + content->getElementName() + "::" + contentState->getElementName()
        + "] is Visible");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Content["
        + content->getElementName() + "] is not Visible");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
  }
#endif
  // Remove itself from the constraint hierarchy for coverage.
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsVisible::getSymbol() const
{
  return ".isVisible()";
}

RBAExpressionType
RBAIsVisible::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
