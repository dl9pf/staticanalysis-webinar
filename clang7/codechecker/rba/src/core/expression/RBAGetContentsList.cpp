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
 * GetContentsList class definition file
 */

#include "RBAGetContentsList.hpp"

#include "RBAAllocatable.hpp"
#include "RBAContentSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAGetContentsList::accept(RBAExpressionVisitor& visitor)
{
  // This path is not used, because RBASceneAllocatableCollector, 
  // the only existing visitor as of now, does not accept content.
  // But, keep this because another visitor may accept, in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAGetContentsList::getModelElementType() const
{
  return RBAModelElementType::GetContentsList;
}

const RBARuleObject*
RBAGetContentsList::getReferenceObjectCore(RBAConstraintInfo* info,
                                           RBAArbitratorImpl* arb) const
{
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};

  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAAllocatable* allocatable {nullptr};
  if (ruleObj != nullptr) {
    allocatable = dynamic_cast<const RBAAllocatable*>(ruleObj->getRawObject());
  }
  // Indicates whether the content referenced by this constraint expression 
  // is the result of the previous arbitration result.

  if (leftInfo->isExceptionBeforeArbitrate() || (allocatable == nullptr)) {
    // As of now, this path is not used due to the following reasons.
    //  - The expression below GetContentsList is before arbitration
    //  - Constraint expression that returns null as allocatable 
    //    can not be described(specified) 
    // But, defined this for maintainability (especially expandability).
    info->setExceptionBeforeArbitrate(true);
    return nullptr;
  }

  return allocatable->getContentSet();
}

#ifdef RBA_USE_LOG
// At the moment, the arbitration FW cannot write a constraint expression 
// to call createHierarchy() of GetContentsList, 
// so it does not go through this path. 
// But, defined this for maintainability (especially expandability.
void
RBAGetContentsList::createHierarchy()
{
  // No operation because  it does not affect structure.
}
#endif

}
