#ifndef iLiveRoomOption_h_
#define iLiveRoomOption_h_

#include <ilivesdk/iLiveCommon.h>
#include <avsdk/av_common.h>
#include <avsdk/av_room_multi.h>

using tencent::av::AudioCategory;
using tencent::av::AVRoomMulti;
using tencent::av::VideoRecvMode;

namespace ilivesdk
{
	/**
	@brief SDK主动退出房间监听函数指针。
	@details SDK内部会因为30s心跳包超时等原因主动退出房间，APP需要监听此退出房间事件并对该事件进行相应处理。
	@param [in] reason 退出原因, 参考av_error.h。
	@param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧。
	*/
	typedef void (*iLiveRoomDisconnectListener)(int32 reason, void* data);
	/**
	@brief 房间内成员变化监听函数指针。
	@details 当房间成员发生状态变化(如是否发音频、是否发视频等)时，会通过该函数指针通知业务侧。
	@param [in] event_id 状态变化id，详见EndpointEventId的定义。
	@param [in] identifier_list 发生状态变化的成员id列表。
	@param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧。
	*/
	typedef void (*iLiveMemStatusListener)(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data);
	/**
    @brief 半自动模式接收摄像头视频的事件通知。
    @details 半自动模式接收摄像头视频的事件通知。也就是当进入房间时，如果已经有人发送了视频，则会自动接收这些视频，不用手动去请求。当然，进入房间后，如果其他人再发送视频，则不会自动接收。
	@param [in] identifier_list 自动接收的摄像头视频所对应的成员id列表。
	@param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧。
    */
	typedef	void (*iLiveSemiAutoRecvCameraVideoListener)(std::vector<std::string> identifier_list, void* data);

	/**
	@brief iLiveRoom配置项。
	@details 在创建或者加入房间时，需要先填写此结构作为参数传入;
	*/
	struct iLiveRoomOption
	{
		/**
		@brief 构造函数，初始化成员变量值。
		*/
		iLiveRoomOption()
			:roomId(0)
			,m_roomDisconnectListener(NULL)
			,m_memberStatusListener(NULL)
			,m_autoRecvListener(NULL)
			,data(NULL)
		{
		}

		uint32			roomId;			///< 房间ID,由业务侧创建并维护的房间ID
		std::string		auth_buffer;	///< 通话能力权限位的加密串
		std::string		control_role;	///< 角色名，web端音视频参数配置工具所设置的角色名
		AudioCategory	audio_category;	///< 音视场景策略,详细信息见AudioCategory的定义.
		VideoRecvMode	video_recv_mode;///< 视频接收模式

		iLiveRoomDisconnectListener				m_roomDisconnectListener; ///< SDK主动退出房间提示,参见iLiveRoomDisconnectListener定义。
		iLiveMemStatusListener					m_memberStatusListener;	  ///< 房间成员状态变化通知，参见iLiveMemStatusListener定义。
		iLiveSemiAutoRecvCameraVideoListener	m_autoRecvListener;		  ///< 半自动模式接收摄像头视频的通知，参见iLiveSemiAutoRecvCameraVideoListener定义。
		void*									data;					  ///< 用户自定义数据类型，在m_roomDisconnectListener、m_memberStatusListener和m_autoRecvListener中原封不动返回。
	};
}

#endif//iLiveRoomOption_h_