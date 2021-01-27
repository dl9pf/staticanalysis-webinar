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
 * AffectInfo class header
 */

#ifndef RBAAFFECTINFO_HPP
#define RBAAFFECTINFO_HPP

#include <unordered_map>
#include <set>

namespace rba
{

class RBAAllocatable;

class RBAAffectInfo
{
public:
  RBAAffectInfo()=default;
  RBAAffectInfo(const RBAAffectInfo&)=delete;
  RBAAffectInfo(const RBAAffectInfo&&)=delete;
  RBAAffectInfo& operator=(const RBAAffectInfo&)=delete;
  RBAAffectInfo& operator=(const RBAAffectInfo&&)=delete;
  virtual ~RBAAffectInfo()=default;

public:
  bool alreadyKnowsThatFormerHasAffectedToLatter(const RBAAllocatable* const allocatable,
						 const RBAAllocatable* const affectAllocatable) const;
  void addInfoThatFormerAffectedToLatter(const RBAAllocatable* const allocatable,
					 const RBAAllocatable* const affectAllocatable);
  void removeAffectInfo(const RBAAllocatable* const affectAllocatable);

private:
  // Information of other "allocatable" affected by "allocatable"
  mutable std::unordered_map<const RBAAllocatable*,
		   std::set<const RBAAllocatable*>>reaffected_;

};

}

#endif
