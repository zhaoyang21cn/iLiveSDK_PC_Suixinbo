#pragma once

#include "av_common.h"

namespace tencent {

/**
@brief CrashReport：crash上报模块。

@details crash上报模块。可以借助该模块进行crash上报。这边主要上报SDK内部出现的crash，
并由腾讯侧来查看和解决这些crash，以提高SDK的稳定性等。客户可以不用关心这些上报的细节。

*/
class AV_EXPORT CrashReport {
public:
    /**
    @brief 打开/关闭crash上报。

    @details 打开/关闭crash上报。

    @param [in] is_enable 是否打开。

    @param [in] show_ui crash的时候，是否显示界面提示以让用户确定是否上报crash。

    @return 无。

    @remark 可以在任意时刻调用该接口。
    */
    static void EnableCrashReport(bool is_enable, bool show_ui = false);
};

} // namespace tencent