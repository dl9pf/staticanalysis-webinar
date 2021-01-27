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
 * If statement class header file
 */

#ifndef RBAIFSTATEMENT_HPP
#define RBAIFSTATEMENT_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAIfStatement : public RBAExpression
{
public:
  RBAIfStatement()=default;
  RBAIfStatement(const RBAIfStatement&)=delete;
  RBAIfStatement(const RBAIfStatement&&)=delete;
  RBAIfStatement& operator=(const RBAIfStatement&)=delete;
  RBAIfStatement& operator=(const RBAIfStatement&&)=delete;
  virtual ~RBAIfStatement()=default;

public:
  void setCondition(RBAExpression* const expr);
  void setThenExpression(RBAExpression* const expr);
  void setElseExpression(RBAExpression* const expr);
  RBAExpression* const getCondition() const;
  RBAExpression* const getThenExpression() const;
  RBAExpression* const getElseExpression() const;

  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitratorImpl* arb) const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitratorImpl* arb) const override;
  void doActionCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

 private:
  RBAExpression* condition_ {nullptr};
  RBAExpression* thenExpression_ {nullptr};
  RBAExpression* elseExpression_ {nullptr};

};

}

#endif
