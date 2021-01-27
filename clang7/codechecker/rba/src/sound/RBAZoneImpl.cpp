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
 * Zone implementation clas
 */

#include "RBASoundContentImpl.hpp"
#include "RBAZone.hpp"
#include "RBAArbitrationPolicy.hpp"
#include "RBAExpression.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAContent.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAZoneImpl::RBAZoneImpl(const std::string& name)
  : RBARuleObject{name},
    RBAZone(),
    RBAAllocatable{name}
{
}

std::string
RBAZoneImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBAZoneImpl::getPriority() const
{
  // Zone priority is treated the same as Area Visibility internally
  return getVisibility();
}

const std::list<const RBASoundContent*>&
RBAZoneImpl::getContents() const
{
  if(externContents_.size() == 0U) {
    for(const RBAContent* content : getInternalContents()) {
      externContents_.push_back(dynamic_cast<const RBASoundContentImpl*>(content));
    }
  }

  return externContents_;
}

RBAArbitrationPolicy
RBAZoneImpl::getArbitrationPolicy() const
{
  return getAllocatableArbitrationPolicy();
}

void
RBAZoneImpl::addContent(const RBASoundContentImpl* const content)
{
  RBAAbstractAllocatable::addContent(content);
}

RBAModelElementType
RBAZoneImpl::getModelElementType() const
{
  return RBAModelElementType::Zone;
}

#ifdef RBA_USE_LOG
std::string
RBAZoneImpl::getSymbol() const
{
  return "Zone";
}

std::string
RBAZoneImpl::getHiddenSymbol() const
{
  return "muted";
}
#endif

}

