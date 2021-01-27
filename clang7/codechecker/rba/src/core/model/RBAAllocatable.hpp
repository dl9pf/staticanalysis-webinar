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
 * Allocatable class header
 */

#ifndef RBAALLOCATABLE_HPP
#define RBAALLOCATABLE_HPP

#include "RBAAbstractAllocatable.hpp"
#include "RBAArbitrationPolicy.hpp"

namespace rba
{

class RBAViewContent;
class RBANotificationChain;
class RBAContentState;
class RBAConstraintImpl;
enum class RBAConstraintMap : std::uint8_t;

class DLL_EXPORT RBAAllocatable : public RBAAbstractAllocatable
{
public:
  explicit RBAAllocatable(const std::string& name="");
  RBAAllocatable(const RBAAllocatable&)=delete;
  RBAAllocatable(const RBAAllocatable&&)=delete;
  RBAAllocatable& operator=(const RBAAllocatable&)=delete;
  RBAAllocatable& operator=(const RBAAllocatable&&)=delete;
  virtual ~RBAAllocatable()=default;

public:
  void clearStatus() override;
  virtual bool isArea() const;
  virtual bool isZone() const;
  RBAArbitrationPolicy getAllocatableArbitrationPolicy() const;
  void setArbitrationPolicy(const RBAArbitrationPolicy newPolicy);
  std::int32_t getVisibility() const;
  void setVisibility(const std::int32_t newVisibility);
  const std::list<const RBAAllocatable*>& getAllocatablesAffectedByYou() const;
  void clearAllocatablesAffectedByYou();
  void addAllocatableWhichHasBeenAffectedByYou(const RBAAllocatable* const allocatable);
  void removeAffectAllocatable(const RBAAllocatable* const allocatable);
  void clearAffectAllocatable();
  virtual void clearChecked();
  std::int32_t getIndex() const;
  void setIndex(const std::int32_t newIndex);

  static bool compare(const RBAAllocatable* const arg0, const RBAAllocatable* const arg1);
  static bool compareIndex(const RBAAllocatable* const arg0, const RBAAllocatable* const arg1);
  const static RBAArbitrationPolicy ARBITRATION_POLICY_EDEFAULT =
                                    RBAArbitrationPolicy::DEFAULT;
  void addConstraint(RBAConstraintImpl* const constraint, const RBAConstraintMap& kind);
  std::list<RBAConstraintImpl*>& getConstraints();
  std::list<RBAConstraintImpl*>& getHiddenTrueCheckConstraints();
  std::list<RBAConstraintImpl*>& getHiddenFalseCheckConstraints();
  std::list<RBAConstraintImpl*>& getAttenuateTrueCheckConstraints();
  std::list<RBAConstraintImpl*>& getAttenuateFalseCheckConstraints();
  bool hasConstraint(const RBAConstraintImpl* const constraint) const;

  bool isChecked() const;
  void setChecked(const bool checked);
  bool isHiddenChecked() const;
  void setHiddenChecked(const bool hiddenChecked);
  bool isAttenuateChecked() const;
  void setAttenuateChecked(const bool attenuateChecked=false);
  bool isAttenuated() const;
  void setAttenuated(const bool attenuated=false);
  bool isHidden() const;
  void setHidden(const bool hidden=false);
  const RBAContentState* getState() const;
  void setState(const RBAContentState* const state);

  // Log
#ifdef RBA_USE_LOG
  virtual std::string getSymbol() const;
  virtual std::string getHiddenSymbol() const;
  std::string getArbitrationPolicyString() const;
  std::string getVisibilityString() const;
#endif

 private:
  void addConstraintImpl(RBAConstraintImpl* const constraint,
                         std::list<RBAConstraintImpl*>& constraints);

protected:
  // Zone should be a Z-order below the minimum Area
  const static std::int32_t ZONE_ZORDER = -2;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAAllocatable*> allocatablesAffectedByThisAllocatable_;
  std::list<RBAConstraintImpl*> constraints_;
  std::list<RBAConstraintImpl*> hiddenTrueCheckConstraints_;
  std::list<RBAConstraintImpl*> hiddenFalseCheckConstraints_;
  std::list<RBAConstraintImpl*> attenuateTrueCheckConstraints_;
  std::list<RBAConstraintImpl*> attenuateFalseCheckConstraints_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  RBAArbitrationPolicy arbitrationPolicy_{ARBITRATION_POLICY_EDEFAULT};
  std::int32_t visibility_ {0};
  std::int32_t index_ {0};
  const RBAContentState * state_ {nullptr};
  bool hiddenChecked_ {false};
  bool checked_ {false};
  bool attenuateChecked_ {false};
  bool hidden_ {false};
  bool attenuated_ {false};
};

}

#endif
