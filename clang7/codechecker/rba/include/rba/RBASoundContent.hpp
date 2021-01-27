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
 * Sound content class
 */

#ifndef RBASOUNDCONTENT_HPP
#define RBASOUNDCONTENT_HPP

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
#include "RBAContentLoserType.hpp"

namespace rba
{

class RBASoundContentState;
class RBAZone;
  
/**
 * @class RBASoundContent
 * Define the object of sound content.<br>
 * Sound content has plural status.
 * When sound contents connected to a zone, active status is output.
 * Object has zone definitions, that can output itself.
 * Each object can define plural zone which can output sound contents.
 */
class DLL_EXPORT RBASoundContent
{
protected:
  RBASoundContent()=default;
  RBASoundContent(const RBASoundContent&)=delete;
  RBASoundContent(RBASoundContent&&)=delete;
  RBASoundContent& operator=(const RBASoundContent&)=delete;
  RBASoundContent& operator=(RBASoundContent&&)=delete;
  ~RBASoundContent()=default;

public:
  /**
   * @brief Returns the name of the sound content.
   * @return Sound content name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the state of the sound content.
   * @return List of the sound content state
   */
  virtual const std::list<const RBASoundContentState*>& getContentStates() const=0;

  /**
   * @brief Returns the zone of the sound content.
   * @return List of the zone
   */
  virtual const std::list<const RBAZone*>& getZones() const=0;

  /**
   * @brief Returns the loser type.
   * @return Loser type
   */
  virtual RBAContentLoserType getLoserType() const=0;

public:
  /**
   * @brief Defines the default loser type.
   */
  const static RBAContentLoserType LOSER_TYPE_EDEFAULT =
    RBAContentLoserType::NEVER_GIVEUP;

};

}

#endif
