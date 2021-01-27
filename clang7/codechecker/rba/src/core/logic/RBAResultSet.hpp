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
 * ResultSet (set arbitration result) class header
 */

#ifndef RBARESULTSET_HPP
#define RBARESULTSET_HPP

#include <cstdint>
#include <list>
#include <memory>
#include <set>
#include <unordered_map>
#include <mutex>

#include "RBAContentStatusType.hpp"
#include "RBAContentStatus.hpp"

namespace rba
{

class RBADisplay;
class RBASize;
class RBAAllocatable;
class RBAArea;
class RBAZone;
class RBAContent;
class RBAViewContent;
class RBASoundContent;
class RBAContentState;
class RBAViewContentState;
class RBASoundContentState;
class RBAScene;
class RBASceneImpl;
class RBAAbstractProperty;
class RBAEventProcessing;
class RBAConstraint;

class RBAResultSet
{
public:
  RBAResultSet()=default;
  RBAResultSet(const RBAResultSet& resultSet);
  RBAResultSet(const RBAResultSet&&)=delete;
  RBAResultSet& operator=(const RBAResultSet&)=delete;
  RBAResultSet& operator=(const RBAResultSet&&)=delete;
  virtual ~RBAResultSet()=default;

public:
  // Impl [get VisibleArea/SoundingZone]
  const std::set<const RBAAllocatable*>& getOutputtingAllocatables() const;
  const std::list<const RBAArea*>& getVisibleAreas() const;
  const std::list<const RBAZone*>& getSoundingZones() const;
  
  // Impl [get Visible/Sounding ContentStates]
  const std::list<const RBAViewContentState*>& getVisibleContentStates() const;
  const std::list<const RBASoundContentState*>& getSoundingContentStates() const;

  // Impl [get Active View/Sound ContentStates]
  const std::set<const RBAContentState*>& getActiveContentStates() const;
  const std::list<const RBAViewContentState*>& getActiveViewContentStates() const;
  const std::list<const RBASoundContentState*>& getActiveSoundContentStates() const;
 
  // Impl [get Active Scenes]
  const std::list<const RBAScene*>& getActiveScenes() const;

  // Impl [get InvisibleAreas/UnsoundingZone]
  const std::list<const RBAArea*>& getInvisibleAreas() const;
  const std::list<const RBAZone*>& getUnsoundingZones() const;

  // Impl [get HiddenAreas/MuteZones]
  const std::list<const RBAArea*>& getHiddenAreas() const;
  const std::list<const RBAZone*>& getMuteZones() const;

  // Impl [get Attenuated]
  const std::list<const RBAZone*>& getAttenuatedZones() const;

  // Impl [get Canceled Contents]
  const std::list<const RBAViewContent*>& getCanceledViewContents() const;
  const std::list<const RBASoundContent*>& getCanceledSoundContents() const;

  // Impl [get Standby Contents]
  const std::list<const RBAViewContent*>& getStandbyViewContents() const;
  const std::list<const RBASoundContent*>& getStandbySoundContents() const;

  // Impl [get ContentStates]
  const RBAContentState* getContentState(const RBAAllocatable* const alloc) const;
  const RBAContentState* getDirectContentState(const RBAAllocatable* const alloc) const;

  // Impl [get Areas/Zones by ConentState]
  void getAlloc(const RBAContentState* const state,
	              std::list<const RBAAllocatable*>& allocList) const;
  void getArea(const RBAViewContentState* const state,
	             std::list<const RBAArea*>& areaList) const;
  void getZone(const RBASoundContentState* const state,
	             std::list<const RBAZone*>& zoneList) const;

  // Impl [get Areas/Zones by Content]
  void getArea(const RBAViewContent* const content,
	             std::list<const RBAArea*>& areaList) const;
  void getZone(const RBASoundContent* const content,
	             std::list<const RBAZone*>& zoneList) const;

  // Impl [get Size]
  const RBASize* getSize(const RBAArea* const area) const;

  // Impl [check Active Scene/Content/ContentState]
  bool isActive(const RBAScene* const scene) const;
  bool isActive(const RBAContent* const content) const;
  bool isActive(const RBAContentState* const state) const;
  const RBAContentState* getReqestState(const RBAContent* const content) const;
 
  // Impl [check Outputting Allocatable/ContentState]
  bool isOutputting(const RBAAllocatable* const alloc) const;
  bool isOutputting(const RBAContentState* const state) const;

  // Impl [check Hidden]
  bool isHidden(const RBAAllocatable* const alloc) const;

  // Impl [check Attenuated Zone]
  bool isAttenuated(const RBAZone* const zone) const;

  // Impl [check Cancel ContentState]
  bool isCancel(const RBAContentState* const state) const;

  // Impl [check Aleady OutPutting]
  bool isAlreadyOutputting(const RBAContentState* const state) const;

  // Impl [set Active Scene/ContentState]
  void setActive(const RBAScene* const scene, const bool newActive);
  void setActive(const RBAContentState* const state, const bool newActive);

  // [cancel ContentState]
  void cancelContentState(const RBAContentState* const state);

  // Impl [set Cancel ContentState]
  void setCancel(const RBAContentState* const state, const bool checked);

  // Impl [set ContentState]
  void setContentState(const RBAAllocatable* const alloc, const RBAContentState* const state);

  // Impl [add Outputting ContentState]
  void addOutputtingContentState(const RBAContentState* const state);

  // Impl [add Standby Content]
  void addStandbyContent(const RBAContent* const content);

  // [activeView]
  void copyActives(const std::unique_ptr<RBAResultSet>& resultSet);
  void updateActiveContentStates();

  // [Property]
  void copyProperties(const std::unique_ptr<RBAResultSet>& resultSet);
  void setSceneProperty(const RBAScene* const scene,
                        const std::string& propertyName,
			                  const std::int32_t value);
  void setSceneProperty(const RBAAbstractProperty* const property,
			                  const std::int32_t value);
  std::int32_t getSceneProperty(const RBAAbstractProperty* const property) const;

  // [EventProcessing]
  void setContentOfEventProcessing(const RBAEventProcessing* const eventProcessing,
                                   const RBAContent* const content);
  const RBAContent* getContentOfEventProcessing(const RBAEventProcessing* const eventProcessing) const;

  // [DisplayContents]
  bool hasDisplayingArea(const RBADisplay* const display) const;

  // common
  bool isLater(const RBAContent* const target, const RBAContent* const comparisonTarget) const;
  std::set<const RBASceneImpl*>& getDifferentConditionScenes(const RBAResultSet& target);
  void updateRequestStatus(const RBAContent* const content, const bool isOnRequest);
  void setStatusType(const RBAContent* const content, const RBAContentStatusType type);
  RBAContentStatusType getStatusType(const RBAContent* const content) const;
  bool isOutput(const RBAContent* const content) const;
  bool isStandby(const RBAContent* const content) const;
  bool hasBeenCanceled(const RBAContent* const content) const;
  bool hasBeenDisplayed(const RBAContent* const content) const;
  std::unordered_map<const RBAContent*, RBAContentStatus>* getStatus() const;
#ifdef RBA_USE_LOG
  void addFailedConstraint(const RBAConstraint* constraint);
  const std::list<const RBAConstraint*>& getFailedConstraints();
#endif

private:
  const std::unordered_map<const RBAAbstractProperty*, std::int32_t>& getScenePropertyMap() const;
  void setOrder(const RBAContentState* const state, const std::int32_t newOrder) const;

  std::set<const RBAAllocatable*> outputtingAllocs_;
  std::set<const RBAAllocatable*> hiddenAllocs_;
  std::set<const RBAContentState*> activeContentStates_;
  std::set<const RBAContentState*> canceledContentStates_;
  std::unordered_map<const RBAAllocatable*, const RBAContentState*> allocToContentState_;

  // The lists for getList type acquisition function
  std::list<const RBAArea*> visibleAreas_;
  std::list<const RBAZone*> soundingZones_;
  std::list<const RBAArea*> invisibleAreas_;
  std::list<const RBAZone*> unsoundingZones_;
  std::list<const RBAArea*> hiddenAreas_;
  std::list<const RBAZone*> muteZones_;
  std::list<const RBAZone*> attenuatedZones_;
  std::list<const RBAViewContent*> canceledViewContents_;
  std::list<const RBASoundContent*> canceledSoundContents_;
  std::list<const RBAViewContent*> standbyViewContents_;
  std::list<const RBASoundContent*> standbySoundContents_;
  std::list<const RBAViewContentState*> visibleContentStates_;
  std::list<const RBASoundContentState*> soundingContentStates_;
  std::list<const RBAViewContentState*> activeViewContentStates_;
  std::list<const RBASoundContentState*> activeSoundContentStates_;

  // common
  std::int32_t requestOrderView_ {1};
  std::int32_t requestOrderSound_ {1};
  std::list<const RBAScene*> activeScenes_;
  std::unordered_map<const RBAAbstractProperty*, std::int32_t> propertyMap_;
  std::unordered_map<const RBAEventProcessing*, const RBAContent*> event_content_;
  mutable std::unordered_map<const RBAContent*, RBAContentStatus> contentToStatus_;
  std::set<const RBASceneImpl*> differentConditionScenes_;

  mutable std::unordered_map<const RBAContent*, const RBAContentState*> requestContentStateMap_;

  mutable std::mutex mutex_;
#ifdef RBA_USE_LOG
  std::list<const RBAConstraint*> failedConstraints_;
#endif

};

}
#endif
