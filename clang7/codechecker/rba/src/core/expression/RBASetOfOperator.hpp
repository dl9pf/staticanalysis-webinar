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
 * RBASetOfOperator class header
 */

#ifndef RBASETOFOPERATOR_HPP
#define RBASETOFOPERATOR_HPP

#include <memory>
#include "RBAOperator.hpp"

namespace rba
{

class RBAAllocatableSet;
class RBAContentSet;

class DLL_EXPORT RBASetOfOperator : public RBAOperator
{
public:
  RBASetOfOperator();
  RBASetOfOperator(const RBASetOfOperator&)=delete;
  RBASetOfOperator(const RBASetOfOperator&&)=delete;
  RBASetOfOperator& operator=(const RBASetOfOperator&)=delete;
  RBASetOfOperator& operator=(const RBASetOfOperator&&)=delete;
  virtual ~RBASetOfOperator()=default;
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
  void createHierarchy() override;
  RBAExpressionType getUnderlyingType() const override;
#endif

protected:
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitratorImpl* arb) const override;
  void doActionCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAAllocatableSet> allocatableSet_;
  std::unique_ptr<RBAContentSet> contentSet_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
