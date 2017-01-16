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
	WATER_MARK_TYPE_NONE = 0,
	WATER_MARK_TYPE_320_240 = 1,//针对编码分辨率为320*240的视频设置水印。
	WATER_MARK_TYPE_480_360 = 2,//针对编码分辨率为480*360的视频设置水印。
	WATER_MARK_TYPE_640_480 = 3,//针对编码分辨率为640*480的视频设置水印。
	WATER_MARK_TYPE_640_368 = 4,//针对编码分辨率为640*368的视频设置水印。
	WATER_MARK_TYPE_960_540 = 5,//针对编码分辨率为960*540的视频设置水印。
	WATER_MARK_TYPE_1280_720 = 6,//针对编码分辨率为1280*720的视频设置水印。
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
  DISALLOW_EVIL_DESTRUCTIONS(AVVideoCtrl)
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
  virtual int AddWaterMark(int water_mark_type, int *argb_data, int width, int height) = 0;

#if defined(ANDROID) || defined(TARGET_OS_IPHONE)
  //摄像头设备相关
  typedef void (*EnableCameraCompleteCallback)(bool is_enable, int ret_code, void* custom_data);
  typedef void (*SwitchCameraCompleteCallback)(int camera_id, int ret_code, void* custom_data);

  /**
  @brief 打开/关闭摄像头。

  @param [in] camera_id 为摄像头id。 camera_id等于0时代表前置摄像头，camera_id等于1时代表后置摄像头。
  @param [in] is_enable 是否打开。
  @param [in] callback 操作完成的回调。
  @param [in] custom_data 业务侧自定义参数。会在操作回调中原样返回。

  @return 返回错误码。当返回AV_OK时，操作回调才会被执行；否则就不会执行，需要处理具体的错误码。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual int EnableCamera(int camera_id, bool is_enable, EnableCameraCompleteCallback callback, void* custom_data) = 0;

  /**
  @brief 却换摄像头。

  @param [in] camera_id 摄像头的id。id取值范围[0, 摄像头个数-1]。
  @param [in] callback 操作完成的回调。
  @param [in] custom_data 业务侧自定义参数。会在操作回调中原样返回。

  @return 返回错误码。当返回AV_OK时，操作回调才会被执行；否则就不会执行，需要处理具体的错误码。

  @remark
  . 这个接口只有Android/iOS平台支持。
  . 建议用EnableCamera接口代替SwitchCamera接口，SwitchCamera接口没必要用。
  */
  virtual int SwitchCamera(int camera_id, SwitchCameraCompleteCallback callback, void* custom_data) = 0;

  /**
  @brief 获取摄像头个数。

  @return 返回摄像头个数。如果获取失败则返回0。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual int GetCameraNum() = 0;

  /**
  @brief 设置画面旋转角度。

  @param [in] rotation 画面旋转角度。角度取值：0，90，180，270。

  @remark
  . 这个接口只有Android平台支持。
  */
  virtual void SetRotation(int rotation) = 0;

#if defined(ANDROID)
  virtual void SetCameraPara(jobject cameraPara) = 0;

  virtual jobject GetCameraPara() = 0;

  virtual void SetCameraPreviewChangeCallback(jobject cameraPreviewChangeCallback) = 0;

  virtual void SetAfterPreviewListener(jobject afterPreviewListener) = 0;

  virtual jobject GetCamera() = 0;

  virtual jobject GetCameraHandler() = 0;
#endif
  /**
    @brief 设置摄像头的预览回调。

    @details 设置摄像头的预览回调。如果设置了该回调，那么就可以获取所请求(请求几路就可以获得几路)的远端视频画面的帧序列，业务侧可以实现对视频帧的处理及渲染等。

    @param [in] callback 预览回调。
    @param [in] custom_data 业务侧自定义参数。会在预览回调中原样返回。

    @return true 代表设置成功，否则设置失败。

    @remark 该音视频SDK会在主线程调用该预览回调，业务侧根据实际需要决定是否却换线程。

    @remark
    . 这个接口只有Android/iOS平台支持。
  */
  virtual bool SetLocalVideoPreviewCallback(AVSupportVideoPreview::PreviewCallback callback, void* custom_data) = 0;

  /**
    @brief 设置摄像头前处理函数

    @details 设置摄像头的前处理函数。如果设置了该回调，那么本地显示的数据为处理后的图像，并且发送给远端的图像数据也为处理后的数据。

    @param [in] callback 前处理回调。
    @param [in] custom_data 业务侧自定义参数。会在预览回调中原样返回。

    @return true 代表设置成功，否则设置失败。

    @remark 该音视频SDK在非主线程调用

    @remark
    . 这个接口只有Android平台支持。
  */
  virtual bool SetLocalVideoPreProcessCallback(AVSupportVideoPreTreatment::PreTreatmentFun callback,
      void* custom_data) = 0;

  /**
  @brief 设置远端视频的预览回调。

  @details 设置远端视频的预览回调。如果设置了该回调，那么就可以获取所请求(请求几路就可以获得几路)的远端视频画面的帧序列，业务侧可以实现对视频帧的处理及渲染等。

  @param [in] callback 预览回调。
  @param [in] custom_data 业务侧自定义参数。会在预览回调中原样返回。

  @return true 代表设置成功，否则设置失败。

  @remark 该音视频SDK会在主线程调用该预览回调，业务侧根据实际需要决定是否却换线程。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual bool SetRemoteVideoPreviewCallback(AVSupportVideoPreview::PreviewCallback callback, void* custom_data) = 0;

  /**
    @brief 设置远端屏幕视频设备的预览回调。

    @details 设置远端屏幕视频设备的预览回调。如果设置了该回调，那么就可以获取所请求的远端屏幕视频设备的视频画面的帧序列，业务侧可以实现对视频帧的处理及渲染等。

    @param [in] callback 预览回调。
    @param [in] custom_data 业务侧自定义参数。会在预览回调中原样返回。

    @return true 代表设置成功，否则设置失败。

    @remark 该音视频SDK会在主线程调用该预览回调，业务侧根据实际需要决定是否却换线程。

    @remark
    . 这个接口只有Android/iOS平台支持。
    */
  virtual bool SetRemoteScreenVideoPreviewCallback(AVSupportVideoPreview::PreviewCallback callback,
      void* custom_data) = 0;

  //外部视频捕获设备相关
  typedef void (*EnableExternalCaptureCompleteCallback)(bool, int, void*);

  /**
  @brief 打开/关闭外部视频捕获设备。

  @param [in] is_enable 是否打开。
  @param [in] callback 操作完成的回调。
  @param [in] custom_data 业务侧自定义参数。会在操作回调中原样返回。

  @return 返回错误码。当返回AV_OK时，操作回调才会被执行；否则就不会执行，需要处理具体的错误码。
  */
  virtual int EnableExternalCapture(bool is_enable, EnableExternalCaptureCompleteCallback callback,
                                    void* custom_data) = 0;

  /**
  @brief 输入从外部视频捕获设备获取的视频图像到SDK。SDK将会将数据编码之后发给接收方。

  @param [in] frame 视频帧数据及相关参数。

  @remark 要控制好传入视频帧的频率，具体频率视实际使用场景而定。
  @remark 图像颜色格式。当前仅支持COLOR_FORMAT_I420。
  @remark 视频源类型。当前仅支持VIDEO_SRC_TYPE_CAMERA。

  @return 返回值为AV_OK时表示成功，否则表示失败。
  */
  virtual int FillExternalCaptureFrame(VideoFrame& frame) = 0;


  /**
   @brief 设置音视频SDK的美颜程度参数

   @param [in] param 美颜程度参数。

   @remark param取值范围在0-9之间，0表示美颜关闭

   @return 返回值为true时表示成功，否则表示失败。
   */

  virtual bool InputBeautyParam(float param) = 0;
    

    
#if defined(TARGET_OS_IPHONE)
    
    /**
     @brief 判断当前使用的是前置摄像头还是后置
     
     @return 返回值为true时表示前置，否则表示后置。
     */
    
    virtual bool isFrontcamera() = 0;

  virtual void switchVideoDecode(bool isEnable) = 0;
    
  virtual void switchVideoEncode(bool isEnable) = 0;
    
  typedef void(*IOSCameraRawCallback)(void* sampleBuf,void **result, void* custom_data);

  virtual bool SetCameraRawCallback(IOSCameraRawCallback callback, void* custom_data) = 0;

#endif
#endif
};

} // namespace av
} // namespace tencent