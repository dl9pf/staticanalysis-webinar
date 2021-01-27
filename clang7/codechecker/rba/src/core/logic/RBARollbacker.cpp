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
 * Rollbacker (rollback of arbitration results) class implementation
 */

#include "RBARollbacker.hpp"
#include "RBAModelImpl.hpp"
#include "RBABackUpAllocatable.hpp"
#include "RBAArbitratorImpl.hpp"

namespace rba
{

RBARollbacker::~RBARollbacker() noexcept
{
  children_.clear();
}

void
RBARollbacker::addChild(const std::shared_ptr<RBARollbacker> child)
{
  children_.push_back(child);
}

void
RBARollbacker::removeChild(const std::shared_ptr<RBARollbacker> child)
{
  children_.remove(child);
}

void
RBARollbacker::backup(std::list<const RBAAllocatable*>& backuplist)
{
  backupMap_.clear();
  for(const RBAAllocatable* const original : backuplist) {
    std::unique_ptr<RBAAllocatable> backupObj
      {std::make_unique<RBABackUpAllocatable>("backup_"
                                               + original->getElementName())};
    copyAllocatable(original, backupObj.get());
    backupMap_[original] = std::move(backupObj);
  }
}

void
RBARollbacker::rollback()
{
  for (auto& Child : children_) {
    // @Deviation (MEM05-CPP,Rule-7_5_4,A7-5-2)
    // [Contents that deviate from the rules]
    //  rollback() is called recursively
    // [Explanation that there is no problem if you deviate from the rules]
    //  RBARollbacker is created each time the re-arbitration nest becomes 
    //  deeper, but since the infinite loop prevention process is implemented 
    //  in re-arbitration, stack overflow does not occur.
    Child->rollback();
  }
  for(auto itr = backupMap_.begin(); itr != backupMap_.end(); ++itr) {
    const RBAAllocatable* const original {itr->first};
    const RBAAllocatable* const backupVal {itr->second.get()};
    copyAllocatable(backupVal, const_cast<RBAAllocatable*>(original));
  }
}

void
RBARollbacker::copyAllocatable(const RBAAllocatable* const from,
			       RBAAllocatable* const to)
{
  to->setHiddenChecked(from->isHiddenChecked());
  to->setHidden(from->isHidden());
  to->setChecked(from->isChecked());
  to->setState(from->getState());
  to->clearAllocatablesAffectedByYou();
  for(const RBAAllocatable* const allocatable : from->getAllocatablesAffectedByYou()) {
    to->addAllocatableWhichHasBeenAffectedByYou(allocatable);
  }
  to->setAttenuateChecked(from->isAttenuateChecked());
  to->setAttenuated(from->isAttenuated());
}

}
