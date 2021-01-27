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

/// @file  RBAVariableMaker.cpp
/// @brief Variable object generator class definition

#include "RBAVariableMaker.hpp"
#include "RBAVariable.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAVariableMaker::RBAVariableMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"Variable"}
{
}

RBAModelElement*
RBAVariableMaker::create(const RBAJsonElement* jsonElem,
                         RBAModelImpl* model,
                         RBAModelElement* owner)
{
  // Register the instance without a name, because Variable has the same name
  std::unique_ptr<RBAModelElement> inst
    {createInstance(jsonElem->findChildren("name")->getString())};
  const auto element = inst.get();
  static_cast<void>(model->addModelElement(std::move(inst)));

  return setProperty(element, jsonElem, model, owner);
}

std::unique_ptr<RBAModelElement>
RBAVariableMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAVariable>(name);
}

RBAModelElement*
RBAVariableMaker::setProperty(RBAModelElement* element,
                              const RBAJsonElement* jsonElem,
                              RBAModelImpl* model,
                              RBAModelElement* owner)
{
  return element;
}

}
