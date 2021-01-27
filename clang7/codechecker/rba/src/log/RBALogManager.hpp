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
 * Log manager class header file
 */

#ifndef RBALOGMANAGER_HPP
#define RBALOGMANAGER_HPP

#include <memory>
#include "RBACoverageLog.hpp"

#ifdef RBA_USE_LOG

namespace rba
{

class DLL_EXPORT RBALogManager
{
public:
  RBALogManager();
  RBALogManager(const RBALogManager&)=delete;
  RBALogManager(const RBALogManager&&)=delete;
  RBALogManager& operator=(const RBALogManager&)=delete;
  RBALogManager& operator=(const RBALogManager&&)=delete;
  virtual ~RBALogManager()=default;

  // Interefae for RBA Tool
  static void init(int32_t level);
  void addCoverageLogCollector(RBAILogCollector* collector);
  void removeCoverageLogCollector(RBAILogCollector* collector);
  static void addStartLogLine(const std::string& log);
  static void coverageHierarchyOfConstraintLogLine(const std::string& message);
  static void setLogManager(RBALogManager* logManager);
  static RBALogManager* getLogManager();
  static void setEnable(std::uint16_t logType, bool sw=true);

  // Interface private to the outside of RBA
  static void setType(std::uint16_t logType);
  static void requestLogLine(const std::string& message);
  static void resultLogLine(const std::string& message);
  static void arbitrateAreaLogLine(const std::string& message);
  static void arbitrateContentLogLine(const std::string& message);
  static void arbitrateConstraintLogLine(const std::string& message);
  static void arbitrateConstraintLogicLogLine(const std::string& message);
  static void allConstraintLogLine(const std::string& message);
  static void cancelRequestLogLine(const std::string& message);
  static std::string getArbitrateLog();
  static std::string getAllConstraintLog();
  static std::string getCheckAllConstraintLog();
  static std::string getRequestLog();
  static std::string getPreviousResultLog();
  static std::string getResultLog();
  static std::string getCancelRequestLog(); 
  static void coverageRequestLogLine(const std::string& message);
  static void coveragePrevResultLogLine(const std::string& message);
  static void coverageResultLogLine(const std::string& message);
  static void coverageConstraintStartLog(const RBAAbstractConstraint* constraint);
  static void coverageConstraintEndLog(const RBAAbstractConstraint* constraint);
  static void coverageConstraintExpressionLog(const std::string& expressionText,
                                              RBAExecuteResult result);
  static void coverageConstraintExpressionLog(const std::string& expressionText);
  static void coverageCanceledRequestLogLine(const std::string& message);
  static void coverageHierarchyOfConstraintStartLog(const RBAAbstractConstraint* constraint);
  static void coverageHierarchyOfConstraintEndLog(const RBAAbstractConstraint* constraint);
  static void coverageHierarchyOfConstraintExpressionLog(const std::string& expressionText,
							 RBAExpression* expression);
  static void initConstraintHierarchy();
  static bool addHierarchy(const std::string& data);
  static void removeHierarchy();
  static const std::string& boolToString(const bool value);
  static void setIndent(std::int32_t nest);

private:
  void setTypeImpl(std::uint16_t logType);
  void setEnableImpl(std::uint16_t logType, bool sw=true);
  void initImpl(int32_t level);
  void requestLogLineImpl(const std::string& message);
  void resultLogLineImpl(const std::string& message);
  void arbitrateAreaLogLineImpl(const std::string& message);
  void arbitrateContentLogLineImpl(const std::string& message);
  void arbitrateConstraintLogLineImpl(const std::string& message);
  void arbitrateConstraintLogicLogLineImpl(const std::string& message);
  void allConstraintLogLineImpl(const std::string& message);
  void cancelRequestLogLineImpl(const std::string& message);
  std::string getArbitrateLogImpl();
  std::string getAllConstraintLogImpl();
  std::string getCheckAllConstraintLogImpl();
  std::string getRequestLogImpl();
  std::string getPreviousResultLogImpl();
  std::string getResultLogImpl();
  std::string getCancelRequestLogImpl();
  void coverageRequestLogLineImpl(const std::string& message);
  void coveragePrevResultLogLineImpl(const std::string& message);
  void coverageResultLogLineImpl(const std::string& message);
  void coverageConstraintStartLogImpl(const RBAAbstractConstraint* constraint);
  void coverageConstraintEndLogImpl(const RBAAbstractConstraint* constraint);
  void coverageConstraintExpressionLogImpl(const std::string& expressionText,
                                           RBAExecuteResult result);
  void coverageConstraintExpressionLogImpl(const std::string& expressionText);
  void coverageCanceledRequestLogLineImpl(const std::string& message);
  void addStartLogLineImpl(const std::string& log);
  void coverageHierarchyOfConstraintLogLineImpl(const std::string& message);
  void coverageHierarchyOfConstraintStartLogImpl(const RBAAbstractConstraint* constraint);
  void coverageHierarchyOfConstraintEndLogImpl(const RBAAbstractConstraint* constraint);
  void coverageHierarchyOfConstraintExpressionLogImpl(const std::string& expressionText,
						      const RBAExpression* expression);
  void initConstraintHierarchyImpl();
  bool addHierarchyImpl(const std::string& data);
  void removeHierarchyImpl();

public:
  const static std::uint16_t TYPE_NOTHING               =0x0000U;
  const static std::uint16_t TYPE_ALL_CONSTRAINTS       =0x0001U;
  const static std::uint16_t TYPE_REQUEST               =0x0002U;
  const static std::uint16_t TYPE_PREVIOUS_RESULT       =0x0004U;
  const static std::uint16_t TYPE_ARBITRATE             =0x0008U;
  const static std::uint16_t TYPE_CANCEL_REQUEST        =0x0010U;
  const static std::uint16_t TYPE_CHECK_ALL_CONSTRAINTS =0x0020U;
  const static std::uint16_t TYPE_RESULT                =0x0080U;
  /*
   * Used when implementing log output feature in C++.
   * Currebtly, the file is output on the RBATool side 
   * when TYPE_SAVE_LOG is on, so this information is not referenced.
   */
  const static std::uint16_t TYPE_SAVE_LOG = 0x0100U;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  const static std::string STR_TRUE;
  const static std::string STR_FALSE;
  static RBALogManager* instance_;
  static std::string indent_;
  std::vector<std::shared_ptr<RBALog>> requestLogs_;
  std::vector<std::shared_ptr<RBALog>> previousResultLogs_;
  std::vector<std::shared_ptr<RBALog>> resultLogs_;
  std::vector<std::shared_ptr<RBALog>> cancelLogs_;
  std::vector<std::shared_ptr<RBALog>> checkAllConstraintsLogs_;
  int32_t level_ = 0;
  std::uint16_t requestType_ = RBALogManager::TYPE_NOTHING;
  std::uint16_t execType_ = RBALogManager::TYPE_NOTHING;
  std::vector<std::shared_ptr<RBALog>> allConstraintLogs_;
  std::vector<std::shared_ptr<RBALog>> arbitrateLogs_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  RBACoverageLog coverageLog_;

};

}

// @Deviation (PRE00-CPP,Rule-16_0_4,Rule-16_2_1)
// [Contents that deviate from the rules]
//   Function-like macros shall not be defined.
// [Explanation that there is no problem even if it deviates from the rules]
//   Do not modify because it will cause processing load 
//   if it is not a function macro
#define LOG_initConstraintHierarchy() \
  rba::RBALogManager::initConstraintHierarchy()
#define LOG_removeHierarchy() \
  rba::RBALogManager::removeHierarchy()
#define LOG_coverageHierarchyOfConstraintStartLog(log) \
  rba::RBALogManager::coverageHierarchyOfConstraintStartLog(log)
#define LOG_coverageHierarchyOfConstraintEndLog(log) \
  rba::RBALogManager::coverageHierarchyOfConstraintEndLog(log)
#define LOG_addCoverageLogCollector(collector) \
  rba::RBALogManager::addCoverageLogCollector(collector)
#define LOG_addHierarchy(log) \
  rba::RBALogManager::addHierarchy(log)
#define LOG_allConstraintLogLine(log) \
  rba::RBALogManager::allConstraintLogLine(log)
#define LOG_arbitrateAreaLogLine(log) \
  rba::RBALogManager::arbitrateAreaLogLine(log)
#define LOG_arbitrateConstraintLogLine(log) \
  rba::RBALogManager::arbitrateConstraintLogLine(log)
#define LOG_arbitrateConstraintLogicLogLine(log) \
  rba::RBALogManager::arbitrateConstraintLogicLogLine(log)
#define LOG_coverageConstraintExpressionLog(log, flag) \
  rba::RBALogManager::coverageConstraintExpressionLog(log, flag)
#define LOG_coverageConstraintExpressionLog2(log) \
  rba::RBALogManager::coverageConstraintExpressionLog(log)
#define LOG_coverageConstraintStartLog(constraint) \
  rba::RBALogManager::coverageConstraintStartLog(constraint)
#define LOG_coverageConstraintEndLog(constraint) \
  rba::RBALogManager::coverageConstraintEndLog(constraint)
#else
#define LOG_initConstraintHierarchy()  do{} while(false)
#define LOG_removeHierarchy()  do{} while(false)
#define LOG_coverageHierarchyOfConstraintStartLog(log)   do{} while(false)
#define LOG_coverageHierarchyOfConstraintEndLog(log)   do{} while(false)
#define LOG_addCoverageLogCollector(collector)  do{} while(false)
#define LOG_addHierarchy(log)  do{} while(false)
#define LOG_allConstraintLogLine(log)  do{} while(false)
#define LOG_arbitrateAreaLogLine(log)  do{} while(false)
#define LOG_arbitrateConstraintLogLine(log)  do{} while(false)
#define LOG_arbitrateConstraintLogicLogLine(log)  do{} while(false)
#define LOG_coverageConstraintExpressionLog(log, flag)  do{} while(false)
#define LOG_coverageConstraintExpressionLog2(log)  do{} while(false)
#define LOG_coverageConstraintStartLog(constraint)  do{} while(false)
#define LOG_coverageConstraintEndLog(constraint)  do{} while(false)
#endif

// class method
#ifdef RBA_USE_LOG
#define LOG_getSymbol()  getSymbol()
#define LOG_getExpressionText()  getExpressionText()
#define LOG_getCoverageExpressionText()  getCoverageExpressionText()
#else
#define LOG_getSymbol()  std::string("")
#define LOG_getExpressionText()  std::string("")
#define LOG_getCoverageExpressionText()  std::string("")
#endif

#endif
