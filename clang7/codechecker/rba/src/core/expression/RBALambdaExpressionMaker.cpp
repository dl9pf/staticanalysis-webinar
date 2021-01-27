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

/// @file  RBALambdaExpressionMaker.cpp
/// @brief LambdaExpression object generation class definition

#include "RBALambdaExpressionMaker.hpp"
#include "RBALambdaExpression.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBALambdaExpressionMaker::RBALambdaExpressionMaker()
  : RBAExpressionMaker{"LambdaExpression"}
{
}

std::unique_ptr<RBAModelElement>
RBALambdaExpressionMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBALambdaExpression>();
}

RBAModelElement*
RBALambdaExpressionMaker::setProperty(RBAModelElement* element,
                                      const RBAJsonElement* jsonElem,
                                      RBAModelImpl* model,
                                      RBAModelElement* owner)
{
  RBALambdaExpression* const lambdaExpr
    {dynamic_cast<RBALambdaExpression*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, lambdaExpr, jsonElem)};

  // Set variable
  const RBAJsonElement* const varElement {jsonElem->findChildren("x")};
  RBAVariable* const var
    {dynamic_cast<RBAVariable*>(getFactory()->createElement("Variable",
                                                         varElement))};
  lambdaExpr->setX(var);
  // Set bodyText
  getFactory()->pushVariable(var);
  const RBAJsonElement* const body {jsonElem->findChildren("bodyText")};
  RBAExpression* const expr
    {dynamic_cast<RBAExpression*>(getFactory()->createElement(body->getClassName(),
                                                           body))};
  lambdaExpr->setBodyText(expr);

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }
  
  return lambdaExpr;
}

}
