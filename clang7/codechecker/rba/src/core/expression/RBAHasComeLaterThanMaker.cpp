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

/// @file  RBAHasComeLaterThanMaker.cpp
/// @brief HasComeLaterThan object generation class definitino file

#include "RBAHasComeLaterThanMaker.hpp"
#include "RBAHasComeLaterThan.hpp"

namespace rba
{

RBAHasComeLaterThanMaker::RBAHasComeLaterThanMaker()
  : RBAOperatorMaker{"HasComeLaterThan"}
{
}

std::unique_ptr<RBAModelElement>
RBAHasComeLaterThanMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAHasComeLaterThan>();
}

}
