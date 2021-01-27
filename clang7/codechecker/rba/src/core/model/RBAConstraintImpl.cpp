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
 * Constraint Implementation class
 */

#include "RBAConstraintImpl.hpp"

#include "RBAExpression.hpp"
#include "RBALogManager.hpp"

namespace rba
{

RBAConstraintImpl::RBAConstraintImpl(const std::string& name)
  : RBAConstraint(),
    RBAAbstractConstraint{name}
{
}

void
RBAConstraintImpl::setRuntime(const bool newRuntime)
{
  runtime_ = newRuntime;
}

std::string
RBAConstraintImpl::getName() const
{
  return RBANamedElement::getElementName();
}

bool
RBAConstraintImpl::isConstraint() const
{
  return true;
}

bool
RBAConstraintImpl::isRuntime() const
{
  return runtime_;
}

bool
RBAConstraintImpl::execute(RBAArbitratorImpl* const arb)
{
  LOG_arbitrateConstraintLogicLogLine("    constraint expression["
						 + getExpression()->LOG_getExpressionText()
						 + "] check start");
  LOG_initConstraintHierarchy();
  LOG_coverageConstraintStartLog(this);

  clearInfo();

  bool res {getExpression()->execute(getInfo(), arb)};
#ifdef RBA_USE_LOG
  std::string log = "    constraint expression[" + getExpression()->getExpressionText();

  if (res == true) {
    log += "] true";
  } else {
#endif
    if (getInfo()->isExceptionBeforeArbitrate() == true) {
#ifdef RBA_USE_LOG
      log += "] before arbitrate skip";
#endif
      res = true;
#ifdef RBA_USE_LOG
    } else {
      log += "] false";
    }
#endif
  }
  LOG_arbitrateConstraintLogicLogLine(log + "\n");

  LOG_coverageConstraintEndLog(this);

  return res;
}

}
