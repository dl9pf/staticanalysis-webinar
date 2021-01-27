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
 * Arbitration result class
 */

#ifndef RBARESULT_HPP
#define RBARESULT_HPP

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <memory>
#include <list>
#include "RBAResultStatusType.hpp"
#include "RBAViewAction.hpp"
#include "RBAScene.hpp"

namespace rba
{

class RBAArea;
class RBAViewContent;
class RBAViewContentState;
class RBAScene;
class RBASize;
class RBAZone;
class RBASoundContent;
class RBASoundContentState;
// internal {
class RBADisplay;
// }

/**
 * @class RBAResult
 * Stores an arbitration result.<br>
 * The Arbitrator allocates Contents to Areas. Related
 * information of those can be acquired from RBAResult.\n
 * The arbitration result indicates which content is allocated to each 
 * area / zone.
 * Also, snapshot information and view action information (only display
 * results) indicating the difference from the last arbitration are included.
 */
class DLL_EXPORT RBAResult
{
public:
  RBAResult()=default;
  RBAResult(const RBAResult&)=delete;
  RBAResult(RBAResult&&)=delete;
  RBAResult& operator=(const RBAResult&)=delete;
  RBAResult& operator=(RBAResult&&)=delete;
  virtual ~RBAResult()=default;

public:

  // [VisibleArea/SoundingZone]

  /**
   * @brief Returns the displaying areas determined by the last arbitration.
   * @return List of visible areas.
   */
  virtual const std::list<const RBAArea*>& getVisibleAreas() const=0;

  /**
   * @brief Returns the outputting zones determined by the last arbitration.
   * @return List of sounding zones.
   */
  virtual const std::list<const RBAZone*>& getSoundingZones() const=0;

  // [Visible/Sounding ContentStates]

  /**
   * @brief Returns the view content states to be displayed determined by the last arbitration.
   * @return List of visible view content states.
   */
  virtual const std::list<const RBAViewContentState*>& getVisibleContentStates() const=0;

  /**
   * @brief Returns the sound content states to be output determined by the last arbitration.
   * @return List of sound content states to be output.
   * @details The list contains sound contents to be attenuated.
   */
  virtual const std::list<const RBASoundContentState*>& getSoundingContentStates() const=0;

  // [Active View/Sound ContentStates]

  /**
   * @brief Returns the active view content states at the last arbitration
   * result.
   * @return List of active view content states.
   * @details
   * The active view content states are those that have been requested to
   * display so far. They do not include the view content state whose request
   * has been withdrawn or canceled.
   */
  virtual const std::list<const RBAViewContentState*>& getActiveViewContentStates() const=0;

  /**
   * @brief Returns the active sound content states at the last arbitration
   * result.
   * @return List of active sound content states.
   * @details
   * The active sound content states are those that have been requested to
   * output so far.  They do not include the sound content state whose request
   * has been withdrawn or canceled.
   */
  virtual const std::list<const RBASoundContentState*>& getActiveSoundContentStates() const=0;

  // [Active Scenes]

  /**
   * @brief Returns the active scenes at the last arbitration.
   * @return List of active scenes.
   * @details
   * The active scenes are those that have been requested for ON so far.
   * They do not include scenes requested for OFF afterwards.
   */
  virtual const std::list<const RBAScene*>& getActiveScenes() const=0;

  // [InvisibleAreas/UnsoundingZone]

  /**
   * @brief Returns the invisible areas determined by the last arbitration.
   * @return List of invisible areas.
   * @details
   * Returns the areas which are not displayed out of all areas.\n
   * The list contains areas to be hidden.
   */
  virtual const std::list<const RBAArea*>& getInvisibleAreas() const=0;

  /*
   * @brief Returns the unsounding zones determined by the last arbitration.
   * @return List of unsounding zones.
   * @details
   * Returns the zones which are not output out of all zones.
   * The list contains zones to be muted.
   */
  virtual const std::list<const RBAZone*>& getUnsoundingZones() const=0;

  // [HiddenAreas/MuteZones]

  /**
   * @brief Returns the area that is hidden state and content has been
   * allocated.\n
   * The hidden state is a state in which the area must be hidden by a
   * constraint expression.
   * @return List of areas.
   * Returns the area which become to be invisible.
   * The area invisible in the previous time is not included.
   */
  virtual const std::list<const RBAArea*>& getHiddenAreas() const=0;

  /**
   * @brief Returns the zone that is muted state and content has been
   * allocated.\n
   * The muted state is a state in which the zone must be muted by a
   * constraint expression.
   * @return List of muted zones.
   *
   * Retuens the zones that is defeted and canceled sound contents.
   */
  virtual const std::list<const RBAZone*>& getMuteZones() const=0;

  // [get Attenuated]

  /**
   * @brief Returns the attenuated zones determined by the last arbitration.
   * @return List of attenuated zones.
   */
  virtual const std::list<const RBAZone*>& getAttenuatedZones() const=0;

  // [Canceled Contents]

  /**
   * @brief Returns the canceled view contents determined by the last arbitration.
   * @return List of canceled view contents.
   * @details
   * Reterns list of view contents which are canceled by Request handling on lost definition\n
   * such as Loser Type and Post Constraints.\n
   * The list does not contain contents which are withdrawn.
   */
  virtual const std::list<const RBAViewContent*>& getCanceledViewContents() const=0;

  /**
   * @brief Returns the canceled sound contents determined by the last arbitration.
   * @return List of canceled sound contents.
   * @details
   * Reterns list of sound contents which are canceled by Request handling on lost definition\n
   * such as Loser Type and Post Constraints.\n
   * The list does not contain contents which are withdrawn.
   */
  virtual const std::list<const RBASoundContent*>& getCanceledSoundContents() const=0;

  // [Standby Contents]

  /**
   * @brief Returns the stand by view contents due to defeated at the last
   * arbitration.
   * @return List of stand by view contents.
   * @details
   * Returns list of view contents which are active but not allocated to any area.
   * The list does not contains which are canceled contents or are allocated to hidden area.
   */
  virtual const std::list<const RBAViewContent*>& getStandbyViewContents() const=0;

  /**
   * @brief Returns the stand by sound contents due to defeated at the last
   * arbitration.
   * @return List of stand by sound contents.
   * @details
   * Returns list of sound contents which are active but not allocated to any area.
   * The list does not contains which are canceled contents or are allocated to muted area.
   */
  virtual const std::list<const RBASoundContent*>& getStandbySoundContents() const=0;

  // [ContentStates]

  /**
   * @brief Returns the view content state assigned to the area of the last
   * arbitration.
   * @param area Area
   * @return The view content state assign to the area.
   * @details
   * If no view content state is allocated to the area, nullptr is returnd.\n
   * If area is not defined in the Model or nullptr, nullptr is returnd.
   */
  virtual const RBAViewContentState* getContentState(const RBAArea* area) const=0;

  /**
   * @brief Returns the sound content state assigned to the zone of the last
   * arbitration.
   * @param zone Zone
   * @return The sound content state assign to the zone.
   * @details
   * If no sound content state is allocated to the zone, nullptr is returned.\n
   * If zone is not defined in the Model or nullptr, nullptr is returnd.
   */
  virtual const RBASoundContentState* getContentState(const RBAZone* zone) const=0;

  // [Areas/Zones by ConentState]

  /**
   * @brief Returns the area to which the view content state is allocated at the
   * last arbitration.
   * @param state View content state
   * @return The areas to which the view content state.
   * @details
   * If the view content state is not assigned to any area, empty list is returned.\n
   * If state is not defined in the Model or nullptr, empty list is returned.
   */
  virtual const std::list<const RBAArea*> getArea(const RBAViewContentState* state) const=0;

  /**
   * @brief Get the zone to which the sound content state is allocated of the
   * last arbitration.
   * @param state Sound content state
   * @return The zones to which the sound content state is allocated.
   * @details
   * If the sound content state is not assigned to any zone,
   * empty list is retuened.\n
   * If state is not defined in the Model or nullptr, empty list is returned.
   */
  virtual const std::list<const RBAZone*> getZone(const RBASoundContentState* state) const=0;

  // [Areas/Zones by Content]

  /**
   * @brief Returns the area to which the view content is allocated of the
   * last arbitration.
   * @param content View content
   * @return The areas to which the view content is allocated.
   * @details
   * If the view content is not assigned to any area, empty list is returned.\n
   * If content is not defined in the Model or nullptr, empty list is returned.\n
   * This API is the same as getArea(RBAViewContentState*) \n
   * except for the type of argument.
   */
  virtual const std::list<const RBAArea*> getArea(const RBAViewContent* content)const=0;

  /**
   * @brief Returns the zone to which the sound content state is allocated of the
   * last arbitration.
   * @param content Sound content
   * @return The zones to which the sound content is allocated.
   * @details
   * If the sound content is not assigned to any area, nullptr is returned.\n
   * If content is not defined in the Model or nullptr, empty list is returned.\n
   * This API is the same as getZone(RBASoundContentState*) \n
   * except for the type of argument.
   */
  virtual const std::list<const RBAZone*> getZone(const RBASoundContent* content) const=0;

  // [Size]

  /**
   * @brief Returns the size of the area determined in the last arbitration.
   * @param area Area
   * @return The size of the area.
   * @details
   * Area may have multiple sizes and its size will vary by the allocated content.\n
   * This API returns the size which are matched with allocated content.\n
   * If no content is allocated to the area, returns nullptr.\n
   * If area is not defined in the Model or nullptr, returns nullptr.
   */
  virtual const RBASize* getSize(const RBAArea* area) const=0;

  // [Active check Scene]

  /**
   * @brief Returns true if the scene is ON at the last arbitration.
   * @param scene Reference scene to be checked.
   * @return true: the scene is ON
   * @return false: the scene is OFF
   * @details
   * If scene is not defined in the Model or nullptr, returns false.
   */
  virtual bool isActive(const RBAScene* scene) const=0;

  // [Active check ContentState]

  /**
   * @brief Returns true if the view content is active.
   * @param state Reference view content to be checked.
   * @return true: Active
   * @return false: Not active
   * @details
   * If content is not defined in the Model or nullptr, returns false.
   */
  virtual bool isActive(const RBAViewContent* content) const=0;

  /**
   * @brief Returns true if the sound content is active.
   * @param state Reference sound content to be checked.
   * @return true: Active
   * @return false: Not active
   * @details
   * If content is not defined in the Model or nullptr, returns false.
   */
  virtual bool isActive(const RBASoundContent* content) const=0;

  // [Visible/Sounding Area/Zonecheck]

  /**
   * @brief Returns true if the area is visible of the last arbitration.
   * @param area Reference area to be checked.
   * @return true: Visible
   * @return false: Not visible
   * @details
   * Returns false if the area is hidden.\n
   * If area is not defined in the Model or nullptr, returns false.
   */
  virtual bool isVisible(const RBAArea* area) const=0;

  /**
   * @brief Returns true if the zone is sounding of the last arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Sounding
   * @return false: Not sounding
   * @details
   * Returns false if the zone is muted.\n
   * If zone is not defined in the Model or nullptr, returns false.
   */
  virtual bool isSounding(const RBAZone* zone) const=0;

  // [Visible/Sounding ContentState check]

  /**
   * @brief Returns true if the view content state is visible
   * of the last arbitration.
   * @param state Reference view content state to be checked.
   * @return true: state is allocated to visible area.
   * @return false: state is not allocated to visible area.
   * @details
   * If all of the areas to which the content is allocated are hidden, returns false\n
   * If state is not defined in the Model or nullptr, returns false.
   */
  virtual bool isVisible(const RBAViewContentState* state) const=0;

  /**
   * @brief Returns true if the sound content state is sounding
   * of the last arbitration.
   * @param state Reference sound content state to be check.
   * @return true: state is allocated to outputting zone.
   * @return false: state is not allocated to outputting zone.
   * @details
   * If all of the zones to which the content is allocated are muted, returns false\n
   * If state is not defined in the Model or nullptr, returns false.
   */
  virtual bool isSounding(const RBASoundContentState* state) const=0;

  // [View/Sound ContentState]

  /**
   * @brief Returns the view content state allocated to the area
   * of the last arbitration.
   * @param area Area
   * @return The view content state allocated to the area.
   * @details
   *  Even if the area is hidden, Returns the allocated content state.\n
   * If no visible view content state is allocated the area, nullptr is returnd.\n
   * If area is not defined in the Model or nullptr, returns nullptr.
   */
  virtual const RBAViewContentState* getViewContentState(const RBAArea* area) const=0;

  /**
   * @brief Returns the sounding sound content state assigned to the zone
   * of the last arbitration.
   * @param zone Zone
   * @return The sounding sound content state assign to the zone.
   * @details
   *  Even if the zone is muted, Returns the allocated content state.\n
   * If no sounding sound content state is allocated the area,
   * nullptr is returnd.\n
   * If zone is not defined in the Model or nullptr, returns nullptr.
   */
  virtual const RBASoundContentState* getSoundContentState(const RBAZone* zone) const=0;

  // [Hidden/Mute check]

  /**
   * @brief Returns true if the area is hidden state of the last arbitration.\n
   * The hidden state is a state in which the area must be hidden by a
   * constraint expression.\n
   * In the hidden state, it returns true even if the content is not assigned.
   * @param area Reference area to be checked.
   * @return true: Hidden
   * @return false: Not hidden
   * @details
   * If area is not defined in the Model or nullptr, returns nullptr.
   */
  virtual bool isHidden(const RBAArea* area) const=0;

  /**
   * @brief Returns true if the zone is muted state of the last arbitration.\n
   * The muted state is a state in which the zone must be muted by a
   * constraint expression.\n
   * In the muted state, it returns true even if the content is not assigned.
   * @param zone Reference zone to be checked.
   * @return true: Muted
   * @return false: Not muted
   * @details
   * If zone is not defined in the Model or nullptr, returns nullptr.
   */
  virtual bool isMute(const RBAZone* zone) const=0;

  // [Check Attenuated]

  /**
   * @brief Returns true if the zone is attenuated
   * of the last arbitration.
   * @param zone Reference zone to be check.
   * @return true: Attenuated
   * @return false: Not attenuated
   * @details
   * If zone is not defined in the Model or nullptr, returns nullptr.
   */
  virtual bool isAttenuated(const RBAZone* zone) const=0;

  // [Cancel check]

  /**
   * @brief Returns true if the view content state is canceled
   * at the last arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled or Not request view content state
   * @details
   * If state is not active, returns false.\n
   * If state is not defined in the Model or nullptr, returns false.
   */
  virtual bool isCancel(const RBAViewContentState* state) const=0;

  /**
   * @brief Returns true if the sound content state is canceled
   * at the last arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled
   * @details
   * If state is not active, returns false.\n
   * If state is not defined in the Model or nullptr, returns false.
   */
  virtual bool isCancel(const RBASoundContentState* state) const=0;

  // common

  /**
   * @brief Returns information of view status changes
   * (the view actions) of the last arbitration.
   * @return List of view actions.
   * @details
   * ViewAction is an information of differences \n
   * between the last arbitration result and its previous result.\
   * There is no difference between hidden and not displayed for visible status.\n
   */
  virtual const std::list<const RBAViewAction*>& getViewActions() const=0;

  /**
   * @brief Returns the result status type of the last arbitration.
   * @return SUCCESS: Success
   * @return UNKNOWN_CONTENT_STATE: Failed (The reuqest is unknown)
   * @return CANCEL_ERROR: Cancel arbitrration error
   * @endcond
   */
  virtual RBAResultStatusType getStatusType() const=0;

  /**
   * @brief Returns satisfied status of all online constraints.
   * @return true:All online constraints check result is OK, and arbitration finished.
   * @return false:All online constraints check result is NG, and arbitration finished.
   */
  virtual bool satisfiesConstraints() const=0;

  /**
   * @brief Returns the property value of scene.
   * @return Property value
   * @details
   * If the scene or propertyName is not defined in the Model, returns -99.\n
   * @endcond
   */
  virtual std::int32_t getSceneProperty(const RBAScene* scene, const std::string& propertyName) const=0;

  // internal {
  /**
   * @brief Returns the displaying areas of the previous arbitration.
   * @return List of visible areas.
   */
  virtual const std::list<const RBAArea*>& getPreVisibleAreas() const=0;

  /**
   * @brief Returns the outputting sounding zones of the previous arbitration.
   * @return List of sounding zones.
   */
  virtual const std::list<const RBAZone*>& getPreSoundingZones() const=0;

  /**
   * @brief Returns the view content states to be displayed of the previous arbitration.
   * @return List of visible view content states.
   */
  virtual const std::list<const RBAViewContentState*>& getPreVisibleContentStates() const=0;

  /**
   * @brief Returns the sound content states to be outputted of the previous arbitration.
   * @return List of sounding sound content states.
   * @details The list contains attenuated content states.
   */
  virtual const std::list<const RBASoundContentState*>& getPreSoundingContentStates() const=0;

  /**
   * @brief Returns the active view content states of the previous arbitration
   * result.
   * @return List of active view content states.
   * @details
   * The active view content states are those that have been requested to
   * display so far.  They do not include the view content state whose request
   * has been withdrawn or canceled.
   */
  virtual const std::list<const RBAViewContentState*>& getPreActiveViewContentStates() const=0;

  /**
   * @brief Returns the active sound content states of the previous arbitration
   * result.
   * @return List of active sound content states.
   * @details
   * The active sound content states are those that have been requested to
   * output so far.  They do not include the sound content state whose request
   * has been withdrawn or canceled.
   */
  virtual const std::list<const RBASoundContentState*>& getPreActiveSoundContentStates() const=0;

  /**
   * @brief Returns the active scenes of the previous arbitration.
   * @return List of active scenes.
   * @details
   * The active scenes are those that have been requested for ON so far.
   * They do not include scenes requested for OFF afterwards.
   */
  virtual const std::list<const RBAScene*>& getPreActiveScenes() const=0;

  /**
   * @brief Returns the invisible areas of the previous arbitration.
   * @return List of invisible areas.
   * @details
   * Returns the areas which are not displayed out of all areas.
   */
  virtual const std::list<const RBAArea*>& getPreInvisibleAreas() const=0;

  /*
   * @brief Returns the unsounding zones of the previous arbitration.
   * @return List of unsounding zones.
   * @details
   * Returns the zones which are not outputted out of all zones.
   */
  virtual const std::list<const RBAZone*>& getPreUnsoundingZones() const=0;

  /**
   * @brief Returns the areas which have become invisible at the previous arbitration.
   * @return List of areas.
   *
   * Returns the area which become to be invisible.
   */
  virtual const std::list<const RBAArea*>& getPreHiddenAreas() const=0;

  /**
   * @brief Get the muted zones of the previous arbitration.
   * @return List of muted zones.
   *
   * Retuens the zones that is defeted and canceled sound contents.
   */
  virtual const std::list<const RBAZone*>& getPreMuteZones() const=0;

  /**
   * @brief Returns the attenuated zones of the previous arbitration.
   * @return List of attenuated zones.
   */
  virtual const std::list<const RBAZone*>& getPreAttenuatedZones() const=0;

  /**
   * @brief Returns the canceled view contents of the previous arbitration.
   * @return List of canceled view contents.
   */
  virtual const std::list<const RBAViewContent*>& getPreCanceledViewContents() const=0;

  /**
   * @brief Returns the canceled sound contents of the previous arbitration.
   * @return List of canceled sound contents.
   */
  virtual const std::list<const RBASoundContent*>& getPreCanceledSoundContents() const=0;

  /**
   * @brief Returns the stand by view contents due to defeated at the previous
   * arbitration.
   * @return List of stand by view contents.
   */
  virtual const std::list<const RBAViewContent*>& getPreStandbyViewContents() const=0;

  /**
   * @brief Returns the stand by sound contents due to defeated at previous
   * arbitration.
   * @return List of stand by sound contents.
   */
  virtual const std::list<const RBASoundContent*>& getPreStandbySoundContents() const=0;

  /**
   * @brief Returns the view content state assigned to the area of the previous
   * arbitration.
   * @param area Area
   * @return The view content state assign to the area.
   *
   * If no view content state is allocated to the area, nullptr is returnd.
   */
  virtual const RBAViewContentState* getPreContentState(const RBAArea* area) const=0;

  /**
   * @brief Returns the sound content state assigned to the zone of the previous
   * arbitration.
   * @param zone Zone
   * @return The sound content state assign to the zone.
   *
   * If no sound content state is allocated to the zone, nullptr is returned.
   */
  virtual const RBASoundContentState* getPreContentState(const RBAZone* zone) const=0;

  /**
   * @brief Returns the area to which the view content state is allocated of the
   * previous arbitration.
   * @param state View content state
   * @return The areas to which the view content state.
   *
   * If the view content state is not assigned to any area, nullptr is returned.
   */
  virtual const std::list<const RBAArea*> getPreArea(const RBAViewContentState* state) const=0;

  /**
   * @brief Get the zone to which the sound content state is allocated of the
   * previous arbitration.
   * @param state Sound content state
   * @return The zones to which the sound content state is allocated.
   *
   * If the sound content state is not assigned to any zone,
   * null ptr is retuened.
   */
  virtual const std::list<const RBAZone*> getPreZone(const RBASoundContentState* state) const=0;

  /**
   * @brief Returns the area to which the view content is allocated of the
   * previous arbitration.
   * @param content View content
   * @return The areas to which the view content is allocated.
   *
   * If the view content is not assigned to any area, nullptr is returned.
   */
  virtual const std::list<const RBAArea*> getPreArea(const RBAViewContent* content) const=0;

  /**
   * @brief Returns the zone to which the sound content state is allocated of the
   * previous arbitration.
   * @param content Sound content
   * @return The zones to which the sound content is allocated.
   *
   * If the sound content is not assigned to any area, nullptr is returned.
   */
  virtual const std::list<const RBAZone*> getPreZone(const RBASoundContent* content) const=0;

  /**
   * @brief Returns the size of the area
   * determined in the previous arbitration.
   * @param area Area
   * @return The size of the area.
   */
  virtual const RBASize* getPreSize(const RBAArea* area) const=0;

  /**
   * @brief Returns true if the scene is active
   * of the previous arbitration.
   * @param scene Reference scene to be checked.
   * @return true: Active
   * @return false: Not active
   *
   * The active scene is the scene requested  to ON.
   */
  virtual bool isPreActive(const RBAScene* scene) const=0;

  /**
   * @brief Returns true if the view content is active
   * of the previous arbitration.
   * @param state Reference view content to be checked.
   * @return true: Active
   * @return false: Not active
   *
   * The active view content is the content requested to be displayed.
   */
  virtual bool isPreActive(const RBAViewContent* content) const=0;

  /**
   * @brief Returns true if the sound content is active
   * of the previous arbitration.
   * @param state Reference sound content to be checked.
   * @return true: Active
   * @return false: Not active
   *
   * The active sound content is the content requested to be outputted.
   */
  virtual bool isPreActive(const RBASoundContent* content) const=0;

  /**
   * @brief Returns true if the area is visible
   * of the previous arbitration.
   * @param area Reference area to be checked.
   * @return true: Visible
   * @return false: Not visible
   */
  virtual bool isPreVisible(const RBAArea* area) const=0;

  /**
   * @brief Returns true if the zone is sounding
   * of the previous arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Sounding
   * @return false: Not sounding
   */
  virtual bool isPreSounding(const RBAZone* zone) const=0;

  /**
   * @brief Returns true if the view content state is visible
   * of the previous arbitration.
   * @param state Reference view content state to be checked.
   * @return true: state is allocated to visible area.
   * @return false: state is not allocated to visible area.
   */
  virtual bool isPreVisible(const RBAViewContentState* state) const=0;

  /**
   * @brief Returns true if the sound content state is sounding
   * of the previous arbitration.
   * @param state Reference sound content state to check.
   * @return true: state is allocated to outputting zone.
   * @return false: state is not allocated to outputting zone.
   */
  virtual bool isPreSounding(const RBASoundContentState* state) const=0;

  /**
   * @brief Returns the sounding sound content state assigned to the zone
   * of the previous arbitration.
   * @param zone Zone
   * @return The sounding sound content state assign to the zone.
   *
   *  When a zone is muted, Returns the content state.
   * If no sounding sound content state is allocated the area,
   * nullptr is returnd.
   */
  virtual const RBASoundContentState* getPreSoundContentState(const RBAZone* zone) const=0;

  /**
   * @brief Returns true if the area is hidden
   * of the previous arbitration.
   * @param area Reference area to be checked.
   * @return true: Hidden
   * @return false: Not hidden
   */
  virtual bool isPreHidden(const RBAArea* area) const=0;

  /**
   * @brief Returns true if the zone is muted of the previous arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Muted
   * @return false: Not muted
   */
  virtual bool isPreMute(const RBAZone* zone) const=0;

  /**
   * @brief Returns true if the zone is attenuated
   * of the previous arbitration.
   * @param zone Reference zone to be checked.
   * @return true: Attenuated
   * @return false: Not attenuated
   */
  virtual bool isPreAttenuated(const RBAZone* zone) const=0;

  /**
   * @brief Returns true if the view content state is canceled
   * of the previous arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled or Not request view content state
   */
  virtual bool isPreCancel(const RBAViewContentState* state) const=0;

  /**
   * @brief Returns true if the sound content state is canceled
   * of the previous arbitration.
   * @param state Reference view content state to be checked.
   * @return true: Canceled
   * @return false: Not canceled
   */
  virtual bool isPreCancel(const RBASoundContentState* state) const=0;

  /**
   * @brief Returns the log of the last arbitration.
   * @return Log string
   */
  virtual std::string getLog() const=0;

  /**
   * @brief Returns displaying status
   * @param display to be checked display
   * @return true: something is displayed
   * @return false: nothing is displayed
   */
  virtual bool hasDisplayingArea(const RBADisplay* display) const=0;
  // }

};

}

#endif
