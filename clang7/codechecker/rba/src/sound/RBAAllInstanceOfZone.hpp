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
 * AllInstanceOfZone class header
 */

#ifndef RBAALLINSTANCEOFZONE_HPP
#define RBAALLINSTANCEOFZONE_HPP

#include "RBASetExpression.hpp"
#include "RBAZoneSet.hpp"

namespace rba
{

class DLL_EXPORT RBAAllInstanceOfZone : public RBASetExpression
{
public:
  RBAAllInstanceOfZone()=default;
  RBAAllInstanceOfZone(const RBAAllInstanceOfZone&)=delete;
  RBAAllInstanceOfZone(const RBAAllInstanceOfZone&&)=delete;
  RBAAllInstanceOfZone& operator=(const RBAAllInstanceOfZone&)=delete;
  RBAAllInstanceOfZone& operator=(const RBAAllInstanceOfZone&&)=delete;
  virtual ~RBAAllInstanceOfZone()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitratorImpl* arb) const override;
  void setZones(const std::list<const RBAZoneImpl*> zones);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  RBAZoneSet allZoneSet_;

};

}

#endif
