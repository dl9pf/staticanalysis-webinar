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
/// @file  RBASizeMaker.cpp
/// @brief Size information object generation class

#include "RBASizeMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBASizeMaker::RBASizeMaker()
  : RBAModelElementMaker::RBAModelElementMaker{"Size"}
{
}

RBAModelElement*
RBASizeMaker::create(const RBAJsonElement* jsonElem,
                     RBAModelImpl* model,
                     RBAModelElement* owner)
{
  std::unique_ptr<RBAModelElement> inst
    {createInstance(jsonElem->findChildren("name")->getString())};
  const auto element = inst.get();
  static_cast<void>(model->addSizeInstance(dynamic_cast<RBANamedElement*>(owner)->getElementName(), std::move(inst)));

  return setProperty(element, jsonElem, model, owner);
}

std::unique_ptr<RBAModelElement>
RBASizeMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASizeImpl>(name);
}

RBAModelElement*
RBASizeMaker::setProperty(RBAModelElement* element,
                          const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner)
{
  RBASizeImpl* const size {dynamic_cast<RBASizeImpl*>(element)};

  // Set width
  size->setWidth(jsonElem->findChildren("width")->getInt());
  // Set height
  size->setHeight(jsonElem->findChildren("height")->getInt());

  return size;
}

}
