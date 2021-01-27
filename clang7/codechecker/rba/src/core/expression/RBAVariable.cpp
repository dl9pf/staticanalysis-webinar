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
 * Variable class defintion
 */

#include "RBAVariable.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAVariable::RBAVariable(const std::string& name)
  : RBARuleObject{name}
{
}

RBAModelElementType
RBAVariable::getModelElementType() const
{
  return RBAModelElementType::Variable;
}

const RBARuleObject*
RBAVariable::getRuleObj() const
{
  return ruleObj_;
}

void
RBAVariable::setRuleObj(const RBARuleObject* const ruleObj)
{
  ruleObj_ = ruleObj;
}

void
RBAVariable::clearRuleObj()
{
  ruleObj_ = nullptr;
}

RBAConstraintInfo*
RBAVariable::createConstraintInfo()
{
  // When the "Let" expression is written in a lambda expression such as 
  // "For-All", the expansion result of the "Let" expression also changes 
  // each time the variable of "For-All" changes. Even if the Let expression 
  // is written in "For-All", there is only one valiable object.
  // Therefore, "constraintInfo" cannot be cleared and reused, and it is 
  // necessary to do "make_shared" each time the "Let" expression is evaluated.
  // The ownership of the "ConstraintInfo" of the "Let" expression is 
  // transferred to the "ConstraintInfo" of the "RBAObjectReference" 
  // when the RBAObjectReference that refers to the definition of the Let 
  // expression is evaluated.
  constraintInfo_ = std::make_shared<RBAConstraintInfo>();
  return constraintInfo_.get();
}

std::shared_ptr<RBAConstraintInfo>
RBAVariable::getConstraintInfo() const
{
  return constraintInfo_;
}

}
