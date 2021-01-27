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
 * HasComeLaterThan class
 */

#include "RBAHasComeLaterThan.hpp"

#include "RBAContent.hpp"
#include "RBAArbitratorImpl.hpp"
#include "RBAExpressionVisitor.hpp"
#include "RBALogManager.hpp"
#include "RBAModelElementType.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

void RBAHasComeLaterThan::accept(RBAExpressionVisitor& visitor)
{
  visitor.visit(*this);
}

RBAModelElementType
RBAHasComeLaterThan::getModelElementType() const
{
  return RBAModelElementType::HasComeLater;
}

bool
RBAHasComeLaterThan::executeCore(RBAConstraintInfo* info,
				     RBAArbitratorImpl* arb) const
{
  // Add itself to the constraint hierarchy for coverage
  LOG_addHierarchy(LOG_getSymbol());

  bool isResult {false};
  // pop the Content of left hand side expresion
  RBAConstraintInfo* const leftInfo {info->getChild(0U)};
  const RBARuleObject* ruleObj {getLhsOperand()->getReferenceObject(leftInfo, arb)};
  const RBAContent* contentLhs {nullptr};
  if(ruleObj != nullptr) {
    contentLhs = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }

  // pop the Content of left hand side expresion
  RBAConstraintInfo* const rightInfo {info->getChild(1U)};
  ruleObj = getRhsOperand()->getReferenceObject(rightInfo, arb);
  const RBAContent* contentRhs {nullptr};
  if(ruleObj != nullptr) {
    contentRhs = dynamic_cast<const RBAContent*>(ruleObj->getRawObject());
  }

  if((contentLhs == nullptr) || (contentRhs == nullptr)) {
    info->setExceptionBeforeArbitrate(true);
  } else {
    if (!((arb->getResult()->isActive(contentLhs))
        && (arb->getResult()->isActive(contentRhs)))) {
      info->setExceptionBeforeArbitrate(true);
    }
    else if(contentLhs == contentRhs) {
      isResult = false;
    }
    else {
      isResult = arb->getResult()->isLater(contentLhs, contentRhs);
    }
  }
#ifdef RBA_USE_LOG
  std::string lhsName;
  std::string rhsName;
  std::string resultText;
  if(contentLhs == nullptr) {
    lhsName = "NULL";
  } else {
    lhsName = contentLhs->getElementName();
  }
  if (contentRhs == nullptr) {
    rhsName = "NULL";
  } else {
    rhsName = contentRhs->getElementName();
  }
  if (info->isExceptionBeforeArbitrate() == true ) {
    resultText = "is before arbitrate skip";
    LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
					RBAExecuteResult::SKIP);
  } else {
    resultText = RBALogManager::boolToString(isResult);
    if(isResult) {
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
					  RBAExecuteResult::TRUE);
    }
    else {
      LOG_coverageConstraintExpressionLog(LOG_getCoverageExpressionText(),
					  RBAExecuteResult::FALSE);
    }
  }
  LOG_arbitrateConstraintLogicLogLine(
      "      Content[" + lhsName + "] has come later than Content[" + rhsName + "] " + resultText);
#endif
  // Remove itself from the constraint hierarchy for coverage
  LOG_removeHierarchy();

  return isResult;
}

#ifdef RBA_USE_LOG
const std::string
RBAHasComeLaterThan::getSymbol() const
{
  return ".hasComeLaterThan";
}

const std::string
RBAHasComeLaterThan::getExpressionText() const
{
  RBAExpression* exprLhs = getLhsOperand();
  RBAExpression* exprRhs = getRhsOperand();
  return exprLhs->getExpressionText() + getSymbol()
    + "(" + exprRhs->getExpressionText() + ")";
}

const std::string
RBAHasComeLaterThan::getCoverageExpressionText() const
{
  RBAExpression* exprLhs = getLhsOperand();
  RBAExpression* exprRhs = getRhsOperand();
  return exprLhs->getCoverageExpressionText() + getSymbol()
    + "(" + exprRhs->getCoverageExpressionText() + ")";
}

RBAExpressionType
RBAHasComeLaterThan::getUnderlyingType() const
{
  return RBAExpressionType::BOOLEAN;
}
#endif

}
