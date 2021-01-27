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

//
// RBAAllwaysCheckConstraintCollector.hpp
//

#ifndef RBAALLWAYSCHECKCONSTRAINTSETTER_HPP
#define RBAALLWAYSCHECKCONSTRAINTSETTER_HPP

#include "RBAAbstractCollector.hpp"

namespace rba
{
class RBAConstraintImpl;

class RBAAllwaysCheckConstraintCollector : public RBAAbstractCollector
{
 public:
  RBAAllwaysCheckConstraintCollector(RBAModelImpl* const model);
  RBAAllwaysCheckConstraintCollector(const RBAAllwaysCheckConstraintCollector&)=default;
  RBAAllwaysCheckConstraintCollector(RBAAllwaysCheckConstraintCollector&&)=default;
  RBAAllwaysCheckConstraintCollector& operator=(const RBAAllwaysCheckConstraintCollector&)=default;
  RBAAllwaysCheckConstraintCollector& operator=(RBAAllwaysCheckConstraintCollector&&)=default;
  virtual ~RBAAllwaysCheckConstraintCollector()=default;
  void init(const RBAConstraintImpl* const constraint);
  bool isAllways() const;
  void visit(RBAPreviousModifier& exp) final;
 private:
  // Constraint expression during search
  const RBAConstraintImpl* constraint_ {nullptr};
  // True if the constraint expression being searched is a constraint expression that must always be arbitrated
  bool isAllways_ {false};
};

} /* namespace rba */

#endif /* RBAALLWAYSCHECKCONSTRAINTSETTER_HPP */
