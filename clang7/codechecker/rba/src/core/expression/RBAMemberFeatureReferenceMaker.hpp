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

/// @file  RBAMemberFeatureReferenceMaker.cpp
/// @brief ObjectReference of property object generator class header

#ifndef RBAMEMBERFEATUREREFERENCEMAKER_HPP
#define RBAMEMBERFEATUREREFERENCEMAKER_HPP

#include "RBAObjectReferenceMaker.hpp"

namespace rba
{

class RBARuleObject;

/// @brief ObjectReference of property object generator class
class RBAMemberFeatureReferenceMaker : public RBAObjectReferenceMaker
{
public:
  RBAMemberFeatureReferenceMaker();
  RBAMemberFeatureReferenceMaker(const RBAMemberFeatureReferenceMaker&)=delete;
  RBAMemberFeatureReferenceMaker(const RBAMemberFeatureReferenceMaker&&)=delete;
  RBAMemberFeatureReferenceMaker& operator=(const RBAMemberFeatureReferenceMaker&)=delete;
  RBAMemberFeatureReferenceMaker& operator=(const RBAMemberFeatureReferenceMaker&&)=delete;
  virtual ~RBAMemberFeatureReferenceMaker()=default;

protected:
  /// @brief generate an empty instance
  /// @details generate an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief Set model element attributes for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store generated object
  /// @param[in,out] owner Parent object (Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner) override;
private:
  const RBARuleObject* getRuleObject(const RBAJsonElement* const jsonElem,
                                     RBAModelImpl* const model);
};

}

#endif
