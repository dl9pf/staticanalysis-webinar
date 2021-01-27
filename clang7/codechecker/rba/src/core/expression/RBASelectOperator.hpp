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
 * SelectOperator class header
 */

#ifndef RBASELECTOPERATOR_HPP
#define RBASELECTOPERATOR_HPP

#include "RBALambdaContext.hpp"

namespace rba
{

class RBAAllocatableSet;
class RBAContentSet;

class RBASelectOperator : public RBALambdaContext
{
 public:
  RBASelectOperator();
  RBASelectOperator(const RBASelectOperator&)=delete;
  RBASelectOperator(const RBASelectOperator&&)=delete;
  RBASelectOperator& operator=(const RBASelectOperator&)=delete;
  RBASelectOperator& operator=(const RBASelectOperator&&)=delete;
  virtual ~RBASelectOperator()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitratorImpl* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif
 private:
  std::unique_ptr<RBAAllocatableSet> allocatableSet_;
  std::unique_ptr<RBAContentSet> contentSet_;
};

} /* namespace rba */

#endif /* RBASELECTOPERATOR_HPP */
