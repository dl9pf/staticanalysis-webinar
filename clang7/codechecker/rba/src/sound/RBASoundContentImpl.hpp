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
 * Sound Content implementation class header
 */

#ifndef RBASOUNDCONTENTIMPL_HPP
#define RBASOUNDCONTENTIMPL_HPP

#include <string>
#include "RBASoundContent.hpp"
#include "RBAContent.hpp"

namespace rba
{

class RBASoundContentState;
class RBAZone;
class RBAZoneImpl;
class RBASoundContentStateImpl;

class DLL_EXPORT RBASoundContentImpl : public RBASoundContent, public RBAContent
{
public:
  explicit RBASoundContentImpl(const std::string& name="");
  RBASoundContentImpl(const RBASoundContentImpl&)=delete;
  RBASoundContentImpl(const RBASoundContentImpl&&)=delete;
  RBASoundContentImpl& operator=(const RBASoundContentImpl&)=delete;
  RBASoundContentImpl& operator=(const RBASoundContentImpl&&)=delete;
  virtual ~RBASoundContentImpl()=default;

public:
  bool isSoundContent() const override;
  std::string getName() const override;
  const std::list<const RBASoundContentState*>& getContentStates() const override;
  const std::list<const RBAZone*>& getZones() const override;
  RBAContentLoserType getLoserType() const override;

  RBAModelElementType getModelElementType() const override;

  // Log
#ifdef RBA_USE_LOG
  std::string getSymbol() const override;
  std::string getVisibleSymbol() const override;
#endif

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  mutable std::list<const RBASoundContentState*> externStates_;
  mutable std::list<const RBAZone*> externZones_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
