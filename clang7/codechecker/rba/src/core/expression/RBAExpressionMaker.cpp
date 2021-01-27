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

/// @file  RBAExpreessionMaker.cpp
/// @brief Abstract class definition file for expression object generation

#include "RBAExpressionMaker.hpp"
#include "RBAJsonElement.hpp"
#include "RBALetStatementMaker.hpp"
#include "RBALetStatement.hpp"

namespace rba
{

RBAExpressionMaker::RBAExpressionMaker(const std::string& label)
  : RBAModelElementMaker{label}
{
}

std::int32_t
RBAExpressionMaker::setLetStatement(RBAModelImpl* const model,
                                    RBAExpression* const expr,
                                    const RBAJsonElement* const jsonElem)
{
  std::int32_t var_num {0};
  const RBAJsonElement* const letElem {jsonElem->findChildren("letStatements")};
  if(letElem != nullptr) {
    RBALetStatementMaker letMaker;
    letMaker.setFactory(getFactory());
    for(const auto& param : letElem->getChildren()) {  
      // execute pushVariable() in letMaker::create()
      RBALetStatement* const letExpr
        {dynamic_cast<RBALetStatement*>(letMaker.create(param.get(), model))};
      expr->addLetStatement(letExpr);
      var_num += 1;
    }
  }

  return var_num;
}

}
