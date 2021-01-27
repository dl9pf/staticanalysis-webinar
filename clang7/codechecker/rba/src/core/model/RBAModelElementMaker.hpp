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
/// @file  RBAModelElementMaker.hpp
/// @brief ModelElement object genartor abstract class header

#ifndef RBAMODELELEMENTMAKER_HPP
#define RBAMODELELEMENTMAKER_HPP

#include <memory>
#include <string>
#include "RBADllExport.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

class RBAModelElement;
class RBAJsonElement;
class RBAModelImpl;

/// @brief  ModelElement object genartor abstract class
class DLL_EXPORT RBAModelElementMaker
{
public:
  /// @brief Constructor that specifies the label
  /// @details Set label and generate
  /// @param[in] label labe to set
  RBAModelElementMaker()=default;
  explicit RBAModelElementMaker(const std::string& label);
  virtual ~RBAModelElementMaker()=default;

protected:
  RBAModelElementMaker(const RBAModelElementMaker& maker)=delete;
  RBAModelElementMaker& operator=(const RBAModelElementMaker& maker)=delete;
  // Use "move" in RBAAbstractModelTable::addMaker()
  RBAModelElementMaker(RBAModelElementMaker&&)=default;
  RBAModelElementMaker& operator=(RBAModelElementMaker&&)=default;

public:
  /// @brief Set model factory
  /// @param[in] factory model factory
  void setFactory(RBAModelFactory* const factory);

  /// @brief Get label
  /// @details Returns the label of the corresponding JSON element
  /// @return Label string
  const std::string& getLabel() const;

  /// @brief Create ModelElement object
  /// @details create ModelElement object and register unique_ptr to model
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The moder to store created object
  /// @param[in,out] owner Parent object (Not in use)
  /// @return ModelElement object
  virtual RBAModelElement* create(const RBAJsonElement* jsonElem,
                                  RBAModelImpl* model,
                                  RBAModelElement* owner=nullptr);

  /// @brief Get instance
  /// @details Get the element corresponding to name from model.
  ///          If there is no name or it is not in model, 
  ///          create an instance and register it in model.
  /// @return ModelElement object
  virtual RBAModelElement* getInstance(RBAModelImpl* model,
                                       const std::string& name="",
                                       RBAModelElement* owner=nullptr);

  /// @brief Register Maker
  /// @details Register the Maker corresponding to the class name 
  ///          used in JSON in the map
  /// @return void
  static void addMaker(const std::string& typeName, 
                        std::unique_ptr<RBAModelElementMaker> maker);

  /// @brief Get Maker
  /// @details Get the Maker corresponding to the class name from the map
  /// @return Corresponding Maker. If it doesn't exist, return null.
  static RBAModelElementMaker* getMaker(const std::string& typeName);

protected:
  /// @brief Create an empty instance
  /// @details Create an empty instance of unique_ptr in derived class
  /// @return unique_ptr for instance
  virtual std::unique_ptr<RBAModelElement> createInstance(const std::string& name="")=0;

  /// @brief Set model element attributes for each derived class
  /// @param[in] jsonElem JSON element of ModelElement
  /// @param[in] model The model to store generated RBARuleObjectMaker
  /// @param[in,out] owner Parent object (Not in use)
  virtual RBAModelElement* setProperty(RBAModelElement* element,
                                       const RBAJsonElement* jsonElem,
                                       RBAModelImpl* model,
                                       RBAModelElement* owner=nullptr)=0;

  /// @brief Get model factory
  /// @details Get model factory
  /// @return model factory
  RBAModelFactory* getFactory() const;

private:
  /// @brief Factory for recursively generating objects
  RBAModelFactory* factory_;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  /// @brief Label of corresponding JSON element
  const std::string label_;

  /// @brief Correspondence map of each Maker and the character string that 
  ///        represents the class used in JSON
  static std::unordered_map<std::string, std::unique_ptr<RBAModelElementMaker>> makerMap_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
