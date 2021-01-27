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
 * RBAViewMove.cpp
 */

#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBAViewMove.hpp"

namespace rba {

RBAViewMove::RBAViewMove(const RBAArea* const newFromArea, const RBAArea* const newToArea,
			 const RBAViewContentState* const newContentState)
  : RBAViewAction{}
{
  fromArea_ = newFromArea;
  toArea_ = newToArea;
  contentState_ = newContentState;
}

RBAViewMove::RBAViewMove(const RBAViewMove& viewMove)
  : RBAViewAction{viewMove}
{
  fromArea_ = viewMove.fromArea_;
  toArea_ = viewMove.toArea_;
  contentState_ = viewMove.contentState_;
}

bool
RBAViewMove::operator==(const RBAViewAction& viewAction)
{
  if(getViewActionType() != viewAction.getViewActionType()) {
    // False if the view action types do not match
    return false;
  }

  const RBAViewMove* const viewMove {dynamic_cast<const RBAViewMove*>(&viewAction)};
  return ((fromArea_ == viewMove->fromArea_) &&
          (toArea_ == viewMove->toArea_) &&
          (contentState_ == viewMove->contentState_));
}

const RBAArea*
RBAViewMove::getFromArea() const
{
  return fromArea_;
}

const RBAArea*
RBAViewMove::getToArea() const
{
  return toArea_;
}

const RBAViewContent*
RBAViewMove::getContent() const
{
  return contentState_->getOwner();
}

const RBAViewContentState*
RBAViewMove::getContentState() const
{
  return contentState_;
}

RBAViewActionType
RBAViewMove::getViewActionType() const
{
  return RBAViewActionType::MOVE;
}

}
