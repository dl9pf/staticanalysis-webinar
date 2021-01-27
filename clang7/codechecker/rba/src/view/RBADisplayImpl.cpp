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
 * Display implmentation class
 */

#include "RBADisplayImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBAAreaImpl.hpp"

namespace rba
{

RBADisplayImpl::RBADisplayImpl(const std::string& name)
  : RBADisplay(),
    RBANamedElement{name}
{
}

std::string
RBADisplayImpl::getName() const
{
  return RBANamedElement::getElementName();
}
  
const RBASize*
RBADisplayImpl::getSize() const
{
  return size_;
}

const std::list<const RBAArea*>&
RBADisplayImpl::getAreas() const
{
  return getAreaImpls();
}

void
RBADisplayImpl::setSize(const RBASizeImpl* const newSize)
{
  size_ = newSize;
}

void
RBADisplayImpl::addArea(const RBAAreaImpl* area)
{
  areas_.push_back(area);
}

const std::list<const RBAArea*>&
RBADisplayImpl::getAreaImpls() const
{
  return areas_;
}

}
