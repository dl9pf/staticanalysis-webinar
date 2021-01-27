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
/// @file  RBAViewMakerTable.hpp
/// @brief ViewMakerTable class header

#ifndef RBAVIEWMAKERTABLE_HPP
#define RBAVIEWMAKERTABLE_HPP

#include <functional>
#include "RBAAbstractMakerTable.hpp"

namespace rba
{

class DLL_EXPORT RBAViewMakerTable : public RBAAbstractMakerTable
{
public:
  RBAViewMakerTable();
  RBAViewMakerTable(const RBAViewMakerTable&)=delete;
  RBAViewMakerTable(const RBAViewMakerTable&&)=delete;
  RBAViewMakerTable& operator=(const RBAViewMakerTable&)=delete;
  RBAViewMakerTable& operator=(const RBAViewMakerTable&&)=delete;
  virtual ~RBAViewMakerTable()=default;

public:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<std::unique_ptr<RBAModelElementMaker>> getMakers() const override;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
