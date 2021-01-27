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

/// @file  RBAAbstractAllocatableMaker.hpp
/// @brief AbstractAllocatable generator class header

#ifndef RBAABSTRACTALLOCATABLEMAKER_HPP
#define RBAABSTRACTALLOCATABLEMAKER_HPP

#include "RBARuleObjectMaker.hpp"

namespace rba
{

/// @brief AbstractAllocatable generator class
class DLL_EXPORT RBAAbstractAllocatableMaker : virtual public RBARuleObjectMaker
{
public:
  explicit RBAAbstractAllocatableMaker(const std::string& label="");
  RBAAbstractAllocatableMaker(const RBAAbstractAllocatableMaker&)=delete;
  RBAAbstractAllocatableMaker(const RBAAbstractAllocatableMaker&&)=delete;
  RBAAbstractAllocatableMaker& operator=(const RBAAbstractAllocatableMaker&)=delete;
  RBAAbstractAllocatableMaker& operator=(const RBAAbstractAllocatableMaker&&)=delete;
  virtual ~RBAAbstractAllocatableMaker()=default;

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
