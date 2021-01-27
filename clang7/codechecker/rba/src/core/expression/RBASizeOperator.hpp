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

//
// SizeOperator class header
//

#ifndef RBASIZEOPERATOR_HPP
#define RBASIZEOPERATOR_HPP

#include "RBASetOperator.hpp"

namespace rba
{

class RBASizeOperator : public RBASetOperator
{
 public:
  RBASizeOperator()=default;
  RBASizeOperator(const RBASizeOperator&)=delete;
  RBASizeOperator(const RBASizeOperator&&)=delete;
  RBASizeOperator& operator=(const RBASizeOperator&)=delete;
  RBASizeOperator& operator=(const RBASizeOperator&&)=delete;
  virtual ~RBASizeOperator()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  std::int32_t getValueCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const override;
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif
};

} /* namespace rba */

#endif /* SRC_CORE_EXPRESSION_RBASIZEOPERATOR_HPP_ */
