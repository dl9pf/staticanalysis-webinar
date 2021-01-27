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
 * Sound content state class
 */

#ifndef RBASOUNDCONTENTSTATE_HPP
#define RBASOUNDCONTENTSTATE_HPP

#include <string>

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

namespace rba
{

class RBASoundContent;

/**
 * @class RBASoundContentState
 * Define the state of sound contents.
 */
class DLL_EXPORT RBASoundContentState
{
protected:
  RBASoundContentState()=default;
  RBASoundContentState(const RBASoundContentState&)=delete;
  RBASoundContentState(RBASoundContentState&&)=delete;
  RBASoundContentState& operator=(const RBASoundContentState&)=delete;
  RBASoundContentState& operator=(RBASoundContentState&&)=delete;
  ~RBASoundContentState()=default;

public:
  /**
   * @brief Returns the name of the sound contents state.
   * @return sound contents state name.
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the priority.
   * @return priority value
   */
  virtual std::int32_t getPriority() const=0;

  /**
   * @brief Returns the sound content.
   * @return sound content
   */
  virtual const RBASoundContent* getOwner() const=0;

  /**
   * @brief Returns the order.
   * @return order value
   * @detail The order is a number of sequence of the entry sound content state
   * by request. The order value is an integer value starting from 1 and
   * incremented in order, and the order value of the sound content state
   * without sound request is set to 0.\n
   * The order of the sound content state does not include the output request
   * of the view content state.
   */
  virtual std::int32_t getOrder() const=0;

  /**
   * @brief Returns the unique character string of the sound contents state.
   * @return Unique character string of the sound contents state.
   *
   * Unique character string is
   * sound content name + CONTEXT_SEPARATER + sound content state name.
   * Use the unique character string as a context name.
   */
  virtual std::string getUniqueName() const=0;

  /**
   * @brief Returns the name of the sound content from context name.
   * @param context the context name
   * @return name of the sound content
   */
  static std::string getContentNameByContext(const std::string& context);

  /**
   * @brief Returns the state of the sound content from context name.
   * @param context the context name
   * @return state of the sound content
   */
  static std::string getContentStateNameByContext(const std::string& context);

  /**
   * @brief Check if argument is The unique character string(context name).
   * @param context the context name
   * @return true: unique character string(context name)
   * @return false: Not unique character string(context name)
   */
  static bool isUniqueName(const std::string& context);

public:
  /**
   * @brief Defines the default priority value.
   */
  const static std::int32_t PRIORITY_EDEFAULT = 0;

  /**
   * @brief Defines the separator for separating sound content name and sound content state name.
   * And be the character to connect it.
   */
  const static char CONTEXT_SEPARATER = '/';

};

}

#endif
