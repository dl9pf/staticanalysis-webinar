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

/*
 * LetStatement class definition
 */

#include "RBALetStatement.hpp"
#include "RBALogManager.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAModelElementType.hpp"
#include "RBAVariable.hpp"
#include "RBAExpressionVisitor.hpp"

namespace rba
{

RBAModelElementType RBALetStatement::getModelElementType() const
{
  return RBAModelElementType::LetStatement;
}

void RBALetStatement::setVariable(RBAVariable* const var)
{
  variable_ = var;
}

void
RBALetStatement::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

void RBALetStatement::setVariable(RBAArbitratorImpl* const arb)
{
  RBAConstraintInfo* const info {variable_->createConstraintInfo()};
  variable_->setRuleObj(getLhsOperand()->getReferenceObject(info, arb));
#ifdef RBA_USE_LOG
  std::string valueName;
  if (info->isExceptionBeforeArbitrate() == true) {
    valueName = "before arbitrate skip";
  } else if (variable_->getRuleObj() == nullptr) {
    valueName = "NULL";
  } else {
    valueName = variable_->getRuleObj()->getElementName();
    if (valueName == "") {
      valueName = variable_->getRuleObj()->getDynamicName();
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      let " + variable_->getElementName() + " = "
          + getLhsOperand()->getExpressionText() + " = " + valueName);
#endif
}
} /* namespace rba */
