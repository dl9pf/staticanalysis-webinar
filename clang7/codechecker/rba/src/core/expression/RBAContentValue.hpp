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

/* 
 * ContentValue class header file 
 */

#ifndef RBACONTENTVALUE_HPP
#define RBACONTENTVALUE_HPP

#include <cstdint>
#include "RBAAllocatableOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAContentValue : public RBAAllocatableOperator
{
public:
  RBAContentValue()=default;
  RBAContentValue(const RBAContentValue&)=delete;
  RBAContentValue(RBAContentValue&&)=delete;
  RBAContentValue& operator=(const RBAContentValue&)=delete;
  RBAContentValue& operator=(RBAContentValue&&)=delete;
  virtual ~RBAContentValue()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                            RBAArbitratorImpl* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif

};

}

#endif
