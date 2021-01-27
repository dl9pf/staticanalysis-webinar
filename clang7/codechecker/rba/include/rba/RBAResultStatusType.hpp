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
 * Result status type cluss
 */

#ifndef RBARESULTSTATUSTYPE_HPP
#define RBARESULTSTATUSTYPE_HPP

namespace rba
{

/**
 * @enum RBAResultStatusType
 * Status of the arbitration result.
 */
enum class RBAResultStatusType : std::uint8_t
{
  /**
   * @brief Success
   */
  SUCCESS,

  /**
   * @brief Failed
   */
  FAILED,

  /**
   * @brief Unknown context or content state
   */
  UNKNOWN_CONTENT_STATE,

  /**
   * @brief Cancel arbitration error
   */
  CANCEL_ERROR

};

}

#endif
