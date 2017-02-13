#pragma once

#include "build_config.h"
#include "basictypes.h"
#include "av_error.h"
#include "av_export.h"
#include <string>
#include <vector>

namespace tencent {
namespace av {

//////////////////////////////////////////////////////////////////////////
//
// 通用的，未分类的由此开始

/**
@brief 参数类型为void*的通用回调函数。

@details 此函数是和异步操作一起使用的回调函数，用来异步返回执行结果。

@param custom_data 值等于调用异步操作时的入参custom_data。

@todo 补充一下相关接口。
*/
typedef void (*AVClosure)(void* custom_data);


//////////////////////////////////////////////////////////////////////////
//
// AVContext相关的由此开始



//////////////////////////////////////////////////////////////////////////
//
// AVRoom相关的由此开始

/// 音频场景策略。
enum AudioCategory {
    AUDIO_CATEGORY_VOICECHAT = 0, ///< VoIP模式。适合于实时音频通信场景，如实时语音通话。
    AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD = 1, ///< 媒体采集与播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的主播人员。
    AUDIO_CATEGORY_MEDIA_PLAYBACK = 2, ///< 媒体播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的听众。
};

/// 视频接收模式。
enum VideoRecvMode {
    VIDEO_RECV_MODE_MANUAL = 0, ///< 手动模式。也就是需要业务侧调用请求画面"RequestView"接口来请求接收视频。
    VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO = 1, ///< 半自动模式，只针对摄像头视频。也就是当进入房间时，如果已经有人发送了视频，则会自动接收，不用手动去请求。当然，进入房间后，如何其他人再发送，则不会自动接收。
    VIDEO_RECV_MODE_UNKNOWN = 256,
};

/// 屏幕分享接收模式。
enum ScreenRecvMode {
    SCREEN_RECV_MODE_MANUAL = 0, ///< 手动模式。也就是需要业务侧调用请求画面"RequestView"接口来请求接收视频。
    SCREEN_RECV_MODE_SEMI_AUTO_RECV_SCREEN_VIDEO = 1, ///< 半自动模式，只针对屏幕分享。也就是当进入房间时，如果已经有人发送了屏幕分享，则会自动接收，不用手动去请求。当然，进入房间后，如何其他人再发送，则不会自动接收。
    SCREEN_RECV_MODE_UNKNOWN = 256,
};

//////////////////////////////////////////////////////////////////////////
//
// 音频相关的由此开始

/**
@brief 音频源类型。

@details 音频源类型，预留。
*/
enum AudioSrcType {
    AUDIO_SRC_TYPE_NONE = 0, ///< 默认值，无意义。
    //AUDIO_SRC_TYPE_MIC = 1, ///< 麦克风。
    //AUDIO_SRC_TYPE_ACCOMPANY = 2, ///< 伴奏。
    //AUDIO_SRC_TYPE_MIX_INPUT = 3, ///< 混音输入。
    //AUDIO_SRC_TYPE_MIX_OUTPUT = 4, ///< 混音输出。
};

/**
@brief 音频数据帧格式。

@details 音频数据帧格式。
*/
struct AudioFrameDesc {
    AudioFrameDesc()
        : sample_rate(0)
        , channel_num(0)
        , bits(0)
        , src_type(AUDIO_SRC_TYPE_NONE) {}

    uint32 sample_rate; ///< 采样率，单位：赫兹（Hz）。
    uint32 channel_num; ///< 通道数，1表示单声道（mono），2表示立体声（stereo）。
    uint32 bits; ///< 音频数据位宽。SDK1.6版本暂固定为16。
    int32 src_type; ///< 音频源类型。
};

/**
@brief 音频数据帧。

@details 音频数据帧。
*/
struct AudioFrame {
    AudioFrame()
        : data_size(0)
        , data(NULL)
        , time_stamp(0) {}

    std::string identifier; ///< 音频帧所属的房间成员id。
    AudioFrameDesc desc;  ///< 音频帧描述。
    uint32 data_size; ///< 音频帧的数据缓冲区大小，单位：字节。
    uint8* data; ///< 音频帧的数据缓冲区，SDK内部会管理缓冲区的分配和释放。
    uint64 time_stamp; ///< 音频帧的时间戳，SDK内部会自动填写好，utc时间，0为无效值。
};


//////////////////////////////////////////////////////////////////////////
//
// 视频相关的由此开始

/**
@brief 色彩格式。

@details 色彩格式。
*/
enum ColorFormat {
    COLOR_FORMAT_NONE = -1, ///< 无意义
    COLOR_FORMAT_I420 = 0, ///< i420格式
    COLOR_FORMAT_NV21 = 1,
    //COLOR_FORMAT_YV12 = 2,
    COLOR_FORMAT_NV12 = 3,
    //COLOR_FORMAT_UYVY = 4,
    //COLOR_FORMAT_YUYV = 5,
    //COLOR_FORMAT_YUY2 = 6,
    COLOR_FORMAT_RGB16 = 7,
    COLOR_FORMAT_RGB24 = 8, ///< rgb24格式
    COLOR_FORMAT_RGB32 = 9,
};


enum ExternalFormat {
    RAWIMAGE_FORMAT_NV12    = 18,
    RAWIMAGE_FORMAT_NV21    = 17,
    RAWIMAGE_FORMAT_NV16    = 16,
    RAWIMAGE_FORMAT_YUYV    = 20,
    RAWIMAGE_FORMAT_I420    = 100,
    RAWIMAGE_FORMAT_YUV420  = 100,
    RAWIMAGE_FORMAT_YVYU    = 101,
    RAWIMAGE_FORMAT_UYVY    = 102,
    RAWIMAGE_FORMAT_VYUY    = 103,
    RAWIMAGE_FORMAT_RGB565  = 4,
    RAWIMAGE_FORMAT_RGB24   = 110,
    RAWIMAGE_FORMAT_RGB32   = 111,
};

/**
@brief 视频源类型。

@details 视频源类型。
*/
enum VideoSrcType {
    VIDEO_SRC_TYPE_NONE = 0, ///< 默认值，无意义。
    VIDEO_SRC_TYPE_CAMERA = 1, ///< 摄像头。
    VIDEO_SRC_TYPE_SCREEN = 2, ///< 屏幕。
    VIDEO_SRC_TYPE_MEDIA = 3, ///< 播片。
};


/**
@brief 画面大小。

@details 画面大小, 这里仅代表从服务器接收的画面最大分辨率，实际运行过程中受视频上行方约束。
*/
enum ViewSizeType {
    VIEW_SIZE_TYPE_SMALL = 0, ///< 小画面，分辨率包含192x144、160x120。
    VIEW_SIZE_TYPE_BIG = 1, ///< 大画面，分辨率包含320x240、480x360、640x480、800x600、720P、1080P。
};

/**
@brief 视频画面参数。

@details 视频画面参数。
*/
typedef struct View {
    View()
        : video_src_type(VIDEO_SRC_TYPE_CAMERA),
          size_type(VIEW_SIZE_TYPE_BIG) {
    }

    VideoSrcType video_src_type; ///< 视频源类型，详情见VideoSrcType的定义。
    ViewSizeType size_type; ///< 画面大小，详情见ViewSizeType的定义。
} View;

/**
@brief 视频帧描述。

@details 视频帧描述。
@todo rotate使用枚举类型。
@todo src_type使用枚举类型。
*/
struct VideoFrameDesc {
    VideoFrameDesc()
        : color_format(COLOR_FORMAT_RGB24)
        , width(0)
        , height(0)
        , externalData(false)
        , rotate(0)
        , src_type(VIDEO_SRC_TYPE_CAMERA) {}

    ColorFormat color_format; ///< 色彩格式，详情见ColorFormat的定义。
    uint32 width; ///< 宽度，单位：像素。
    uint32 height; ///< 高度，单位：像素。
    bool externalData;///< 数据是否来自外部摄像头。

    /**
    画面旋转的角度：
    - source_type为VIDEO_SRC_TYPE_CAMERA时，表示视频源为摄像头。
      在终端上，摄像头画面是支持旋转的，App需要根据旋转角度调整渲染层的处理，以保证画面的正常显示。
    - source_type为其他值时，rotate恒为0。
    */
    int32 rotate;

    VideoSrcType src_type; ///< 视频源类型，详情见VideoSrcType的定义。
};

/**
@brief 视频帧。

@details 视频帧。
*/
struct VideoFrame {
    VideoFrame()
        : data_size(0)
        , data(NULL)
        , time_stamp(0) {}

    std::string identifier; ///< 视频帧所属的房间成员id。
    VideoFrameDesc desc; ///< 视频帧描述。
    uint32 data_size; ///< 视频帧的数据缓冲区大小，单位：字节。
    uint8* data; ///< 视频帧的数据缓冲区，SDK内部会管理缓冲区的分配和释放。
    uint64 time_stamp; ///< 视频帧的时间戳，SDK内部会自动填写好，utc时间，0为无效值。
};

/**
@brief 视频帧。

@details 视频帧。
*/
struct VideoBit {
    VideoBit()
        : data_size(0)
        , data(NULL) {}

    uint32 data_size; ///< 视频帧的数据缓冲区大小，单位：字节。
    uint8* data; ///< 视频帧的数据缓冲区，SDK内部会管理缓冲区的分配和释放。

};

/**
@brief 网络连接类型。

@details 网络连接类型。
*/
enum NetStateType {
    NETTYPE_E_NONE  = 0, ///< 无连接.
    NETTYPE_E_LINE  = 1, ///< LINE
    NETTYPE_E_WIFI  = 2, ///< WIFI
    NETTYPE_E_3G    = 3, ///< 3G
    NETTYPE_E_2G    = 4, ///< 2G
    NETTYPE_E_4G    = 5, ///< 4G
};

/**
@brief 硬件检测类型。

@details 硬件检测类型。
*/
typedef enum {
    Detect_Speaker   = 0,  ///< 检测到扬声器
    Detect_Mic, ///< 检测到麦克风
    Detect_Camera,
} DetectedDeviceType;

/**
@brief 硬件检测信息。

@details 硬件检测信息。
*/
typedef struct {
    DetectedDeviceType flow; ///< 硬件检测类型
    std::string strName; ///< 设备名称。
    std::string strGuid; ///< 设备GUID。
    bool isUsedDevice;   ///< 仅对拔出设备时有效，代表拔出的是使用中的设备。
    bool isNewDevice;    ///< true: 新启用设备，false: 拔出或禁用设备。
} DetectedDeviceInfo;

    
/// Room基本信息
struct BaseInfoStatParam{
    
    char* sdk_version;
    uint16 exeCpuRate;		///< 应用CPU使用率×10000(例如：3456对应于34.56%)
    uint16 sysCpuRate;		///< 系统CPU使用率×10000(例如：3456对应于34.56%)
};

/// 网络运行时参数。
struct NetworkStatParam {
    uint32 kbps_send;       ///< 发包速率,单位kbps
    uint16 loss_rate_send;  ///< 上行丢包率，从Hello的回包中获得
    uint16 loss_rate_send_udt; ///< udt后上行丢包率
    uint32 packet_send;     ///< 发包速率,每秒发包的个数
    uint16 loss_model_send; ///< 上行平均连续丢包个数，从Hello的回包中获得
    
    uint32 kbps_recv;       ///< 收包速率,单位kbps
    uint16 loss_rate_recv_udt; ///< udt后下行丢包率
    uint16 loss_rate_recv;  ///< 下行丢包率
    uint32 packet_recv;     ///< 收包速率,每秒收包的个数
    uint32 unsend_udt;      ///< udt未发送包数
    uint32 interface_ip;    ///< 接口机ip
    uint16 interface_port;  ///< 与接口机连接的端口
    uint32 client_ip;          ///< 客户端ip
    bool isTcp;              ///< 是否为tcp
    uint16 loss_model_recv; ///< 下行平均连续丢包个数
    
    uint16 cpu_rate_app;    ///< App进程的CPU使用率×10000(例如：3456对应于34.56%)
    uint16 cpu_rate_sys;    ///< 当前系统的CPU使用率×10000(例如：3456对应于34.56%)
    uint32 rtt;             ///< 往返时延（Round-Trip Time），单位毫秒，统计方法：Hello SendData 的时候记一个 TickCount，Hello Reply 的时候记一个 TickCount，两者的差值为时延
    
    
    
};


/// 视频采集参数。
struct VideoCaptureParam {
    uint32 width;    ///< 视频宽
    uint32 height;   ///< 视频高
    uint32 fps;      ///< 帧率
};

/// 视频编码参数。
struct VideoEncodeParam {
    /**
     画面类型，作为编码信息索引：
     - 0：主路大画面
     - 1: 主路小画面
     - 2: 辅路
     */
    uint32 view_type;
    uint32 width;           ///< 视频编码宽
    uint32 height;          ///< 视频编码高
    uint32 fps;             ///< 视频编码实时帧率×10
    uint32 bitrate;         ///< 视频编码码率(无包头)
    uint32 angle;           ///< 角度
    uint32 encode_type;     ///< 视频编码类型
    uint32 hw;              ///< 是否开硬件编码
};

/// 视频解码参数。
struct VideoDecodeParam {
    uint64 tiny_id;     ///< 解码用户
    /**
     画面类型，作为编码信息索引：
     - 0：主路大画面
     - 1: 主路小画面
     - 2: 辅路
     */
    uint32 view_type;
    uint32 width;   ///< 视频解码宽
    uint32 height;  ///< 视频解码高
    uint32 fps;     ///< 视频解码出的帧率×10
    uint32 bitrate; ///< 视频解码出的码率(无包头)
    uint32 hw;      ///< 是否开启硬编解
    uint32 codec_type;///< 解码类型
    uint32 hwdec_delay; //解码延迟
};

/// 视频流控下发参数。
struct VideoQosParam {
    uint32 width;    ///<视频宽
    uint32 height;   ///<视频高
    uint32 fps;      ///<帧率
    uint32 bitrate;  ///<码率
    uint32 encode_type; ///<视频流控下发参数编码类型
    uint32 min_qp;      ///<视频流控下发最小质量
    uint32 max_qp;      ///<视频流控下发最大质量
    uint32 fectype;     ///<视频流控下发参数fec类型
    uint32 i_fec_precent;   ///<视频流控下发i帧fec
    uint32 sp_fec_precent;  ///<视频流控下发sp帧fec
    uint32 p_fec_precent;   ///<视频流控下发p帧fec
    uint32 i_mtu;           ///<视频流控下发参数I帧mtu
    uint32 sp_mtu;          ///<视频流控下发参数sp帧mtu
    uint32 p_mtu;           ///<视频流控下发参数p帧mtu
    uint32 i_fec_min_pkg;   ///<视频流控下发参数i帧最小包
    uint32 sp_fec_min_pkg;  ///<视频流控下发参数sp帧最小包
    uint32 p_fec_min_pkg;   ///<视频流控下发参数p帧最小包
    uint32 i_fec_min_size;  ///<视频流控下发参数i帧最小包大小
    uint32 sp_fec_min_size; ///<视频流控下发参数sp帧最小包大小
    uint32 p_fec_min_size;  ///<视频流控下发参数p帧最小包大小
    uint32 gop_type;        ///<视频流控下发参数gop类型
    uint32 gop;             ///<视频流控下发参数gop
    uint32 enc_mode;        ///<视频流控下发编码模式
    uint32 hw;              ///< 0:不启用硬件加速；1:启用硬件加速
};

struct VideoSendParam{
    uint32 loss_rate;       ///< 视频发送参数丢包率
    uint32 i_fec;           ///< 视频发送参数I帧fec
    uint32 sp_fec;          ///< 视频发送参数sp帧
    uint32 pkt;             ///< 视频发送包数
    uint32 STnSB_Gain_Loss_12s;//人为补零 //人为丢包
    uint32 STnSB_DecLost_MaxConcal_12s;  //解码端统计的丢包 //jitter中统计的EOS、大于一定数量的连续丢包
    uint32 STnSB_Break_SmallBreak_ContiPlc_12s;//卡顿次数 //可能的小卡顿次数 //连续plc
};

struct VideoRecvParam{
    float loss_rate;        ///< 视频接收丢包率
    uint32 dwJitter_R;      ///< 视频接收抖动
    uint32 dwBR_R;          ///< 视频接收码率
};
/// 视频相关的状态参数。
struct VideoStatParam {
    
    VideoStatParam()
    :encode_params(NULL),
    decode_params(NULL),
    recv_param(NULL),
    is_anchor(false)
    {}
    VideoCaptureParam capture_param;    ///< 视频采集参数
    VideoEncodeParam* encode_params;    ///< 视频编码参数
    uint32 encode_count;                ///< 视频编码路数
    VideoSendParam send_param;          ///< 视频发送参数
    
    VideoDecodeParam* decode_params;    ///< 视频解码参数
    uint32 decode_count;                ///< 视频解码路数
    VideoRecvParam* recv_param;         ///< 视频接收参数
    bool is_anchor;                   ///< 是否为主播(只要有视频上行就认为是主播)
    VideoQosParam qos_param_big;        ///< 大画面的视频流控下发参数
    VideoQosParam qos_param_small;      ///< 小画面的视频流控下发参数
    VideoQosParam qos_param_sub_big;        ///< 辅路大画面的视频流控下发参数
    VideoQosParam qos_param_sub_small;        ///< 辅路大画面的视频流控下发参数
    ~VideoStatParam(){
        if(encode_params){
            delete [] encode_params;
            encode_params = NULL;
        }
        if(decode_params){
            delete [] decode_params;
            decode_params = NULL;
        }
        if(recv_param){
            delete [] recv_param;
            recv_param = NULL;
        }
    }
};



/// 音频流控下发参数。
struct AudioQosParam {
    uint32 sample_rate;             ///< 采样率
    uint32 channel_count;           ///< 通道数，1表示单声道（mono），2表示立体声（stereo）
    uint32 codec_type;              ///< 编码类型
    uint32 bitrate;                 ///< 码率
    uint8 aec_enable;               ///< AEC功能是否开启
    uint8 agc_enable;               ///< AGC功能是否开启
    uint32 fec;                     ///< 音频流控下发fec
    uint32 vad;                     ///< 音频流控下发vad
    uint32 pack_duration;           ///< 音频流控下发pack
    uint32 recn;                    ///< 音频流控下发recn
    uint32 recm;                    ///< 音频流控下发recm
    uint32 audio_mtu;               ///< 音频流控下发mtu
    uint32 jitter_min_delay;        ///< Jitter的最小延时，单位毫秒
    uint32 jitter_min_max_delay;    ///< Jitter最大延时的最小阀值
    uint32 jitter_max_max_delay;    ///< Jitter最大延时的最大阀值
    uint32 jitter_drop_scale;       ///< Jitter最大延时的损失比例，百分比eg:10%-->10,50%-->50
    
};

struct AudioCaptureParam{
    uint32 sample_rate;             ///< 采样率
    uint32 channel_count;           ///< 通道数，1表示单声道（mono），2表示立体声（stereo）
};

struct AudioEncodeParam{
	AudioEncodeParam()
		:encode_bitrate(0),
		encode_type(0),
		vad(0){}
    uint32 encode_type;              ///< 音频编码类型
    uint32 encode_bitrate;           ///< 音频编码码率
    uint32 vad;                      ///< 音频编码vad参数
};

struct AudioSendParam{
    uint32 loss_rate;               ///< 音频发送丢包率
    uint32 FEC;                     ///< 音频发送FEC
    uint32 jitter;                  ///< 音频发送抖动
    uint32 send_br;                 ///< 音频发送发送码率
    uint32 send_br_udt;             ///< 音频发送发送码率udt
};

struct AudioDecodeParam{
    uint32 decode_type;             ///< 音频解码类型
    uint32 sample_rate;             ///< 音频编码采样率
    uint32 channel_count;           ///< 通道数，1表示单声道（mono），2表示立体声（stereo）
    uint64 tiny_id;                 ///< 音频解码用户
};

struct AudioRecvParam{
    uint32 play_delay;              ///< 音频接收播放时延
    uint32 loss_rate;               ///< 音频接收丢包率
};

/// 音频运行时参数。
struct AudioStatParam {
    AudioStatParam()
    :decode_count(0)
    {
        decode_param.clear();
    }
    AudioCaptureParam capture_param;            ///<音频采集信息
    AudioEncodeParam encode_param;              ///<音频编码信息
    AudioSendParam  send_param;                 ///<音频发送信息
    std::vector<AudioDecodeParam>decode_param;  ///<音频解码信息
    uint32 decode_count;                        ///<音频解码路数
    AudioRecvParam recv_param;                  ///<音频接收信息
    AudioQosParam qos_param;                    ///<音频流控下发
    uint32 audio_category;                      ///<音频场景
};

/**
 @brief 音视频房间相关的统计参数。
 
 @details 进入音视频房间之后，App可以通过AVRoom::GetQualityParam()获得。
 */
struct RoomStatParam {
    uint64 tick_count_begin;    ///< 统计开始时时间点，使用本地TickCount
    uint64 tick_count_end;      ///< 统计结束的时间点，使用本地TickCount
    BaseInfoStatParam  baseinfo_param;  ///< SDK基本信息参数
    NetworkStatParam network_param; ///< 网络层相关的统计参数
    VideoStatParam video_param;   ///< 视频相关的统计参数
    AudioStatParam audio_param;   ///< 音频相关的统计参数
};
#ifndef WIN32
/**
 @brief 音视频无参考评估分数。
 
 @details 进入音视频房间之后，App可以通过AVRoom::GetStatisticParam()获得。
 */

struct AudioQualityEva {
    uint32 AudioQualityEva1;
    uint32 AudioQualityEva2;
    uint32 AudioQualityEva3;
    uint32 AudioQualityEva4;
    uint32 AudioQualityEva5;
    uint32 AudioQualityEva6;

    uint32 AvgAudioQualityEva;
};

struct VideoQualityEva {
    uint32 VideoQualityEva1;
    uint32 VideoQualityEva2;
    uint32 VideoQualityEva3;
    uint32 VideoQualityEva4;
    uint32 VideoQualityEva5;
    uint32 VideoQualityEva6;

    uint32 AvgVideoQualityEva;
};


struct StatisticsParam {

    AudioQualityEva audioeva;
    VideoQualityEva videoeva;

    uint32 FirstVFWaitByAutoPush;
    uint32 FirstVFWaitByReqView;
};
#endif
// Room AV state enumeration.
/**
@brief 房间音视频态。

@details 进入音视频房间之后，App可以通过AVRoom::ChangeAVState()设置。
*/
enum RoomAVState {
    ROOM_AV_STATE_NONE        = 0, // 初始值，没有意义
    ROOM_AV_STATE_ENTER_AUDIO = 1, // 进入群语音
    ROOM_AV_STATE_EXIT_AUDIO  = 2, // 退出群语音
    ROOM_AV_STATE_ENTER_VIDEO = 3, // 进入群视频并抢座
    ROOM_AV_STATE_EXIT_VIDEO  = 4, // 退出群视频
};

// Room AV state enumeration.
/**
@brief 房间辅路音视频态。

@details 进入音视频房间之后，App可以通过AVRoom::ChangeAVState()设置。
*/
enum RoomAVSubState {
    ROOM_AV_SUB_STATE_NONE        = 0, // 初始值，没有意义
    ROOM_AV_SUB_STATE_ENTER_VIDEO = 1, // 进入辅路视频
    ROOM_AV_SUB_STATE_EXIT_VIDEO  = 2, // 退出辅路视频
};

// Room AV state enumeration.
/**
@brief 事件定义。

@details 各种事件定义。
*/
enum RoomAVMainEventType {
    ROOM_AV_MAIN_EVENT_TYPE_NONE    = 0, // 初始值，没有意义
    ROOM_AV_MAIN_EVENT_TYPE_NETWORK = 1, //网络事件
    ROOM_AV_MAIN_EVENT_TYPE_TIME_CONSUMEINFO = 100, //耗时细分
};
/**
@brief 事件定义。

@details 各种事件定义。
*/
enum RoomAVSubNetworkEventType {
    ROOM_AV_SUB_NETWORK_EVENT_TYPE_NONE    = 0, // 初始值，没有意义
    ROOM_AV_SUB_NETWORK_EVENT_TYPE_TIMEOUT = 1, //网络事件
};

/**
@brief 事件定义。

@details 各种事件定义。
*/
enum RoomAVTimeConsumeEventType {
    ROOM_AV_SUB_TIMECONSUME_EVENT_TYPE_NONE    = 0, // 初始值，没有意义
    ROOM_AV_SUB_TIMECONSUME_EVENT_TYPE_ENTERROOM = 1, //进房耗时细分
};
/// 网络事件对象。
struct NetWorkInfo {
    uint32 ip;     /// ip地址
    uint32 port;   /// 端口
};

/// 进房时间、看首帧等信息细分对象。
struct TimeConsumeInfo {
    uint64 enterroom_start;
    uint64 enterroom_request_auth_key_and_int_svr_conn_info_start;
    uint64 enterroom_net_channel_send_app_cmd_start;
    uint64 enterroom_net_channel_send_app_cmd_end;
    uint64 enterroom_request_auth_key_and_int_svr_conn_info_end;
    uint64 enterroom_init_avsdk_core_start;
    uint64 enterroom_init_avsdk_core_end;
    uint64 enterroom_init_audio_device_start;
    uint64 enterroom_init_audio_device_end;
    uint64 enterroom_init_video_device_start;
    uint64 enterroom_init_video_device_end;
    uint64 enterroom_request_enter_room_start;
    uint64 enterroom_connect_start;
    uint64 enterroom_connect_end;
    uint64 enterroom_send_request_enter_room_cmd_start;
    uint64 enterroom_send_request_enter_room_cmd_end;
    uint64 enterroom_request_enter_room_end;
    uint64 enterroom_end;

    uint64 requestview_start;
    uint64 requestview_send_request_cmd_start;
    uint64 requestview_send_request_cmd_end;
    uint64 requestview_end;

    uint64 recvdata_start;//recv_first_pkg
    uint64 recvdata_recv_first_udt_pkg;
    uint64 recvdata_send_first_pkg_to_dec;
    uint64 recvdata_decode_first_frame_end;
    uint64 recvdata_discard_first_frame;
    uint64 recvdata_end;//send to render
};


} // namespace av
} // namespace tencent
