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

/// @file  RBAHasComeEarlierThanMaker.hpp
/// @brief HasComeEarlierThan object generation class header

#ifndef RBAHASCOMEEARLIERTHANMAKER_HPP
#define RBAHASCOMEEARLIERTHANMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief HasComeEarlierThan object generation class
class RBAHasComeEarlierThanMaker : public RBAOperatorMaker
{
public:
  RBAHasComeEarlierThanMaker();
  RBAHasComeEarlierThanMaker(const RBAHasComeEarlierThanMaker&)=delete;
  RBAHasComeEarlierThanMaker(const RBAHasComeEarlierThanMaker&&)=delete;
  RBAHasComeEarlierThanMaker& operator=(const RBAHasComeEarlierThanMaker&)=delete;
  RBAHasComeEarlierThanMaker& operator=(const RBAHasComeEarlierThanMaker&&)=delete;
  virtual ~RBAHasComeEarlierThanMaker()=default;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
