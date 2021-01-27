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
 * Abstract search class implementation file
 */

#include <memory>

#include "RBAAbstractCollector.hpp"

#include "RBAAllocatable.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAAllocatedContent.hpp"
#include "RBAAndOperator.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAContentValue.hpp"
#include "RBADisplayingContent.hpp"
#include "RBAExistsOperator.hpp"
#include "RBAForAllOperator.hpp"
#include "RBAGetAllocatables.hpp"
#include "RBAActiveState.hpp"
#include "RBAActiveContents.hpp"
#include "RBAGetContentsList.hpp"
#include "RBAGetProperty.hpp"
#include "RBAHasBeenDisplayed.hpp"
#include "RBAHasComeEarlierThan.hpp"
#include "RBAHasComeLaterThan.hpp"
#include "RBAIfStatement.hpp"
#include "RBAImpliesOperator.hpp"
#include "RBAIsActive.hpp"
#include "RBAIsAttenuated.hpp"
#include "RBAIsDisplayed.hpp"
#include "RBAIsEqualToOperator.hpp"
#include "RBAIsGreaterThanEqualOperator.hpp"
#include "RBAIsGreaterThanOperator.hpp"
#include "RBAIsHidden.hpp"
#include "RBAIsLowerThanEqualOperator.hpp"
#include "RBAIsLowerThanOperator.hpp"
#include "RBAIsMuted.hpp"
#include "RBAIsOn.hpp"
#include "RBAIsOutputted.hpp"
#include "RBAIsSounding.hpp"
#include "RBAIsVisible.hpp"
#include "RBALambdaExpression.hpp"
#include "RBAModelImpl.hpp"
#include "RBANotOperator.hpp"
#include "RBAObjectCompare.hpp"
#include "RBAOrOperator.hpp"
#include "RBAOutputtingSound.hpp"
#include "RBAPreviousModifier.hpp"
#include "RBAMaxOperator.hpp"
#include "RBAMinOperator.hpp"
#include "RBASelectOperator.hpp"
#include "RBASizeOperator.hpp"
#include "RBAResultImpl.hpp"
#include "RBAResultSet.hpp"
#include "RBAStateValue.hpp"
#include "RBAObjectReference.hpp"
#include "RBASetOfOperator.hpp"
#include "RBALetStatement.hpp"
#include "RBAOperator.hpp"
#include "RBAIsTypeOfOperator.hpp"
#include "RBAPreviousObjectWrapper.hpp"

namespace rba
{

RBAAbstractCollector::RBAAbstractCollector(RBAModelImpl* const model)
    : RBAExpressionVisitor(),
      model_{model},
      isLhs_{false},
      isPreviousModifier_{false},
      isPositive_{true},
      visitsLetStatement_{false}
{
}

// area status
void RBAAbstractCollector::visit(RBAIsDisplayed& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBADisplayingContent& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAAllocatedContent& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsHidden& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAContentValue& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAGetContentsList& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

void RBAAbstractCollector::visit(RBAActiveContents& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

// display content status
void RBAAbstractCollector::visit(RBAIsActive& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsVisible& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAStateValue& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAHasBeenDisplayed& exp)
{
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAHasComeEarlierThan& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAHasComeLaterThan& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAGetAllocatables& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAActiveState& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// zone status
void RBAAbstractCollector::visit(RBAIsOutputted& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAOutputtingSound& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// allocatedContent is common with area
void RBAAbstractCollector::visit(RBAIsMuted& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsAttenuated& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// contentValue is common with area
// contentsList is common with area

// sound content status
// isActive is common with display content
void RBAAbstractCollector::visit(RBAIsSounding& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// stateValue is common with display content
// hasComeEarlierThan is common with display content
// hasComeLaterThan is common with display content
// allocatables is common with display content

// scene status
void RBAAbstractCollector::visit(RBAIsOn& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAGetProperty& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

void RBAAbstractCollector::visit(RBAIsTypeOfOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}

// operator
void RBAAbstractCollector::visit(RBAAndOperator& exp)
{
  visitLetStatement(exp);
  for (RBAExpression* const ope : exp.getOperand()) {
    ope->accept(*this);
  }
}
void RBAAbstractCollector::visit(RBAOrOperator& exp)
{
  visitLetStatement(exp);
  for (RBAExpression* const ope : exp.getOperand()) {
    ope->accept(*this);
  }
}
void RBAAbstractCollector::visit(RBANotOperator& exp)
{
  visitLetStatement(exp);
  isPositive_ = !isPositive_;
  exp.getLhsOperand()->accept(*this);
  isPositive_ = !isPositive_;
}
void RBAAbstractCollector::visit(RBAImpliesOperator& exp)
{
  visitLetStatement(exp);
  const bool backup {isLhs_};
  exp.getLhsOperand()->accept(*this);
  isLhs_ = backup;
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsEqualToOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAObjectCompare& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsGreaterThanOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsGreaterThanEqualOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsLowerThanOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}
void RBAAbstractCollector::visit(RBAIsLowerThanEqualOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
  exp.getRhsOperand()->accept(*this);
}

// Quantification symbol
void RBAAbstractCollector::visit(RBAForAllOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitratorImpl dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // As you go through this path, you may be referencing the LetStatement's Variable
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBAExistsOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitratorImpl dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // As you go through this path, you may be referencing the LetStatement's Variable
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}

// Built-in definition expression
void RBAAbstractCollector::visit(RBAAllInstanceOfArea& exp)
{
  // This Visitor implementation refers to the set of ForAll and Exists with
  // ReferenceObject, sets it to Variable, and then accepts it to the body.
  // It does not accept to the set, so it does not pass through this path.
}
void RBAAbstractCollector::visit(RBAAllInstanceOfViewContent& exp)
{
  // This Visitor implementation refers to the set of ForAll and Exists with
  // ReferenceObject, sets it to Variable, and then accepts it to the body.
  // It does not accept to the set, so it does not pass through this path.
}
void RBAAbstractCollector::visit(RBAAllInstanceOfZone& exp)
{
  // This Visitor implementation refers to the set of ForAll and Exists with
  // ReferenceObject, sets it to Variable, and then accepts it to the body.
  // It does not accept to the set, so it does not pass through this path.
}
void RBAAbstractCollector::visit(RBAAllInstanceOfSoundContent& exp)
{
  // This Visitor implementation refers to the set of ForAll and Exists with
  // ReferenceObject, sets it to Variable, and then accepts it to the body.
  // It does not accept to the set, so it does not pass through this path.
}

// statement
void RBAAbstractCollector::visit(RBAIfStatement& exp)
{
  visitLetStatement(exp);
  const bool backup {isLhs_};
  isLhs_ = true;
  exp.getCondition()->accept(*this);
  isLhs_ = backup;
  exp.getThenExpression()->accept(*this);
  exp.getElseExpression()->accept(*this);
}
void RBAAbstractCollector::visit(RBALetStatement& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// modifier
void RBAAbstractCollector::visit(RBAPreviousModifier& exp)
{
  visitLetStatement(exp);
  const bool b_isPreviousModifier_ {isPreviousModifier_};
  isPreviousModifier_ = true;
  exp.getObjReference()->accept(*this);
  isPreviousModifier_ = b_isPreviousModifier_;
}
// max operator
void RBAAbstractCollector::visit(RBAMaxOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitratorImpl dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // As you go through this path, you may be referencing the LetStatement's Variable
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBAMinOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitratorImpl dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // As you go through this path, you may be referencing the LetStatement's Variable
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBASelectOperator& exp)
{
  visitLetStatement(exp);
  RBAConstraintInfo dummyInfo;
  RBAArbitratorImpl dummyArb;
  dummyArb.setModel(model_);
  dummyArb.setResult(std::make_unique<RBAResultImpl>(
      &dummyArb, std::make_unique<RBAResultSet>()));
  const RBARuleObject* const ruleObj {exp.getLhsOperand()->getReferenceObject(
      &dummyInfo, &dummyArb)};
  if (ruleObj != nullptr) {
    std::vector<const RBARuleObject*> objs;
    const RBARuleObject* const objset {ruleObj->getRawObject()};
    if (dynamic_cast<const RBAAllocatableSet*>(objset) != nullptr) {
      for (const auto& alloc : dynamic_cast<const RBAAllocatableSet*>(objset)
          ->getLeafAllocatable()) {
        objs.push_back(alloc);
      }
    } else {
      for (const auto& cont : dynamic_cast<const RBAContentSet*>(objset)
          ->getLeafContent()) {
        objs.push_back(cont);
      }
    }
    for (const RBARuleObject* const obj : objs) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  } else {
    // As you go through this path, you may be referencing the LetStatement's Variable
    for (auto& obj : letVal_) {
      exp.getLambda()->setRuleObj(obj);
      exp.getLambda()->getBodyText()->accept(*this);
    }
  }
}
void RBAAbstractCollector::visit(RBASizeOperator& exp)
{
  visitLetStatement(exp);
  exp.getLhsOperand()->accept(*this);
}
// object reference
void RBAAbstractCollector::visit(RBAObjectReference& exp)
{
  visitLetStatement(exp);
}
void RBAAbstractCollector::visit(RBASetOfOperator& exp)
{
  visitLetStatement(exp);
  for (RBAExpression* const ope : exp.getOperand()) {
    ope->accept(*this);
  }
}
void RBAAbstractCollector::visitLetStatement(RBAExpression& exp)
{
  const bool backup_let {visitsLetStatement_};
  visitsLetStatement_ = true;
  for (auto& letStatement : exp.getLetStatements()) {
    letStatement->accept(*this);
  }
  visitsLetStatement_ = backup_let;
}

std::set<const RBARuleObject*>& RBAAbstractCollector::getLetVal()
{
  return letVal_;
}

void RBAAbstractCollector::addLetVal(const RBARuleObject* const obj)
{
  static_cast<void>(letVal_.insert(obj));
}

bool RBAAbstractCollector::isVisitsLetStatement() const
{
  return visitsLetStatement_;
}

bool RBAAbstractCollector::isLhs() const
{
  return isLhs_;
}

void RBAAbstractCollector::setLhs(const bool lhs)
{
  isLhs_ = lhs;
}

bool RBAAbstractCollector::isPositive() const
{
  return isPositive_;
}

RBAModelImpl* RBAAbstractCollector::getModel() const
{
  return model_;
}

bool RBAAbstractCollector::isPreviousModifier() const 
{
  return isPreviousModifier_;
}

} /* namespace rba */
