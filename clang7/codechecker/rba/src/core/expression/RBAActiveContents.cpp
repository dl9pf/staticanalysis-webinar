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
 * Select operator class definition
 */

#include <memory>
#include "RBAActiveContents.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAAllocatable.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"

namespace rba
{

RBAActiveContents::RBAActiveContents()
: RBAAllocatableOperator(),
  contentSet_{std::make_unique<RBAContentSet>()}
{
}

void
RBAActiveContents::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAActiveContents::getModelElementType() const
{
  return RBAModelElementType::ActiveContents;
}

const RBARuleObject*
RBAActiveContents::getReferenceObjectCore(RBAConstraintInfo* info, RBAArbitratorImpl* arb) const
{
  LOG_addHierarchy(LOG_getSymbol());
  const RBARuleObject* returnObj {nullptr};
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* const lhsObj {getLhsOperand()->getReferenceObject(leftInfo, arb)};

  if (leftInfo->isExceptionBeforeArbitrate()) {
    info->setExceptionBeforeArbitrate(true);
  }
  else if (lhsObj != nullptr) {
    contentSet_->clear();
    const RBAAllocatable* const alloc {dynamic_cast<const RBAAllocatable*>(lhsObj->getRawObject())};
#ifdef RBA_USE_LOG
    if (arb == nullptr) {
      // Follow this path when called from createHierarchy()
      returnObj = alloc->getContentSet();
    } else {
#endif
      for (auto& content : alloc->getInternalContents()) {
        if (alloc->isPrevious()) {
          if (arb->getResult()->isPreActive(content)) {
            contentSet_->addTarget(content);
          }
        } else {
          if (arb->getResult()->isActive(content)) {
            contentSet_->addTarget(content);
          }
        }
      }
      returnObj = contentSet_.get();
#ifdef RBA_USE_LOG
    }
#endif
  } else {
    ;
  }
#ifdef RBA_USE_LOG
  std::string objName = "NULL";
  if (returnObj != nullptr) {
    objName = returnObj->getElementName();
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      " + LOG_getExpressionText() + " is " + objName);
#endif
  LOG_removeHierarchy();
  return returnObj;
}
#ifdef RBA_USE_LOG
const std::string
RBAActiveContents::getSymbol() const
{
  return ".activeContents()";
}
#endif

}
