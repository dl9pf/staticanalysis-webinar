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
 * ContentState class header
 */

#ifndef RBACONTENTSTATE_HPP
#define RBACONTENTSTATE_HPP

#include <cstdint>
#include "RBARuleObject.hpp"

namespace rba
{

class DLL_EXPORT RBAContentState : public RBARuleObject
{
protected:
  explicit RBAContentState(const std::string& name);
  RBAContentState(const RBAContentState&)=delete;
  RBAContentState(const RBAContentState&&)=delete;
  RBAContentState& operator=(const RBAContentState&)=delete;
  RBAContentState& operator=(const RBAContentState&&)=delete;

public:
  virtual ~RBAContentState()=default;

public:
  void clearStatus() final;
  virtual bool isViewContentState() const;
  virtual bool isSoundContentState() const;

  std::string getUniqueName() const override;
  std::int32_t getContentStatePriority() const;
  void setPriority(const std::int32_t newPriority);
  std::int32_t getContentStateOrder() const;
  void setOrder(const std::int32_t newOrder);

  static bool compareFirstComeFirst(const RBAContentState* const lhs,
				    const RBAContentState* const rhs);
  static bool compareLastComeFirst(const RBAContentState* const lhs,
				   const RBAContentState* const rhs);
  static bool comparePriorityFirstComeFirst(const RBAContentState* const lhs,
					    const RBAContentState* const rhs);
  static bool comparePriorityLastComeFirst(const RBAContentState* const lhs,
					   const RBAContentState* const rhs);

  // Log
  const std::string getPriorityString() const;
  const std::string getOrderString() const;
  
private:
  std::int32_t priority_ {0};
  std::int32_t order_ {0};

};

}

#endif
