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
 * RBAViewTransition.cpp
 */

#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBAViewTransition.hpp"

namespace rba {

RBAViewTransition::RBAViewTransition(
    const RBAViewActionType newViewActionType, const RBAArea* const newArea,
    const RBAViewContentState* const newContentState1,
    const RBAViewContentState* const newContentState2)
    : RBAViewAction(),
      viewActionType_{newViewActionType},
      area_{newArea},
      contentState1_{newContentState1},
      contentState2_{newContentState2}
{
}

RBAViewTransition::RBAViewTransition(const RBAViewTransition& viewTrans)
  : RBAViewAction{viewTrans}
{
  viewActionType_ = viewTrans.viewActionType_;
  area_ = viewTrans.area_;
  contentState1_ = viewTrans.contentState1_;
  contentState2_ = viewTrans.contentState2_;
}

bool
RBAViewTransition::operator==(const RBAViewAction& viewAction)
{
  if(getViewActionType() != viewAction.getViewActionType()) {
    // False if the view action types do not match
    return false;
  }

  const RBAViewTransition* const viewTran
    {dynamic_cast<const RBAViewTransition*>(&viewAction)};
  return ((area_ == viewTran->area_) &&
          (contentState1_ == viewTran->contentState1_) &&
          (contentState2_ == viewTran->contentState2_));
}

const RBAArea*
RBAViewTransition::getArea() const
{
  return area_;
}

const RBAViewContent*
RBAViewTransition::getFromContent() const
{
  if((contentState1_ == nullptr) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState1_->getOwner();
}

const RBAViewContent*
RBAViewTransition::getToContent() const
{
  if((contentState2_ == nullptr) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState2_->getOwner();
}

const RBAViewContentState*
RBAViewTransition::getFromContentState() const
{
  if((viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState1_;
}
  
const RBAViewContentState*
RBAViewTransition::getToContentState() const
{
  if((viewActionType_ == RBAViewActionType::TRANSITION_ADD) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REMOVE)) {
    return nullptr;
  }
  return contentState2_;
}

const RBAViewContent*
RBAViewTransition::getContent() const
{
  if((contentState1_ == nullptr) ||
     (viewActionType_ == RBAViewActionType::TRANSITION_REPLACE)) {
    return nullptr;
  }
  return contentState1_->getOwner();
}

const RBAViewContentState*
RBAViewTransition::getContentState() const
{
  if(viewActionType_ == RBAViewActionType::TRANSITION_REPLACE) {
    return nullptr;
  }
  return contentState1_;
}

RBAViewActionType
RBAViewTransition::getViewActionType() const
{
  return viewActionType_;
}

}
