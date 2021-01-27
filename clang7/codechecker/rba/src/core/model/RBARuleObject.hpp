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
 * RuleObject class header
 */

#ifndef RBARULEOBJECT_HPP
#define RBARULEOBJECT_HPP

#include <unordered_map>
#include <unordered_set>
#include <string>

#include "RBANamedElement.hpp"

namespace rba
{

class DLL_EXPORT RBARuleObject : public RBANamedElement
{
protected:
  explicit RBARuleObject(const std::string& name="");
  RBARuleObject(const RBARuleObject&)=delete;
  RBARuleObject(const RBARuleObject&&)=delete;
  RBARuleObject& operator=(const RBARuleObject&)=delete;
  RBARuleObject& operator=(const RBARuleObject&&)=delete;

public:
  virtual ~RBARuleObject()=default;
  virtual bool isPrevious() const;
  virtual const RBARuleObject* getRawObject() const;
  bool containsTag(const std::string& tag) const;
  void addTag(const std::string& tag);
  virtual void addMember(RBARuleObject* member);
  virtual const RBARuleObject* getMember(const std::string& memberName) const;
  RBARuleObject* getOwner() const;
  virtual void setOwner(RBARuleObject* owner);
  std::string getUniqueName() const override;

protected:
  void addMember(const std::string& memberName, RBARuleObject* const val);
  const std::unordered_map<std::string, RBARuleObject*>& getMembers() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unordered_set<std::string> tags_;
  std::unordered_map<std::string, RBARuleObject*> members_;
  RBARuleObject* owner_ {nullptr};
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
