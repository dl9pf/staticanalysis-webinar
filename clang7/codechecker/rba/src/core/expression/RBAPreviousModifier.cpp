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
 * PreviousModifier class definition
 */

#include "RBAPreviousModifier.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAPreviousObjectWrapper.hpp"

namespace rba
{

RBAPreviousModifier::RBAPreviousModifier()
    : RBAExpression(),
      previousObj_{std::make_unique<RBAPreviousObjectWrapper>()}
{
}

void
RBAPreviousModifier::accept(RBAExpressionVisitor& visitor)
{
  // RBASceneAllocatableCollector, 
  // which is the only vistor that exists at the moment, 
  // does not pass this path because it does not accept the rule object.
  // In the future, another visitor may accept, so implement this.
  visitor.visit(*this);
}

void
RBAPreviousModifier::setObjReference(RBAExpression* const newObjRef)
{
  objReference_ = newObjRef;
}

RBAExpression* const
RBAPreviousModifier::getObjReference() const
{
  return objReference_;
}

const RBARuleObject*
RBAPreviousModifier::getReferenceObjectCore(RBAConstraintInfo* info,
                                            RBAArbitratorImpl* arb) const
{
  previousObj_->setRefObject(objReference_->getReferenceObject(info, arb));
  return previousObj_.get();
}

#ifdef RBA_USE_LOG
const std::string
RBAPreviousModifier::getSymbol() const
{
  return "(pre)";
}

void
RBAPreviousModifier::createHierarchy()
{
  objReference_->createHierarchy();
}

const std::string
RBAPreviousModifier::getExpressionText() const
{
  return getSymbol() + objReference_->getExpressionText();
}

const std::string
RBAPreviousModifier::getCoverageExpressionText() const
{
  return getSymbol() + objReference_->getCoverageExpressionText();
}

RBAExpressionType
RBAPreviousModifier::getUnderlyingType() const
{
  return objReference_->getUnderlyingType();
}

#endif

}
