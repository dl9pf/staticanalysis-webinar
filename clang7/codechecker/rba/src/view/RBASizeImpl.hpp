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
 * Size information implementation class header
 */

#ifndef RBASIZEIMPL_HPP
#define RBASIZEIMPL_HPP

#include "RBASize.hpp"
#include "RBANamedElement.hpp"

namespace rba
{

class RBASizeImpl : public RBASize, public RBANamedElement
{
public:
  explicit RBASizeImpl(const std::string& name="");
  RBASizeImpl(const RBASizeImpl&)=default;
  RBASizeImpl(RBASizeImpl&&)=default;
  RBASizeImpl& operator=(const RBASizeImpl&)=default;
  RBASizeImpl& operator=(RBASizeImpl&&)=default;
  virtual ~RBASizeImpl()=default;

public:
  std::string getName() const override;
  std::int32_t getWidth() const override;
  std::int32_t getHeight() const override;

  void setWidth(const std::int32_t newWidth);
  void setHeight(const std::int32_t newHeight);

  std::int32_t diff(const RBASizeImpl* const size) const;

private:
  std::int32_t width_ {WIDTH_EDEFAULT};
  std::int32_t height_ {HEIGHT_EDEFAULT};

};

}

#endif
