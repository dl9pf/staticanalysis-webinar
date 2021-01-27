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
 * AbstractAllocatable class implementation
 */

#include "RBAAbstractAllocatable.hpp"

#include "RBAModelElementType.hpp"
#include "RBAContent.hpp"
#include "RBAContentSet.hpp"
#include "RBAViewContentSet.hpp"
#include "RBASoundContentSet.hpp"

namespace rba
{

RBAAbstractAllocatable::RBAAbstractAllocatable(const std::string& name)
  : RBARuleObject{name},
    contentSet_{std::make_unique<RBAContentSet>()}
{
}

const std::list<const RBAContent*>&
RBAAbstractAllocatable::getInternalContents() const
{
  return contentSet_->getLeafContent();
}

void
RBAAbstractAllocatable::addContent(const RBAContent* const content)
{
  contentSet_->addTarget(content);
}

const RBAContentSet*
RBAAbstractAllocatable::getContentSet() const
{
  return contentSet_.get();
}

}
