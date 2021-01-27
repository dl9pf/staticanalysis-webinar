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
 * LambdaContext class header file
 */

#ifndef RBALAMBDACONTEXT_HPP
#define RBALAMBDACONTEXT_HPP

#include "RBASetOperator.hpp"

namespace rba
{

class RBALambdaExpression;

class DLL_EXPORT RBALambdaContext : public RBASetOperator
{
protected:
  RBALambdaContext()=default;
  RBALambdaContext(const RBALambdaContext&)=delete;
  RBALambdaContext(const RBALambdaContext&&)=delete;
  RBALambdaContext& operator=(const RBALambdaContext&)=delete;
  RBALambdaContext& operator=(const RBALambdaContext&&)=delete;
public:
  virtual ~RBALambdaContext()=default;

public:
  RBALambdaExpression* const getLambda() const;
  void setLambda(RBALambdaExpression* const newLambda);

#ifdef RBA_USE_LOG
  void createHierarchy() override;
#endif

private:
  RBALambdaExpression* lambda_ {nullptr};

};

}

#endif
