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
 * ActiveContents operator
 */

#ifndef RBAACTIVECONTENTS_HPP
#define RBAACTIVECONTENTS_HPP

#include "RBAAllocatableOperator.hpp"
#include "RBAContentSet.hpp"

namespace rba
{

class RBAActiveContents : public RBAAllocatableOperator
{
 public:
  RBAActiveContents();
  RBAActiveContents(const RBAActiveContents&)=delete;
  RBAActiveContents(const RBAActiveContents&&)=delete;
  RBAActiveContents& operator=(const RBAActiveContents&)=delete;
  RBAActiveContents& operator=(const RBAActiveContents&&)=delete;
  virtual ~RBAActiveContents()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitratorImpl* arb) const override;

#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif
 private:
  std::unique_ptr<RBAContentSet> contentSet_;
};

}

#endif
