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
 * LambdaContext class definition file
 */

#include "RBALambdaContext.hpp"
#include "RBALogManager.hpp"
#include "RBAVariable.hpp"
#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBALambdaExpression* const
RBALambdaContext::getLambda() const
{
  return lambda_;
}

void
RBALambdaContext::setLambda(RBALambdaExpression* const newLambda)
{
  lambda_ = newLambda;
}

#ifdef RBA_USE_LOG
void
RBALambdaContext::createHierarchy()
{
  lambda_->getX()->clearRuleObj();
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  // Get rule object and loop
  RBAExpression* setObj = getLhsOperand();
  RBAConstraintInfo dummyInfo;
  // Since it is not referenced by "AllInstanceOf..." or "SetOfOperator" 
  // used for the set of "For-All" or "Exists", nullptr is no problem
  RBAArbitratorImpl* dummyArb = nullptr;
  const RBARuleObject* objset = setObj->getReferenceObject(&dummyInfo, dummyArb);
  std::vector<const RBARuleObject*> objs;
  if(objset) {
    if(dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      const RBAAllocatableSet* aSet
	= dynamic_cast<const RBAAllocatableSet*>(objset);
      for(const auto& alloc : aSet->getLeafAllocatable()) {
	objs.push_back(alloc);
      }
    }
    else if(dynamic_cast<const RBAContentSet*>(objset) != nullptr) {
      const RBAContentSet* cSet = dynamic_cast<const RBAContentSet*>(objset);
      for(const auto& cont : cSet->getLeafContent() ){
	objs.push_back(cont);
      }
    }
  }

  // Enable expansion of own variables in the coverage log
  std::int32_t idx=0;
  for(const RBARuleObject* obj : objs) {
    LOG_addHierarchy("#" + std::to_string(idx++));
    lambda_->getX()->setRuleObj(obj);
    lambda_->createHierarchy();
    LOG_removeHierarchy();
  }

  // Remove own to Constraint hierarchy for coverage
  LOG_removeHierarchy();
}
#endif

}
