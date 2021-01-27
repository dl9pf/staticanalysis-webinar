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

#ifndef RBACONTENTSTATUS_HPP
#define RBACONTENTSTATUS_HPP
#include <cstdint>

#include "RBAContentStatusType.hpp"

namespace rba
{
class RBAContentState;

class RBAContentStatus
{
 public:
  RBAContentStatus()=default;
  // Copy constructor is defined in default because it is used in another class
  RBAContentStatus(const RBAContentStatus&)=default;
  RBAContentStatus(const RBAContentStatus&&)=delete;
  // Copy assignment operator is defined in default 
  //  because it is used in other classes
  RBAContentStatus& operator=(const RBAContentStatus&)=default;
  RBAContentStatus& operator=(const RBAContentStatus&&)=delete;
  virtual ~RBAContentStatus()=default;
  void onRequest();
  void setStatusType(const RBAContentStatusType type);
  RBAContentStatusType getStatusType() const;
  bool isActive() const;
  bool isUndisplayed() const;
  bool isDisplayed() const;
  bool isStandby() const;
  bool hasBeenCanceled() const;
  bool hasBeenDisplayed() const;
 private:
  RBAContentStatusType status_ {RBAContentStatusType::NoRequest};
};

} /* namespace rba */

#endif /* RBACONTENTSTATUS_HPP */
