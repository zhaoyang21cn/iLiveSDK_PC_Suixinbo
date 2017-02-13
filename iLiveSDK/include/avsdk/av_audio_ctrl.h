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
* @brief Mic 与Speaker 的状态值
*/
typedef enum AVAudioStatus {
    AV_AUDIO_CLOSE              = 0,
    AV_AUDIO_OPEN               = 1,
    AV_AUDIO_OPREATIING         = 2,
    AV_AUDIO_DEVICE_NOT_EXIST   = 3,
    AV_AUDIO_ERROR              = 4,
} audioStatus;

/**
@brief 音频控制器的封装类。

@details 由SDK在进入房间后创建。用户通过AVContext获取此类，无法自己直接实例化此类。

@remark 。
*/
class AV_EXPORT AVAudioCtrl {
protected:
    virtual ~AVAudioCtrl() {}

public:
    /**
    @brief 获取通话中实时音频质量相关信息，业务侧可以不用关心，主要用来查看通话情况、排查问题等。

    @return 以字符串形式返回音频相关的质量参数。
    */
    virtual std::string GetQualityTips() = 0;

    /**
    @brief 打开/关闭音频自监听功能。

    @details 打开/关闭音频自监听功能，打开以后，就可以在本地听到自己的声音。

    @param [in] is_enable 打开还是关闭。

    @remark
    . 这个接口只有PC和iOS平台支持。
    */
    virtual bool EnableLoopback(bool is_enable) = 0;

    /*
      @brief 音频数据输入和输出类型。
    */
    enum AudioDataSourceType {
        AUDIO_DATA_SOURCE_MIC           = 0, ///获取本地麦克风采集的音频数据。
        AUDIO_DATA_SOURCE_MIXTOSEND     = 1, ///输入额外的音频数据，与本地发送的音频数据混音后发送出去。
        AUDIO_DATA_SOURCE_SEND          = 2, ///发送方最终发送出去的音频数据。
        AUDIO_DATA_SOURCE_MIXTOPLAY     = 3, ///输入额外的音频数据，与本地播放的音频数据混音后给扬声器播放出来。
        AUDIO_DATA_SOURCE_PLAY          = 4, ///获取本地扬声器播放音频数据。
        AUDIO_DATA_SOURCE_NETSTREM      = 5, ///接收方收到的音频数据。
        AUDIO_DATA_SOURCE_VOICEDISPOSE  = 6, ///麦克风音频数据预处理。
        AUDIO_DATA_SOURCE_AACRAWSTREAM  = 7, ///编码AAC数据获取 内部使用类型，暂不对外开放
        AUDIO_DATA_SOURCE_END           = 8, ///结束标志。
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
       SDK通过回调返回值来判断数据处理是否成功输。处理成功请返回 AV_OK，否则返回 AV_ERR_FAIL。

      @remark 回调函数设定为专门处理数据用。函数回调在非主线程，请确保线程安全。特别是不要在回调函数中直接调用SDK接口。
    */
    typedef int(*AudioDataCallback)(AudioFrame* audio_frame, AudioDataSourceType src_type, void* custom_data);

    /**
      @brief 注册具体数据类型的回调函数。
      @param [in] src_type 音频数据类型。
      @param [in] callback 用户自定义的回调函数地址。
      @param [in] custom_data 用户自定义回调数据。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 无。
    */
    virtual int RegistAudioDataCallback(
        AudioDataSourceType src_type,
        AudioDataCallback callback,
        void* custom_data) = 0;

    /**
      @brief 反注册具体数据类型的回调函数。
      @param [in] src_type 音频数据类型。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 无。
    */
    virtual int UnregistAudioDataCallback(AudioDataSourceType src_type) = 0;

    /**
      @brief 反注册所有回调函数。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 无。
    */
    virtual int UnregistAudioDataCallbackAll() = 0;

    /**
      @brief 设置某类型的音频格式参数。
      @param [in] src_type 音频数据类型。
      @param [in] audio_desc 音频数据的格式。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 会直接影响callback传入的AudioFrame的格式。
    */
    virtual int SetAudioDataFormat(AudioDataSourceType src_type, AudioFrameDesc audio_desc) = 0;

    /**
      @brief 获取某类型的音频格式参数。
      @param [in] src_type 音频数据类型。
      @param [out] audio_desc 音频数据的格式。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 无。
    */
    virtual int GetAudioDataFormat(AudioDataSourceType src_type, AudioFrameDesc& audio_desc) = 0;

    /**
      @brief 设置某类型的音频音量。
      @param [in] src_type 音频数据类型。
      @param [in] volume 音量 (范围 0-1)。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 没有注册对应类型的callback会直接返回AV_ERR_FAIL。
    */
    virtual int SetAudioDataVolume(AudioDataSourceType src_type, float volume) = 0;

    /**
      @brief 获取某类型的音频音量。
      @param [in] src_type 音频数据类型。
      @param [out] volume 音量 (范围 0-1)。
      @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
      @remark 没有注册对应类型的callback无法设置音量。
    */
    virtual int GetAudioDataVolume(AudioDataSourceType src_type, float* volume) = 0;

    /**
     @brief 设置某类型的音频音量。
     @param [in] src_type 音频数据类型。
     @param [in] volume 音量 (范围 0-121)。// 0代表静音，－30db－30db，每增加1增加0.5db
     @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
     @remark 没有注册对应类型的callback会直接返回AV_ERR_FAIL。
     */
    virtual int SetAudioDataDBVolume(AudioDataSourceType src_type, int  volume) = 0;

    /**
     @brief 获取某类型的音频音量。
     @param [in] src_type 音频数据类型。 // 0代表静音，－30db－30db，每增加1增加0.5db
     @param [out] volume 音量 (范围 0-121)。
     @return 成功返回AV_OK, 否则返回AV_ERR_FAIL。
     @remark 没有注册对应类型的callback无法设置音量。
     */
    virtual int GetAudioDataDBVolume(AudioDataSourceType src_type, int* volume) = 0;

    virtual int GetAudioCategory(int* currentAudioCategory) = 0;

};

} // namespace av
} // namespace tencent