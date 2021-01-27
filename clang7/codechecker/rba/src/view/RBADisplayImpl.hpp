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
 * Display implmentation class header
 */

#ifndef RBADISPLAYIMPL_HPP
#define RBADISPLAYIMPL_HPP

#include "RBADisplay.hpp"
#include "RBANamedElement.hpp"

namespace rba
{

class RBASizeImpl;
class RBAAreaImpl;

class RBADisplayImpl : public RBADisplay, public RBANamedElement
{
public:
  explicit RBADisplayImpl(const std::string& name);
  RBADisplayImpl(const RBADisplayImpl&)=delete;
  RBADisplayImpl(const RBADisplayImpl&&)=delete;
  RBADisplayImpl& operator=(const RBADisplayImpl&)=delete;
  RBADisplayImpl& operator=(const RBADisplayImpl&&)=delete;
  virtual ~RBADisplayImpl()=default;

public:
  std::string getName() const override;
  const RBASize* getSize() const override;
  const std::list<const RBAArea*>& getAreas() const override;

  void setSize(const RBASizeImpl* const newSize);
  void addArea(const RBAAreaImpl* area);
  const std::list<const RBAArea*>& getAreaImpls() const;

private:
  std::list<const RBAArea*> areas_;
  const RBASizeImpl* size_ {nullptr};

};

}

#endif
