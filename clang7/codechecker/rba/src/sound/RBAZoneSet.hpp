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
 * ZoneSet class header
 */

#ifndef RBAZONESET_HPP
#define RBAZONESET_HPP

#include "RBAAllocatableSet.hpp"

namespace rba
{

class RBAZoneImpl;
class RBAZone;

class DLL_EXPORT RBAZoneSet : public RBAAllocatableSet
{
public:
  explicit RBAZoneSet(const std::string& name="");
  RBAZoneSet(const RBAZoneSet&)=delete;
  RBAZoneSet(const RBAZoneSet&&)=delete;
  RBAZoneSet& operator=(const RBAZoneSet&)=delete;
  RBAZoneSet& operator=(const RBAZoneSet&&)=delete;
  virtual ~RBAZoneSet()=default;

public:
  const std::list<const RBAZone*>& getTargets() const;
  void addTarget(const RBAAllocatable* alloc) override;
  void clear() override;
  RBAModelElementType getModelElementType() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAZone*> externZones_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
