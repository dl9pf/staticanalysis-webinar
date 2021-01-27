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
 * View action class
 */

#ifndef RBAVIEWACTION_HPP
#define RBAVIEWACTION_HPP

#include "RBAViewActionType.hpp"

#ifdef _MSC_VER
#ifdef _WINDLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#else
#define DLL_EXPORT
#endif

namespace rba {

class RBAArea;
class RBAViewContent;
class RBAViewContentState;

/**
 * @class RBAViewAction
 * Define the change information of view contents.<br>
 * Change information has 2 type.
 * The contents transition, that view contents change for an area.
 * The contents move, that the view content displayed area changes.
 */
class DLL_EXPORT RBAViewAction
{
public:
  RBAViewAction()=default;
  RBAViewAction(RBAViewAction&&)=delete;
  RBAViewAction& operator=(const RBAViewAction&)=delete;
  RBAViewAction& operator=(RBAViewAction&&)=delete;
  virtual ~RBAViewAction()=default;

protected:
  // Copy constructor is defined in default because it is used in another class
  RBAViewAction(const RBAViewAction&)=default;

public:
  /**
   * @brief Returns the area of the contents transition.
   * @return Area of the contents transition
   */
  virtual const RBAArea* getArea() const;

  /**
   * @brief Returns previously displayed the view content.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Previously displayed the view content
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   */
  virtual const RBAViewContent* getFromContent() const;

  /**
   * @brief Returns subsequently displayed the view content.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Subsequently displayed the view content.
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   */
  virtual const RBAViewContent* getToContent() const;

  /**
   * @brief Returns previously displayed the view content state.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Previously displayed the view content state
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   */
  virtual const RBAViewContentState* getFromContentState() const;

  /**
   * @brief Returns subsequently displayed the view content state.
   * Used when change information type is the contents transition(TRANSITION_REPLACE).
   * @return Subsequently displayed the view content state.
   *
   * * If the change information type is not the contents transition(TRANSITION_REPLACE), returns nullptr.
   */
  virtual const RBAViewContentState* getToContentState() const;

  /**
   * @brief Returns previously displayed the area.
   * Used when change information type is the contents move(MOVE).
   * @return Previously displayed the area
   *
   * * If the change information type is not the contents move(MOVE), returns nullptr.
   */
  virtual const RBAArea* getFromArea() const;

  /**
   * @brief Returns subsequently displayed the area.
   * Used when change information type is the contents move(MOVE).
   * @return Subsequently displayed the area
   *
   * * If the change information type is not the contents move(MOVE), returns nullptr.
   */
  virtual const RBAArea* getToArea() const;

  /**
   * @brief Returns view content of change information.
   * @return View content of change information
   *
   * * If getViewActionType() == TRANSITION_ADD, returns display view content.
   * * If getViewActionType() == TRANSITION_REMOVE, returns hide view content.
   * * If getViewActionType() == TRANSITION_REPLACE, returns nullptr.
   * * If getViewActionType() == MOVE, returns view content which changes the area.
   */
  virtual const RBAViewContent* getContent() const;

  /**
   * @brief Returns view content state of change information.
   * @return View content state of change information
   *
   * * If getViewActionType() == TRANSITION_ADD, returns display view content state.
   * * If getViewActionType() == TRANSITION_REMOVE, returns hide view content state.
   * * If getViewActionType() == TRANSITION_REPLACE, returns nullptr.
   * * If getViewActionType() == MOVE, returns view content state which changes the area.
   */
  virtual const RBAViewContentState* getContentState() const;

  /**
   * @brief Returns view action type.
   * @return View action type
   */
  virtual RBAViewActionType getViewActionType() const=0;

  /**
   * @brief Equal operator
   * @return true: equal
   * @return false: not equal
   */
  virtual bool operator==(const RBAViewAction& viewAction)=0;

};

}

#endif
