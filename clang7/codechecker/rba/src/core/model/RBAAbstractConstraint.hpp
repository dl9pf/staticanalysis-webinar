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
 * AbstractConstraint class header
 */

#ifndef RBAABSTRACTCONSTRAINT_HPP
#define RBAABSTRACTCONSTRAINT_HPP

#include <memory>
#include "RBANamedElement.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAAbstractConstraint : public RBANamedElement
{
protected:
  explicit RBAAbstractConstraint(const std::string& name);
  RBAAbstractConstraint(const RBAAbstractConstraint&)=delete;
  RBAAbstractConstraint(const RBAAbstractConstraint&&)=delete;
  RBAAbstractConstraint& operator=(const RBAAbstractConstraint&)=delete;
  RBAAbstractConstraint& operator=(const RBAAbstractConstraint&&)=delete;
  void clearInfo();

public:
  virtual ~RBAAbstractConstraint()=default;
  virtual bool isConstraint() const;
  virtual bool isRule() const;
  virtual void setExpression(RBAExpression*);
  virtual RBAExpression* const getExpression() const;
  RBAConstraintInfo* getInfo() const;

  // Log
#ifdef RBA_USE_LOG
  virtual void createHierarchy();
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAConstraintInfo> info_ {std::make_unique<RBAConstraintInfo>()};
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  RBAExpression* expression_ {nullptr};

};

}

#endif
