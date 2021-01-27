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
 * RBASetOfOperator class definition
 */

#include <sstream>
#include "RBASetOfOperator.hpp"
#include "RBARuleObject.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContentSet.hpp"
#include "RBAAllocatable.hpp"
#include "RBAContent.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBASetOfOperator::RBASetOfOperator()
    : RBAOperator(),
      allocatableSet_{std::make_unique<RBAAllocatableSet>()},
      contentSet_{std::make_unique<RBAContentSet>()}
{
}

void
RBASetOfOperator::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBASetOfOperator::getModelElementType() const
{
  return RBAModelElementType::SetOfOperator;
}

const RBARuleObject*
RBASetOfOperator::getReferenceObjectCore(RBAConstraintInfo* info,
                                         RBAArbitratorImpl* arb) const
{
  allocatableSet_->clear();
  contentSet_->clear();

  bool isAllocatableSet {false};
  bool isContentSet {false};

  std::uint32_t i {0U};
  for(const RBAExpression* const expr : getOperand()) {
    RBAConstraintInfo* const childInfo {info->getChild(i)};
    const RBARuleObject* const obj {expr->getReferenceObject(childInfo,arb)};
    if(childInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
      return nullptr;
    }
    if(obj != nullptr) {
      if (obj->isModelElementType(RBAModelElementType::Area) ||
          obj->isModelElementType(RBAModelElementType::Zone)) {
        allocatableSet_->addTarget(dynamic_cast<const RBAAllocatable*>(obj));
        isAllocatableSet = true;
      }
      else if (obj->isModelElementType(RBAModelElementType::ViewContent) ||
               obj->isModelElementType(RBAModelElementType::SoundContent)) {
        contentSet_->addTarget(dynamic_cast<const RBAContent*>(obj));
        isContentSet = true;
      }
      else if (dynamic_cast<const RBAAllocatableSet*>(obj) != nullptr) {
        for (const RBAAllocatable* const a : dynamic_cast<const RBAAllocatableSet*>(obj)->getLeafAllocatable()) {
          allocatableSet_->addTarget(a);
        }
        isAllocatableSet = true;
      } else {
        for (const RBAContent* const c : dynamic_cast<const RBAContentSet*>(obj)->getLeafContent()) {
          contentSet_->addTarget(c);
        }
        isContentSet = true;
      }
    }
    i++;
  }
  if (isAllocatableSet) {
    return allocatableSet_.get();
  } else if (isContentSet){
    return contentSet_.get();
  } else {
    return nullptr;
  }
}

void
RBASetOfOperator::doActionCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb)
{
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy("SetOf");

  std::uint32_t i {0U};
  for(RBAExpression* const expr : getOperand()) {
    // Add number of element to Constraint hierarchy for coverage
    LOG_addHierarchy("#" + std::to_string(i) + ":");

    // Since it should only execute Action, info is as it is
    expr->doAction(info, arb);
    i++;

    // Remove number of element from Constraint hierarchy for coverage
    LOG_removeHierarchy();
  }
  // Remove itself from Constraint hierarchy for coverage
  LOG_removeHierarchy();

  return;
}

#ifdef RBA_USE_LOG
const std::string
RBASetOfOperator::getExpressionText() const
{
  std::ostringstream oss;
  oss << "{";
  const auto& exprList = getOperand();
  const auto& lastExpr = exprList.back();
  for (const auto& expr : exprList) {
    oss << expr->getExpressionText();
    if (expr != lastExpr) {
      oss << ", ";
    }
  }
  oss << "}";

  return oss.str();
}

const std::string
RBASetOfOperator::getCoverageExpressionText() const
{
  std::ostringstream oss;
  oss << "{";
  const auto& exprList = getOperand();
  const auto& lastExpr = exprList.back();
  for (const auto& expr : exprList) {
    oss << expr->getCoverageExpressionText();
    if (expr != lastExpr) {
      oss << ", ";
    }
  }
  oss << "}";

  return oss.str();
}

void
RBASetOfOperator::createHierarchy()
{
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy("SetOf");
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);
  uint32_t idx=0;
  for(RBAExpression* expr : getOperand()) {
    // Add number of element to Constraint hierarchy for coverage
    LOG_addHierarchy("#"+std::to_string(idx)+":");
    expr->createHierarchy();
    // Remove number of element from Constraint hierarchy for coverage
    LOG_removeHierarchy();
    idx++;
  }
  // Remove itself from Constraint hierarchy for coverage
  LOG_removeHierarchy();
}

RBAExpressionType
RBASetOfOperator::getUnderlyingType() const
{
  return getLhsOperand()->getUnderlyingType();
}
#endif

}
