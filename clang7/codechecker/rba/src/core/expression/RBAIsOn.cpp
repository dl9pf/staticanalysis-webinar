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
 * IsOn class (to judge if a Scene is active) definition file
 */

#include "RBAIsOn.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBASceneImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAIsOn::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIsOn::getModelElementType() const
{
  return RBAModelElementType::IsOn;
}

bool
RBAIsOn::executeCore(RBAConstraintInfo* info,
                     RBAArbitratorImpl* arb) const
{
  bool isPassed {false};
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (ruleObj != nullptr){
    const RBASceneImpl* const scene {dynamic_cast<const RBASceneImpl*>(ruleObj->getRawObject())};
    if (ruleObj->isPrevious() == false) {
      isPassed = arb->getResult()->isActive(scene);
    } else {
      isPassed = arb->getResult()->isPreActive(scene);
    }
  } else {
    // Currently, there is no expression that returns null as "Scene", 
    // so it does not go through this path. But an expression  that returns null
    // may be added  in the future, so it is described as it is.
    ;
  }
#ifdef RBA_USE_LOG
  if (ruleObj != nullptr) {
    const RBASceneImpl* scene = dynamic_cast<const RBASceneImpl*>(ruleObj
        ->getRawObject());
    if (info->isExceptionBeforeArbitrate() == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      Scene[" + scene->getName() + "] before arbitrate skip");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::SKIP);
    } else if (isPassed == true) {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Scene["
              + scene->getName() + "] is On");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::TRUE);
    } else {
      LOG_arbitrateConstraintLogicLogLine(
          "      " + getPreMsg(ruleObj->isPrevious()) + "Scene["
              + scene->getName() + "] is not On");
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                          RBAExecuteResult::FALSE);
    }
  } else {
    // Currently, there is no expression that returns null as "Scene", 
    // so it does not go through this path. But an expression  that returns null
    // may be added  in the future, so it is described as it is.
    LOG_arbitrateConstraintLogicLogLine(
        "      " + getPreMsg(ruleObj->isPrevious()) + "Scene[NULL] is not On");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
  }
#endif
  // Remove itself from Constraint hierarchy for coverage
  LOG_removeHierarchy();
  return isPassed;
}

#ifdef RBA_USE_LOG
const std::string
RBAIsOn::getSymbol() const
{
  return ".isOn()";
}

const std::string
RBAIsOn::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string RBAIsOn::getCoverageExpressionText() const
{
  return getLhsOperand()->getCoverageExpressionText() + getSymbol();
}

RBAExpressionType
RBAIsOn::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
