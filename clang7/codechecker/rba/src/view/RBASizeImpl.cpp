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
 * Size information implementation class
 */

#include "RBASizeImpl.hpp"

namespace rba
{

RBASizeImpl::RBASizeImpl(const std::string& name)
  : RBASize(),
    RBANamedElement{name}
{
}

std::string
RBASizeImpl::getName() const
{
  return RBANamedElement::getElementName();
}

std::int32_t
RBASizeImpl::getWidth() const
{
  return width_;
}

std::int32_t
RBASizeImpl::getHeight() const
{
  return height_;
}

void
RBASizeImpl::setWidth(const std::int32_t newWidth)
{
  width_ = newWidth;
}

void
RBASizeImpl::setHeight(const std::int32_t newHeight)
{
  height_ = newHeight;
}

std::int32_t
RBASizeImpl::diff(const RBASizeImpl* const size) const
{
  std::int32_t w {width_ - size->getWidth()};
  if(w < 0) {
    w = -w;
  }
  std::int32_t h {height_ - size->getHeight()};
  if(h < 0) {
    h = -h;
  }

  return w + h;
}

}
