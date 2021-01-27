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

/// @file  RBAIfStatementMaker.cpp
/// @brief IfStatement object generation class definition file

#include "RBAIfStatementMaker.hpp"
#include "RBAIfStatement.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAIfStatementMaker::RBAIfStatementMaker()
  : RBAExpressionMaker{"IfStatement"}
{
}

std::unique_ptr<RBAModelElement>
RBAIfStatementMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAIfStatement>();
}

RBAModelElement*
RBAIfStatementMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  RBAIfStatement* const ifstmt {dynamic_cast<RBAIfStatement*>(element)};

  // Set LetStatement
  const std::int32_t pop_num {setLetStatement(model, ifstmt, jsonElem)};

  // Set condition
  const RBAJsonElement* const condElem {jsonElem->findChildren("condition")};
  RBAModelElement* const condExpr
    {getFactory()->createElement(condElem->getClassName(), condElem)};
  ifstmt->setCondition(dynamic_cast<RBAExpression*>(condExpr));
  // Set "then"
  const RBAJsonElement* const thenElem {jsonElem->findChildren("thenExpression")};
  RBAModelElement* thenExpr {nullptr};
  if(thenElem != nullptr) {
    thenExpr = getFactory()->createElement(thenElem->getClassName(), thenElem);
  }
  ifstmt->setThenExpression(dynamic_cast<RBAExpression*>(thenExpr));
  // Set "else"
  const RBAJsonElement* const elseElem {jsonElem->findChildren("elseExpression")};
  RBAModelElement* elseExpr {nullptr};
  if(elseElem != nullptr) {
    elseExpr = getFactory()->createElement(elseElem->getClassName(), elseElem);
  }
  ifstmt->setElseExpression(dynamic_cast<RBAExpression*>(elseExpr));

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return ifstmt;
}

}
