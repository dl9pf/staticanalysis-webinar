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
/// @file  RBAViewContentMaker.cpp
/// @brief ViewContent object generation class

#include "RBAViewContentMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBASizeMaker.hpp"
#include "RBAViewContentStateMaker.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAViewContentMaker::RBAViewContentMaker()
  : RBARuleObjectMaker{"viewcontents"},
    RBAContentMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAViewContentMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAViewContentImpl>(name);
}

RBAModelElement*
RBAViewContentMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  element = RBAContentMaker::setProperty(element, jsonElem, model, owner);
  if(element == nullptr) {
    return nullptr;
  }

  RBAViewContentImpl* const content {dynamic_cast<RBAViewContentImpl*>(element)};

  // size
  RBASizeMaker szMaker;
  szMaker.setFactory(getFactory());
  for(auto& size : jsonElem->findChildren("size")->getChildren()) {
    const auto sizeInst = szMaker.create(size.get(), model, content);
    content->addSize(dynamic_cast<RBASizeImpl*>(sizeInst));
  }

  return content;
}

}
