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
 * ContentSet class header
 */

#ifndef RBACONTENTSET_HPP
#define RBACONTENTSET_HPP

#include <list>
#include "RBAAbstractContent.hpp"

namespace rba
{

class RBAContent;

class DLL_EXPORT RBAContentSet : public RBAAbstractContent
{
public:
  explicit RBAContentSet(const std::string& name="");
  RBAContentSet(const RBAContentSet&)=delete;
  RBAContentSet(const RBAContentSet&&)=delete;
  RBAContentSet& operator=(const RBAContentSet&)=delete;
  RBAContentSet& operator=(const RBAContentSet&&)=delete;
  virtual ~RBAContentSet()=default;

public:
  virtual void addTarget(const RBAContent* content);
  virtual void clear();
  const std::list<const RBAContent*>& getLeafContent() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAContent*> leafContent_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
