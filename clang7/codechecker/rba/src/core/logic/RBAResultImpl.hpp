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
 * RBAResultImpl (result of arbitration implementation) class header
 */

#ifndef RBARESULTIMPL_HPP
#define RBARESULTIMPL_HPP

#include <memory>
#include <unordered_map>
#include <set>
#include "RBAResult.hpp"
#include "RBAResultStatusType.hpp"
#include "RBAContentStatusType.hpp"

namespace rba {

class RBAArbitratorImpl;
class RBAArea;
class RBAViewContent;
class RBAViewContentState;
class RBASize;
class RBAScene;
class RBAAbstractProperty;
class RBAAreaImpl;
class RBAContentStateImpl;
class RBAViewContentImpl;
class RBAViewContentStateImpl;
class RBASizeImpl;
class RBASceneImpl;
class RBAResultSet;
class RBAViewAction;
class RBAZoneImpl;
class RBASoundContentImpl;
class RBASoundContentStateImpl;
class RBASoundContent;
class RBASoundContentState;
class RBAContentState;
class RBAAllocatable;
class RBAContent;
class RBAEventProcessing;
class RBAConstraint;
class RBAContentStatus;

class DLL_EXPORT RBAResultImpl : public RBAResult
{
public:
  RBAResultImpl(const RBAArbitratorImpl* const arb,
                std::unique_ptr<RBAResultSet> newPrevResultSet);
  RBAResultImpl(const RBAArbitratorImpl* const arb,
                std::unique_ptr<RBAResultSet> newPrevResultSet,
                std::unique_ptr<RBAResultSet> newCurResultSet);
  RBAResultImpl(const RBAResultImpl* const replicationTarget);
  RBAResultImpl(const RBAResultImpl&)=delete;
  RBAResultImpl(const RBAResultImpl&&)=delete;
  RBAResultImpl& operator=(const RBAResultImpl&)=delete;
  RBAResultImpl& operator=(const RBAResultImpl&&)=delete;
  virtual ~RBAResultImpl()=default;

public:

  //
  // External
  //

  // [get VisibleArea/SoundingZone]
  const std::list<const RBAArea*>& getVisibleAreas() const override;
  const std::list<const RBAArea*>& getPreVisibleAreas() const override;
  const std::list<const RBAZone*>& getSoundingZones() const override;
  const std::list<const RBAZone*>& getPreSoundingZones() const override;

  // [get Visible/Sounding ContentStates]
  const std::list<const RBAViewContentState*>& getVisibleContentStates() const override;
  const std::list<const RBAViewContentState*>& getPreVisibleContentStates() const override;
  const std::list<const RBASoundContentState*>& getSoundingContentStates() const override;
  const std::list<const RBASoundContentState*>& getPreSoundingContentStates() const override;

  // [get Active View/Sound ContentStates]
  const std::list<const RBAViewContentState*>& getActiveViewContentStates() const override;
  const std::list<const RBAViewContentState*>& getPreActiveViewContentStates() const override;
  const std::list<const RBASoundContentState*>& getActiveSoundContentStates() const override;
  const std::list<const RBASoundContentState*>& getPreActiveSoundContentStates() const override;

  // [get Active Scenes]
  const std::list<const RBAScene*>& getActiveScenes() const override;
  const std::list<const RBAScene*>& getPreActiveScenes() const override;

  // [get InvisibleAreas/UnsoundingZone]
  const std::list<const RBAArea*>& getInvisibleAreas() const override;
  const std::list<const RBAArea*>& getPreInvisibleAreas() const override;
  const std::list<const RBAZone*>& getUnsoundingZones() const override;
  const std::list<const RBAZone*>& getPreUnsoundingZones() const override;

  // [get HiddenAreas/MuteZones]
  const std::list<const RBAArea*>& getHiddenAreas() const override;
  const std::list<const RBAArea*>& getPreHiddenAreas() const override;
  const std::list<const RBAZone*>& getMuteZones() const override;
  const std::list<const RBAZone*>& getPreMuteZones() const override;

  // [get Attenuated]
  const std::list<const RBAZone*>& getAttenuatedZones() const override;
  const std::list<const RBAZone*>& getPreAttenuatedZones() const override;

  // [get Canceled Contents]
  const std::list<const RBAViewContent*>& getCanceledViewContents() const override;
  const std::list<const RBAViewContent*>& getPreCanceledViewContents() const override;
  const std::list<const RBASoundContent*>& getCanceledSoundContents() const override;
  const std::list<const RBASoundContent*>& getPreCanceledSoundContents() const override;

  // [get Standby Contents]
  const std::list<const RBAViewContent*>& getStandbyViewContents() const override;
  const std::list<const RBAViewContent*>& getPreStandbyViewContents() const override;
  const std::list<const RBASoundContent*>& getStandbySoundContents() const override;
  const std::list<const RBASoundContent*>& getPreStandbySoundContents() const override;

  // [get ContentStates]
  const RBAViewContentState* getContentState(const RBAArea* area) const override;
  const RBAViewContentState* getPreContentState(const RBAArea* area) const override;
  const RBASoundContentState* getContentState(const RBAZone* zone) const override;
  const RBASoundContentState* getPreContentState(const RBAZone* zone) const override;

  // [get Areas/Zones by ConentState]
  const std::list<const RBAArea*> getArea(const RBAViewContentState* state) const override;
  const std::list<const RBAArea*> getPreArea(const RBAViewContentState* state) const override;
  const std::list<const RBAZone*> getZone(const RBASoundContentState* state) const override;
  const std::list<const RBAZone*> getPreZone(const RBASoundContentState* state) const override;

  // [get Areas/Zones by Content]
  const std::list<const RBAArea*> getArea(const RBAViewContent* content) const override;
  const std::list<const RBAArea*> getPreArea(const RBAViewContent* content) const override;
  const std::list<const RBAZone*> getZone(const RBASoundContent* content) const override;
  const std::list<const RBAZone*> getPreZone(const RBASoundContent* content) const override;

  // [get Size]
  const RBASize* getSize(const RBAArea* area) const override;
  const RBASize* getPreSize(const RBAArea* area) const override;

  // [check Active Scene]
  bool isActive(const RBAScene* scene) const override;
  bool isPreActive(const RBAScene* scene) const override;

  // [check Active Content]
  bool isActive(const RBAContent* const content) const;
  bool isPreActive(const RBAContent* const content) const;
  bool isActive(const RBAViewContent* content) const override;
  bool isActive(const RBASoundContent* content) const override;
  bool isPreActive(const RBAViewContent* content) const override;
  bool isPreActive(const RBASoundContent* content) const override;

  // [check Visible/Sounding Area/Zone]
  bool isVisible(const RBAArea* area) const override;
  bool isPreVisible(const RBAArea* area) const override;
  bool isSounding(const RBAZone* zone) const override;
  bool isPreSounding(const RBAZone* zone) const override;

  // [check Visible/Sounding ContentState]
  bool isVisible(const RBAViewContentState* state) const override;
  bool isPreVisible(const RBAViewContentState* state) const override;
  bool isSounding(const RBASoundContentState* state) const override;
  bool isPreSounding(const RBASoundContentState* state) const override;

  // [get View/Sound ContentState]
  const RBAViewContentState* getViewContentState(const RBAArea* area) const override;
  virtual const RBAViewContentState* getPreViewContentState(const RBAArea* area) const;
  const RBASoundContentState* getSoundContentState(const RBAZone* zone) const override;
  const RBASoundContentState* getPreSoundContentState(const RBAZone* zone) const override;

  // [check Hidden/Mute]
  bool isHidden(const RBAArea* area) const override;
  bool isPreHidden(const RBAArea* area) const override;
  bool isMute(const RBAZone* zone) const override;
  bool isPreMute(const RBAZone* zone) const override;

  // [check Attenuated]
  bool isAttenuated(const RBAZone* zone) const override;
  bool isPreAttenuated(const RBAZone* zone) const override;

  // [check Cancel]
  bool isCancel(const RBAViewContentState* state) const override;
  bool isPreCancel(const RBAViewContentState* state) const override;
  bool isCancel(const RBASoundContentState* state) const override;
  bool isPreCancel(const RBASoundContentState* state) const override;

  // [common]
  const std::list<const RBAViewAction*>& getViewActions() const override;
  RBAResultStatusType getStatusType() const override;
  bool isLater(const RBAContent* const target,
               const RBAContent* const comparisonTarget) const;

  std::string getLog() const override;
  void setLog(const std::string& log);

  bool hasDisplayingArea(const RBADisplay* display) const override;

  bool satisfiesConstraints() const override;

  std::int32_t getSceneProperty(const RBAScene* scene,
					            const std::string& propertyName) const override;
  //
  // Internal
  //

  // Impl [get VisibleArea/SoundingZone]
  const std::set<const RBAAllocatable*>& getOutputtingAllocatables() const;

  // Impl [get Active View/Sound ContentStates]
  const std::set<const RBAContentState*>& getActiveContentStates() const;

  // Impl [get ContentStates]
  const RBAContentState* getContentState(const RBAAllocatable* const allocatable) const;
  const RBAContentState* getDirectContentState(const RBAAllocatable* const allocatable) const;
  const RBAContentState* getPreContentState(const RBAAllocatable* const allocatable) const;
  const RBAContentState* getDirectPreContentState(const RBAAllocatable* const allocatable) const;

  // Impl [get Areas/Zones by ConentState]
  std::list<const RBAAllocatable*> getAllocatable(const RBAContentState* const state) const;

  // Impl [check Aleady Outputting]
  bool isAlreadyOutputting(const RBAContentState* const state) const;

  // Impl [set Active Scene]
  void setActive(const RBAScene* const scene, const bool newActive);

  // Impl [check Active ContentState]
  bool isActive(const RBAContentState* const state) const;
  bool isActive(const RBAViewContentState* const state) const;
  bool isActive(const RBASoundContentState* const state) const;
  bool isPreActive(const RBAContentState* const state) const;
  bool isPreActive(const RBAViewContentState* const state) const;
  bool isPreActive(const RBASoundContentState* const state) const;
  const RBAContentState* getActiveState(const RBAContent* const content) const;
  const RBAContentState* getPreActiveState(const RBAContent* const content) const;

  // Impl [set Active ContentState]
  void setActive(const RBAContentState* const state, const bool newActive);

  // Impl [add Standby Content]
  void addStandbyContent(const RBAContent* const content);

  // Impl [check Visible/Sounding Alloc ContentState]
  bool isOutputting(const RBAAllocatable* const alloc) const;
  bool isPreOutputting(const RBAAllocatable* const alloc) const;
  bool isOutputting(const RBAContentState* const state) const;
  bool isPreOutputting(const RBAContentState* const state) const;

  // Impl [get View/Sound ContentState by Allocatable]
  const RBAContentState* getAllocatedContentState(const RBAAllocatable* const allocatable) const;
  const RBAContentState* getPreAllocatedContentState(const RBAAllocatable* const allocatable) const;

  // Impl [set View/Sound ContentState]
  void setContentState(const RBAAllocatable* const allocatable, const RBAContentState* const state);

  // Impl [check Hidden/Mute Area/Zone]
  bool isHidden(const RBAAllocatable* const allocatable) const;
  bool isPreHidden(const RBAAllocatable* const allocatable) const;

  // Impl [set Cancel ContentState]
  void setCancel(const RBAContentState* const state, const bool checked);

  // Impl [check Cancel ContentState]
  bool isCancel(const RBAContentState* const state) const;
  bool isPreCancel(const RBAContentState* const state) const;

  // Impl [add Visible/Sounding ContentState]
  void addOutputtingContentState(const RBAContentState* const state);

  // Impl [cancel ContentState]
  void cancelContentState(const RBAContentState* const state);
  
  // Impl [common]
  std::unique_ptr<RBAResultSet> createBackupCurrentResultSet();
  std::unique_ptr<RBAResultSet> createNextCurrentResultSet();
  void addViewAction(std::unique_ptr<RBAViewAction>& newViewAction);
  void setStatusType(const RBAResultStatusType newStatusType);
  void updateActiveContentStates();
  void setSceneProperty(const RBASceneImpl* const scene,
                        const std::string& propertyName,
                        const std::int32_t value);
  void setSceneProperty(const RBAAbstractProperty* const property,
                        const std::int32_t value);
  std::int32_t getSceneProperty(const RBAAbstractProperty* const property) const;
  std::int32_t getPreSceneProperty(const RBAAbstractProperty* const property) const;
  void setContentOfEventProcessing(const RBAEventProcessing* const eventProcessing,
				                           const RBAContent* const viewContent);
  std::unique_ptr<RBAResultSet>& getCurResultSet();
  std::unique_ptr<RBAResultSet>& getPreResultSet();
  RBAContentStatusType getStatusType(const RBAContent* const content) const;
  bool isStandby(const RBAContent* const content) const;
  bool hasBeenCanceled(const RBAContent* const content) const;
  bool hasBeenPreCanceled(const RBAContent* const content) const;
  bool hasBeenDisplayed(const RBAContent* const content) const;
  bool hasBeenPreDisplayed(const RBAContent* const content) const;

  /// @brief Update status of Content
  /// @details Update the status based on the request status, 
  ///          output status, and status at the time of request of the content
  /// @param[in] content Content to be updated
  void updateStatus(const RBAContent* const content);

  std::unordered_map<const RBAContent*, RBAContentStatus>* getCurStatus() const;
  std::set<const RBASceneImpl*>& getDifferentConditionScenes() const;
#ifdef RBA_USE_LOG
  void addFailedConstraint(const RBAConstraint* constraint);
  const std::list<const RBAConstraint*>& getFailedConstraints() const;
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<RBAResultSet> curResultSet_;
  std::unique_ptr<RBAResultSet> preResultSet_;
  mutable std::list<std::unique_ptr<RBAViewAction>> viewActions_;
  mutable std::list<const RBAViewAction*> viewActionsForPublicUse_;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  const RBAArbitratorImpl* arb_;
  RBAResultStatusType statusType_;
  std::string log_;

};

}

#endif
