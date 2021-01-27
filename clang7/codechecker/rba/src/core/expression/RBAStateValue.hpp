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

 /// StateValue class header

#ifndef RBASTATEVALUE_HPP
#define RBASTATEVALUE_HPP

#include <cstdint>
#include "RBAContentOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAStateValue : public RBAContentOperator
{
public:
  RBAStateValue()=default;
  RBAStateValue(const RBAStateValue&)=delete;
  RBAStateValue(RBAStateValue&&)=delete;
  RBAStateValue& operator=(const RBAStateValue&)=delete;
  RBAStateValue& operator=(RBAStateValue&&)=delete;
  virtual ~RBAStateValue()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                            RBAArbitratorImpl* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif

};

}

#endif
