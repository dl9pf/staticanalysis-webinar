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
 * Scene implementation class header
 */

#ifndef RBASCENEIMPL_HPP
#define RBASCENEIMPL_HPP

#include <memory>
#include "RBAScene.hpp"
#include "RBARuleObject.hpp"

namespace rba
{

class RBAAbstractProperty;

class RBASceneImpl : public RBAScene, public RBARuleObject
{
public:
  explicit RBASceneImpl(const std::string& name="");
  RBASceneImpl(const RBASceneImpl&)=delete;
  RBASceneImpl(const RBASceneImpl&&)=delete;
  RBASceneImpl& operator=(const RBASceneImpl&)=delete;
  RBASceneImpl& operator=(const RBASceneImpl&&)=delete;
  virtual ~RBASceneImpl()=default;

public:
  std::string getName() const override;
  RBAModelElementType getModelElementType() const override;
  bool isGlobal() const override;
  const std::list<std::string>& getPropertyNames() const override;
  std::int32_t getPropertyValue(const std::string& propertyName) const override;
  const RBARuleObject* getMember(const std::string& memberName) const override;
  const RBAAbstractProperty* getProperty(const std::string& propertyName) const;

  void setGlobal(const bool newGlobal);
  const RBAAbstractProperty* addProperty(const std::string& newName,
                                         std::int32_t newValue);

private:
  bool global_ {false};
  // Used to get property name in RBAScene
  std::list<std::string> propertyNames_; 
  std::list<std::unique_ptr<RBAAbstractProperty>> properties_;
  std::unordered_map<std::string, RBAAbstractProperty*> nameToProperty_;
};

}

#endif
