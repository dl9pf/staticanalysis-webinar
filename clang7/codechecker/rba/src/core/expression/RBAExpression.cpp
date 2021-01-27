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
 * Expression class definition
 */

#include "RBAExpression.hpp"

#include "RBALetStatement.hpp"
#include "RBAConstraintInfo.hpp"
#ifdef RBA_USE_LOG
#include "RBAExpressionType.hpp"
#endif

namespace rba
{

void RBAExpression::addLetStatement(RBALetStatement* const letStatement)
{
  letStatements_.push_back(letStatement);
}

void
RBAExpression::accept(RBAExpressionVisitor& visitor)
{
  // Not be called because the function of the derived class is called
}

bool
RBAExpression::execute(RBAConstraintInfo* const info, RBAArbitratorImpl * const arb) const
{
  info->setExpression(this);
  for (RBALetStatement* const& letStatement : letStatements_) {
    letStatement->setVariable(arb);
  }
  const bool result {executeCore(info, arb)};
  if (result) {
    info->setResult(RBAExecuteResult::TRUE);
  } else {
    info->setResult(RBAExecuteResult::FALSE);
  }
  return result;
}

bool
RBAExpression::executeCore(RBAConstraintInfo* info, RBAArbitratorImpl * arb) const
{
  // This function is called when an Expression that does not define 
  // getReferenceObject() in evaluate() is specified. 
  info->setExceptionBeforeArbitrate(true);
  return false;
}

const RBARuleObject*
RBAExpression::getReferenceObject(RBAConstraintInfo* const info,
                                      RBAArbitratorImpl* const arb) const
{
  info->setExpression(this);
  for (RBALetStatement* const& letStatement : letStatements_) {
    letStatement->setVariable(arb);
  }
  return getReferenceObjectCore(info, arb);
}

const RBARuleObject*
RBAExpression::getReferenceObjectCore(RBAConstraintInfo* info,
                                      RBAArbitratorImpl* arb) const
{
  // This function is called when an Expression that does not define 
  // getReferenceObject() in evaluateObject() is specified. 
  return nullptr;
}

std::int32_t
RBAExpression::getValue(RBAConstraintInfo* const info, RBAArbitratorImpl * const arb) const
{
  info->setExpression(this);
  for (RBALetStatement* const& letStatement : letStatements_) {
    letStatement->setVariable(arb);
  }
  return getValueCore(info, arb);
}

const std::vector<RBALetStatement*>&
RBAExpression::getLetStatements() const
{
  return letStatements_;
}
std::int32_t
RBAExpression::getValueCore(RBAConstraintInfo* info, RBAArbitratorImpl * arb) const
{
  // This function is called when an Expression that does not define 
  // getValue() in evaluateValue() is specified. 
  return -99;
}

void
RBAExpression::doAction(RBAConstraintInfo* const info, RBAArbitratorImpl* const arb)
{
  info->setExpression(this);
  doActionCore(info, arb);
  return;
}

void
RBAExpression::doActionCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb)
{
  // This function is called when an Expression that does not define 
  // doAction() in evaluateDoAction() is specified. 
  return;
}

#ifdef RBA_USE_LOG
const std::string
RBAExpression::getExpressionText() const
{
  // Not called because the function of the derived class is called
  return "Unsupported operation exception";
}

const std::string
RBAExpression::getCoverageExpressionText() const
{
  // Not called because the function of the derived class is called
  return "Unsupported operation exception";
}

void
RBAExpression::createHierarchy()
{
  // Not called because the function of the derived class is called
}

RBAExpressionType
RBAExpression::getUnderlyingType() const
{
  // Not called because the function of the derived class is called
  return RBAExpressionType::EXCEPTION;
}
#endif

}
