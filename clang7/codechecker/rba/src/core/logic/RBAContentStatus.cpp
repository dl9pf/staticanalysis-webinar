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
// ContentStatus (Content state transition management) class
//

#include "RBAContentState.hpp"
#include "RBAContentStatus.hpp"
#include "RBAContentStatusType.hpp"

namespace rba
{

void RBAContentStatus::onRequest()
{
  if ((status_ != RBAContentStatusType::Displayed)
      && (status_ != RBAContentStatusType::StandBy)) {
    status_ = RBAContentStatusType::Undisplayed;
  }
}
void RBAContentStatus::setStatusType(
    const RBAContentStatusType type)
{
  status_ = type;
}
RBAContentStatusType RBAContentStatus::getStatusType() const
{
  return status_;
}
bool RBAContentStatus::isActive() const
{
  return ((status_ != RBAContentStatusType::NoRequest)
      && (status_ != RBAContentStatusType::Canceled));
}

bool RBAContentStatus::isUndisplayed() const
{
  return (status_ == RBAContentStatusType::Undisplayed);
}

bool RBAContentStatus::isDisplayed() const
{
  return (status_ == RBAContentStatusType::Displayed);
}
bool RBAContentStatus::isStandby() const
{
  return (status_ == RBAContentStatusType::StandBy);
}
bool RBAContentStatus::hasBeenCanceled() const
{
  return (status_ == RBAContentStatusType::Canceled);
}
bool RBAContentStatus::hasBeenDisplayed() const
{
  return ((status_ == RBAContentStatusType::Displayed)
      || (status_ == RBAContentStatusType::StandBy));
}
} /* namespace rba */
