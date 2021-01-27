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

/// @file  RBAVariableMaker.cpp
/// @brief Variable object generator class header

#ifndef RBAVARIABLEMAKER_HPP
#define RBAVARIABLEMAKER_HPP

#include "RBAModelElementMaker.hpp"

namespace rba
{

/// @brief Variable object generator class
class RBAVariableMaker : public RBAModelElementMaker
{
public:
  RBAVariableMaker();
  RBAVariableMaker(const RBAVariableMaker&)=delete;
  RBAVariableMaker(const RBAVariableMaker&&)=delete;
  RBAVariableMaker& operator=(const RBAVariableMaker&)=delete;
  RBAVariableMaker& operator=(const RBAVariableMaker&&)=delete;
  virtual ~RBAVariableMaker()=default;

public:
  /// @brief Create ModelElement object
  /// @details Create ModelElement object and register unique_ptr to model.
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store created object
  /// @param[in,out] owner Parent object (Not in use)
  /// @return ModelElement object
  RBAModelElement* create(const RBAJsonElement* jsonElem,
                          RBAModelImpl* model,
                          RBAModelElement* owner=nullptr) override;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief Set attributes of model element for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store created object
  /// @param[in,out] owner Parent object (Not in use)
  /// @return ModelElement object
  RBAModelElement* setProperty(RBAModelElement* element,
                               const RBAJsonElement* jsonElem,
                               RBAModelImpl* model,
                               RBAModelElement* owner=nullptr) override;

};

}

#endif
