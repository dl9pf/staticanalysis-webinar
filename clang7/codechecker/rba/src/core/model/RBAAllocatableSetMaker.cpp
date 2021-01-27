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

/// @file  RBAAllocatableSetMaker.cpp
/// @brief AllocatableSet object genartor abstract class implementation

#include <iostream>
#include "RBAAllocatableSetMaker.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllocatableSetMaker::RBAAllocatableSetMaker(const std::string& label)
  : RBARuleObjectMaker{label},
    RBAAbstractAllocatableMaker{label}
{
}

RBAModelElement*
RBAAllocatableSetMaker::setProperty(RBAModelElement* element,
                                    const RBAJsonElement* jsonElem,
                                    RBAModelImpl* model,
                                    RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractAllocatableMaker::setProperty(element, jsonElem, model, owner));

  const auto allocSet = dynamic_cast<RBAAllocatableSet*>(element);

  // Set target
  const RBAJsonElement* const target {jsonElem->findChildren("target")};
  for(const auto& targetElem : target->getChildren()) {
    const auto alloc = model->findAllocatable(targetElem->getName());
    allocSet->addTarget(alloc);
  }

  return allocSet;
}

}
