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
/// @file  RBAPositionContainerMaker.cpp
/// @brief PositionContainer object generation class

#include "RBAPositionContainerMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAPositionContainerImpl.hpp"
#include "RBASizeMaker.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAPositionContainerMaker::RBAPositionContainerMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"PositionContainer"}
{
}

std::unique_ptr<RBAModelElement>
RBAPositionContainerMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAPositionContainerImpl>();
}

RBAModelElement*
RBAPositionContainerMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  RBAPositionContainerImpl* const posCont
    {dynamic_cast<RBAPositionContainerImpl*>(element)};

  // Set areaReference and x,y
  std::int32_t x {-1};
  std::int32_t y {-1};
  const RBAJsonElement* const areaRef {jsonElem->findChildren("areaReference")};
  RBAAreaImpl* const area {const_cast<RBAAreaImpl*>(model->findAreaImpl(areaRef->getString()))};
  //// set area to owner
  RBADisplayImpl* const display {dynamic_cast<RBADisplayImpl*>(owner)};
  display->addArea(area);
  //// set default x,y to area
  const RBAJsonElement* const elemX {jsonElem->findChildren("x")};
  if(elemX != nullptr) {
    x = elemX->getInt();
    area->setDefaultX(x);
  }
  const RBAJsonElement* const elemY {jsonElem->findChildren("y")};
  if(elemY != nullptr) {
    y = elemY->getInt();
    area->setDefaultY(y);
  }
  posCont->setArea(area);
  posCont->setX(x);
  posCont->setY(y);

  // Set basePoint
  const std::string basePoint {jsonElem->findChildren("basePoint")->getString()};
  RBABasePoint basePointVal{RBAPositionContainer::BASE_POINT_EDEFAULT};
  if(basePoint == "LEFT_TOP") {
    basePointVal = RBABasePoint::LEFT_TOP;
  } else if(basePoint == "LEFT_MIDDLE") {
    basePointVal = RBABasePoint::LEFT_MIDDLE;
  } else if(basePoint == "LEFT_BOTTOM") {
    basePointVal = RBABasePoint::LEFT_BOTTOM;
  } else if(basePoint == "RIGHT_TOP") {
    basePointVal = RBABasePoint::RIGHT_TOP;
  } else if(basePoint == "RIGHT_MIDDLE") {
    basePointVal = RBABasePoint::RIGHT_MIDDLE;
  } else if(basePoint == "RIGHT_BOTTOM") {
    basePointVal = RBABasePoint::RIGHT_BOTTOM;
  } else if(basePoint == "CENTER_TOP") {
    basePointVal = RBABasePoint::CENTER_TOP;
  } else if(basePoint == "CENTER_MIDDLE") {
    basePointVal = RBABasePoint::CENTER_MIDDLE;
  } else if(basePoint == "CENTER_BOTTOM") {
    basePointVal = RBABasePoint::CENTER_BOTTOM;
  } else {
    ;
  }
  posCont->setBasePoint(basePointVal);

  // Set offset
  const RBAJsonElement* const offsets {jsonElem->findChildren("Offset")};
  if(offsets != nullptr) {
    for(const auto& offset : offsets->getChildren()) {
      const RBAJsonElement* const elemSizeRef {offset->findChildren("sizeReference")};
      if(elemSizeRef != nullptr) {
        std::int32_t offsetX {-1};
        const RBAJsonElement* const elemOffsetX {offset->findChildren("x")};
        if(elemOffsetX != nullptr) {
          offsetX = elemOffsetX->getInt();
        }
        std::int32_t offsetY {-1};
        const RBAJsonElement* const elemOffsetY {offset->findChildren("y")};
        if(elemOffsetY != nullptr) {
          offsetY = elemOffsetY->getInt();
        }
        posCont->addOffset(elemSizeRef->getString(), offsetX, offsetY);
      }
    }
  }

  model->addPositionContainer(posCont);

  return posCont;
}

}
