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

/// @file  RBACommonMakerTable.cpp
/// @brief Expression element maker table class definition file

#include "RBACommonMakerTable.hpp"
#include "RBAActiveStateMaker.hpp"
#include "RBAAllocatedContentMaker.hpp"
#include "RBAActiveContentsMaker.hpp"
#include "RBAAndOperatorMaker.hpp"
#include "RBAContentValueMaker.hpp"
#include "RBAExistsOperatorMaker.hpp"
#include "RBAForAllOperatorMaker.hpp"
#include "RBAGetAllocatablesMaker.hpp"
#include "RBAGetContentsListMaker.hpp"
#include "RBAGetPropertyMaker.hpp"
#include "RBAHasBeenDisplayedMaker.hpp"
#include "RBAHasComeEarlierThanMaker.hpp"
#include "RBAHasComeLaterThanMaker.hpp"
#include "RBAIfStatementMaker.hpp"
#include "RBAImpliesOperatorMaker.hpp"
#include "RBAIntegerValueMaker.hpp"
#include "RBAIsActiveMaker.hpp"
#include "RBAIsEqualToOperatorMaker.hpp"
#include "RBAIsGreaterThanEqualOperatorMaker.hpp"
#include "RBAIsGreaterThanOperatorMaker.hpp"
#include "RBAIsLowerThanEqualOperatorMaker.hpp"
#include "RBAIsLowerThanOperatorMaker.hpp"
#include "RBAIsOnMaker.hpp"
#include "RBAIsTypeOfOperatorMaker.hpp"
#include "RBALambdaExpressionMaker.hpp"
#include "RBAMaxOperatorMaker.hpp"
#include "RBAMemberFeatureReferenceMaker.hpp"
#include "RBAMinOperatorMaker.hpp"
#include "RBASelectOperatorMaker.hpp"
#include "RBANotOperatorMaker.hpp"
#include "RBAObjectCompareMaker.hpp"
#include "RBAObjectReferenceMaker.hpp"
#include "RBAOrOperatorMaker.hpp"
#include "RBAPlusOperatorMaker.hpp"
#include "RBAPreviousModifierMaker.hpp"
#include "RBASetOfOperatorMaker.hpp"
#include "RBASizeOperatorMaker.hpp"
#include "RBAStateValueMaker.hpp"
#include "RBAVariableMaker.hpp"
#include "RBAConstraintMaker.hpp"
#include "RBASceneMaker.hpp"
#include "RBAModelElement.hpp"

namespace rba
{

RBACommonMakerTable::RBACommonMakerTable()
  : RBAAbstractMakerTable{}
{
  addTag("scenes");
  addTag("constraints");
  addTag("postconstraints");
  addTag("rules");
}

std::list<std::unique_ptr<RBAModelElementMaker>>
RBACommonMakerTable::getMakers() const
{
  std::list<std::unique_ptr<RBAModelElementMaker>> makers;
  makers.push_back(std::make_unique<RBAActiveStateMaker>());
  makers.push_back(std::make_unique<RBAAllocatedContentMaker>());
  makers.push_back(std::make_unique<RBAActiveContentsMaker>());
  makers.push_back(std::make_unique<RBAAndOperatorMaker>());
  makers.push_back(std::make_unique<RBAContentValueMaker>());
  makers.push_back(std::make_unique<RBAExistsOperatorMaker>());
  makers.push_back(std::make_unique<RBAForAllOperatorMaker>());
  makers.push_back(std::make_unique<RBAGetAllocatablesMaker>());
  makers.push_back(std::make_unique<RBAGetContentsListMaker>());
  makers.push_back(std::make_unique<RBAGetPropertyMaker>());
  makers.push_back(std::make_unique<RBAHasBeenDisplayedMaker>());
  makers.push_back(std::make_unique<RBAHasComeEarlierThanMaker>());
  makers.push_back(std::make_unique<RBAHasComeLaterThanMaker>());
  makers.push_back(std::make_unique<RBAIfStatementMaker>());
  makers.push_back(std::make_unique<RBAImpliesOperatorMaker>());
  makers.push_back(std::make_unique<RBAIntegerValueMaker>());
  makers.push_back(std::make_unique<RBAIsActiveMaker>());
  makers.push_back(std::make_unique<RBAIsEqualToOperatorMaker>());
  makers.push_back(std::make_unique<RBAIsGreaterThanEqualOperatorMaker>());
  makers.push_back(std::make_unique<RBAIsGreaterThanOperatorMaker>());
  makers.push_back(std::make_unique<RBAIsLowerThanEqualOperatorMaker>());
  makers.push_back(std::make_unique<RBAIsLowerThanOperatorMaker>());
  makers.push_back(std::make_unique<RBAIsOnMaker>());
  makers.push_back(std::make_unique<RBAIsTypeOfOperatorMaker>());
  makers.push_back(std::make_unique<RBALambdaExpressionMaker>());
  makers.push_back(std::make_unique<RBAMaxOperatorMaker>());
  makers.push_back(std::make_unique<RBAMemberFeatureReferenceMaker>());
  makers.push_back(std::make_unique<RBAMinOperatorMaker>());
  makers.push_back(std::make_unique<RBASelectOperatorMaker>());
  makers.push_back(std::make_unique<RBANotOperatorMaker>());
  makers.push_back(std::make_unique<RBAObjectCompareMaker>());
  makers.push_back(std::make_unique<RBAObjectReferenceMaker>());
  makers.push_back(std::make_unique<RBAOrOperatorMaker>());
  makers.push_back(std::make_unique<RBAPlusOperatorMaker>());
  makers.push_back(std::make_unique<RBAPreviousModifierMaker>());
  makers.push_back(std::make_unique<RBASetOfOperatorMaker>());
  makers.push_back(std::make_unique<RBASizeOperatorMaker>());
  makers.push_back(std::make_unique<RBAStateValueMaker>());
  makers.push_back(std::make_unique<RBAVariableMaker>());
  makers.push_back(std::make_unique<RBAConstraintMaker>());
  makers.push_back(std::make_unique<RBASceneMaker>());
  RBAModelElementMaker::addMaker("SCENE", std::make_unique<RBASceneMaker>());

  return makers;
}

}
