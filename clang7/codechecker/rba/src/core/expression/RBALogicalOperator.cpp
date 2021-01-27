
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
 * LogicalOperator class definition
 */

#include <sstream>
#include "RBALogicalOperator.hpp"
#include "RBAExpressionType.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
const std::string
RBALogicalOperator::getExpressionText() const
{
  std::ostringstream oss;
  oss << "(";
  const auto& exprList = getOperand();
  const auto& lastExpr = exprList.back();
  for (const auto& expr : exprList) {
    oss << expr->getExpressionText();
    if (expr != lastExpr) {
      oss << " " << getSymbol() << " ";
    }
  }
  oss << ")";

  return oss.str();
}

const std::string
RBALogicalOperator::getCoverageExpressionText() const
{
  std::ostringstream oss;
  oss << "(";
  auto exprList = getOperand();
  auto lastExpr = exprList.back();
  for (const auto& expr : exprList) {
    oss << expr->getCoverageExpressionText();
    if (expr != lastExpr) {
      oss << " " << getSymbol() << " ";
    }
  }
  oss << ")";

  return oss.str();
}

RBAExpressionType
RBALogicalOperator::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
