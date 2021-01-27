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
 * ViewAction Class implementation
 */

#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBAViewAction.hpp"
#include "RBAViewMove.hpp"
#include "RBAViewTransition.hpp"

namespace rba {

const RBAArea*
RBAViewAction::getArea() const
{
  return nullptr;
}

const RBAViewContent*
RBAViewAction::getFromContent() const
{
  return nullptr;
}

const RBAViewContent*
RBAViewAction::getToContent() const
{
  return nullptr;
}

const RBAViewContentState*
RBAViewAction::getFromContentState() const
{
  return nullptr;
}

const RBAViewContentState*
RBAViewAction::getToContentState() const
{
  return nullptr;
}

const RBAArea*
RBAViewAction::getFromArea() const
{
  return nullptr;
}

const RBAArea*
RBAViewAction::getToArea() const
{
  return nullptr;
}

const RBAViewContent*
RBAViewAction::getContent() const
{
  // This function is never called because the function of the derived class 
  // is always called
  return nullptr;
}

const RBAViewContentState*
RBAViewAction::getContentState() const
{
  // This function is never called because the function of the derived class 
  // is always called
  return nullptr;
}

}
