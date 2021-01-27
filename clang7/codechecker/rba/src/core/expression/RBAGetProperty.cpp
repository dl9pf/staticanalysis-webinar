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
 * RBAGetProperty class defintino file
 */

#include "RBAGetProperty.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBASceneImpl.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBALogManager.hpp"
#include "RBAExpressionType.hpp"
#include "RBAModelElementType.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba
{

void
RBAGetProperty::accept(RBAExpressionVisitor& visitor)
{
  // This path is not used, because RBASceneAllocatableCollector, 
  // the only existing visitor as of now, does not accept content.
  // But, keep this because another visitor may accept, in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAGetProperty::getModelElementType() const
{
  return RBAModelElementType::GetProperty;
}

std::int32_t
RBAGetProperty::getValueCore(RBAConstraintInfo* info,
				 RBAArbitratorImpl* arb) const
{
  std::int32_t value{0};
  const RBAAbstractProperty* prop{nullptr};
  const RBARuleObject* const ruleObj {getLhsOperand()->getReferenceObject(info, arb)};
  if(ruleObj->isPrevious()) {
    prop = dynamic_cast<const RBAAbstractProperty*>(ruleObj->getRawObject());
    value = arb->getResult()->getPreSceneProperty(prop);
  }
  else {
    prop = dynamic_cast<const RBAAbstractProperty*>(ruleObj);
    value = arb->getResult()->getSceneProperty(prop);
  }
  LOG_arbitrateConstraintLogicLogLine("      "
				      + getPreMsg(ruleObj->isPrevious())
				      + "Property["
				      + prop->getScene()->getElementName()
				      + "::"
				      + prop->getElementName()
				      + "] get["
				      + std::to_string(value)
				      + "]");
  return value;
}

#ifdef RBA_USE_LOG
const std::string
RBAGetProperty::getSymbol() const
{
  return ".get()";
}

const std::string
RBAGetProperty::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}

const std::string
RBAGetProperty::getCoverageExpressionText() const
{
  return getExpressionText();
}

RBAExpressionType
RBAGetProperty::getUnderlyingType() const
{
  return RBAExpressionType::VALUE;
}
#endif

}
