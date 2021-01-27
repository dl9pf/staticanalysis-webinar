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
 * PreviousObjectWrapper (Previous Wrapper of RuleObject) 
 * generator class header
 */

#ifndef RBAPREVIOUSOBJECTWRAPPER_HPP
#define RBAPREVIOUSOBJECTWRAPPER_HPP

#include "RBARuleObject.hpp"

namespace rba
{

class DLL_EXPORT RBAPreviousObjectWrapper : public RBARuleObject
{
public:
  RBAPreviousObjectWrapper()=default;
  RBAPreviousObjectWrapper(const RBAPreviousObjectWrapper&)=delete;
  RBAPreviousObjectWrapper(const RBAPreviousObjectWrapper&&)=delete;
  RBAPreviousObjectWrapper& operator=(const RBAPreviousObjectWrapper&)=delete;
  RBAPreviousObjectWrapper& operator=(const RBAPreviousObjectWrapper&&)=delete;
  virtual ~RBAPreviousObjectWrapper()=default;

public:
  bool isPrevious() const override;
  const RBARuleObject* getRawObject() const override;
  void setRefObject(const RBARuleObject* const obj);

private:
  const RBARuleObject* refObject_ {nullptr};

};

}

#endif
