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

/// @file  RBALetStatementMaker.cpp
/// @brief LetStatement object generation class defintino.

#include "RBALetStatementMaker.hpp"
#include "RBALetStatement.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBALetStatementMaker::RBALetStatementMaker()
  : RBAExpressionMaker{"LetStatement"}
{
}

std::unique_ptr<RBAModelElement>
RBALetStatementMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBALetStatement>();
}

RBAModelElement*
RBALetStatementMaker::setProperty(RBAModelElement* element,
                                  const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner)
{
  RBALetStatement* const letStmt {dynamic_cast<RBALetStatement*>(element)};

  // Set variable
  const RBAJsonElement* const varElement {jsonElem->findChildren("variable")};
  RBAVariable* const var
    {dynamic_cast<RBAVariable*>(getFactory()->createElement("Variable",
                                                         varElement))};
  letStmt->setVariable(var); // Set Body
  
  // popVariable() is executed by the caller of this function
  getFactory()->pushVariable(var); 
  const RBAJsonElement* const body {jsonElem->findChildren("body")};
  RBAExpression* const expr
    {dynamic_cast<RBAExpression*>(getFactory()->createElement(body->getClassName(),
                                                           body))};
  letStmt->addOperand(expr);

  return letStmt;
}

}
