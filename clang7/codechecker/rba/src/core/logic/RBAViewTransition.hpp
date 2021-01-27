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
 * RBAViewTransition.hpp
 */

#ifndef RBAVIEWTRANSITION_HPP
#define RBAVIEWTRANSITION_HPP

#include "RBAViewAction.hpp"

namespace rba {

class RBAArea;

class DLL_EXPORT RBAViewTransition : public RBAViewAction
{
public:
  RBAViewTransition(const RBAViewActionType newViewActionType, const RBAArea* const newArea,
                    const RBAViewContentState* const newContentState1,
                    const RBAViewContentState* const newContentState2 = nullptr);
  RBAViewTransition(const RBAViewTransition& viewTrans);
  RBAViewTransition(const RBAViewTransition&&)=delete;
  RBAViewTransition& operator=(const RBAViewTransition&)=delete;
  RBAViewTransition& operator=(const RBAViewTransition&&)=delete;
  virtual ~RBAViewTransition()=default;

  bool operator==(const RBAViewAction& viewAction) override;

public:
  const RBAArea* getArea() const override;

  const RBAViewContent* getFromContent() const override;
  const RBAViewContent* getToContent() const override;
  const RBAViewContentState* getFromContentState() const override;
  const RBAViewContentState* getToContentState() const override;
  const RBAViewContent* getContent() const override;
  const RBAViewContentState* getContentState() const override;
  RBAViewActionType getViewActionType() const override;

private:
  RBAViewActionType viewActionType_;
  const RBAArea* area_;
  const RBAViewContentState* contentState1_;
  const RBAViewContentState* contentState2_;
};

}

#endif
