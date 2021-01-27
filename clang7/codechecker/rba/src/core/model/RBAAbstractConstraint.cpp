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
 * AbstractConstraint class implementation
 */

#include "RBAAbstractConstraint.hpp"

#include "RBAExpression.hpp"
#include "RBALogManager.hpp"

namespace rba
{

RBAAbstractConstraint::RBAAbstractConstraint(const std::string& name)
  : RBANamedElement{name}
{
}

bool
RBAAbstractConstraint::isConstraint() const
{
  return false;
}

bool
RBAAbstractConstraint::isRule() const
{
  return false;
}

void
RBAAbstractConstraint::clearInfo()
{
  info_->clear();
}

void
RBAAbstractConstraint::setExpression(RBAExpression* newExpr)
{
  expression_ = newExpr;
}

RBAExpression* const
RBAAbstractConstraint::getExpression() const
{
  return expression_;
}

RBAConstraintInfo*
RBAAbstractConstraint::getInfo() const
{
  return info_.get();
}

#ifdef RBA_USE_LOG
void
RBAAbstractConstraint::createHierarchy()
{
  LOG_initConstraintHierarchy();
  LOG_coverageHierarchyOfConstraintStartLog(this);
  getExpression()->createHierarchy();
  LOG_coverageHierarchyOfConstraintEndLog(this);
}
#endif

}
