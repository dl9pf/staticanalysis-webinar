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
 * Arbitration policy class
 */

#ifndef RBAARBITRATIONPOLICY_HPP
#define RBAARBITRATIONPOLICY_HPP

namespace rba
{

/**
 * @enum RBAArbitrationPolicy
 * Type of arbitration policy.
 */
enum class RBAArbitrationPolicy : std::uint8_t
{
  /**
   * @brief Same PRIORITY_LAST_COME_FIRST.
   */
  DEFAULT,
  /**
   * @brief First Come First Arbitration.
   * @details give priority to first come request.
   */
  FIRST_COME_FIRST,
  /**
   * @brief Last Come First Arbitration.
   * @details give priority to last come request.
   */
  LAST_COME_FIRST,
  /**
   * @brief Priority and First Come First Arbitration.
   * @details Follow the Priority of Contents.
   * If same priority then give priority to first come request.
   */
  PRIORITY_FIRST_COME_FIRST,
  /**
   * @brief Priority and Last Come First Arbitration.
   * @details Follow the Priority of Contents.
   * If same priority then give priority to last come request.
   */
  PRIORITY_LAST_COME_FIRST
};

}

#endif
