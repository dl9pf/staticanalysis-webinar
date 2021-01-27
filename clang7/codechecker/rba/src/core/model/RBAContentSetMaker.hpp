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
/// @file  RBAContentSetMaker.hpp
/// @brief ContentSet object generator class header

#ifndef RBACONTENTSETMAKER_HPP
#define RBACONTENTSETMAKER_HPP

#include "RBAAbstractContentMaker.hpp"

namespace rba
{

/// @brief ContentSet object generator class
class RBAContentSetMaker : public RBAAbstractContentMaker
{
public:
  explicit RBAContentSetMaker(const std::string& label="");
  RBAContentSetMaker(const RBAContentSetMaker&)=delete;
  RBAContentSetMaker(const RBAContentSetMaker&&)=delete;
  RBAContentSetMaker& operator=(const RBAContentSetMaker&)=delete;
  RBAContentSetMaker& operator=(const RBAContentSetMaker&&)=delete;
  virtual ~RBAContentSetMaker()=default;

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
