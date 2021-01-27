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
/// @file  RBAViewContentSetMaker.hpp
/// @brief ViewContentSet object geneation class header

#ifndef RBAVIEWCONTENTSETMAKER_HPP
#define RBAVIEWCONTENTSETMAKER_HPP

#include "RBAContentSetMaker.hpp"

namespace rba
{

/// @brief ViewContentSet object geneation class
class RBAViewContentSetMaker : public RBAContentSetMaker
{
public:
  RBAViewContentSetMaker();
  RBAViewContentSetMaker(const RBAViewContentSetMaker&)=delete;
  RBAViewContentSetMaker(const RBAViewContentSetMaker&&)=delete;
  RBAViewContentSetMaker& operator=(const RBAViewContentSetMaker&)=delete;
  RBAViewContentSetMaker& operator=(const RBAViewContentSetMaker&&)=delete;
  virtual ~RBAViewContentSetMaker()=default;

protected:
  /// @brief create empty instance
  /// @details Create an empty instance of unique_ptr in your derived class.
  /// @return unique_ptr for instance
  std::unique_ptr<RBAModelElement> createInstance(const std::string& name="") override;

  /// @brief Set model element attributes for each derived class
  /// @param[in] JSON element of jsonElem ModelElement
  /// @param[in] model Model to save the generated object
  /// @param[in,out] owner Parent object (unused)
  RBAModelElement* setProperty(RBAModelElement* element,
                               const RBAJsonElement* jsonElem,
                               RBAModelImpl* model,
                               RBAModelElement* owner=nullptr) override;

};

}

#endif
