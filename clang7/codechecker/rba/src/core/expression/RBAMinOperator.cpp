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

/// MinOperator class definition

#include "RBAMinOperator.hpp"
#include "RBAAllocatable.hpp"
#include "RBAContent.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALambdaExpression.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBAMinOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAMinOperator::getModelElementType() const
{
  return RBAModelElementType::MinOperator;
}

const RBARuleObject* RBAMinOperator::getReferenceObjectCore(
    RBAConstraintInfo* info, RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  const RBARuleObject* returnObj {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const lhsObj {getLhsOperand()->getReferenceObject(leftInfo,
                                                                    arb)};
  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (lhsObj != nullptr) {
      const RBAAllocatableSet* alloSet = dynamic_cast<const RBAAllocatableSet*>(lhsObj);
      if (alloSet != nullptr) {
        std::uint32_t i { 0U };
        std::int32_t minVal { INT32_MAX };
        RBALambdaExpression* const lambda { getLambda() };
        for (auto& obj : alloSet->getLeafAllocatable()) {
          LOG_addHierarchy("#" + std::to_string(i));
          ++i;
          RBAConstraintInfo* const childInfo { info->getChild(i) };
          lambda->setRuleObj(obj);
          const std::int32_t val { lambda->getValue(childInfo, arb) };
          LOG_removeHierarchy();
          if ((val != -99) && (minVal > val)
              && (!childInfo->isExceptionBeforeArbitrate())) {
            minVal = val;
            returnObj = obj;
          }
        }
      } else {
        const RBAContentSet* contentSet = dynamic_cast<const RBAContentSet*>(lhsObj);
        if (contentSet != nullptr) {
          std::uint32_t i { 0U };
          std::int32_t minVal { INT32_MAX };
          RBALambdaExpression* const lambda { getLambda() };
          for (auto& obj : contentSet->getLeafContent()) {
            LOG_addHierarchy("#" + std::to_string(i));
            ++i;
            RBAConstraintInfo* const childInfo { info->getChild(i) };
            lambda->setRuleObj(obj);
            const std::int32_t val { lambda->getValue(childInfo, arb) };
            LOG_removeHierarchy();
            if ((val != -99) && (minVal > val)
                && (!childInfo->isExceptionBeforeArbitrate())) {
              minVal = val;
              returnObj = obj;
            }
          }
        }
      }
    }
  }
#ifdef RBA_USE_LOG
  std::string objName = "NULL";
  if (info->isExceptionBeforeArbitrate()) {
    objName = "before arbitrate skip";
  } else {
    if (returnObj != nullptr){
      objName = returnObj->getElementName();
      if (objName == "") {
        objName = returnObj->getDynamicName();
      }
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      " + LOG_getExpressionText() + " is " + objName);
#endif
  LOG_removeHierarchy();
  return returnObj;
}
#ifdef RBA_USE_LOG
const std::string RBAMinOperator::getSymbol() const
{
  return ".mix";
}

const std::string RBAMinOperator::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol()
      + getLambda()->getExpressionText();
}

const std::string RBAMinOperator::getCoverageExpressionText() const
{
  getLambda()->clearRuleObj();
  return getLhsOperand()->getCoverageExpressionText() + getSymbol()
      + getLambda()->getCoverageExpressionText();
}
#endif

} // namespace rba
