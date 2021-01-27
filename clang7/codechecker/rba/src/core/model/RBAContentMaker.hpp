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

/// @file  RBAContentMaker.hpp
/// @brief Content obecjt generator class header

#ifndef RBACONTENTMAKER_HPP
#define RBACONTENTMAKER_HPP

#include "RBAAbstractContentMaker.hpp"

namespace rba
{

/// @brief Content obecjt generator class
class DLL_EXPORT RBAContentMaker : public RBAAbstractContentMaker
{
public:
  explicit RBAContentMaker(const std::string& label="");
  RBAContentMaker(const RBAContentMaker&)=delete;
  RBAContentMaker(const RBAContentMaker&&)=delete;
  RBAContentMaker& operator=(const RBAContentMaker&)=delete;
  RBAContentMaker& operator=(const RBAContentMaker&&)=delete;
  virtual ~RBAContentMaker()=default;

protected:
  /// @brief Set model element attributes for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store generated RBARuleObjectMaker
  /// @param[in,out] owner Parent object (Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                               const RBAJsonElement* jsonElem,
                               RBAModelImpl* model,
                               RBAModelElement* owner=nullptr) override;

};

}

#endif
