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

/**
 * SetOperator class header
 */

#ifndef RBASETOPERATOR_HPP
#define RBASETOPERATOR_HPP

#include "RBAOperator.hpp"

namespace rba
{

class DLL_EXPORT RBASetOperator : public RBAOperator
{
protected:
  RBASetOperator()=default;
  RBASetOperator(const RBASetOperator&)=delete;
  RBASetOperator(const RBASetOperator&&)=delete;
  RBASetOperator& operator=(const RBASetOperator&)=delete;
  RBASetOperator& operator=(const RBASetOperator&&)=delete;
public:
  virtual ~RBASetOperator()=default;

};

}

#endif
