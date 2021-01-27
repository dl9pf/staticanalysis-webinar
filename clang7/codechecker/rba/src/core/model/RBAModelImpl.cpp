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
/// @file  RBAModelmpl.cpp
/// @brief Model implementation class 

#include "RBAModelImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAAreaSet.hpp"
#include "RBAZoneSet.hpp"
#include "RBAViewContentSet.hpp"
#include "RBASoundContentSet.hpp"

namespace rba
{

const RBAContentState*
RBAModelImpl::findContentState(const std::string& stateName)
{
  const auto elem = findModelElementImpl(stateName);
  auto contentState = dynamic_cast<const RBAContentState*>(elem);
  if (contentState == nullptr) {
    const auto content = dynamic_cast<const RBAContent*>(elem);
    if (content != nullptr) {
      contentState = content->getStates().front();
    }
  }
  return contentState;
}
  
const RBAArea*
RBAModelImpl::findArea(const std::string& areaName) const
{
  return findAreaImpl(areaName);
}
  
const RBAViewContent*
RBAModelImpl::findViewContent(const std::string& contName) const
{
  return findViewContentImpl(contName);
}
  
const RBAViewContentState*
RBAModelImpl::findViewContentState(const std::string& stateName) const
{
  return findViewContentStateImpl(stateName);
}
  
const RBASize*
RBAModelImpl::findSize(const std::string& sizeName) const
{
  return findSizeImpl(sizeName);
}
  
const RBAZone*
RBAModelImpl::findZone(const std::string& zoneName) const
{
  return findZoneImpl(zoneName);
}
  
const RBASoundContent*
RBAModelImpl::findSoundContent(const std::string& contName) const
{
  return findSoundContentImpl(contName);
}
  
const RBASoundContentState*
RBAModelImpl::findSoundContentState(const std::string& stateName) const
{
  return findSoundContentStateImpl(stateName);
}
  
const RBAScene*
RBAModelImpl::findScene(const std::string& sceneName) const
{
  return findSceneImpl(sceneName);
}

const RBADisplay*
RBAModelImpl::findDisplay(const std::string& displayName) const
{
  return findDisplayImpl(displayName);
}

const RBAModelElement*
RBAModelImpl::findModelElement(const std::string& elementName) const
{
  return findModelElementImpl(elementName);
}

const std::list<const RBAArea*>&
RBAModelImpl::getAreas() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAArea is the base class of RBAAreaImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBAArea*>&>(getAreaImpls());
}

const std::list<const RBAViewContent*>&
RBAModelImpl::getViewContents() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAViewContent is the base class of 
  //  RBAViewContentImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBAViewContent*>&>(getViewContentImpls());
}
  
const std::list<const RBAViewContentState*>&
RBAModelImpl::getViewContentStates() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAViewContentState is the base class of 
  //  RBAViewContentStateImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBAViewContentState*>&>(getViewContentStateImpls());
}
  
const std::list<const RBASize*>&
RBAModelImpl::getSizes() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBASize is the base class of RBASizeImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBASize*>&>(getSizeImpls());
}

const std::list<const RBAZone*>&
RBAModelImpl::getZones() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAZone is the base class of RBAZoneImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBAZone*>&>(getZoneImpls());
}

const std::list<const RBASoundContent*>&
RBAModelImpl::getSoundContents() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBASoundContent is the base class of 
  //  RBASoundContentImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBASoundContent*>&>(getSoundContentImpls());
}
  
const std::list<const RBASoundContentState*>&
RBAModelImpl::getSoundContentStates() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBASoundContentState is the base class of 
  //  RBASoundContentStateImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBASoundContentState*>&>(getSoundContentStateImpls());
}
  
const std::list<const RBAScene*>&
RBAModelImpl::getScenes() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAScene is the base class of 
  //  RBASceneImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBAScene*>&>(getSceneImpls());
}

const std::list<const RBAAreaSet*>&
RBAModelImpl::getAreaSets() const
{
  return getAreaSetImpls();
}

const std::list<const RBAViewContentSet*>&
RBAModelImpl::getViewContentSets() const
{
  return getViewContentSetImpls();
}

const std::list<const RBAZoneSet*>&
RBAModelImpl::getZoneSets() const
{
  return getZoneSetImpls();
}

const std::list<const RBASoundContentSet*>&
RBAModelImpl::getSoundContentSets() const
{
  return getSoundContentSetImpls();
}

const std::list<const RBAPositionContainer*>&
RBAModelImpl::getPositionContainers() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAPositionContainer is the base class of 
  //  RBAPositionContainerImpl.
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBAPositionContainer*>&>(getPositionContainerImpls());
}

const std::list<const RBADisplay*>&
RBAModelImpl::getDisplays() const
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBADisplay is the base class of RBADisplayImpl. 
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<const std::list<const RBADisplay*>&>(getDisplayImpls());
}

std::list<RBAConstraint*>&
RBAModelImpl::getConstraints()
{
  // @Deviation (A5-2-4)
  // [Contents that deviate from the rules]
  //  reinterpret_cast shall not be used.
  // [Reason that there is no problem if the rule is deviated]
  //  There is no problem because RBAConstraint is the base class of 
  //  RBAConstraintImpl. 
  //  Since the conversion process is costly, it deviates because it hides 
  //  the internal structure.
  return reinterpret_cast<std::list<RBAConstraint*>&>(getConstraintImpls());
}

void RBAModelImpl::clearElementsStatus()
{
  for (auto& o : unnamedObjects_) {
    o->clearStatus();
  }
  for (auto& o : nameToObject_) {
    o.second->clearStatus();
  }
}

const RBAAllocatable*
RBAModelImpl::findAllocatable(const std::string& allocatableName) const
{
  auto it = nameToObject_.find(allocatableName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAAllocatable*>(it->second.get());
  }

  return nullptr;
}

const RBAContent*
RBAModelImpl::findContent(const std::string& contentName) const
{
  auto it = nameToObject_.find(contentName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAContent*>(it->second.get());
  }

  return nullptr;
}

const RBAAreaImpl*
RBAModelImpl::findAreaImpl(const std::string& areaName) const
{
  auto it = nameToObject_.find(areaName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAAreaImpl*>(it->second.get());
  }

  return nullptr;
}
  
const RBAViewContentImpl*
RBAModelImpl::findViewContentImpl(const std::string& contName) const
{
  auto it = nameToObject_.find(contName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAViewContentImpl*>(it->second.get());
  }

  return nullptr;
}
  
const RBAViewContentStateImpl*
RBAModelImpl::findViewContentStateImpl(const std::string& stateName) const
{
  const RBAViewContentStateImpl* ret {nullptr};
  if(RBAViewContentState::isUniqueName(stateName)) {
    auto it = nameToObject_.find(stateName);
    if(it != nameToObject_.end()) {
      ret = dynamic_cast<const RBAViewContentStateImpl*>(it->second.get());
    }
  }
  else {
    const RBAViewContentImpl* const content {findViewContentImpl(stateName)};
    if(content != nullptr) {
      const RBAContentState* const state {content->getStates().front()};
      ret = dynamic_cast<const RBAViewContentStateImpl*>(state);
    }
  }

  return ret;
}
  
const RBASizeImpl*
RBAModelImpl::findSizeImpl(const std::string& sizeName) const
{
  auto it = nameToObject_.find(sizeName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBASizeImpl*>(it->second.get());
  }

  return nullptr;
}
  
const RBAZoneImpl*
RBAModelImpl::findZoneImpl(const std::string& zoneName) const
{
  auto it = nameToObject_.find(zoneName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAZoneImpl*>(it->second.get());
  }

  return nullptr;
}
  
const RBASoundContentImpl*
RBAModelImpl::findSoundContentImpl(const std::string& contName) const
{
  auto it = nameToObject_.find(contName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBASoundContentImpl*>(it->second.get());
  }

  return nullptr;
}
  
const RBASoundContentStateImpl*
RBAModelImpl::findSoundContentStateImpl(const std::string& stateName) const
{
  const RBASoundContentStateImpl* ret {nullptr};
  if(RBASoundContentState::isUniqueName(stateName)) {
    auto it = nameToObject_.find(stateName);
    if(it != nameToObject_.end()) {
      ret = dynamic_cast<const RBASoundContentStateImpl*>(it->second.get());
    }
  }
  else {
    const RBASoundContentImpl* const content {findSoundContentImpl(stateName)};
    if(content != nullptr) {
      const RBAContentState* const state {content->getStates().front()};
      ret = dynamic_cast<const RBASoundContentStateImpl*>(state);
    }
  }

  return ret;
}
  
const RBASceneImpl*
RBAModelImpl::findSceneImpl(const std::string& sceneName) const
{
  auto it = nameToObject_.find(sceneName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBASceneImpl*>(it->second.get());
  }

  return nullptr;
}

const RBADisplayImpl*
RBAModelImpl::findDisplayImpl(const std::string& displayName) const
{
  auto it = nameToObject_.find(displayName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBADisplayImpl*>(it->second.get());
  }

  return nullptr;
}

const RBAModelElement*
RBAModelImpl::findModelElementImpl(const std::string& elementName) const
{
  auto it = nameToObject_.find(elementName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAModelElement*>(it->second.get());
  }

  return nullptr;
}

const std::list<const RBAAllocatable*>&
RBAModelImpl::getAllocatables() const
{
  return allocatables_;
}

const std::list<const RBAContent*>&
RBAModelImpl::getContents() const
{
  return contents_;
}

const std::list<const RBAContentState*>&
RBAModelImpl::getContentStates() const
{
  return contentStates_;
}

const std::list<const RBAAreaImpl*>&
RBAModelImpl::getAreaImpls() const
{
  return areas_;
}

const std::list<const RBAViewContentImpl*>&
RBAModelImpl::getViewContentImpls() const
{
  return viewContents_;
}
  
const std::list<const RBAViewContentStateImpl*>&
RBAModelImpl::getViewContentStateImpls() const
{
  return viewContentStates_;
}
  
const std::list<const RBASizeImpl*>&
RBAModelImpl::getSizeImpls() const
{
  return sizes_;
}

const std::list<const RBAZoneImpl*>&
RBAModelImpl::getZoneImpls() const
{
  return zones_;
}

const std::list<const RBASoundContentImpl*>&
RBAModelImpl::getSoundContentImpls() const
{
  return soundContents_;
}
  
const std::list<const RBASoundContentStateImpl*>&
RBAModelImpl::getSoundContentStateImpls() const
{
  return soundContentStates_;
}

const std::list<const RBASceneImpl*>&
RBAModelImpl::getSceneImpls() const
{
  return scenes_;
}

const std::list<const RBAPositionContainerImpl*>&
RBAModelImpl::getPositionContainerImpls() const
{
  return positionContainers_;
}

const std::list<const RBADisplayImpl*>&
RBAModelImpl::getDisplayImpls() const
{
  return displays_;
}

void
RBAModelImpl::createSortedAllocatables()
{
  if(!(sortedAllocatables_.empty())) {
    sortedAllocatables_.clear();
  }

  for(auto& alloc : allocatables_) {
    sortedAllocatables_.push_back(const_cast<RBAAllocatable*>(alloc));
  }
  sortedAllocatables_.sort(&RBAAllocatable::compare);

  std::int32_t index{0};
  for(RBAAllocatable* const allocatable : sortedAllocatables_) {
    allocatable->setIndex(index);
    index++;
  }
}

std::list<RBAAllocatable*>&
RBAModelImpl::getSortedAllocatables()
{
  return sortedAllocatables_;
}

RBAConstraintImpl*
RBAModelImpl::findConstraintImpl(const std::string& consName) const
{
  auto it = nameToObject_.find(consName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<RBAConstraintImpl*>(it->second.get());
  }

  return nullptr;
}

const RBAAreaSet*
RBAModelImpl::findAreaSetImpl(const std::string& areaSetName) const
{
  auto it = nameToObject_.find(areaSetName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAAreaSet*>(it->second.get());
  }

  return nullptr;
}

const RBAZoneSet*
RBAModelImpl::findZoneSetImpl(const std::string& zoneSetName) const
{
  auto it = nameToObject_.find(zoneSetName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAZoneSet*>(it->second.get());
  }

  return nullptr;
}

const RBAViewContentSet*
RBAModelImpl::findViewContentSetImpl(const std::string& contSetName) const
{
  auto it = nameToObject_.find(contSetName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBAViewContentSet*>(it->second.get());
  }

  return nullptr;
}

const RBASoundContentSet*
RBAModelImpl::findSoundContentSetImpl(const std::string& contSetName) const
{
  auto it = nameToObject_.find(contSetName);
  if(it != nameToObject_.end()) {
    return dynamic_cast<const RBASoundContentSet*>(it->second.get());
  }

  return nullptr;
}

const RBAPositionContainerImpl*
RBAModelImpl::findPositionContainerImpl(const std::string& areaName) const
{
  auto it = areaNameToPositionContainer_.find(areaName);
  if(it != areaNameToPositionContainer_.end()) {
    return dynamic_cast<const RBAPositionContainerImpl*>(it->second);
  }

  return nullptr;
}

/*
 * get list functions
 */

std::list<const RBAConstraintImpl*>&
RBAModelImpl::getConstraintImpls()
{
  return constraints_;
}

const std::list<const RBAAreaSet*>&
RBAModelImpl::getAreaSetImpls() const
{
  return areaSets_;
}

const std::list<const RBAZoneSet*>&
RBAModelImpl::getZoneSetImpls() const
{
  return zoneSets_;
}

const std::list<const RBAViewContentSet*>&
RBAModelImpl::getViewContentSetImpls() const
{
  return viewContentSets_;
}

const std::list<const RBASoundContentSet*>&
RBAModelImpl::getSoundContentSetImpls() const
{
  return soundContentSets_;
}

RBAModelElement*
RBAModelImpl::addModelElement(std::unique_ptr<RBAModelElement> newElement)
{
  RBAModelElement* const element {newElement.get()};
  unnamedObjects_.push_back(std::move(newElement));
  return element;
}

RBANamedElement*
RBAModelImpl::addNamedElement(std::unique_ptr<RBAModelElement> newElement)
{
  RBANamedElement* const element {dynamic_cast<RBANamedElement*>(newElement.get())};
  nameToObject_[element->getUniqueName()] = std::move(newElement);
  return element;
}

void
RBAModelImpl::addAllocatable(const RBAAllocatable* newAlloc)
{
  allocatables_.push_back(newAlloc);
  if(newAlloc->isArea()) {
    areas_.push_back(dynamic_cast<const RBAAreaImpl*>(newAlloc));
  }
  else if (newAlloc->isZone()) {
    zones_.push_back(dynamic_cast<const RBAZoneImpl*>(newAlloc));
  } else {
    ;
  }
}

void
RBAModelImpl::addContent(const RBAContent* newContent)
{
  contents_.push_back(newContent);
  if(newContent->isViewContent()) {
    viewContents_.push_back(dynamic_cast<const RBAViewContentImpl*>(newContent));
  }
  else if (newContent->isSoundContent()) {
    soundContents_.push_back(dynamic_cast<const RBASoundContentImpl*>(newContent));
  } else {
    ;
  }
}

void
RBAModelImpl::addContentState(const RBAContentState* newState)
{
  contentStates_.push_back(newState);
  if(newState->isViewContentState()) {
    viewContentStates_.push_back(dynamic_cast<const RBAViewContentStateImpl*>(newState));
  }
  else {
    soundContentStates_.push_back(dynamic_cast<const RBASoundContentStateImpl*>(newState));
  }
}

void
RBAModelImpl::addAreaSet(const RBAAreaSet* newAreaSet)
{
  areaSets_.push_back(newAreaSet);
}

void
RBAModelImpl::addZoneSet(const RBAZoneSet* newZoneSet)
{
  zoneSets_.push_back(newZoneSet);
}

void
RBAModelImpl::addConstraint(const RBAConstraintImpl* newConstraint)
{
  constraints_.push_back(newConstraint);
}

void
RBAModelImpl::addViewContentSet(const RBAViewContentSet* newContentSet)
{
  viewContentSets_.push_back(newContentSet);
}

void
RBAModelImpl::addSoundContentSet(const RBASoundContentSet* newContentSet)
{
  soundContentSets_.push_back(newContentSet);
}

void
RBAModelImpl::addScene(const RBASceneImpl* newScene)
{
  scenes_.push_back(newScene);
}

RBASizeImpl*
RBAModelImpl::addSizeInstance(const std::string& ownerName,
                              std::unique_ptr<RBAModelElement> newSize)
{
  RBASizeImpl* sizeImpl {dynamic_cast<RBASizeImpl*>(newSize.get())};
  sizes_.push_back(sizeImpl);
  nameToObject_[ownerName+std::string("/")+sizeImpl->getName()]
    = std::move(newSize);
  return sizeImpl;
}

void
RBAModelImpl::addPositionContainer(const RBAPositionContainerImpl* newPositionContainer)
{
  positionContainers_.push_back(newPositionContainer);
  areaNameToPositionContainer_[newPositionContainer->getArea()->getName()]
    = newPositionContainer;
}

void
RBAModelImpl::addDisplay(const RBADisplayImpl* newDisplay)
{
  displays_.push_back(newDisplay);
}

void
RBAModelImpl::addLabeledElement(const std::string& label,
                                RBAModelElement* element)
{
  labelToElements_[label].push_back(element);
}

void
RBAModelImpl::addLabeledConstraint(const std::string& label,
                                   RBAAbstractConstraint* constraint)
{
  labelToConstraints_[label].push_back(constraint);
}

const std::list<const RBAModelElement*>
RBAModelImpl::getLabeledElements(const std::string& label) const
{
  auto it = labelToElements_.find(label);
  if(it != labelToElements_.end()) {
    return it->second;
  }

  const std::list<const RBAModelElement*> emp;
  return emp;
}

const std::list<RBAAbstractConstraint*>
RBAModelImpl::getLabeledConstraints(const std::string& label) const
{
  auto it = labelToConstraints_.find(label);
  if(it != labelToConstraints_.end()) {
    return it->second;
  }

  const std::list<RBAAbstractConstraint*> emp;
  return emp;
}

const RBAModelElement*
RBAModelImpl::findLabeledElement(const std::string& label,
                                 const std::string& name) const
{
  const std::list<const RBAModelElement*> elems {getLabeledElements(label)};
  for(const RBAModelElement* const elem : elems) {
    if(dynamic_cast<const RBANamedElement*>(elem)->getElementName() == name) {
      return elem;
    }
  }

  return nullptr;
}

void
RBAModelImpl::addAffectedAllocsMap(const RBAModelElement* const owner, RBAAllocatable* const alloc)
{
  affectedAllocsMap_[owner].push_back(alloc);
}

const std::list<RBAAllocatable*>*
RBAModelImpl::getAffectedAllocs(const RBAModelElement* const owner)
{
  auto itr = affectedAllocsMap_.find(owner);
  if (itr != affectedAllocsMap_.end()) {
    return &itr->second;
  }
  return nullptr;
}

}
