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
 * Coverage Log class
 */

#ifndef RBACOVERAGELOG_HPP
#define RBACOVERAGELOG_HPP

#include <vector>
#include <set>
#include "RBAILogCollector.hpp"
#include "RBAExecuteResult.hpp"

namespace rba
{

#ifdef RBA_USE_LOG
class RBALog;
class RBAExpression;
class RBAAbstractConstraint;

class DLL_EXPORT RBACoverageLog
{
public:
  RBACoverageLog()=default;
  RBACoverageLog(const RBACoverageLog&)=delete;
  RBACoverageLog(const RBACoverageLog&&)=delete;
  RBACoverageLog& operator=(const RBACoverageLog&)=delete;
  RBACoverageLog& operator=(const RBACoverageLog&&)=delete;
  virtual ~RBACoverageLog()=default;

public:
  void addRequestLogLine(const std::string& message);
  void addPrevResultLogLine(const std::string& message);
  void addResultLogLine(const std::string& message);
  void addStartLogLine(const std::string& log);
  void addCoverageLogCollector(RBAILogCollector* collector);
  void removeCoverageLogCollector(RBAILogCollector* collector);
  void addConstraintLogLine(const std::string& message);
  void addConstraintStartLog(const RBAAbstractConstraint* element);
  void addConstraintEndLog(const RBAAbstractConstraint* element);
  void addConstraintExpressionLog(const std::string& expressionText,
                                  const RBAExecuteResult result);
  void addConstraintExpressionLog(const std::string& expressionText);
  void addCanceledRequestLogLine(const std::string& message);
  void addHierarchyOfConstraintLogLine(const std::string& message);
  void addHierarchyOfConstraintStartLog(const RBAAbstractConstraint* element);
  void addHierarchyOfConstraintEndLog(const RBAAbstractConstraint* element);
  void addHierarchyOfConstraintExpressionLog(const std::string& expressionText,
					     const RBAExpression* expression);
  void initConstraintHierarchy();
  std::string getHierarchy() const;
  bool addHierarchy(const std::string& data);
  void removeHierarchy();
  std::string getExpressionType(const RBAExpression* expression) const;

public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  // Delimiters other than constraint expression lines
  const static std::string SEP;
  // Delimiters of constraint expression line (Tab)
  const static std::string EXP_SEP;
  const static std::string START;
  const static std::string END;
  const static std::string EXPRESSION;
  const static std::string CONSTRAINT;
  const static std::string RULE;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

private:
  std::string createLog(std::vector<RBALog*> logs);
  void notify(const std::string& log);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::vector<std::string> hierarchys_; // Constraint hierarchy (x#y#z format)
  std::set<RBAILogCollector*> collectors_;
  std::vector<RBALog*> requestLogs_;
  std::vector<RBALog*> resultLogs_;
  std::vector<RBALog*> constraintLogs;
  std::vector<RBALog*> canceledRequestLogs_;

    // Constraint structure log for finding the denominator of 
  // constraint coverage. The constraint log is different 
  // because it also has the execution result.
  std::vector<RBALog*> hierarchyOfConstraintLogs_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};
#endif

}
#endif
