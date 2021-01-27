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
 * RBALambdaExpression class defnition
 */

#include "RBALambdaExpression.hpp"
#include "RBAVariable.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void
RBALambdaExpression::setX(RBAVariable* const x)
{
  variable_ = x;
}

void
RBALambdaExpression::setBodyText(RBAExpression* const expr)
{
  bodyText_ = expr;
}

RBAVariable* const
RBALambdaExpression::getX() const
{
  return variable_;
}

RBAExpression* const
RBALambdaExpression::getBodyText() const
{
  return bodyText_;
}

RBAModelElementType
RBALambdaExpression::getModelElementType() const
{
  return RBAModelElementType::LambdaExpression;
}

bool
RBALambdaExpression::executeCore(RBAConstraintInfo* info, RBAArbitratorImpl * arb) const
{
  getX()->setRuleObj(ruleObj_);

  RBAConstraintInfo* const childInfo {info->getChild(0U)};
  bool res {getBodyText()->execute(childInfo,arb)};
  if(childInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
    res = false;
  }

  return res;
}

const RBARuleObject*
RBALambdaExpression::getReferenceObjectCore(RBAConstraintInfo* info,
                                            RBAArbitratorImpl* arb) const
{
  getX()->setRuleObj(ruleObj_);

  RBAConstraintInfo* const childInfo {info->getChild(0U)};
  const RBARuleObject* const res {getBodyText()->getReferenceObject(childInfo, arb)};
  if (childInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  }

  return res;
}
std::int32_t
RBALambdaExpression::getValueCore(RBAConstraintInfo* info,
                                  RBAArbitratorImpl* arb) const
{
  getX()->setRuleObj(ruleObj_);

  RBAConstraintInfo* const childInfo {info->getChild(0U)};
  const std::int32_t res {getBodyText()->getValue(childInfo, arb)};
  if (childInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  }

  return res;
}
#ifdef RBA_USE_LOG
void
RBALambdaExpression::createHierarchy()
{
  bodyText_->createHierarchy();
}

const std::string
RBALambdaExpression::getExpressionText() const
{
  return "{ " + getX()->getElementName() + " |"
    + bodyText_->getExpressionText() + "}";
}

const std::string
RBALambdaExpression::getCoverageExpressionText() const
{
  return "{ " + getX()->getElementName() + " |" +
    bodyText_->getCoverageExpressionText() + "}";
}
#endif

void
RBALambdaExpression::setRuleObj(const RBARuleObject* const ruleObj)
{
  ruleObj_ = ruleObj;
  getX()->setRuleObj(ruleObj);
}

void
RBALambdaExpression::clearRuleObj()
{
  ruleObj_ = nullptr;
  getX()->clearRuleObj();
}

}
