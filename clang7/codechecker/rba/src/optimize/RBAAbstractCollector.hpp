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
 * Abstract search class header file
 */

#ifndef RBAABSTRACTCOLLECTOR_HPP
#define RBAABSTRACTCOLLECTOR_HPP

#include <set>

#include "RBAExpressionVisitor.hpp"
#include "RBAExpression.hpp"

namespace rba
{
class RBAModelImpl;
class RBARuleObject;

class RBAAbstractCollector : public RBAExpressionVisitor
{
 public:
  RBAAbstractCollector(RBAModelImpl* const model);
  RBAAbstractCollector(const RBAAbstractCollector&)=default;
  RBAAbstractCollector(RBAAbstractCollector&&)=default;
  RBAAbstractCollector& operator=(const RBAAbstractCollector&)=default;
  RBAAbstractCollector& operator=(RBAAbstractCollector&&)=default;
  virtual ~RBAAbstractCollector()=default;

  // area status
  void visit(RBAIsDisplayed& exp) override;
  void visit(RBADisplayingContent& exp) override;
  void visit(RBAAllocatedContent& exp) override;
  void visit(RBAIsHidden& exp) override;
  void visit(RBAContentValue& exp) override;
  void visit(RBAGetContentsList& exp) override;
  void visit(RBAActiveContents& exp) override;

  // display content status
  void visit(RBAIsActive& exp) override;
  void visit(RBAIsVisible& exp) override;
  void visit(RBAStateValue& exp) override;
  void visit(RBAHasBeenDisplayed& exp) override;
  void visit(RBAHasComeEarlierThan& exp) override;
  void visit(RBAHasComeLaterThan& exp) override;
  void visit(RBAGetAllocatables& exp) override;
  void visit(RBAActiveState& exp) override;

  // zone status
  void visit(RBAIsOutputted& exp) override;
  void visit(RBAOutputtingSound& exp) override;
  // allocatedContent is common with area
  void visit(RBAIsMuted& exp) override;
  void visit(RBAIsAttenuated& exp) override;
  // contentValue is common with area
  // contentsList is common with area

  // sound content status
  // isActive is common with display content
  void visit(RBAIsSounding& exp) override;
  // stateValue is common with display content
  // hasComeEarlierThan is common with display content
  // hasComeLaterThan is common with display content
  // allocatables is common with display content
  // activeState is common with display content

  // scene
  void visit(RBAIsOn& exp) override;
  void visit(RBAGetProperty& exp) override;

  void visit(RBAIsTypeOfOperator& exp) override;

  // operator
  void visit(RBAAndOperator& exp) override;
  void visit(RBAOrOperator& exp) override;
  void visit(RBANotOperator& exp) override;
  void visit(RBAImpliesOperator& exp) override;
  void visit(RBAIsEqualToOperator& exp) override;
  void visit(RBAObjectCompare& exp) override;
  void visit(RBAIsGreaterThanOperator& exp) override;
  void visit(RBAIsGreaterThanEqualOperator& exp) override;
  void visit(RBAIsLowerThanOperator& exp) override;
  void visit(RBAIsLowerThanEqualOperator& exp) override;

  // Quantification symbol
  void visit(RBAForAllOperator& exp) override;
  void visit(RBAExistsOperator& exp) override;

  // Built-in definition expression
  void visit(RBAAllInstanceOfArea& exp) override;
  void visit(RBAAllInstanceOfViewContent& exp) override;
  void visit(RBAAllInstanceOfZone& exp) override;
  void visit(RBAAllInstanceOfSoundContent& exp) override;

  // statement
  void visit(RBAIfStatement& exp) override;
  void visit(RBALetStatement& exp) override;

  // modifier
  void visit(RBAPreviousModifier& exp) override;

  // operator
  void visit(RBAMaxOperator& exp) override;
  void visit(RBAMinOperator& exp) override;
  void visit(RBASelectOperator& exp) override;
  void visit(RBASizeOperator& exp) override;

  // object reference
  void visit(RBAObjectReference& exp) override;
  void visit(RBASetOfOperator& exp) override;

 protected:
  void visitLetStatement(RBAExpression& exp) ;

  // getter, setter
  std::set<const RBARuleObject*>& getLetVal();
  void addLetVal(const RBARuleObject* const obj);
  bool isVisitsLetStatement() const;
  bool isLhs() const;
  void setLhs(const bool lhs);
  bool isPositive() const;
  RBAModelImpl* getModel() const;
  bool isPreviousModifier() const;

 private:
  // Object that can be taken as the evaluation result of letStatement
  std::set<const RBARuleObject*> letVal_;
  // Model referenced in getReferenceObject()
  RBAModelImpl* model_;
  // True when searching the left side
  // Otherwise, false
  bool isLhs_;
  // true when in Expression under (pre)
  // Otherwise, false
  bool isPreviousModifier_;
  // True if not inverted with Not
  // False if inverted with Not
  bool isPositive_;
  // true when searching through letStatement
  // Otherwise, false
  bool visitsLetStatement_;
};

} /* namespace rba */

#endif /* RBAABSTRACTCOLLECTOR_HPP */
