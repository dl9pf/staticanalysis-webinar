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

/// @file  RBAPreviousModifierMaker.cpp
/// @brief PreviousModifier object generator class header

#ifndef RBAPREVIOUSMODIFIERMAKER_HPP
#define RBAPREVIOUSMODIFIERMAKER_HPP

#include "RBAExpressionMaker.hpp"

namespace rba
{

/// @brief PreviousModifier object generator class
class RBAPreviousModifierMaker : public RBAExpressionMaker
{
public:
  RBAPreviousModifierMaker();
  RBAPreviousModifierMaker(const RBAPreviousModifierMaker&)=delete;
  RBAPreviousModifierMaker(const RBAPreviousModifierMaker&&)=delete;
  RBAPreviousModifierMaker& operator=(const RBAPreviousModifierMaker&)=delete;
  RBAPreviousModifierMaker& operator=(const RBAPreviousModifierMaker&&)=delete;
  virtual ~RBAPreviousModifierMaker()=default;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

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
