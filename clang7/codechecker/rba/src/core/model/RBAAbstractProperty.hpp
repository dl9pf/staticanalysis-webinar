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
 * Abstract property class header
 */

#ifndef RBAABSTRACTPROPERTY_HPP
#define RBAABSTRACTPROPERTY_HPP

#include <cstdint>
#include "RBARuleObject.hpp"

namespace rba
{

class RBASceneImpl;

class RBAAbstractProperty : public RBARuleObject
{
protected:
  RBAAbstractProperty(const RBASceneImpl* const scene, const std::string& name);
  RBAAbstractProperty(const RBAAbstractProperty&)=delete;
  RBAAbstractProperty(const RBAAbstractProperty&&)=delete;
  RBAAbstractProperty& operator=(const RBAAbstractProperty&)=delete;
  RBAAbstractProperty& operator=(const RBAAbstractProperty&&)=delete;

public:
  virtual ~RBAAbstractProperty()=default;

public:
  RBAModelElementType getModelElementType() const override;
  virtual std::int32_t getValue() const=0;
  virtual const RBASceneImpl* getScene() const;

  // Log
#ifdef RBA_USE_LOG
  virtual const std::string getExpressionText() const=0;
#endif

private:
  const RBASceneImpl* scene_;

};

}

#endif
