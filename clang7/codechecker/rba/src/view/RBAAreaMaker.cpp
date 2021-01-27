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
/// @file  RBAAreaMaker.cpp
/// @brief Area object generation class

#include <iostream>
#include "RBAAreaMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBASizeMaker.hpp"

namespace rba
{

RBAAreaMaker::RBAAreaMaker()
  : RBARuleObjectMaker{"areas"},
    RBAAllocatableMaker()
{
}

std::unique_ptr<RBAModelElement>
RBAAreaMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAreaImpl>(name);
}

RBAModelElement*
RBAAreaMaker::setProperty(RBAModelElement* element,
                          const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner)
{
  element = RBAAllocatableMaker::setProperty(element, jsonElem, model, owner);
  if (element == nullptr) {
    return nullptr;
  }

  RBAAreaImpl* const area {dynamic_cast<RBAAreaImpl*>(element)};

  // Set default X and Y
  std::int32_t x{-1};
  std::int32_t y{-1};
  const RBAJsonElement* const elemX {jsonElem->findChildren("x")};
  const RBAJsonElement* const elemY {jsonElem->findChildren("y")};
  if(elemX != nullptr) {
    x = elemX->getInt();
  }
  if(elemY != nullptr) {
    y = elemY->getInt();
  }
  area->setDefaultX(x);
  area->setDefaultY(y);

  // Set zorder
  const RBAJsonElement* const zorder {jsonElem->findChildren("zorder")};
  if(zorder == nullptr) {
    std::cerr << area->getElementName()
              << ": zorder not found" << &std::endl;
    return nullptr;
  }
  area->setZorder(zorder->getInt());

  // Size
  RBASizeMaker szMaker;
  szMaker.setFactory(getFactory());
  for(const auto& size : jsonElem->findChildren("size")->getChildren()) {
    const auto sizeInst = szMaker.create(size.get(), model, area);
    area->addSize(dynamic_cast<RBASizeImpl*>(sizeInst));
  }

  return area;
}

}
