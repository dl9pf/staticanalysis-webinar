/**
 * 調停ロジック実装クラスヘッダファイル
 */

#ifndef RBAARBITORATORIMPL_HPP
#define RBAARBITORATORIMPL_HPP

#include <cstdint>
#include <set>
#include <memory>
#include <mutex>
#include <deque>
#include <unordered_map>
#include "RBAArbitrator.hpp"
#include "RBARequestQueMember.hpp"
#include "RBAResultSet.hpp"
#include "RBAResultImpl.hpp"

namespace rba
{

class RBAModelImpl;
class RBAAffectInfo;
class RBARollbacker;
class RBAWindowRouter;
class RBAConstraintImpl;
#ifdef RBA_USE_LOG
class RBALogManager;
#endif

class DLL_EXPORT RBAArbitratorImpl
{
public:
  RBAArbitratorImpl()=default;
  RBAArbitratorImpl(const RBAArbitratorImpl&)=delete;
  RBAArbitratorImpl(const RBAArbitratorImpl&&)=delete;
  RBAArbitratorImpl& operator=(const RBAArbitratorImpl&)=delete;
  RBAArbitratorImpl& operator=(const RBAArbitratorImpl&&)=delete;
  virtual ~RBAArbitratorImpl()=default;

  bool isValidContext(const std::string& context);
  bool isValidContext(std::list<std::string>& contexts);
  bool setRequestData(
      const std::string& context, bool require,
      std::list<std::pair<std::string, std::int32_t>>* const properties = nullptr,
      std::uint32_t syncIndex = 0xFFFFU);
  void setRequestData(const RBAContentState* state, bool require);
  void setRequestData(const RBAContent* const content, bool require);
  void setActive(const RBASceneImpl* const scene, const bool require);
  void setSceneProperty(const RBAAbstractProperty* const prop, const std::int32_t value);
  void setRequestData(std::list<std::string>& contexts, const bool require);
#ifdef RBA_USE_LOG
  void checkAllConstraints();
#endif
  void updateResult();
  void checkCancelContent() const;
  void createResultData();

  bool satisfiesConstraints() const;
  std::unique_ptr<RBAResult> arbitrateMain();
  void arbitrate(std::list<RBAAllocatable*>& allocatables);
  void arbitrateAllocatable(RBAAllocatable* allocatable,
                            std::set<const RBAAllocatable*>& revisited,
                            const std::int32_t nest, RBAAffectInfo* const affectInfo,
                            RBARollbacker* const parentRollbacker);
  void getAffectedAllocatables(
      RBAAllocatable* allocatable,
      std::list<RBAConstraintImpl*>& falseConstraints,
      std::list<RBAAllocatable*>& affectedAllocatables);
  void getAffectAllocatableWithoutAlreadyAffected(
      std::list<RBAAllocatable*>& allocatables,
      RBAAllocatable* affectAllocatable, RBAAffectInfo* affectInfo,
      std::list<RBAAllocatable*>& result);
  void addAffectAllocatable(std::list<RBAAllocatable*>& allocatables,
                            RBAAllocatable* affectAllocatable,
                            RBAAffectInfo* affectInfo);

  bool sortContentStates(const RBAAllocatable* const allocatable,
                         std::list<const RBAContentState*>& states) const;
  void postArbitrate();
  void changeContentStateCancelWithPolicy(const RBAContentState* const state);
  void collectRevisitAllocatable(
      std::list<const RBAAllocatable*>* const totalRevisitAllocatables,
      RBAAllocatable*& allocatable,
      std::list<RBAConstraintImpl*>& falseConstraints,
      std::set<const RBAAllocatable*>& revisited);

  bool isDefeat(const RBAContentState* const winner,
                const RBAContentState* const loser) const;

  static std::int32_t getViewActionPriority(const RBAViewActionType viewActionType);
  static bool compareViewAction(const std::unique_ptr<RBAViewAction>& lhs,
                                const std::unique_ptr<RBAViewAction>& rhs);
  RBAResultImpl* getResult() const;  /// rba_toolで使用する
  bool isCancelChecked(const RBAContentState* const state) const;
  bool isCancel(const RBAContentState* const state) const;

#ifdef RBA_USE_LOG
  void setResultLog();
#endif

 private:
  void differenceArbitrate();
  bool checkConstraints(std::list<RBAConstraintImpl*>& constraints,
                        std::list<RBAConstraintImpl*>& falseConstraints,
                        const RBAAllocatable* const allocatable);
  bool checkConstraintAndReArbitrate(RBAAllocatable* allocatable,
                                     std::set<const RBAAllocatable*>& revisited,
                                     const std::int32_t nest,
                                     RBAAffectInfo* const affectInfo,
                                     RBARollbacker* const parentRollbacker,
                                     std::list<RBAConstraintImpl*>& constraints,
                                     bool * const isSkipped, const bool isFinal);
  void setCancel(const RBAContentState* const state, const bool checked);
  void getSortedContentStates(
      const RBAAllocatable* const allocatable,
      std::list<const RBAContentState*>& contentStates) const;

#ifdef RBA_USE_LOG
  // ログ出力
  void logRequestArbitration();
  void logPreResultArbitration();
  void logRequestForCoverage();
  void logResultArbitration();
  void logResultForCoverage();
  void setLogToResult();
#endif

 public:
  RBAArbitrator* getArb() const;
  void setArb(RBAArbitrator* const arb);
  RBAModelImpl* getModel() const;
  void setModel(RBAModelImpl* const model);
  std::set<const RBAContentState*>& getCancelChecked();
  std::unique_ptr<RBAResultImpl>& getResultRef() const;
  void setResult(std::unique_ptr<RBAResultImpl> result);
  std::unique_ptr<RBAResultSet>& getNextResultSet();
  void setNextResultSet(std::unique_ptr<RBAResultSet> nextResultSet);
  std::unique_ptr<RBAResultSet>& getBackupResultSet();
  void setBackupResultSet(std::unique_ptr<RBAResultSet> backupResultSet);
  std::unique_ptr<RBAResultSet>& getReservedResultSet();
  void setReservedResultSet(std::unique_ptr<RBAResultSet> reservedResultSet);
  std::recursive_mutex& getMutex() const;
#ifdef RBA_USE_LOG
  bool getSimulationMode();
  void setSimulationMode(bool simulationMode);
#endif
  std::deque<std::unique_ptr<RBARequestQueMember>>& getRequestQue();

 private:
  RBAArbitrator* arb_ {nullptr};
  RBAModelImpl* model_ {nullptr};
  RBAWindowRouter* windowRouter_ {nullptr};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::set<const RBAContentState*> cancelChecked_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

  mutable std::unique_ptr<RBAResultImpl> result_;
  // 次の調停でCurrentResultSetとして使用するResultSet
  std::unique_ptr<RBAResultSet> nextResultSet_;
  // 次の調停でPreviousResultSetとして使用するResultSet
  std::unique_ptr<RBAResultSet> backupResultSet_;
  // cancelArbitration()でCurrentResultSetとして使用するResultSet
  std::unique_ptr<RBAResultSet> reservedResultSet_;
  // satisfiesConstraints()でCurrentResultSetとして使用するResultSet
  std::unique_ptr<RBAResultSet> resultSetForSatisfiesConstraints_;
  mutable std::recursive_mutex mutex_;
  // 調停要求を受けた時とき、常に調停するアロケータブル
  std::set<const RBAAllocatable*> allwaysArbitrateAllocatables_;
#ifdef RBA_USE_LOG
  bool simulationMode_ = false;
#endif
  std::deque<std::unique_ptr<RBARequestQueMember>> requestQue_;
  std::uint32_t syncIndex_ {0xFFFFU};

};

class DLL_EXPORT RBAArbitrator::Impl
{
 public:
  Impl(RBAArbitrator* const arb, RBAModelImpl* const newModel);
  Impl(const Impl&)=delete;
  Impl(const Impl&&)=delete;
  Impl& operator=(const Impl&)=delete;
  Impl& operator=(const Impl&&)=delete;
#ifdef RBA_USE_LOG
  Impl(RBAArbitrator* arb,
       RBAModelImpl* newModel, RBALogManager* logManager);
#endif
  virtual ~Impl()=default;

 public:
  RBAModelImpl* getModel();
  void setModel(RBAModelImpl* const newModel);
  void initialize(std::list<std::string>& contexts);
  std::unique_ptr<RBAResult> execute(const std::string& contextName,
                                     const bool require = true);
  std::unique_ptr<RBAResult> execute(std::list<std::string>& contexts,
                                     const bool require = true);
  std::unique_ptr<RBAResult> execute(
      const std::string& sceneName,
      std::list<std::pair<std::string, std::int32_t>>& properties);
  std::unique_ptr<RBAResult>
  setResultContentState(const std::string& allocatableName,
                        const std::string& contextName);
  std::unique_ptr<RBAResult> cancelArbitration();

  void clearArbitration();
  bool setScene(const std::string& sceneName, const bool require,
                std::list<std::pair<std::string, std::int32_t>>& properties);
  bool setContentState(const std::string& contextName, const bool require);
  bool setAllocatableResult(const std::string& allocatableName,
                            const std::string& contextName);

  bool evaluate(const RBAExpression* const expression);
  const RBARuleObject* evaluateObject(const RBAExpression* const expression);
  int32_t evaluateValue(const RBAExpression* const expression);

  RBAArbitratorImpl* getImpl();

 private:
  RBAArbitratorImpl impl_;

};

}

#endif
