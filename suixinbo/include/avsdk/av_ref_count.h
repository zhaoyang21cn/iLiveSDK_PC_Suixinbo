#pragma once

#include "basictypes.h"

namespace tencent {
namespace av {

/// SDK的引用计数接口定义
class AVRefCount {
 public:
  virtual ~AVRefCount() {}

  virtual int32 AddRef() {
    return ++m_refCount;
  }

  virtual bool Release() {
    --m_refCount;

    if (0 == m_refCount) {
      delete this;
      return true;
    }

    return false;
  }

 protected:
  AVRefCount() {
    m_refCount = 1;
  }

  int32 m_refCount;
};

} // namespace av
} // namespace tencent