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
 * RBALambdaExpression class header
 */

#ifndef RBALAMBDAEXPRESSION_HPP
#define RBALAMBDAEXPRESSION_HPP

#include "RBAExpression.hpp"

namespace rba
{

class RBAArbitratorImpl;
class RBAConstraintInfo;
class RBAVariable;
class RBARuleObject;

class DLL_EXPORT RBALambdaExpression : public RBAExpression
{
public:
  RBALambdaExpression()=default;
  RBALambdaExpression(const RBALambdaExpression&)=delete;
  RBALambdaExpression(const RBALambdaExpression&&)=delete;
  RBALambdaExpression& operator=(const RBALambdaExpression&)=delete;
  RBALambdaExpression& operator=(const RBALambdaExpression&&)=delete;
  virtual ~RBALambdaExpression()=default;

public:
  void setX(RBAVariable* const x);
  void setBodyText(RBAExpression* const expr);
  RBAVariable* const getX() const;
  RBAExpression* const getBodyText() const;

  RBAModelElementType getModelElementType() const override;
  bool executeCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitratorImpl* arb) const override;
  std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitratorImpl* arb) const override;

  void setRuleObj(const RBARuleObject* const ruleObj);
  void clearRuleObj();

  // Log
#ifdef RBA_USE_LOG
  void createHierarchy();
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  // "variable" is not const because it calls setExpression() 
  // in the arbitration process.
  RBAVariable* variable_;
  RBAExpression* bodyText_ {nullptr};
  const RBARuleObject* ruleObj_ {nullptr};
};

}

#endif
