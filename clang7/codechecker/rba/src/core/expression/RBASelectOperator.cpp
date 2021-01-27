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
 * SelectOperator class definition
 */

#include <memory>
#include "RBASelectOperator.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALambdaExpression.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASelectOperator::RBASelectOperator()
: RBALambdaContext(),
  allocatableSet_{std::make_unique<RBAAllocatableSet>()},
  contentSet_{std::make_unique<RBAContentSet>()}
{
}

void
RBASelectOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBASelectOperator::getModelElementType() const
{
  return RBAModelElementType::SelectOperator;
}

const RBARuleObject* RBASelectOperator::getReferenceObjectCore(
    RBAConstraintInfo* info, RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  const RBARuleObject* returnObj {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const lhsObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                    arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else if (lhsObj != nullptr) {
    if (dynamic_cast<const RBAAllocatableSet*>(lhsObj) != nullptr) {
      std::list<const RBAAllocatable*> objs {
          dynamic_cast<const RBAAllocatableSet*>(lhsObj)->getLeafAllocatable()};
      allocatableSet_->clear();
      std::uint32_t i {0U};
      RBALambdaExpression* const lambda {getLambda()};
      for (auto& obj : objs) {
        LOG_addHierarchy("#" + std::to_string(i));
        ++i;
        RBAConstraintInfo* const childInfo {info->getChild(i)};
        lambda->setRuleObj(obj);
        const bool isPassed {lambda->execute(childInfo, arb)};
        LOG_removeHierarchy();
        if (isPassed && (!childInfo->isExceptionBeforeArbitrate())) {
          allocatableSet_->addTarget(obj);
        }
      }
      returnObj = allocatableSet_.get();
    } else {
      std::list<const RBAContent*> objs {
          dynamic_cast<const RBAContentSet*>(lhsObj)->getLeafContent()};
      contentSet_->clear();
      std::uint32_t i {0U};
      RBALambdaExpression* const lambda {getLambda()};
      for (auto& obj : objs) {
        LOG_addHierarchy("#" + std::to_string(i));
        ++i;
        RBAConstraintInfo* const childInfo {info->getChild(i)};
        lambda->setRuleObj(obj);
        const bool isPassed {lambda->execute(childInfo, arb)};
        LOG_removeHierarchy();
        if (isPassed && (!childInfo->isExceptionBeforeArbitrate())) {
          contentSet_->addTarget(obj);
        }
      }
      returnObj = contentSet_.get();
    }
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  std::string objName = "NULL";
  if (returnObj != nullptr) {
    objName = returnObj->getElementName();
    if (objName == "") {
      objName = returnObj->getDynamicName();
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      " + LOG_getExpressionText() + " is " + objName);
#endif
  LOG_removeHierarchy();
  return returnObj;
}
#ifdef RBA_USE_LOG
const std::string RBASelectOperator::getSymbol() const
{
  return ".select";
}

const std::string RBASelectOperator::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol()
      + getLambda()->getExpressionText();
}

const std::string RBASelectOperator::getCoverageExpressionText() const
{
  getLambda()->clearRuleObj();
  return getLhsOperand()->getCoverageExpressionText() + getSymbol()
      + getLambda()->getCoverageExpressionText();
}
#endif

} // namespace rba
