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
/// @file  RBAModelImplhpp
/// @brief Model implementaion class header

#ifndef RBAMODELIMPL_HPP
#define RBAMODELIMPL_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include "RBAAreaImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBADisplayImpl.hpp"
#include "RBAExpression.hpp"
#include "RBAModel.hpp"
#include "RBAModelElement.hpp"
#include "RBAPositionContainerImpl.hpp"
#include "RBASceneImpl.hpp"
#include "RBASizeImpl.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBASoundContentStateImpl.hpp"
#include "RBAVariable.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBAZoneImpl.hpp"

namespace rba
{

class RBAAreaSet;
class RBAZoneSet;
class RBAViewContentSet;
class RBASoundContentSet;

class DLL_EXPORT RBAModelImpl : public RBAModel
{
public:
  RBAModelImpl()=default;
  RBAModelImpl(const RBAModelImpl&)=delete;
  RBAModelImpl(const RBAModelImpl&&)=delete;
  RBAModelImpl& operator=(const RBAModelImpl&)=delete;
  RBAModelImpl& operator=(const RBAModelImpl&&)=delete;
  virtual ~RBAModelImpl()=default;

public:
  const RBAArea* findArea(const std::string& areaName) const override;
  const RBAViewContent* findViewContent(const std::string& contName) const override;
  const RBAViewContentState* findViewContentState(const std::string& stateName) const override;
  const RBASize* findSize(const std::string& sizeName) const override;
  const RBAZone* findZone(const std::string& zoneName) const override;
  const RBASoundContent* findSoundContent(const std::string& contName) const override;
  const RBASoundContentState* findSoundContentState(const std::string& stateName) const override;
  const RBAScene* findScene(const std::string& sceneName) const override;
  const RBADisplay* findDisplay(const std::string& displayName) const override;
  const RBAModelElement* findModelElement(const std::string& elementName) const;

  const std::list<const RBAArea*>& getAreas() const override;
  const std::list<const RBAViewContent*>& getViewContents() const override;
  const std::list<const RBAViewContentState*>& getViewContentStates() const override;
  const std::list<const RBASize*>& getSizes() const override;
  const std::list<const RBAZone*>& getZones() const override;
  const std::list<const RBASoundContent*>& getSoundContents() const override;
  const std::list<const RBASoundContentState*>& getSoundContentStates() const override;
  const std::list<const RBAScene*>& getScenes() const override;
  const std::list<const RBAAreaSet*>& getAreaSets() const;
  const std::list<const RBAViewContentSet*>& getViewContentSets() const;
  virtual const std::list<const RBAZoneSet*>& getZoneSets() const;
  virtual const std::list<const RBASoundContentSet*>& getSoundContentSets() const;
  const std::list<const RBAPositionContainer*>& getPositionContainers() const override;
  const std::list<const RBADisplay*>& getDisplays() const override;
  std::list<RBAConstraint*>& getConstraints();

  virtual void clearElementsStatus();
  virtual const RBAContentState* findContentState(const std::string& stateName);
  const RBAAllocatable* findAllocatable(const std::string& allocatableName) const;
  const RBAContent* findContent(const std::string& contentName) const;
  virtual const RBAAreaImpl* findAreaImpl(const std::string& areaName) const;
  virtual const RBAViewContentImpl* findViewContentImpl(const std::string& contName) const;
  virtual const RBAViewContentStateImpl* findViewContentStateImpl(const std::string& stateName) const;
  virtual const RBASizeImpl* findSizeImpl(const std::string& sizeName) const;
  virtual const RBAZoneImpl* findZoneImpl(const std::string& zoneName) const;
  virtual const RBASoundContentImpl* findSoundContentImpl(const std::string& contName) const;
  virtual const RBASoundContentStateImpl* findSoundContentStateImpl(const std::string& stateName) const;
  virtual const RBASceneImpl* findSceneImpl(const std::string& sceneName) const;
  virtual const RBADisplayImpl* findDisplayImpl(const std::string& displayName) const;
  virtual const RBAModelElement* findModelElementImpl(const std::string& elementName) const;

  virtual const std::list<const RBAAllocatable*>& getAllocatables() const;
  virtual const std::list<const RBAContent*>&  getContents() const;
  virtual const std::list<const RBAContentState*>& getContentStates() const;

  virtual const std::list<const RBAAreaImpl*>& getAreaImpls() const;
  virtual const std::list<const RBAViewContentImpl*>& getViewContentImpls() const;
  virtual const std::list<const RBAViewContentStateImpl*>& getViewContentStateImpls() const;
  virtual const std::list<const RBASizeImpl*>& getSizeImpls() const;
  virtual const std::list<const RBAZoneImpl*>& getZoneImpls() const;
  virtual const std::list<const RBASoundContentImpl*>& getSoundContentImpls() const;
  virtual const std::list<const RBASoundContentStateImpl*>& getSoundContentStateImpls() const;
  virtual const std::list<const RBASceneImpl*>& getSceneImpls() const;
  virtual const std::list<const RBAPositionContainerImpl*>& getPositionContainerImpls() const;
  virtual const std::list<const RBADisplayImpl*>& getDisplayImpls() const;

  virtual void createSortedAllocatables();

  virtual RBAConstraintImpl* findConstraintImpl(const std::string& consName) const;
  virtual const RBAAreaSet* findAreaSetImpl(const std::string& areaSetName) const;
  virtual const RBAZoneSet* findZoneSetImpl(const std::string& zoneSetName) const;
  virtual const RBAViewContentSet* findViewContentSetImpl(const std::string& contSetName) const;
  virtual const RBASoundContentSet* findSoundContentSetImpl(const std::string& contSetName) const;
  virtual const RBAPositionContainerImpl* findPositionContainerImpl(const std::string& areaName) const;

  virtual std::list<const RBAConstraintImpl*>& getConstraintImpls();
  virtual const std::list<const RBAAreaSet*>& getAreaSetImpls() const;
  virtual const std::list<const RBAZoneSet*>& getZoneSetImpls() const;
  virtual const std::list<const RBAViewContentSet*>& getViewContentSetImpls() const;
  virtual const std::list<const RBASoundContentSet*>& getSoundContentSetImpls() const;
  // Do not set to const because the internal state is changed by arbitration 
  // processing
  virtual std::list<RBAAllocatable*>& getSortedAllocatables();

  virtual RBAModelElement* addModelElement(std::unique_ptr<RBAModelElement> newElement);
  virtual RBANamedElement* addNamedElement(std::unique_ptr<RBAModelElement> newElement);
  virtual RBASizeImpl* addSizeInstance(const std::string& ownerName,
                                       std::unique_ptr<RBAModelElement> newSize);

  virtual void addAllocatable(const RBAAllocatable* newAlloc);
  virtual void addContent(const RBAContent* newContent);
  virtual void addContentState(const RBAContentState* newState);
  virtual void addAreaSet(const RBAAreaSet* newAreaSet);
  virtual void addZoneSet(const RBAZoneSet* newZoneSet);
  virtual void addConstraint(const RBAConstraintImpl* newConstraint);
  virtual void addViewContentSet(const RBAViewContentSet* newContentSet);
  virtual void addSoundContentSet(const RBASoundContentSet* newContentSet);
  virtual void addScene(const RBASceneImpl* newScene);
  virtual void addPositionContainer(const RBAPositionContainerImpl* newPositionContainer);
  virtual void addDisplay(const RBADisplayImpl* newDisplay);
  /// Add element with label
  virtual void addLabeledElement(const std::string& label,
                                 RBAModelElement* element);
  /// Add constraint expression with label
  virtual void addLabeledConstraint(const std::string& label,
                                    RBAAbstractConstraint* constraint);

  /// Add element list with label
  virtual const std::list<const RBAModelElement*> getLabeledElements(const std::string& label) const;
  /// Add constraint expression list with label
  virtual const std::list<RBAAbstractConstraint*> getLabeledConstraints(const std::string& label) const;
  /// Search element with label
  virtual const RBAModelElement* findLabeledElement(const std::string& label,
                                                    const std::string& name) const;

  // Add to Allcatable map
  void addAffectedAllocsMap(const RBAModelElement* const owner, RBAAllocatable* const alloc);
  // Get affected Allocatable list
  const std::list<RBAAllocatable*>* getAffectedAllocs(const RBAModelElement* const owner);
  

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAAllocatable*> allocatables_;
  std::list<const RBAContent*> contents_;
  std::list<const RBAContentState*> contentStates_;
  std::list<const RBAAreaImpl*> areas_;
  std::list<const RBAViewContentImpl*> viewContents_;
  std::list<const RBAViewContentStateImpl*> viewContentStates_;
  std::list<const RBASizeImpl*> sizes_;
  std::list<const RBAZoneImpl*> zones_;
  std::list<const RBASoundContentImpl*> soundContents_;
  std::list<const RBASoundContentStateImpl*> soundContentStates_;
  std::list<const RBAConstraintImpl*> constraints_;
  std::list<const RBAAreaSet*> areaSets_;
  std::list<const RBAZoneSet*> zoneSets_;
  std::list<const RBASceneImpl*> scenes_;
  std::list<const RBAViewContentSet*> viewContentSets_;
  std::list<const RBASoundContentSet*> soundContentSets_;
  std::list<const RBAPositionContainerImpl*> positionContainers_;
  std::list<const RBADisplayImpl*> displays_;

  // Do not set to const because the internal state is changed by arbitration 
  // processing
  std::list<RBAAllocatable*> sortedAllocatables_;

  // For storing objects not managed by name
  // expression, variable are applicable.
  std::list<std::unique_ptr<RBAModelElement>> unnamedObjects_;

  // Managing RBARuleObject and RBASize
  std::unordered_map<std::string, std::unique_ptr<RBAModelElement>> nameToObject_;
  // Position container is managed by map paired with Area name
  std::unordered_map<std::string, const RBAPositionContainerImpl*> areaNameToPositionContainer_;

  // Managing Labeled element model for extensions
  std::unordered_map<std::string, std::list<const RBAModelElement*>> labelToElements_;
  // Managing Labeled Constraint Expressions for extensions
  std::unordered_map<std::string, std::list<RBAAbstractConstraint*>> labelToConstraints_;

  // Allocatable map
  std::unordered_map<const RBAModelElement*, std::list<RBAAllocatable*>> affectedAllocsMap_; 

#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
