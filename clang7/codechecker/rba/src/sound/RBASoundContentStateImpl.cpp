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
 * SoundContentState implementation class
 */

#include "RBASoundContentStateImpl.hpp"
#include "RBAContent.hpp"
#include "RBAContentState.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASoundContentStateImpl::RBASoundContentStateImpl(const std::string& name)
  : RBASoundContentState(),
    RBAContentState{name}
{
}

bool
RBASoundContentStateImpl::isSoundContentState() const
{
  return true;
}

std::string
RBASoundContentStateImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBASoundContentStateImpl::getPriority() const
{
  return getContentStatePriority();
}

const RBASoundContent*
RBASoundContentStateImpl::getOwner() const
{
  return dynamic_cast<const RBASoundContentImpl*>(RBARuleObject::getOwner());
}

std::int32_t
RBASoundContentStateImpl::getOrder() const
{
  return getContentStateOrder();
}

std::string
RBASoundContentStateImpl::getUniqueName() const
{
  return RBARuleObject::getOwner()->getUniqueName() + CONTEXT_SEPARATER + getName();
}

RBAModelElementType
RBASoundContentStateImpl::getModelElementType() const
{
  return RBAModelElementType::SoundContentState;
}

}
