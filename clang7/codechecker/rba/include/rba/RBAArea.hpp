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
 * Area class
 */

#ifndef RBAAREA_HPP
#define RBAAREA_HPP

#include <list>
#include <string>
#include "RBAArbitrationPolicy.hpp"

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

namespace rba
{

class RBASize;
class RBAViewContent;

/**
 * @class RBAArea
 * Defines a Frame for displaying the view content.<br>
 * At run time, at most one view content is allocated to one area.
 */
class DLL_EXPORT RBAArea
{
protected:
  RBAArea()=default;
  RBAArea(const RBAArea&)=delete;
  RBAArea(RBAArea&&)=delete;
  RBAArea& operator=(const RBAArea&)=delete;
  RBAArea& operator=(RBAArea&&)=delete;
  ~RBAArea()=default;

public:
  /**
   * @brief Returns the name of the area.
   * @return Area name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the x-axis value of the base point of the area
   * @return X-axis Value of the base point
   */
  virtual std::int32_t getX() const=0;

  /**
   * @brief Returns the y-axis value of the base point of the area
   * @return Y-axis Value of the base point
   */
  virtual std::int32_t getY() const=0;

  /**
   * @brief Returns the z-order value.
   * An area with a large z-order value is displayed on the front of an area with small z-order value.
   * @return Z-order value
   */
  virtual std::int32_t getZorder() const=0;

  /**
   * @brief Returns the list of content which can be displayed on this area.
   * @return list of content
   */
  virtual const std::list<const RBAViewContent*>& getContents() const=0;

  /**
   * @brief Returns the list of size defined to this area .
   * Since multiple size can be defined, returns a list of size.
   * @return list of size
   */
  virtual const std::list<const RBASize*>& getSizes() const=0;

  /**
   * @brief Returns the arbitration policy value defined to this area.
   * @return arbitration policy value
   */
  virtual RBAArbitrationPolicy getArbitrationPolicy() const=0;
};

}

#endif
