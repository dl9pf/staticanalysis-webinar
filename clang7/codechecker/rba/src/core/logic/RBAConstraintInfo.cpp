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

/// ConstraintInfo class

#include <algorithm>
#include "RBAAllocatable.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAExpression.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void RBAConstraintInfo::setExpression(const RBAExpression* const expression)
{
  expression_ = expression;
}

const RBAExpression*
RBAConstraintInfo::getExpression() const
{
  return expression_;
}

void RBAConstraintInfo::addOperandAllocatable(const RBAAllocatable* const operandAllocatable)
{
  static_cast<void>(operandAllocatable_.insert(operandAllocatable));
}

void RBAConstraintInfo::setResult(const RBAExecuteResult result)
{
  result_ = result;
}

RBAConstraintInfo*
RBAConstraintInfo::getChild(const std::uint32_t index) const
{
  const std::size_t requiredSize {static_cast<std::size_t>(index + 1U)};
  if (children_.size() < requiredSize) {
    children_.resize(requiredSize, std::make_unique<RBAConstraintInfo>());
  }
  // Use "[]" instead of "at" because it doesn't access out of range
  return children_[static_cast<std::size_t>(index)].get();
}

void RBAConstraintInfo::setChild(const std::shared_ptr<RBAConstraintInfo> info)
{
  // This function is used in "let" expressions, which generate a new 
  // "ConstraintInfo" on each evaluation.
  // Therefore, in the case of "add", "children" will be added for each arbitration, 
  // so use "set" to set "children" for each arbitration.
  children_ = { info };
}

void RBAConstraintInfo::addTrueAllocatable(const RBAAllocatable* const allocatable)
{
  static_cast<void>(trueAllocatables_.insert(allocatable));
}

void RBAConstraintInfo::addFalseAllocatable(const RBAAllocatable* const allocatable)
{
  static_cast<void>(falseAllocatables_.insert(allocatable));
}

void RBAConstraintInfo::addTrueAllocatableFromOperand()
{
  for (const auto& c : children_) {
    for (const auto& a : c->operandAllocatable_) {
      static_cast<void>(trueAllocatables_.insert(a));
    }
  }
}

void RBAConstraintInfo::addFalseAllocatableFromOperand()
{
  for (const auto& c : children_) {
    for (const auto& a : c->operandAllocatable_) {
      static_cast<void>(falseAllocatables_.insert(a));
    }
  }
}

void RBAConstraintInfo::clearFalseAllocatable()
{
  falseAllocatables_.clear();
}

/// TCheck whether to invert True/False
/// @return
bool RBAConstraintInfo::isRevert() const
{
  if ((expression_ != nullptr)
      && expression_->isModelElementType(RBAModelElementType::NotOperator)) {
    return true;
  }
  return false;
}

bool RBAConstraintInfo::isSizeOperator() const
{
  if ((expression_ != nullptr)
      && (expression_->isModelElementType(RBAModelElementType::SizeOperator))) {
    return true;
  }
  return false;
}

const bool RBAConstraintInfo::isImplies() const
{
  if ((expression_ != nullptr)
      && (expression_->isModelElementType(RBAModelElementType::ImpliesOperator)
          || expression_->isModelElementType(RBAModelElementType::IfStatement))) {
    return true;
  }
  return false;
}

void RBAConstraintInfo::clear()
{
  for (const std::shared_ptr<RBAConstraintInfo>& child : children_) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    //  [Contents that deviate from the rules]
    //   recursively calling clear()
    //   [Reason that there is no problem if the rule is deviated]
    //   ConstraintInfo is created for each node in the Constraint expression 
    //   tree. The Constraint expression tree is determined by the constraint 
    //   expressions written in the model file, and its depth is finite.
    //   Therefore, stack overflow does not occur and there is no problem
    child->clear();
  }
  result_ = RBAExecuteResult::SKIP;
  exceptionBeforeArbitrate_ = false;
  trueAllocatables_.clear();
  falseAllocatables_.clear();
  operandAllocatable_.clear();
}

bool RBAConstraintInfo::isExceptionBeforeArbitrate() const
{
  return exceptionBeforeArbitrate_;
}

void RBAConstraintInfo::setExceptionBeforeArbitrate(
    const bool exceptionBeforeArbitrate)
{
  exceptionBeforeArbitrate_ = exceptionBeforeArbitrate;
}

bool RBAConstraintInfo::needsReRearbitrationFor(
    const RBAAllocatable* const allocatable) const
{
  bool result {false};
  if (children_.empty() == false) {
    switch (expression_->getModelElementType()) {
      case RBAModelElementType::ImpliesOperator:
        if (children_.front()->isExceptionBeforeArbitrate()) {
          result = children_.back()->needsReRearbitrationFor(allocatable);
        }
        break;
      case RBAModelElementType::IfStatement:
        if (children_.front()->isExceptionBeforeArbitrate()) {
          // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
          //  [Contents that deviate from the rules]
          //   Function '::rba::RBAConstraintInfo::needsReRearbitrationFor=(_,
          //                          p={c::rba::RBAAllocatable})' is recursive.
          //   [Reason that there is no problem if the rule is deviated]
          //   Recursive call is required as a feature
          result = children_.back()->needsReRearbitrationFor(allocatable);
        }
        break;
      default:
        for (const auto& child : children_) {
          result = (result || child->needsReRearbitrationFor(allocatable));
        }
        result =
            (result || (trueAllocatables_.find(allocatable)  != trueAllocatables_.end())
                    || (falseAllocatables_.find(allocatable) != falseAllocatables_.end()));
        break;
    }
  }
  return result;
}

bool RBAConstraintInfo::needsRearbitrationFor(const RBAAllocatable* const allocatable,
                                              bool isImplies) const
{
  bool result {false};  // Necessity of re-arbitration
  if (children_.empty() == false) {
    // When the syntax of the constraint expression is 
    //  - ImpliesOperator
    //  - IfStatement 
    //  - other than the above
    switch (expression_->getModelElementType()) {
      case RBAModelElementType::ImpliesOperator:
        // If the left side of the implication is true and 
        // the left side contains an Allocatable during arbitration, 
        // re-arbitration is required.
        //
        // If the left side of the implication is true and 
        // the left side contains an allocatable state reference expression, 
        // re-arbitration is NOT required.
        if (children_.front()->isTrue()) {
          if (children_.front()->contains(allocatable)) {
            result = true;
          } else {
            if (children_.front()->contains(nullptr)) {
              isImplies = true;
            }
            result = (result || children_.back()->needsRearbitrationFor(allocatable,
                      isImplies));
          }
        }
        break;
      case RBAModelElementType::IfStatement:
        // If the IF condition includes Allocatble in arbitration, 
        // re-arbitration is required.
        // If the IF condition includes an Allocatable state reference 
        // expression, re-arbitration is NOT required.
        // If the IF condition does not include an allocatable state reference 
        // expression, search the child syntax.
        if (children_.front()->contains(allocatable)) {
          result = true;
        } else {
          if (children_.front()->contains(nullptr)) {
            isImplies = true;
          }
          result = (result || children_.back()->needsRearbitrationFor(allocatable,
                                                                      isImplies));
        }
        break;
      default:
        for (const auto& child : children_) {
          // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
          //  [Contents that deviate from the rules]
          //   Function '::rba::RBAConstraintInfo::needsRearbitrationFor=(_,
          //                       p={c::rba::RBAAllocatable},_o)' is recursive. 
          //   [Reason that there is no problem if the rule is deviated]
          //   Recursive call is required as a feature
          result = (result || child->needsRearbitrationFor(allocatable, isImplies));
        }
        // The Constraint expression does not include IF or implication,
        //  or
        // the Allocatable state reference expression is not included  in the 
        // left side of the IF condition of the parent syntax or 
        // the implication of the parent syntax,
        //  or
        // "Allocable" during arbitration is included in the left side of 
        // the IF condition of the parent syntax or the implication of the 
        // parent syntax,
        //
        // re-arbitration is required.
        if (!isImplies && contains(allocatable)) {
          result = true;
        }
        break;
    }
  }
  return result;
}

/// @brief Collect "Allocatable" whose right side is false.
/// @details
///  - Do not collect if an exception has occurred
///  - When expression_ is nullptr or When expression_ is implication
///    - If the left side is satisfied and there is a condition on the left 
///      side that is affected by the allocatable state, collect the 
///      allocatable that caused the right side to be false.
///    - If the left side is satisfied and there is NO condition affected by 
///      the allocatable state on the left side, this function is called on 
///      the right side. (To correspond to implication or IF nest)
///  - When expression_ is IF
///    - If there is a condition on the left side that is affected by the 
///      "Allocatable" state, collect the "Allocatable that caused the 
///      right side to be false.
///    - If there is no condition affected by the allocatable state on the left 
///      side, call this function for the right side. 
///      (To correspond to the implication or nest of IF)
///  - When expression_ is negative
///    - Call this function with "isNot" inverted for the left side.
///      (To deal with implications or IFs present in children.)
///  - When expression_ is above
///    - Call this function for the child ConstraintInfo. 
///      (To deal with implications or IFs present in children.)
/// @param[in] allocatable "Allcatable" during arbitration
/// @param[out] targets "Allocatable" for re-arbitration
/// @param[in] isNot Inversion state of right and wrong by negation operator.
void RBAConstraintInfo::collectRearbitrationTargetFor(
    const RBAAllocatable* const allocatable, std::set<const RBAAllocatable*>& targets,
    const bool isNot) const
{
  if (isExceptionBeforeArbitrate()) {
    return;
  }
  if (children_.empty() == false) {
    switch (expression_->getModelElementType()) {
      case RBAModelElementType::ImpliesOperator:
        if (children_.front()->isTrue()) {
          if (isNot) {
            children_.back()->collectTrueAllocatables(targets);
          } else {
            children_.back()->collectFalseAllocatables(targets);
          }
        } else if (!children_.front()->isFalse()) {
          children_.back()->collectRearbitrationTargetFor(allocatable, targets,
                                                          isNot);
        } else {
        }
        break;
      case RBAModelElementType::IfStatement:
        if (isNot) {
          children_.back()->collectTrueAllocatables(targets);
        } else {
          children_.back()->collectFalseAllocatables(targets);
        }
        break;
      case RBAModelElementType::NotOperator:
        // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
        //  [Contents that deviate from the rules]
        //   Function '::rba::RBAConstraintInfo::collectRearbitrationTargetFor=(_,p={c::rba::RBAAllocatable},
        //     &{c::std::set<p={c::rba::RBAAllocatable},{c::std::less<p={c::rba::RBAAllocatable}>},
        //     {c::std::allocator<p={c::rba::RBAAllocatable}>}>},_o)' is recursive. 
        //   [Reason that there is no problem if the rule is deviated]
        //   Recursive call is required as a feature
        children_.front()->collectRearbitrationTargetFor(allocatable, targets,
                                                         !isNot);
        break;
      default:
        for (const auto& child : children_) {
          child->collectRearbitrationTargetFor(allocatable, targets, isNot);
        }
        break;
    }
  }
}

void RBAConstraintInfo::collectTrueAllocatables(
    std::set<const RBAAllocatable*>& allocatables) const
{
  if (isExceptionBeforeArbitrate() || isFalse()) {
    return;
  }
  if (isRevert()) {
    for (const auto& child : children_) {
      child->collectFalseAllocatables(allocatables);
    }
    allocatables.insert(falseAllocatables_.begin(), falseAllocatables_.end());
  } else if (isImplies()) {
    children_.back()->collectTrueAllocatables(allocatables);
  } else if (isSizeOperator()) {
    // Since the size operator evaluates the number of sets, 
    // the Allocatable that combines FalseAllocatable and TrueAllocatable 
    // becomes TrueAllocatables.
    children_.back()->collectTrueAllocatables(allocatables);
    children_.back()->collectFalseAllocatables(allocatables);
  } else {
    for (const auto& child : children_) {
      // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
      //  [Contents that deviate from the rules]
      //   Function '::rba::RBAConstraintInfo::collectTrueAllocatables=(_,
      //     &{c::std::set<p={c::rba::RBAAllocatable},
      //     {c::std::less<p={c::rba::RBAAllocatable}>},
      //     {c::std::allocator<p={c::rba::RBAAllocatable}>}>})' is recursive. 
      //   [Reason that there is no problem if the rule is deviated]
      //   Recursive call is required as a feature
      child->collectTrueAllocatables(allocatables);
    }
    allocatables.insert(trueAllocatables_.begin(), trueAllocatables_.end());
  }
  return;
}

void RBAConstraintInfo::collectFalseAllocatables(
    std::set<const RBAAllocatable*>& allocatables) const
{
  if (isExceptionBeforeArbitrate() || isTrue()) {
    return;
  }
  if (isRevert()) {
    for (const auto& child : children_) {
      child->collectTrueAllocatables(allocatables);
    }
    allocatables.insert(trueAllocatables_.begin(), trueAllocatables_.end());
  } else if (isImplies()) {
    children_.back()->collectFalseAllocatables(allocatables);
  } else if (isSizeOperator()) {
    // The size operator evaluates the number of sets, so "Allocatable", 
    // which is a combination of "FalseAllocatable" and "TrueAllocatable", 
    // becomes "FalseAllocatables".
    children_.back()->collectTrueAllocatables(allocatables);
    children_.back()->collectFalseAllocatables(allocatables);
  } else {
    for (const auto& child : children_) {
      // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
      //  [Contents that deviate from the rules]
      //   Function '::rba::RBAConstraintInfo::collectFalseAllocatables=(_,
      //           &{c::std::set<p={c::rba::RBAAllocatable},
      //           {c::std::less<p={c::rba::RBAAllocatable}>},
      //           {c::std::allocator<p={c::rba::RBAAllocatable}>}>})' 
      //   is recursive. 
      //   [Reason that there is no problem if the rule is deviated]
      //   Recursive call is required as a feature
      child->collectFalseAllocatables(allocatables);
    }
    allocatables.insert(falseAllocatables_.begin(), falseAllocatables_.end());
  }
  return;
}

bool RBAConstraintInfo::contains(const RBAAllocatable* const allocatable) const
{
  if (allocatable != nullptr) {
    if (trueAllocatables_.find(allocatable) != trueAllocatables_.end()) {
      return true;
    }
    if (falseAllocatables_.find(allocatable) != falseAllocatables_.end()) {
      return true;
    }
  } else {
    if (!trueAllocatables_.empty() || !falseAllocatables_.empty()) {
      return true;
    }
  }
  for (const auto& child : children_) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    //  [Contents that deviate from the rules]
    //   Function '::rba::RBAConstraintInfo::contains=(_,
    //                                p={c::rba::RBAAllocatable})' 
    //   is recursive. 
    //   [Reason that there is no problem if the rule is deviated]
    //   Recursive call is required as a feature
    if (child->contains(allocatable)) {
      return true;
    }
  }
  return false;
}

bool RBAConstraintInfo::isTrue() const
{
  return (result_ == RBAExecuteResult::TRUE);
}

bool RBAConstraintInfo::isFalse() const
{
  return (result_ == RBAExecuteResult::FALSE);
}

void RBAConstraintInfo::collectAffectedAllocatables(
    const bool isRevert, std::set<const RBAAllocatable*>& affectAllocatables,
    const bool collecting,
    const bool forObject)
{
  // Collect the allocatable that caused the constraint expression to be False.
  // It is implemented by recursively calling ConstraintInfo of the tree 
  // structure created at the time of "Constraint" expression evaluation.
  // with this function.
  // Collect True because the success or failure of ConstraintInfo below 
  // "negative" is reversed.
  switch (getExpression()->getModelElementType()) {
    case RBAModelElementType::NotOperator:
      // ConstraintInfo below negative negates success or failure, 
      // so invert isRevert and call child Info.
      children_[0U]->collectAffectedAllocatables(!isRevert, affectAllocatables,
                                                 collecting, forObject);
      break;
    case RBAModelElementType::SizeOperator:
      // Since the size operator evaluates the number of sets, 
      // "Allocatable" which is a combination of "FalseAllocatable" and 
      // "TrueAllocatable" becomes "affectAllocatables".
      children_[0U]->collectAffectedAllocatables(false, affectAllocatables,
                                                 true, true);
      break;
    case RBAModelElementType::OrOperator:
    case RBAModelElementType::ExistsOperator:
      // the same processing is performed, because "Exists {A,B}{x|x.isXXX}" 
      // is equivalent to "A.isXXX OR B.isXXX"
      if (!isRevert) {
        // Processing when "Info" of "OR"  in which evaluation result that is not 
        // qualified by an odd number of negative is "Skip" or evaluation reslt 
        // that is not qualified by an odd number of negative is "False".
        if (!isTrue()) {
          // Collect the Allocatable of child Info whose 
          // whose evaluation result is False.
          // When "A.isXXX OR B.isXXX", if the evaluation result of A is True, 
          // the evaluation result of OR will be True even if the evaluation 
          // result of B is False. Therefore, A affects B. 
          // Conversely, B also affects A.
          // Therefore, set "collecting" to True and 
          // search "child Info" for allocatable.
          for (auto& i : children_) {
            i->collectAffectedAllocatables(isRevert, affectAllocatables, true,
                                           forObject);  // Collct when "OR"
          }
        }
      } else {
        // Processing when "Info" of "OR"  in which evaluation result that is not 
        // qualified by an odd number of negative is "Skip" or evaluation reslt 
        // that is not qualified by an odd number of negative is "False".
        // "!(A.isXXX OR B.isXXX)" can be decomposed into 
        // "!A.isXXX AND !B.isXXX", so if "NOT", perform the same processing 
        // as "AND".
        if (!isFalse()) {
          for (auto& i : children_) {
            i->collectAffectedAllocatables(isRevert, affectAllocatables,
                                           collecting, forObject);
          }
        }
      }
      break;
    case RBAModelElementType::AndOperator:
    case RBAModelElementType::ForAllOperator:
      //"For-All {A,B}{x|x.isXXX}" is equivalent to "A.isXXX AND B.isXXX", 
      // so the same processing is performed
      if (isRevert) {
        // Processing when "Info" of "AND"  in which evaluation result that 
        // is not qualified by an odd number of "negative" is "Skip" or 
        // evaluation reslt that is not qualified by an odd number of negative 
        // is "True".
        //
        // "!(A.isXXX AND B.isXXX)" can be decomposed into 
        // "!A.isXXX OR !B.isXXX", so if "NOT", perform the same processing 
        // as "OR".
        if (!isFalse()) {
          for (auto& i : children_) {
            // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
            //  [Contents that deviate from the rules]
            //   Function '::rba::RBAConstraintInfo::collectAffectedAllocatables(_,_o,&{c::std::set<p={c::rba::RBAAllocatable},
            //   {c::std::less<p={c::rba::RBAAllocatable}>},{c::std::allocator<p={c::rba::RBAAllocatable}>}>},_o)' is recursive.
            //   [Reason that there is no problem if the rule is deviated]
            //   Recursive call is required as a feature
            i->collectAffectedAllocatables(isRevert, affectAllocatables, true,
                                           forObject);
          }
        }
      } else {
        // Processing when "Info" of "AND"  in which evaluation result that 
        // is not qualified by an odd number of "negative" is "Skip" or 
        // evaluation reslt that is not qualified by an odd number of negative 
        // is "True".
        //
        // When "A.isXXX AND B.isXXX", the evaluation result of "AND" does not 
        // become True unless the evaluation result of B becomes True, 
        // regardless of the evaluation result of A.  Therefore, A does not 
        // affect B, and B does not affect A.
        // Therefore, "collecting" is as it is, and the "child Info" is 
        // searched for an allocable influence.
        if (!isTrue()) {
          for (auto& i : children_) {
            i->collectAffectedAllocatables(isRevert, affectAllocatables,
                                           collecting, forObject);
          }
        }
      }
      break;
    case RBAModelElementType::MaxOperator:
    case RBAModelElementType::MinOperator:
    {
      // When the <set> expression is "IF(A.isDisplayed) THEN {B,C} ELSE {D,E}", 
      // scan the left side to extract A as the area of influence
      children_[0U]->collectAffectedAllocatables(false, affectAllocatables,
                                                 collecting,forObject);
      // All the operands that are "x" in the lambda expression affect 
      // each other, so it is necessary to extract them as the affected Area.
      for (std::uint8_t i { 1U }; i < children_.size(); ++i) {
        children_[i]->collectAffectedAllocatables(isRevert, affectAllocatables,
                                                  true, true);
      }
      break;
    }
    // "A -> B" is the same as "!A OR B".
    case RBAModelElementType::ImpliesOperator:
      if (!isRevert) {
        if (!isTrue()) {
          // "A.isXXX -> B.isXXX" can be decomposed into "!A.isXXX OR B.isXXX", 
          // so the same process as OR is performed
          // For the above reason, the acquisition target on the left side 
          // inverts isRevert.
          children_[0U]->collectAffectedAllocatables(!isRevert,
                                                     affectAllocatables, true,
                                                     forObject);
          children_[1U]->collectAffectedAllocatables(isRevert,
                                                     affectAllocatables, true,
                                                     forObject);
        }
      } else {
        if (!isFalse()) {
          // "!(A.isXXX -> B.isXXX)" can be decomposed into "A.isXXX OR !B.isXXX"
          // For the above reason, the acquisition target on the left side 
          // inverts isRevert.
          children_[0U]->collectAffectedAllocatables(!isRevert,
                                                     affectAllocatables,
                                                     collecting, forObject);
          children_[1U]->collectAffectedAllocatables(isRevert,
                                                     affectAllocatables,
                                                     collecting, forObject);
        }
      }
      break;
    case RBAModelElementType::IfStatement:
    // "IF(A) THEN B ELSE C" is the same as "!A OR B" if A is True, 
    // and the same as "A OR C" if A is False
      if (children_[0U]->isTrue()) {
        if (!isRevert) {
          if (!isTrue()) {
            // "IF(A.isXXX) THEN B.isXXX ELSE C.isXXX" can be decomposed into 
            // "(!A.isXXX OR B.isXXX)" when A is True.
            // For the above reason, the acquisition target on the left side 
            // inverts isRevert.
            children_[0U]->collectAffectedAllocatables(!isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        } else {
          if (!isFalse()) {
            // "!(IF(A.isXXX) THEN B.isXXX ELSE C.isXXX)" can be decomposed into 
            // "(!A.isXXX OR !B.isXXX)" when A is True.
            // For the above reason, the acquisition target on the left side 
            // inverts isRevert.
            children_[0U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        }
      } else {
        if (!isRevert) {
          if (!isTrue()) {
            // "IF(A.isXXX) THEN B.isXXX ELSE C.isXXX" can be decomposed into 
            // "(A.isXXX OR C.isXXX)" when A is False.
            children_[0U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        } else {
          if (!isFalse()) {
            // "!(IF(A.isXXX) THEN B.isXXX ELSE C.isXXX)" can be decomposed into 
            // "(A.isXXX OR !C.isXXX)" when A is False.
            children_[0U]->collectAffectedAllocatables(!isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
            children_[1U]->collectAffectedAllocatables(isRevert,
                                                       affectAllocatables, true,
                                                       forObject);
          }
        }
      }
      break;
    default:  // Collect Allocatable
      if (collecting) {
        if (isRevert) {
          affectAllocatables.insert(trueAllocatables_.begin(),
                                    trueAllocatables_.end());
        } else {
          affectAllocatables.insert(falseAllocatables_.begin(),
                                    falseAllocatables_.end());
        }
        if (forObject) {
          for (const auto& a : operandAllocatable_) {
            affectAllocatables.insert(a);
          }
        }
      }
      for (auto& i : children_) {
        i->collectAffectedAllocatables(isRevert, affectAllocatables, collecting,
                                       forObject);
      }
      break;
  }
  return;
}

}

