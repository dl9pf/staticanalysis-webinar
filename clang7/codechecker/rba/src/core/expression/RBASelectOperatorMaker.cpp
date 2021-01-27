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

/// @file  RBASelectOperatorMaker.cpp
/// @brief SelectOperator object generator class definition

#include "RBASelectOperatorMaker.hpp"
#include "RBASelectOperator.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBALambdaExpression.hpp"

namespace rba
{

RBASelectOperatorMaker::RBASelectOperatorMaker()
  : RBALambdaContextMaker{"SelectOperator"}
{
}

std::unique_ptr<RBAModelElement>
RBASelectOperatorMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASelectOperator>();
}

RBAModelElement*
RBASelectOperatorMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(
      RBALambdaContextMaker::setProperty(element, jsonElem, model, owner));

  return element;
}

std::unique_ptr<RBALambdaContext>
RBASelectOperatorMaker::createLambdaContext()
{
  return std::make_unique<RBASelectOperator>();
}

}
