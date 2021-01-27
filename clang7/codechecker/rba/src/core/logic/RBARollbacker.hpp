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
 * Rollbacker (rollback of arbitration results) class header
 */

#ifndef RBARROLLBACKER_HPP
#define RBARROLLBACKER_HPP

#include <unordered_map>
#include <memory>
#include <list>

namespace rba
{
class RBAModel;
class RBAAllocatable;
class RBAArbitratorImpl;

class RBARollbacker
{
 public:
  RBARollbacker()=default;
  RBARollbacker(const RBARollbacker&)=delete;
  RBARollbacker(const RBARollbacker&&)=delete;
  RBARollbacker& operator=(const RBARollbacker&)=delete;
  RBARollbacker& operator=(const RBARollbacker&&)=delete;
  virtual ~RBARollbacker() noexcept;

  /**
   * Register a backup for child re-arbitration when execute re-arbitration 
   * during re-arbitration.
   * Restore child backup when rolling back
   */
  void addChild(const std::shared_ptr<RBARollbacker> child);

  void removeChild(const std::shared_ptr<RBARollbacker> child);

  /**
   * Back up arbitration status and impact information.
   * (Only "Allocatable" that directly arbitration is backed up)
   * Child will back up re-arbitraion during execution of re-aribitration.
   *
   * Backing up all "Allocatable" on a model is inefficient, 
   * so back up only those that execute re-arbitration
   */
  void backup(std::list<const RBAAllocatable*>& backuplist);

  /**
   * Roll back the arbitration state and impact information to 
   * the state when the instance was created
   */
  void rollback();

 private:
  /**
   * @brief Copy Allocable arbitration state
   * @param from source of copy
   * @param to destination of copy
   */
  void copyAllocatable(const RBAAllocatable* const from, RBAAllocatable* const to);

  std::list<std::shared_ptr<RBARollbacker>> children_;
  // Rollback information when arbitration fails
  std::unordered_map<const RBAAllocatable*, std::unique_ptr<RBAAllocatable>> backupMap_; 
};

}

#endif
