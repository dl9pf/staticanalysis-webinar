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
/**
 * NamedElement clsass 
 */

#include "RBANamedElement.hpp"

namespace rba
{

RBANamedElement::RBANamedElement(const std::string& newName)
    : RBAModelElement(),
      name_(newName)
{
}

std::string
RBANamedElement::getUniqueName() const
{
  return getElementName();
}

const std::string&
RBANamedElement::getElementName() const
{
  return name_;
}

const std::string&
RBANamedElement::getDynamicName() const
{
  return dynamic_name_;
}

void
RBANamedElement::setDynamicName(const std::string& newName)
{
  dynamic_name_ = newName;
}
}
