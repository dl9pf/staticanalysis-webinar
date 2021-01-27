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
 * Content class header
 */

#ifndef RBACONTENT_HPP
#define RBACONTENT_HPP

#include <memory>
#include <set>
#include "RBAAbstractContent.hpp"
#include "RBAAllocatableSet.hpp"
#include "RBAContentLoserType.hpp"

namespace rba
{

class RBAArbitratorImpl;
class RBAAllocatable;
class RBAContentState;
class RBAResultImpl;
class RBAResultSet;
class RBAExpression;
class RBASize;

class DLL_EXPORT RBAContent : public RBAAbstractContent
{
public:
  explicit RBAContent(const std::string& name="");
  RBAContent(const RBAContent&)=delete;
  RBAContent(const RBAContent&&)=delete;
  RBAContent& operator=(const RBAContent&)=delete;
  RBAContent& operator=(const RBAContent&&)=delete;
  virtual ~RBAContent()=default;

public:
  virtual bool isViewContent() const;
  virtual bool isSoundContent() const;

  const std::list<const RBAContentState*>& getStates() const;
  void addState(const RBAContentState* const state);
  const std::list<const RBAAllocatable*>& getAllocatables() const;
  void addAllocatable(const RBAAllocatable* const alloc);
  RBAContentLoserType getContentLoserType() const;
  void setLoserType(const RBAContentLoserType newLoserType);
  const RBAAllocatableSet* getAllocatableSet() const;
  void updateRequestStatus(RBAResultSet* const resultset, const bool isOnRequest);
  void updateStatus(RBAResultImpl* const result);
  virtual const std::list<const RBASize*>& getSizes() const;

#ifdef RBA_USE_LOG
  virtual std::string getSymbol() const = 0;
  virtual std::string getVisibleSymbol() const = 0;
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBAContentState*> states_;
  std::unique_ptr<RBAAllocatableSet> allocatableSet_ {std::make_unique<RBAAllocatableSet>()};
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  RBAContentLoserType loserType_ {RBAContentLoserType::DO_NOT_GIVEUP_UNTIL_WIN};

};

}

#endif
