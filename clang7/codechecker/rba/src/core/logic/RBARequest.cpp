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
 * RBARequest (request arbitration) class implementation 
 */

#include "RBARequest.hpp"

namespace rba
{

RBARequest::RBARequest(const std::string& context, const bool isOn) :
  context_{context},
  isOn_{isOn}
{
}

std::string
RBARequest::getContext() const
{
  return context_;
}

bool
RBARequest::isOn() const
{
  return isOn_;
}

}
