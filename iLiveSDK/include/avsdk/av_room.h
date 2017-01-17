#ifndef AV_ROOM_H_
#define AV_ROOM_H_

#include "av_common.h"
#include "av_endpoint.h"

namespace tencent {
namespace av {

/// 音视频通话的通话能力权限位。
#define AUTH_BITS_DEFAULT           0xFFFFFFFFFFFFFFFFUL ///< 所有权限。
#define AUTH_BITS_CREATE_ROOM       0x00000001 ///< 创建房间权限。
#define AUTH_BITS_JOIN_ROOM         0x00000002 ///< 加入房间的权限。
#define AUTH_BITS_SEND_AUDIO        0x00000004 ///< 发送音频的权限。
#define AUTH_BITS_RECV_AUDIO        0x00000008 ///< 接收音频的权限。
#define AUTH_BITS_SEND_CAMERA_VIDEO 0x00000010 ///< 发送摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)的权限。
#define AUTH_BITS_RECV_CAMERA_VIDEO 0x00000020 ///< 接收摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)的权限。
#define AUTH_BITS_SEND_SCREEN_VIDEO 0x00000040 ///< 发送屏幕视频(也就是捕获计算机屏幕画面所得到的视频)的权限。
#define AUTH_BITS_RECV_SCREEN_VIDEO 0x00000080 ///< 接收屏幕视频(也就是捕获计算机屏幕画面所得到的视频)的权限。

/**
@brief 音视频通话房间基类。

@details 音视频通话房间基类。要进行音视频通话，必须先创建并进入一个房间，然后才可进行发送和接收音视频数据，以进行音视频通话。
*/
class AV_EXPORT AVRoom {
  DISALLOW_EVIL_DESTRUCTIONS(AVRoom)
 public:
  /// 房间类型。
  enum RoomType {
    ROOM_TYPE_NONE = 0, ///< 无。
    ROOM_TYPE_PAIR = 1, ///< 双人房间。暂不支持。可以用多人房间来模拟双人通话，也就是创建一个多人房间，然后通话双方都进入房间就可以进行双人通话。
    ROOM_TYPE_MULTI = 2, ///< 多人房间。
  };

  /// 通话模式。
  enum Mode {
    MODE_AUDIO = 0, ///< 音频模式，只可收发音频的通话模式。如整个音视频通话过程中，自始至终都只允许收发音频，则可设置为这种模式。
    MODE_VIDEO = 1, ///< 视频模式，可收发音频亦可同时收发视频的通话模式。如整个音视频通话过程中，可收发音频，亦可收发视频，则可设置为这种模式。
  };

  /// 音频场景策略。
  enum AudioCategory {
    AUDIO_CATEGORY_VOICECHAT = 0, ///< VoIP模式。适合于实时音频通信场景，如实时语音通话。
    AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD = 1, ///< 媒体采集与播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的主播人员。
    AUDIO_CATEGORY_MEDIA_PLAYBACK = 2, ///< 媒体播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的听众。
  };

  /// 成员事件id。
  enum EndpointEventId {
    EVENT_ID_NONE = 0, ///< 无。
    EVENT_ID_ENDPOINT_ENTER = 1, ///< 进入房间事件。
    EVENT_ID_ENDPOINT_EXIT = 2, ///< 退出房间事件。
    EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO = 3, ///< 有发摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)事件。
    EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO = 4, ///< 无发摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)事件。
    EVENT_ID_ENDPOINT_HAS_AUDIO = 5, ///< 有发音频事件。
    EVENT_ID_ENDPOINT_NO_AUDIO = 6, ///< 无发音频事件。
    EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO = 7, ///< 有发屏幕视频(也就是捕获计算机屏幕画面所得到的视频)事件。
    EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO = 8, ///< 无发屏幕视频(也就是捕获计算机屏幕画面所得到的视频)事件。
  };

  /// 视频接收模式。
  enum VideoRecvMode {
    VIDEO_RECV_MODE_MANUAL = 0, ///< 手动模式。也就是需要业务侧调用请求画面"RequestView"接口来请求接收视频。
    VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO = 1, ///< 半自动模式，只针对摄像头视频。也就是当进入房间时，如果已经有人发送了视频，则会自动接收这些视频，不用手动去请求。当然，进入房间后，如何其他人再发送的视频，则不会自动接收。
  };

  /// 房间委托基类。业务侧需要实现该基类来处理房间异步操作返回的结果。
  struct Delegate {
    virtual ~Delegate() {}
    /**
    @brief 返回AVContext::EnterRoom()的异步操作结果的函数。

    @details 此函数用来返回AVContext::EnterRoom()的异步操作结果。

    @param ret_code 返回码。SDK的各种返回码的定义和其他详细说明参考av_error.h。
    */
    virtual void OnEnterRoomComplete(int32 ret_code) = 0;

    /**
    @brief 返回AVContext::ExitRoom()的异步操作结果的函数。

    @details 此函数用来返回AVContext::ExitRoom()的异步操作结果。

    @param ret_code 返回码。SDK的各种返回码的定义和其他详细说明参考av_error.h。
    */
    virtual void OnExitRoomComplete(int32 ret_code) = 0;

    /**
    @brief 房间成员状态变化通知的函数。

    @details 当房间成员发生状态变化(如是否发音频、是否发视频等)时，会通过该函数通知业务侧。

    @param event_id 状态变化id，详见EndpointEventId的定义。
    @param identifier_list 发生状态变化的成员id列表。
    */
    virtual void OnEndpointsUpdateInfo(EndpointEventId event_id, std::vector<std::string> identifier_list) = 0;

    /**
    @brief 房间成员无某个通话能力权限却去使用相关通话能力而导致的异常通知的函数。

    @details 当房间成员使用某个通话能力(如发送视频)且这时并没有这个通话能力权限，就会通过这个函数通知业务侧。

    @param privilege 当前SDK侧所记录的该房间成员的通话能力权限值。

    */
    virtual void OnPrivilegeDiffNotify(int32 privilege) = 0;

    /**
      @brief 半自动模式接收摄像头视频的事件通知。

      @details 半自动模式接收摄像头视频的事件通知。也就是当进入房间时，如果已经有人发送了视频，则会自动接收这些视频，不用手动去请求。当然，进入房间后，如何其他人再发送的视频，则不会自动接收。

      @param identifier_list 自动接收的摄像头视频所对应的成员id列表。
      */
    virtual void OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list) = 0;
  };

  /// 调用AVContext::EnterRoom()进入房间时所需传入的参数。
  struct EnterRoomParam {
    RoomType room_type; ///< 房间类型，详见RoomType的定义。
  };

  /// 房间信息。
  struct Info {
    Info()
      : room_type(ROOM_TYPE_NONE)
      , room_id(0)
      , relation_type(RELATION_TYPE_OPENSDK)
      , relation_id(0)
      , mode(MODE_AUDIO)
      , auth_bits(AUTH_BITS_DEFAULT)
      , audio_category(AUDIO_CATEGORY_VOICECHAT)
      , video_recv_mode(VIDEO_RECV_MODE_MANUAL) {
    }

    virtual ~Info() {}

    RoomType room_type; ///< 房间类型，详见RoomType的定义。
    uint64 room_id; ///< SDK侧的房间id，也就是由SDK侧创建并维护的房间id，区别于业务侧的房间id。
    RelationType relation_type; ///< 关系类型，多人房间专用。业务侧开发人员在接入SDK时，固定将该参数设置为6即可。
    uint32 relation_id; ///< 业务侧的房间id，也就是由业务侧创建并维护的房间id，区别于SDK侧的房间id，多人房间专用。该id可以是业务侧的讨论组号、群号、座位号等一切用于区分每个音视频通话的id。
    std::string peer_identifier; ///< 对方成员id，双人房间专用。
    Mode mode; ///< 通话模式，双人房间专用，详见Mode的定义。
    uint64 auth_bits; ///< 通话能力权限位，多人房间专用。
    std::string auth_buffer; ///通话能力权限位的加密串，多人房间专用。
    AudioCategory audio_category; ///< 音频场景策略，多人房间专用。
    std::string av_control_role; ///< 角色名，多人房间专用。该角色名就是web端音视频参数配置工具所设置的角色名。
    VideoRecvMode video_recv_mode; ///< 视频接收模式。详见VideoRecvMode的定义。
  };

  /**
  @brief 获取房间信息。

  @return 返回房间信息，详见Info的定义。
  */
  virtual const Info* GetRoomInfo() = 0;

  /**
  @brief 获取SDK侧的房间id。

  @return 返回SDK侧的房间id，详见Info.room_id的定义。
  */
  virtual uint64 GetRoomId() = 0;

  /**
  @brief 获取房间类型。

  @return 返回房间类型，详见Info.room_type的定义。
  */
  virtual RoomType GetRoomType() = 0;

  /**
  @brief 获取音视频通话的实时通话质量的相关信息。该函数主要用来查看实时通话质量、排查问题等，业务侧可以不用关心它。

  @return 返回音视频通话的实时通话质量的相关参数，并以字符串形式返回。
  */
  virtual std::string GetQualityTips() = 0;

  /**
  @brief 获取音视频通话的实时通话质量的相关信息。该函数主要用来查看实时通话质量、排查问题等，业务侧可以用其来做些提高用户体验的功能，如提示网络差，通话质量也较差。

  @param param 音视频通话的实时通话质量的相关参数。
  @return 返回值为true时代表获取成功，否则代表获取失败。
  */
  virtual bool GetQualityParam(RoomStatParam* param) = 0;
    
#ifndef WIN32
    
  /**
  @brief 获取音视频无参考评估分数。
     
  @param qualityEva 音视频无参考评估分数。
  @return 返回值为true时代表获取成功，否则代表获取失败。
  */

  virtual bool GetStatisticsParam(StatisticsParam& param) = 0;
#endif

  /**
  @brief 设置当前网络类型。
  @remark 建议网络有变更时，就设置网络类型，以让SDK侧能够根据网络类型更佳地智能调优音视频通话质量。
  */
  virtual void SetNetType(NetStateType type) = 0;

#ifdef WIN32
  /**
  @brief 同时请求一个或多个成员的视频画面。

  @details 同时请求一个或多个成员的视频画面。同一时刻只能请求一次成员的画面，并且必须等待异步结果返回后，才能进行新的请求画面操作。

  @param [in] identifier_list 成员id列表。
  @param [in] view_list 视频画面参数列表。
  @param [in] complete_callback 该操作的回调函数。
  @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

  @return AV_OK表示调用成功；AV_ERR_BUSY表示上一次操作(包括RequestViewList和CancelAllView)还在进行中；AV_ERR_FAILED表示操作失败，可能是因为所请求的成员当前已经没有对应视频源的视频、所请求成员已经退出房间等。

  @remark
      . 画面大小可以根据业务层实际需要及硬件能力决定。
      . 如果是手机，建议只有其中一路是大画面，其他都是小画面，这样硬件更容易扛得住，同时减少流量。
      . 这边把320×240及以上大小的画面认为是大画面；反之，认为是小画面。
      . 实际上请求到的画面大小，由发送方决定。如A传的画面是小画面，即使这边即使想请求它的大画面，也只能请求到的小画面。
      . 发送方传的画面大小，是否同时有大画面和小画面，由其所设置的编解码参数、场景、硬件、网络等因素决定。
      . RequestViewList和CancelAllView不能并发执行，即同一时刻只能进行一种操作。
      . identifier_list和view_list的元素个数必须等于count，同时每个元素是一一对应的。
    . 在请求画面前最好先检查该成员是否有对应的视频源。
  */
  virtual int32 RequestViewList(const std::vector<std::string> identifier_list, const std::vector<View> view_list,
                                AVEndpoint::RequestViewListCompleteCallback complete_callback, void* custom_data) = 0;

  /**
  @brief 取消所有请求的视频画面。

  @details 取消所有请求的视频画面。

  @param [in] complete_callback 该操作的回调函数。
  @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

  @return AV_OK表示调用成功；AV_ERR_BUSY表示上一次操作(包括RequestViewList和CancelAllView)还在进行中；AV_ERR_FAILED表示操作失败。

  @remark
      . RequestViewList和CancelAllView不能并发执行，即同一时刻只能进行一种操作。
  */
  virtual int32 CancelAllView(AVEndpoint::CancelAllViewCompleteCallback complete_callback, void* custom_data) = 0;
#endif
};

} // namespace av
} // namespace tencent

#endif // #ifndef AV_ROOM_H_