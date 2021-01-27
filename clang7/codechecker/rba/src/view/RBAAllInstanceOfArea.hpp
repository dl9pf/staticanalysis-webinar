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
 * AllInstanceOfArea class header file
 */

#ifndef RBAAllInstanceOfArea_HPP
#define RBAAllInstanceOfArea_HPP

#include "RBAAreaSet.hpp"
#include "RBASetExpression.hpp"

namespace rba
{
class DLL_EXPORT RBAAllInstanceOfArea : public RBASetExpression
{
 public:
  RBAAllInstanceOfArea()=default;
  RBAAllInstanceOfArea(const RBAAllInstanceOfArea&)=delete;
  RBAAllInstanceOfArea(const RBAAllInstanceOfArea&&)=delete;
  RBAAllInstanceOfArea& operator=(const RBAAllInstanceOfArea&)=delete;
  RBAAllInstanceOfArea& operator=(const RBAAllInstanceOfArea&&)=delete;

 public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                        RBAArbitratorImpl* arb) const override;
  void setAreas(const std::list<const RBAAreaImpl*>& areas);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

 private:
  RBAAreaSet allAreaSet_;
};

}

#endif
