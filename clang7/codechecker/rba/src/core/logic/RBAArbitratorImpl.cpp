/**
 * 調停ロジック実装クラス定義ファイル
 */

#include <algorithm>
#include <sstream>
#include "RBAArbitratorImpl.hpp"
#include "RBAModelImpl.hpp"
#include "RBAResultImpl.hpp"
#include "RBAResultSet.hpp"
#include "RBAAreaImpl.hpp"
#include "RBAAllocatable.hpp"
#include "RBAAffectInfo.hpp"
#include "RBAViewContentImpl.hpp"
#include "RBAViewContentStateImpl.hpp"
#include "RBAConstraintImpl.hpp"
#include "RBARuleObject.hpp"
#include "RBAViewAction.hpp"
#include "RBAViewTransition.hpp"
#include "RBAViewMove.hpp"
#include "RBAConstraintInfo.hpp"
#include "RBAZoneImpl.hpp"
#include "RBASoundContentImpl.hpp"
#include "RBAContentState.hpp"
#include "RBARollbacker.hpp"
#include "RBALogManager.hpp"
#include "RBAModelFactory.hpp"
#include "RBAAllwaysCheckConstraintCollector.hpp"
#include "RBAModelElementType.hpp"
#include "RBARequestQueMember.hpp"

namespace rba {

RBAArbitrator::Impl::
Impl(RBAArbitrator* const arb, RBAModelImpl* const newModel)
  : impl_{}
{
  impl_.setArb(arb);
  setModel(newModel);
}

#ifdef RBA_USE_LOG
RBAArbitrator::Impl::
Impl(RBAArbitrator* arb,
     RBAModelImpl* newModel, RBALogManager* logManager)
{
  impl_.setArb(arb);
  setModel(newModel);
  RBALogManager::setLogManager(logManager);
  // 引数logManagerがnullだとしても、rba外部からsetLogManager()されている可能性があるので、
  // 引数判定ではなく、getLogManager()で判定
  if (RBALogManager::getLogManager() != nullptr) {
    impl_.setSimulationMode(true);
  }
}
#endif

RBAModelImpl*
RBAArbitrator::Impl::
getModel()
{
  return impl_.getModel();
}

void
RBAArbitrator::Impl::
setModel(RBAModelImpl* const newModel)
{
  std::lock_guard<std::recursive_mutex> lock {impl_.getMutex()};
  impl_.setModel(newModel);
  impl_.getModel()->createSortedAllocatables();
  clearArbitration();
}

void
RBAArbitrator::Impl::
initialize(std::list<std::string>& contexts)
{
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  impl_.setRequestData(contexts, true);
}

std::unique_ptr<RBAResult> RBAArbitrator::Impl::execute(
    const std::string& contextName, const bool require)
{
  const std::lock_guard<std::recursive_mutex> lock {impl_.getMutex()};
  if (impl_.isValidContext(contextName) == false) {
    // エラーの場合は、Resultのコピーを生成してエラーフラグをセットして返す
    std::unique_ptr<RBAResultImpl> result {std::make_unique<RBAResultImpl>(
        &impl_, std::make_unique<RBAResultSet>(*impl_.getBackupResultSet()))};
    result->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(result);
  } else {
    static_cast<void>(impl_.setRequestData(contextName, require, nullptr,
                      static_cast<std::uint32_t>(impl_.getRequestQue().size())));
    return impl_.arbitrateMain();
  }
}

std::unique_ptr<RBAResult> RBAArbitrator::Impl::execute(
    std::list<std::string>& contexts, const bool require)
{
  const std::lock_guard<std::recursive_mutex> lock {impl_.getMutex()};
  if (impl_.isValidContext(contexts) == false) {
    // エラーの場合は、Resultのコピーを生成してエラーフラグをセットして返す
    std::unique_ptr<RBAResultImpl> result {std::make_unique<RBAResultImpl>(
        &impl_, std::make_unique<RBAResultSet>(*impl_.getBackupResultSet()))};
    result->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(result);
  } else {
    impl_.setRequestData(contexts, require);
    return impl_.arbitrateMain();
  }
}

std::unique_ptr<RBAResult> RBAArbitrator::Impl::execute(
    const std::string& sceneName,
    std::list<std::pair<std::string, std::int32_t>>& properties)
{
  const std::lock_guard<std::recursive_mutex> lock {impl_.getMutex()};
  // 引数チェック
  if (impl_.isValidContext(sceneName) == false) {
    // エラーの場合は、Resultのコピーを生成してエラーフラグをセットして返す
    std::unique_ptr<RBAResultImpl> result {std::make_unique<RBAResultImpl>(
        &impl_, std::make_unique<RBAResultSet>(*impl_.getBackupResultSet()))};
    result->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(result);
  } else {
    static_cast<void>(impl_.setRequestData(sceneName, true, &properties,
                      static_cast<std::uint32_t>(impl_.getRequestQue().size())));
    return impl_.arbitrateMain();
  }
}

std::unique_ptr<RBAResult>
RBAArbitrator::Impl::
setResultContentState(const std::string& allocatableName,
		      const std::string& contextName)
{
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  RBAResultSet* const backupResultSetTmp {impl_.getBackupResultSet().get()};
  if (impl_.getReservedResultSet() == nullptr) {
    impl_.setResult(std::make_unique<RBAResultImpl>(&impl_,
                                                    std::make_unique<RBAResultSet>(),
                                                    std::move(impl_.getBackupResultSet())));
  } else {
    RBAResultSet* const reservedResultSetTmp {impl_.getReservedResultSet().get()};
    impl_.setResult(std::make_unique<RBAResultImpl>(&impl_,
                                                    std::move(impl_.getReservedResultSet()),
                                                    std::move(impl_.getBackupResultSet())));
    impl_.setReservedResultSet(std::make_unique<RBAResultSet>(*reservedResultSetTmp));
  }
  impl_.setBackupResultSet(std::make_unique<RBAResultSet>(*backupResultSetTmp));
  
  // find allocatable
  const RBAAllocatable* alloc {nullptr};
  const RBAAreaImpl* const area {impl_.getModel()->findAreaImpl(allocatableName)};
  if(area != nullptr) {
    alloc = area;
  }
  else {
    const RBAZoneImpl* const zone {impl_.getModel()->findZoneImpl(allocatableName)};
    if(zone != nullptr) {
      alloc = zone;
    }
  }
  // find content state
  const RBAContentState* state {nullptr};
  const RBAViewContentStateImpl* const viewState
    {impl_.getModel()->findViewContentStateImpl(contextName)};
  if(viewState != nullptr) {
    state = viewState;
  }
  else {
    const RBASoundContentStateImpl* const soundState
      {impl_.getModel()->findSoundContentStateImpl(contextName)};
    if(soundState != nullptr) {
      state = soundState;
    }
  }
  if( (alloc == nullptr) || (state == nullptr) ) {
    // Unknown context or allocatable
    impl_.getResult()->setStatusType(RBAResultStatusType::UNKNOWN_CONTENT_STATE);
    return std::move(impl_.getResultRef());
  }
  // Set alloc and state to result
  const RBAContentState* const beforeContentState {alloc->getState()};
  const_cast<RBAAllocatable*>(alloc)->setState(state);
  const_cast<RBAAllocatable*>(alloc)->setChecked(true);
  impl_.getResult()->setActive(state, true);
  impl_.getResult()->setContentState(alloc, state);

  // ----------------------------------------------------------
  // 調停後処理
  // ----------------------------------------------------------
  impl_.postArbitrate();

  // オフライン制約を動かす
#ifdef RBA_USE_LOG
  impl_.checkAllConstraints();
#endif

  // ----------------------------------------------------------
  // コンテントの状態を更新する
  // ----------------------------------------------------------
  if (beforeContentState != nullptr) {
    // 要求されたアロケータブルに元々割り当てられていたコンテントの状態を更新する
    dynamic_cast<RBAContent*>(beforeContentState->getOwner())->updateStatus(impl_.getResultRef().get());
  }
  // 要求されたコンテントの状態を更新する
  dynamic_cast<RBAContent*>(state->getOwner())->updateStatus(impl_.getResultRef().get());

  // コンテントのキャンセル処理
  // C++版で追加した処理
  impl_.checkCancelContent();

  // C++版で追加した処理
  // 表示エリア,非表示エリアの更新
  impl_.updateResult();

  // 結果を生成
  impl_.createResultData();

  // 現在の調停結果セットのバックアップを保存
  impl_.setBackupResultSet(impl_.getResult()->createBackupCurrentResultSet());
  // 次の調停結果セットを作成
  impl_.setNextResultSet(impl_.getResult()->createNextCurrentResultSet());

  return std::move(impl_.getResultRef());
}

std::unique_ptr<RBAResult>
RBAArbitrator::Impl::
cancelArbitration()
{
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  if(impl_.getReservedResultSet() == nullptr) {
    std::unique_ptr<RBAResultImpl> res
      {std::make_unique<RBAResultImpl>(&impl_,
                                        std::make_unique<RBAResultSet>())};
    res->setStatusType(RBAResultStatusType::CANCEL_ERROR);
    return std::move(res);
  }

  impl_.setResult(
      std::make_unique<RBAResultImpl>(&impl_,
                                      std::make_unique<RBAResultSet>(),
                                      std::move(impl_.getReservedResultSet())));
  impl_.setBackupResultSet(impl_.getResult()->createBackupCurrentResultSet());
  impl_.setNextResultSet(impl_.getResult()->createNextCurrentResultSet());

  return std::move(impl_.getResultRef());
}

void
RBAArbitrator::Impl::
clearArbitration()
{
  std::lock_guard<std::recursive_mutex> lock {impl_.getMutex()};
  impl_.getCancelChecked().clear();
  impl_.setReservedResultSet(nullptr);
  impl_.setBackupResultSet(std::make_unique<RBAResultSet>());
  for(const auto& scene : impl_.getModel()->getSceneImpls()) {
    for(const std::string propertyName : scene->getPropertyNames()) {
      const std::int32_t value {scene->getPropertyValue(propertyName)};
      impl_.getBackupResultSet()->setSceneProperty(scene, propertyName, value);
    }
  }
  impl_.setNextResultSet(
      std::make_unique<RBAResultSet>(*impl_.getBackupResultSet().get()));
  impl_.setResult(std::make_unique<RBAResultImpl>(
      &impl_,
      std::make_unique<RBAResultSet>(*impl_.getBackupResultSet().get())));

  impl_.getModel()->clearElementsStatus();
}

bool
RBAArbitrator::Impl::
setScene(
    const std::string& sceneName, const bool require,
    std::list<std::pair<std::string, std::int32_t>>& properties)
{
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  return impl_.setRequestData(sceneName, require, &properties);
}

bool
RBAArbitrator::Impl::
setContentState(const std::string& contextName, const bool require)
{
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  const std::deque<std::unique_ptr<RBARequestQueMember>>& requestQue{impl_.getRequestQue()};
  std::uint32_t syncIndex{static_cast<std::uint32_t>(requestQue.size())};
  if (syncIndex > 0U ) {
    const std::unique_ptr<RBARequestQueMember>& prevReq{requestQue.back()};
    if (prevReq->isOn() == require) {
      syncIndex = prevReq->getSyncIndex();
    }
  }
  return impl_.setRequestData(contextName, require, nullptr, syncIndex);
}

bool
RBAArbitrator::Impl::
setAllocatableResult(const std::string& allocatableName,
		     const std::string& contextName)
{
  std::lock_guard<std::recursive_mutex> lock {impl_.getMutex()};
  // Get allocatable
  const auto alloc = impl_.getModel()->findAllocatable(allocatableName);
  if(alloc == nullptr) {
    return false;
  }

  // Get context
  const auto state = impl_.getModel()->findContentState(contextName);
  if(state == nullptr) {
    return false;
  }

  // Set state to allocatable
  const auto beforeContentState = alloc->getState();
  const_cast<RBAAllocatable*>(alloc)->setState(state);
  RBAResultSet* const nextResultSet {impl_.getNextResultSet().get()};
  RBAResultSet* const prevResultSet {impl_.getBackupResultSet().get()};
  nextResultSet->setContentState(alloc, state);
  prevResultSet->setContentState(alloc, state);
  nextResultSet->setActive(state, true);
  prevResultSet->setActive(state, true);

  ///////////////////////////
  // コンテントの状態を更新する
  ///////////////////////////
  // コンテントの状態を更新は前回の状態を見て今回の遷移先を決定するので、
  // Resultを作成して、状態を更新している
  impl_.setResult(std::make_unique<RBAResultImpl>(
      &impl_,
      std::make_unique<RBAResultSet>(*impl_.getBackupResultSet()),
      std::make_unique<RBAResultSet>(*impl_.getNextResultSet())));
  RBAContent* const content {dynamic_cast<RBAContent*>(state->getOwner())};
  content->updateRequestStatus(impl_.getResult()->getCurResultSet().get(), true);
  if (beforeContentState != nullptr) {
    // 要求されたアロケータブルに元々割り当てられていたコンテントの状態を更新する
    dynamic_cast<RBAContent*>(beforeContentState->getOwner())->updateStatus(impl_.getResultRef().get());
  }
  // 要求されたコンテントの状態を更新する
  content->updateStatus(impl_.getResultRef().get());

  impl_.setBackupResultSet(std::make_unique<RBAResultSet>(*impl_.getResult()->getPreResultSet()));
  impl_.setNextResultSet(impl_.getResult()->createNextCurrentResultSet());

  return true;
}

bool
RBAArbitrator::Impl::
evaluate(const RBAExpression* const expression)
{
  if(expression == nullptr) {
    return false;
  }
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  RBAConstraintInfo info;
  // 制約式の評価
  return expression->execute(&info, &impl_);
}

const RBARuleObject*
RBAArbitrator::Impl::
evaluateObject(const RBAExpression* const expression)
{
  if(expression == nullptr) {
    return nullptr;
  }
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  RBAConstraintInfo info;
  // 制約式の評価
  const RBARuleObject* const ruleObj
    {expression->getReferenceObject(&info, &impl_)};
  if (ruleObj != nullptr) {
    return ruleObj->getRawObject();
  } else {
    return nullptr;
  }
}

int32_t
RBAArbitrator::Impl::
evaluateValue(const RBAExpression* const expression)
{
  if(expression == nullptr) {
    return -99;
  }
  const std::lock_guard<std::recursive_mutex> lock{impl_.getMutex()};
  RBAConstraintInfo info;
  // 制約式の評価
  return expression->getValue(&info, &impl_);
}

RBAArbitratorImpl*
RBAArbitrator::Impl::
getImpl()
{
  return &impl_;
}

// @Deviation (EXP55-CPP)
// 【ルールに逸脱している内容】
// このconstメンバ関数は、メンバ変数を変更します。
// 【ルールを逸脱しても問題ないことの説明】
// constメンバ関数であるsatisfiesConstraintsで、thisからconstを外して、使用しているが、
// execute()では、キャッシュ値しか変更しないので、問題なし。
bool
RBAArbitratorImpl::
satisfiesConstraints() const
{
  const std::lock_guard<std::recursive_mutex> lock{mutex_};
  // 評価用にresult_を使うため、実際のresult_を一時保管する
  std::unique_ptr<RBAResultImpl> tmpResult {std::move(result_)};
  result_ = std::make_unique<RBAResultImpl>(
      this,
      std::make_unique<RBAResultSet>(*(reservedResultSet_.get())),
      std::make_unique<RBAResultSet>(*(resultSetForSatisfiesConstraints_.get())));
  bool result {true};
  for(const RBAConstraintImpl*& constraint : model_->getConstraintImpls()) {
    if (constraint->isRuntime() == true) {
      // 引数のRBAArbitratorImplの実体は、内部状態を変更するメソッド呼び出しを
      // 使用するため、constにできない。そのため、ここではconst_castで渡して
      // constを外している。
      result = const_cast<RBAConstraintImpl*>(constraint)->execute(const_cast<RBAArbitratorImpl*>(this));
      if (result == false) {
        break;
      }
    }
  }
  result_ = std::move(tmpResult);
  return result;
}

/**
 * 調停実行
 */
std::unique_ptr<RBAResult>
RBAArbitratorImpl::arbitrateMain()
{
  // cancelArbitration()されたときのために調停前の要求状態を保存
  reservedResultSet_ = std::make_unique<RBAResultSet>(*backupResultSet_);

  // 要求毎の差分調停
  if (requestQue_.empty()) {
    // differenceArbitrateで使用するのでここで、Resultを用意しておく
    result_ = std::make_unique<RBAResultImpl>(this,
                                              std::move(backupResultSet_),
                                              std::move(nextResultSet_));
    // 引数なしの調停要求。この中のonDisplayedにより、requestQue_にキューイングされる可能性がある
    differenceArbitrate();
  }
  if (!requestQue_.empty()) {
    result_ = std::make_unique<RBAResultImpl>(this,
                                              std::move(backupResultSet_),
                                              std::move(nextResultSet_));
    do {
      const std::unique_ptr<RBARequestQueMember> request {std::move(requestQue_.front())};
      requestQue_.pop_front();
      result_->setActive(request->getContentState(), request->isOn());
      // コンテントの状態を更新する
      RBAContent* const content {dynamic_cast<RBAContent*>(request->getContentState()->getOwner())};
      content->updateRequestStatus(result_->getCurResultSet().get(), request->isOn());
      if (requestQue_.empty()) {
        differenceArbitrate();
        if (!requestQue_.empty()) {
          // 次のdifferenceArbitrate()に備えて、更新しておく。
          result_ = std::make_unique<RBAResultImpl>(this,
                                                    std::move(backupResultSet_),
                                                    std::move(nextResultSet_));
        }
      } else if (requestQue_.front()->getSyncIndex() != request->getSyncIndex()) {
        differenceArbitrate();
        // 次のdifferenceArbitrate()に備えて、更新しておく。
        result_ = std::make_unique<RBAResultImpl>(this,
                                                  std::move(backupResultSet_),
                                                  std::move(nextResultSet_));
      } else {
        // 何もしない
      }
    } while (!requestQue_.empty());
  }

  result_ = std::make_unique<RBAResultImpl>(
      this, std::make_unique<RBAResultSet>(*reservedResultSet_),
      result_->createBackupCurrentResultSet());

  // コンテントのキャンセル処理
  // C++版で追加した処理
  checkCancelContent();

  // C++版で追加した処理
  // 表示エリア,非表示エリアの更新
  updateResult();

#ifdef RBA_USE_LOG
  RBALogManager::setType(RBALogManager::TYPE_RESULT);
  logResultArbitration();

  setLogToResult();
  RBALogManager::setType(RBALogManager::TYPE_NOTHING);
#endif

  createResultData();
  // 現在の調停結果セットのバックアップを保存
  backupResultSet_ = result_->createBackupCurrentResultSet();
  // 次の調停結果セットを作成
  nextResultSet_ = result_->createNextCurrentResultSet();

  // 保管用にresult_を使うため、戻り値のresult_を別名にする
  auto retResult = std::move(result_);

  // 調停中以外の場合で、調停結果を利用することがあるため、調停結果を保持しておく
  result_ = std::make_unique<RBAResultImpl>(retResult.get());

  // std::unique_ptr<RBAResultImpl>をstd::unique_ptr<RBAResult>にキャストするので
  // std::move()がないとコンパイルエラーになる
  return std::move(retResult);
}

bool
RBAArbitratorImpl::
isValidContext(const std::string& context)
{
  if (context != "") {
    const RBAContentState* const state {model_->findContentState(context)};
    if (state == nullptr) {
      const RBASceneImpl* const scene {model_->findSceneImpl(context)};
      if (scene == nullptr) {
        return false;
      }
    }
  }

  return true;
}

bool
RBAArbitratorImpl::
isValidContext(std::list<std::string>& contexts)
{
  for(const std::string contextName : contexts) {
    if(isValidContext(contextName) == false) {
      return false;
    }
  }

  return true;
}

/**
 * 入力情報を反映
 */

bool
RBAArbitratorImpl::setRequestData(
    const std::string& context, bool require,
    std::list<std::pair<std::string, std::int32_t>>* const properties,
    std::uint32_t syncIndex)
{
  bool isSet {false};
  if (context != "") {
    // コンテントステートが指定された場合
    // contextNameがコンテント名のみの場合は、先頭のコンテントステートを取り出す
    const RBAContentState* state {model_->findContentState(context)};
    if (state != nullptr) {
      requestQue_.push_back( std::make_unique<RBARequestQueMember>(state, require, syncIndex));
      isSet = true;
    } else {
      // シーンが指定された場合
      const RBASceneImpl* const scene {model_->findSceneImpl(context)};
      if (scene != nullptr) {
        nextResultSet_->setActive(scene, require); // 次の調停用
        result_->setActive(scene, require);        // 次の調停前にResultを参照されたとき用
        isSet = true;
        if (properties != nullptr) {
          for (auto& p : *properties) {
            const RBAAbstractProperty* const ap {scene->getProperty(p.first)};
            if (ap != nullptr) {
              nextResultSet_->setSceneProperty(ap, p.second); // 次の調停用
              result_->setSceneProperty(ap, p.second);        // 次の調停前にResultを参照されたとき用
            }
          }
        }
      }
    }
  }
  return isSet;
}

void
RBAArbitratorImpl::setRequestData(const RBAContentState* state,
                                  bool require)
{
  if (requestQue_.empty()){
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(state, require, 0U));
  } else {
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(state, require, requestQue_.back()->getSyncIndex()));
  }
}

void
RBAArbitratorImpl::setRequestData(const RBAContent* const content,
                                  bool require)
{
  if (requestQue_.empty()){
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(content->getStates().front(), require, 0U));
  } else {
    requestQue_.push_back( std::make_unique<RBARequestQueMember>(content->getStates().front(), require, requestQue_.back()->getSyncIndex()));
  }
}

void
RBAArbitratorImpl::setActive(const RBASceneImpl* const scene, const bool require)
{
  if (nextResultSet_ != nullptr) {
    // onRequest、onWithdrawnでonSceneされるときはnextResultSet_を更新する
    nextResultSet_->setActive(scene, require);
  } else {
    result_->setActive(scene, require);
  }
}

void
RBAArbitratorImpl::setSceneProperty(const RBAAbstractProperty* const prop, const std::int32_t value)
{
  if (nextResultSet_ != nullptr) {
    // onRequest、onWithdrawnでsetされるときはnextResultSet_を更新する
    nextResultSet_->setSceneProperty(prop, value);
  } else {
    result_->getCurResultSet()->setSceneProperty(prop, value);
  }
}

void
RBAArbitratorImpl::setRequestData(std::list<std::string>& contexts,
                                  const bool require)
{
  const std::uint32_t syncIndex {static_cast<std::uint32_t>(requestQue_.size())};
  for (auto& c : contexts) {
    static_cast<void>(setRequestData(c, require, nullptr, syncIndex));
  }
}

/**
 * 含意がfalse時に再調停を行える拡張版の調停を行う
 * @param areas
 */
void
RBAArbitratorImpl::
arbitrate(std::list<RBAAllocatable*>& allocatables)
{
  LOG_arbitrateAreaLogLine("----Arbitrate----");
  std::set<const RBAAllocatable*> revisitedInitSet;

  std::set<const RBAAllocatable*> revisited;
  for (auto& alloc : allocatables) {
    revisited = revisitedInitSet;
    // -------------------------------------------------------------------------
    // 無限ループ対策として調停の中で対象アロケータブルに影響を与えた他アロケータブルの
    // 登録は一回までに制限させるための情報を生成
    // -------------------------------------------------------------------------
    RBAAffectInfo affectInfo;
    LOG_arbitrateAreaLogLine(
        alloc->getSymbol() + "[" + alloc->getElementName() + "] check start");
    arbitrateAllocatable(alloc, revisited, 0, &affectInfo, nullptr);
  }
  for (auto& a : model_->getSortedAllocatables()) {
    result_->setContentState(a, a->getState());
  }
}

/**
 * アロケータブルの調停を再帰的に行う
 * @param allocatable 調停したいアロケータブル
 * @param revisited 再調停済のアロケータブル
 * @param nest 再調停のネスト階層（一番初めの調停は0）
 * @param affectInfo allocatableが影響を与えたアロケータブルの情報
 */
void RBAArbitratorImpl::arbitrateAllocatable(
    RBAAllocatable* allocatable,
    std::set<const RBAAllocatable*>& revisited,
    const std::int32_t nest,
    RBAAffectInfo* const affectInfo,
    RBARollbacker* const parentRollbacker)
{
#ifdef RBA_USE_LOG
  RBALogManager::setIndent(nest);
#endif
  // この変数が定義されるまでの再帰処理中に、今回の調停対象アロケータブルが影響を与えたアロケータブル
  // 再調停前の状態を覚えておく
  std::set<const RBAAllocatable*> affectAllocatables;
  affectAllocatables.insert(allocatable->getAllocatablesAffectedByYou().begin(), allocatable->getAllocatablesAffectedByYou().end());

  const RBAContentState* const beforeState {allocatable->getState()};

  // 対象アロケータブルのコンテンツ割当をチェック済とする
  allocatable->setChecked(true);
  // 調停ポリシーでソートされたコンテンツ状態を取得(Activeな要求だけが入る)
  std::list<const RBAContentState*> contentStates;
  getSortedContentStates(allocatable, contentStates);
  for(const RBAContentState* const contentState : contentStates) {
    // エリアにコンテンツを割り当てる
    allocatable->setState(contentState);
#ifdef RBA_USE_LOG
    {
      std::string str = "  Content[";
      if (contentState == nullptr) {
        str += "null";
      } else {
        str += contentState->getOwner()->getElementName() + "::"
            + contentState->getElementName();
      }
      str += "] check online constraints start";
      RBALogManager::arbitrateContentLogLine(str);
    }
#endif
    bool isSkipped {false};
    const bool isPassed {checkConstraintAndReArbitrate(
        allocatable, revisited, nest, affectInfo, parentRollbacker,
        allocatable->getConstraints(), &isSkipped, false)};
    if (isPassed == true) {

      // ----------------------------------------------------------
      // コンテンツ割り当て処理後に制約式によって自アロケータブルが隠蔽されるべきかをチェック
      // contentValue()があるため、コンテンツ未割り当てでも確認する
      // ----------------------------------------------------------
#ifdef RBA_USE_LOG
      std::string alloSymbol = allocatable->getSymbol();
      std::string alloName = allocatable->getElementName();
      if (allocatable->isArea() == true) {
        LOG_arbitrateAreaLogLine(
            "  check online constraints to confirm area hidden state");
      } else {
        LOG_arbitrateAreaLogLine(
            "  check online constraints to confirm zone muted state");
      }
#endif
      // 対象アロケータブルのhiddenをチェック済とする
      allocatable->setHiddenChecked(true);
      // 対象アロケータブルのhiddenをfalseにする
      allocatable->setHidden(false);
      bool hiddenIsPassed {checkConstraintAndReArbitrate(
          allocatable, revisited, nest, affectInfo, parentRollbacker,
          allocatable->getHiddenFalseCheckConstraints(), &isSkipped, !allocatable->isZone())};
      if (hiddenIsPassed == false) {
        allocatable->setHidden(true);
        hiddenIsPassed = checkConstraintAndReArbitrate(
            allocatable, revisited, nest, affectInfo, parentRollbacker,
            allocatable->getHiddenTrueCheckConstraints(), &isSkipped, !allocatable->isZone());
        if (hiddenIsPassed == false) {
          // アロケータブルの隠蔽状態をクリアする
          allocatable->setHiddenChecked(false);
        } else {
          LOG_arbitrateAreaLogLine(
              alloSymbol + "[" + alloName + "] change "
                  + allocatable->getHiddenSymbol());
        }
      }

      // -------------------------------------
      // ゾーンは隠蔽(ミュート)後にアッテネートを判定する
      // -------------------------------------
      bool attenuateIsPassed {true};
      if (allocatable->isZone()) {
        RBAZoneImpl* const zone {dynamic_cast<RBAZoneImpl*>(allocatable)};
        // 対象ゾーンのアッテネートをチェック済とする
        zone->setAttenuateChecked(true);
        // 対象ゾーンのアッテネートをfalseにする
        zone->setAttenuated(false);
        LOG_arbitrateAreaLogLine(
            "  check online constraints to confirm zone attenuated state");
        attenuateIsPassed = checkConstraintAndReArbitrate(
            allocatable, revisited, nest, affectInfo, parentRollbacker,
            allocatable->getAttenuateFalseCheckConstraints(), &isSkipped, true);
        if (attenuateIsPassed == false) {
          zone->setAttenuated(true);
          attenuateIsPassed = checkConstraintAndReArbitrate(
              allocatable, revisited, nest, affectInfo, parentRollbacker,
              allocatable->getAttenuateTrueCheckConstraints(), &isSkipped, true);
          if (attenuateIsPassed == false) {
            allocatable->setAttenuateChecked(false);
          } else {
            LOG_arbitrateAreaLogLine(
                alloSymbol + "[" + alloName + "] change attenuated");
          }
        }
      }
#ifdef RBA_USE_LOG
      {
        std::string str = alloSymbol + "[" + alloName + "] ";
        if (allocatable->isArea() == true) {
          str += "displays";
        } else {
          str += "outputs";
        }
        str += " Content[";
        const RBAContentState* state = allocatable->getState();
        if (state == nullptr) {
          str += "null";
        } else {
          str += state->getOwner()->getElementName() + "::"
            + state->getElementName();
        }
        str += "] " + allocatable->getHiddenSymbol() + "["
            + RBALogManager::boolToString(allocatable->isHidden()) + "]";
        if (allocatable->isZone() == true) {
          str += " attenuated["
              + RBALogManager::boolToString(allocatable->isAttenuated()) + "]";
        }
        str += "\n";
        LOG_arbitrateAreaLogLine(str);
      }
#endif
      if ((hiddenIsPassed == true) && (attenuateIsPassed == true)) {
        break;
      }
    }
  }
  // ---------------------------------------------------------------------
  // 影響を与えたアロケータブルを再調停
  // ---------------------------------------------------------------------
  if ((beforeState != allocatable->getState())
          || allocatable->isHidden()
          || allocatable->isAttenuated()) {

    // コンテント割当時には隠蔽ではない状態で再調停しているので、
    // 隠蔽、アッテネート状態になった場合、コンテント割り当て時の再調停で影響を与えたアロケータブルも再調停が必要
    // 影響を与えたエリアが増えた分を更新する
    if (allocatable->isHidden() || allocatable->isAttenuated()) {
      for (const auto& a : allocatable->getAllocatablesAffectedByYou()) {
        static_cast<void>(affectAllocatables.insert(a));
      }
    }

    // 影響エリア/ゾーンの再調停対象に、再調停元のエリア/ゾーン(再調停のネストがある場合そのすべての再調停元を含む)が、
    // 調停中のエリア/ゾーンに影響を受けたエリア/ゾーンとなった場合は、そのエリア/ゾーンは再調停対象から除外して影響エリア/ゾーンの再調停を行う。
    // また、影響エリア/ゾーンがその時点で、未調停アロケータブルだった場合も、
    // 通常手番の調停時に調停すればよいため、影響エリアの再調停対象から除外する。
    for (const auto& a : revisited) {
      if (affectAllocatables.find(a) != affectAllocatables.end()
          || (!a->isChecked())) {
        static_cast<void>(affectAllocatables.erase(a));
      }
    }
    std::list<const RBAAllocatable*> sortedAllocatables(affectAllocatables.begin(),affectAllocatables.end());
    sortedAllocatables.sort(&RBAAllocatable::compareIndex);
    if (parentRollbacker != nullptr) {
      std::shared_ptr<RBARollbacker> rollbacker {std::make_shared<RBARollbacker>()};
      parentRollbacker->addChild(rollbacker);
      rollbacker->backup(sortedAllocatables);
    }

    for (auto& affect : sortedAllocatables) {
      // これから再調停するアロケータブルを、調停中アロケータブルの影響を与えたアロケータブルから削除
      allocatable->removeAffectAllocatable(affect);
    }
    static_cast<void>(revisited.insert(allocatable)); // 調停済みエリアに追加する
    for (auto& affectAllocatable : sortedAllocatables) {
      // @Deviation (EXP55-CPP,Rule-5_2_5,A5-2-3)
      // 【ルールに逸脱している内容】
      // This is a 'const_cast' expression that strips away a 'const' or 'volatile' qualifier.
      // 【ルールを逸脱しても問題ないことの説明】
      // 設計書上、問題無いことを確認出来ており、改修にはクラス設計の見直しが必要なため、今は修正しない。
      RBAAllocatable* allo {const_cast<RBAAllocatable*>(affectAllocatable)};

      // これから影響アロケータブルの再調停を実施するアロケータブルのチェックフラグを初期化
      // 影響アロケータブルを事前にまとめてクリアすると、
      // 先に実施した影響アロケータブルの再調停中の制約式評価でスキップが発生し、
      // その後実施した影響アロケータブルの再調停中に、再調停が動いてしまうため、
      // 影響アロケータブルの再調停前に個別にクリアする
      allo->clearChecked();

      LOG_arbitrateAreaLogLine( "    " +
          affectAllocatable->getSymbol() + "["
                                + affectAllocatable->getElementName()
                                + "] affect allocatable check start");
      // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
      // 【ルールに逸脱している内容】
      // arbitrateAllocatable()を再帰呼び出ししている
      // 【ルールを逸脱しても問題ないことの説明】
      // 影響エリアの再調停に必要な処理であり、無限ループ防止処理を入れているため、
      // スタックオーバーフローすることはなく、問題無い。
      arbitrateAllocatable(allo, revisited, nest + 1, affectInfo,
                           parentRollbacker);
    }
    for(const RBAAllocatable* const revisitAllocatable : sortedAllocatables) {
      static_cast<void>(revisited.erase(revisitAllocatable));
    }
  }

  // --------------------------------------------------
  // 再調停の中での無限ループ防止用の一時的な影響情報を削除する
  // --------------------------------------------------
  affectInfo->removeAffectInfo(allocatable);
#ifdef RBA_USE_LOG
  RBALogManager::setIndent(nest-1);
#endif
}

/**
 * 調停ポリシーに基づいてコンテンツ状態のソートを行う
 * @param allocatable
 * @param contentStates
 * @return sort成否
 */
bool
RBAArbitratorImpl::
sortContentStates(const RBAAllocatable* const allocatable,
                  std::list<const RBAContentState*>& states) const
{
  bool isResult {true};
  switch(allocatable->getAllocatableArbitrationPolicy()) {
  case RBAArbitrationPolicy::FIRST_COME_FIRST:
	states.sort(&RBAContentState::compareFirstComeFirst);
    break;
  case RBAArbitrationPolicy::LAST_COME_FIRST:
	states.sort(&RBAContentState::compareLastComeFirst);
    break;
  case RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST:
	states.sort(&RBAContentState::comparePriorityFirstComeFirst);
    break;
  case RBAArbitrationPolicy::DEFAULT:
  case RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST:
	states.sort(&RBAContentState::comparePriorityLastComeFirst);
    break;
  default:
    isResult = false;
    break;
  }

  return isResult;
}

/**
 * 判定NG制約から再調停リストを取得する
 * @param totalRevisitAllocatables
 * @param allocatable
 * @param falseConstraints
 * @param revisited
 */
void
RBAArbitratorImpl::
collectRevisitAllocatable(std::list<const RBAAllocatable*>* const totalRevisitAllocatables,
        RBAAllocatable*& allocatable,
        std::list<RBAConstraintImpl*>& falseConstraints,
        std::set<const RBAAllocatable*>& revisited)
{
  std::set<const RBAAllocatable*> revisitAllocatablesSet;

  // 再調停をすべきかを判定NGだった制約から判断する
  for(RBAConstraintImpl*& constraint : falseConstraints) {
    // 制約情報取得
    const RBAConstraintInfo* const info {constraint->getInfo()};
    // 再調停候補のアロケータブル
    std::set<const RBAAllocatable*> rightFalseAllocatables;

    if (info->needsRearbitrationFor(allocatable)) {
      info->collectRearbitrationTargetFor(allocatable, rightFalseAllocatables, false);
    }
    if (rightFalseAllocatables.empty()) {
      // 含意でない制約式
      // "現在調停中のアロケータブル"がより"低優先度のアロケータブル"に調停負けしてしまうことを防ぐために、
      // "再調停候補のアロケータブル"に"低優先度のアロケータブル"が含まれている場合は"低優先度のアロケータブル"を再調停する。
      // 調停は優先度順に行われるので、"低優先度のアロケータブル"が"再調停候補のアロケータブル"に含まれることは通常ないが、
      // "低優先度のアロケータブル"が調停された後の"現在調停中のアロケータブル"の再調停で含まれる。
      info->collectFalseAllocatables(rightFalseAllocatables);
      bool isContainsLowPriorityAllocatable {false};
      for(const RBAAllocatable* const rightFalseAllocatable
	    : rightFalseAllocatables) {
        if(RBAAllocatable::compareIndex(allocatable,rightFalseAllocatable)) { // indexは優先度の高いアロケータブルほど小さい
          isContainsLowPriorityAllocatable = true;
          break;
        }
      }
      if(!isContainsLowPriorityAllocatable) {
        continue;
      }
    }

    // 調停中のアロケータブルを再調停対象から外す
    static_cast<void>(rightFalseAllocatables.erase(allocatable));

    // 再調停候補のアロケータブルが、1つでも再調停済なら再々調停は無し。次のコンテンツの割り当てに移る
    for(const RBAAllocatable* const rightFalseAllocatable : rightFalseAllocatables) {
      if(revisited.find(rightFalseAllocatable) != revisited.end()) {
        return;
      }
    }

    // 再調停アロケータブルを設定
    for(const RBAAllocatable* const alloc : rightFalseAllocatables) {
      static_cast<void>(revisitAllocatablesSet.insert(alloc));
    }
  }

  // 再調停アロケータブルがある
  if(!(revisitAllocatablesSet.empty())) {
    // std::setをstd::listに詰め替え
    static_cast<void>(totalRevisitAllocatables->insert(totalRevisitAllocatables->end(), revisitAllocatablesSet.begin(), revisitAllocatablesSet.end()));
    // 再調停エリアを優先度に基づいて低い順にソートする
    // モデルの並び順も考慮するのでindex比較でのソートが必要
    totalRevisitAllocatables->sort(&RBAAllocatable::compareIndex);
  }
}

/**
 * 調停負けの要求キャンセルをするために全コンテント状態のキャンセル確認をする
 */
void
RBAArbitratorImpl::
postArbitrate()
{
#ifdef RBA_USE_LOG
  RBALogManager::cancelRequestLogLine("----Cancel Request----");
#endif
  for(const RBAContentState* const state : model_->getContentStates()) {
#ifdef RBA_USE_LOG
    RBALogManager::cancelRequestLogLine("Content["+
			     state->getOwner()->getElementName()+"::"+
			     state->getElementName()+
			     "] check start");
#endif
    static_cast<void>(cancelChecked_.insert(state));
    if(!result_->isActive(state)) {
#ifdef RBA_USE_LOG
	    RBALogManager::cancelRequestLogLine("  Content["+
				 state->getOwner()->getElementName()+"::"+
				 state->getElementName()+
				 "] is not Active skip");
#endif
      continue;
    }
    if(result_->isAlreadyOutputting(state)) {
#ifdef RBA_USE_LOG
      std::string contTypeName;
      if(state->isViewContentState()) {
        contTypeName = "Visible";
      }
      else {
        contTypeName = "Sounding";
      }
      RBALogManager::cancelRequestLogLine("  Content["+
                                          state->getOwner()->getElementName()+"::"+
                                          state->getElementName()+
                                          "] is "+contTypeName+" skip");
#endif
      continue;
    }

    changeContentStateCancelWithPolicy(state);
  }

#ifdef RBA_USE_LOG
  // 要求キャンセルのカバレッジ向けログ出力
  for(const RBAContentState* state : model_->getContentStates()) {
    std::string contentName = state->getOwner()->getElementName();
    std::string stateName = state->getElementName();
    std::string canceled = isCancel(state) ? "t" : "f";
    RBALogManager::coverageCanceledRequestLogLine(
        contentName + "," + stateName + ',' +canceled);
  }
#endif
}

/**
 * 非表示であるコンテント状態のキャンセル情報を調停結果とキャンセルポリシーに
 * 基づいて変更する
 * @param state
 */
void
RBAArbitratorImpl::
changeContentStateCancelWithPolicy(const RBAContentState* const state)
{
  switch(dynamic_cast<RBAContent*>(state->getOwner())->getContentLoserType()) {
  case RBAContentLoserType::GOOD_LOSER:
#ifdef RBA_USE_LOG
     RBALogManager::cancelRequestLogLine("  Content["+
                              state->getOwner()->getElementName()+"::"+
                              state->getElementName()+
                              "] is Canceled because GOOD_LOSER");
#endif
    setCancel(state, true);
    break;
  case RBAContentLoserType::NEVER_GIVEUP:
#ifdef RBA_USE_LOG
    RBALogManager::cancelRequestLogLine("  Content["+
                             state->getOwner()->getElementName()+"::"+
                             state->getElementName()+
                             "] is not Canceled because NEVER_GIVEUP");
#endif
    setCancel(state, false);
    break;
  case RBAContentLoserType::DO_NOT_GIVEUP_UNTIL_WIN:
    if(state->isModelElementType(RBAModelElementType::ViewContentState)) {
      if(result_->isPreVisible(dynamic_cast<const RBAViewContentStateImpl*>(state))) {
#ifdef RBA_USE_LOG
        RBALogManager::cancelRequestLogLine("  Content["+
                                 state->getOwner()->getElementName()+"::"+
                                 state->getElementName()+
                                 "] is Canceled because DO_NOT_GIVEUP_UNTIL_WIN");
#endif
        setCancel(state, true);
      } else {
#ifdef RBA_USE_LOG
        RBALogManager::cancelRequestLogLine("  Content["+
                                 state->getOwner()->getElementName()+"::"+
                                 state->getElementName()+
                                 "] is not Canceled because DO_NOT_GIVEUP_UNTIL_WIN");
#endif
        setCancel(state, false);
      }
    }
    else {
      if(result_->isPreSounding(dynamic_cast<const RBASoundContentStateImpl*>(state))) {
        setCancel(state, true);
      } else {
        setCancel(state, false);
      }
    }
    break;
  default:
    break;
  }
}

#ifdef RBA_USE_LOG
void
RBAArbitratorImpl::
checkAllConstraints()
{
  std::string log;
  LOG_arbitrateConstraintLogLine("----Check All Constraint----");

  if(simulationMode_) {
    for(const RBAConstraintImpl* constraint : model_->getConstraintImpls()) {
      bool result = const_cast<RBAConstraintImpl*>(constraint)->execute(this);
      if(result == false) {
	result_->addFailedConstraint(constraint);
      }
      if (constraint->isRuntime() == true) {
        log += "online  ";
      } else {
        log += "offline ";
      }
      log += "constraint[" + constraint->getElementName() + "] ";
      log += "result[" + RBALogManager::boolToString(result) + "]\n";
    }
    if (log.empty() != true ) {
      log.erase(log.end() - 1, log.end()); //最後の改行を削除する
    }
  }

}
#endif

bool
RBAArbitratorImpl::
isDefeat(const RBAContentState* const winner, const RBAContentState* const loser) const
{
  bool loserVisible {false}; // 負けコンテンツの表示有無
  bool winnerVisible {false}; // 勝ちコンテンツの表示有無
  const RBAContent* const loserContent {dynamic_cast<RBAContent*>(loser->getOwner())};
  const RBAContent* const winnerContent {dynamic_cast<RBAContent*>(winner->getOwner())};

  // --------------------------------------------------------------------
  // 判定の優先順位
  // loserが表示されているならfalse
  // winnerが全エリア調停済にも関わらず表示されていないならfalse
  // loserが表示されておらず全エリアが調停済で、winnerが表示されているならtrue
  // --------------------------------------------------------------------
  for(const RBAAllocatable* const allocatable : loserContent->getAllocatables()) {
    // エリアが隠蔽されている
    if(allocatable->isHiddenChecked() && allocatable->isHidden()) {
      continue;
    }
    // loserが表示されている
    const RBAContentState* const state {result_->getContentState(allocatable)};
    if(state == loser) {
      loserVisible = true;
      break;
    }
  }
  for(const RBAAllocatable* const allocatable	: winnerContent->getAllocatables()) {
    // エリアが隠蔽されている
    if(allocatable->isHiddenChecked() && allocatable->isHidden()) {
      continue;
    }
    // winnerが表示されている
    const RBAContentState* const state {result_->getContentState(allocatable)};
    if(state == winner) {
      winnerVisible = true;
    }
  }
  if(loserVisible) {
    // loserが表示されているならfalse
    return false;
  }
  else if(!winnerVisible) {
    // winnerが全エリア調停済にも関わらず表示されていないならfalse
    return false;
  }
  else {
    // loserが表示されておらず全エリアが調停済で、winnerが表示されているならtrue
    return true;
  }
}

void
RBAArbitratorImpl::
checkCancelContent() const
{
  for(const RBAViewContentState* const viewState
	: result_->getActiveViewContentStates()) {
    if(result_->isCancel(viewState)) {
      result_->cancelContentState(dynamic_cast<const RBAContentState*>(viewState));
    }
  }
  for(const RBASoundContentState* const soundState
	: result_->getActiveSoundContentStates()) {
    if(result_->isCancel(soundState)) {
      result_->cancelContentState(dynamic_cast<const RBAContentState*>(soundState));
    }
  }
}

/**
 * @brief 表示アロケータブルリスト、非表示アロケータブルリストを更新する
 */
void
RBAArbitratorImpl::
updateResult()
{
  // キャンセルしたコンテントのアクティブを解除する
  result_->updateActiveContentStates();

  // エリアの座標を更新する
  for(auto& area : result_->getVisibleAreas()) {
    const RBAAreaImpl* const areaImpl {dynamic_cast<const RBAAreaImpl*>(area)};
    const auto posCont = model_->findPositionContainerImpl(area->getName());
    const auto sizeObj = result_->getSize(area);
    if((posCont != nullptr) && (sizeObj != nullptr)) {
      const auto offset = posCont->getOffset(sizeObj->getName());
      const_cast<RBAAreaImpl*>(areaImpl)->setOffsetX(offset.first);
      const_cast<RBAAreaImpl*>(areaImpl)->setOffsetY(offset.second);
    }
  }

  // 出力コンテントステートリストを設定
  std::set<const RBAContentState*> outputtingContentStateSet;
  for(auto& alloc : result_->getOutputtingAllocatables()) {
    const auto state = result_->getAllocatedContentState(alloc);
    static_cast<void>(outputtingContentStateSet.insert(state));
  }
  for(auto& state : outputtingContentStateSet) {
    static_cast<void>(result_->addOutputtingContentState(state));
  }
  
  for(auto& state : result_->getActiveContentStates()) {
    // 表示要求で割り当てられたエリアが表示されていなければStanbyContentに設定
    const auto allocs = result_->getAllocatable(state);
    if(allocs.empty()) {
      result_->addStandbyContent(dynamic_cast<RBAContent*>(state->getOwner()));
    }
  }
}

/**
 * ### 結果情報を生成する
 *
 * アニメーション情報(RBAViewAction)を生成し、RBAResultのviewActionsリスト
 * に登録する。\n
 * アニメーション情報の生成パターンは以下の通り。
 *
 * | エリアA(pre)  | エリアB(pre) | エリアA(cur) | エリアB(cur) | type            |
 * |:-:           |:-:       |:-:           |:-:          |:----              |
 * | (none)       | -        | **content**  | -           | TRANSITON_ADD      |
 * | **content**  | -        | (none)       | -           | TRANSITION_REMOVE  |
 * | **contentA** | -        | **contentB** | -           | TRANSITION_REPLACE |
 * | **content**  | (none)   | (none)       | **content** | MOVE               |
 */
void
RBAArbitratorImpl::
createResultData()
{
  std::list<std::unique_ptr<RBAViewAction>> actions;
  // 変化がなかったエリアはチェックしておく
  std::set<const RBAArea*> stableAreas;
  for(const RBAArea* const preArea : result_->getPreVisibleAreas()) {
    if(result_->isVisible(preArea)) {
      const RBAViewContent* const curContent {result_->getContentState(preArea)->getOwner()};
      const RBAViewContent* const preContent {result_->getPreContentState(preArea)->getOwner()};
      if(curContent == preContent) {
        static_cast<void>(stableAreas.insert(preArea));
      }
    }
  }
  // MOVEを調べる
  std::set<const RBAViewContent*> movedContents;
  for(const RBAArea* curArea : result_->getVisibleAreas()) {
    // 今回の表示エリア
    const RBAViewContentState* curState {result_->getContentState(curArea)};
    const RBAViewContent* const curContent {curState->getOwner()};
    // stableなエリアをスキップ
    if(stableAreas.find(curArea) != stableAreas.end()) {
      continue;
    }
    for(const RBAArea* preArea : result_->getPreVisibleAreas()) {
      // stableエリアは変化したと見なさない
      if (stableAreas.find(preArea) != stableAreas.end()) {
    	  continue;
      }
      // 前回の表示エリア
      const RBAViewContent* const preContent {result_->getPreContentState(preArea)->getOwner()};
      if(curContent == preContent) {
        // 一致したコンテンツがあればMOVE
        actions.push_back(std::make_unique<RBAViewMove>(preArea, curArea,
							curState));
        // 移動したコンテントはチェック
        static_cast<void>(movedContents.insert(curState->getOwner()));
      }
    }
  }
  // REMOVEを調べる
  for(const RBAArea* preArea : result_->getPreVisibleAreas()) {
    // stableなエリアをスキップ
    if(stableAreas.find(preArea) != stableAreas.end()) {
      continue;
    }
    const RBAViewContentState* preState {result_->getPreContentState(preArea)};
    // MOVEのコンテンツならスキップ
    if(movedContents.find(preState->getOwner())
       != movedContents.end()) {
      continue;
    }
    if(!result_->isVisible(preArea)) {
      // 前回表示されていたエリアが今回非表示ならばREMOVE
      actions.push_back(std::make_unique<RBAViewTransition>(
          RBAViewActionType::TRANSITION_REMOVE, preArea, preState));
    }
  }
  // MOVE絡みのADD/REMOVEとREPLACEを調べる
  for(const RBAArea* curArea : result_->getVisibleAreas()) {
    // 今回の表示エリア
    // stableなエリアをスキップ
    if(stableAreas.find(curArea) != stableAreas.end()) {
      continue;
    }
    const RBAViewContentState* curState {result_->getContentState(curArea)};
    const RBAViewContent* const curContent {curState->getOwner()};
    const RBAViewContentState* preState {result_->getPreContentState(curArea)};
    // MOVEのコンテンツなら
    if(movedContents.find(curContent) != movedContents.end()) {
      if((preState != nullptr) && (!result_->isVisible(preState))) {
        // 前回表示していたコンテンツが非表示ならREMOVE
        actions.push_back(std::make_unique<RBAViewTransition>(
			  RBAViewActionType::TRANSITION_REMOVE,
			  curArea, preState));
      }
      else {
	continue;
      }
    }
    else if(result_->isPreVisible(curArea)) {
      // 前回も表示エリアだった
      // preがMOVEのコンテンツなら
      const RBAViewContent* const preContent {preState->getOwner()};
      if(movedContents.find(preContent) != movedContents.end()) {
        // 今回表示のコンテンツはADD
        actions.push_back(std::make_unique<RBAViewTransition>(
		          RBAViewActionType::TRANSITION_ADD,
			  curArea, curState));
      }
      else if(curContent != preContent) {
        // コンテントが違うのでREPLACE
        actions.push_back(std::make_unique<RBAViewTransition>(
			  RBAViewActionType::TRANSITION_REPLACE,
			  curArea, preState, curState));
      } else {
        ;
      }
    }
    else {
      // 前回は表示エリアでなかったのでADD
      actions.push_back(std::make_unique<RBAViewTransition>(
			RBAViewActionType::TRANSITION_ADD,
			curArea, curState));
    }
  }

  // ソートして登録
  actions.sort(&compareViewAction);
  for(auto& action : actions) {
    result_->addViewAction(action);
  }
}

void
RBAArbitratorImpl::differenceArbitrate()
{
#ifdef RBA_USE_LOG
  // 要求情報をログに設定
  RBALogManager::setType(RBALogManager::TYPE_REQUEST);
  logRequestArbitration();
  RBALogManager::setType(RBALogManager::TYPE_PREVIOUS_RESULT);
  logPreResultArbitration();
  logRequestForCoverage();
#endif

  for (auto& a : model_->getSortedAllocatables()) {
    a->clearStatus();
  }

  // ----------------------------------------------------------
  // 調停
  // ----------------------------------------------------------
  // 優先度と後勝ち調停（価値調停は今のところ優先度調停と同じ）
#ifdef RBA_USE_LOG
RBALogManager::setType(RBALogManager::TYPE_ARBITRATE);
#endif
  arbitrate(model_->getSortedAllocatables());

  // ----------------------------------------------------------
  // 調停後処理
  // ----------------------------------------------------------
#ifdef RBA_USE_LOG
RBALogManager::setType(RBALogManager::TYPE_CANCEL_REQUEST);
#endif
  // satisfiesConstraints()で制約式評価を行うとき、キャンセル状態がexecute()時と異なっていると、
  // 結果がfalseになる可能性があるため、キャンセル処理前の状態を保存しておく。
  // satisfiesConstraints()で制約式評価を行うときに、この値に戻して評価する。
  resultSetForSatisfiesConstraints_ = std::make_unique<RBAResultSet>(
      *result_->getCurResultSet());
  postArbitrate();

  // オフライン制約を動かす
#ifdef RBA_USE_LOG
RBALogManager::setType(RBALogManager::TYPE_CHECK_ALL_CONSTRAINTS);
  checkAllConstraints();
#endif

  // ----------------------------------------------------------
  // コンテントの状態を更新する
  // ----------------------------------------------------------
  for (auto& c : model_->getContents()){
    const_cast<RBAContent*>(c)->updateStatus(result_.get());
  }

  backupResultSet_ = result_->createBackupCurrentResultSet();
  nextResultSet_ = result_->createNextCurrentResultSet();

#ifdef RBA_USE_LOG
  logResultForCoverage();
#endif
}

bool
RBAArbitratorImpl::
checkConstraints( std::list<RBAConstraintImpl*>& constraints,
                  std::list<RBAConstraintImpl*>& falseConstraints,
                  const RBAAllocatable* const allocatable)
{
  bool containsSkip {false};
  for (const auto& constraint : constraints) {
    const bool isPassed {constraint->execute(this)};
    if (isPassed == false) {
      falseConstraints.push_back(constraint);
    }
    if (constraint->getInfo()->isExceptionBeforeArbitrate()) {
      if (constraint->getInfo()->needsReRearbitrationFor(allocatable)) {
        containsSkip = true;
      }
    }
  }
  return containsSkip;
}

bool
RBAArbitratorImpl::
checkConstraintAndReArbitrate(RBAAllocatable* allocatable,
                              std::set<const RBAAllocatable*>& revisited,
                              const std::int32_t nest,
                              RBAAffectInfo* const affectInfo,
                              RBARollbacker* const parentRollbacker,
                              std::list<RBAConstraintImpl*>& constraints,
                              bool * const isSkipped,
                              const bool isFinal)
{
  bool isPassed {false};
  std::list<RBAConstraintImpl*> falseConstraints;
  const bool containsSkip {checkConstraints(constraints, falseConstraints, allocatable)};
  if(falseConstraints.empty()) {
    *isSkipped = (*isSkipped || containsSkip);
    if(!containsSkip && !*isSkipped && isFinal) {
      static_cast<void>(revisited.insert(allocatable));
    }
    isPassed = true;
  } else {
    std::list<const RBAAllocatable*> revisitAllocatables;
    collectRevisitAllocatable(&revisitAllocatables, allocatable, falseConstraints, revisited);
    if(!(revisitAllocatables.empty())) {
      // 再調停アロケータブルが存在する
      // 再調停失敗時のロールバック向けバックアップ情報を生成
      // 処理速度を考え、再調停が初めて必要になった場合にのみ1回だけインスタンスを生成
       // コンテント割り当て後にバックアップしているので、ロールバック後は割り当てたコンテントをNULLに戻す必要有り
      std::shared_ptr<RBARollbacker> rollbacker {std::make_shared<RBARollbacker>()}; // 再調停失敗時のロールバック情報
      if (parentRollbacker != nullptr) {
        parentRollbacker->addChild(rollbacker);
      }
      rollbacker->backup(revisitAllocatables);
      // 先に再調停するアロケータブルを全て初期化
      for (auto& a : revisitAllocatables) {
        const_cast<RBAAllocatable*>(a)->clearChecked();
      }
      // --------------------------------------------------
      // 再調停候補リストから、再帰内で再調停済でないアロケータブルを再調停する
      // --------------------------------------------------
      static_cast<void>(revisited.insert(allocatable));
      for(const RBAAllocatable* const revisitAllocatable : revisitAllocatables) {
        LOG_arbitrateAreaLogLine( "    " +
            revisitAllocatable->getSymbol() + "["
                                  + revisitAllocatable->getElementName()
                                  + "] revisit allocatable check start");
        arbitrateAllocatable(const_cast<RBAAllocatable*>(revisitAllocatable),
			     revisited, nest + 1, affectInfo, rollbacker.get());
      }
      for(const RBAAllocatable* const revisitAllocatable : revisitAllocatables) {
        static_cast<void>(revisited.erase(revisitAllocatable));
      }
      // --------------------------------------------------
      // 再調停によりコンテントの割り当てが成功するようになったかを確認する
      // --------------------------------------------------
      falseConstraints.clear();
      static_cast<void>(checkConstraints(constraints, falseConstraints, allocatable));
      if (falseConstraints.empty()) {
        // 再調停によってアロケータブルの割当コンテンツが確定したので、
         // ループを抜けて次のアロケータブルへ
        // 再帰によって自アロケータブルの再調停がされて割当コンテンツがなくなるケースも
         // あるが、全コンテンツチェックが済のため次のアロケータブルへ
        isPassed = true;
      } else {
        rollbacker->rollback(); // 調停状態と影響情報をロールバックする
        if (parentRollbacker != nullptr) {
          parentRollbacker->removeChild(rollbacker);
        }
      }
    }
  }
  if (isPassed == false) {
    //調停中のエリアに影響を与えたエリアを収集する
    std::set<const RBAAllocatable*> allocatablesWhichHaveAffectedToThisAllocatable;

    for (const RBAConstraintImpl* const constraint : falseConstraints) {
      constraint->getInfo()->collectAffectedAllocatables(
          false, allocatablesWhichHaveAffectedToThisAllocatable, false,
          false);
    }
    static_cast<void>(allocatablesWhichHaveAffectedToThisAllocatable.erase(allocatable));

    //調停中のエリアが影響を受けたエリアを記録する
    //逆に言えば、調停中のエリアに影響を与えたエリアに、調停中のエリアに影響を与えたことを記録する
    //AffectInfoには影響を与えたエリアの再調停済みのものを覚えておくので、すでに再調停済みのものは記憶しない
    for (const RBAAllocatable* const a : allocatablesWhichHaveAffectedToThisAllocatable) {
      if (!(affectInfo->alreadyKnowsThatFormerHasAffectedToLatter(a,
                                                                  allocatable))) {
        const_cast<RBAAllocatable*>(a)->addAllocatableWhichHasBeenAffectedByYou(
            allocatable);
        affectInfo->addInfoThatFormerAffectedToLatter(a, allocatable);
      }
    }
  }
  return isPassed;
}

bool
RBAArbitratorImpl::
isCancelChecked(const RBAContentState* const state) const
{
  return cancelChecked_.find(state) != cancelChecked_.end();
}

void
RBAArbitratorImpl::
setCancel(const RBAContentState* const state, const bool checked)
{
  result_->setCancel(state, checked);
}

bool
RBAArbitratorImpl::
isCancel(const RBAContentState* const state) const
{
  if(state->isViewContentState()) {
    return result_->isCancel(state);
  }
  else {
    return result_->isCancel(state);
  }
}

void
RBAArbitratorImpl::
getSortedContentStates(const RBAAllocatable* const allocatable,
                       std::list<const RBAContentState*>& contentStates) const
{
  for (const RBAContent* const content : allocatable->getInternalContents()) {
    const RBAContentState* const state {result_->getActiveState(content)};
    if (state != nullptr) {
      contentStates.push_back(state);
#ifdef RBA_USE_LOG
    } else {
      RBALogManager::arbitrateContentLogLine(
          "  Content[" + content->getElementName() + "] is not Active skip");
#endif
    }
  }
  static_cast<void>(sortContentStates(allocatable, contentStates));
  // 未割り当て時の制約式評価をするため、最後にnullを追加
  contentStates.push_back(nullptr);
}

std::int32_t
RBAArbitratorImpl::
getViewActionPriority(const RBAViewActionType viewActionType)
{
  std::int32_t result{0};

  switch(viewActionType) {
  case RBAViewActionType::TRANSITION_REMOVE:
    result = 4;
    break;
  case RBAViewActionType::MOVE:
    result = 3;
    break;
  case RBAViewActionType::TRANSITION_ADD:
    result = 2;
    break;
  case RBAViewActionType::TRANSITION_REPLACE:
    result = 1;
    break;
  default:
    break;
  }

  return result;
}

bool
RBAArbitratorImpl::
compareViewAction(const std::unique_ptr<RBAViewAction>& lhs,
                  const std::unique_ptr<RBAViewAction>& rhs)
{
  const std::int32_t lval {getViewActionPriority(lhs->getViewActionType())};
  const std::int32_t rval {getViewActionPriority(rhs->getViewActionType())};

  return lval > rval;
}

RBAResultImpl*
RBAArbitratorImpl::getResult() const
{
  return result_.get();
}

void RBAArbitratorImpl::setResult(std::unique_ptr<RBAResultImpl> result)
{
  result_ = std::move(result);
}

RBAArbitrator* RBAArbitratorImpl::getArb() const
{
  return arb_;
}

void RBAArbitratorImpl::setArb(RBAArbitrator* const arb)
{
  arb_ = arb;
}

RBAModelImpl* RBAArbitratorImpl::getModel() const
{
  return model_;
}

void RBAArbitratorImpl::setModel(RBAModelImpl* const model)
{
  model_ = model;
}

std::set<const RBAContentState*>& RBAArbitratorImpl::getCancelChecked()
{
  return cancelChecked_;
}

std::unique_ptr<RBAResultImpl>& RBAArbitratorImpl::getResultRef() const
{
  return result_;
}

std::unique_ptr<RBAResultSet>& RBAArbitratorImpl::getNextResultSet()
{
  return nextResultSet_;
}

void RBAArbitratorImpl::setNextResultSet(std::unique_ptr<RBAResultSet> nextResultSet)
{
  nextResultSet_ = std::move(nextResultSet);
}

std::unique_ptr<RBAResultSet>& RBAArbitratorImpl::getBackupResultSet()
{
  return backupResultSet_;
}
  
void RBAArbitratorImpl::setBackupResultSet(std::unique_ptr<RBAResultSet> backupResultSet)
{
  backupResultSet_ = std::move(backupResultSet);
}

std::unique_ptr<RBAResultSet>& RBAArbitratorImpl::getReservedResultSet()
{
  return reservedResultSet_;
}

void RBAArbitratorImpl::setReservedResultSet(std::unique_ptr<RBAResultSet> reservedResultSet)
{
  reservedResultSet_ = std::move(reservedResultSet);
}

std::recursive_mutex& RBAArbitratorImpl::getMutex() const
{
  return mutex_;
}

#ifdef RBA_USE_LOG
bool RBAArbitratorImpl::getSimulationMode()
{
  return simulationMode_;
}

void RBAArbitratorImpl::setSimulationMode(bool simulationMode)
{
  simulationMode_ = simulationMode;
}
#endif

std::deque<std::unique_ptr<RBARequestQueMember>>& RBAArbitratorImpl::getRequestQue()
{
  return requestQue_;
}

#ifdef RBA_USE_LOG
/**
 * ログビュー向けにリクエスト情報を出力する
 */
void
RBAArbitratorImpl::logRequestArbitration()
{
  const std::list<const RBAAllocatable*> allocatables =
      model_->getAllocatables();
  RBALogManager::requestLogLine("----Request Information----");
  RBALogManager::requestLogLine(
      "Allocatable Count:" + std::to_string(allocatables.size()));
  for (const RBAAllocatable* allocatable : allocatables) {
    RBALogManager::requestLogLine(
        "  " + allocatable->getSymbol() + "[" + allocatable->getElementName()
            + "] policy[" + allocatable->getArbitrationPolicyString()
            + "] visibility[" + allocatable->getVisibilityString() + "]");
  }

  const std::list<const RBAContentState*> contentStates = model_
      ->getContentStates();
  RBALogManager::requestLogLine(
      "ContentState Count:" + std::to_string(contentStates.size()));
  for (const RBAContentState* contentState : contentStates) {
    std::string active;
    if (contentState->getModelElementType() == RBAModelElementType::ViewContentState) {
      active = RBALogManager::boolToString(
          result_->isActive(
              dynamic_cast<const RBAViewContentState*>(contentState)));
    } else {
      active = RBALogManager::boolToString(
          result_->isActive(
              dynamic_cast<const RBASoundContentState*>(contentState)));
    }
    RBALogManager::requestLogLine(
        "  " + dynamic_cast<RBAContent*>(contentState->getOwner())->getSymbol() + "["
            + contentState->getOwner()->getElementName() + "::"
            + contentState->getElementName() + "] priority["
            + contentState->getPriorityString() + "] isActive[" + active
            + "] order[" + contentState->getOrderString() + "]");
  }

  const std::list<const RBAScene*> scenes = model_->getScenes();
  RBALogManager::requestLogLine("Scene Count:" + std::to_string(scenes.size()));
  for (const RBAScene* scene : scenes) {
    RBALogManager::requestLogLine(
        "  Scene[" + scene->getName() + "] isActive["
            + RBALogManager::boolToString(result_->isActive(scene))
            + "]");
  }

  std::list<RBAConstraint*> constraints = model_->getConstraints();
  RBALogManager::requestLogLine(
      "Constraint Count:" + std::to_string(constraints.size()));
  for (RBAConstraint* constraint : constraints) {
    RBAConstraintImpl* impl = dynamic_cast<RBAConstraintImpl*>(constraint);
    RBALogManager::requestLogLine(
        "  Constraint[" + impl->getName() + "] Expression["
            + impl->getExpression()->getExpressionText() + "] runtime["
            + RBALogManager::boolToString(impl->isRuntime()) + "]");
  }

}

/**
 * ログビュー向けに前回調停結果を出力する
 */
void
RBAArbitratorImpl::logPreResultArbitration()
{
  RBALogManager::resultLogLine("----Previous Result Information----");

  auto allocs = model_->getAllocatables();
  RBALogManager::resultLogLine("Allocatable TotalCount:"
                               + std::to_string(allocs.size()));
  for (auto& alloc : allocs) {
    auto contentState = result_->getPreContentState(alloc);
    auto hidden = result_->isPreHidden(alloc);
    std::string str = "  " + alloc->getSymbol()
                      + "[" + alloc->getElementName() + "] Content[";
    if (contentState == nullptr) {
      str += "null";
    } else {
      str += contentState->getOwner()->getElementName()
             + "::" + contentState->getElementName();
    }
    str += "] " + alloc->getHiddenSymbol()
           + "[" + RBALogManager::boolToString(hidden) + "]";
    if (alloc->isZone() == true) {
      str += " attenuated[";
      str += RBALogManager::boolToString(
              result_->isPreAttenuated(dynamic_cast<const RBAZone*>(alloc)));
      str += "]";
    }
    RBALogManager::resultLogLine(str);
    if (contentState && !hidden) {
      RBALogManager::coveragePrevResultLogLine(
        "A," + alloc->getElementName() + ","
        + contentState->getOwner()->getElementName() + ","
        + contentState->getElementName());
    }
  }

  auto contents = model_->getContents();
  RBALogManager::resultLogLine("Content TotalCount:"
                               + std::to_string(contents.size()));
  for (auto& content : contents) {
    auto state = result_->getPreActiveState(content);
    bool isOutputting = false;
    bool isActive = false;
    if (state != nullptr) {
      isActive = true;
      isOutputting = result_->isPreOutputting(state);
    }
    RBALogManager::resultLogLine(
      "  " + content->getSymbol() + "[" + content->getElementName() + "] "
      + content->getVisibleSymbol() + "["
      + RBALogManager::boolToString(isOutputting) + "] active["
      + RBALogManager::boolToString(isActive) + "]");
    for (auto alloc : content->getAllocatables()) {
      auto allocatedState = result_->getPreContentState(alloc);
      if ((allocatedState != nullptr)
          && (allocatedState->getOwner() == content)) {
        RBALogManager::resultLogLine(
          "    allocated " + alloc->getSymbol() + "["
          + alloc->getElementName() + "]");
      }
    }
  }
}

/**
 * ログビュー向けに今回調停結果を出力する
 */
void
RBAArbitratorImpl::logResultArbitration()
{
  RBALogManager::resultLogLine("----Result Information----");

  const std::list<const RBAAllocatable*> allocatables
    = model_->getAllocatables();
  RBALogManager::resultLogLine("Allocatable TotalCount:" + std::to_string(allocatables.size()));
  for(const RBAAllocatable* allocatable : allocatables) {
    const RBAContentState* contentState = result_->getContentState(allocatable);
    std::string str = "  ";
    str += allocatable->getSymbol();
    str += "[";
    str += allocatable->getElementName();
    str += "] Content[";
    if (contentState == nullptr) {
      str += "null";
    } else {
      str += contentState->getOwner()->getElementName() + "::"
        + contentState->getElementName();
    }
    str += "] ";
    str += allocatable->getHiddenSymbol();
    str += "[";
    str += RBALogManager::boolToString(result_->isHidden(allocatable));
    str += "]";
    if (allocatable->isZone() == true) {
      str += " attenuated[";
      str += RBALogManager::boolToString(result_->isAttenuated(dynamic_cast<const RBAZone*>(allocatable)));
      str += "]";
    }
    RBALogManager::resultLogLine(str);
  }

  const std::list<const RBAContent*> contents = model_->getContents();
  RBALogManager::resultLogLine("Content TotalCount:" + std::to_string(contents.size()));
  for(const RBAContent* content : contents) {
    bool isOutputting = false;
    bool isCancel = false;
    const RBAContentState* state = result_->getActiveState(content);
    if(state != nullptr) {
      isOutputting = result_->isOutputting(state);
    } else {
      for(const RBAContentState* state : content->getStates()) {
        isCancel |= result_->isCancel(state);
      }
    }
    RBALogManager::resultLogLine("  "
        + content->getSymbol()
        + "["
        + content->getElementName()
        + "] "
        + content->getVisibleSymbol()
        + "["
        + RBALogManager::boolToString(isOutputting)
        + "] cancel["
        + RBALogManager::boolToString(isCancel)
        + "]");
    for(const RBAAllocatable* allocatable : content->getAllocatables()) {
      const RBAContentState* allocatedState
	= result_->getContentState(allocatable);
      if((allocatedState != nullptr) && (allocatedState->getOwner() == content)) {
        RBALogManager::resultLogLine("    allocated "
                                     + allocatable->getSymbol() + "["
                                     + allocatable->getElementName() + "]");
      }
    }
  }
}

/**
 * カバレッジ向け：要求情報を出力する
 */
void
RBAArbitratorImpl::logRequestForCoverage()
{
  for(const RBAContentState* contentState : model_->getContentStates()) {
    std::ostringstream oss;
    oss << "C,";
    if(result_->isActive(contentState)) {
      oss << "on,";
    }
    else {
      oss << "off,";
    }
    oss << contentState->getOwner()->getElementName() << ",";
    oss << contentState->getElementName() << ",";
    oss << contentState->getContentStateOrder();
    RBALogManager::coverageRequestLogLine(oss.str());
  }
  for(const RBAScene* scene : model_->getScenes()) {
    std::ostringstream oss;
    oss << "S,";
    if(result_->isActive(scene)) {
      oss << "on,";
    }
    else {
      oss << "off,";
    }
    oss << scene->getName();
    for(const auto& name : scene->getPropertyNames()) {
      std::int32_t value {result_->getSceneProperty(scene, name)};
      oss << ",";
      oss << name;
      oss << ":";
      oss << value;
    }
    RBALogManager::coverageRequestLogLine(oss.str());
  }
}

/**
 * カバレッジ向け：結果情報を出力する
 */
void
RBAArbitratorImpl::logResultForCoverage()
{
  for(const RBAAllocatable* allocatable : model_->getAllocatables()) {
    std::ostringstream oss;
    oss << "A,";
    oss << allocatable->getElementName() + ",";
    const RBAContentState* contentState = result_->getContentState(allocatable);
    if((contentState != nullptr) && (!result_->isHidden(allocatable))) {
      oss << contentState->getOwner()->getElementName();
    }
    RBALogManager::coverageResultLogLine(oss.str());
  }
}

void
RBAArbitratorImpl::setLogToResult()
{
  std::ostringstream oss;
  oss << RBALogManager::getAllConstraintLog();
  oss << RBALogManager::getRequestLog();
  oss << RBALogManager::getPreviousResultLog();
  oss << RBALogManager::getArbitrateLog();
  oss << RBALogManager::getCancelRequestLog();
  oss << RBALogManager::getCheckAllConstraintLog();
  oss << RBALogManager::getResultLog();
  result_->setLog(oss.str());
}
#endif

}
