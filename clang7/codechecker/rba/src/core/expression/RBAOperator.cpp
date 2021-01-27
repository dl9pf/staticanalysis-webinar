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
 * Operator class definition
 */

#include "RBAOperator.hpp"
#include "RBALogManager.hpp"

namespace rba
{

const std::vector<RBAExpression*>&
RBAOperator::getOperand() const
{
  return operand_;
}

void
RBAOperator::addOperand(RBAExpression* const newExpr)
{
  if(newExpr != nullptr) {
    operand_.push_back(newExpr);
  }
}

RBAExpression*
RBAOperator::getLhsOperand() const
{
  return operand_.front();
}

RBAExpression*
RBAOperator::getRhsOperand() const
{
  return operand_.back();
}

const std::string
RBAOperator::getPreMsg(const bool isPrevious) const
{
  if(isPrevious) {
    return "(pre)";
  }
  else {
    return "";
  }
}

#ifdef RBA_USE_LOG
const std::string
RBAOperator::getSymbol() const
{
  return "";
}

void
RBAOperator::createHierarchy()
{
  // Add itself to Constraint hierarchy for coverage
  LOG_addHierarchy(getSymbol());
  RBALogManager::coverageHierarchyOfConstraintExpressionLog(getCoverageExpressionText(), this);

  std::uint32_t oprSize{ static_cast<std::uint32_t>(getOperand().size()) };
  if(oprSize == 1U) {
    RBAExpression* expr = getLhsOperand();
      expr->createHierarchy();
  }
  else {
    std::uint32_t num{ 0U };
    for(RBAExpression* expr : getOperand()) {
      // Add count to Constraint hierarchy for coverage
      LOG_addHierarchy("#" + std::to_string(num++));
      expr->createHierarchy();
      // Remove count from Constraint hierarchy for coverage
      LOG_removeHierarchy();
    }
  }

  // Remove count from Constraint hierarchy for coverage
  LOG_removeHierarchy();
}
#endif

}
