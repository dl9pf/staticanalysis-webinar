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
 * JSON parser class
 */

#ifndef RBAJSONPARSER_HPP
#define RBAJSONPARSER_HPP

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

#include <memory>
#include "RBAModel.hpp"

namespace rba
{

class RBAModel;

/**
 * @class RBAJsonParser
 * Provides the facility that loads a model file in JSON format and generate a Model object.
 */
class DLL_EXPORT RBAJsonParser
{
public:
  RBAJsonParser();
  RBAJsonParser(const RBAJsonParser&)=delete;
  RBAJsonParser(const RBAJsonParser&&)=delete;
  RBAJsonParser& operator=(const RBAJsonParser&)=delete;
  RBAJsonParser& operator=(const RBAJsonParser&&)=delete;
  virtual ~RBAJsonParser() noexcept;

public:
  /**
   * @brief Loads a JSON file and generates a model object.
   * @param filename Path of JSON file
   * @return Model
   * If the file is not found, returns nullptr.
   *
   * **Example**
   *
   * ```
   *    rba::RBAJsonParser parser;
   *    rba::RBAModel* model = parser.parse("RBAModel.json");
   *    if(model == nullptr) {
   *        std::cout << "ERRROR: Could not read JSON file" << std::endl;
   *        return 1;
   *    }
   *    rba::RBAArbitrator* arb = new rba::RBAArbitrator(model);
   * ```
   */
  RBAModel* parse(const std::string& filename);


private:
  class Impl;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::unique_ptr<Impl> impl_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
