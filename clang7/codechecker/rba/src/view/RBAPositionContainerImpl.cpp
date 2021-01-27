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
 * PositionContainerImpl class 
 */

#include "RBAPositionContainerImpl.hpp"
#include "RBAAreaImpl.hpp"

namespace rba
{

std::int32_t
RBAPositionContainerImpl::getX() const
{
  return x_;
}

void
RBAPositionContainerImpl::setX(const std::int32_t newX)
{
  x_ = newX;
}

std::int32_t
RBAPositionContainerImpl::getY() const
{
  return y_;
}

void
RBAPositionContainerImpl::setY(const std::int32_t newY)
{
  y_ = newY;
}

RBABasePoint
RBAPositionContainerImpl::getBasePoint() const
{
  return basePoint_;
}

void
RBAPositionContainerImpl::setBasePoint(const RBABasePoint newBasePoint)
{
  basePoint_ = newBasePoint;
}

const RBAArea*
RBAPositionContainerImpl::getArea() const
{
  return getAreaImpl();
}

void
RBAPositionContainerImpl::setArea(const RBAAreaImpl* const newArea)
{
  area_ = newArea;
}

const RBAAreaImpl*
RBAPositionContainerImpl::getAreaImpl() const
{
  return area_;
}

void
RBAPositionContainerImpl::addOffset(const std::string& sizeName,
				    std::int32_t offsetX, std::int32_t offsetY)
{
  sizeToOffset_[sizeName] = std::make_pair(offsetX, offsetY);
}

std::pair<std::int32_t, std::int32_t>
RBAPositionContainerImpl::getOffset(const std::string& sizeName) const
{
  std::pair<std::int32_t, std::int32_t> offset;

  auto it = sizeToOffset_.find(sizeName);
  if(it != sizeToOffset_.end()) {
    offset = it->second;
  }
  else {
    offset = std::make_pair(0, 0);
  }

  return offset;
}

}
