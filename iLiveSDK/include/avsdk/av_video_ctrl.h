#pragma once

#include "av_common.h"

#if defined(ANDROID)
#include <jni.h>
#endif

namespace tencent {
namespace av {

/**
@brief 视频编码器类型。

@details 视频编码器类型。
*/
enum VideoCodecType {
    VIDEO_CODEC_TYPE_H264 = 5, // h264
};


/**
@brief 水印类型。

@details 水印类型。也就是针对哪种编码分辨率的视频设置水印。
*/
enum WaterMarkType {
    WATER_MARK_TYPE_NONE        = 0,
    WATER_MARK_TYPE_320_240     = 1, //针对编码分辨率为320*240的视频设置水印。
    WATER_MARK_TYPE_480_360     = 2, //针对编码分辨率为480*360的视频设置水印。
    WATER_MARK_TYPE_640_480     = 3, //针对编码分辨率为640*480的视频设置水印。
    WATER_MARK_TYPE_640_368     = 4, //针对编码分辨率为640*368的视频设置水印。
    WATER_MARK_TYPE_960_540     = 5, //针对编码分辨率为960*540的视频设置水印。
    WATER_MARK_TYPE_1280_720    = 6, //针对编码分辨率为1280*720的视频设置水印。
    WATER_MARK_TYPE_192_144     = 7, //针对编码分辨率为192*144的视频设置水印。
    WATER_MARK_TYPE_MAX,
};


/**
@brief 摄像头信息。

@details 摄像头信息。
*/
struct CameraInfo {
    std::string device_id; ///< 摄像头设备id
    uint32 width;  ///< 采集画面宽度
    uint32 height; ///< 采集画面高度
    uint32 fps; ///< 采集帧率
};

/**
@brief 视频控制器的封装类。

@details 由SDK在进入房间后创建。用户通过AVContext获取此类，无法自己直接实例化此类。
*/
class AV_EXPORT AVVideoCtrl {
protected:
    virtual ~AVVideoCtrl() {}

public:
    /**
    @brief 获取通话中实时视频质量相关信息，业务侧可以不用关心，主要用来查看通话情况、排查问题等。

    @return 以字符串形式返回视频相关的质量参数。
    */
    virtual std::string GetQualityTips() = 0;

    /**
    @brief 开启外部采集之前必须设置外部采集的能力，包括图像大小，帧率。

    @return true表示成功，false表示失败。
    @remark
    . 这个接口暂不支持。
    */
    virtual bool SetExternalCapAbility(CameraInfo* info) = 0;

    /**
    @brief 设置音视频SDK画面的水印。
    @remark 为了画面里水印的效果，每个编码分辨率需要设置对应的水印。
            目前注意在startcontext之后进入房间前调。
    @return 返回值为av_ok时表示成功，否则表示失败。
    */
    virtual int AddWaterMark(int water_mark_type, int* argb_data, int width, int height) = 0;

    /**
    @brief 设置音视频SDK的美颜程度参数

    @param [in] grade 美颜程度参数。

    @remark grade取值范围在0-9之间，0表示美颜关闭

    @return 返回值为true时表示成功，否则表示失败。
    */
    virtual int SetSkinSmoothGrade(int grade) = 0;

    /**
    @brief 设置音视频SDK的美白程度参数

    @param [in] grade 美白程度参数。

    @remark grade取值范围在0-9之间，0表示美白关闭

    @return 返回值为true时表示成功，否则表示失败。
    */
    virtual int SetSkinWhitenessGrade(int grade) = 0;
};

} // namespace av
} // namespace tencent
