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
 * NamedElement clsass header
 */

#ifndef RBANAMEDELEMENT_HPP
#define RBANAMEDELEMENT_HPP

#include <string>
#include "RBAModelElement.hpp"

namespace rba
{

class DLL_EXPORT RBANamedElement : public RBAModelElement
{
protected:
  explicit RBANamedElement(const std::string& newName = "");
  RBANamedElement(const RBANamedElement&)=delete;
  RBANamedElement(const RBANamedElement&&)=delete;
  RBANamedElement& operator=(const RBANamedElement&)=delete;
  RBANamedElement& operator=(const RBANamedElement&&)=delete;

public:
  virtual ~RBANamedElement()=default;
  virtual std::string getUniqueName() const;
  const std::string& getElementName() const;
  const std::string& getDynamicName() const;
  void setDynamicName(const std::string& newName);

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  const std::string name_;
  std::string dynamic_name_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
