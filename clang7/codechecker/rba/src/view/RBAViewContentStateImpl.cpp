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
 *  View Content state implementation class
 */

#include "RBAViewContentImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAViewContentStateImpl::RBAViewContentStateImpl(const std::string& name)
  : RBAViewContentState(),
    RBAContentState{name}
{
}

std::string
RBAViewContentStateImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBAViewContentStateImpl::getPriority() const
{
  return getContentStatePriority();
}

const RBAViewContent*
RBAViewContentStateImpl::getOwner() const
{
  return dynamic_cast<const RBAViewContent*>(RBARuleObject::getOwner());
}

std::int32_t
RBAViewContentStateImpl::getOrder() const
{
  return getContentStateOrder();
}

std::string
RBAViewContentStateImpl::getUniqueName() const
{
  return RBARuleObject::getOwner()->getUniqueName() + CONTEXT_SEPARATER + getName();
}

bool
RBAViewContentStateImpl::isViewContentState() const
{
  return true;
}

RBAModelElementType
RBAViewContentStateImpl::getModelElementType() const
{
  return RBAModelElementType::ViewContentState;
}

}
