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
 * RBAResultImpl (result of arbitration implementation) class
 */

#include "RBAResultImpl.hpp"

#include "RBAContentStatusType.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBASoundContentStateImpl.hpp"
#include "RBAResultSet.hpp"
#include "RBAAllocatable.hpp"
#include "RBAContentState.hpp"
#include "RBAContent.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAZoneImpl.hpp"
#include "RBASceneImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBAConstraint.hpp"
#include "RBAModelElementType.hpp"
#include "RBAViewActionType.hpp"
#include "RBAViewTransition.hpp"
#include "RBAViewMove.hpp"

namespace rba {

RBAResultImpl::RBAResultImpl(const RBAArbitratorImpl* const arb,
                              std::unique_ptr<RBAResultSet> newPrevResultSet):
                                RBAResult(),
                                preResultSet_{std::move(newPrevResultSet)},
                                arb_{arb},
                                statusType_{RBAResultStatusType::SUCCESS}
{
  curResultSet_ = std::make_unique<RBAResultSet>();
  curResultSet_->copyActives(preResultSet_);
  curResultSet_->copyProperties(preResultSet_);
}

RBAResultImpl::RBAResultImpl(const RBAArbitratorImpl* const arb,
                              std::unique_ptr<RBAResultSet> newPrevResultSet,
                              std::unique_ptr<RBAResultSet> newCurResultSet):
                                RBAResult(),
                                curResultSet_{std::move(newCurResultSet)},
                                preResultSet_{std::move(newPrevResultSet)},
                                arb_{arb},
                                statusType_{RBAResultStatusType::SUCCESS}
{
}

RBAResultImpl::RBAResultImpl(const RBAResultImpl* const replicationTarget)
  : RBAResult{},
    curResultSet_{std::make_unique<RBAResultSet>(*(replicationTarget->curResultSet_.get()))},
    preResultSet_{std::make_unique<RBAResultSet>(*(replicationTarget->preResultSet_.get()))},
    arb_{replicationTarget->arb_},
    statusType_{RBAResultStatusType::SUCCESS},
    log_{replicationTarget->log_}
{
  for (const auto &va : replicationTarget->viewActions_) {
    if (va->getViewActionType() == RBAViewActionType::MOVE) {
      viewActions_.push_back(
          std::make_unique<RBAViewMove>(va->getFromArea(), va->getToArea(),
                                        va->getContentState()));
    } else if (va->getViewActionType()
        == RBAViewActionType::TRANSITION_REPLACE) {
      viewActions_.push_back(
          std::make_unique<RBAViewTransition>(va->getViewActionType(),
                                              va->getArea(),
                                              va->getFromContentState(),
                                              va->getToContentState()));
    } else {
      viewActions_.push_back(
          std::make_unique<RBAViewTransition>(va->getViewActionType(),
                                              va->getArea(),
                                              va->getContentState()));
    }
  }
}

//
// External
//

// [get VisibleArea/SoundingZone]

const std::list<const RBAArea*>&
RBAResultImpl::getVisibleAreas() const
{
  return curResultSet_->getVisibleAreas();
}

const std::list<const RBAArea*>&
RBAResultImpl::getPreVisibleAreas() const
{
  return preResultSet_->getVisibleAreas();
}

const std::list<const RBAZone*>&
RBAResultImpl::getSoundingZones() const
{
  return curResultSet_->getSoundingZones();
}

const std::list<const RBAZone*>&
RBAResultImpl::getPreSoundingZones() const
{
  return preResultSet_->getSoundingZones();
}

// [get Visible/Sounding ContentStates]

const std::list<const RBAViewContentState*>&
RBAResultImpl::getVisibleContentStates() const
{
  return curResultSet_->getVisibleContentStates();
}

const std::list<const RBAViewContentState*>&
RBAResultImpl::getPreVisibleContentStates() const
{
  return preResultSet_->getVisibleContentStates();
}

const std::list<const RBASoundContentState*>&
RBAResultImpl::getSoundingContentStates() const
{
  return curResultSet_->getSoundingContentStates();
}

const std::list<const RBASoundContentState*>&
RBAResultImpl::getPreSoundingContentStates() const
{
  return preResultSet_->getSoundingContentStates();
}

// [get Active View/Sound ContentStates]

const std::list<const RBAViewContentState*>&
RBAResultImpl::getActiveViewContentStates() const
{
  return curResultSet_->getActiveViewContentStates();
}

const std::list<const RBAViewContentState*>&
RBAResultImpl::getPreActiveViewContentStates() const
{
  return preResultSet_->getActiveViewContentStates();
}

const std::list<const RBASoundContentState*>&
RBAResultImpl::getActiveSoundContentStates() const
{
  return curResultSet_->getActiveSoundContentStates();
}

const std::list<const RBASoundContentState*>&
RBAResultImpl::getPreActiveSoundContentStates() const
{
  return preResultSet_->getActiveSoundContentStates();
}

// [get etActive Scenes]

const std::list<const RBAScene*>&
RBAResultImpl::getActiveScenes() const
{
  return curResultSet_->getActiveScenes();
}

const std::list<const RBAScene*>&
RBAResultImpl::getPreActiveScenes() const
{
  return preResultSet_->getActiveScenes();
}

// [get InvisibleAreas/UnsoundingZone]

const std::list<const RBAArea*>&
RBAResultImpl::getInvisibleAreas() const
{
  return curResultSet_->getInvisibleAreas();
}

const std::list<const RBAArea*>&
RBAResultImpl::getPreInvisibleAreas() const
{
  return preResultSet_->getInvisibleAreas();
}

const std::list<const RBAZone*>&
RBAResultImpl::getUnsoundingZones() const
{
  return curResultSet_->getUnsoundingZones();
}

const std::list<const RBAZone*>&
RBAResultImpl::getPreUnsoundingZones() const
{
  return preResultSet_->getUnsoundingZones();
}

// [get HiddenAreas/MuteZones]

const std::list<const RBAArea*>&
RBAResultImpl::getHiddenAreas() const
{
  return curResultSet_->getHiddenAreas();
}

const std::list<const RBAArea*>&
RBAResultImpl::getPreHiddenAreas() const
{
  return preResultSet_->getHiddenAreas();
}

const std::list<const RBAZone*>&
RBAResultImpl::getMuteZones() const
{
  return curResultSet_->getMuteZones();
}

const std::list<const RBAZone*>&
RBAResultImpl::getPreMuteZones() const
{
  return preResultSet_->getMuteZones();
}

// [get Attenuated]

const std::list<const RBAZone*>&
RBAResultImpl::getAttenuatedZones() const
{
  return curResultSet_->getAttenuatedZones();
}

const std::list<const RBAZone*>&
RBAResultImpl::getPreAttenuatedZones() const
{
  return preResultSet_->getAttenuatedZones();
}

// [get Canceled Contents]

const std::list<const RBAViewContent*>&
RBAResultImpl::getCanceledViewContents() const
{
  return curResultSet_->getCanceledViewContents();
}

const std::list<const RBAViewContent*>&
RBAResultImpl::getPreCanceledViewContents() const
{
  return preResultSet_->getCanceledViewContents();
}

const std::list<const RBASoundContent*>&
RBAResultImpl::getCanceledSoundContents() const
{
  return curResultSet_->getCanceledSoundContents();
}

const std::list<const RBASoundContent*>&
RBAResultImpl::getPreCanceledSoundContents() const
{
  return preResultSet_->getCanceledSoundContents();
}

// [get Standby Contents]

const std::list<const RBAViewContent*>&
RBAResultImpl::getStandbyViewContents() const
{
  return curResultSet_->getStandbyViewContents();
}

const std::list<const RBAViewContent*>&
RBAResultImpl::getPreStandbyViewContents() const
{
  return preResultSet_->getStandbyViewContents();
}

const std::list<const RBASoundContent*>&
RBAResultImpl::getStandbySoundContents() const
{
  return curResultSet_->getStandbySoundContents();
}

const std::list<const RBASoundContent*>&
RBAResultImpl::getPreStandbySoundContents() const
{
  return preResultSet_->getStandbySoundContents();
}

// [get ContentStates]

const RBAViewContentState*
RBAResultImpl::getContentState(const RBAArea* area) const
{
  return dynamic_cast<const RBAViewContentState*>(
          curResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(area)));
}

const RBAViewContentState*
RBAResultImpl::getPreContentState(const RBAArea* area) const
{
  return dynamic_cast<const RBAViewContentState*>(
          preResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(area)));
}

const RBASoundContentState*
RBAResultImpl::getContentState(const RBAZone* zone) const
{
  return dynamic_cast<const RBASoundContentState*>(
          curResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(zone)));
}

const RBASoundContentState*
RBAResultImpl::getPreContentState(const RBAZone* zone) const
{
  return dynamic_cast<const RBASoundContentState*>(
          preResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(zone)));
}

// [get Areas/Zones by ConentState]

const std::list<const RBAArea*>
RBAResultImpl::getArea(const RBAViewContentState* state) const
{
  std::list<const RBAArea*> areaList;
  curResultSet_->getArea(state, areaList);
  return areaList;
}

const std::list<const RBAArea*>
RBAResultImpl::getPreArea(const RBAViewContentState* state) const
{
  std::list<const RBAArea*> areaList;
  preResultSet_->getArea(state, areaList);
  return areaList;
}

const std::list<const RBAZone*>
RBAResultImpl::getZone(const RBASoundContentState* state) const
{
  std::list<const RBAZone*> zoneList;
  curResultSet_->getZone(state, zoneList);
  return zoneList;
}

const std::list<const RBAZone*>
RBAResultImpl::getPreZone(const RBASoundContentState* state) const
{
  std::list<const RBAZone*> zoneList;
  preResultSet_->getZone(state, zoneList);
  return zoneList;
}

// [get Areas/Zones by Content]

const std::list<const RBAArea*>
RBAResultImpl::getArea(const RBAViewContent* content) const
{
  std::list<const RBAArea*> areaList;
  curResultSet_->getArea(content, areaList);
  return areaList;
}

const std::list<const RBAArea*>
RBAResultImpl::getPreArea(const RBAViewContent* content) const
{
  std::list<const RBAArea*> areaList;
  preResultSet_->getArea(content, areaList);
  return areaList;
}

const std::list<const RBAZone*>
RBAResultImpl::getZone(const RBASoundContent* content) const
{
  std::list<const RBAZone*> zoneList;
  curResultSet_->getZone(content, zoneList);
  return zoneList;
}

const std::list<const RBAZone*>
RBAResultImpl::getPreZone(const RBASoundContent* content) const
{
  std::list<const RBAZone*> zoneList;
  preResultSet_->getZone(content, zoneList);
  return zoneList;
}

// [get Size]

const RBASize*
RBAResultImpl::getSize(const RBAArea* area) const
{
  return curResultSet_->getSize(area);
}

const RBASize*
RBAResultImpl::getPreSize(const RBAArea* area) const
{
  return preResultSet_->getSize(area);
}

// [check Active Scene]
bool
RBAResultImpl::isActive(const RBAScene* scene) const
{
  return curResultSet_->isActive(scene);
}

bool
RBAResultImpl::isPreActive(const RBAScene* scene) const
{
  return preResultSet_->isActive(scene);
}

// [check Active Content]
bool
RBAResultImpl::isActive(const RBAContent* const content) const
{
  return curResultSet_->isActive(content);
}
bool
RBAResultImpl::isActive(const RBAViewContent* content) const
{
  return curResultSet_->isActive(dynamic_cast<const RBAContent*>(content));
}

bool
RBAResultImpl::isActive(const RBASoundContent* content) const
{
  return curResultSet_->isActive(dynamic_cast<const RBAContent*>(content));
}
bool
RBAResultImpl::isPreActive(const RBAContent* const content) const
{
  return preResultSet_->isActive(content);
}
bool
RBAResultImpl::isPreActive(const RBAViewContent* content) const
{
  return preResultSet_->isActive(dynamic_cast<const RBAContent*>(content));
}

bool
RBAResultImpl::isPreActive(const RBASoundContent* content) const
{
  return preResultSet_->isActive(dynamic_cast<const RBAContent*>(content));
}

// [check Active ContentState]
bool
RBAResultImpl::isActive(const RBAContentState* const state) const
{
  return curResultSet_->isActive(state);
}

bool
RBAResultImpl::isActive(const RBAViewContentState* const state) const
{
  return isActive(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isActive(const RBASoundContentState* const state) const
{
  return isActive(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isPreActive(const RBAContentState* const state) const
{
  return preResultSet_->isActive(state);
}

bool
RBAResultImpl::isPreActive(const RBAViewContentState* const state) const
{
  return isPreActive(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isPreActive(const RBASoundContentState* const state) const
{
  return isPreActive(dynamic_cast<const RBAContentState*>(state));
}

const RBAContentState*
RBAResultImpl::getActiveState(const RBAContent* const content) const
{
  if (curResultSet_->isActive(content)){
    return curResultSet_->getReqestState(content);
  }
  return nullptr;
}

const RBAContentState*
RBAResultImpl::getPreActiveState(const RBAContent* const content) const
{
  if (preResultSet_->isActive(content)){
    return preResultSet_->getReqestState(content);
  }
  return nullptr;
}

// [check Visible/Sounding Alloc ContentState]

bool
RBAResultImpl::isOutputting(const RBAAllocatable* const alloc) const
{
  return curResultSet_->isOutputting(alloc);
}

bool
RBAResultImpl::isPreOutputting(const RBAAllocatable* const alloc) const
{
  return preResultSet_->isOutputting(alloc);
}

bool
RBAResultImpl::isOutputting(const RBAContentState* const state) const
{
  return curResultSet_->isOutputting(state);
}

bool
RBAResultImpl::isPreOutputting(const RBAContentState* const state) const
{
  return preResultSet_->isOutputting(state);
}

bool
RBAResultImpl::isVisible(const RBAViewContentState* state) const
{
  return isOutputting(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isPreVisible(const RBAViewContentState* state) const
{
  return isPreOutputting(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isSounding(const RBASoundContentState* state) const
{
  return isOutputting(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isPreSounding(const RBASoundContentState* state) const
{
  return isPreOutputting(dynamic_cast<const RBAContentState*>(state));
}

// [get View/Sound ContentState]

const RBAContentState*
RBAResultImpl::getAllocatedContentState(const RBAAllocatable* const allocatable) const
{
  return curResultSet_->getContentState(allocatable);
}

const RBAContentState*
RBAResultImpl::getPreAllocatedContentState(const RBAAllocatable* const allocatable) const
{
  return preResultSet_->getContentState(allocatable);
}

const RBAViewContentState*
RBAResultImpl::getViewContentState(const RBAArea* area) const
{
  return dynamic_cast<const RBAViewContentState*>(
          curResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(area)));
}

const RBAViewContentState*
RBAResultImpl::getPreViewContentState(const RBAArea* area) const
{
  return dynamic_cast<const RBAViewContentState*>(
          preResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(area)));
}

const RBASoundContentState*
RBAResultImpl::getSoundContentState(const RBAZone* zone) const
{
  return dynamic_cast<const RBASoundContentState*>(
          curResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(zone)));
}

const RBASoundContentState*
RBAResultImpl::getPreSoundContentState(const RBAZone* zone) const
{
  return dynamic_cast<const RBASoundContentState*>(
          preResultSet_->getContentState(dynamic_cast<const RBAAllocatable*>(zone)));
}

// [check Hidden/Mute]

bool
RBAResultImpl::isHidden(const RBAArea* area) const
{
  return isHidden(dynamic_cast<const RBAAllocatable*>(area));
}

bool
RBAResultImpl::isPreHidden(const RBAArea* area) const
{
  return isPreHidden(dynamic_cast<const RBAAllocatable*>(area));
}

bool
RBAResultImpl::isMute(const RBAZone* zone) const
{
  return isHidden(dynamic_cast<const RBAAllocatable*>(zone));
}

bool
RBAResultImpl::isPreMute(const RBAZone* zone) const
{
  return isPreHidden(dynamic_cast<const RBAAllocatable*>(zone));
}

// [check Attenuated]
bool
RBAResultImpl::isAttenuated(const RBAZone* zone) const
{
  return curResultSet_->isAttenuated(zone);
}

bool
RBAResultImpl::isPreAttenuated(const RBAZone* zone) const
{
  return preResultSet_->isAttenuated(zone);
}

// [common]

const std::list<const RBAViewAction*>&
RBAResultImpl::getViewActions() const
{
  viewActionsForPublicUse_.clear();
  for (auto& va :viewActions_) {
    viewActionsForPublicUse_.push_back(va.get());
  }
  return viewActionsForPublicUse_;
}

RBAResultStatusType
RBAResultImpl::getStatusType() const
{
  return statusType_;
}

bool
RBAResultImpl::isLater(const RBAContent* const target,
                       const RBAContent* const comparisonTarget) const
{
  return curResultSet_->isLater(target, comparisonTarget);
}

std::string
RBAResultImpl::getLog() const
{
  return log_;
}

void
RBAResultImpl::setLog(const std::string& log)
{
  log_ = log;
}

bool
RBAResultImpl::hasDisplayingArea(const RBADisplay* display) const
{
  if (display == nullptr) {
    return false;
  } else {
    return curResultSet_->hasDisplayingArea(display);
  }
}

bool
RBAResultImpl::satisfiesConstraints() const
{
  if(statusType_ != RBAResultStatusType::SUCCESS) {
    return false;
  }
  return arb_->satisfiesConstraints();
}

void
RBAResultImpl::setSceneProperty(const RBASceneImpl* const scene,
                                const std::string& propertyName,
                                const std::int32_t value)
{
  curResultSet_->setSceneProperty(scene->getProperty(propertyName), value);
}

void
RBAResultImpl::setSceneProperty(const RBAAbstractProperty* const property,
                                const std::int32_t value)
{
  curResultSet_->setSceneProperty(property, value);
}

std::int32_t
RBAResultImpl::getSceneProperty(const RBAScene* scene,
				const std::string& propertyName) const
{
  if(scene == nullptr) {
    return -99;
  }

  const RBAAbstractProperty* const prop
    {dynamic_cast<const RBASceneImpl*>(scene)->getProperty(propertyName)};
  if(prop == nullptr) {
    return -99;
  }

  return curResultSet_->getSceneProperty(prop);
}

std::int32_t
RBAResultImpl::getSceneProperty(const RBAAbstractProperty* const property) const
{
  return curResultSet_->getSceneProperty(property);
}

std::int32_t
RBAResultImpl::getPreSceneProperty(const RBAAbstractProperty* const property) const
{
  return preResultSet_->getSceneProperty(property);
}

//
// Internal
//

// Impl [VisibleArea/SoundingZone]

const std::set<const RBAAllocatable*>&
RBAResultImpl::getOutputtingAllocatables() const
{
  return curResultSet_->getOutputtingAllocatables();
}

// Impl [get Active View/Sound ContentStates]

const std::set<const RBAContentState*>&
RBAResultImpl::getActiveContentStates() const
{
  return curResultSet_->getActiveContentStates();
}

// Impl [get ContentStates]
const RBAContentState*
RBAResultImpl::getContentState(const RBAAllocatable* const allocatable) const
{
  return curResultSet_->getContentState(allocatable);
}

const RBAContentState*
RBAResultImpl::getDirectContentState(const RBAAllocatable* const allocatable) const
{
  return curResultSet_->getDirectContentState(allocatable);
}

const RBAContentState*
RBAResultImpl::getPreContentState(const RBAAllocatable* const allocatable) const
{
  return preResultSet_->getContentState(allocatable);
}

const RBAContentState*
RBAResultImpl::getDirectPreContentState(const RBAAllocatable* const allocatable) const
{
  return preResultSet_->getDirectContentState(allocatable);
}

// Impl [get Areas/Zones by ConentState]

std::list<const RBAAllocatable*>
RBAResultImpl::getAllocatable(const RBAContentState* const state) const
{
  std::list<const RBAAllocatable*> allocatables;
  if(state->isViewContentState()) {
    std::list<const RBAArea*> areaList;
    curResultSet_->getArea(dynamic_cast<const RBAViewContentState*>(state),
			   areaList);
    for (const auto& area : areaList) {
      allocatables.push_back(dynamic_cast<const RBAAllocatable*>(area));
    }
  }
  else {
    std::list<const RBAZone*> zoneList;
    curResultSet_->getZone(dynamic_cast<const RBASoundContentState*>(state),
			   zoneList);
    for (const auto& zone : zoneList) {
      allocatables.push_back(dynamic_cast<const RBAAllocatable*>(zone));
    }
  }
  return allocatables;
}

// Impl [check Aleady Visible/Sounding]
bool
RBAResultImpl::isAlreadyOutputting(const RBAContentState* const state) const
{
  return curResultSet_->isAlreadyOutputting(state);
}

// Impl [set Active Scene]

void
RBAResultImpl::setActive(const RBAScene* const scene, const bool newActive)
{
  curResultSet_->setActive(scene, newActive);
}

// Impl [set Active ContentState]

void
RBAResultImpl::setActive(const RBAContentState* const state, const bool newActive)
{
  curResultSet_->setActive(state, newActive);
}

// Impl [add Standby Content]

void
RBAResultImpl::addStandbyContent(const RBAContent* const content)
{
  curResultSet_->addStandbyContent(content);
}

// Impl [check Visible/Sounding Area/Zone]

bool
RBAResultImpl::isVisible(const RBAArea* area) const
{
  return curResultSet_->isOutputting(dynamic_cast<const RBAAllocatable*>(area));
}

bool
RBAResultImpl::isPreVisible(const RBAArea* area) const
{
  return preResultSet_->isOutputting(dynamic_cast<const RBAAllocatable*>(area));
}

bool
RBAResultImpl::isSounding(const RBAZone* zone) const
{
  return curResultSet_->isOutputting(dynamic_cast<const RBAAllocatable*>(zone));
}

bool
RBAResultImpl::isPreSounding(const RBAZone* zone) const
{
  return preResultSet_->isOutputting(dynamic_cast<const RBAAllocatable*>(zone));
}

// Impl [set View/Sound ContentState]

void RBAResultImpl::setContentState(const RBAAllocatable* const allocatable,
                                    const RBAContentState* const state)
{
  curResultSet_->setContentState(allocatable, state);
}

// Impl [check Hidden/Mute Area/Zone]

bool
RBAResultImpl::isHidden(const RBAAllocatable* const allocatable) const
{
  return curResultSet_->isHidden(allocatable);
}

bool
RBAResultImpl::isPreHidden(const RBAAllocatable* const allocatable) const
{
  return preResultSet_->isHidden(allocatable);
}

// Impl [set Cancel ContentState]

void
RBAResultImpl::setCancel(const RBAContentState* const state, const bool checked)
{
  curResultSet_->setCancel(state, checked);
}

// Impl [check Cancel ContentState]

bool
RBAResultImpl::isCancel(const RBAContentState* const state) const
{
  return curResultSet_->isCancel(state);
}

bool
RBAResultImpl::isPreCancel(const RBAContentState* const state) const
{
  return preResultSet_->isCancel(state);
}

bool
RBAResultImpl::isCancel(const RBAViewContentState* state) const
{
  return isCancel(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isPreCancel(const RBAViewContentState* state) const
{
  return isPreCancel(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isCancel(const RBASoundContentState* state) const
{
  return isCancel(dynamic_cast<const RBAContentState*>(state));
}

bool
RBAResultImpl::isPreCancel(const RBASoundContentState* state) const
{
  return isPreCancel(dynamic_cast<const RBAContentState*>(state));
}

// Impl [add Visible/Sounding ContentState]

void
RBAResultImpl::addOutputtingContentState(const RBAContentState* const state)
{
  curResultSet_->addOutputtingContentState(state);
}

// Impl [cancel ContentState]

void
RBAResultImpl::cancelContentState(const RBAContentState* const state)
{
  curResultSet_->cancelContentState(state);
}

// Impl [common]

std::unique_ptr<RBAResultSet>
RBAResultImpl::createBackupCurrentResultSet()
{
  return std::make_unique<RBAResultSet>(*curResultSet_);
}

std::unique_ptr<RBAResultSet>
RBAResultImpl::createNextCurrentResultSet()
{
  std::unique_ptr<RBAResultSet> nextResultSet {std::make_unique<RBAResultSet>()};
  nextResultSet->copyActives(curResultSet_);
  nextResultSet->copyProperties(curResultSet_);
  return nextResultSet;
}

void
RBAResultImpl::addViewAction(std::unique_ptr<RBAViewAction>& newViewAction)
{
  viewActions_.push_back(move(newViewAction));
}

void
RBAResultImpl::setStatusType(const RBAResultStatusType newStatusType)
{
  statusType_ = newStatusType;
}

void
RBAResultImpl::updateActiveContentStates()
{
  curResultSet_->updateActiveContentStates();
}

void
RBAResultImpl::setContentOfEventProcessing(const RBAEventProcessing* const eventProcessing,
					                                 const RBAContent* const viewContent)
{
  curResultSet_->setContentOfEventProcessing(eventProcessing, viewContent);
}

std::unique_ptr<RBAResultSet>&
RBAResultImpl::getCurResultSet()
{
  return curResultSet_;
}

std::unique_ptr<RBAResultSet>&
RBAResultImpl::getPreResultSet()
{
  return preResultSet_;
}

RBAContentStatusType RBAResultImpl::getStatusType(const RBAContent* const content) const
{
  return curResultSet_->getStatusType(content);
}
bool RBAResultImpl::isStandby(const RBAContent* const content) const
{
  return curResultSet_->isStandby(content);
}

bool RBAResultImpl::hasBeenCanceled(const RBAContent* const content) const
{
  return curResultSet_->hasBeenCanceled(content);
}

bool RBAResultImpl::hasBeenPreCanceled(const RBAContent* const content) const
{
  return preResultSet_->hasBeenCanceled(content);
}

bool RBAResultImpl::hasBeenDisplayed(const RBAContent* const content) const
{
  return curResultSet_->hasBeenDisplayed(content);
}
bool RBAResultImpl::hasBeenPreDisplayed(const RBAContent* const content) const
{
  return preResultSet_->hasBeenDisplayed(content);
}

void RBAResultImpl::updateStatus(const RBAContent* const content)
{
  const RBAContentState* const s {getActiveState(content)};
  if (s != nullptr) {
    if (isOutputting(s)) {
      curResultSet_->setStatusType(content, RBAContentStatusType::Displayed);
    } else if (isCancel(s)) {
      curResultSet_->setStatusType(content, RBAContentStatusType::Canceled);
    } else if (curResultSet_->getStatusType(content) != RBAContentStatusType::Undisplayed) {
      curResultSet_->setStatusType(content, RBAContentStatusType::StandBy);
    } else {
      ;
    }
  }
}

std::unordered_map<const RBAContent*, RBAContentStatus>* RBAResultImpl::getCurStatus() const
{
  return curResultSet_->getStatus();
}

std::set<const RBASceneImpl*>& RBAResultImpl::getDifferentConditionScenes() const
{
  return (curResultSet_->getDifferentConditionScenes(*preResultSet_.get()));
}
#ifdef RBA_USE_LOG
void
RBAResultImpl::addFailedConstraint(const RBAConstraint* constraint)
{
  curResultSet_->addFailedConstraint(constraint);
}

const std::list<const RBAConstraint*>&
RBAResultImpl::getFailedConstraints() const
{
  return curResultSet_->getFailedConstraints();
}
#endif

}
