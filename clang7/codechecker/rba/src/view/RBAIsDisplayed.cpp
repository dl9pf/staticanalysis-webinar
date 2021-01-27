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
/// IsDisplayed class

#include "RBAIsDisplayed.hpp"

#include "RBAExpression.hpp"
#include "RBAAllocatable.hpp"
#include "RBARuleObject.hpp"
#include "RBAContentState.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAResultImpl.hpp"
#include "RBAContent.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAIsDisplayed::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsDisplayed::getModelElementType() const
{
  return RBAModelElementType::IsDisplayed;
}

bool
RBAIsDisplayed::executeCore(RBAConstraintInfo* info,
                            RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to the constraint hierarchy for coverage.
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                     arb)};
  if ((leftInfo->isExceptionBeforeArbitrate()) || (ruleObj == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    const RBAAllocatable* const allocatable {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(allocatable);
    if (ruleObj->isPrevious() == true) {
      if ((arb->getResult()->isPreHidden(allocatable) == false)
          && (arb->getResult()->getPreAllocatedContentState(allocatable)
              != nullptr)) {
        isPassed = true;
      }
    } else {
      if ((allocatable->isHiddenChecked() == true)
          && (allocatable->isHidden() == true)) {
        info->addFalseAllocatable(allocatable);
      } else {
        if (allocatable->isChecked() == true) {
          if (allocatable->getState() != nullptr) {
            info->addTrueAllocatable(allocatable);
            isPassed = true;
          } else {
            info->addFalseAllocatable(allocatable);
          }
        } else {
          info->setExceptionBeforeArbitrate(true);
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string lhsName;
  const RBAAllocatable* allocatable = nullptr;
  if (ruleObj == nullptr) {
    // At the moment, there is no expression that returns null as Allocatable, 
    // so it will not go through this path.
    // but in the future, an expression that returns null may be added 
    // so this is implemented.
    lhsName = "NULL";
  } else {
    allocatable = dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject());
    lhsName = allocatable->getElementName();
  }
  if (info->isExceptionBeforeArbitrate() == true) {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Area[" + lhsName
            + "] is before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
  } else if (isPassed == true) {
    const RBAContentState* contentState;
    if (ruleObj->isPrevious() == true) {
      contentState = arb->getResult()->getPreAllocatedContentState(allocatable);
    } else {
      contentState = allocatable->getState();
    }
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Area[" + lhsName
            + "] is Displayed Content["
        + contentState->getOwner()->getElementName()
            + "::" + contentState->getElementName() + "]");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Area[" + lhsName
            + "] is not Displayed");
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
RBAIsDisplayed::getSymbol() const
{
  return ".isDisplayed()";
}

RBAExpressionType
RBAIsDisplayed::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
