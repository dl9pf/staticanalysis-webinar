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
 * ResultSet (set arbitration result) class
 */

#include <algorithm>
#include <unordered_map>
#include "RBAResultSet.hpp"

#include "RBAContentStatusType.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAViewContentState.hpp"
#include "RBASizeImpl.hpp"
#include "RBAZone.hpp"
#include "RBAZoneImpl.hpp"
#include "RBASoundContent.hpp"
#include "RBASoundContentState.hpp"
#include "RBASceneImpl.hpp"
#include "RBAContentState.hpp"
#include "RBAContent.hpp"
#include "RBAAbstractAllocatable.hpp"
#include "RBAAllocatable.hpp"
#include "RBAConstraint.hpp"
#include "RBADisplay.hpp"
#include "RBAAbstractProperty.hpp"

namespace rba {

RBAResultSet::RBAResultSet(const RBAResultSet& resultSet)
  : outputtingAllocs_{resultSet.outputtingAllocs_}
  , hiddenAllocs_{resultSet.hiddenAllocs_}
  , activeContentStates_{resultSet.activeContentStates_}
  , canceledContentStates_{resultSet.canceledContentStates_}
  , allocToContentState_{resultSet.allocToContentState_}
  , visibleAreas_{resultSet.visibleAreas_}
  , soundingZones_{resultSet.soundingZones_}
  , invisibleAreas_{resultSet.invisibleAreas_}
  , unsoundingZones_{resultSet.unsoundingZones_}
  , hiddenAreas_{resultSet.hiddenAreas_}
  , muteZones_{resultSet.muteZones_}
  , attenuatedZones_{resultSet.attenuatedZones_}
  , canceledViewContents_{resultSet.canceledViewContents_}
  , canceledSoundContents_{resultSet.canceledSoundContents_}
  , standbyViewContents_{resultSet.standbyViewContents_}
  , standbySoundContents_{resultSet.standbySoundContents_}
  , visibleContentStates_{resultSet.visibleContentStates_}
  , soundingContentStates_{resultSet.soundingContentStates_}
  , activeViewContentStates_{resultSet.activeViewContentStates_}
  , activeSoundContentStates_{resultSet.activeSoundContentStates_}
  , requestOrderView_{resultSet.requestOrderView_}
  , requestOrderSound_{resultSet.requestOrderSound_}
  , activeScenes_{resultSet.activeScenes_}
  , propertyMap_{resultSet.propertyMap_}
  , event_content_{resultSet.event_content_}
  , contentToStatus_{resultSet.contentToStatus_}
  , requestContentStateMap_{resultSet.requestContentStateMap_}
#ifdef RBA_USE_LOG
  , failedConstraints_{resultSet.failedConstraints_}
#endif
{
}

// Impl [get VisibleArea/SoundingZone]

const std::set<const RBAAllocatable*>&
RBAResultSet::getOutputtingAllocatables() const
{
  return outputtingAllocs_;
}

const std::list<const RBAArea*>&
RBAResultSet::getVisibleAreas() const
{
  return visibleAreas_;
}
  
const std::list<const RBAZone*>&
RBAResultSet::getSoundingZones() const
{
  return soundingZones_;
}

// Impl [get Visible/Sounding ContentStates]

const std::list<const RBAViewContentState*>&
RBAResultSet::getVisibleContentStates() const
{
  return visibleContentStates_;
}

const std::list<const RBASoundContentState*>&
RBAResultSet::getSoundingContentStates() const
{
  return soundingContentStates_;
}

// Impl [get Active View/Sound ContentStates]

const std::set<const RBAContentState*>&
RBAResultSet::getActiveContentStates() const
{
  return activeContentStates_;
}

const std::list<const RBAViewContentState*>&
RBAResultSet::getActiveViewContentStates() const
{
  return activeViewContentStates_;
}

const std::list<const RBASoundContentState*>&
RBAResultSet::getActiveSoundContentStates() const
{
  return activeSoundContentStates_;
}

// Impl [get Active Scenes]

const std::list<const RBAScene*>&
RBAResultSet::getActiveScenes() const
{
  return activeScenes_;
}

// Impl [get InvisibleAreas/UnsoundingZone]

const std::list<const RBAArea*>&
RBAResultSet::getInvisibleAreas() const
{
  return invisibleAreas_;
}

const std::list<const RBAZone*>&
RBAResultSet::getUnsoundingZones() const
{
  return unsoundingZones_;
}

// Impl [get HiddenAreas/MuteZones]

const std::list<const RBAArea*>&
RBAResultSet::getHiddenAreas() const
{
  return hiddenAreas_;
}

const std::list<const RBAZone*>&
RBAResultSet::getMuteZones() const
{
  return muteZones_;
}

// Impl [get Attenuated]
const std::list<const RBAZone*>&
RBAResultSet::getAttenuatedZones() const
{
  return attenuatedZones_;
}

// Impl [get Canceled Contents]

const std::list<const RBAViewContent*>&
RBAResultSet::getCanceledViewContents() const
{
  return canceledViewContents_;
}

const std::list<const RBASoundContent*>&
RBAResultSet::getCanceledSoundContents() const
{
  return canceledSoundContents_;
}

// Impl [get Standby Contents]

const std::list<const RBAViewContent*>&
RBAResultSet::getStandbyViewContents() const
{
  return standbyViewContents_;
}

const std::list<const RBASoundContent*>&
RBAResultSet::getStandbySoundContents() const
{
  return standbySoundContents_;
}

// Impl [get ContentStates]

const RBAContentState*
RBAResultSet::getContentState(const RBAAllocatable* const alloc) const
{
  if(alloc != nullptr) {
    auto it = allocToContentState_.find(alloc);
    if(it != allocToContentState_.end()) {
      auto state = it->second;
      // If the content(state) assigned to the "alloc" has the 
      // allocatable function (such as cyclic), the contentState assigned to it 
      // is the contentState assigned to the "alloc".
      // Search this until it is not allocatable content. 
      while ((state != nullptr) 
              && (dynamic_cast<RBAAllocatable*>(state->getOwner()) != nullptr)) {
        it = allocToContentState_.find(dynamic_cast<RBAAllocatable*>(state->getOwner()));
        state = it->second;
      }
      return state;
    }
  }
  return nullptr;
}

const RBAContentState*
RBAResultSet::getDirectContentState(const RBAAllocatable* const alloc) const
{
  if(alloc != nullptr) {
    auto it = allocToContentState_.find(alloc);
    if(it != allocToContentState_.end()) {
      return it->second;
    }
  }
  return nullptr;
}

// Impl [get Areas/Zones by ConentState]

void
RBAResultSet::getAlloc(const RBAContentState* const state,
	                     std::list<const RBAAllocatable*>& allocList) const
{
  if(state != nullptr) {
    for(const auto& it : allocToContentState_) {
      if(it.second == state) {
	      allocList.push_back(it.first);
      }
    }
  }
}

void
RBAResultSet::getArea(const RBAViewContentState* const state,
		                  std::list<const RBAArea*>& areaList) const
{
  if(state != nullptr) {
    for(const auto& it : allocToContentState_) {
      if(dynamic_cast<const RBAViewContentState*>(it.second) == state) {
        const RBAContent* const content {dynamic_cast<const RBAContent*>(it.first)};
        if (content != nullptr) { // In case of CyclicContent
          // Get ViewContentState assigned to CyclicContent
          const RBAViewContentState* const ownerState
            {dynamic_cast<const RBAViewContentState*>(getReqestState(content))};
          // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
          //  [Contents that deviate from the rules]
          //   calling getArea() recursively
          //   [Reason that there is no problem if the rule is deviated]
          //   When getArea() is performed on CyclicContent, at that time, 
          //   respond Area where ViewContent assigned to CyclicContent 
          //   is assigned. When CyclicContent is assigned to CyclicContent, 
          //   multiple recursive calls may be made, but the rule model 
          //   definition is finite. 
          //   Therefore, stack overflow will not be occured, no problem.
          getArea(ownerState, areaList);
        } else {
  	      areaList.push_back(dynamic_cast<const RBAArea*>(it.first));
        }
      }
    }
  }
}

void
RBAResultSet::getZone(const RBASoundContentState* const state,
		                  std::list<const RBAZone*>& zoneList) const
{
  if(state != nullptr) {
    for(const auto& it : allocToContentState_) {
      if (dynamic_cast<const RBASoundContentState*>(it.second) == state) {
        const RBAContent* const content {dynamic_cast<const RBAContent*>(it.first)};
        if (content != nullptr) {
          const RBASoundContentState* const ownerState
            {dynamic_cast<const RBASoundContentState*>(getReqestState(content))};
          // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
          //  [Contents that deviate from the rules]
          //   Function '::rba::RBAResultSet::getZone=(_,
          //                  p={c::rba::RBASoundContentState},
          //                  &{c::std::__cxx11::list<p={c::rba::RBAZone},
          //                  {c::std::allocator<p={c::rba::RBAZone}>}>})' 
          //   is recursive. 
          //   [Reason that there is no problem if the rule is deviated]
          //   Recursive call is required as a feature
          getZone(ownerState, zoneList);
        } else {
	        zoneList.push_back(dynamic_cast<const RBAZone*>(it.first));
        }
      }
    }
  }
}

// Impl [get Areas/Zones by Content]

void
RBAResultSet::getArea(const RBAViewContent* const content,
		                  std::list<const RBAArea*>& areaList) const
{
  if(content != nullptr) {
    for(auto& state : content->getContentStates()) {
      getArea(state, areaList);
      if(!areaList.empty()) {
	      break;
      }
    }
  }
}

void
RBAResultSet::getZone(const RBASoundContent* const content,
		                  std::list<const RBAZone*>& zoneList) const
{
  if(content != nullptr) {
    for(auto& state : content->getContentStates()) {
      getZone(state, zoneList);
      if(!zoneList.empty()) {
	      break;
      }
    }
  }
}

// Impl [get Size]

const RBASize*
RBAResultSet::getSize(const RBAArea* const area) const
{
  if(area == nullptr) {
    return nullptr;
  }
  const RBAAreaImpl* const areaImpl {dynamic_cast<const RBAAreaImpl*>(area)};
  auto it = allocToContentState_.find(areaImpl);
  if(it == allocToContentState_.end() || (it->second == nullptr)) {
    return nullptr;
  }
  const RBAContent* const content {dynamic_cast<RBAContent*>(it->second->getOwner())};
  const RBASize* backupAreaSize {nullptr};
  std::int32_t backupDiffVal {-1};
  for(auto& areaSize : areaImpl->getSizes()) {
    const RBASizeImpl* const areaSizeImpl {dynamic_cast<const RBASizeImpl*>(areaSize)};
    for(auto& contentSize : content->getSizes()) {
      const RBASizeImpl* const contentSizeImpl {dynamic_cast<const RBASizeImpl*>(contentSize)};
      const auto diffVal = areaSizeImpl->diff(contentSizeImpl);
      if(diffVal == 0) {
	      return areaSizeImpl;
      }
      else if((backupDiffVal < 0) || (backupDiffVal > diffVal)) {
	      backupAreaSize = areaSizeImpl;
	      backupDiffVal = diffVal;
      } else {
        ;
      }
    }
  }

  return backupAreaSize;
}

// Impl [check Active Scene]

bool
RBAResultSet::isActive(const RBAScene* const scene) const
{
  return (std::find(activeScenes_.begin(), activeScenes_.end(), scene)
          != activeScenes_.end());
}

// Impl [check Active ContentState]
bool
RBAResultSet::isActive(const RBAContent* const content) const
{
  if (contentToStatus_.find(content) != contentToStatus_.end()) {
    return contentToStatus_[content].isActive();
  }
  return false;
}

bool
RBAResultSet::isActive(const RBAContentState* const state) const
{
  const RBAContent* const content {dynamic_cast<RBAContent*>(state->getOwner())};
  return (isActive(content) && (getReqestState(content) == state));
}

const RBAContentState*
RBAResultSet::getReqestState(const RBAContent* const content) const
{
  if (requestContentStateMap_.find(content) != requestContentStateMap_.end()) {
    return requestContentStateMap_[content];
  }
  return nullptr;
}

// Impl [check Outputting Allocatable]

bool
RBAResultSet::isOutputting(const RBAAllocatable* const alloc) const
{
  return outputtingAllocs_.find(alloc) != outputtingAllocs_.end();
}

// Impl [check Outputting ContentState]

bool
RBAResultSet::isOutputting(const RBAContentState* const state) const
{
  std::list<const RBAAllocatable*> allocList;
  getAlloc(state, allocList);
  for(auto& alloc : allocList) {
    if(isOutputting(alloc)) {
      return true;
    }
  }
  return false;
}

// Impl [check Hidden/Mute Area/Zone]

bool
RBAResultSet::isHidden(const RBAAllocatable* const alloc) const
{
  return hiddenAllocs_.find(alloc) != hiddenAllocs_.end();
}

// Impl [check Attenuated Zone]

bool
RBAResultSet::isAttenuated(const RBAZone* const zone) const
{
  return std::find(attenuatedZones_.begin(), attenuatedZones_.end(), zone) != attenuatedZones_.end();
}

// Impl [check Cancel ContentState]

bool
RBAResultSet::isCancel(const RBAContentState* const state) const
{
  return canceledContentStates_.find(state) != canceledContentStates_.end();
}

// Impl [check Aleady OutPutting]

bool
RBAResultSet::isAlreadyOutputting(const RBAContentState* const state) const
{
  const auto content = dynamic_cast<const RBAContent*>(state->getOwner());
  for(auto& alloc : content->getAllocatables()) {
    if((getContentState(alloc) == state) && !alloc->isHidden()) {
      return true;
    }
  }
  return false;
}

// Impl [set Active Scene]

/**
 * @brief Set display request or display withdrawal request, for Scene 
 * @param scene Scene
 * @param newActive true: display request, false: display withdrawal request
 */
void
RBAResultSet::setActive(const RBAScene* const scene, const bool newActive)
{
  const auto it = std::find(activeScenes_.begin(), activeScenes_.end(), scene);
  if(it == activeScenes_.end()) {
    if(newActive) {
      activeScenes_.push_back(scene);
    }
  }
  else {
    if(!newActive) {
      static_cast<void>(activeScenes_.erase(it));
    }
  }
}

// Impl [set Active ContentState]

/**
 * @brief Set display request or display withdrawal request, for Content state
 * @details If the content has already been registered, 
            delete the registered content.
 * @param contentState Content state
 * @param newActive true: display request, false: display withdrawal request
 */
void
RBAResultSet::setActive(const RBAContentState* const state, const bool newActive)
{
  updateRequestStatus(dynamic_cast<RBAContent*>(state->getOwner()), newActive);

  // Check if Content is already active
  const RBAContentState* temp {nullptr};
  for(auto& cs : activeContentStates_) {
    if(cs->getOwner() == state->getOwner()) {
      temp = cs;
      break;
    }
  }
  // Delete if Content is active
  if (temp != nullptr) {
    setOrder(temp, 0);
    static_cast<void>(activeContentStates_.erase(temp));
    if (temp->isViewContentState()) {
      activeViewContentStates_.remove(dynamic_cast<const RBAViewContentState*>(temp));
    } else {
      activeSoundContentStates_.remove(dynamic_cast<const RBASoundContentState*>(temp));
    }
  }

  // Rgistre active
  if(newActive) {
    requestContentStateMap_[dynamic_cast<const RBAContent*>(state->getOwner())] = state;
    static_cast<void>(activeContentStates_.insert(state));
    if (state->isViewContentState()) {
      setOrder(state, requestOrderView_);
      requestOrderView_++;
      activeViewContentStates_.push_back(dynamic_cast<const RBAViewContentState*>(state));
    } else {
      setOrder(state, requestOrderSound_);
      requestOrderSound_++;
      activeSoundContentStates_.push_back(dynamic_cast<const RBASoundContentState*>(state));
    }
  }
  else {
    setOrder(state, 0);
    static_cast<void>(requestContentStateMap_.erase(dynamic_cast<const RBAContent*>(state->getOwner())));
  }
}

// [cancel ContentState]

void
RBAResultSet::cancelContentState(const RBAContentState* const state)
{
  setOrder(state, 0);
  if (state->isViewContentState()) {
    canceledViewContents_.push_back(dynamic_cast<const RBAViewContent*>(state->getOwner()));
  } else {
    canceledSoundContents_.push_back(dynamic_cast<const RBASoundContent*>(state->getOwner()));
  }
}

// Impl [set Cancel ContentState]

void
RBAResultSet::setCancel(const RBAContentState* const state, const bool checked)
{
  if(checked) {
    static_cast<void>(canceledContentStates_.insert(state));
  }
  else {
    static_cast<void>(canceledContentStates_.erase(state));
  }
}

// Impl [set ContentState]

void
RBAResultSet::setContentState(const RBAAllocatable* const alloc, const RBAContentState* const state)
{
  //alloc
  allocToContentState_[alloc] = state;
  const bool isHiddenRes {alloc->isHidden()};
  const bool existsState {(state != nullptr)};
  const RBAAreaImpl* area {dynamic_cast<const RBAAreaImpl*>(alloc)};
  const RBAZoneImpl* zone {dynamic_cast<const RBAZoneImpl*>(alloc)};

  if (isHiddenRes) {
	static_cast<void>(hiddenAllocs_.insert(alloc));
  } else {
    // Currently, there is no case to delete the Allocable stored in 
    // hiddenAllocs_. In the future, since hiding may be forcibly released,
    // implement it.
	static_cast<void>(hiddenAllocs_.erase(alloc));
  }

  if (!isHiddenRes && existsState) {
    if (alloc->isArea() || alloc->isZone()) {
      static_cast<void>(outputtingAllocs_.insert(alloc));
    }
    if (isOutputting(alloc)) {
      const RBAContentState* s {state};
      while ((s != nullptr) && (dynamic_cast<RBAAllocatable*>(s->getOwner()) != nullptr)) {
        RBAAllocatable* extAlloc {dynamic_cast<RBAAllocatable*>(s->getOwner())};
        static_cast<void>(outputtingAllocs_.insert(extAlloc));
        s = extAlloc->getState();
      }
    }

    if (alloc->isArea()) {
      if (std::find(visibleAreas_.begin(), visibleAreas_.end(), area) == visibleAreas_.end()) {
        visibleAreas_.push_back(area);
      }
      invisibleAreas_.remove(area);
    } else if (alloc->isZone()) {
      if (std::find(soundingZones_.begin(), soundingZones_.end(), zone) == soundingZones_.end()) {
        soundingZones_.push_back(zone);
      }
      unsoundingZones_.remove(zone);
    } else {
      ;
    }
  } else {
	static_cast<void>(outputtingAllocs_.erase(alloc));
    if (alloc->isArea()) {
      // Currently, there is no case to delete the Area stored in visibleAreas_.
      // In the future, it may happen that content allocation is 
      // forcibly released, so implement thes.
      visibleAreas_.remove(area);
      if (std::find(invisibleAreas_.begin(), invisibleAreas_.end(), area) == invisibleAreas_.end()) {
        invisibleAreas_.push_back(area);
      }
    } else if (alloc->isZone()) {
      // Currently, there is no case to delete the Area stored in soundingZones_.
      // In the future, it may happen that content allocation is 
      // forcibly released, so implement thes.
      soundingZones_.remove(zone);
      if (std::find(unsoundingZones_.begin(), unsoundingZones_.end(), zone) == unsoundingZones_.end()) {
        unsoundingZones_.push_back(zone);
      }
    } else {
      ;
    }
  }

  if (isHiddenRes && existsState) {
    if (alloc->isArea()) {
      if (std::find(hiddenAreas_.begin(), hiddenAreas_.end(), area) == hiddenAreas_.end()) {
        hiddenAreas_.push_back(area);
      }
    } else if (alloc->isZone()) {
      if (std::find(muteZones_.begin(), muteZones_.end(), zone) == muteZones_.end()) {
        muteZones_.push_back(zone);
      }
    } else {
      ;
    }
  } else {
    if (alloc->isArea()) {
      hiddenAreas_.remove(area);
    } else if (alloc->isZone()) {
      muteZones_.remove(zone);
    } else {
      ;
    }
  }

  if (alloc->isZone()) {
    if (existsState && !isHiddenRes && zone->isAttenuated()) {
      if (std::find(attenuatedZones_.begin(), attenuatedZones_.end(), zone) == attenuatedZones_.end()) {
        attenuatedZones_.push_back(zone);
      }
    } else {
      // Currently, there is no case to delete the Allocatable stored in 
      // attenuatedZones_. In the future, there may be cases in which 
      // "attenuation" is forcibly canceled, so implement this.
      attenuatedZones_.remove(zone);
    }
  }
}

// Impl [add Visible/Sounding ContentState]

void
RBAResultSet::addOutputtingContentState(const RBAContentState* const state)
{
  if (state->isViewContentState()) {
    visibleContentStates_.push_back(dynamic_cast<const RBAViewContentState*>(state));
  }
  else if (state->isSoundContentState()) {
    soundingContentStates_.push_back(dynamic_cast<const RBASoundContentState*>(state));
  }
  else {
    ;
  }
}

// Impl [add Standby Content]

void
RBAResultSet::addStandbyContent(const RBAContent* const content)
{
  if (content->isViewContent()) {
    standbyViewContents_.push_back(dynamic_cast<const RBAViewContent*>(content));
  }
  else if (content->isSoundContent()) {
    standbySoundContents_.push_back(dynamic_cast<const RBASoundContent*>(content));
  }
  else {
    ;
  }
}

// [activeView]

void
RBAResultSet::copyActives(const std::unique_ptr<RBAResultSet>& resultSet)
{
  activeContentStates_ = resultSet->activeContentStates_;
  activeViewContentStates_ = resultSet->activeViewContentStates_;
  activeSoundContentStates_ = resultSet->activeSoundContentStates_;
  activeScenes_ = resultSet->activeScenes_;
  contentToStatus_ = resultSet->contentToStatus_;
  requestContentStateMap_ = resultSet->requestContentStateMap_;

  // Reset order
  requestOrderView_ = 1;
  requestOrderSound_ = 1;
  for(const RBAViewContentState* const viewState : activeViewContentStates_) {
    setOrder(dynamic_cast<const RBAContentState*>(viewState), requestOrderView_);
    requestOrderView_++;
  }
  for(const RBASoundContentState* const soundState : activeSoundContentStates_) {
    setOrder(dynamic_cast<const RBAContentState*>(soundState), requestOrderSound_);
    requestOrderSound_++;
  }
}

void
RBAResultSet::updateActiveContentStates()
{
  for (auto& state : canceledContentStates_) {
	static_cast<void>(activeContentStates_.erase(state));
    if (state->isViewContentState()) {
      activeViewContentStates_.remove(dynamic_cast<const RBAViewContentState*>(state));
    } else {
      activeSoundContentStates_.remove(dynamic_cast<const RBASoundContentState*>(state));
    }
  }
}

void
RBAResultSet::copyProperties(const std::unique_ptr<RBAResultSet>& resultSet)
{
  propertyMap_ = resultSet->propertyMap_;
}

void
RBAResultSet::setSceneProperty(const RBAScene* const scene,
                               const std::string& propertyName,
                               const std::int32_t value)
{
  propertyMap_[dynamic_cast<const RBASceneImpl*>(scene)->getProperty(propertyName)] = value;
}

void
RBAResultSet::setSceneProperty(const RBAAbstractProperty* const property,
			                         const std::int32_t value)
{
  propertyMap_[property] = value;
}

std::int32_t
RBAResultSet::getSceneProperty(const RBAAbstractProperty* const property) const
{
  auto it = propertyMap_.find(property);
  if(it == propertyMap_.end()) {
    // Property not registered
    return -99;
  }

  return it->second;
}

void
RBAResultSet::setContentOfEventProcessing(const RBAEventProcessing* const eventProcessing,
					                                const RBAContent* const content)
{
  event_content_[eventProcessing] = content;
}

const RBAContent*
RBAResultSet::getContentOfEventProcessing(const RBAEventProcessing* const eventProcessing) const
{
  if (event_content_.find(eventProcessing) != event_content_.end()) {
    return event_content_.at(eventProcessing);
  }
  return nullptr;
}

bool
RBAResultSet::hasDisplayingArea(const RBADisplay* const display) const
{
  bool displayed {false};
  const std::list<const RBAArea*> areas {display->getAreas()};
  const auto areasBegin = areas.begin();
  const auto areasEnd = areas.end();
  for(const RBAArea* const area : visibleAreas_) {
    if (std::find(areasBegin, areasEnd, area) != areasEnd) {
      displayed = true;
      break;
    }
  }
  return displayed;
}

bool
RBAResultSet::isLater(const RBAContent* const target,
                      const RBAContent* const comparisonTarget) const
{
  bool isLaterRes {false};
  bool isBreak {false};

  if (target->isViewContent()) {
    const RBAViewContent* const targetContent {
        dynamic_cast<const RBAViewContent*>(target)};
    const RBAViewContent* const comparisonTargetContent {
        dynamic_cast<const RBAViewContent*>(comparisonTarget)};
    for (auto it = activeViewContentStates_.rbegin();
        (it != activeViewContentStates_.rend()) && (!isBreak) ; it++) {
      if ((*it)->getOwner() == targetContent) {
        isLaterRes = true;
        isBreak = true;
      } else if ((*it)->getOwner() == comparisonTargetContent) {
        isBreak = true;
      } else {
        ;
      }
    }
  } else {
    const RBASoundContent* const targetContent {
        dynamic_cast<const RBASoundContent*>(target)};
    const RBASoundContent* const comparisonTargetContent {
        dynamic_cast<const RBASoundContent*>(comparisonTarget)};
    for (auto it = activeSoundContentStates_.rbegin();
        (it != activeSoundContentStates_.rend()) && (!isBreak); it++) {
      if ((*it)->getOwner() == targetContent) {
        isLaterRes = true;
        isBreak = true;
      } else if ((*it)->getOwner() == comparisonTargetContent) {
        isBreak = true;
      } else {
        ;
      }
    }
  }
  return isLaterRes;
}

std::set<const RBASceneImpl*>&
RBAResultSet::getDifferentConditionScenes(const RBAResultSet& target)
{
  // Detect the difference from the target scene On state
  const std::list<const RBAScene*> targetScenes {target.getActiveScenes()};
  for (auto& s : activeScenes_) {
    if (std::find(targetScenes.begin(), targetScenes.end(), s)
        == targetScenes.end()) {
      static_cast<void>(differentConditionScenes_.insert(dynamic_cast<const RBASceneImpl*>(s)));
    }
  }
  for (auto& s : targetScenes) {
    if (std::find(activeScenes_.begin(), activeScenes_.end(), s)
        == activeScenes_.end()) {
      static_cast<void>(differentConditionScenes_.insert(dynamic_cast<const RBASceneImpl*>(s)));
    }
  }

  // Detect the difference from the target scene property state
  for (auto& p : propertyMap_) {
    if (target.getSceneProperty(p.first) != p.second) {
      static_cast<void>(differentConditionScenes_.insert(p.first->getScene()));
    }
  }
  for (auto& p : target.getScenePropertyMap()) {
    if (getSceneProperty(p.first) != p.second) {
      static_cast<void>(differentConditionScenes_.insert(p.first->getScene()));
    }
  }
  return differentConditionScenes_;
}

void
RBAResultSet::updateRequestStatus(const RBAContent* const content, const bool isOnRequest)
{
  if (isOnRequest) {
    contentToStatus_[content].onRequest();
  } else {
    // When a content "off request" comes in, turn off the content request 
    // even if the requested state is different from Active state at that time.
    static_cast<void>(contentToStatus_.erase(content));
  }
}

void
RBAResultSet::setStatusType(const RBAContent* const content, const RBAContentStatusType type)
{
  contentToStatus_[content].setStatusType(type);
}

RBAContentStatusType
RBAResultSet::getStatusType(const RBAContent* const content) const
{
  if (contentToStatus_.find(content) != contentToStatus_.end()) {
    return contentToStatus_[content].getStatusType();
  }else {
    return RBAContentStatusType::NoRequest;
  }
}

bool
RBAResultSet::isOutput(const RBAContent* const content) const
{
  if (contentToStatus_.find(content) != contentToStatus_.end()) {
    return contentToStatus_[content].isDisplayed();
  } else {
    return false;
  }
}

bool
RBAResultSet::isStandby(const RBAContent* const content) const
{
  if (contentToStatus_.find(content)
      != contentToStatus_.end()) {
    return contentToStatus_[content].isStandby();
  } else {
    return false;
  }
}

bool
RBAResultSet::hasBeenCanceled(const RBAContent* const content) const
{
  if (contentToStatus_.find(content) != contentToStatus_.end()) {
    return contentToStatus_[content].hasBeenCanceled();
  } else {
    return false;
  }
}

bool
RBAResultSet::hasBeenDisplayed(const RBAContent* const content) const
{
  if (contentToStatus_.find(content) != contentToStatus_.end()) {
    return contentToStatus_[content].hasBeenDisplayed();
  } else {
    return false;
  }
}

std::unordered_map<const RBAContent*, RBAContentStatus>*
RBAResultSet::getStatus() const
{
  return &contentToStatus_;
}

#ifdef RBA_USE_LOG
void
RBAResultSet::addFailedConstraint(const RBAConstraint* constraint)
{
  failedConstraints_.push_back(constraint);
}

const std::list<const RBAConstraint*>&
RBAResultSet::getFailedConstraints()
{
  return failedConstraints_;
}
#endif

const std::unordered_map<const RBAAbstractProperty*, std::int32_t>&
RBAResultSet::getScenePropertyMap() const
{
  return propertyMap_;
}

void
RBAResultSet::setOrder(const RBAContentState* const state, const std::int32_t newOrder) const
{
  const_cast<RBAContentState*>(state)->setOrder(newOrder);
}

}
