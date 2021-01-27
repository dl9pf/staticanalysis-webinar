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

/// ConstraintInfo (Constraint expression Information) class header

#ifndef RBACONSTRAINTINFO_HPP
#define RBACONSTRAINTINFO_HPP

#include <cstdint>
#include <memory>
#include <set>
#include <vector>
#include "RBAExecuteResult.hpp"
#include "RBADllExport.hpp"

namespace rba {

class RBAAllocatable;
class RBAExpression;

class DLL_EXPORT RBAConstraintInfo
{
public:
  RBAConstraintInfo()=default;
  RBAConstraintInfo(const RBAConstraintInfo&)=delete;
  RBAConstraintInfo(const RBAConstraintInfo&&)=delete;
  RBAConstraintInfo& operator=(const RBAConstraintInfo&)=delete;
  RBAConstraintInfo& operator=(const RBAConstraintInfo&&)=delete;
  virtual ~RBAConstraintInfo()=default;

public:
  void setExpression(const RBAExpression* const expression);
  const RBAExpression* getExpression() const;
  void addOperandAllocatable(const RBAAllocatable* const operandAllocatable);
  void setResult(const RBAExecuteResult result);
  RBAConstraintInfo* getChild(const std::uint32_t index) const;
  void setChild(const std::shared_ptr<RBAConstraintInfo> info);
  void addTrueAllocatable(const RBAAllocatable* const allocatable);
  void addFalseAllocatable(const RBAAllocatable* const allocatable);
  void addTrueAllocatableFromOperand();
  void addFalseAllocatableFromOperand();
  void clearFalseAllocatable();
  const bool isImplies() const;
  void clear();

  bool isExceptionBeforeArbitrate() const;
  void setExceptionBeforeArbitrate(const bool exceptionBeforeArbitrate);

  /// @brief Determine the need for re-arbitration
  /// @param [in] allocatable Allcatable druing arbitration
  /// @param [in] isImplies Whether the constraint expression contains 
  ///                       implication syntax.
  /// @return Necessity of re-arbitration (true: need / false: No need)
  bool needsRearbitrationFor(const RBAAllocatable* const allocatable,
                             bool isImplies = false) const;

  bool needsReRearbitrationFor(const RBAAllocatable* const allocatable) const;
  void collectRearbitrationTargetFor(const RBAAllocatable* const allocatable,
				     std::set<const RBAAllocatable*>& targets,
				     const bool isNot) const;
  void collectTrueAllocatables(std::set<const RBAAllocatable*>& allocatables) const;
  void collectFalseAllocatables(std::set<const RBAAllocatable*>& allocatables) const;
  bool contains(const RBAAllocatable* const allocatable) const;
  bool isTrue() const;
  bool isFalse() const;

  /// @brief Extraction of affected Area/Zone
  /// @param [in] isRevert Negative context (true: inside / false: outside)
  /// @param [out] affectAllocatables List of affected Allcatable
  /// @param [out] collecting Collection target context
  ///                         (true: inside / false: outside)
  /// @param [out] forObject ReferenceObject context
  ///                        (true: inside / false: outside)
  /// @return Necessity of re-arbitration (true: need / false: No need)
  void collectAffectedAllocatables(
      const bool isRevert, std::set<const RBAAllocatable*>& affectAllocatables,
      const bool collecting,
      const bool forObject);

private:
  bool isRevert() const;
  bool isSizeOperator() const;

private:
  bool exceptionBeforeArbitrate_ {false};
  const RBAExpression* expression_ {nullptr};
  RBAExecuteResult result_ {RBAExecuteResult::SKIP};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::set<const RBAAllocatable*> trueAllocatables_;
  std::set<const RBAAllocatable*> falseAllocatables_;
  std::set<const RBAAllocatable*> operandAllocatable_;
  // use to respond with an empty set
  const std::set<const RBAAllocatable*> emptyAllocatables_;
  mutable std::vector<std::shared_ptr<RBAConstraintInfo>> children_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

}

#endif
