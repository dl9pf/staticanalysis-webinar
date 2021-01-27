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
 * Arbitrator class definition
 */

#include "RBAArbitrator.hpp"
#include "RBAModelImpl.hpp"
#include "RBAResult.hpp"
#include "RBAArbitratorImpl.hpp"

namespace rba {

RBAArbitrator::RBAArbitrator(RBAModel* newModel)
  : impl_{std::make_unique<RBAArbitrator::Impl>(this,
						dynamic_cast<RBAModelImpl*>(newModel))}
{
}

#ifdef RBA_USE_LOG
RBAArbitrator::RBAArbitrator(RBAModel* newModel, RBALogManager* logManager)
  : impl_(std::make_unique<RBAArbitrator::Impl>(this,
						dynamic_cast<RBAModelImpl*>(newModel), logManager))
{
}
#endif

RBAArbitrator::~RBAArbitrator() noexcept
{
}

void
RBAArbitrator::setModel(RBAModel* newModel)
{
  impl_->setModel(dynamic_cast<RBAModelImpl*>(newModel));
}

const RBAModel*
RBAArbitrator::getModel() const
{
  return impl_->getModel();
}

void
RBAArbitrator::initialize(std::list<std::string>& contexts)
{
  impl_->initialize(contexts);
}

std::unique_ptr<RBAResult>
RBAArbitrator::execute(const std::string& contextName, bool require)
{
  return impl_->execute(contextName, require);
}

std::unique_ptr<RBAResult>
RBAArbitrator::execute(std::list<std::string>& contexts,
		       bool require)
{
  return impl_->execute(contexts, require);
}

std::unique_ptr<RBAResult>
RBAArbitrator::execute(const std::string& sceneName,
		       std::list<std::pair<std::string,std::int32_t>>& properties)
{
  return impl_->execute(sceneName, properties);
}

std::unique_ptr<RBAResult>
RBAArbitrator::setResultContentState(const std::string& allocatableName,
				     const std::string& contextName)
{
  return impl_->setResultContentState(allocatableName, contextName);
}

std::unique_ptr<RBAResult>
RBAArbitrator::cancelArbitration()
{
  return impl_->cancelArbitration();
}

void
RBAArbitrator::clearArbitration()
{
  return impl_->clearArbitration();
}

bool
RBAArbitrator::setScene(const std::string& sceneName, bool require,
			std::list<std::pair<std::string, std::int32_t>>& properties)
{
  return impl_->setScene(sceneName, require, properties);
}

bool
RBAArbitrator::setContentState(const std::string& contextName, bool require)
{
  return impl_->setContentState(contextName, require);
}

bool
RBAArbitrator::setAllocatableResult(const std::string& allocatableName,
				    const std::string& contextName)
{
  return impl_->setAllocatableResult(allocatableName, contextName);
}

bool
RBAArbitrator::RBAArbitrator::evaluate(RBAExpression* expression)
{
  return impl_->evaluate(expression);
}

const RBARuleObject*
RBAArbitrator::evaluateObject(RBAExpression* expression)
{
  return impl_->evaluateObject(expression);
}

int32_t
RBAArbitrator::evaluateValue(RBAExpression* expression)
{
  return impl_->evaluateValue(expression);
}

RBAArbitratorImpl*
RBAArbitrator::getImpl() const
{
  return impl_->getImpl();
}

}