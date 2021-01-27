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
 * Integer value class definition file
 */

#include "RBAIntegerValue.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"

namespace rba
{

void
RBAIntegerValue::setValue(const std::int32_t value)
{
  value_ = value;
}

std::int32_t
RBAIntegerValue::getValue() const
{
  return value_;
}

RBAModelElementType
RBAIntegerValue::getModelElementType() const
{
  return RBAModelElementType::IntegerValue;
}

std::int32_t
RBAIntegerValue::getValueCore(RBAConstraintInfo* info, RBAArbitratorImpl * arb) const
{
  return getValue();
}

#ifdef RBA_USE_LOG
const std::string
RBAIntegerValue::getExpressionText() const
{
  return std::to_string(value_);
}

const std::string
RBAIntegerValue::getCoverageExpressionText() const
{
  return getExpressionText();
}

void
RBAIntegerValue::createHierarchy()
{
  // No opration
  // because there is no hierarchy below this expression
}

RBAExpressionType
RBAIntegerValue::getUnderlyingType() const
{
  return RBAExpressionType::VALUE;
}
#endif

}
