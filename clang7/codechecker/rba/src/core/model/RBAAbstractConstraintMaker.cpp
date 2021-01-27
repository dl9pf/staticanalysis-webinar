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

/// @file  RBAAbstractConstraintMaker.cpp
/// @brief Abstract Constraint expresion generator class

#include "RBAAbstractConstraintMaker.hpp"
#include "RBAAbstractConstraint.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAbstractConstraintMaker::RBAAbstractConstraintMaker(const std::string& label)
  : RBAModelElementMaker{label}
{
}

RBAModelElement*
RBAAbstractConstraintMaker::setProperty(RBAModelElement* element,
                                        const RBAJsonElement* jsonElem,
                                        RBAModelImpl* model,
                                        RBAModelElement* owner)
{
  const auto abstConstraint = dynamic_cast<RBAAbstractConstraint*>(element);

  // Set expression
  const RBAJsonElement* const childElem {jsonElem->findChildren("expression")};
  RBAModelElement* const expr {getFactory()->createElement(childElem->getClassName(),
                                                  childElem)};
  abstConstraint->setExpression(dynamic_cast<RBAExpression*>(expr));

  return abstConstraint;
}

}
