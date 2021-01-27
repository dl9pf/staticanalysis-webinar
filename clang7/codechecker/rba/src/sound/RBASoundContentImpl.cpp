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
 * Sound Content class implementation
 */

#include "RBASoundContentImpl.hpp"
#include "RBASoundContentStateImpl.hpp"
#include "RBAZoneImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASoundContentImpl::RBASoundContentImpl(const std::string& name)
  : RBARuleObject{name},
    RBASoundContent(),
    RBAContent{name}
{
}

bool
RBASoundContentImpl::isSoundContent() const
{
  return true;
}

std::string
RBASoundContentImpl::getName() const
{
  return RBANamedElement::getElementName();
}

const std::list<const RBASoundContentState*>&
RBASoundContentImpl::getContentStates() const
{
  if(externStates_.size() == 0U) {
    for(const RBAContentState* state : getStates()) {
      externStates_.push_back(dynamic_cast<const RBASoundContentStateImpl*>(state));
    }
  }
  return externStates_;
}

const std::list<const RBAZone*>&
RBASoundContentImpl::getZones() const
{
  if(externZones_.size() == 0U) {
    for(const RBAAllocatable* allocatable : getAllocatables()) {
      externZones_.push_back(dynamic_cast<const RBAZoneImpl*>(allocatable));
    }
  }
  return externZones_;
}

RBAContentLoserType
RBASoundContentImpl::getLoserType() const
{
  return getContentLoserType();
}

RBAModelElementType
RBASoundContentImpl::getModelElementType() const
{
  return RBAModelElementType::SoundContent;
}

#ifdef RBA_USE_LOG
std::string
RBASoundContentImpl::getSymbol() const
{
  return "SoundContent";
}

std::string
RBASoundContentImpl::getVisibleSymbol() const
{
  return "sounding";
}
#endif

}
