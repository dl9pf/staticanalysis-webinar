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

/// @file  RBAHasBeenDisplayedMaker.cpp
/// @brief HasBeenDisplayed object generation class defintion file

#include "RBAHasBeenDisplayedMaker.hpp"
#include "RBAHasBeenDisplayed.hpp"

namespace rba
{

RBAHasBeenDisplayedMaker::RBAHasBeenDisplayedMaker()
  : RBAOperatorMaker{"HasBeenDisplayed"}
{
}

std::unique_ptr<RBAModelElement>
RBAHasBeenDisplayedMaker::createInstance(const std::string& name)
{
  return std::make_unique<RBAHasBeenDisplayed>();
}

}
