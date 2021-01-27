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
 * View action type class
 */

#ifndef RBAVIEWACTIONTYPE_HPP
#define RBAVIEWACTIONTYPE_HPP

namespace rba
{

/**
 * @enum RBAViewActionType
 * type of view action
 */
enum class RBAViewActionType : std::uint8_t
{
  /**
   * @brief The content transition(ADD) : content is displayed in the area.
   */
  TRANSITION_ADD,

  /**
   * @brief The content transition(REMOVE) : content is deleted from the area.
   */
  TRANSITION_REMOVE,

  /**
   * @brief The content transition(REPLACE) : content is replaced on the area.
   */
  TRANSITION_REPLACE,

  /**
   * @brief The content move(MOVE) : The display of content changes to another area.
   */
  MOVE
};

}

#endif
