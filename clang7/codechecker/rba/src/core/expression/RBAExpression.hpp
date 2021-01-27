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
 * Expression class header file
 */

#ifndef RBAEXPRESSION_HPP
#define RBAEXPRESSION_HPP

#include <cstdint>
#include <string>
#include <vector>
#include "RBAModelElement.hpp"

namespace rba
{

class RBAExpressionVisitor;
class RBALetStatement;
class RBAArbitratorImpl;
class RBARuleObject;
class RBAConstraintInfo;
#ifdef RBA_USE_LOG
enum class RBAExpressionType : std::uint8_t;
#endif

class DLL_EXPORT RBAExpression : public RBAModelElement
{
protected:
  RBAExpression()=default;
  RBAExpression(const RBAExpression&)=delete;
  RBAExpression(const RBAExpression&&)=delete;
  RBAExpression& operator=(const RBAExpression&)=delete;
  RBAExpression& operator=(const RBAExpression&&)=delete;

public:
  virtual ~RBAExpression()=default;
  void addLetStatement(RBALetStatement* const letStatement);
  virtual void accept(RBAExpressionVisitor& visitor);
  bool execute(RBAConstraintInfo* const info, RBAArbitratorImpl* const arb) const;
  const RBARuleObject* getReferenceObject(RBAConstraintInfo* const info,
                                          RBAArbitratorImpl* const arb) const;
  std::int32_t getValue(RBAConstraintInfo* const info, RBAArbitratorImpl* const arb) const;
  void doAction(RBAConstraintInfo* const info, RBAArbitratorImpl* const arb);
  const std::vector<RBALetStatement*>& getLetStatements() const;

  // Log
#ifdef RBA_USE_LOG
  virtual const std::string getExpressionText() const;
  virtual const std::string getCoverageExpressionText() const;
  virtual void createHierarchy();
  virtual RBAExpressionType getUnderlyingType() const;
#endif

protected:
  virtual bool executeCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const;
  virtual const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                                      RBAArbitratorImpl* arb) const;
  virtual std::int32_t getValueCore(RBAConstraintInfo* info,
                                    RBAArbitratorImpl* arb) const;
  virtual void doActionCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::vector<RBALetStatement*> letStatements_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
