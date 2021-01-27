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
 * Area imeplementation class header
 */

#ifndef RBAAREAIMPL_HPP
#define RBAAREAIMPL_HPP

#include <cstdint>
#include <string>
#include "RBAArea.hpp"
#include "RBAAllocatable.hpp"

namespace rba
{

class RBASize;
class RBASizeImpl;
class RBAViewContent;
class RBAViewContentImpl;

class DLL_EXPORT RBAAreaImpl : public RBAArea, public RBAAllocatable
{
public:
  explicit RBAAreaImpl(const std::string& name="");
  RBAAreaImpl(const RBAAreaImpl&)=delete;
  RBAAreaImpl(const RBAAreaImpl&&)=delete;
  RBAAreaImpl& operator=(const RBAAreaImpl&)=delete;
  RBAAreaImpl& operator=(const RBAAreaImpl&&)=delete;

public:
  std::string getName() const override;
  std::int32_t getX() const override;
  std::int32_t getY() const override;
  std::int32_t getZorder() const override;
  const std::list<const RBAViewContent*>& getContents() const override;
  const std::list<const RBASize*>& getSizes() const override;
  RBAArbitrationPolicy getArbitrationPolicy() const override;

  void clearStatus() final;
  bool isArea() const override;

  void setZorder(const std::int32_t newZorder);
  void setDefaultX(const std::int32_t defaultX);
  void setDefaultY(const std::int32_t defaultY);
  void setOffsetX(const std::int32_t offsetX);
  void setOffsetY(const std::int32_t offsetY);
  void addSize(const RBASizeImpl* size);
  void addContent(const RBAViewContentImpl* const content);
  void resetCoordinate();
  RBAModelElementType getModelElementType() const override;
  const std::list<const RBAViewContent*>& getAllViewContents() const;
  const std::list<const RBAViewContent*> getAllViewContentsRecursive(const RBAAllocatable* const alloc) const;

  // Log
#ifdef RBA_USE_LOG
  std::string getSymbol() const override;
  std::string getHiddenSymbol() const override;
#endif

private:
  std::int32_t x_ {0};
  std::int32_t y_ {0};
  std::int32_t defaultX_ {0};
  std::int32_t defaultY_ {0};
  std::int32_t zorder_ {0};
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::list<const RBASize*> externSizes_;
  mutable std::list<const RBAViewContent*> externContents_;
  mutable std::list<const RBAViewContent*> externAllContents_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

};

}

#endif
