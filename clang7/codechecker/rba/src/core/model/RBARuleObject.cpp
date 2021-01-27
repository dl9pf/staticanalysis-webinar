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
/**
 * RuleObject class
 */

#include <string>
#include <unordered_map>
#include "RBARuleObject.hpp"

namespace rba
{

RBARuleObject::RBARuleObject(const std::string& name)
  : RBANamedElement{name}
{
}

bool
RBARuleObject::isPrevious() const
{
  return false;
}

const RBARuleObject*
RBARuleObject::getRawObject() const
{
  return this;
}

void RBARuleObject::addTag(const std::string& tag)
{
  static_cast<void>(tags_.insert(tag));
}
  
bool RBARuleObject::containsTag(const std::string& tag) const
{
  return (tags_.find(tag) != tags_.end());
}

void RBARuleObject::addMember(RBARuleObject* member)
{
  members_[member->getElementName()] = member;
}

const RBARuleObject* RBARuleObject::getMember(const std::string& memberName) const
{
  if (members_.find(memberName) != members_.end()) {
    return (members_.at(memberName));
  } else {
    return nullptr;
  }
}

void RBARuleObject::addMember(const std::string& memberName, RBARuleObject* const val)
{
  members_[memberName] = val;
}

RBARuleObject*
RBARuleObject::getOwner() const
{
  return owner_;
}
  
void
RBARuleObject::setOwner(RBARuleObject* owner)
{
  owner_ = owner;
}

std::string
RBARuleObject::getUniqueName() const
{
  if (owner_ != nullptr) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // [Contents that deviate from the rules]
    //  Calling getUniqueName() recursively.
    // [Reason that there is no problem if the rule is deviated]
    //   Since the number of elements in the rule model is finite and 
    //  there is no cyclic relationship, stack overflow does not occur.
    return owner_->getUniqueName() + "/" + getElementName();
  }
  return getElementName();
}

const std::unordered_map<std::string, RBARuleObject*>& RBARuleObject::getMembers() const
{
  return members_;
}

}
