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

/// @file  RBAAbstractMakerTable.hpp
/// @brief Maker table abstraction class header

#ifndef RBAABSTRACTMAKERTABLE_HPP
#define RBAABSTRACTMAKERTABLE_HPP

#include <memory>
#include "RBAModelElementMaker.hpp"

namespace rba
{

class DLL_EXPORT RBAAbstractMakerTable
{
public:
  RBAAbstractMakerTable()=default;
  RBAAbstractMakerTable(const RBAAbstractMakerTable&)=delete;
  RBAAbstractMakerTable(const RBAAbstractMakerTable&&)=delete;
  RBAAbstractMakerTable& operator=(const RBAAbstractMakerTable&)=delete;
  RBAAbstractMakerTable& operator=(const RBAAbstractMakerTable&&)=delete;
  virtual ~RBAAbstractMakerTable()=default;

public:
  virtual std::list<std::unique_ptr<RBAModelElementMaker>> getMakers() const=0;
  virtual const std::list<std::string>& getTags() const;

protected:
  void addTag(const std::string& tag);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<std::string> tags_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
