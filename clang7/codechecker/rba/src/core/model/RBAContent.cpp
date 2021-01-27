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
 * Content class 
 */

#include "RBAContent.hpp"
#include "RBAResultImpl.hpp"
#include "RBAResultSet.hpp"
#include "RBAExpression.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

RBAContent::RBAContent(const std::string& name)
  : RBARuleObject{name},
    RBAAbstractContent{name}
{
}

bool
RBAContent::isViewContent() const
{
  return false;
}

bool
RBAContent::isSoundContent() const
{
  return false;
}

const std::list<const RBAContentState*>&
RBAContent::getStates() const
{
  return states_;
}

void
RBAContent::addState(const RBAContentState* const state)
{
  states_.push_back(state);
}

const std::list<const RBAAllocatable*>&
RBAContent::getAllocatables() const
{
  return allocatableSet_->getLeafAllocatable();
}

void
RBAContent::addAllocatable(const RBAAllocatable* const alloc)
{
  allocatableSet_->addTarget(alloc);
}

RBAContentLoserType
RBAContent::getContentLoserType() const
{
  return loserType_;
}

void
RBAContent::setLoserType(const RBAContentLoserType newLoserType)
{
  loserType_ = newLoserType;
}

const RBAAllocatableSet*
RBAContent::getAllocatableSet() const
{
  return allocatableSet_.get();
}

void RBAContent::updateRequestStatus(RBAResultSet* const resultset, const bool isOnRequest)
{
  resultset->updateRequestStatus(this, isOnRequest);
}

void RBAContent::updateStatus(RBAResultImpl* const result)
{
  result->updateStatus(this);
}

const std::list<const RBASize*>&
RBAContent::getSizes() const
{
  static const std::list<const RBASize*> sizes;
  return sizes;
}

}
