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
 * ModelElment class
 */

#include "RBAModelElement.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

void RBAModelElement::clearStatus()
{
  // This function is called from a ModelElement that has no internal state 
  // to clear.
  // The overridden function is called from the ModelElement 
  // that has the internal state to clear.
}
RBAModelElementType
RBAModelElement::getModelElementType() const
{
  // This function is never called because the function of 
  // the derived class is called.
  return RBAModelElementType::None;
}

bool
RBAModelElement::isModelElementType(const RBAModelElementType elemType) const
{
  return (elemType == getModelElementType());
}

}
