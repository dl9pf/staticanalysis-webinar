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
/// @file  RBAContentStateMaker.cpp
/// @brief ContentState object generator abstract class

#include "RBAContentStateMaker.hpp"
#include "RBAContentState.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBAContentStateMaker::RBAContentStateMaker(const std::string& label)
  : RBARuleObjectMaker{label}
{
}

RBAModelElement*
RBAContentStateMaker::getInstance(RBAModelImpl* model,
                                  const std::string& name,
                                  RBAModelElement* owner)
{
  RBAModelElement* ret {nullptr};

  const auto content = dynamic_cast<RBAContent*>(owner);
  const auto uniqueName = content->getUniqueName() + "/" + name;

  const auto element = model->findModelElement(uniqueName);
  // exists in model
  if(element != nullptr) {
    ret = const_cast<RBAModelElement*>(element);
  }
  // not exists in modelmodel
  else {
    std::unique_ptr<RBAModelElement> inst {createInstance(name)};
    const auto contentState = dynamic_cast<RBAContentState*>(inst.get());
    contentState->setOwner(content);
    ret =  model->addNamedElement(std::move(inst));
  }

  return ret;
}

RBAModelElement*
RBAContentStateMaker::setProperty(RBAModelElement* element,
                                  const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty(element, jsonElem, model, owner));

  RBAContentState* const state {dynamic_cast<RBAContentState*>(element)};

  // Set priority
  state->setPriority(jsonElem->findChildren("priority")->getInt());

  model->addContentState(state);

  return state;
}

}
