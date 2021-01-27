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
 * PositionContainerImpl class header
 */

#ifndef RBAPOSITIONCONTAINERIMPL_HPP
#define RBAPOSITIONCONTAINERIMPL_HPP

#include <string>
#include <cstdint>
#include <unordered_map>
#include "RBAPositionContainer.hpp"
#include "RBAModelElement.hpp"

namespace rba
{

class RBAAreaImpl;

class RBAPositionContainerImpl : public RBAPositionContainer,
                                 public RBAModelElement
{
public:
  RBAPositionContainerImpl()=default;
  RBAPositionContainerImpl(const RBAPositionContainerImpl&)=delete;
  RBAPositionContainerImpl(const RBAPositionContainerImpl&&)=delete;
  RBAPositionContainerImpl& operator=(const RBAPositionContainerImpl&)=delete;
  RBAPositionContainerImpl& operator=(const RBAPositionContainerImpl&&)=delete;
  virtual ~RBAPositionContainerImpl()=default;

public:
  std::int32_t getX() const override;
  std::int32_t getY() const override;
  RBABasePoint getBasePoint() const override;
  const RBAArea* getArea() const override;
  void setX(const std::int32_t newX);
  void setY(const std::int32_t newY);
  void setBasePoint(const RBABasePoint newBasePoint);
  void setArea(const RBAAreaImpl* const newArea);
  const RBAAreaImpl* getAreaImpl() const;
  void addOffset(const std::string& sizeName,
		 std::int32_t offsetX, std::int32_t offsetY);
  std::pair<std::int32_t, std::int32_t> getOffset(const std::string& sizeName) const;

private:
  std::int32_t x_ {X_EDEFAULT};
  std::int32_t y_ {Y_EDEFAULT};
  RBABasePoint basePoint_ {BASE_POINT_EDEFAULT};
  const RBAAreaImpl* area_{nullptr};
  std::unordered_map<std::string, std::pair<std::int32_t, std::int32_t>> sizeToOffset_;

};

}

#endif
