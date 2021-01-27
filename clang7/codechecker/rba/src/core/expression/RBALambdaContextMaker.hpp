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

/// @file  RBALambdaContextMaker.cpp
/// @brief LambdaContext object generation abstract class header file

#ifndef RBASETOPERATORMAKER_HPP
#define RBASETOPERATORMAKER_HPP

#include "RBAOperatorMaker.hpp"

namespace rba
{

class RBALambdaContext;

/// @brief LambdaContext object generation abstract class
class RBALambdaContextMaker : public RBAOperatorMaker
{
public:
  explicit RBALambdaContextMaker(const std::string& label="");
  RBALambdaContextMaker(const RBALambdaContextMaker&)=delete;
  RBALambdaContextMaker(const RBALambdaContextMaker&&)=delete;
  RBALambdaContextMaker& operator=(const RBALambdaContextMaker&)=delete;
  RBALambdaContextMaker& operator=(const RBALambdaContextMaker&&)=delete;
  virtual ~RBALambdaContextMaker()=default;

protected:
  /// @brief Set model element attributes for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store generated object
  /// @param[in,out] owner Parent object (Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner=nullptr) override;

  /// @brief generate an empty object of LambdaContext
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for LambdaContext object
  virtual std::unique_ptr<RBALambdaContext> createLambdaContext()=0;

};

}

#endif
