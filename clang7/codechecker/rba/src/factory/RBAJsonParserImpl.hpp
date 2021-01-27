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

/// @file  RBAJsonParserImpl.hpp
/// @brief JSON  Parser implementation class header file

#ifndef RBAJSONPARSERIMPL_HPP
#define RBAJSONPARSERIMPL_HPP

#include <mutex>
#include "RBAJsonParser.hpp"
#include "RBAModelFactory.hpp"

namespace rba
{

class RBAJsonElement;
enum class RBAConstraintMap : std::uint8_t;

/// @brief JSON  Parser implementation class
class RBAJsonParser::Impl
{
public:
  Impl(RBAModelFactory* const factory=nullptr);
  Impl(const Impl&)=delete;
  Impl(const Impl&&)=delete;
  Impl& operator=(const Impl&)=delete;
  Impl& operator=(const Impl&&)=delete;
  virtual ~Impl()=default;

public:
  RBAModel* parse(const std::string& filename);

private:
  virtual void resetFactory();

private:
  void createConstraintMap(const RBAJsonElement* const constraints,
                           const RBAConstraintMap& kind);
  void createAllocatablesMap(const RBAJsonElement* const allocMap);
  std::unique_ptr<RBAJsonElement> readJsonFile(const std::string& filename);
  std::unique_ptr<RBAJsonElement> readJsonString(const std::string& jsonstring);

private:
  enum class Status : std::uint8_t {
    START,
    VALUE,
  };
  RBAModelFactory* orgFactory_;
  RBAModelFactory* factory_;
  std::unique_ptr<RBAModelFactory> uniqueFactory_;
  std::mutex mutex_;
};

}

#endif
