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
 * RBAViewMove.hpp
 */

#ifndef RBAVIEWMOVE_HPP
#define RBAVIEWMOVE_HPP

#include "RBAViewActionType.hpp"
#include "RBAViewAction.hpp"

namespace rba {

class RBAArea;
class RBAViewContent;
class RBAViewContentState;

class DLL_EXPORT RBAViewMove : public RBAViewAction
{
public:
  RBAViewMove(const RBAArea* const newFromArea, const RBAArea* const newToArea,
	      const RBAViewContentState* const newContentState);
  RBAViewMove(const RBAViewMove& viewMove);
  RBAViewMove(const RBAViewMove&&)=delete;
  RBAViewMove& operator=(const RBAViewMove&)=delete;
  RBAViewMove& operator=(const RBAViewMove&&)=delete;
  virtual ~RBAViewMove()=default;

  bool operator==(const RBAViewAction& viewAction) override;

public:
  const RBAArea* getFromArea() const override;
  const RBAArea* getToArea() const override;
  const RBAViewContent* getContent() const override;
  const RBAViewContentState* getContentState() const override;
  RBAViewActionType getViewActionType() const override;

private:
  const RBAArea* fromArea_ {nullptr};
  const RBAArea* toArea_ {nullptr};
  const RBAViewContentState* contentState_ {nullptr};

};

}

#endif
