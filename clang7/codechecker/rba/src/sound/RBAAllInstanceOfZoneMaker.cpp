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
/// @file  RBAAllInstanceOfZoneMaker.cpp
/// @brief AllInstanceOfZone object generator class

#include <iostream>
#include "RBAAllInstanceOfZoneMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAllInstanceOfZone.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllInstanceOfZoneMaker::RBAAllInstanceOfZoneMaker()
  : RBAExpressionMaker{"AllInstanceOfZone"}
{
}

std::unique_ptr<RBAModelElement>
RBAAllInstanceOfZoneMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAAllInstanceOfZone>();
}

RBAModelElement*
RBAAllInstanceOfZoneMaker::setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner)
{
  RBAAllInstanceOfZone* const allInstZone
    {dynamic_cast<RBAAllInstanceOfZone*>(element)};

  // Set zone
  allInstZone->setZones(model->getZoneImpls());

  return allInstZone;
}

}
