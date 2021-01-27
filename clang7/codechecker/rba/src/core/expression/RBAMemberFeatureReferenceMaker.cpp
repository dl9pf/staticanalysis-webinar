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

/// @file  RBAMemberFeatureReferenceMaker.cpp
/// @brief ObjectReference of property object generator class definition

#include "RBAMemberFeatureReferenceMaker.hpp"
#include "RBAObjectReference.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba
{

RBAMemberFeatureReferenceMaker::RBAMemberFeatureReferenceMaker()
  : RBAObjectReferenceMaker{"MemberFeatureReference"}
{
}

std::unique_ptr<RBAModelElement>
RBAMemberFeatureReferenceMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAObjectReference>();
}

RBAModelElement*
RBAMemberFeatureReferenceMaker::setProperty(RBAModelElement* element,
                                            const RBAJsonElement* jsonElem,
                                            RBAModelImpl* model,
                                            RBAModelElement* owner)
{
  RBAObjectReference* const objRef {dynamic_cast<RBAObjectReference*>(element)};

  // Set reference object
  objRef->setRefObject(getRuleObject(jsonElem,model));

  return objRef;
}

const RBARuleObject*
RBAMemberFeatureReferenceMaker::getRuleObject(const RBAJsonElement* 
                                              const jsonElem,
                                              RBAModelImpl* const model)
{
  const RBARuleObject* refObj {nullptr};
  const auto typeStr = jsonElem->findChildren("type")->getString();
  const auto refObjStr = jsonElem->findChildren("refObject")->getString();

  if (jsonElem->findChildren("class")->getString() == "ObjectReference") {
    refObj = dynamic_cast<RBARuleObject*>(getMaker(typeStr)->getInstance(model,
                                          refObjStr));
  } else {  // jsonElem->findChildren("class")->getString() == "MemberFeatureReference"
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // [Contents that deviate from the rules]
    //  calling getRuleObject() recursively
    // [Explain that it is okay to deviate from the rules]
    //  When "Content name.State machine name.State name" is used
    //  in the constraint expression, it becomes the STATEMACHINE_STATE of
    //  Member of "STATEMACHINE" of "CONTENT", so recursive call is used.
    //  Since the number of elements in the rule model is finite and
    //  there is no cyclic relationship, stack overflow does not occur and 
    //  there is no problem.
    const auto owner = const_cast<RBARuleObject*>(getRuleObject(jsonElem->findChildren("operand")->getChild(), model));
    refObj = owner->getMember(refObjStr);
    if (refObj == nullptr) {
      if (getMaker(typeStr) != nullptr) {
        refObj = dynamic_cast<RBARuleObject*>(getMaker(typeStr)->getInstance(model, 
                                              refObjStr, owner));
      }
      if ((refObj == nullptr)
          && (jsonElem->findChildren("type")->getString() == "PROPERTY")) {
        refObj = dynamic_cast<RBASceneImpl*>(owner)->addProperty(refObjStr, -99);
      }
    }
  }
  return refObj;
}
}
