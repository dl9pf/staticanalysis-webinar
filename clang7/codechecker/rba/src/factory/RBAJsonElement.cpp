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

/// @file  RBAJsonElement.cpp
/// @brief JSON element class defintion file

#include "RBAJsonElement.hpp"

#include "RBAArbitrationPolicy.hpp"
#include "RBAContentLoserType.hpp"
#ifdef RBA_USE_LOG
#include "RBAExpressionType.hpp"
#endif

namespace rba
{

// RBAJsonElement clas

std::string RBAJsonElement::emptyStr_;

const std::string&
RBAJsonElement::getString() const
{
  // This function is never called 
  // because the function of the derived class is called
  return emptyStr_;
}

std::int32_t
RBAJsonElement::getInt() const
{
  // This function is never called 
  // because the function of the derived class is called
  return -99;
}

RBAArbitrationPolicy
RBAJsonElement::getArbitrationPolicy() const
{
  // This function is never called 
  // because the function of the derived class is called
  return RBAArbitrationPolicy::DEFAULT;
}

RBAContentLoserType
RBAJsonElement::getLoserType() const
{
  // This function is never called 
  // because the function of the derived class is called
  return RBAContentLoserType::NEVER_GIVEUP;
}

#ifdef RBA_USE_LOG
RBAExpressionType
RBAJsonElement::getExpressionType() const
{
  // This function is never called 
  // because the function of the derived class is called
  return RBAExpressionType::VALUE;
}
#endif

void
RBAJsonElement::setName(const std::string& name)
{
  name_ = name;
}

const std::string&
RBAJsonElement::getName() const
{
  return name_;
}

void
RBAJsonElement::addChild(std::unique_ptr<RBAJsonElement> child)
{
  children_.push_back(move(child));
}

const std::vector<std::unique_ptr<RBAJsonElement>>&
RBAJsonElement::getChildren() const
{
  return children_;
}

RBAJsonElement*
RBAJsonElement::getChild() const
{
  return children_.front().get();
}

const RBAJsonElement*
RBAJsonElement::findChildren(const std::string& name) const
{
  RBAJsonElement* res{nullptr};
  for(const auto& elem : children_) {
    if(elem->getName() == name) {
      res = elem.get();
      break;
    }
  }

  return res;
}

const std::string&
RBAJsonElement::getClassName() const
{
  const RBAJsonElement* const elem {findChildren("class")};
  if(elem != nullptr) {
    return elem->getString();
  }

  return emptyStr_;
}

// RBAJsonElementElement class

RBAJsonElementElement::RBAJsonElementElement(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

// RBAJsonElementString class

RBAJsonElementString::RBAJsonElementString(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

RBAArbitrationPolicy
RBAJsonElementString::getArbitrationPolicy() const
{
  if(str_ == "FIRST_COME_FIRST") {
    return RBAArbitrationPolicy::FIRST_COME_FIRST;
  }
  else if(str_ == "LAST_COME_FIRST") {
    return RBAArbitrationPolicy::LAST_COME_FIRST;
  }
  else if(str_ == "PRIORITY_FIRST_COME_FIRST") {
    return RBAArbitrationPolicy::PRIORITY_FIRST_COME_FIRST;
  }
  else if(str_ == "PRIORITY_LAST_COME_FIRST") {
    return RBAArbitrationPolicy::PRIORITY_LAST_COME_FIRST;
  }
  else {
    return RBAArbitrationPolicy::DEFAULT;
  }
}

RBAContentLoserType
RBAJsonElementString::getLoserType() const
{
  if(str_ == "GOOD_LOSER") {
    return RBAContentLoserType::GOOD_LOSER;
  }
  else if(str_ == "DO_NOT_GIVEUP_UNTIL_WIN") {
    return RBAContentLoserType::DO_NOT_GIVEUP_UNTIL_WIN;
  }
  else {
    return RBAContentLoserType::NEVER_GIVEUP;
  }
}

#ifdef RBA_USE_LOG
RBAExpressionType
RBAJsonElementString::getExpressionType() const
{
    if(str_ == "VALUE") {
      return RBAExpressionType::VALUE;
    }
    else if(str_ == "BOOLEAN") {
      return RBAExpressionType::BOOLEAN;
    }
    else if(str_ == "AREA") {
      return RBAExpressionType::AREA;
    }
    else if(str_ == "CONTENT") {
      return RBAExpressionType::CONTENT;
    }
    else if(str_ == "SOUND") {
      return RBAExpressionType::SOUND;
    }
    else if(str_ == "SET_OF_SOUND") {
      return RBAExpressionType::SET_OF_SOUND;
    }
    else if(str_ == "SET_OF_AREA") {
      return RBAExpressionType::SET_OF_AREA;
    }
    else if(str_ == "SET_OF_CONTENT") {
      return RBAExpressionType::SET_OF_CONTENT;
    }
    else if(str_ == "SET_OF_ZONE") {
      return RBAExpressionType::SET_OF_ZONE;
    }
    else if(str_ == "SCENE") {
      return RBAExpressionType::SCENE;
    }
    else if(str_ == "ZONE") {
      return RBAExpressionType::ZONE;
    }
    else if(str_ == "ACTION") {
      return RBAExpressionType::ACTION;
    }
    else if(str_ == "SET_OF_ACTION") {
      return RBAExpressionType::SET_OF_ACTION;
    }
    else {
      return RBAExpressionType::EXTENSION;
    }
}
#endif

const std::string&
RBAJsonElementString::getString() const
{
  return str_;
}

void
RBAJsonElementString::setString(const std::string& str)
{
  str_ = str;
}

// RBAJsonElementInt class

RBAJsonElementInt::RBAJsonElementInt(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

std::int32_t
RBAJsonElementInt::getInt() const
{
  return val_;
}

void
RBAJsonElementInt::setInt(const std::int32_t val)
{
  val_ = val;
}

// RBAJsonElementArray class

RBAJsonElementArray::RBAJsonElementArray(const std::string& name)
  : RBAJsonElement{}
{
  setName(name);
}

}
