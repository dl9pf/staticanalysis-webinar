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

/// @file  RBAAllocatableMaker.cpp
/// @brief Allocatable object generator abstract class implementation

#include <iostream>
#include "RBAAllocatableMaker.hpp"
#include "RBAAllocatable.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBAAllocatableMaker::RBAAllocatableMaker(const std::string& label)
  : RBARuleObjectMaker{label},
    RBAAbstractAllocatableMaker{label}
{
}

RBAModelElement*
RBAAllocatableMaker::setProperty(RBAModelElement* element,
                                 const RBAJsonElement* jsonElem,
                                 RBAModelImpl* model,
                                 RBAModelElement* owner)
{
  static_cast<void>(RBAAbstractAllocatableMaker::setProperty(element, jsonElem, model, owner));

  const auto alloc = dynamic_cast<RBAAllocatable*>(element);

  // Set policy
  const RBAJsonElement* const policy {jsonElem->findChildren("arbitrationPolicy")};
  if(policy == nullptr) {
    std::cerr << alloc->getElementName()
              << ": arbitrationPolicy not found" << &std::endl;
    return nullptr;
  }
  alloc->setArbitrationPolicy(policy->getArbitrationPolicy());

  // Set visibility or priority
  if (alloc->isArea()) {
    const RBAJsonElement* const visibility {jsonElem->findChildren("visibility")};
    if(visibility == nullptr) {
    	std::cerr << alloc->getElementName()
                << ": visibility not found" << &std::endl;
      return nullptr;
    }
    alloc->setVisibility(visibility->getInt());
  } else if (alloc->isZone()) {
    const RBAJsonElement* const priority {jsonElem->findChildren("priority")};
    if(priority == nullptr) {
      std::cerr << alloc->getElementName()
                << ": priority not found" << &std::endl;
      return nullptr;
    }
    alloc->setVisibility(priority->getInt());
  } else {
    ;
  }

  model->addAllocatable(alloc);

  return alloc;
}

}
