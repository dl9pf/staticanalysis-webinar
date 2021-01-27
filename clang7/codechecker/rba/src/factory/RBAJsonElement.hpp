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

/// @file  RBAJsonElement.hpp
/// @brief JSON element class header file

#ifndef RBAJSONELEMENT_HPP
#define RBAJSONELEMENT_HPP

#include <cstdint>
#include <vector>
#include <memory>
#include <string>
#include "RBADllExport.hpp"

namespace rba
{

enum class RBAArbitrationPolicy : std::uint8_t;
enum class RBAContentLoserType : std::uint8_t;
#ifdef RBA_USE_LOG
enum class RBAExpressionType : std::uint8_t;
#endif

/// @brief JSON Element class
class DLL_EXPORT RBAJsonElement
{
public:
  RBAJsonElement()=default;
  RBAJsonElement(const RBAJsonElement&)=delete;
  RBAJsonElement(const RBAJsonElement&&)=delete;
  RBAJsonElement& operator=(const RBAJsonElement&)=delete;
  RBAJsonElement& operator=(const RBAJsonElement&&)=delete;
  virtual ~RBAJsonElement()=default;

public:
  virtual const std::string& getString() const;
  virtual std::int32_t getInt() const;
  virtual RBAArbitrationPolicy getArbitrationPolicy() const;
  virtual RBAContentLoserType getLoserType() const;
#ifdef RBA_USE_LOG
  virtual RBAExpressionType getExpressionType() const;
#endif

  void setName(const std::string& name);
  const std::string& getName() const;
  void addChild(std::unique_ptr<RBAJsonElement> child);
  const std::vector<std::unique_ptr<RBAJsonElement>>& getChildren() const;
  RBAJsonElement* getChild() const;
  const RBAJsonElement* findChildren(const std::string& name) const;
  const std::string& getClassName() const;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::string name_ {""};
  std::vector<std::unique_ptr<RBAJsonElement>> children_;
  static std::string emptyStr_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

class RBAJsonElementElement : public RBAJsonElement
{
public:
  explicit RBAJsonElementElement(const std::string& name);
  RBAJsonElementElement(const RBAJsonElementElement&)=delete;
  RBAJsonElementElement(const RBAJsonElementElement&&)=delete;
  RBAJsonElementElement& operator=(const RBAJsonElementElement&)=delete;
  RBAJsonElementElement& operator=(const RBAJsonElementElement&&)=delete;
  virtual ~RBAJsonElementElement()=default;
};

class RBAJsonElementString : public RBAJsonElement
{
public:
  explicit RBAJsonElementString(const std::string& name);
  RBAJsonElementString(const RBAJsonElementString&)=delete;
  RBAJsonElementString(const RBAJsonElementString&&)=delete;
  RBAJsonElementString& operator=(const RBAJsonElementString&)=delete;
  RBAJsonElementString& operator=(const RBAJsonElementString&&)=delete;
  virtual ~RBAJsonElementString()=default;

public:
  RBAArbitrationPolicy getArbitrationPolicy() const override;
  RBAContentLoserType getLoserType() const override;
#ifdef RBA_USE_LOG
  RBAExpressionType getExpressionType() const override;
#endif

  const std::string& getString() const override;
  void setString(const std::string& str);

private:
  std::string str_ {""};

};

class RBAJsonElementInt : public RBAJsonElement
{
public:
  explicit RBAJsonElementInt(const std::string& name);
  RBAJsonElementInt(const RBAJsonElementInt&)=delete;
  RBAJsonElementInt(const RBAJsonElementInt&&)=delete;
  RBAJsonElementInt& operator=(const RBAJsonElementInt&)=delete;
  RBAJsonElementInt& operator=(const RBAJsonElementInt&&)=delete;
  virtual ~RBAJsonElementInt()=default;

public:
  std::int32_t getInt() const override;
  void setInt(const std::int32_t val);

private:
  std::int32_t val_ {0};

};

class RBAJsonElementArray : public RBAJsonElement
{
public:
  explicit RBAJsonElementArray(const std::string& name);
  RBAJsonElementArray(const RBAJsonElementArray&)=delete;
  RBAJsonElementArray(const RBAJsonElementArray&&)=delete;
  RBAJsonElementArray& operator=(const RBAJsonElementArray&)=delete;
  RBAJsonElementArray& operator=(const RBAJsonElementArray&&)=delete;
  virtual ~RBAJsonElementArray()=default;
};
  
}

#endif
