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

/// @file  RBAIsGreaterThanEqualOperatorMaker.hpp
/// @brief IsGreaterThanEqualOperator object generation class header file

#ifndef RBAISGREATERTHANOPERATORMAKER_HPP
#define RBAISGREATERTHANOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief IsGreaterThanEqualOperator object generation class
class RBAIsGreaterThanOperatorMaker : public RBAOperatorMaker
{
public:
  RBAIsGreaterThanOperatorMaker();
  RBAIsGreaterThanOperatorMaker(const RBAIsGreaterThanOperatorMaker&)=delete;
  RBAIsGreaterThanOperatorMaker(const RBAIsGreaterThanOperatorMaker&&)=delete;
  RBAIsGreaterThanOperatorMaker& operator=(const RBAIsGreaterThanOperatorMaker&)=delete;
  RBAIsGreaterThanOperatorMaker& operator=(const RBAIsGreaterThanOperatorMaker&&)=delete;
  virtual ~RBAIsGreaterThanOperatorMaker()=default;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
