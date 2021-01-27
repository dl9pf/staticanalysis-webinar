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
 * ModelElementType class header
 */

#ifndef RBAMODELELEMENTTYPE_HPP
#define RBAMODELELEMENTTYPE_HPP

namespace rba
{

enum class RBAModelElementType : std::uint8_t
{
  AllInstanceOfArea,
  AllInstanceOfViewContent,
  AllInstanceOfZone,
  AllInstanceOfSoundContent,
  Allocatable,
  AllocatedContent,
  AndOperator,
  Area,
  AreaSet,
  ArithmeticOperator,
  Constraint,
  ViewContent,
  ViewContentSet,
  ViewContentState,
  ContentValue,
  DisplayingContent,
  ExistsOperator,
  ForAllOperator,
  GetAllocatables,
  ActiveState,
  ActiveContents,
  GetContentsList,
  IfStatement,
  IfActionOperator,
  ImpliesOperator,
  IntegerValue,
  IsActive,
  IsDisplayed,
  IsEqualToOperator,
  IsGreaterThanEqualOperator,
  IsGreaterThanOperator,
  IsHidden,
  IsLowerThanEqualOperator,
  IsLowerThanOperator,
  IsVisible,
  LambdaContext,
  LambdaExpression,
  LetStatement,
  NotOperator,
  ObjectCompare,
  ObjectReference,
  MemberFeatureReference,
  OrOperator,
  PlusOperator,
  PreviousModifier,
  RuleObject,
  Scene,
  Property,
  SetExpression,
  SetOfOperator,
  SetOperator,
  ValueExpression,
  Variable,
  IsOn,
  Zone,
  ZoneSet,
  SoundContent,
  SoundContentSet,
  SoundContentState,
  IsAttenuated,
  IsOutputted,
  IsMuted,
  IsSounding,
  Rule,
  OnScene,
  OffScene,
  GetProperty,
  SetProperty,
  IntegerProperty,
  OutputtingSound,
  StateValue,
  HasBeenCanceled,
  HasBeenDisplayed,
  HasComeEarlier,
  HasComeLater,
  EventProcessing,
  MaxOperator,
  MinOperator,
  SelectOperator,
  SizeOperator,
  Undisplayed,
  IsTypeOfOperator,
  Displayed,
  None
};

}

#endif
