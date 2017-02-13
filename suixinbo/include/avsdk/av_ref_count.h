#pragma once

#include "basictypes.h"
#include "build_config.h"

namespace tencent {
namespace av {

/// SDK的引用计数接口定义
class AVRefCount {
public:
    virtual ~AVRefCount() {}

    inline int32 RefCount() const {
        return _refCount;
    }

#ifdef _MSC_VER
    virtual int32 AddRef() const {
        return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&_refCount));
    }

    virtual bool Release() const {
        if (InterlockedDecrement(reinterpret_cast<volatile LONG*>(&_refCount)) == 0) {
            const_cast<AVRefCount*>(this)->DeleteObject();
            return true;
        }
        return false;
    }
#else
    virtual int32 AddRef() const;
    virtual bool Release() const;
#endif

    virtual void DeleteObject() {
        delete this;
    }

protected:
    AVRefCount() {
        _refCount = 1;
    }

    mutable int32 _refCount;
};

} // namespace av
} // namespace tencent