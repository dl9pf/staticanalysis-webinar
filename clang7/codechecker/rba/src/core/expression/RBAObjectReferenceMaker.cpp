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

/// @file  RBAObjectReferenceMaker.cpp
/// @brief ObjectReference object generator class definition

#include "RBAObjectReferenceMaker.hpp"
#include "RBAObjectReference.hpp"

#include "RBAJsonElement.hpp"
#include "RBAModelFactory.hpp"
#include "RBAModelImpl.hpp"

namespace rba
{

RBAObjectReferenceMaker::RBAObjectReferenceMaker(const std::string& label)
  : RBAExpressionMaker{label}
{
}

std::unique_ptr<RBAModelElement>
RBAObjectReferenceMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAObjectReference>();
}

RBAModelElement*
RBAObjectReferenceMaker::setProperty(RBAModelElement* element,
                                     const RBAJsonElement* jsonElem,
                                     RBAModelImpl* model,
                                     RBAModelElement* owner)
{
  RBAObjectReference* const objRef {dynamic_cast<RBAObjectReference*>(element)};

  // Set reference object
  //// Getting reference object string
  const auto& refObjectStr = jsonElem->findChildren("refObject")->getString();

  //// Find object
  auto ruleObj = model->findModelElement(refObjectStr);

  if(ruleObj == nullptr) {
    ruleObj = getFactory()->getVariable(refObjectStr);
    if(ruleObj == nullptr) {
      const auto& typeStr = jsonElem->findChildren("type")->getString();
      auto maker = getMaker(typeStr);
      if (maker != nullptr) {
        ruleObj = maker->getInstance(model, refObjectStr, owner);
      }
    }
  }
  objRef->setRefObject(dynamic_cast<const RBARuleObject*>(ruleObj));

#ifdef RBA_USE_LOG
  // Set expression type
  const RBAExpressionType exprType {jsonElem->getExpressionType()};
  objRef->setExpressionType(exprType);
#endif

  return objRef;
}

}
