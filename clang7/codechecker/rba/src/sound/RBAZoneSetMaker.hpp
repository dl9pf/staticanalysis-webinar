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
/// @file  RBAZoneSetMaker.hpp
/// @brief ZoneSet object generator class header

#ifndef RBAZONESETMAKER_HPP
#define RBAZONESETMAKER_HPP

#include "RBAAllocatableSetMaker.hpp"

namespace rba
{

/// @brief ZoneSet  object generator class
class RBAZoneSetMaker : public RBAAllocatableSetMaker
{
public:
  RBAZoneSetMaker();
  RBAZoneSetMaker(const RBAZoneSetMaker&)=delete;
  RBAZoneSetMaker(const RBAZoneSetMaker&&)=delete;
  RBAZoneSetMaker& operator=(const RBAZoneSetMaker&)=delete;
  RBAZoneSetMaker& operator=(const RBAZoneSetMaker&&)=delete;
  virtual ~RBAZoneSetMaker()=default;

protected:
  /// @brief Empty instanciation
  /// @details Create an empty instance of unique_ptr in a derived class
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief Set model element attributes for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store generated RBARuleObjectMaker
  /// @param[in,out] owner Parent object (Not in use)
  RBAModelElement* setProperty(RBAModelElement* element,
                               const RBAJsonElement* jsonElem,
                               RBAModelImpl* model,
                               RBAModelElement* owner=nullptr) override;

};

}

#endif
