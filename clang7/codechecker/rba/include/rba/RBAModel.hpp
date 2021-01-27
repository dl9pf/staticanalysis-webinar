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
 * Model class
 */

#ifndef RBAMODEL_HPP
#define RBAMODEL_HPP

#include <string>
#include "RBAArea.hpp"
#include "RBAViewContent.hpp"
#include "RBAViewContentState.hpp"
#include "RBASize.hpp"
#include "RBAZone.hpp"
#include "RBASoundContent.hpp"
#include "RBASoundContentState.hpp"
#include "RBAScene.hpp"
#include "RBADisplay.hpp"
#include "RBAPositionContainer.hpp"
#include "RBAJsonParser.hpp"

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
 * @class RBAModel
 * Defines the arbitration rule model which is used by Arbitrator.<br>
 * The model consists of model elements such as areas, zones, contens, scenes,
 * constraint expressions, and so on.
 * Elements can be searched by name, and the list of elements for each type can be retrieved.
 */
class DLL_EXPORT RBAModel
{
public:
  RBAModel()=default;
  RBAModel(const RBAModel&)=delete;
  RBAModel(RBAModel&&)=delete;
  RBAModel& operator=(const RBAModel&)=delete;
  RBAModel& operator=(RBAModel&&)=delete;
  virtual ~RBAModel()=default;

public:
  /**
   * @brief Search for area with a name
   * @param areaName Area name
   * @return Area
   *
   * If the area name does not exist, returns nullptr.
   */
  virtual const RBAArea* findArea(const std::string& areaName) const=0;

  /**
   * @brief Search for view content with a name.
   * @param contName Content name
   * @return Content
   *
   * If the content name does not exist, returns nullptr.
   */
  virtual const RBAViewContent* findViewContent(const std::string& contName) const=0;

  /**
   * @brief Search for view content state with a name.
   * @param stateName Content state name
   * @return State of view content
   *
   * If the content state name does not exist, returns nullptr.
   */
  virtual const RBAViewContentState* findViewContentState(const std::string& stateName) const=0;

  /**
   * @brief Search for size with a name.
   * @param sizeName Name of the search size
   * @return Size
   *
   * Specify the name of the search size as follows.\n
   * In the case of the size linked to the area:
   * <area_name>/<size_name>
   * In the case of the size linked to the content:
   * <content_name>/<size_name>
   * \n
   * If the name of the search size does not exist, returns nullptr.
   */
  virtual const RBASize* findSize(const std::string& sizeName) const=0;

  /**
   * @brief Search for zone with a name.
   * @param zoneName Zone name
   * @return Zone
   *
   * If the zone name does not exist, returns nullptr.
   */
  virtual const RBAZone* findZone(const std::string& zoneName) const=0;

  /**
   * @brief Search for sound content with a name.
   * @param contName Content name
   * @return Sound content
   *
   * If the content name does not exist, returns nullptr.
   */
  virtual const RBASoundContent* findSoundContent(const std::string& contName) const=0;

  /**
   * @brief Search for sound content state with a name.
   * @param stateName Content state name
   * @return Sound content state
   *
   * If the content state name does not exist, returns nullptr.
   */
  virtual const RBASoundContentState* findSoundContentState(const std::string& stateName) const=0;

  /**
   * @brief Search for scene with a name.
   * @param sceneName Scene name
   * @return Scene
   *
   * If the scene name does not exist, returns nullptr.
   */
  virtual const RBAScene* findScene(const std::string& sceneName) const=0;

  /**
   * @brief Search for display with a name.
   * @param displayName Display name.
   * @return Display
   *
   * If the display name does not exist, returns nullptr.
   */
  virtual const RBADisplay* findDisplay(const std::string& displayName) const=0;

  /**
   * @brief Returns all the areas.
   * @return List of areas
   */
  virtual const std::list<const RBAArea*>& getAreas() const=0;

  /**
   * @brief Returns all the view contents.
   * @return List of contents
   */
  virtual const std::list<const RBAViewContent*>& getViewContents() const=0;

  /**
   * @brief Returns all the view content states.
   * @return List of view content states
   */
  virtual const std::list<const RBAViewContentState*>& getViewContentStates() const=0;

  /**
   * @brief Returns all the sizes.
   * @return List of sizes
   */
  virtual const std::list<const RBASize*>& getSizes() const=0;

  /**
   * @brief Returns all the zones.
   * @return List of zones
   */
  virtual const std::list<const RBAZone*>& getZones() const=0;

  /**
   * @brief Returns all the sound contents.
   * @return List of sound contents
   */
  virtual const std::list<const RBASoundContent*>& getSoundContents() const=0;

  /**
   * @brief Returns all the sound content states.
   * @return List of sound content states
   */
  virtual const std::list<const RBASoundContentState*>& getSoundContentStates() const=0;

  /**
   * @brief Returns all the scenes.
   * @return List of scenes
   */
  virtual const std::list<const RBAScene*>& getScenes() const=0;

  /**
   * @brief Returns all the displays.
   * @return List of displays
   */
  virtual const std::list<const RBADisplay*>& getDisplays() const=0;

  // internal {
  /**
   * @brief Returns all the position containers.
   * @return List of sets of position containers
   */
  virtual const std::list<const RBAPositionContainer*>& getPositionContainers() const=0;
 // }

};

}

#endif
