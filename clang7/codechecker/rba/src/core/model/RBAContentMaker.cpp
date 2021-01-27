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

/// @file  RBAContentMaker.cpp
/// @brief Content obecjt generator abstract class

#include <iostream>
#include "RBAContentMaker.hpp"
#include "RBAContent.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAViewContentStateMaker.hpp"
#include "RBASoundContentStateMaker.hpp"

namespace rba
{

RBAContentMaker::RBAContentMaker(const std::string& label)
  : RBARuleObjectMaker{label},
    RBAAbstractContentMaker{label}
{
}

RBAModelElement*
RBAContentMaker::setProperty(RBAModelElement* element,
                             const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractContentMaker::setProperty(element, jsonElem, model, owner));

  RBAContent* const content {dynamic_cast<RBAContent*>(element)};

  // loserType
  const RBAJsonElement* const loserTypeElem {jsonElem->findChildren("loserType")};
  if(loserTypeElem == nullptr) {
    std::cerr << content->getElementName()
              << ": loserType not found" << &std::endl;
    return nullptr;
  }
  content->setLoserType(loserTypeElem->getLoserType());

  // allocatable
  for(auto& allocElem : jsonElem->findChildren("allocatable")->getChildren()) {
    const auto str = allocElem->getName();
    std::string allocName {""};
    std::string className {""};
    if (str.find(':') != std::string::npos) {
      allocName = str.substr(0U, str.find(':'));
      className = str.substr(str.find(':') + 1U);
    } else {
      allocName = str;
    }

    auto alloc = model->findAllocatable(allocName);
    if (alloc == nullptr) {
      alloc = dynamic_cast<RBAAllocatable*>(getMaker(className)->getInstance(model, allocName));
    }
    const_cast<RBAAllocatable*>(alloc)->addContent(content);
    content->addAllocatable(alloc);
  }

  // state
  if (content->isViewContent()) {
    RBAViewContentStateMaker csMaker;
    for(const auto& state : jsonElem->findChildren("states")->getChildren()) {
      RBAModelElement* const s {csMaker.create(state.get(), model, content)};
      content->addMember(dynamic_cast<RBARuleObject*>(s));
      content->addState(dynamic_cast<RBAContentState*>(s));
    }
  }
  else if (content->isSoundContent()) {
    RBASoundContentStateMaker csMaker;
    for(const auto& state : jsonElem->findChildren("states")->getChildren()) {
      RBAModelElement* const s {csMaker.create(state.get(), model, content)};
      content->addMember(dynamic_cast<RBARuleObject*>(s));
      content->addState(dynamic_cast<RBAContentState*>(s));
    }
  }
  // Expand Content
  else {
    auto alloc = content->getAllocatables().front();
    // Seek until it becomes an Area or Zone
    while (!alloc->isArea() && !alloc->isZone()) {
      alloc = dynamic_cast<const RBAContent*>(alloc)->getAllocatables().front();
    }
    if (alloc->isArea()) {
      RBAViewContentStateMaker csMaker;
      for(const auto& state : jsonElem->findChildren("states")->getChildren()) {
        RBAModelElement* const s {csMaker.create(state.get(), model, content)};
        content->addMember(dynamic_cast<RBARuleObject*>(s));
        content->addState(dynamic_cast<RBAContentState*>(s));
      }
    } else if (alloc->isZone()) {
      RBASoundContentStateMaker csMaker;
      for(const auto& state : jsonElem->findChildren("states")->getChildren()) {
        RBAModelElement* const s {csMaker.create(state.get(), model, content)};
        content->addMember(dynamic_cast<RBARuleObject*>(s));
        content->addState(dynamic_cast<RBAContentState*>(s));
      }
    } else {
      ;
    }
  }

  model->addContent(content);

  return content;
}

}
