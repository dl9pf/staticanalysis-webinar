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

/// @file  RBAAllInstanceOfAreaMaker.cpp
/// @brief AllInstanceOfArea object generation class definition file

#include <iostream>
#include "RBAAllInstanceOfAreaMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAllInstanceOfArea.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllInstanceOfAreaMaker::RBAAllInstanceOfAreaMaker()
  : RBAExpressionMaker{"AllInstanceOfArea"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllInstanceOfAreaMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllInstanceOfArea>();
}

RBAModelElement*
RBAAllInstanceOfAreaMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  RBAAllInstanceOfArea* const allArea
    {dynamic_cast<RBAAllInstanceOfArea*>(element)};
  allArea->setAreas(model->getAreaImpls());

  return allArea;
}

}
