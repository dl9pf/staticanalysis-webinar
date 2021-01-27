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
/// IsHidden class

#include "RBAIsHidden.hpp"

#include "RBAArbitratorImpl.hpp"
#include "RBAAllocatable.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAResultImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAIsHidden::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsHidden::getModelElementType() const
{
  return RBAModelElementType::IsHidden;
}

bool
RBAIsHidden::executeCore(RBAConstraintInfo* info,
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
    const RBAAllocatable* const area {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(area);
    if (ruleObj->isPrevious() == false) {
      if (area->isHiddenChecked() == false) {
        info->setExceptionBeforeArbitrate(true);
      } else if (area->isHidden() == true) {
        isPassed = true;
        info->addTrueAllocatable(area);
      } else {
        info->addFalseAllocatable(area);
      }
    } else {
      isPassed = arb->getResult()->isPreHidden(area);
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAAllocatable* area = dynamic_cast<const RBAAllocatable*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + area->getElementName() + getSymbol()
              + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + area->getElementName()
              + getSymbol() + "] true");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + area->getElementName()
              + getSymbol() + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // At the moment, there is no expression that returns null as Allocatable, 
    // so it will not go through this path.
    // but in the future, an expression that returns null may be added 
    // so this is implemented.
    LOG_arbitrateConstraintLogicLogLine(
        "      [NULL" + getSymbol() + "] false");
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
RBAIsHidden::getSymbol() const
{
  return ".isHidden()";
}

RBAExpressionType
RBAIsHidden::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
