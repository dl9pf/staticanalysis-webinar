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
/// @file  RBADisplayMaker.cpp
/// @brief Display object generation class

#include "RBADisplayMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBADisplayImpl.hpp"
#include "RBASizeMaker.hpp"
#include "RBAPositionContainerMaker.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBADisplayMaker::RBADisplayMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"displays"}
{
}

std::unique_ptr<RBAModelElement>
RBADisplayMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBADisplayImpl>(name);
}

RBAModelElement*
RBADisplayMaker::setProperty(RBAModelElement* element,
                             const RBAJsonElement* jsonElem,
                             RBAModelImpl* model,
                             RBAModelElement* owner)
{
  RBADisplayImpl* const display {dynamic_cast<RBADisplayImpl*>(element)};

  // Set size
  RBASizeMaker sizeMaker;
  sizeMaker.setFactory(getFactory());
  const RBAModelElement* const size {sizeMaker.create(jsonElem->findChildren("size"), model,
                                           display)};
  display->setSize(dynamic_cast<const RBASizeImpl*>(size));

  // Set position container
  const RBAJsonElement* const jsonPosConts {jsonElem->findChildren("PositionContainer")};
  if(jsonPosConts != nullptr) {
    RBAPositionContainerMaker pcMaker;
    pcMaker.setFactory(getFactory());
    for(const auto& jsonPosCont : jsonPosConts->getChildren()) {
      static_cast<void>(pcMaker.create(jsonPosCont.get(), model, display));
    }
  }

  model->addDisplay(display);

  return display;
}

}
