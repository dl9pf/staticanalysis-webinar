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

/// @file  RBALambdaContextMaker.cpp
/// @brief LambdaContext object generation abstract class definition

#include "RBALambdaContextMaker.hpp"
#include "RBALambdaContext.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBALambdaContextMaker::RBALambdaContextMaker(const std::string& label)
  : RBAOperatorMaker{label}
{
}

RBAModelElement*
RBALambdaContextMaker::setProperty(RBAModelElement* element,
                                   const RBAJsonElement* jsonElem,
                                   RBAModelImpl* model,
                                   RBAModelElement* owner)
{
  RBALambdaContext* const lambdaContext
    {dynamic_cast<RBALambdaContext*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, lambdaContext, jsonElem)};
  // Set lambda
  const RBAJsonElement* const lambdaElement {jsonElem->findChildren("lambda")};
  RBAModelElement* const lambdaExpr
    {getFactory()->createElement(lambdaElement->getClassName(), lambdaElement)};
  lambdaContext->setLambda(dynamic_cast<RBALambdaExpression*>(lambdaExpr));
  // Set operand
  const RBAJsonElement* const param {jsonElem->findChildren("operand")->getChild()};
  RBAModelElement* const expr
    {getFactory()->createElement(param->getClassName(), param)};
  lambdaContext->addOperand(dynamic_cast<RBAExpression*>(expr));
  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return lambdaContext;
}

}
