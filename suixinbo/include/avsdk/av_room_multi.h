#pragma once

#include "av_common.h"
#include "av_endpoint.h"

namespace tencent {
namespace av {

/// 音视频通话的通话能力权限位。
const uint64 AUTH_BITS_DEFAULT              = -1; ///< 所有权限。
const uint64 AUTH_BITS_CREATE_ROOM          = 0x00000001; ///< 创建房间权限。
const uint64 AUTH_BITS_JOIN_ROOM            = 0x00000002; ///< 加入房间的权限。
const uint64 AUTH_BITS_SEND_AUDIO           = 0x00000004; ///< 发送音频的权限。
const uint64 AUTH_BITS_RECV_AUDIO           = 0x00000008; ///< 接收音频的权限。
const uint64 AUTH_BITS_SEND_CAMERA_VIDEO    = 0x00000010; ///< 发送摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)的权限。
const uint64 AUTH_BITS_RECV_CAMERA_VIDEO    = 0x00000020; ///< 接收摄像头视频(也就是来至摄像头设备AVCameraDevice或外部视频捕获设备AVExternalCapture的视频)的权限。
const uint64 AUTH_BITS_SEND_SCREEN_VIDEO    = 0x00000040; ///< 发送屏幕视频(也就是捕获计算机屏幕画面所得到的视频)的权限。
const uint64 AUTH_BITS_RECV_SCREEN_VIDEO    = 0x00000080; ///< 接收屏幕视频(也就是捕获计算机屏幕画面所得到的视频)的权限。

/**
@brief 多人音视频房间类。
*/
class AVRoomMulti {
public:
    enum State {
        STATE_EXIT = 0,     ///< 初始状态，没有进入音视频房间之前，调用AVContext::ExitRoom()之后均为此状态。
        STATE_ENTER_ING,    ///< 正在进入房间，APP调用AVContext::EnterRoom()之后，房间状态会从STATE_EXIT切换到此状态。
        STATE_ENTER_OK,     ///< 已经进入房间，AVContext::EnterRoom()结束之后，房间状态会从STATE_ENTER_ING切换到此状态。
        STATE_EXIT_ING,
        STATE_SWITCH_ING,   ///< 正在切换房间，APP调用AVContext::SwitchRoom()之后，房间状态会从STATE_ENTER切换到此状态。
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
		EVENT_ID_ENDPOINT_HAS_MEDIA_VIDEO = 9, ///< 有播放视频事件。
		EVENT_ID_ENDPOINT_NO_MEDIA_VIDEO = 10, ///< 无播放视频事件。
    };

    /// 房间委托基类。业务侧需要实现该基类来处理房间异步操作返回的结果。
    struct Delegate {
        virtual ~Delegate() {}
        /**
        @brief 返回AVContext::EnterRoom()的异步操作结果的函数。

        @details 此函数用来返回AVContext::EnterRoom()的异步操作结果。

        @param ret_code 返回码。SDK的各种返回码的定义和其他详细说明参考av_error.h。
        */
        virtual void OnEnterRoomComplete(int32 result, const std::string& error_info) = 0;

        /**
        @brief 退出房间完成回调。

        @details APP调用ExitRoom()后，SDK通过此回调通知APP成功退出了房间。
        */
        virtual void OnExitRoomComplete() = 0;

        /**
        @brief SDK主动退出房间提示。

        @details 该回调方法表示SDK内部主动退出了房间。SDK内部会因为30s心跳包超时等原因主动退出房间，APP需要监听此退出房间事件并对该事件进行相应处理

        @param reason 退出房间的原因，具体值见返回码。SDK的各种返回码的定义和其他详细说明参考av_error.h。
        */
        virtual void OnRoomDisconnect(int32 reason, const std::string& error_info) = 0;


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

          @details 半自动模式接收摄像头视频的事件通知。也就是当进入房间时，如果已经有人发送了视频，则会自动接收，不用手动去请求。当然，进入房间后，如何其他人再发送，则不会自动接收。

          @param identifier_list 自动接收的摄像头视频所对应的成员id列表。
          */
        virtual void OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list) = 0;

        /**
          @brief 半自动模式接收屏幕分享的事件通知。

          @details 半自动模式接收屏幕分享的事件通知。也就是当进入房间时，如果已经有人发送了屏幕分享，则会自动接收，不用手动去请求。当然，进入房间后，如何其他人再发送，则不会自动接收。

          @param identifier_list 自动接收的屏幕分享所对应的成员id列表。
          */
        virtual void OnSemiAutoRecvScreenVideo(std::vector<std::string> identifier_list) = 0;

        /**
          @brief 半自动模式接收播片的事件通知。

          @details 半自动模式接收播片的事件通知。也就是当进入房间时，如果已经有人发送了播片，则会自动接收，不用手动去请求。当然，进入房间后，如何其他人再发送，则不会自动接收。

          @param identifier_list 自动接收的播片所对应的成员id列表。
          */
        virtual void OnSemiAutoRecvMediaFileVideo(std::vector<std::string> identifier_list) = 0;
        /**
             @brief 摄像头分辨率和帧率修改通知。

             @details 客户如果使用外部输入流的话（enableExternalCapture）需要根据此通知中的分辨率和帧率动态修改摄像头的分辨率和帧率。分辨率的设置优先选比通知中的分辨率同比高档次的分辨率，其次选高档次分辨率，如果以上两种分辨率都没，建议设置为640*480

             @param width 分辨率宽  height分辨率高  fps 帧率
             */
        virtual void OnCameraSettingNotify(int32 width, int32 height, int32 fps) = 0;

        /**
             @brief返回switchRoom()的异步操作结果的函数。<br/>
             @details APP使用switchRoom可以快速切换房间，在使用switchRoom之后可以通过这个回调拿到执行结果，APP需要根据结果进行相应处理.retCode要关注以下三个取值：AV_OK, AV_ERR_NOT_TRY_NEW_ROOM, AV_ERR_TRY_NEW_ROOM_FAILED.
             @param ret_code 返回码。AV_OK表示切换成功，需要APP侧将前一个房间的成员、以及视频相关内容清空;AV_ERR_NOT_TRY_NEW_ROOM表示切换中途停止而仍然留在原房间;AV_ERR_TRY_NEW_ROOM_FAILED表示原房间已退出，而新房间进入失败，APP侧要做退出房间的处理
         */

        virtual void OnSwitchRoomComplete(int32 result, const std::string& error_info) = 0;


#ifndef WIN32
        virtual void OnDisableAudioIssue() = 0;

        /**
             @brief 进房间的时间通知。

             @param event_type 主事件类型
             @param subevent_ype 子事件类型
             @param event_data 事件数据
             */
        virtual void OnRoomEvent(int event_type, int subevent_ype, void* event_data) = 0;

        /*!
             @brief      硬件状态事件通知
             @details	 用于通知硬件软件切换的状态
             @param      isEncoder		 编码还是解码选择
             @param      isMainVideo     主路辅路选择
             @param      isSwitchToSoft  是不是切换到软件选择
             @param      identifier      多路解码情况，编解码的identifier
             */
        virtual void OnHwStateChangeNotify(int32 isEncoder, int32 isMainVideo, int32 switchToSoft, std::string identifier) = 0;
#endif
    };

    /// 调用AVContext::EnterRoom()进入多人房间时所需传入的参数。
    struct EnterParam {
        EnterParam()
            : relation_id(0)
            , auth_bits(AUTH_BITS_DEFAULT)
            , audio_category(AUDIO_CATEGORY_VOICECHAT)
            , create_room(true)
            , video_recv_mode(VIDEO_RECV_MODE_MANUAL)
            , screen_recv_mode(SCREEN_RECV_MODE_MANUAL) {
        }

        int32 relation_id; ///< 业务侧的房间id，也就是由业务侧创建并维护的房间id，区别于SDK侧的房间id。该id可以是业务侧的讨论组号、群号、座位号等一切用于区分每个音视频通话的id。
        uint64 auth_bits; ///< 通话能力权限位。
        std::string auth_buffer; ///< 通话能力权限位的加密串。
        std::string control_role; ///< 角色名，web端音视频参数配置工具所设置的角色名。
        AudioCategory audio_category; ///< 音视场景策略。
        bool create_room; ///< 是否创建音视频房间。当房间不存在时，true会创建一个新的房间，false会返回进入房间失败。
        VideoRecvMode video_recv_mode; ///< 视频接收模式。详见VideoRecvMode的定义。
        ScreenRecvMode screen_recv_mode; ///< 屏幕分享接收模式。详见ScreenRecvMode的定义。
    };

    /**
    @brief 获取房间Id。

    @return 房间Id是由SDK分配的，APP调用enterRoom()方法成功进入房间之后，SDK会为当前房间分配一个Id值，互动直播的录制功能开发需要用到该值。
    */
    virtual uint32 GetRoomId() = 0;


    /**
    @brief 获取音视频通话的实时通话质量的相关信息。该函数主要用来查看实时通话质量、排查问题等，业务侧可以不用关心它。

    @return 返回音视频通话的实时通话质量的相关参数，并以字符串形式返回。
    */
    virtual std::string GetQualityTips() = 0;

    /**
    @brief 获取房间成员个数。

    @details 获取当前正在房间内的成员个数。

    @return 返回成员个数。
    */
    virtual int32 GetEndpointCount() = 0;

    /**
    @brief 获取房间成员对象列表。

    @details 获取当前正在房间内的成员对象列表。

    @param [out] endpoints 正在房间内的成员对象列表。

    @return 返回成员对象个数。0表示获取失败。

    @remark 所返回的成员对象的生命周期由SDK侧负责，业务侧不需要关心。最好业务侧不要一直持有它，可以在每次需要时去重新获取它即可。
    */
    virtual int32 GetEndpointList(AVEndpoint** endpoints[]) = 0;

    /**
    @brief 获取房间成员对象。

    @details 根据成员id获取成员对象。

    @param identifier 要获取的成员对象的成员id。

    @return 返回对应的成员对象。如果失败时则返回NULL。

    @remark 所返回的成员对象的生命周期由SDK侧负责，业务侧不需要关心。最好业务侧不要一直持有它，可以在每次需要时去重新获取它即可。
    */
    virtual AVEndpoint* GetEndpointById(const std::string& identifier) = 0;

    /**
    @brief 同时请求一个或多个成员的视频画面。

    @details 同时请求一个或多个成员的视频画面。同一时刻只能请求一次成员的画面，并且必须等待异步结果返回后，才能进行新的请求画面操作。

    @param [in] identifier_list 成员id列表。
    @param [in] view_list 视频画面参数列表。
    @param [in] complete_callback 该操作的回调函数。
    @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

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
    virtual void RequestViewList(const std::vector<std::string> identifier_list, const std::vector<View> view_list,
                                 AVEndpoint::RequestViewListCompleteCallback complete_callback, void* custom_data) = 0;

    /**
    @brief 取消所有请求的视频画面。

    @details 取消所有请求的视频画面。

    @param [in] complete_callback 该操作的回调函数。
    @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

    @return AV_OK表示调用成功；AV_ERR_BUSY表示上一次操作(包括RequestViewList和CancelAllView)还在进行中；AV_ERR_FAIL表示操作失败。

    @remark
        . RequestViewList和CancelAllView不能并发执行，即同一时刻只能进行一种操作。
    */
    virtual void CancelAllView(AVEndpoint::CancelAllViewCompleteCallback complete_callback, void* custom_data) = 0;


	/**
	 @abstract      开启/关闭音频数据白名单逻辑。
	 @param         identifierList为希望收到其音频数据的成员列表
	 @return        AV_OK 表示操作成功 <br/>
					AV_ERR_FAIL表示操作失败，可能是因为房间不存在,个别成员不在房间内或者转换tinyid失败等（这种情况下名单内若有成员id转换成功，仍然会被加入白名单且白名单生效）。
	 @warning       每次最多设置6个成员id，超过6个将添加vector最后6个到白名单，开启白名单时，若identifierList为空，则默认丢弃任所有音频数据；每次调用，白名单将被重置为新的成员列表，而不是累加。需要定制想接收的音频数据才需要调用，不调用则默认接收房间内所有音频数据
	 */

	virtual int32 RequestAudioList(const std::vector<std::string> identifier_list) = 0;

	/**
	@abstract      关闭音频数据白名单逻辑。
	@return        AV_OK 表示成功操作成功 <br/>
				   AV_ERR_FAIL表示操作失败，可能是因为房间不存在等。
	@warning       关闭白名单逻辑则主动接收房间内所有音频数据。
	*/
	virtual int32 CancelAudioList() = 0;

    /**
      @brief 修改通话能力权限操作的回调函数。

      @details 此函数用来返回AVRoomMulti::ChangeAuthority()的异步操作结果。

      @param [in] ret_code 返回码。AV_OK表示操作成功；AV_ERR_FAIL表示操作失败。

      @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。
    */

    typedef void(*ChangeCompleteCallback)(int32 result, const std::string& error_info, void* custom_data);

    /**
    @Deprecated
    @brief 修改通话能力权限。

    @details 修改通话能力权限。通话能力权限包括是否可以创建房间/进入房间/发送音频/接收音频/发送摄像头视频/接收摄像头视频/发送屏幕视频/接收屏幕视频等。

    @param [in] auth_bits 通话能力权限位。

    @param [in] auth_buffer 通话能力权限位的加密串。

    @param [in] callback 回调函数。

    @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

    @return 返回操作结果。
    */
    virtual void ChangeAuthority(uint64 auth_bits, const std::string& auth_buffer, ChangeCompleteCallback callback,
                                 void* custom_data) = 0;

    /**
      @brief 修改角色。

      @details 此前，角色被设定为在进入房间之前指定、进入房间之后不能动态修改。这个接口的作用就是修改这一设定，即：在进入房间之后也能动态修改角色。业务测可以通过此接口让用户在房间内动态调整音视频、网络参数，如将视频模式从清晰切换成流畅。

      @param [in] av_control_role 角色字符串。

      @param [in] change_role_callback 回调函数。

      @param [in] custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

      @remark [改动]这个接口现在已经实现了普通修改角色，修改音视频上下行的权限和切换音频场景的功能，以前切换角色后仍然需要切换权限和切换音频场景，新的接口结合了这三个功能。

      @return 返回操作结果。
      */
    virtual void ChangeAVControlRole(const std::string& av_control_role, ChangeCompleteCallback change_role_callback, void* custom_data) = 0;

    /**
    @brief 获取音视频通话的实时通话质量的相关信息。该函数主要用来查看实时通话质量、排查问题等，业务侧可以用其来做些提高用户体验的功能，如提示网络差，通话质量也较差。

    @param param 音视频通话的实时通话质量的相关参数。
    @return 返回值为true时代表获取成功，否则代表获取失败。
    */
    virtual bool GetQualityParam(RoomStatParam* param) = 0;
};

} // namespace av
} // namespace tencent
