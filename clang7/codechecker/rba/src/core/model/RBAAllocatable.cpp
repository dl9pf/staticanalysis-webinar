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
 * Allocatable class implementation
 */

#include <algorithm>

#include "RBAAllocatable.hpp"
#include "RBAModelElementType.hpp"
#include "RBAViewContent.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAConstraintMap.hpp"

namespace rba
{

RBAAllocatable::RBAAllocatable(const std::string& name)
  : RBARuleObject{name},
    RBAAbstractAllocatable{name}
{
}

void RBAAllocatable::clearStatus()
{
  allocatablesAffectedByThisAllocatable_.clear();
  state_ = nullptr;
  hiddenChecked_ = false;
  checked_ = false;
  attenuateChecked_ = false;
  hidden_ = false;
  attenuated_ = false;
}

bool
RBAAllocatable::isArea() const
{
  return isModelElementType(RBAModelElementType::Area);
}

bool
RBAAllocatable::isZone() const
{
  return isModelElementType(RBAModelElementType::Zone);
}

RBAArbitrationPolicy
RBAAllocatable::getAllocatableArbitrationPolicy() const
{
  return arbitrationPolicy_;
}

void
RBAAllocatable::setArbitrationPolicy(const RBAArbitrationPolicy newPolicy)
{
  arbitrationPolicy_ = newPolicy;
}

std::int32_t
RBAAllocatable::getVisibility() const
{
  return visibility_;
}

void
RBAAllocatable::setVisibility(const std::int32_t newVisibility)
{
  visibility_ = newVisibility;
}
  
const std::list<const RBAAllocatable*>&
RBAAllocatable::getAllocatablesAffectedByYou() const
{
  return allocatablesAffectedByThisAllocatable_;
}

void
RBAAllocatable::clearAllocatablesAffectedByYou()
{
  return allocatablesAffectedByThisAllocatable_.clear();
}

void
RBAAllocatable::addAllocatableWhichHasBeenAffectedByYou(const RBAAllocatable* const allocatable)
{
  allocatablesAffectedByThisAllocatable_.push_back(allocatable);
}

void
RBAAllocatable::removeAffectAllocatable(const RBAAllocatable* const allocatable)
{
  const auto it = std::find(allocatablesAffectedByThisAllocatable_.begin(),
		      allocatablesAffectedByThisAllocatable_.end(), allocatable);
  if(it != allocatablesAffectedByThisAllocatable_.end()) {
    static_cast<void>(allocatablesAffectedByThisAllocatable_.erase(it));
  }
}

void
RBAAllocatable::clearAffectAllocatable()
{
  allocatablesAffectedByThisAllocatable_.clear();
}

void
RBAAllocatable::clearChecked()
{
  hiddenChecked_ = false;
  checked_ = false;
  attenuateChecked_ =false;
  hidden_ = false;
  attenuated_ = false;
}

std::int32_t
RBAAllocatable::getIndex() const
{
  return index_;
}

void
RBAAllocatable::setIndex(const std::int32_t newIndex)
{
  index_ = newIndex;
}

bool
RBAAllocatable::compare(const RBAAllocatable* const arg0, 
                        const RBAAllocatable* const arg1)
{
  const std::int32_t visibility0 {arg0->getVisibility()};
  const std::int32_t visibility1 {arg1->getVisibility()};
  // Do not swap because the front element is more visible than the rear element
  if(visibility0 > visibility1) {
    return true;
  }
  // Compare the Z orders because the front element and the rear element
  // have the same visibility.
  else if(visibility0 == visibility1) {
    std::int32_t zorder0{0};
    std::int32_t zorder1{0};
    if(arg0->isModelElementType(RBAModelElementType::Area)) {
      zorder0 = (dynamic_cast<const RBAAreaImpl*>(arg0))->getZorder();
      zorder1 = (dynamic_cast<const RBAAreaImpl*>(arg1))->getZorder();
    }
    else {
      zorder0 = ZONE_ZORDER;
      zorder1 = ZONE_ZORDER;
    }
    // Do not swap because the front element has a larger Z order than 
    // the rear element.
    if(zorder0 > zorder1) {
      return true;
    }
    // Do not swap because the Z order of the front element and the rear element 
    // is the same
    else if(zorder0 == zorder1) {
      return false;
    }
    // Swap because the front element has a smaller Z order than 
    // the rear element.
    else {
      return false;
    }
  }
  // Replace because the front element is less visible than 
  // the rear element.
  else {
    return false;
  }
}

bool
RBAAllocatable::compareIndex(const RBAAllocatable* const arg0,
			     const RBAAllocatable* const arg1)
{
  return arg0->getIndex() < arg1->getIndex();
}

void
RBAAllocatable::addConstraint(RBAConstraintImpl* const constraint,
                              const RBAConstraintMap& kind)
{
  if (kind == RBAConstraintMap::CONTENT_ALLOCATE_CONSTRAINTS) {
    addConstraintImpl(constraint, constraints_);
  } else if (kind == RBAConstraintMap::HIDDEN_TRUE_CHECK_CONSTRAINTS) {
    addConstraintImpl(constraint, hiddenTrueCheckConstraints_);
  } else if (kind == RBAConstraintMap::HIDDEN_FALSE_CHECK_CONSTRAINTS) {
    addConstraintImpl(constraint, hiddenFalseCheckConstraints_);
  } else if (kind == RBAConstraintMap::ATTENUATE_TRUE_CHECK_CONSTRAINTS) {
    addConstraintImpl(constraint, attenuateTrueCheckConstraints_);
  } else {
    addConstraintImpl(constraint, attenuateFalseCheckConstraints_);
  }
}

std::list<RBAConstraintImpl*>&
RBAAllocatable::getConstraints()
{
  return constraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getHiddenTrueCheckConstraints()
{
  return hiddenTrueCheckConstraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getHiddenFalseCheckConstraints()
{
  return hiddenFalseCheckConstraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getAttenuateTrueCheckConstraints()
{
  return attenuateTrueCheckConstraints_;
}
std::list<RBAConstraintImpl*>& RBAAllocatable::getAttenuateFalseCheckConstraints()
{
  return attenuateFalseCheckConstraints_;
}

bool RBAAllocatable::hasConstraint(const RBAConstraintImpl* const constraint) const
{
  if ((std::find(constraints_.begin(), constraints_.end(), constraint)
      != constraints_.end())
      || (std::find(hiddenTrueCheckConstraints_.begin(),
                    hiddenTrueCheckConstraints_.end(), constraint)
          != hiddenTrueCheckConstraints_.end())
      || (std::find(hiddenFalseCheckConstraints_.begin(),
                    hiddenFalseCheckConstraints_.end(), constraint)
          != hiddenFalseCheckConstraints_.end())
      || (std::find(attenuateTrueCheckConstraints_.begin(),
                    attenuateTrueCheckConstraints_.end(), constraint)
          != attenuateTrueCheckConstraints_.end())
      || (std::find(attenuateFalseCheckConstraints_.begin(),
                    attenuateFalseCheckConstraints_.end(), constraint)
          != attenuateFalseCheckConstraints_.end())) {
    return true;
  }
  return false;
}

bool
RBAAllocatable::isChecked() const
{
  return checked_;
}

void
RBAAllocatable::setChecked(const bool checked)
{
  checked_ = checked;
}

bool
RBAAllocatable::isHiddenChecked() const
{
  return hiddenChecked_;
}

void
RBAAllocatable::setHiddenChecked(const bool hiddenChecked)
{
  hiddenChecked_ = hiddenChecked;
}

bool
RBAAllocatable::isAttenuateChecked() const
{
  return attenuateChecked_;
}

void
RBAAllocatable::setAttenuateChecked(const bool attenuateChecked)
{
  this->attenuateChecked_ = attenuateChecked;
}

bool
RBAAllocatable::isAttenuated() const
{
  return attenuated_;
}

void
RBAAllocatable::setAttenuated(const bool attenuated)
{
  this->attenuated_ = attenuated;
}

bool
RBAAllocatable::isHidden() const
{
  return hidden_;
}

void
RBAAllocatable::setHidden(const bool hidden)
{
  hidden_ = hidden;
}

const RBAContentState*
RBAAllocatable::getState() const
{
  return state_;
}

void
RBAAllocatable::setState(const RBAContentState* const state)
{
  state_ = state;
}

#ifdef RBA_USE_LOG
std::string
RBAAllocatable::getSymbol() const
{
  // This function is never called because the function of the derived class 
  // is called.
  return "Allocatable";
}

std::string
RBAAllocatable::getHiddenSymbol() const
{
  // This function is never called because the function of the derived class 
  // is called.
  return "Allocatable: Unsuppored operation exception";
}

std::string
RBAAllocatable::getArbitrationPolicyString() const
{
  std::string res;
  switch(arbitrationPolicy_) {
  case RBAArbitrationPolicy::FIRST_COME_FIRST:
    res = "FIRST_COME_FIRST";
    break;
  case RBAArbitrationPolicy::LAST_COME_FIRST:
    res = "LAST_COME_FIRST";
    break;
  case RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST:
    res = "PRIORITY_FIRST_COME_FIRST";
    break;
  case RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST:
    res = "PRIORITY_LAST_COME_FIRST";
    break;
  default:
    res = "DEFAULT";
    break;
  }

  return res;
}

std::string
RBAAllocatable::getVisibilityString() const
{
  return std::to_string(visibility_);
}
#endif

void
RBAAllocatable::addConstraintImpl(RBAConstraintImpl* const constraint,
                                  std::list<RBAConstraintImpl*>& constraints)
{
  if (std::find(constraints.begin(), constraints.end(), constraint)
      == constraints.end()) {
    constraints.push_back(constraint);
  }
}

}
