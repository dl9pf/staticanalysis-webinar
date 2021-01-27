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
 * Integer value class
 */

#ifndef RBAINTEGERVALUE_HPP
#define RBAINTEGERVALUE_HPP

#include "RBAValueExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAIntegerValue : public RBAValueExpression
{
public:
  RBAIntegerValue()=default;
  RBAIntegerValue(const RBAIntegerValue&)=delete;
  RBAIntegerValue(const RBAIntegerValue&&)=delete;
  RBAIntegerValue& operator=(const RBAIntegerValue&)=delete;
  RBAIntegerValue& operator=(const RBAIntegerValue&&)=delete;
  virtual ~RBAIntegerValue()=default;

public:
  void setValue(const std::int32_t value);

  std::int32_t getValue() const;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitratorImpl * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

 private:
  std::int32_t value_ {0};

};

}

#endif
