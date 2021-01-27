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
 * Scene class
 */

#ifndef RBASCENE_HPP
#define RBASCENE_HPP

#include <cstdint>
#include <list>
#include <string>

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

/**
 * @class RBAScene
 * Express the state(Including system state) at that time comprehensively.<br>
 * Used scene for switch area/zone and view/sound content state.
 * And plural RBA model(project) can share arbitration result by definitions global scene.
 */
class RBAScene
{
protected:
  RBAScene()=default;
  RBAScene(const RBAScene&)=delete;
  RBAScene(RBAScene&&)=delete;
  RBAScene& operator=(const RBAScene&)=delete;
  RBAScene& operator=(RBAScene&&)=delete;

public:
  virtual ~RBAScene()=default;

public:
  /**
   * @brief Returns the scene name
   * @return Scene name
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the global scene status.
   * @return global scene status.
   */
  virtual bool isGlobal() const=0;

  /**
   * @brief Returns List of the scene property name.
   * @return List of the scene property name
   */
  virtual const std::list<std::string>& getPropertyNames() const=0;

  /**
   * @brief Returns Default value of the scene property.
   * @param propertyName Scene property name
   * @return Default value of the scene property
   */
  virtual std::int32_t getPropertyValue(const std::string& propertyName) const=0;

};

}

#endif
