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

/// @file  RBAExistsOperatorMaker.cpp
/// @brief Exists Operator object maker Class definition

#include "RBAExistsOperatorMaker.hpp"
#include "RBAExistsOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBAExistsOperatorMaker::RBAExistsOperatorMaker()
  : RBALambdaContextMaker{"ExistsOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBAExistsOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAExistsOperator>();
}

RBAModelElement*
RBAExistsOperatorMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBAExistsOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBAExistsOperator>();
}

}
