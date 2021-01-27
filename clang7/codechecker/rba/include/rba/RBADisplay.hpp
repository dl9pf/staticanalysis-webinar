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
 * Display class
 */

#ifndef RBADISPLAY_HPP
#define RBADISPLAY_HPP

#include <list>
#include <string>

namespace rba {

class RBAArea;
class RBASize;

/**
 * @class RBADisplay
 * Defines a screen layout of the display.<br>
 * You can define multiple displays for Multi-Display products.
 * Display defines a set of areas which are laid out on it.
 */
class RBADisplay
{
protected:
  RBADisplay()=default;
  RBADisplay(const RBADisplay&)=delete;
  RBADisplay(RBADisplay&&)=delete;
  RBADisplay& operator=(const RBADisplay&)=delete;
  RBADisplay& operator=(RBADisplay&&)=delete;
  ~RBADisplay()=default;

public:
  /**
   * @brief Returns the name of display
   * @return Display name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the size of display
   * @return Size
   */
  virtual const RBASize* getSize() const=0;

  /**
   * @brief Returns areas which are allocated to the display
   * @return List of area
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

};

}

#endif
