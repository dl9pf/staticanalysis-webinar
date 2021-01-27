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
 * ModelElment class header
 */

#ifndef RBAMODELELEMENT_HPP
#define RBAMODELELEMENT_HPP

#include <cstdint>
#include "RBADllExport.hpp"

namespace rba
{

enum class RBAModelElementType : std::uint8_t;

class DLL_EXPORT RBAModelElement
{
protected:
  RBAModelElement()=default;
  RBAModelElement(const RBAModelElement&)=delete;
  RBAModelElement(const RBAModelElement&&)=delete;
  RBAModelElement& operator=(const RBAModelElement&)=delete;
  RBAModelElement& operator=(const RBAModelElement&&)=delete;

public:
  virtual ~RBAModelElement()=default;

public:
  virtual void clearStatus();
  virtual RBAModelElementType getModelElementType() const;
  bool isModelElementType(const RBAModelElementType elemType) const;

};

}

#endif
