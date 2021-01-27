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
 * ObjectCompare calss header
 */

#ifndef RBAOBJECTCOMPARE_HPP
#define RBAOBJECTCOMPARE_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAObjectCompare : public RBAOperator
{
public:
  RBAObjectCompare()=default;
  RBAObjectCompare(const RBAObjectCompare&)=delete;
  RBAObjectCompare(const RBAObjectCompare&&)=delete;
  RBAObjectCompare& operator=(const RBAObjectCompare&)=delete;
  RBAObjectCompare& operator=(const RBAObjectCompare&&)=delete;
  virtual ~RBAObjectCompare()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitratorImpl * arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
