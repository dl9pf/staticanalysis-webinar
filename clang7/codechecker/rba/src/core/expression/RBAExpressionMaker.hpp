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

/// @file  RBAExpreessionMaker.hpp
/// @brief Abstract class definition header file for expression object generation

#ifndef RBAEXPRESSIONMAKER_HPP
#define RBAEXPRESSIONMAKER_HPP

#include <cstdint>
#include "RBAModelElementMaker.hpp"

namespace rba
{

class RBAExpression;

/// @brief Abstract class for expression object gcreation
class DLL_EXPORT RBAExpressionMaker : public RBAModelElementMaker
{
public:
  explicit RBAExpressionMaker(const std::string& label="");
  RBAExpressionMaker(const RBAExpressionMaker&)=delete;
  RBAExpressionMaker(const RBAExpressionMaker&&)=delete;
  RBAExpressionMaker& operator=(const RBAExpressionMaker&)=delete;
  RBAExpressionMaker& operator=(const RBAExpressionMaker&&)=delete;
  virtual ~RBAExpressionMaker()=default;

protected:
  /// @brief To set "Let" expression
  /// @details Generate Let expression from jsonElem and register it in expr.
  ///          Return the number of variables that have been registered
  ///          (pushed) to ModelFactory, and pop them when the reference of 
  ///          variables is completed in function that called this function.
  /// @return the number of pushed variables
  std::int32_t setLetStatement(RBAModelImpl* model,
                               RBAExpression* expr,
                               const RBAJsonElement* jsonElem);

};

}

#endif
