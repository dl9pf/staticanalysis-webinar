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

/// @file  RBAGetContentsListMaker.hpp
/// @brief GetContentsList object generation class header file

#ifndef RBAGETCONTENTSLISTMAKER_HPP
#define RBAGETCONTENTSLISTMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

/// @brief GetContentsList object generation class
class RBAGetContentsListMaker : public RBAOperatorMaker
{
public:
  RBAGetContentsListMaker();
  RBAGetContentsListMaker(const RBAGetContentsListMaker&)=delete;
  RBAGetContentsListMaker(const RBAGetContentsListMaker&&)=delete;
  RBAGetContentsListMaker& operator=(const RBAGetContentsListMaker&)=delete;
  RBAGetContentsListMaker& operator=(const RBAGetContentsListMaker&&)=delete;
  virtual ~RBAGetContentsListMaker()=default;

protected:
  /// @brief Generate an empty instance
  /// @details Generate an empty class of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

};

}

#endif
