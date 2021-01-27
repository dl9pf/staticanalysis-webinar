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
 * Expression visitor class header file
 */

#ifndef RBAEXPRESSIONVISITOR_HPP
#define RBAEXPRESSIONVISITOR_HPP

namespace rba {
class RBAIsDisplayed;
class RBADisplayingContent;
class RBAAllocatedContent;
class RBAIsHidden;
class RBAContentValue;
class RBAGetContentsList;
class RBAIsActive;
class RBAIsVisible;
class RBAStateValue;
class RBAHasBeenDisplayed;
class RBAHasComeEarlierThan;
class RBAHasComeLaterThan;
class RBAGetAllocatables;
class RBAIsOutputted;
class RBAOutputtingSound;
class RBAIsMuted;
class RBAIsAttenuated;
class RBAIsSounding;
class RBAIsOn;
class RBAGetProperty;
class RBAAndOperator;
class RBAOrOperator;
class RBANotOperator;
class RBAImpliesOperator;
class RBAIsEqualToOperator;
class RBAObjectCompare;
class RBAIsGreaterThanOperator;
class RBAIsGreaterThanEqualOperator;
class RBAIsLowerThanOperator;
class RBAIsLowerThanEqualOperator;
class RBAForAllOperator;
class RBAExistsOperator;
class RBAAllInstanceOfArea;
class RBAAllInstanceOfViewContent;
class RBAAllInstanceOfZone;
class RBAAllInstanceOfSoundContent;
class RBAIfStatement;
class RBALetStatement;
class RBAPreviousModifier;
class RBAActiveState;
class RBAActiveContents;
class RBAMaxOperator;
class RBAMinOperator;
class RBASelectOperator;
class RBASizeOperator;
class RBAObjectReference;
class RBASetOfOperator;
class RBAIsTypeOfOperator;

class RBAExpressionVisitor {
 public:
  RBAExpressionVisitor()=default;
  RBAExpressionVisitor(const RBAExpressionVisitor&)=delete;
  RBAExpressionVisitor(const RBAExpressionVisitor&&)=delete;
  RBAExpressionVisitor& operator=(const RBAExpressionVisitor&)=delete;
  RBAExpressionVisitor& operator=(const RBAExpressionVisitor&&)=delete;
  virtual ~RBAExpressionVisitor() = default;

  // Refer to Area status
  virtual void visit(RBAIsDisplayed& exp) = 0;
  virtual void visit(RBADisplayingContent& exp) = 0;
  virtual void visit(RBAAllocatedContent& exp) = 0;
  virtual void visit(RBAIsHidden& exp) = 0;
  virtual void visit(RBAContentValue& exp) = 0;
  virtual void visit(RBAGetContentsList& exp) = 0;
  virtual void visit(RBAActiveContents& exp) = 0;

  // Refer to display content status
  virtual void visit(RBAIsActive& exp) = 0;
  virtual void visit(RBAIsVisible& exp) = 0;
  virtual void visit(RBAStateValue& exp) = 0;
  virtual void visit(RBAHasBeenDisplayed& exp) = 0;
  virtual void visit(RBAHasComeEarlierThan& exp) = 0;
  virtual void visit(RBAHasComeLaterThan& exp) = 0;
  virtual void visit(RBAGetAllocatables& exp) = 0;
  virtual void visit(RBAActiveState& exp) = 0;

  // Refer to Zone status
  virtual void visit(RBAIsOutputted& exp) = 0;
  virtual void visit(RBAOutputtingSound& exp) = 0;
  // allocatedContent  is common with Area
  virtual void visit(RBAIsMuted& exp) = 0;
  virtual void visit(RBAIsAttenuated& exp) = 0;
  // contentValue is common with Area
  // contentsList  is common with Area

  // Refer to sound content status
  // isActive is common with display content
  virtual void visit(RBAIsSounding& exp) = 0;
  // stateValue is common with display content
  // hasComeEarlierThan is common with display content
  // hasComeLaterThan is common with display content
  // allocatables is common with display content
  // activeState is common with display content

  // Refer to Scene
  virtual void visit(RBAIsOn& exp) = 0;
  virtual void visit(RBAGetProperty& exp) = 0;

  virtual void visit(RBAIsTypeOfOperator& exp) = 0;

  // Operators
  virtual void visit(RBAAndOperator& exp) = 0;
  virtual void visit(RBAOrOperator& exp) = 0;
  virtual void visit(RBANotOperator& exp) = 0;
  virtual void visit(RBAImpliesOperator& exp) = 0;
  virtual void visit(RBAIsEqualToOperator& exp) = 0;
  virtual void visit(RBAObjectCompare& exp) = 0;
  virtual void visit(RBAIsGreaterThanOperator& exp) = 0;
  virtual void visit(RBAIsGreaterThanEqualOperator& exp) = 0;
  virtual void visit(RBAIsLowerThanOperator& exp) = 0;
  virtual void visit(RBAIsLowerThanEqualOperator& exp) = 0;

  // Quantification symbol
  virtual void visit(RBAForAllOperator& exp) = 0;
  virtual void visit(RBAExistsOperator& exp) = 0;

  // Built-in definition expression
  virtual void visit(RBAAllInstanceOfArea& exp) = 0;
  virtual void visit(RBAAllInstanceOfViewContent& exp) = 0;
  virtual void visit(RBAAllInstanceOfZone& exp) = 0;
  virtual void visit(RBAAllInstanceOfSoundContent& exp) = 0;

  // Syntax
  virtual void visit(RBAIfStatement& exp) = 0;
  virtual void visit(RBALetStatement& exp) = 0;

  // Modifier
  virtual void visit(RBAPreviousModifier& exp) = 0;

  // Set operator
  virtual void visit(RBAMaxOperator& exp) = 0;
  virtual void visit(RBAMinOperator& exp) = 0;
  virtual void visit(RBASelectOperator& exp) = 0;
  virtual void visit(RBASizeOperator& exp) = 0;

  // Object references
  virtual void visit(RBAObjectReference& exp) = 0;
  virtual void visit(RBASetOfOperator& exp) = 0;
};

}

#endif
