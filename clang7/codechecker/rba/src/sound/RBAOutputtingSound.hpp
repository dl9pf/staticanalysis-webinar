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
 * OutputtingSound class header
 */

#ifndef RBAOUTPUTTINGSOUND_HPP
#define RBAOUTPUTTINGSOUND_HPP

#include <string>
#include "RBAZoneOperator.hpp"

namespace rba
{

class DLL_EXPORT RBAOutputtingSound : public RBAZoneOperator
{
public:
  RBAOutputtingSound()=default;
  RBAOutputtingSound(const RBAOutputtingSound&)=delete;
  RBAOutputtingSound(const RBAOutputtingSound&&)=delete;
  RBAOutputtingSound& operator=(const RBAOutputtingSound&)=delete;
  RBAOutputtingSound& operator=(const RBAOutputtingSound&&)=delete;
  virtual ~RBAOutputtingSound()=default;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitratorImpl* arb) const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getSymbol() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

};

}

#endif
