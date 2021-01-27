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
 * Variable class header
 */

#ifndef RBAVARIABLE_HPP
#define RBAVARIABLE_HPP

#include <memory>
#include "RBARuleObject.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

class DLL_EXPORT RBAVariable : public RBARuleObject
{
public:
  explicit RBAVariable(const std::string& name="");
  RBAVariable(const RBAVariable&)=delete;
  RBAVariable(const RBAVariable&&)=delete;
  RBAVariable& operator=(const RBAVariable&)=delete;
  RBAVariable& operator=(const RBAVariable&&)=delete;
  virtual ~RBAVariable()=default;

public:
  RBAModelElementType getModelElementType() const override;

  const RBARuleObject* getRuleObj() const;
  void setRuleObj(const RBARuleObject* const ruleObj);
  void clearRuleObj();
  RBAConstraintInfo* createConstraintInfo();
  std::shared_ptr<RBAConstraintInfo> getConstraintInfo() const;

private:
  const RBARuleObject* ruleObj_ {nullptr};
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::shared_ptr<RBAConstraintInfo> constraintInfo_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
