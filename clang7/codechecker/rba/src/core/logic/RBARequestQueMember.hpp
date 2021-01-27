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
 * RBARequestQueueMember class header 
 */

#ifndef RBAREQUESTQUEMEMBER_HPP
#define RBAREQUESTQUEMEMBER_HPP

#include <cstdint>

namespace rba {

class RBAContentState;

class RBARequestQueMember {
 public:
  RBARequestQueMember(const RBAContentState* const contentState, const bool isOn, const std::uint32_t syncIndex);
  RBARequestQueMember()=delete;
  RBARequestQueMember(const RBARequestQueMember&)=delete;
  RBARequestQueMember(const RBARequestQueMember&&)=delete;
  RBARequestQueMember& operator=(const RBARequestQueMember&)=delete;
  RBARequestQueMember& operator=(const RBARequestQueMember&&)=delete;
  virtual ~RBARequestQueMember() = default;

  const RBAContentState* getContentState() const;
  bool isOn() const;
  std::uint32_t getSyncIndex() const;

 private:
  // Content state for which arbitration was requested
  const RBAContentState* contentState_; 
  // Whether display/output request or scene ON request
  bool isOn_;

  /// Index of arbitration syntax
  /// QueMenber with the same value will be arbitrated at the same timing, 
  /// and if the values are different, differential arbitration is performed.
  /// When a request for execute(list,bool) is received, the content icluded
  /// in the list will all have the same value. 
  /// When setContentState(ContentState, bool) request is received twice, 
  /// the first request and the second request have different values.
  /// When created by onRequest or onWithdrawn, 
  /// it has the same value as the request that triggered it.
  std::uint32_t syncIndex_;
};

}

#endif /* RBAREQUESTQUEMEMBER_HPP */
