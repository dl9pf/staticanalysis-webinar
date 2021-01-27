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
 * SoundContentState implementation class header
 */
#ifndef RBASOUNDCONTENTSTATEIMPL_HPP
#define RBASOUNDCONTENTSTATEIMPL_HPP

#include <cstdint>
#include "RBASoundContentState.hpp"
#include "RBAContentState.hpp"

namespace rba
{

class RBASoundContentImpl;

class RBASoundContentStateImpl : public RBASoundContentState,
				 public RBAContentState
{
public:
  explicit RBASoundContentStateImpl(const std::string& name="");
  RBASoundContentStateImpl(const RBASoundContentStateImpl&)=delete;
  RBASoundContentStateImpl(const RBASoundContentStateImpl&&)=delete;
  RBASoundContentStateImpl& operator=(const RBASoundContentStateImpl&)=delete;
  RBASoundContentStateImpl& operator=(const RBASoundContentStateImpl&&)=delete;
  virtual ~RBASoundContentStateImpl()=default;

public:
  bool isSoundContentState() const override;
  std::string getName() const override;
  std::int32_t getPriority() const override;
  const RBASoundContent* getOwner() const override;
  std::int32_t getOrder() const override;
  std::string getUniqueName() const override;
  RBAModelElementType getModelElementType() const override;

};

}

#endif
