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

/// @file  RBAIntegerValueMaker.hpp
/// @brief IntegerValue object generation class header file

#ifndef RBAINTEGERVALUEMAKER_HPP
#define RBAINTEGERVALUEMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief IntegerValue object generation class
class RBAIntegerValueMaker : public RBAExpressionMaker
{
public:
  RBAIntegerValueMaker();
  RBAIntegerValueMaker(const RBAIntegerValueMaker&)=delete;
  RBAIntegerValueMaker(const RBAIntegerValueMaker&&)=delete;
  RBAIntegerValueMaker& operator=(const RBAIntegerValueMaker&)=delete;
  RBAIntegerValueMaker& operator=(const RBAIntegerValueMaker&&)=delete;
  virtual ~RBAIntegerValueMaker()=default;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief set property of Model Element for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model Model for storing generated object
  /// @param[in,out] owner Parent object (Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner=nullptr) override;

};

}

#endif
