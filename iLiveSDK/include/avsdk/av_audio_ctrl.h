#pragma once

#include "av_common.h"

namespace tencent {
namespace av {

/**
@brief 音频编解码类型。
@details 音频编解码类型。
*/
enum AudioCodecType {
  AUDIO_CODEC_TYPE_SILK = 4102, ///< SILK。
  AUDIO_CODEC_TYPE_CELT = 4103, ///< CELT。
};

/**
@brief 音频控制器的封装类。

@details 由SDK在进入房间后创建。用户通过AVContext获取此类，无法自己直接实例化此类。

@remark 。
*/
class AV_EXPORT AVAudioCtrl {
  DISALLOW_EVIL_DESTRUCTIONS(AVAudioCtrl)
 public:
  /**
  @brief 获取通话中实时音频质量相关信息，业务侧可以不用关心，主要用来查看通话情况、排查问题等。

  @return 以字符串形式返回音频相关的质量参数。
  */
  virtual std::string GetQualityTips() = 0;



#if defined(ANDROID) || defined(TARGET_OS_IPHONE)
  virtual void PauseAudio() = 0;
  virtual bool ResumeAudio() = 0;

  /**
  @brief 获取麦克风数字音量。

  @return 麦克风数字音量。数字音量取值范围[0,100]。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual uint32 GetVolume() = 0;

  /**
  @brief 设置麦克风数字音量。

  @param [in] value 麦克风数字音量。数字音量取值范围[0,100]。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual void SetVolume(uint32 value) = 0;

  /**
  @brief 获取麦克风动态音量。

  @return 麦克风动态音量。动态音量取值范围[0,100]。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual uint32 GetDynamicVolume() = 0;

  /**
  @brief 打开/关闭麦克风。

  @param [in] is_enable 是否打开。

  @return true表示操作成功，false表示操作失败。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual bool EnableMic(bool is_enable) = 0;

  /**
  @brief 打开/关闭扬声器。

  @param [in] is_enable 是否打开。

  @return true表示操作成功，false表示操作失败。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual bool EnableSpeaker(bool is_enable) = 0;

  /**
  @brief 设置外放模式。

  @param [in] output_mode 外放模式。0为听筒模式，1为扬声器模式。

  @return true表示操作成功，false表示操作失败。

  @remark
  . 这个接口只有Android/iOS平台支持。
  */
  virtual bool SetAudioOutputMode(int output_mode) = 0;

#endif
    
#if defined(TARGET_OS_IPHONE) || defined(ANDROID)
 /**
  @brief 修改音频场景。。<br/>
  @param category 0代表实时场景，1代表主播模式，2代表观看模式，3代表高音质模式，其他模式待扩展。
  @remark 这个接口只有Android/iOS平台支持。
 */
 virtual int ChangeAudioCategory(int category) = 0;
#endif

#ifndef ANDROID
  /**
  @brief 打开/关闭音频自监听功能。

  @details 打开/关闭音频自监听功能，打开以后，就可以在本地听到自己的声音。

  @param [in] is_enable 打开还是关闭。

  @remark
  . 这个接口只有PC和iOS平台支持。
  */
  virtual bool EnableLoopback(bool is_enable) = 0;
#endif

  /*
    @brief 音频数据输入和输出类型。
  */
  enum AudioDataSourceType {
    AUDIO_DATA_SOURCE_MIC = 0, ///获取本地麦克风采集的音频数据。
    AUDIO_DATA_SOURCE_MIXTOSEND = 1, ///输入额外的音频数据，与本地发送的音频数据混音后发送出去。
    AUDIO_DATA_SOURCE_SEND = 2, ///发送方最终发送出去的音频数据。
    AUDIO_DATA_SOURCE_MIXTOPLAY = 3, ///输入额外的音频数据，与本地播放的音频数据混音后给扬声器播放出来。
    AUDIO_DATA_SOURCE_PLAY = 4, ///获取本地扬声器播放音频数据。
    AUDIO_DATA_SOURCE_NETSTREM = 5, ///接收方收到的音频数据。
    AUDIO_DATA_SOURCE_VOICEDISPOSE = 6, ///麦克风音频数据预处理。
    AUDIO_DATA_SOURCE_END = 7, ///结束标志。
  };

  /**
    @brief 音频数据回调函数定义。
    @details 通过回调函数，来通知外部读取或者写入具体类型的音频数据。
    @param [in] audio_frame 音频数据，输出数据类型从此参数读取数据，输入数据类型将数据写入此参数。
    @param [in] src_type 音频数据类型。
    @param [in] custom_data 用户自定义回调数据。
    @details 对于输出音频数据，AudioFrame::data指向音频数据buffer, AudioFrame::data_size表示音频数据大小。
     对于输入音频数据，AudioFrame::data指向数据缓冲区, 用户将音频数据写入缓冲区, AudioFrame::data_size表示数据缓冲区总大小, 用户需改写为输入音频数据实际大小。
     回调处理要求是非阻塞的，SDK回调时间间隔稳定在20ms左右, 在回调中阻塞过长时间会导致声音异常等问题。
     SDK通过回调返回值来判断数据处理是否成功输。处理成功请返回 AV_OK，否则返回 AV_ERR_FAILED。

    @remark 回调函数设定为专门处理数据用。函数回调在非主线程，请确保线程安全。特别是不要在回调函数中直接调用SDK接口。
  */
  typedef int(*AudioDataCallback)(AudioFrame* audio_frame, AudioDataSourceType src_type, void* custom_data);

  /**
    @brief 注册具体数据类型的回调函数。
    @param [in] src_type 音频数据类型。
    @param [in] callback 用户自定义的回调函数地址。
    @param [in] custom_data 用户自定义回调数据。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 无。
  */
  virtual int RegistAudioDataCallback(AudioDataSourceType src_type, AudioDataCallback callback, void* custom_data) = 0;

  /**
    @brief 反注册具体数据类型的回调函数。
    @param [in] src_type 音频数据类型。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 无。
  */
  virtual int UnregistAudioDataCallback(AudioDataSourceType src_type) = 0;

  /**
    @brief 反注册所有回调函数。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 无。
  */
  virtual int UnregistAudioDataCallbackAll() = 0;

  /**
    @brief 设置某类型的音频格式参数。
    @param [in] src_type 音频数据类型。
    @param [in] audio_desc 音频数据的格式。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 会直接影响callback传入的AudioFrame的格式。
  */
  virtual int SetAudioDataFormat(AudioDataSourceType src_type, AudioFrameDesc audio_desc) = 0;

  /**
    @brief 获取某类型的音频格式参数。
    @param [in] src_type 音频数据类型。
    @param [out] audio_desc 音频数据的格式。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 无。
  */
  virtual int GetAudioDataFormat(AudioDataSourceType src_type, AudioFrameDesc& audio_desc) = 0;

  /**
    @brief 设置某类型的音频音量。
    @param [in] src_type 音频数据类型。
    @param [in] volume 音量 (范围 0-1)。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 没有注册对应类型的callback会直接返回AV_ERR_FAILED。
  */
  virtual int SetAudioDataVolume(AudioDataSourceType src_type, float volume) = 0;



  /**
    @brief 获取某类型的音频音量。
    @param [in] src_type 音频数据类型。
    @param [out] volume 音量 (范围 0-1)。
    @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
    @remark 没有注册对应类型的callback无法设置音量。
  */
  virtual int GetAudioDataVolume(AudioDataSourceType src_type, float* volume) = 0;
    
    /**
     @brief 设置某类型的音频音量。
     @param [in] src_type 音频数据类型。
     @param [in] volume 音量 (范围 0-121)。// 0代表静音，－30db－30db，每增加1增加0.5db
     @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
     @remark 没有注册对应类型的callback会直接返回AV_ERR_FAILED。
     */
   virtual int SetAudioDataDBVolume (AudioDataSourceType src_type, int  volume) = 0;
    
    /**
     @brief 获取某类型的音频音量。
     @param [in] src_type 音频数据类型。 // 0代表静音，－30db－30db，每增加1增加0.5db
     @param [out] volume 音量 (范围 0-121)。
     @return 成功返回AV_OK, 否则返回AV_ERR_FAILED。
     @remark 没有注册对应类型的callback无法设置音量。
     */
    virtual int GetAudioDataDBVolume(AudioDataSourceType src_type, int* volume) = 0;

};

} // namespace av
} // namespace tencent