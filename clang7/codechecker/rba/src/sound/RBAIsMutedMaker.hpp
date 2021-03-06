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
/// @file  RBAIsMutedMaker.hpp
/// @brief IsMuted object generator class header

#ifndef RBAISMUTEDMAKER_HPP
#define RBAISMUTEDMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief IsMuted object generator class
class RBAIsMutedMaker : public RBAOperatorMaker
{
public:
  RBAIsMutedMaker();
  RBAIsMutedMaker(const RBAIsMutedMaker&)=delete;
  RBAIsMutedMaker(const RBAIsMutedMaker&&)=delete;
  RBAIsMutedMaker& operator=(const RBAIsMutedMaker&)=delete;
  RBAIsMutedMaker& operator=(const RBAIsMutedMaker&&)=delete;
  virtual ~RBAIsMutedMaker()=default;

protected:
  /// @brief Empty instanciation
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
