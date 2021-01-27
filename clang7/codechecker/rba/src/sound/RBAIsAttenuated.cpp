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
/// IsAttenuated class 

#include "RBAIsAttenuated.hpp"

#include "RBAExpression.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAResultImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIsAttenuated::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsAttenuated::getModelElementType() const
{
  return RBAModelElementType::IsAttenuated;
}

bool
RBAIsAttenuated::executeCore(RBAConstraintInfo* info,
                                 RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if ((leftInfo->isExceptionBeforeArbitrate() ) || (ruleObj == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    const RBAZoneImpl* const zone {dynamic_cast<const RBAZoneImpl*>(ruleObj->getRawObject())};
    info->addOperandAllocatable(zone);
    if (ruleObj->isPrevious() == true) {
      isPassed = arb->getResult()->isPreAttenuated(zone);
    } else {
      if (zone->isAttenuateChecked() == true) {
        isPassed = zone->isAttenuated();
        if (isPassed == true) {
          info->addTrueAllocatable(zone);
        } else {
          info->addFalseAllocatable(zone);
        }
      } else {
        info->setExceptionBeforeArbitrate(true);
      }
    }
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBAZoneImpl* zone = dynamic_cast<const RBAZoneImpl*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getName()
              + getSymbol() + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getName()
              + getSymbol() + "] true");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + zone->getName()
              + getSymbol() + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // At the moment, there is no expression that returns null as an Allocable, 
    // so it will not go through this path.
    // This is implmented because we may add an expression that returns null, 
    // in the future.
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + "NULL" + getSymbol()
              + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      [" + getPreMsg(ruleObj->isPrevious()) + "NULL" + getSymbol()
              + "] false");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  }
#endif
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsAttenuated::getSymbol() const
{
  return ".isAttenuated()";
}

RBAExpressionType
RBAIsAttenuated::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
