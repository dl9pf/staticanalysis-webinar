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
/// @file  RBASoundContentStateMaker.cpp
/// @brief SoundContentState object generator class

#include "RBASoundContentStateMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBASoundContentStateImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBASoundContentStateMaker::RBASoundContentStateMaker()
  : RBAContentStateMaker{"SoundContentState"}
{
}

std::unique_ptr<RBAModelElement>
RBASoundContentStateMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASoundContentStateImpl>(name);
}

RBAModelElement*
RBASoundContentStateMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  // create instance of unique_ptr and register it to model
  // name, priority and owner are also registered.
  RBAModelElement* const elem {RBAContentStateMaker::setProperty(element, 
                                                       jsonElem, model, owner)};
  if(elem == nullptr) {
    return nullptr;
  }
  RBASoundContentStateImpl* const state
    {dynamic_cast<RBASoundContentStateImpl*>(elem)};

  return state;
}

}
