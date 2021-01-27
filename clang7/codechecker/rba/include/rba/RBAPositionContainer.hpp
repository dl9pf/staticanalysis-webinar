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
 * Position container class
 */

#ifndef RBAPOSITIONCONTAINER_HPP
#define RBAPOSITIONCONTAINER_HPP

#include <cstdint>
#include "RBABasePoint.hpp"

namespace rba
{

class RBAArea;

class RBAPositionContainer
{
protected:
  RBAPositionContainer()=default;
  RBAPositionContainer(const RBAPositionContainer&)=delete;
  RBAPositionContainer(RBAPositionContainer&&)=delete;
  RBAPositionContainer& operator=(const RBAPositionContainer&)=delete;
  RBAPositionContainer& operator=(RBAPositionContainer&&)=delete;
  ~RBAPositionContainer()=default;

public:
  /**
   * @brief Get X coordinate
   * @return X coordinate
   */
  virtual std::int32_t getX() const=0;

  /**
   * @brief Get Y coordinate
   * @return Y coordinate
   */
  virtual std::int32_t getY() const=0;

  /**
   * @brief Get base point
   * @return Base point
   */
  virtual RBABasePoint getBasePoint() const=0;

  /**
   * @brief Get assigned area
   * @return assigned area
   */
  virtual const RBAArea* getArea() const=0;

public:
  /**
   * @brief default X coordinate
   */
  const static std::int32_t X_EDEFAULT=0;

  /**
   * @brief default Y coordinate
   */
  const static std::int32_t Y_EDEFAULT=0;

  /**
   * @brief default base point
   */
  const static RBABasePoint BASE_POINT_EDEFAULT=RBABasePoint::LEFT_TOP;

};

}

#endif
