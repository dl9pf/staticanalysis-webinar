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
 * SoundContentSet class
 */

#include "RBASoundContentSet.hpp"
#include "RBASoundContent.hpp"
#include "RBAContent.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBASoundContentSet::RBASoundContentSet(const std::string& name)
  : RBARuleObject{name},
    RBAContentSet{name}
{
}

const std::list<const RBASoundContent*>&
RBASoundContentSet::getTargets() const
{
  return externalContents_;
}

void
RBASoundContentSet::addTarget(const RBAContent* content)
{
  RBAContentSet::addTarget(content);
  externalContents_.push_back(dynamic_cast<const RBASoundContent*>(content));
}

void
RBASoundContentSet::clear()
{
  RBAContentSet::clear();
  externalContents_.clear();
}

RBAModelElementType
RBASoundContentSet::getModelElementType() const
{
  return RBAModelElementType::SoundContentSet;
}

}
