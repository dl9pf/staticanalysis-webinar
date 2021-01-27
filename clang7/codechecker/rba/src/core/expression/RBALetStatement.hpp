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
 * LetStatement class header file
 */

#ifndef RBALETOPERATOR_HPP_
#define RBALETOPERATOR_HPP_

#include "RBAOperator.hpp"

namespace rba {

class RBAVariable;

class DLL_EXPORT RBALetStatement : public RBAOperator
{
public:
  RBALetStatement()=default;
  RBALetStatement(const RBALetStatement&)=delete;
  RBALetStatement(const RBALetStatement&&)=delete;
  RBALetStatement& operator=(const RBALetStatement&)=delete;
  RBALetStatement& operator=(const RBALetStatement&&)=delete;
  virtual ~RBALetStatement()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  void setVariable(RBAVariable* const var);
  void setVariable(RBAArbitratorImpl* const arb);

private:
  RBAVariable* variable_;

};

}

#endif
