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
 * SceneCondition class header
 */

#ifndef RBASCENECONDITION_HPP
#define RBASCENECONDITION_HPP

#include "RBAExpression.hpp"

namespace rba
{

class DLL_EXPORT RBASceneCondition : public RBAExpression
{
protected:
  RBASceneCondition()=default;
  RBASceneCondition(const RBASceneCondition&)=delete;
  RBASceneCondition(const RBASceneCondition&&)=delete;
  RBASceneCondition& operator=(const RBASceneCondition&)=delete;
  RBASceneCondition& operator=(const RBASceneCondition&&)=delete;
public:
  virtual ~RBASceneCondition()=default;

};

}

#endif
