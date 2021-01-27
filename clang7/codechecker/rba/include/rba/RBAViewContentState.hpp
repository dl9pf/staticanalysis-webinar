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
 * View content state class
 */

#ifndef RBAVIEWCONTENTSTATE_HPP
#define RBAVIEWCONTENTSTATE_HPP

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

class RBAViewContent;

/**
 * @class RBAViewContentState
 * Define the state of view contents.
 */
class DLL_EXPORT RBAViewContentState
{
protected:
  RBAViewContentState()=default;
  RBAViewContentState(const RBAViewContentState&)=delete;
  RBAViewContentState(RBAViewContentState&&)=delete;
  RBAViewContentState& operator=(const RBAViewContentState&)=delete;
  RBAViewContentState& operator=(RBAViewContentState&&)=delete;
  ~RBAViewContentState()=default;

public:
  /**
   * @brief Returns the name of the view contents state.
   * @return view contents state name.
   */
  virtual std::string getName() const=0;

  /**
   * @brief Returns the priority.
   * @return priority value
   */
  virtual std::int32_t getPriority() const=0;

  /**
   * @brief Returns the view content.
   * @return view content
   */
  virtual const RBAViewContent* getOwner() const=0;

  /**
   * @brief Returns the order.
   * @return order value
   * @detail The order is a number of sequence of the entry view content state
   * by request. The order value is an integer value starting from 1 and
   * incremented in order, and the order value of the view content state
   * without view request is set to 0.\n
   * The order of the view content state does not include the output request
   * of the sound content state.
   */
  virtual std::int32_t getOrder() const=0;

  /**
   * @brief Returns the unique character string of the view contents state.
   * @return Unique character string of the view contents state.
   *
   * Unique character string is
   * view content name + CONTEXT_SEPARATER + view content state name.
   * Use the unique character string as a context name.
   */
  virtual std::string getUniqueName() const=0;

  /**
   * @brief Returns the name of the view content from context name.
   * @param context the context name
   * @return name of the view content
   */
  static std::string getContentNameByContext(const std::string& context);

  /**
   * @brief Returns the state of the view content from context name.
   * @param context the context name
   * @return state of the view content
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
   * @brief Defines the separator for separating view content name and view content state name.
   * And be the character to connect it.
   */
  const static char CONTEXT_SEPARATER = '/';

};

}

#endif
