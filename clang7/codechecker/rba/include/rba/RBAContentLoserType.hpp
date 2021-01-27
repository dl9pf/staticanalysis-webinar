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
 * Good loser type class
 */

#ifndef RBACONTENTLOSERTYPE_HPP
#define RBACONTENTLOSERTYPE_HPP

namespace rba
{

/**
 * @enum RBAContentLoserType
 * Type of behavior when content loses the arbitration
 */
enum class RBAContentLoserType : std::uint8_t
{
  /**
   * @brief Always cancels its request when losing arbitration.
   */
  GOOD_LOSER=0,

  /**
   * @brief Cancels its request only if it lost the arbitration in the displaying state.
   */
  DO_NOT_GIVEUP_UNTIL_WIN,

  /**
   * @brief Never cancels its request.
   */
  NEVER_GIVEUP
};

}

#endif
