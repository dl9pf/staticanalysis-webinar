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
 * If statement class defintion file
 */

#include <sstream>
#include "RBAIfStatement.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAIfStatement::setCondition(RBAExpression* const expr)
{
  condition_ = expr;
}

void
RBAIfStatement::setThenExpression(RBAExpression* const expr)
{
  thenExpression_ = expr;
}

void
RBAIfStatement::setElseExpression(RBAExpression* const expr)
{
  elseExpression_ = expr;
}

RBAExpression* const
RBAIfStatement::getCondition() const
{
  return condition_;
}

RBAExpression* const
RBAIfStatement::getThenExpression() const
{
  return thenExpression_;
}

RBAExpression* const
RBAIfStatement::getElseExpression() const
{
  return elseExpression_;
}

void
RBAIfStatement::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAIfStatement::getModelElementType() const
{
  return RBAModelElementType::IfStatement;
}

bool
RBAIfStatement::executeCore(RBAConstraintInfo* info,
                            RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy("IF");
  bool isPassed;
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  LOG_addHierarchy("#condition:");
  const bool cond {getCondition()->execute(leftInfo, arb)};
  LOG_removeHierarchy();
  if (cond == true) {
    LOG_addHierarchy("#then:");
    isPassed = getThenExpression()->execute(rightInfo, arb);
    LOG_removeHierarchy();
  } else {
    LOG_addHierarchy("#else:");
    isPassed = getElseExpression()->execute(rightInfo, arb);
    LOG_removeHierarchy();
  }
  if ((leftInfo->isExceptionBeforeArbitrate() == true)
      || (rightInfo->isExceptionBeforeArbitrate() == true)) {
    info->setExceptionBeforeArbitrate(true);
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::SKIP);
#ifdef RBA_USE_LOG
  } else if (isPassed == true) {
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::TRUE);
  } else {
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
                                        RBAExecuteResult::FALSE);
#endif
  }
  LOG_removeHierarchy();
  return isPassed;
}

const RBARuleObject*
RBAIfStatement::getReferenceObjectCore(RBAConstraintInfo* info,
                                       RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy("IF");
  const RBARuleObject* object {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  LOG_addHierarchy("#condition:");
  const bool cond {getCondition()->execute(leftInfo, arb)};
  LOG_removeHierarchy();
  if (cond == true) {
    LOG_addHierarchy("#then:");
    object = getThenExpression()->getReferenceObject(rightInfo, arb);
    LOG_removeHierarchy();
  } else {
    LOG_addHierarchy("#else:");
    object = getElseExpression()->getReferenceObject(rightInfo, arb);
    LOG_removeHierarchy();
    if ((leftInfo->isExceptionBeforeArbitrate() == true)
        || (rightInfo->isExceptionBeforeArbitrate() == true)) {
      info->setExceptionBeforeArbitrate(true);
    }
  }
  LOG_removeHierarchy();
  return object;
}

std::int32_t
RBAIfStatement::getValueCore(RBAConstraintInfo* info,
                             RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy("IF");
  std::int32_t value;
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  LOG_addHierarchy("#condition:");
  const bool cond {getCondition()->execute(leftInfo, arb)};
  LOG_removeHierarchy();
  if (cond == true) {
    LOG_addHierarchy("#then:");
    value = getThenExpression()->getValue(rightInfo, arb);
    LOG_removeHierarchy();
  } else {
    LOG_addHierarchy("#else:");
    value = getElseExpression()->getValue(rightInfo, arb);
    LOG_removeHierarchy();
    if ((leftInfo->isExceptionBeforeArbitrate() == true)
        || (rightInfo->isExceptionBeforeArbitrate() == true)) {
      info->setExceptionBeforeArbitrate(true);
    }
  }
  LOG_removeHierarchy();
  return value;
}

void
RBAIfStatement::doActionCore(RBAConstraintInfo* info,
                             RBAArbitratorImpl* arb)
{
  LOG_addHierarchy("IF");
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  LOG_addHierarchy("#condition:");
  const bool cond {getCondition()->execute(leftInfo, arb)};
  LOG_removeHierarchy();
  if (cond == true) {
    LOG_addHierarchy("#then:");
    getThenExpression()->doAction(rightInfo, arb);
    LOG_removeHierarchy();
  } else {
    LOG_addHierarchy("#else:");
    getElseExpression()->doAction(rightInfo, arb);
    LOG_removeHierarchy();
  }
#ifdef RBA_USE_LOG
  LOG_coverageConstraintExpressionLog2(LOG_getCoverageExpressionText());
#endif
  LOG_removeHierarchy();
  return;
}

#ifdef RBA_USE_LOG
const std::string
RBAIfStatement::getExpressionText() const
{
  std::ostringstream oss;
  oss << "IF(";
  oss << condition_->getExpressionText();
  oss << ") THEN ";
  oss << thenExpression_->getExpressionText();
  oss << " ELSE ";
  oss << elseExpression_->getExpressionText();

  return oss.str();
}

const std::string
RBAIfStatement::getCoverageExpressionText() const
{
  std::ostringstream oss;
  oss << "IF(";
  oss << condition_->getCoverageExpressionText();
  oss << ") THEN ";
  oss << thenExpression_->getCoverageExpressionText();
  oss << " ELSE ";
  oss << elseExpression_->getCoverageExpressionText();

  return oss.str();
}

void
RBAIfStatement::createHierarchy()
{
  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy("IF");
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(),
						 this);

  // Add condition to the constraint hierarchy for coverage
  LOG_addHierarchy("#condition:");
  condition_->createHierarchy();
  // Remove condtion from to the constraint hierarchy for coverage
  LOG_removeHierarchy();

  if(thenExpression_) {
    // Add "then" to the constraint hierarchy for coverage
    LOG_addHierarchy("#then:");
    thenExpression_->createHierarchy();
    // Remove "then" from the constraint hierarchy for coverage
    LOG_removeHierarchy();
  }

  if(elseExpression_) {
    // Add "else" to the constraint hierarchy for coverage
    LOG_addHierarchy("#else:");
    elseExpression_->createHierarchy();
    // Remove "else" from the constraint hierarchy for coverage
    LOG_removeHierarchy();
  }

  // Remove itself from the constraint hierarchy for coverage
  LOG_removeHierarchy();
}

RBAExpressionType
RBAIfStatement::getUnderlyingType() const
{
  return thenExpression_->getUnderlyingType();
}
#endif
}
