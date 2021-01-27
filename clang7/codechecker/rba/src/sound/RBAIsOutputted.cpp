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
/// IsOutputted class

#include "RBAIsOutputted.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAResultImpl.hpp"
#include "RBAContentState.hpp"
#include "RBAContent.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIsOutputted::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsOutputted::getModelElementType() const
{
  return RBAModelElementType::IsOutputted;
}

bool
RBAIsOutputted::executeCore(RBAConstraintInfo* info,
                                RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if ((leftInfo->isExceptionBeforeArbitrate()) || (ruleObj == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    const RBAAllocatable* const zone {dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(zone);
    if (ruleObj->isPrevious() == true) {
      if ((arb->getResult()->isPreHidden(zone) == false)
          && (arb->getResult()->getPreAllocatedContentState(zone) != nullptr)) {
        isPassed = true;
      }
    } else {
      if ((zone->isHiddenChecked()==true) && (zone->isHidden()==true)) {
        info->addFalseAllocatable(zone);
      } else {
        if (zone->isChecked()) {
          if (zone->getState() != nullptr) {
            info->clearFalseAllocatable();
            info->addTrueAllocatable(zone);
            isPassed = true;
          } else {
            info->addFalseAllocatable(zone);
          }
        } else {
          info->setExceptionBeforeArbitrate(true);
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAAllocatable* zone = dynamic_cast<const RBAAllocatable*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      Zone[" + zone->getElementName()
          + "] is before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      const RBAContentState* contentState;
      if (ruleObj->isPrevious() == true) {
        contentState = arb->getResult()->getPreAllocatedContentState(zone);
      } else {
        contentState = zone->getState();
      }
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Zone["
              + zone->getElementName() + "] is Outputted Content["
              + contentState->getOwner()->getElementName() + "::"
              + contentState->getElementName() + "]");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Zone["
              + zone->getElementName() + "] is not Outputted");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else if (info->isExceptionBeforeArbitrate() == true) {
    // At the moment, there is no expression that returns null as an Allocable, 
    // so it will not go through this path.
    // This is implmented because we may add an expression that returns null, 
    // in the future.
    LOG_arbitrateConstraintLogicLogLine(
        "      Zone[NULL] is not Outputted");
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
RBAIsOutputted::getSymbol() const
{
  return ".isOutputted()";
}

RBAExpressionType
RBAIsOutputted::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
