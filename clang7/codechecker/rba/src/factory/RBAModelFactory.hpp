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


/// @file  RBAModelFactory.hpp
/// @brief Model Factory class header file

#ifndef RBAMODELFACTORY_HPP
#define RBAMODELFACTORY_HPP

#include <string>
#include <list>
#include <memory>
#include <unordered_map>
#include "RBADllExport.hpp"

namespace rba
{

class RBAModel;
class RBAModelImpl;
class RBAJsonElement;
class RBAModelElement;
class RBAVariable;
class RBAAbstractMakerTable;
class RBAModelElementMaker;
enum class RBAConstraintMap : std::uint8_t;

/// @brief Model Factory class
class DLL_EXPORT RBAModelFactory
{
public:
  RBAModelFactory(RBAModelImpl* const model=nullptr);
  RBAModelFactory(const RBAModelFactory&)=delete;
  RBAModelFactory(const RBAModelFactory&&)=delete;
  RBAModelFactory& operator=(const RBAModelFactory&)=delete;
  RBAModelFactory& operator=(const RBAModelFactory&&)=delete;
  virtual ~RBAModelFactory() noexcept;

 public:
  RBAModel* const getModel() const;
  void deleteModel();
  void addMakerTable(const RBAAbstractMakerTable& makerTable);
  void addMaker(const std::string label,
                std::unique_ptr<RBAModelElementMaker> maker);
  bool hasMaker() const;
  const std::list<std::string>& getTags() const;

  RBAModelElement* createElement(const std::string& className,
                                 const RBAJsonElement* const jsonElement,
                                 RBAModelElement* const owner=nullptr);

  void setAllocatableConstraint(const std::string& allocatableName,
                                const std::string& constraintName,
                                const RBAConstraintMap& kind);

  void pushVariable(const RBAVariable* const var);
  void popVariable();
  const RBAVariable* getVariable(const std::string& varName);

  void resetException();
  void setException();
  bool isException() const;

private:
  RBAModelImpl* model_;
  bool exception_;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unordered_map<std::string, RBAModelElementMaker*> nameToMaker_;
  // unique_ptr list for storing
  std::list<std::unique_ptr<RBAModelElementMaker>> makers_;
  // current variable for working
  std::list<const RBAVariable*> currentVariables_;
  // JSON element tag list, set from the registered MakerTable
  std::list<std::string> tags_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
