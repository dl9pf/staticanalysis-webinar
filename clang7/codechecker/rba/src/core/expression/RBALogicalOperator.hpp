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
 * LogicalOperator class header
 */

#ifndef RBALOGICOPERATOR_HPP
#define RBALOGICOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBALogicalOperator : public RBAOperator
{
 protected:
  RBALogicalOperator()=default;
  RBALogicalOperator(const RBALogicalOperator&)=delete;
  RBALogicalOperator(const RBALogicalOperator&&)=delete;
  RBALogicalOperator& operator=(const RBALogicalOperator&)=delete;
  RBALogicalOperator& operator=(const RBALogicalOperator&&)=delete;

 public:
  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
