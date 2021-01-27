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
/// IsDisplayed class header

#ifndef RBAISDISPLAYED_HPP
#define RBAISDISPLAYED_HPP

#include "RBAAreaOperator.hpp"

namespace rba
{

class RBAExpression;

class DLL_EXPORT RBAIsDisplayed : public RBAAreaOperator
{
public:
  RBAIsDisplayed()=default;
  RBAIsDisplayed(const RBAIsDisplayed&)=delete;
  RBAIsDisplayed(const RBAIsDisplayed&&)=delete;
  RBAIsDisplayed& operator=(const RBAIsDisplayed&)=delete;
  RBAIsDisplayed& operator=(const RBAIsDisplayed&&)=delete;
  virtual ~RBAIsDisplayed()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitratorImpl * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
