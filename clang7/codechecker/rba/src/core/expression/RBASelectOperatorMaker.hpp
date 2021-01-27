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

/// @file  RBASelectOperatorMaker.cpp
/// @brief SelectOperator object generator class header

#ifndef RBASELECTOPERATORMAKER_HPP
#define RBASELECTOPERATORMAKER_HPP

#include "RBALambdaContextMaker.hpp"

namespace rba
{

/// @brief SelectOperator object generator class
class RBASelectOperatorMaker : public RBALambdaContextMaker
{
public:
  RBASelectOperatorMaker();
  RBASelectOperatorMaker(const RBASelectOperatorMaker&)=delete;
  RBASelectOperatorMaker(const RBASelectOperatorMaker&&)=delete;
  RBASelectOperatorMaker& operator=(const RBASelectOperatorMaker&)=delete;
  RBASelectOperatorMaker& operator=(const RBASelectOperatorMaker&&)=delete;
  virtual ~RBASelectOperatorMaker()=default;

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

  /// @brief generate an empty object of LambdaContext
  /// @details generate an empty object of unique_ptr
  /// @return unique_ptr for object of LambdaContext
  std::unique_ptr<RBALambdaContext> createLambdaContext() override;

};

}

#endif
