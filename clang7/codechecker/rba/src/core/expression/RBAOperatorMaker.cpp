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

/// @file  RBAOperatorMaker.cpp
/// @brief Operator object generator abstract class

#include "RBAOperatorMaker.hpp"
#include "RBAOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAOperatorMaker::RBAOperatorMaker(const std::string& label)
  : RBAExpressionMaker{label}
{
}

RBAModelElement*
RBAOperatorMaker::setProperty(RBAModelElement* element,
                              const RBAJsonElement* jsonElem,
                              RBAModelImpl* model,
                              RBAModelElement* owner)
{
  // Create expression
  RBAOperator* const exprOpr {dynamic_cast<RBAOperator*>(element)};

  // Set LetStatement
  const auto pop_num = setLetStatement(model, exprOpr, jsonElem);

  // Set operand
  for(auto& param : jsonElem->findChildren("operand")->getChildren()) {
    const auto expr = getFactory()->createElement(param->getClassName(), param.get());
    exprOpr->addOperand(dynamic_cast<RBAExpression*>(expr));
  }

  // Pop variable
  for(std::int32_t i{0}; i<pop_num; i++) {
    getFactory()->popVariable();
  }

  return exprOpr;
}

}
