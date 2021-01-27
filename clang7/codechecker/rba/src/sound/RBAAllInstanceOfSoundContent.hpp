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
 * AllInstanceOfSoundContent class header
 */

#ifndef RBAALLINSRTANCEOFSOUNDCONTENTIMPL_HPP
#define RBAALLINSRTANCEOFSOUNDCONTENTIMPL_HPP

#include "RBASetExpression.hpp"
#include "RBASoundContentSet.hpp"

namespace rba {

class DLL_EXPORT RBAAllInstanceOfSoundContent : public RBASetExpression
{
public:
  RBAAllInstanceOfSoundContent()=default;
  RBAAllInstanceOfSoundContent(const RBAAllInstanceOfSoundContent&)=delete;
  RBAAllInstanceOfSoundContent(const RBAAllInstanceOfSoundContent&&)=delete;
  RBAAllInstanceOfSoundContent& operator=(const RBAAllInstanceOfSoundContent&)=delete;
  RBAAllInstanceOfSoundContent& operator=(const RBAAllInstanceOfSoundContent&&)=delete;
  virtual ~RBAAllInstanceOfSoundContent()=default;

public:
  void accept(RBAExpressionVisitor& visitor) override;
  RBAModelElementType getModelElementType() const override;
  const RBARuleObject* getReferenceObjectCore(RBAConstraintInfo* info,
                                              RBAArbitratorImpl* arb) const override;
  void setContents(const std::list<const RBASoundContentImpl*>& contents);

  // Log
#ifdef RBA_USE_LOG
  const std::string getExpressionText() const override;
  const std::string getCoverageExpressionText() const override;
#endif

private:
  RBASoundContentSet allSoundContentSet_;

};

}

#endif
