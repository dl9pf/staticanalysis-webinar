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
 * ContentState class
 */

#include <string>

#include "RBAViewContentState.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"

namespace rba
{

RBAContentState::RBAContentState(const std::string& name)
  : RBARuleObject{name}
{
}

void
RBAContentState::clearStatus()
{
  order_ = 0;
}

bool
RBAContentState::isViewContentState() const
{
  return false;
}

bool
RBAContentState::isSoundContentState() const
{
  return false;
}

std::string
RBAContentState::getUniqueName() const
{
  return getOwner()->getElementName() + RBAViewContentState::CONTEXT_SEPARATER + getElementName();
}

std::int32_t
RBAContentState::getContentStatePriority() const
{
  return priority_;
}

void
RBAContentState::setPriority(const std::int32_t newPriority)
{
  priority_ = newPriority;
}
  
std::int32_t
RBAContentState::getContentStateOrder() const
{
  return order_;
}

void
RBAContentState::setOrder(const std::int32_t newOrder)
{
  order_ = newOrder;
}
  
bool
RBAContentState::compareFirstComeFirst(const RBAContentState* const lhs,
				       const RBAContentState* const rhs)
{
  return lhs->getContentStateOrder() < rhs->getContentStateOrder();
}

bool
RBAContentState::compareLastComeFirst(const RBAContentState* const lhs,
				      const RBAContentState* const rhs)
{
  return lhs->getContentStateOrder() > rhs->getContentStateOrder();
}

bool
RBAContentState::comparePriorityFirstComeFirst(const RBAContentState* const lhs,
					       const RBAContentState* const rhs)
{
  if(lhs->getContentStatePriority() == rhs->getContentStatePriority()) {
    return compareFirstComeFirst(lhs, rhs);
  }
  else {
    return lhs->getContentStatePriority() > rhs->getContentStatePriority();
  }
}

bool
RBAContentState::comparePriorityLastComeFirst(const RBAContentState* const lhs,
					      const RBAContentState* const rhs)
{
  if(lhs->getContentStatePriority() == rhs->getContentStatePriority()) {
    return compareLastComeFirst(lhs, rhs);
  }
  else {
    return lhs->getContentStatePriority() > rhs->getContentStatePriority();
  }
}

const std::string
RBAContentState::getPriorityString() const
{
  return std::to_string(priority_);
}

const std::string
RBAContentState::getOrderString() const
{
  return std::to_string(order_);
}

}
