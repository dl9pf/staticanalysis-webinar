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
 * Coverage Log class definition file
 */

#include <algorithm>
#include <sstream>
#include "RBACoverageLog.hpp"

#include "RBAExpression.hpp"
#include "RBALog.hpp"
#include "RBAAbstractConstraint.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBAILogCollector.hpp"
#include "RBAExpressionType.hpp"
#include "RBAConstraintInfo.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
const std::string RBACoverageLog::SEP = ",";
const std::string RBACoverageLog::EXP_SEP = "\t";
const std::string RBACoverageLog::START = "START";
const std::string RBACoverageLog::END = "END";
const std::string RBACoverageLog::EXPRESSION = "EXPRESSION";
const std::string RBACoverageLog::CONSTRAINT = "Constraint";
const std::string RBACoverageLog::RULE = "Rule";

/**
 * Add request log in one line
 *
 * @param message log message
 */
void
RBACoverageLog::addRequestLogLine(const std::string& message)
{
  notify("#Request#" + message);
}

/**
 * Add allocate setting log in one line
 *
 * @param message log 
 */
void
RBACoverageLog::addPrevResultLogLine(const std::string& message)
{
  notify("#PrevResult#" + message);
}

/**
 * Add result log in one line
 *
 * @param message
 */
void
RBACoverageLog::addResultLogLine(const std::string& message)
{
  notify("#Result#" + message);
}

void
RBACoverageLog::addStartLogLine(const std::string& log)
{
  notify(log);
}

void
RBACoverageLog::addCoverageLogCollector(RBAILogCollector* collector)
{
  collectors_.insert(collector);
}

void
RBACoverageLog::removeCoverageLogCollector(RBAILogCollector* collector)
{
  auto it = std::find(collectors_.begin(), collectors_.end(), collector);
  if(it != collectors_.end()) {
    collectors_.erase(it);
  }
}

/**
 * Add "Constraint" log in one line
 *
 * @param message
 */
void
RBACoverageLog::addConstraintLogLine(const std::string& message)
{
  notify("#Constraint#" + message);
}

/**
 * Add "Constraint" start log
 *
 * @param constraint
 */
void
RBACoverageLog::addConstraintStartLog(const RBAAbstractConstraint* element)
{
  std::string isRuntime = "t";
  std::string eleName = element->getElementName();
  if(element->isConstraint()) {
    const RBAConstraintImpl* constraint
      = dynamic_cast<const RBAConstraintImpl*>(element);
    if(!constraint->isRuntime()) {
      isRuntime = "f";
    }
  }
  addConstraintLogLine(START + SEP + eleName + SEP + isRuntime);
}

/**
 * Add "Constraint" finish log
 *
 * @param constraint
 */
void
RBACoverageLog::addConstraintEndLog(const RBAAbstractConstraint* element)
{
  addConstraintLogLine(END);
}

/**
 * Add "Constraint expression" execution log
 *
 * @param expressionText
 * @param result
 */
void
RBACoverageLog::addConstraintExpressionLog(
    const std::string& expressionText, RBAExecuteResult result)
{
  std::string resultMsg;
  if (RBAExecuteResult::TRUE == result) {
    resultMsg = "t";
  } else if (RBAExecuteResult::FALSE == result) {
    resultMsg = "f";
  } else if (RBAExecuteResult::EXE == result) {
    resultMsg = "e";
  } else if (RBAExecuteResult::NOTEXE == result) {
    resultMsg = "ne";
  } else {
    resultMsg = "skip";
  }
  addConstraintLogLine(
      EXPRESSION + EXP_SEP + getHierarchy() + EXP_SEP + expressionText + EXP_SEP
          + resultMsg);
}

/**
 * Add "Constraint expression" execution log (For Action)
 *
 * @param expressionText
 */
void
RBACoverageLog::addConstraintExpressionLog(const std::string& expressionText)
{
  addConstraintLogLine(EXPRESSION + EXP_SEP +
		       getHierarchy() + EXP_SEP +
		       expressionText);
}

/**
 * Add request cancellation log in one line
 *
 * @param message
 */
void
RBACoverageLog::addCanceledRequestLogLine(const std::string& message)
{
  notify("#CanceledRequest#" + message);
}

/**
 * Add constraint structure log in one line
 *
 * @param message
 */
void
RBACoverageLog::addHierarchyOfConstraintLogLine(const std::string& message)
{
  notify("#HierarchyOfConstraint#" + message);
}

/**
 * Add constraint structure start log in one line
 *
 * @param message
 */
void

RBACoverageLog::
addHierarchyOfConstraintStartLog(const RBAAbstractConstraint* element)
{
  std::string isRuntime = "t";
  std::string type = CONSTRAINT;
  std::string eleName = element->getElementName();
  if(element->isConstraint()) {
    const RBAConstraintImpl* constraint
      = dynamic_cast<const RBAConstraintImpl*>(element);
    if(!constraint->isRuntime()) {
      isRuntime = "f";
    }
  }
  else if(element->isRule()) {
    type = RULE;
  }
  addHierarchyOfConstraintLogLine(START + SEP +
                                  eleName + SEP +
                                  isRuntime + SEP + type);
}

/**
 * Add constraint structure finish log 
 *
 * @param constraint
 */
void
RBACoverageLog::addHierarchyOfConstraintEndLog(const RBAAbstractConstraint* element)
{
  std::string eleName = element->getElementName();
  addHierarchyOfConstraintLogLine(END + SEP + eleName);
}

/**
 * Add constraint structure execution log
 *
 * @param expressionText
 * @param result
 */
void
RBACoverageLog::
addHierarchyOfConstraintExpressionLog(const std::string& expressionText,
				      const RBAExpression* expression)
{
  addHierarchyOfConstraintLogLine(EXPRESSION + EXP_SEP +
				  getHierarchy() + EXP_SEP +
				  expressionText + EXP_SEP +
				  getExpressionType(expression));
}

// ---------------------------------------------------------
// Hierarchical information of constraint log for coverage
// ---------------------------------------------------------

/**
 * Initialize the constraint hierarchy
 */
void
RBACoverageLog::initConstraintHierarchy()
{
  hierarchys_.clear();
}

/**
 * Returns the constraint hierarchy as a string
 *
 * @return
 */
std::string
RBACoverageLog::getHierarchy() const
{
  std::ostringstream oss;

  std::string pre;
  int32_t i=0;
  for(std::string now : hierarchys_) {
    if((i != 0) && (pre[0] != '#')) {
      // If it is the first time and it is not treated as multiple operators,
      // add split identifier
      oss << "#";
    }
    pre = now;
    if(now[0] == '#') {
      now = now.substr(1, now.length());
    }
    oss << now;
    i++;
  }

  return oss.str();
}

/**
 * Add constraint hierarchy
 *
 * @param data
 * @return
 */
bool
RBACoverageLog::addHierarchy(const std::string& data)
{
  hierarchys_.push_back(data);
  return true;
}

/**
 * Remove constraint hierarchy
 *
 * @param data
 * @return
 */
void
RBACoverageLog::removeHierarchy()
{
  hierarchys_.pop_back();
}

/**
 * Returns the type string of the expression 
 * to be output to the hierarchical log
 *
 * @param expression
 * @return
 */
std::string
RBACoverageLog::getExpressionType(const RBAExpression* expression) const
{
  switch(expression->getUnderlyingType()) {
  case RBAExpressionType::BOOLEAN:
    return "boolean";
  case RBAExpressionType::ACTION:
  case RBAExpressionType::SET_OF_ACTION:
    return "action";
  default:
    return "unknown";
  }
}

void
RBACoverageLog::notify(const std::string& log)
{
  for(RBAILogCollector* collector : collectors_) {
    collector->log(log);
  }
}
#endif

}
