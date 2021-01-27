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
 * RBARequestQueueMember class implementation 
 */

#include <cstdint>

#include "RBARequestQueMember.hpp"
#include "RBAContentState.hpp"

namespace rba {

RBARequestQueMember::RBARequestQueMember(const RBAContentState* const contentState, const bool isOn,
                                         const std::uint32_t syncIndex):
    contentState_{contentState},
    isOn_{isOn},
    syncIndex_{syncIndex}
{
}

const RBAContentState* RBARequestQueMember::getContentState() const {
  return contentState_;
}

bool RBARequestQueMember::isOn() const {
  return isOn_;
}

std::uint32_t RBARequestQueMember::getSyncIndex() const {
  return syncIndex_;
}

}
