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
 * ViewContentSet class
 */

#include "RBAViewContentSet.hpp"
#include "RBAViewContent.hpp"
#include "RBAContent.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAViewContentSet::RBAViewContentSet(const std::string& name)
  : RBARuleObject{name},
    RBAContentSet{name}
{
}

const std::list<const RBAViewContent*>&
RBAViewContentSet::getTargets() const
{
  return externalContents_;
}

void
RBAViewContentSet::addTarget(const RBAContent* content)
{
  RBAContentSet::addTarget(content);
  externalContents_.push_back(dynamic_cast<const RBAViewContent*>(content));
}

void
RBAViewContentSet::clear()
{
  RBAContentSet::clear();
  externalContents_.clear();
}

RBAModelElementType
RBAViewContentSet::getModelElementType() const
{
  return RBAModelElementType::ViewContentSet;
}

}
