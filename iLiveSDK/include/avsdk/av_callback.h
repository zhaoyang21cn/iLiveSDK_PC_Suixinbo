#pragma once

#include "av_delegate.h"

namespace tencent {
namespace av {

class AVCallback : public AVRefCount {
public:
    virtual void OnComplete(int32 result, const std::string& error_info) = 0;
};

DECLARE_DELEGATE_BEGIN(AVCallbackDelegate, AVCallback)
IMPLEMENT_DELEGATE_METHOD(OnComplete, (int32 result, const std::string& error_info), (result, error_info))
DECLARE_DELEGATE_END()

} // namespace av
} // namespace tencent