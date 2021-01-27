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

/// @file  RBAAbstractContentMaker.cpp
/// @brief Abstract Content generator class implementation

#include "RBAAbstractContentMaker.hpp"
#include "RBAAbstractContent.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAbstractContentMaker::RBAAbstractContentMaker(const std::string& label)
  : RBARuleObjectMaker{label}
{
}

RBAModelElement*
RBAAbstractContentMaker::setProperty(RBAModelElement* element,
                                     const RBAJsonElement* jsonElem,
                                     RBAModelImpl* model,
                                     RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty( element, jsonElem, 
  	                                                 model, owner));
  
  const auto abstContent = dynamic_cast<RBAAbstractContent*>(element);

  // Currently, there is no member set by RBAAbstractContentMaker
  // as model information, but this process is implemented 
  // because it may be added in the future.

  return abstContent;
}

}
