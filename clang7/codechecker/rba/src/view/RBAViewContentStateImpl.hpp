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
 *  View Content state implementation class header
 */

#ifndef RBAVIEWCONTENTSTATEIMPL_HPP
#define RBAVIEWCONTENTSTATEIMPL_HPP

#include <cstdint>
#include "RBAViewContentState.hpp"
#include "RBAContentState.hpp"

namespace rba
{

class RBAViewContentImpl;

class RBAViewContentStateImpl : public RBAViewContentState,
				public RBAContentState
{
public:
  explicit RBAViewContentStateImpl(const std::string& name="");
  RBAViewContentStateImpl(const RBAViewContentStateImpl&)=delete;
  RBAViewContentStateImpl(const RBAViewContentStateImpl&&)=delete;
  RBAViewContentStateImpl& operator=(const RBAViewContentStateImpl&)=delete;
  RBAViewContentStateImpl& operator=(const RBAViewContentStateImpl&&)=delete;
  virtual ~RBAViewContentStateImpl()=default;

public:
  std::string getName() const override;
  std::int32_t getPriority() const override;
  const RBAViewContent* getOwner() const override;
  std::int32_t getOrder() const override;
  std::string getUniqueName() const override;
  bool isViewContentState() const override;
  RBAModelElementType getModelElementType() const override;

};

}

#endif
