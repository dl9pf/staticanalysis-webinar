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

/// @file  RBAConstraintMaker.cpp
/// @brief Constraint object genartor class implementation

#include "RBAConstraintMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAConstraintMaker::RBAConstraintMaker()
  : RBAAbstractConstraintMaker{"constraints"}
{
}

std::unique_ptr<RBAModelElement>
RBAConstraintMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAConstraintImpl>(name);
}

RBAModelElement*
RBAConstraintMaker::setProperty(RBAModelElement* element,
                                const RBAJsonElement* jsonElem,
                                RBAModelImpl* model,
                                RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractConstraintMaker::setProperty(element, jsonElem, model, owner));

  const auto constraint = dynamic_cast<RBAConstraintImpl*>(element);

  // Set runtime
  bool runtime {false};
  if(jsonElem->findChildren("runtime")->getString() == "true") {
    runtime = true;
  }
  constraint->setRuntime(runtime);

  model->addConstraint(constraint);

  return constraint;
}

}
