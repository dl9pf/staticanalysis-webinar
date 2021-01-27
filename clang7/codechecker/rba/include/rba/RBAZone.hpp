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
 * Zone class
 */

#ifndef RBAZONE_HPP
#define RBAZONE_HPP

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <list>
#include <string>
#include "RBAArbitrationPolicy.hpp"

namespace rba
{

class RBASoundContent;

/**
 * @class RBAZone
 * Defines a Frame for outputting sound content.<br>
 * At run time, at most one sound content is allocated to one zone.
 * This class has arbitration policy definitions, because it is executed for each zone.
 */
class DLL_EXPORT RBAZone
{
protected:
  RBAZone()=default;
  RBAZone(const RBAZone&)=delete;
  RBAZone(RBAZone&&)=delete;
  RBAZone& operator=(const RBAZone&)=delete;
  RBAZone& operator=(RBAZone&&)=delete;
  ~RBAZone()=default;

public:
  /**
   * @brief Returns the name of the zone.
   * @return Zone name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the priority.
   * @return Priority value
   */
  virtual std::int32_t getPriority() const=0;

  /**
   * @brief Returns the list of content which can be output in this zone.
   * @return List of content
   */
  virtual const std::list<const RBASoundContent*>& getContents() const=0;

  /**
   * @brief Returns the arbitration policy value defined to this zone.
   * @return arbitration policy value
   */
  virtual RBAArbitrationPolicy getArbitrationPolicy() const=0;
};

}

#endif
