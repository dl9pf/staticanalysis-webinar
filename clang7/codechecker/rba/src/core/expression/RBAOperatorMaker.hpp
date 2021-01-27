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

/// @file  RBAOperatorMaker.hpp
/// @brief Operator object generator abstract class header

#ifndef RBAOPERATORMAKER_HPP
#define RBAOPERATORMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief Operator object generator abstract class
class DLL_EXPORT RBAOperatorMaker : public RBAExpressionMaker
{
public:
  explicit RBAOperatorMaker(const std::string& label="");
  RBAOperatorMaker(const RBAOperatorMaker&)=delete;
  RBAOperatorMaker(const RBAOperatorMaker&&)=delete;
  RBAOperatorMaker& operator=(const RBAOperatorMaker&)=delete;
  RBAOperatorMaker& operator=(const RBAOperatorMaker&&)=delete;
  virtual ~RBAOperatorMaker()=default;

protected:
  /// @brief Set model element attributes for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store generated object
  /// @param[in,out] owner Parent object (Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner) override;

};

}

#endif
