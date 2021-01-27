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
 * View Content implmentation class
 */

#include "RBAViewContentImpl.hpp"

#include "RBAAreaImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAViewContentImpl::RBAViewContentImpl(const std::string& name)
  : RBARuleObject{name},
    RBAViewContent(),
    RBAContent{name}
{
}

/**
 * Return true if RBAViewContent
 */
bool
RBAViewContentImpl::isViewContent() const
{
  return true;
}

std::string
RBAViewContentImpl::getName() const
{
  return RBANamedElement::getElementName();
}

const std::list<const RBAViewContentState*>&
RBAViewContentImpl::getContentStates() const
{
  if(externStates_.size() == 0U) {
    for(const RBAContentState* state : getStates()) {
      externStates_.push_back(dynamic_cast<const RBAViewContentStateImpl*>(state));
    }
  }
  return externStates_;
}

const std::list<const RBAArea*>&
RBAViewContentImpl::getAreas() const
{
  if(externAreas_.size() == 0U) {
    for(const RBAAllocatable* allocatable : getAllocatables()) {
      externAreas_.push_back(dynamic_cast<const RBAAreaImpl*>(allocatable));
    }
  }
  return externAreas_;
}

const std::list<const RBASize*>&
RBAViewContentImpl::getSizes() const
{
  return externSizes_;
}

RBAContentLoserType
RBAViewContentImpl::getLoserType() const
{
  return getContentLoserType();
}

void
RBAViewContentImpl::addSize(const RBASizeImpl* size)
{
  externSizes_.push_back(size);
}

RBAModelElementType
RBAViewContentImpl::getModelElementType() const
{
  return RBAModelElementType::ViewContent;
}

#ifdef RBA_USE_LOG
std::string
RBAViewContentImpl::getSymbol() const
{
  return "ViewContent";
}

std::string
RBAViewContentImpl::getVisibleSymbol() const
{
  return "visible";
}
#endif

}
