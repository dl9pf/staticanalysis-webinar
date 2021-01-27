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
 * ForAll operator class
 */

#include "RBAForAllOperator.hpp"

#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALambdaExpression.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAForAllOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAForAllOperator::getModelElementType() const
{
  return RBAModelElementType::ForAllOperator;
}

bool
RBAForAllOperator::executeCore(RBAConstraintInfo* info,
				   RBAArbitratorImpl * arb) const
{
  const RBAExpression* const setObj {getLhsOperand()};
  RBALambdaExpression* const lambda {getLambda()};

  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());

  // get Rule object and loop
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};

  std::vector<const RBARuleObject*> objs;
  const RBARuleObject* const ruleObj {setObj->getReferenceObject(leftInfo, arb)};
  const RBARuleObject* objset {nullptr};
  if (ruleObj != nullptr) {
    objset = ruleObj->getRawObject();
  }

  if(leftInfo->isExceptionBeforeArbitrate() || (objset == nullptr)) {
    // Remove itself from the constraint hierarchy for coverage
    LOG_removeHierarchy();

    info->setExceptionBeforeArbitrate(true);
    return false;
  }
  if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
    objs.clear();
    for(const RBAAllocatable* alloc
	  : dynamic_cast<const RBAAllocatableSet*>(objset)->getLeafAllocatable()) {
      objs.push_back(alloc);
    }
  }
  else {
    objs.clear();
    for(const auto& cont : dynamic_cast<const RBAContentSet*>(objset)->getLeafContent() ){
      objs.push_back(cont);
    }
  }

  bool isTrue {true};
  std::uint32_t i {0U};
  for(const RBARuleObject* const obj : objs) {
    // Add count to the constraint hierarchy for coverage
    LOG_addHierarchy("#" + std::to_string(i));

    RBAConstraintInfo* const childInfo {info->getChild(i)};
    lambda->setRuleObj(obj);

    const bool res {lambda->execute(childInfo, arb)};

    // Remove count from the constraint hierarchy for coverage
    LOG_removeHierarchy();

    if(childInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
    } else {
      isTrue = (isTrue && res);
    }
    i++;
  }

  if (isTrue == false) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] false");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
    // Remove count from the constraint hierarchy for coverage
    LOG_removeHierarchy();
    info->setExceptionBeforeArbitrate(false);
    return false;
  } else if (info->isExceptionBeforeArbitrate()) {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] before arbitrate skip");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
    // Remove count from the constraint hierarchy for coverage
    LOG_removeHierarchy();
    return false;
  } else {
    LOG_arbitrateConstraintLogicLogLine(
        "      [" + LOG_getExpressionText() + "] true");
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
    // Remove count from the constraint hierarchy for coverage
    LOG_removeHierarchy();
    return true;
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAForAllOperator::getSymbol() const
{
  return "For All";
}

const std::string
RBAForAllOperator::getExpressionText() const
{
  RBAExpression* exprLhs = getLhsOperand();
  return getSymbol() + " "
    + exprLhs->getExpressionText() + " "
    + getLambda()->getExpressionText();
}

const std::string
RBAForAllOperator::getCoverageExpressionText() const
{
  getLambda()->clearRuleObj();
  RBAExpression* exprLhs = getLhsOperand();
  return getSymbol() + " "
    + exprLhs->getCoverageExpressionText() + " "
    + getLambda()->getCoverageExpressionText();
}

RBAExpressionType
RBAForAllOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
