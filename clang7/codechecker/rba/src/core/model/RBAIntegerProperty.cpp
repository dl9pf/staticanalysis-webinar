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
 * Integer property class
 */

#include "RBAIntegerProperty.hpp"
#include "RBASceneImpl.hpp"

namespace rba
{

RBAIntegerProperty::RBAIntegerProperty(const RBASceneImpl* const scene,
                                       const std::string& newName,
                                       const std::int32_t newValue)
  : RBAAbstractProperty{scene, newName},
    value_{newValue}
{
}

std::int32_t
RBAIntegerProperty::getValue() const
{
  return value_;
}

#ifdef RBA_USE_LOG
const std::string
RBAIntegerProperty::getExpressionText() const
{
  return getScene()->getElementName() + "." + getElementName();
}
#endif

}
