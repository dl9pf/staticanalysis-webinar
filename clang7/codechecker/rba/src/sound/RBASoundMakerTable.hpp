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
/// @file  RBASoundMakerTable.hpp
/// @brief Sound element maker table class header

#ifndef RBASOUNDMAKERTABLE_HPP
#define RBASOUNDMAKERTABLE_HPP

#include <functional>
#include "RBAAbstractMakerTable.hpp"

namespace rba
{

class DLL_EXPORT RBASoundMakerTable : public RBAAbstractMakerTable
{
public:
  RBASoundMakerTable();
  RBASoundMakerTable(const RBASoundMakerTable&)=delete;
  RBASoundMakerTable(const RBASoundMakerTable&&)=delete;
  RBASoundMakerTable& operator=(const RBASoundMakerTable&)=delete;
  RBASoundMakerTable& operator=(const RBASoundMakerTable&&)=delete;
  virtual ~RBASoundMakerTable()=default;

public:
  std::list<std::unique_ptr<RBAModelElementMaker>> getMakers() const override;

};

}

#endif
