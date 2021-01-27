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
 * GetAllocatables class definition file
 */

#include "RBAGetAllocatables.hpp"                                                       

#include "RBAContent.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBAModelElementType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void
RBAGetAllocatables::accept(RBAExpressionVisitor& visitor)
{
  // This path is not used, because RBASceneAllocatableCollector, 
  // the only existing visitor as of now, does not accept content.
  // But, keep this because another visitor may accept, in the future.
  visitor.visit(*this);
}

RBAModelElementType
RBAGetAllocatables::getModelElementType() const
{
  return RBAModelElementType::GetAllocatables;
}

const RBARuleObject*
RBAGetAllocatables::getReferenceObjectCore(RBAConstraintInfo* info,
                                           RBAArbitratorImpl* arb) const
{
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};

  const RBARuleObject* const ruleObj
    {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAContent* content {nullptr};
  if (ruleObj != nullptr) {
    content = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }

  if (content == nullptr) {
    if (leftInfo->isExceptionBeforeArbitrate()) {
      info->setExceptionBeforeArbitrate(true);
    }
    return nullptr;
  }

  return content->getAllocatableSet();
}

#ifdef RBA_USE_LOG
const std::string
RBAGetAllocatables::getSymbol() const
{
  return ".allocatables()";
}

const std::string
RBAGetAllocatables::getExpressionText() const
{
  return getLhsOperand()->getExpressionText() + getSymbol();
}
                                                    
// At the moment, the arbitration FW cannot write a constraint expression 
// to call createHierarchy() of GetAllocatables, 
// so it does not go through this path. 
// But, defined this for maintainability (especially expandability.
void
RBAGetAllocatables::createHierarchy()
{
  // No operation because  it does not affect structure.
}

#endif

}
