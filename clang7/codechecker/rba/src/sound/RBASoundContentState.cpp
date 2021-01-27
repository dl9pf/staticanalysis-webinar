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
 * SoundContentState class
 */

#include "RBASoundContentState.hpp"

namespace rba
{

std::string
RBASoundContentState::getContentNameByContext(const std::string& context)
{
  return context.substr(0U, context.find(CONTEXT_SEPARATER));
}

std::string
RBASoundContentState::getContentStateNameByContext(const std::string& context)
{
  const std::string::size_type pos {context.find(CONTEXT_SEPARATER)};
  if(pos == std::string::npos) {
    // Returns null string if it does not contain a separator character.
    return "";
  }
  else {
    return context.substr(pos+1U, context.length()-1U);
  }
}

bool
RBASoundContentState::isUniqueName(const std::string& context)
{
  return (context.find(CONTEXT_SEPARATER) != std::string::npos);
}

}
