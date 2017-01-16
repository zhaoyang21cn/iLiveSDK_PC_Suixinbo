#pragma once

#include "av_common.h"
#include "av_device_base.h"
#include <vector>

namespace tencent {
namespace av {

class AVContext;
/// 常量宏，表示未知的设备类型，可作为默认值。
#define DEVICE_UNKNOWN      "\\unknown"           // Unknown device type.

// Video input/output device type/id
#define DEVICE_VIDEO        "\\video"               // Video device type.
#define DEVICE_CAMERA       "\\video\\camera"       // Camera device type.
#define DEVICE_REMOTE_VIDEO "\\video\\remote_video" // The virtual remote video output device.
#define DEVICE_EXTERNAL_CAPTURE "\\video\\external_capture" //external capture device type.

#define DEVICE_LOCAL_SCREEN_VIDEO "\\video\\local_screen_video" //local screen video.
#define DEVICE_REMOTE_SCREEN_VIDEO "\\video\\remote_screen_video" //remote screen video.

// Audio input/output device type/id
#define DEVICE_AUDIO        "\\audio"               // Audio device type.
#define DEVICE_MIC          "\\audio\\mic"          // Mic device type.
#define DEVICE_PLAYER       "\\audio\\player"       // Sound player device type.
#define DEVICE_ACCOMPANY    "\\audio\\accompany"    // Audio Accompany device type.

//////////////////////////////////////////////////////////////////////////
//
// 音频设备相关的由此开始

/// 常量宏，表示音量的最小值。
#define MIN_AUDIO_DEVICE_VOLUME 0

/// 常量宏，表示音量的最大值。
#define MAX_AUDIO_DEVICE_VOLUME 121

/// 常量宏，表示默认的屏幕视频的采集频率
#define DEFAULT_SCREEN_VIDEO_CAPTURE_FPS 10

/// 常量宏，表示默认的屏幕视频的最小采集频率
#define MIN_SCREEN_VIDEO_CAPTURE_FPS 1

/// 常量宏，表示默认的屏幕视频的最大采集频率
#define MAX_SCREEN_VIDEO_CAPTURE_FPS 10

/**
@brief 音频设备封装类的基类。

@details AVAudioDevice表示系统中一个物理的或虚拟的音频设备。
  AVAudioDevice提供了操作音频设备的通用方法，例如音量调节等。
  音频设备可分为音频输入设备和音频输出设备。

@remark 下面所提到的音量，全部为App内部的音量，和操作系统的音量没有联系。

@todo SetFrameDataCallback缺注释。
@todo GetFrameDataCallback()和GetFrameCustomData()必要性？
*/
class AV_EXPORT AVAudioDevice : public AVDevice {
 public:
  /**
  @brief 获得音频设备音量大小。

  @return 返回音频设备音量值，取值范围[0,100]。

  @remark 需要特别说明的是伴奏，当输入源为播放器（QQ音乐、酷狗音乐）时，值为相对音量，10为1倍，100为10倍，1为原来的1/10。
    当输入源为系统音量时，值为绝对音量。

  @todo 伴奏这里的说明比较模糊。
  */
  virtual uint32 GetVolume() = 0;

  /**
  @brief 设置音频设备音量大小。

  @param value 音频设备目标音量，取值范围[0,100]。

  @remark 如果入参的大小超出取值范围，会自动进行截取。
    需要特别说明的是伴奏，当输入源为播放器（QQ音乐、酷狗音乐）时，值为相对音量，10为1倍，100为10倍，1为原来的1/10。
    当输入源为系统音量时，值为绝对音量。

  @todo 参数命名风格不一致。
  */
  virtual void SetVolume(uint32 value) = 0;

  /**
  @brief 获得音频设备动态音量。

  @return 返回音频设备动态音量，取值范围[0,100]。

  @todo 动态音量有没有更加通俗的称呼。
  */
  virtual uint32 GetDynamicVolume() = 0;

  /**
  @brief SetFrameDataCallback()的回调函数， 内部使用。

  @details 此函数是和SetFrameDataCallback()一起使用的回调函数，用来向App回传音频数据。
  */
  typedef void(*FrameDataCallback)(AudioFrame* audio_frame, void* custom_data);

  /**
  @brief 设置采集回调函数，内部使用。
  @details 设置采集回调函数，内部使用。
  */
  virtual void SetFrameDataCallback(FrameDataCallback frame_callback, void* custom_data = NULL) = 0;

  /**
  @details 获取采集回调函数，内部使用。
  */
  virtual FrameDataCallback GetFrameDataCallback() = 0;

  /**
  @details 获取采集回调函数自定义数据，内部使用。
  */
  virtual void* GetFrameCustomData() = 0;
};

/**
@brief 音频预览能力的封装类。

@details SDK的各种音频设备封装类，通过继承AVSupportAudioPreview，向App提供音频预览能力。
  App可以通过AVSupportAudioPreview获得音频设备的输入/输出数据。

@todo 补充说明预览回调会重复触发。
*/
class AV_EXPORT AVSupportAudioPreview {
 public:
  /**
  @brief SetPreviewCallback()的回调函数。

  @details 此函数是和SetPreviewCallback()一起使用的回调函数，用来向App回传音频数据。

  @param audio_frame 音频帧对象。
  @param custom_data 值等于调用SetPreviewCallback()时的入参custom_data。
  */
  typedef void(*PreviewCallback)(AudioFrame* audio_frame, void* custom_data);

  /**
  @brief 设置音频预览回调。

  @details App可以通过设置音频预览回调，在回调函数中获得音频设备的输入/输出数据。

  @param [in] frame_callback 函数指针，指向App定义的回调函数，NULL表示取消回调。
  @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。
  */
  virtual void SetPreviewCallback(PreviewCallback frame_callback, void* custom_data = NULL) = 0;

  /**
  @brief 音频预览回调函数。
  @details App可以通过获取上次设置的音频预览回调函数，没有设置过返回NULL。
  */
  virtual PreviewCallback GetPreviewCallback() = 0;

  /**
  @brief 获取音频预览回调自定义数据。
  @details App可以通过获取上次设置的音频预览自定义数据，没有设置过返回NULL
  */
  virtual void* GetPreviewCustomData() = 0;
};

/**
@brief 远端音频设备的封装类。

@details 远端音频设备是一个虚拟的设备，它属于音频输出设备，用于输出远端音频。
  可以把AVRemoteAudioDevice理解成是所有房间成员的音频数据分发器。
  App可以通过AVRemoteAudioDevice获得单个房间成员的音频数据。
*/
class AV_EXPORT AVRemoteAudioDevice
  : public AVAudioDevice
  , public AVSupportAudioPreview {
 public:

};

/**
@brief 麦克风的封装类。

@details 麦克风属于音频输入设备。
  一个终端上可能存在多个麦克风。
  可以使用AVDeviceMgr::GetDeviceByType(DEVICE_MIC)，获得当前系统的麦克风列表。
*/
class AV_EXPORT AVMicDevice
  : public AVAudioDevice {
 public:

};

/**
@brief 音频播放设备的封装类。

@details 音频播放设备属于音频输出设备音频，它包括扬声器和听筒。
  一个终端上可能存在多个音频播放设备。
  可以使用AVDeviceMgr::GetDeviceByType(DEVICE_PLAYER)，获得当前系统的音频播放设备列表。
*/
class AV_EXPORT AVPlayerDevice
  : public AVAudioDevice {
 public:

};

/**
@brief 伴奏设备。

@details 伴奏设备是一个虚拟的设备，它既是音频输入设备，也是音频输出设备。
  App可以选择系统伴奏或者应用伴奏来添加背景声音，本地和远端都会输出背景声音。

@attention 只有Windows版本的SDK才支持伴奏。
*/
class AV_EXPORT AVAccompanyDevice
  : public AVAudioDevice {
 public:
  /**
  @brief 伴奏源类型。

  @todo 枚举值定义可以再精简一些。
  */
  enum SourceType {
    AV_ACCOMPANY_SOURCE_TYPE_NONE = 0, ///< 默认值，无意义。
    AV_ACCOMPANY_SOURCE_TYPE_SYSTEM = 1, ///< 系统伴奏，来源为系统的声音。
    ACCOMPANY_SOURCE_TYPE_PROCESS = 2, ///< 应用伴奏，来源为播放器进程的声音。
  };

 public:
  /**
  @brief 设置伴奏源。

  @details 当伴奏源为ACCOMPANY_SOURCE_TYPE_PROCESS，player_path不能为空，
    若media_file_path为空，则自动以当前播放器播放的声音为伴奏源；
    若media_file_path不为空，会自动使用播放器播放指定歌曲。
    当伴奏源为ACCOMPANY_SOURCE_TYPE_ SYSTEM，player_path和media_file_path不需要设置。

  @param player_path 播放器路径。
  @param media_file_path 使用播放器播放的音频文件路径。
  @param source_type 伴奏源。

  @todo 这个接口用法太复杂了，可以进一步优化。
  */
  virtual void SetSource(std::string player_path, std::string media_file_path, SourceType source_type) = 0;

  /**
  @brief 获得伴奏源类型。

  @return 返回伴奏源类型，详情见SourceType的定义。
  */
  virtual SourceType GetSourceType() = 0;

  /**
  @brief 获得播放器进程的路径。

  @return 当伴奏源类型为ACCOMPANY_SOURCE_TYPE_PROCESS时，返回播放器进程的路径。
  */
  virtual std::string GetPlayerPath() = 0;

  /**
  @brief 获得影音文件路径。

  @return 当伴奏源类型为ACCOMPANY_SOURCE_TYPE_PROCESS时，返回影音文件的路径。
  */
  virtual std::string GetMediaFilePath() = 0;
};

//////////////////////////////////////////////////////////////////////////
//
// 视频设备相关的由此开始

/**
@brief 视频设备封装类的基类。

@details AVVideoDevice表示系统中一个物理的或虚拟的视频设备。
  视频设备可分为视频输入设备和视频输出设备。

@todo SetFrameDataCallback()是否跟Preview重复了？
*/
class AV_EXPORT AVVideoDevice : public AVDevice {
 public:
  typedef void(*FrameDataCallback)(VideoFrame* video_frame, void* custom_data);

  /**
  @brief 设置采集回调函数，内部使用。
  */
  virtual void SetFrameDataCallback(FrameDataCallback frame_callback, void* custom_data = NULL) = 0;

  /**
  @brief 获取采集回调函数，内部使用。
  */
  virtual FrameDataCallback GetFrameDataCallback() = 0;

  /**
  @brief 获取采集回调函数的自定义数据，内部使用。
  */
  virtual void* GetFrameCustomData() = 0;
};

/**
@brief 视频预览能力的封装类。

@details SDK的各种视频设备封装类，通过继承AVSupportVideoPreview，向App提供视频预览能力。
  App可以通过AVSupportVideoPreview获得视频设备的输入/输出数据。

@param device_id 当为空字符串时，代表这个设备的所有画面都用这组设置的参数；当不为空时，如果该设备是AVRemoteVideoDevice时，将device_id设置为远端设备对应的成员identifier，就可以针对每个成员的画面设置这些参数。
@param width 预览画面宽度。如果设置为0，代表用视频图像的默认宽度和高度。
@param height 预览画面高度。如果设置为0，代表用视频图像的默认宽度和高度。
@param color_format 预览视频图像的颜色格式。 如果设置为COLOR_FORMAT_NONE，代表用视频图像默认的颜色格式。
@param src_type 视频源类型。每个设备的视频源类型是固定的。
@todo 补充说明预览回调会重复触发。
@todo GetPreviewCallback()和GetPreviewCustomData()是否需要。
@todo SetPreviewParam()的入参使用结构。
*/
class AV_EXPORT AVSupportVideoPreview {
 public:
  /**
  @brief 视频预览能力的封装类。
  @details 通过SetPreviewParam设置，通过ClearPreviewParam来清空设置，当有图像数据时，SDK会根据设置参数进行转换。
  @details 如果没有设置过任何参数，则拿到的图像数据为原始图像数据。
  */
  struct PreviewParam {
    std::string device_id; ///预览设备id
    uint32 width; ///预览期望图像像素高
    uint32 height; ///预览期望图像像素宽
    ColorFormat color_format; ///预览期望图像格式
    VideoSrcType src_type; ///未使用
  };

  /**
  @brief SetPreviewCallback()的回调函数。

  @details 此函数是和SetPreviewCallback()一起使用的回调函数，用来向App回传视频数据。

  @param video_frame 视频帧对象。
  @param custom_data 值等于调用SetPreviewCallback()时的入参custom_data。
  */
  typedef void(*PreviewCallback)(VideoFrame* video_frame, void* custom_data);

  /**
  @brief 设置视频预览回调。

  @details App可以通过设置视频预览回调，在回调函数中获得视频设备的输入/输出数据。

  @param [in] frame_callback 函数指针，指向App定义的回调函数，NULL表示取消回调。
  @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。
  */
  virtual void SetPreviewCallback(PreviewCallback frame_callback, void* custom_data = NULL) = 0;

  /**
  @brief 设置预览视频画面的参数。

  @param id 画面Id。如果是本地摄像头画面，因为只有一路，可以填""。如果是远端视频画面，填每个画面的成员id即可。
  @param width 预览画面宽度，最好是4的倍数。
  @param height 预览画面高度，最好是4的倍数。
  @param color_format 色彩格式，SDK目前只支持RGB24、I420。

  @remark 目前仅Windows平台支持设置预览视频画面的参数。可以给每路成员分别设置，也可以给所有成员统一设置。如果是给所有成员设置, 则id填""即可。
  @todo 需要加返回值，加一个入参判断的逻辑。
  */
  virtual int SetPreviewParam(std::string id, uint32 width, uint32 height, ColorFormat color_format) = 0;

  /**
  @brief 清空所有预览视频画面的参数。

  @remark 清空后，预览接口将返回原始图像。
  */
  virtual int ClearPreviewParam() = 0;

  /**
  @brief 获取视频预览回调函数。
  @remark App可以通过获取上次设置的视频预览回调，没有设置过返回NULL。
  */
  virtual PreviewCallback GetPreviewCallback() = 0;

  /**
  @brief 获取视频预览回调自定义数据。
  @remark App可以通过获取上次设置的自定义的参数，没有设置过返回NULL
  */
  virtual void* GetPreviewCustomData() = 0;
};

/**
@brief 视频预处理能力的封装类。

@details SDK的各种视频设备封装类，通过继承AVSupportVideoPreTreatment，向App提供视频预处理能力。
  App可以通过AVSupportVideoPreTreatment获得视频设备的输入数据。
*/
class AV_EXPORT AVSupportVideoPreTreatment {
 public:
  /**
  @brief SetPreTreatmentFun()的回调函数。

  @details 此函数是和SetPreTreatmentFun()一起使用的回调函数，App可以通过实现此函数来对视频数据进行预处理。

  @param video_frame 视频帧对象。
  @param custom_data 值等于调用SetPreviewCallback()时的入参custom_data。
  */
  typedef void(*PreTreatmentFun)(VideoFrame* video_frame, void* custom_data);

  /**
  @brief 设置预处理函数指针。

  @param [in] pre_fun 预处理函数指针。
  @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

  @remark 业务侧实现该预处理函数，然后由SDK同步调用它。实现预处理函数的注意事项：预处理函数耗时不要过久，最好控制在10ms内；同时不能改变图像大小和图像颜色格式。
  */
  virtual void SetPreTreatmentFun(PreTreatmentFun pre_fun, void* custom_data = NULL) = 0;
};

/**
@brief 远端视频设备的封装类。

@details 远端视频设备是一个虚拟的设备，它属于视频输出设备，用于输出远端视频。
  可以把AVRemoteVideoDevice理解成是所有房间成员的视频数据分发器。
  App可以通过AVRemoteVideoDevice获得单个房间成员的视频数据。
*/
class AV_EXPORT AVRemoteVideoDevice
  : public AVVideoDevice
  , public AVSupportVideoPreview {
 public:

};

/**
@brief 摄像头的封装类。

@details 摄像头属于视频输入设备。

@remark iOS版本的SDK有特定的接口。
*/
class AV_EXPORT AVCameraDevice
  : public AVVideoDevice
  , public AVSupportVideoPreview
  , public AVSupportVideoPreTreatment {
 public:

#ifdef OS_IOS
  /**
  @brief 获取预览显示层。

  @details 同步返回结果。预览显示层是针对iOS做的一个高级封装。

  @return 预览显示层的id。

  @remark iOS特有接口。

  @todo 需要明确一下用法。
  */
  virtual void* GetPreviewLayer() = 0;

  /**
  @brief 获取iOS系统的摄像头视频图像采集对象。

  @details 获取iOS系统的摄像头图像采集对象。可以使用它来控制摄像头采集的自动调焦、图像分辨率、帧率等参数。

  @return 返回iOS系统的摄像头图像采集对象指针。
  */
  virtual void* GetCameraSession() = 0;
#endif
};

/**
@brief 外部视频捕获设备。

@details 外部视频捕获设备属于视频输入设备。

@remark
*/
class AV_EXPORT AVExternalCapture
    : public AVVideoDevice{
 public:
  /**
  @brief 外部输入视频数据接口。

  @details 外部视频捕获设备属于视频输入设备。

  @param frame 外部输入的视频帧数据。

  @remark 选中此设备并打开后，App通过此函数输入视频数据，SDK会将此数据代替摄像头采集的数据发送出去。
  */
  virtual int OnCaptureFrame(VideoFrame& frame) = 0;
};



/**
@brief 远端屏幕视频设备的封装类。

@details 远端屏幕视频设备是一种虚拟的设备，属于视频输出设备，用于输出接收到的远端屏幕视频。
*/
class AV_EXPORT AVRemoteScreenVideoDevice
  : public AVVideoDevice
  , public AVSupportVideoPreview {
 public:

};

/**
@brief 本地屏幕视频设备的封装类。

@details 本地屏幕视频设备是一种虚拟的设备，属于视频输入设备，用于采集本地屏幕视频。

@remark
  . 仅支持Windows平台发送屏幕视频。
  . 同一时刻，一个房间只允许一个人开启并发送屏幕视频。

*/
class AV_EXPORT AVLocalScreenVideoDevice
  : public AVVideoDevice
  , public AVSupportVideoPreview
  , public AVSupportVideoPreTreatment {
 public:
  /**
  @brief 设置屏幕画面捕获的参数。

  @details 设置屏幕画面捕获的参数。

  @param left/top/right/bottom 所要捕获屏幕画面的某个子区域或整个区域的左上角坐标(left, top)和右下角坐标(right, bottom)。它们是以屏幕的左上角坐标为原点的。
  @param fps 捕获帧率，取值范围[MIN_SCREEN_VIDEO_CAPTURE_FPS-MAX_SCREEN_VIDEO_CAPTURE_FPS]，具体参考MIN_SCREEN_VIDEO_CAPTURE_FPS和MAX_SCREEN_VIDEO_CAPTURE_FPS两个宏的定义。
  @remark
   . 如果left/top/right/bottom都为0，代表要捕获整个屏幕画面。所要捕获的画面最大不能超过整个屏幕，宽度最小不能小于16，高度最小不能小于4，并且宽度必须为16的倍数，高度必需为2的倍数，否则SDK内部也会自动修正。
   . 暂不支持在屏幕视频过程中更改分享画面大小和位置，所以这个接口必须在屏幕视频开始前调用才有效。
  */
  virtual void SetScreenCaptureParam(uint32 left = 0, uint32 top = 0, uint32 right = 0, uint32 bottom = 0,
                                     uint32 fps = DEFAULT_SCREEN_VIDEO_CAPTURE_FPS) = 0;

  /**
    @brief 获取屏幕画面捕获的参数。

    @details 获取屏幕画面捕获的参数。

    @param left/top/right/bottom 所要捕获屏幕画面的某个子区域或整个区域的左上角坐标(left, top)和右下角坐标(right, bottom)。它们是以屏幕的左上角坐标为原点的。
    @param fps 捕获帧率，取值范围[MIN_SCREEN_VIDEO_CAPTURE_FPS-MAX_SCREEN_VIDEO_CAPTURE_FPS]，具体参考MIN_SCREEN_VIDEO_CAPTURE_FPS和MAX_SCREEN_VIDEO_CAPTURE_FPS两个宏的定义。
    */
  virtual void GetScreenCaptureParam(uint32& left, uint32& top, uint32& right, uint32& bottom, uint32& fps) = 0;

  /**
    @brief 设置屏幕视频的模式。

    @details 设置屏幕视频的模式。可以是清晰模式，也可以是流畅模式，默认为清晰模式。
    清晰模式指：编码分辨率为1920*1200，帧率由SDK内部控制。实际上，最终的编码分辨率是多大，还要考虑到采集的分辨率是多大；如果采集分辨率小于1920*1200，则最终的编码分辨率为采集分辨率；如果采集分辨率大于1920*1200，则最终的编码分辨率为1920*1200。
    流畅模式指：编码分辨率为960*720，帧率由SDK内部控制。实际上，最终的编码分辨率也会根据实际采集分辨率做些调整，也就是如果采集分辨率比较大，则会按采集分辨率的长宽等比例缩小得到最终的编码分辨率；例如，假设采集分辨率为1920*1200，则最终的编码分辨率为960*540。

    @param is_enable 当为true表示开启清晰模式，否则为流畅模式。
  */
  virtual void EnableHDMode(bool is_enable) = 0;
};

} // namespace av
} // namespace tencent
