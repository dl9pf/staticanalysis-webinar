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
 * Operator class header
 */

#ifndef RBAOPERATOR_HPP
#define RBAOPERATOR_HPP

#include <vector>
#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBAOperator : public RBAExpression
{
protected:
  RBAOperator()=default;
  RBAOperator(const RBAOperator&)=delete;
  RBAOperator(const RBAOperator&&)=delete;
  RBAOperator& operator=(const RBAOperator&)=delete;
  RBAOperator& operator=(const RBAOperator&&)=delete;

public:
  const std::vector<RBAExpression*>& getOperand() const;
  void addOperand(RBAExpression* const newExpr);
  RBAExpression* getLhsOperand() const;
  RBAExpression* getRhsOperand() const;

  // Log
#ifdef RBA_USE_LOG
  virtual const std::string getSymbol() const;
  void createHierarchy() override;
#endif

protected:
  std::string const getPreMsg(const bool isPrevious) const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::vector<RBAExpression*> operand_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

}

#endif
