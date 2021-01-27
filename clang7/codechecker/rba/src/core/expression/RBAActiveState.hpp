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
// activeState header
//

#ifndef RBAACTIVESTATE_HPP
#define RBAACTIVESTATE_HPP

#include "RBAContentOperator.hpp"

namespace rba
{

class RBAActiveState : public RBAContentOperator
{
 public:
  RBAActiveState()=default;
  RBAActiveState(const RBAActiveState&)=delete;
  RBAActiveState(const RBAActiveState&&)=delete;
  RBAActiveState& operator=(const RBAActiveState&)=delete;
  RBAActiveState& operator=(const RBAActiveState&&)=delete;
  virtual ~RBAActiveState()=default;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitratorImpl* arb) const override;
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
#endif
};

} /* namespace rba */

#endif /* RBAACTIVESTATE_HPP */
