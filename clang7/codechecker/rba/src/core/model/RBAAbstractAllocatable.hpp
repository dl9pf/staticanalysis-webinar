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
 * AbstractAllocatable class header
 */

#ifndef RBAABSTRACTALLOCATABLE_HPP
#define RBAABSTRACTALLOCATABLE_HPP

#include <memory>
#include <list>
#include "RBARuleObject.hpp"
#include "RBAContentSet.hpp"

namespace rba
{

class RBAContent;

class DLL_EXPORT RBAAbstractAllocatable : virtual public RBARuleObject
{
protected:
  explicit RBAAbstractAllocatable(const std::string& name="");
  RBAAbstractAllocatable(const RBAAbstractAllocatable&)=delete;
  RBAAbstractAllocatable(const RBAAbstractAllocatable&&)=delete;
  RBAAbstractAllocatable& operator=(const RBAAbstractAllocatable&)=delete;
  RBAAbstractAllocatable& operator=(const RBAAbstractAllocatable&&)=delete;

public:
  virtual ~RBAAbstractAllocatable()=default;

public:
  const std::list<const RBAContent*>& getInternalContents() const;
  void addContent(const RBAContent* const content);
  const RBAContentSet* getContentSet() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAContentSet> contentSet_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
