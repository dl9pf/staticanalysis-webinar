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

/// @file  RBAImpliesOperatorMaker.hpp
/// @brief ImpliesOperator object generation class header file

#ifndef RBAIMPLIEDOPERATORMAKER_HPP
#define RBAIMPLIEDOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief ImpliesOperator object generation class
class RBAImpliesOperatorMaker : public RBAOperatorMaker
{
public:
  RBAImpliesOperatorMaker();
  RBAImpliesOperatorMaker(const RBAImpliesOperatorMaker&)=delete;
  RBAImpliesOperatorMaker(const RBAImpliesOperatorMaker&&)=delete;
  RBAImpliesOperatorMaker& operator=(const RBAImpliesOperatorMaker&)=delete;
  RBAImpliesOperatorMaker& operator=(const RBAImpliesOperatorMaker&&)=delete;
  virtual ~RBAImpliesOperatorMaker()=default;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
