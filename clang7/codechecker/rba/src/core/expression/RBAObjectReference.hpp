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

/// ObjectReference class header

#ifndef RBAOBJECTREFERENCE_HPP
#define RBAOBJECTREFERENCE_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAObjectReference : public RBAExpression
{
public:
  RBAObjectReference()=default;
  RBAObjectReference(const RBAObjectReference&)=delete;
  RBAObjectReference(const RBAObjectReference&&)=delete;
  RBAObjectReference& operator=(const RBAObjectReference&)=delete;
  RBAObjectReference& operator=(const RBAObjectReference&&)=delete;
  virtual ~RBAObjectReference()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitratorImpl* arb) const override;
  void setRefObject(const RBARuleObject* const newRefObject);

  // Log
#ifdef RBA_USE_LOG
  void setExpressionType(RBAExpressionType const newExprType);
  void createHierarchy() override;
  const std::string getExpressionText() const override;
  RBAExpressionType getUnderlyingType() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  const RBARuleObject* refObject_;
#ifdef RBA_USE_LOG
  RBAExpressionType expressionType_;
#endif

};

}

#endif
