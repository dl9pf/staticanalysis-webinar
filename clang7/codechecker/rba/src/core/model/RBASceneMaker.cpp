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
/// @file  RBASceneMaker.cpp
/// @brief Scene  object generator class

#include "RBASceneMaker.hpp"
#include "RBASceneImpl.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba
{

RBASceneMaker::RBASceneMaker()
  : RBARuleObjectMaker{"scenes"}
{
}

std::unique_ptr<RBAModelElement>
RBASceneMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBASceneImpl>(name);
}

RBAModelElement*
RBASceneMaker::setProperty(RBAModelElement* element,
                           const RBAJsonElement* jsonElem,
                           RBAModelImpl* model,
                           RBAModelElement* owner)
{
  static_cast<void>(RBARuleObjectMaker::setProperty(element, jsonElem, model, owner));

  RBASceneImpl* const scene {dynamic_cast<RBASceneImpl*>(element)};

  // Set global
  const std::string global {jsonElem->findChildren("global")->getString()};
  if(global == "true") {
    scene->setGlobal(true);
  }
  else {
    scene->setGlobal(false);
  }

  // Set property
  const RBAJsonElement* const properties {jsonElem->findChildren("property")};
  if(properties != nullptr) {
    for(const auto& property : properties->getChildren()) {
      const std::string propertyName {property->findChildren("name")->getString()};
      const std::int32_t value {property->findChildren("value")->getInt()};
      static_cast<void>(scene->addProperty(propertyName, value));
    }
  }

  model->addScene(scene);

  return scene;
}

}
