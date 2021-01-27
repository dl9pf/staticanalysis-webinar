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
 * AllocatableSet class header
 */

#ifndef RBAALLOCATABLESET_HPP
#define RBAALLOCATABLESET_HPP

#include "RBAAbstractAllocatable.hpp"

namespace rba
{

class RBAAllocatable;

class DLL_EXPORT RBAAllocatableSet : public RBAAbstractAllocatable
{
public:
  explicit RBAAllocatableSet(const std::string& name="");
  RBAAllocatableSet(const RBAAllocatableSet&)=delete;
  RBAAllocatableSet(const RBAAllocatableSet&&)=delete;
  RBAAllocatableSet& operator=(const RBAAllocatableSet&)=delete;
  RBAAllocatableSet& operator=(const RBAAllocatableSet&&)=delete;
  virtual ~RBAAllocatableSet()=default;

public:
  virtual void addTarget(const RBAAllocatable* alloc);
  virtual void clear();
  const std::list<const RBAAllocatable*>& getLeafAllocatable() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAAllocatable*> leafAllocatable_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}
#endif
