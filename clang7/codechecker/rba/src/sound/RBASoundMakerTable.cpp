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
/// @file  RBASoundMakerTable.cpp
/// @brief Sound element maker table class

#include "RBASoundMakerTable.hpp"
#include "RBAAllInstanceOfSoundContentMaker.hpp"
#include "RBAAllInstanceOfZoneMaker.hpp"
#include "RBAIsAttenuatedMaker.hpp"
#include "RBAIsMutedMaker.hpp"
#include "RBAIsOutputtedMaker.hpp"
#include "RBAIsSoundingMaker.hpp"
#include "RBAOutputtingSoundMaker.hpp"
#include "RBASoundContentMaker.hpp"
#include "RBASoundContentSetMaker.hpp"
#include "RBASoundContentStateMaker.hpp"
#include "RBAZoneMaker.hpp"
#include "RBAZoneSetMaker.hpp"

namespace rba
{

RBASoundMakerTable::RBASoundMakerTable()
  : RBAAbstractMakerTable{}
{
  addTag("zones");
  addTag("zonesets");
  addTag("soundcontents");
  addTag("soundcontentsets");
}

std::list<std::unique_ptr<RBAModelElementMaker>>
RBASoundMakerTable::getMakers() const
{
  std::list<std::unique_ptr<RBAModelElementMaker>> makers;
  makers.push_back(std::make_unique<RBAAllInstanceOfSoundContentMaker>());
  makers.push_back(std::make_unique<RBAAllInstanceOfZoneMaker>());
  makers.push_back(std::make_unique<RBAIsAttenuatedMaker>());
  makers.push_back(std::make_unique<RBAIsMutedMaker>());
  makers.push_back(std::make_unique<RBAIsOutputtedMaker>());
  makers.push_back(std::make_unique<RBAIsSoundingMaker>());
  makers.push_back(std::make_unique<RBAOutputtingSoundMaker>());
  makers.push_back(std::make_unique<RBASoundContentMaker>());
  RBAModelElementMaker::addMaker("SOUND", std::make_unique<RBASoundContentMaker>());
  RBAModelElementMaker::addMaker("SoundContent", std::make_unique<RBASoundContentMaker>());
  makers.push_back(std::make_unique<RBASoundContentSetMaker>());
  RBAModelElementMaker::addMaker("SET_OF_SOUND", std::make_unique<RBASoundContentSetMaker>());
  makers.push_back(std::make_unique<RBASoundContentStateMaker>());
  makers.push_back(std::make_unique<RBAZoneMaker>());
  RBAModelElementMaker::addMaker("ZONE", std::make_unique<RBAZoneMaker>());
  makers.push_back(std::make_unique<RBAZoneSetMaker>());
  RBAModelElementMaker::addMaker("SET_OF_ZONE", std::make_unique<RBAZoneSetMaker>());

  return makers;
}

}
