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
 * Expression type enumeration class header file
 */

#ifndef RBAEXPRESSIONTYPE_HPP
#define RBAEXPRESSIONTYPE_HPP

#ifdef RBA_USE_LOG

#include <cstdint>

namespace rba
{

enum class RBAExpressionType : std::uint8_t
{
  VALUE =  0,
  BOOLEAN,
  AREA,
  CONTENT,
  SET_OF_AREA,
  SET_OF_CONTENT,
  LAMBDA,
  SCENE,
  ZONE,
  SET_OF_ZONE,
  SOUND,
  SET_OF_SOUND,
  ACTION,
  SET_OF_ACTION,
  PROPERTY,
  EXTENSION,
  CONTENT_STATE,
  EXCEPTION
};

}

#endif
#endif
