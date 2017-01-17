#pragma once

#include "av_common.h"

namespace tencent {
namespace av {

/**
Spear流控参数Json格式，字段意义和范围。
{
    "audio":{ 音频参数 (所有参数必填)
        "aec":0, AEC开关 (-1自适应, 0关，1开)
        "agc":0, AGC开关 (-1自适应, 0关，1开)
        "ans":0, ANC开关 (-1自适应, 0关，1开)
        "au_scheme":1, 音频场景 (2种场景: 1主播，2观众)
		"codec_prof":4106, 音频编码协议 (固定为4106 acc)
		"sample_rate":48000, 采样率 (固定为48000)
        "channel":2, 通道数 (2个档位: 1单通道，2双通道)
        "frame":40, 帧长 (-1自适应, 自定义2个档位: 40, 80)
        "kbps":24, 编码码率 (-1自适应, 最小值10, 最大值64)
        "silence_detect":0 静音检测 (0关，1开)
        "anti_dropout":0, 冗余抗丢包 (-1自适应, 0关，1开)
    },
    "video":{ 视频参数 (所有参数必填)
        "codec_prof":5, 视频编码协议 (固定为5: h264)
        "format_fix_height":368, 固定图像高 (和WEB流控配置可选分辨率对齐, 其他分辨率不支持)
        "format_fix_width":640, 固定图像宽 (和WEB流控配置可选分辨率对齐, 其他分辨率不支持)
        "format_max_height":-1, 最大图像高 (和WEB流控配置可选分辨率对齐, 其他分辨率不支持)
        "format_max_width":-1, 最大图像宽 (和WEB流控配置可选分辨率对齐, 其他分辨率不支持)
        "fps":25, 编码帧率 (-1自适应, 最小值10, 最大值30)
        "live_adapt":0, 自适应流控 (-1自适应, 0关，1开)
        "fqueue_time":5, 帧序列时间 (-1自适应, 最小值1, 最大值5)
        "maxkbps":800, 最大码率 (最小值30, 最大值1500)
        "minkbps":800, 最小码率 (最小值30, 最大值1500)
        "maxqp":31, 最大QP (-1自适应, 最小值10, 最大值51)
        "minqp":18, 最大QP (-1自适应, 最小值10, 最大值51)
        "qclear":1, qclear (-1自适应, 0关，1开)
		"anti_dropout":0, 冗余抗丢包 (-1自适应, 0关，1开)
        "small_video_upload":0 小画面上传 (目前不支持打开，固定填0)
    },
    "net":{ 网络参数 (所有参数必填)
        "rc_anti_dropout":1, 重传抗丢包 (-1自适应, 0关，1开)
        "rc_init_delay":1000, 重传初始延迟 (-1自适应, 最小值0, 最大值10000)
        "rc_max_delay":2000 重传最大延迟 (-1自适应, 最小值0, 最大值10000)
    }
}
**/

/// SpearEngine配置模式。
enum SpearEngineMode {
  SPEAR_EGINE_MODE_WEBCLOUD = 1, ///< WEB云端流控配置模式。
  SPEAR_EGINE_MODE_CUSTOM = 2, ///< 自定义流控配置模式。
};

/**
@brief Spear云端流控配置控制器。
*/

class AV_EXPORT AVWebCloudSpearEngineCtrl {
    DISALLOW_EVIL_DESTRUCTIONS(AVWebCloudSpearEngineCtrl)

public:
    /**
    @brief 设置默认流控参数。

    @param [in] jsonParam 默认流控参数

    @return 设置成功返回AV_OK, 否则返回失败。

    @details 仅当WEB配置拉取异常的情况下（从未从云流控配置系统成功拉取过配置）生效。
    */
	virtual int32 SetDefaultParam(std::string jsonParam) = 0;
};

/**
@brief Spear自定义流控配置控制器。
*/

class AV_EXPORT AVCustomSpearEngineCtrl {
  DISALLOW_EVIL_DESTRUCTIONS(AVCustomSpearEngineCtrl)
 
public:
    /**
    @brief 新增角色及其对应的流控参数。

    @param [in] role 新增流控角色名

    @param [in] jsonParam 新增流控角色流控参数

    @return 成功返回AV_OK, 否则返回失败。
    */
	virtual int32 AddParamByRole(std::string role, std::string jsonParam) = 0;

    /**
    @brief 清空所有流控参数。

    @return void
    */
	virtual void Clear() = 0;

    /**
    @brief 获取当前自定义流控参数个数。

    @return 流控参数个数。
    */
	virtual uint32 GetParamCount() = 0;

    /**
    @brief 根据index获取已存在的流控角色名。

    @param [in] index 流控角色索引。

    @return 存在则返回流控角色名, 否则返回空串。
    */
	virtual std::string GetRoleByIndex(uint32 index) = 0;

    /**
    @brief 判断角色是否已存在。

    @param role 流控角色名

    @return 存在则返回true, 否则返回false。
    */
	virtual bool HasRole(std::string role) = 0;

    /**
    @brief 获取流控角色对应的流控参数。

    @param [in] role 流控角色名

    @return 成功返回流控角色对应的流控参数, 否则返回空串。
    */
	virtual std::string GetParamByRole(std::string role) = 0;

    /**
    @brief 获取当前默认流控角色名。

    @return 存在则返回流控角色名, 否则返回空串。

    @details SDK缺省将index为0对应的角色设置为默认角色。
    */
	virtual std::string GetDefaultRole() = 0;

    /**
    @brief 设置当前默认流控角色名。

    @return 成功返回AV_OK, 否则返回失败。

    @details SDK缺省将index为0对应的角色设置为默认角色。
    */
	virtual int32 SetDefaultRole(std::string role) = 0;
};

} // namespace av
} // namespace tencent