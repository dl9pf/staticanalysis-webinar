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
 * Zone implementation clas header
 */

#ifndef RBAZONEIMPL_HPP
#define RBAZONEIMPL_HPP

#include <cstdint>
#include <string>
#include "RBAAllocatable.hpp"
#include "RBAArbitrationPolicy.hpp"
#include "RBAZone.hpp"

namespace rba
{

class RBASoundContent;
class RBASoundContentImpl;

class RBAZoneImpl : public RBAZone, public RBAAllocatable
{
public:
  explicit RBAZoneImpl(const std::string& name="");
  RBAZoneImpl(const RBAZoneImpl&)=delete;
  RBAZoneImpl(const RBAZoneImpl&&)=delete;
  RBAZoneImpl& operator=(const RBAZoneImpl&)=delete;
  RBAZoneImpl& operator=(const RBAZoneImpl&&)=delete;
  virtual ~RBAZoneImpl()=default;

public:
  std::string getName() const override;
  std::int32_t getPriority() const override;
  const std::list<const RBASoundContent*>& getContents() const override;
  RBAArbitrationPolicy getArbitrationPolicy() const override;

  void addContent(const RBASoundContentImpl* const content);
  RBAModelElementType getModelElementType() const override;

  // Log
#ifdef RBA_USE_LOG
  std::string getSymbol() const override;
  std::string getHiddenSymbol() const override;
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  mutable std::list<const RBASoundContent*> externContents_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  
};

}

#endif
