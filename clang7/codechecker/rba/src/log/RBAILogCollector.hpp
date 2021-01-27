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
 * Log collector interface class 
 */

#ifndef RBAILOGCOLLECTOR_HPP
#define RBAILOGCOLLECTOR_HPP

#include <string>
#include "RBADllExport.hpp"

namespace rba
{

class DLL_EXPORT RBAILogCollector
{
protected:
  RBAILogCollector()=default;
  RBAILogCollector(const RBAILogCollector&)=delete;
  RBAILogCollector(const RBAILogCollector&&)=delete;
  RBAILogCollector& operator=(const RBAILogCollector&)=delete;
  RBAILogCollector& operator=(const RBAILogCollector&&)=delete;
  virtual ~RBAILogCollector()=default;

public:
  virtual void log(const std::string& logLine)=0;

};

}

#endif
