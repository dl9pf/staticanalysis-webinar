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
/// @file  RBARuleObjectMaker.cpp
/// @brief RuleObject generator class 

#include "RBARuleObjectMaker.hpp"
#include "RBARuleObject.hpp"
#include "RBAJsonElement.hpp"
#include "RBAModelElement.hpp"
#include "RBAModelImpl.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

RBARuleObjectMaker::RBARuleObjectMaker(const std::string& label)
  : RBAModelElementMaker{label}
{  
}

RBAModelElement*
RBARuleObjectMaker::setProperty(RBAModelElement* element,
                                const RBAJsonElement* jsonElem,
                                RBAModelImpl* model,
                                RBAModelElement* owner)
{
  const auto ruleObj = dynamic_cast<RBARuleObject*>(element);

  // Tag
  const RBAJsonElement* const tags {jsonElem->findChildren("tags")};
  if (tags != nullptr) {
    for (const auto& tag : tags->getChildren()) {
      const RBAJsonElement* const tagName {tag->findChildren("name")};
      if (tagName != nullptr) {
        ruleObj->addTag(tagName->getString());
      }
    }
  }

  // owner
  const auto ownerRuleObj = dynamic_cast<RBARuleObject*>(owner);
  if (ownerRuleObj != nullptr) {
    ruleObj->setOwner(ownerRuleObj);
  }

  return ruleObj;
}

}
