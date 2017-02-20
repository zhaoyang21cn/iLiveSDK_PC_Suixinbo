#ifndef iLiveRoomMgr_h_
#define iLiveRoomMgr_h_

#include <imsdk/tim_group_c.h>
#include <imsdk/tim_msg.h>
#include <imsdk/tim_int.h>
#include <imsdk/tim_comm.h>
#include <avsdk/av_common.h>
#include <avsdk/av_device.h>
#include <ilivesdk/iLiveCommon.h>
#include <ilivesdk/iLiveRoomOption.h>
#include <ilivesdk/iLivePushOption.h>
#include <ilivesdk/iLiveRecordOption.h>
using imcore::TIMMessage;
using imcore::TIMCallBack;
using imcore::TIMStreamRsp;
using imcore::TIMValueCallBack;
using tencent::av::AVDevice;
using tencent::av::AVDeviceMgr;
using tencent::av::View;
using tencent::av::DetectedDeviceInfo;
using tencent::av::AVSupportVideoPreview;
using tencent::av::AVSupportVideoPreTreatment;
using tencent::av::VideoFrame;
using tencent::av::AVAudioCtrl;
using tencent::av::AVVideoCtrl;
using tencent::av::AVLocalScreenVideoDevice;

namespace ilivesdk
{
	/**
	@brief 屏幕共享状态。
	@details 屏幕共享状态。
	*/
	enum E_ScreenShareState
	{
		E_ScreenShareNone,	///< 未开启屏幕分享
		E_ScreenShareWnd,	///< 开启了指定窗口的共享
		E_ScreenShareArea,	///< 开启了指定区域的共享
	};

	/**
	@brief iLiveRoom管理类。
	@details 此类封装了iLiveRoom的相关操作接口。
	*/
	class iLiveAPI iLiveRoomMgr
	{
		enum E_EnterRoomType
		{
			E_EnterRoomInvalid,
			E_EnterRoomCreate,
			E_EnterRoomJoin,
		};

		struct sRequestPair
		{
			sRequestPair(std::string id, View v);
			bool IdAndSrcTypeEqual(const sRequestPair& other);

			std::string identifier;
			View view;
		};

		class AVRoomMultiDelegate : public AVRoomMulti::Delegate
		{
		public:
			virtual void	OnEnterRoomComplete(int32 result, const std::string& error_info) override; //返回AVContext::EnterRoom()的异步操作结果的函数
			virtual void	OnExitRoomComplete() override; //退出房间完成回调
			virtual void	OnRoomDisconnect(int32 reason, const std::string& error_info) override; //SDK主动退出房间提示
			virtual void	OnEndpointsUpdateInfo(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list) override; //房间成员状态变化通知的函数
			virtual void	OnPrivilegeDiffNotify(int32 privilege); //房间成员无某个通话能力权限却去使用相关通话能力而导致的异常通知的函数
			virtual void	OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list) override;//半自动模式接收摄像头视频的事件通知
			virtual void	OnSemiAutoRecvScreenVideo(std::vector<std::string> identifier_list) override;//半自动模式接收屏幕分享的事件通知
			virtual void	OnSemiAutoRecvMediaFileVideo(std::vector<std::string> identifier_list) override;//半自动模式接收播片的事件通知
			virtual void	OnCameraSettingNotify(int32 width, int32 height, int32 fps) override;//摄像头分辨率和帧率修改通知
			virtual void	OnSwitchRoomComplete(int32 result, const std::string& error_info) override;//返回switchRoom()的异步操作结果的函数
		};
		
		class SendC2CMessageCB : public TIMCallBack
		{
		public:
			virtual void OnSuccess();
			virtual void OnError(int code, const std::string &desc);
		};

		class SendGroupMessageCB : public TIMCallBack
		{
		public:
			virtual void OnSuccess();
			virtual void OnError(int code, const std::string &desc);
		};

		class StartPushStreamCB : public TIMValueCallBack<TIMStreamRsp&>
		{
		public:
			virtual void OnSuccess(TIMStreamRsp& value);
			virtual void OnError(int code, const std::string &desc);
		};

		class StopPushStreamCB: public TIMCallBack
		{
		public:
			virtual void OnSuccess();
			virtual void OnError(int code, const std::string &desc);
		};

		class StartRecordCB : public TIMCallBack
		{
		public:
			virtual void OnSuccess();
			virtual void OnError(int code, const std::string &desc);
		};

		class StopRecordCB : public TIMValueCallBack< std::list<std::string>& >
		{
		public:
			virtual void OnSuccess(std::list<std::string>& value);
			virtual void OnError(int code, const std::string &desc);
		};

	public:
		/**
		@brief 获取单例对象。
		@return 返回此类的单例对象。
		*/
		static iLiveRoomMgr*	getInstance();

		/**
		@brief 设置预处理函数指针。
		@param [in] pPreTreatmentFun 预处理函数指针，参见AVSupportVideoPreTreatment::PreTreatmentFun的定义。
		@param [in] pCustomData 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。
		@remark 业务侧实现该预处理函数，然后由SDK同步调用它。实现预处理函数的注意事项：预处理函数耗时不要过久，最好控制在10ms内；同时不能改变图像大小和图像颜色格式。
		*/
		void					setPreTreatmentFun( AVSupportVideoPreTreatment::PreTreatmentFun pPreTreatmentFun, void* pCustomData );
		/**
		@brief 设置本地视频回调函数指针。
		@param [in] pLocalVideoCB 本地视频回调函数指针，参见AVSupportVideoPreview::PreviewCallback的定义。
		@param [in] pCustomData 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。
		@remark 业务侧实现该回调函数，SDK向该回调函数传入本地视频相关数据，业务侧拿到数据后进行渲染显示;
		*/
		void					setLocalVideoCallBack( AVSupportVideoPreview::PreviewCallback pLocalVideoCB, void* pCustomData );
		/**
		@brief 设置远程视频回到函数指针。
		@param [in] pRemoteVideoCB 远程视频回调函数指针，参见AVSupportVideoPreview::PreviewCallback的定义。
		@param [in] pCustomData 业务侧自定义的参数，会在执行回到函数是原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。
		@remark 业务侧实现该回调函数，SDK向该回调函数传入远程视频相关数据，业务侧拿到数据后进行渲染显示;
		*/
		void					setRemoteVideoCallBack( AVSupportVideoPreview::PreviewCallback pRemoteVideoCB, void* pCustomData );

		/**
		@brief 创建直播房间(主播端调用)。
		@param [in] roomOption 房间配置。
		@param [in] suc 成功的回调函数。
		@param [in] err 失败的回调函数。
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					createRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 加入直播房间(观众端调用)。
		@param [in] roomOption 房间配置。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					joinRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 退出直播间。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					quitRoom( SuccessCalllback suc, ErrorCallback err, void* data );

		/**
		@brief 发送C2C消息。
		@param [in] dstUser 接收方id。
		@param [in] message IM消息。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					sendC2CMessage( const std::string dstUser, TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 发送Group消息。
		@param [in] message IM消息。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		@remark  此处发送Group消息，仅限于在当前直播间中发送Group消息。
		*/
		void					sendGroupMessage( TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );
		
		/**
		@brief 请求一个或多个成员的视频画面。
		@param [in] identifiers 请求画面的id列表;
		@param [in] views 请求画面的view列表;
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		@note 1、identifiers和views必须一一对应;
			  2、requestViewList操作必须等待异步回调函数执行结束后，才能进行新的requestViewList操作；
			  3、requestViewList、cancelViewList和cancelAllView不能并发执行，即同一时刻只能进行一种操作；
			  4、在请求画面前最好先检查该成员是否有对应的视频源；
		*/
		void					requestViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief  取消指定用户的画面。
		@param [in] identifiers 取消画面的用户列表。
		@param [in] views 取消画面的view列表;
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		@note identifiers和views必须一一对应;requestViewList、cancelViewList和cancelAllView不能并发执行，即同一时刻只能进行一种操作;
		*/
		void					cancelViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 取消所有请求的视频画面。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		@note requestViewList、cancelViewList和cancelAllView不能并发执行，即同一时刻只能进行一种操作；
		*/
		void					cancelAllView( SuccessCalllback suc, ErrorCallback err, void* data );

		/**
		@brief  更改通话能力权限。
		@details 通话能力权限包括是否可以创建房间/进入房间/发送音频/接收音频/发送摄像头视频/接收摄像头视频/发送屏幕视频/接收屏幕视频等。
		@param [in] authBits 通话能力权限位,在<ilivesdk/iLiveRoomOption.h>文件中可以查看所有权限位定义。
		@param [in] authBuffer 通话能力权限位的加密串。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					changeAuthority( uint64 authBits, const std::string& authBuffer, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 更改角色。
		@details 更改角色不包括修改音频场景，音频场景需要在进入房间前指定而且进入房间以后不能修改。
		@param [in] szControlRole 角色字符串(由用户App的控制台生成)。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					changeRole( const std::string& szControlRole, SuccessCalllback suc, ErrorCallback err, void* data );

		/**
		@brief 设置美颜程度。
		@param [in] grade 美颜程度参数。grade取值范围在0-9之间，0表示美颜关闭
		@return 返回值为NO_ERR时表示成功，否则表示失败。
		*/
		int						SetSkinSmoothGrade(int grade);
		
		/**
		@brief 设置美白程度。
		@param [in] grade 美白程度参数。grade取值范围在0-9之间，0表示美白关闭
		@return 返回值为NO_ERR时表示成功，否则表示失败。
		*/
		int						SetSkinWhitenessGrade(int grade);

		/**
		@brief 获取本计算机可用的摄像头列表。
		@param [out] cameraList 传回获取到的摄像机列表,如果传回的列表为空，表示本机无可用摄像头。
		@return 操作结果,NO_ERR表示无错误;
		*/
		int						getCameraList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> > &cameraList );
		/**
		@brief 打开摄像头。
		@param [in] szCameraId 通过getCameraList()函数获取的摄像头列表中的某个摄像头id。
		@return 操作结果，NO_ERR表示无错误;
		@note 打开摄像头成功，如果用户有上传视频权限，便会自动开始上传摄像头视频;
		*/
		int						openCamera( std::string szCameraId );
		/**
		@brief 关闭当前打开的摄像头。
		@return 操作结果，NO_ERR表示无错误。
		*/
		int						closeCamera();

		/**
		@brief 获取本计算机可用的麦克风列表。
		@param [out] micList 传回获取到的麦克风列表,如果传回的列表为空，表示本机无可用麦克风。
		@return 操作结果,NO_ERR表示无错误;
		*/
		int						getMicList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> > &micList);
		/**
		@brief 打开麦克风。
		@param [in] szMicId 通过getMicList()函数获取的麦克风列表中的某个麦克风id。
		@return 操作结果，NO_ERR表示无错误;
		@note 打开麦克风成功，如果用户有上传语音权限，便会自动开始上传麦克风音频。
		*/
		int						openMic( std::string szMicId );
		/**
		@brief 关闭当前打开的麦克风。
		@return 操作结果，NO_ERR表示无错误。
		*/
		int						closeMic();
		
		/**
		@brief 获取本计算机可用的扬声器列表。
		@param [out] playerList 传回获取到的扬声器列表,如果传回的列表为空，表示本机无可用扬声器。
		@return 操作结果,NO_ERR表示无错误;
		*/
		int						getPlayerList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> > &playerList );
		/**
		@brief 打开扬声器。
		@param [in] szPlayerId 通过getPlayerList()函数获取的扬声器列表中的某个扬声器id。
		@return 操作结果，NO_ERR表示无错误;
		@note 打开扬声器成功，如果用户有接收音频权限，便会自动开始播放远端音频。
		*/
		int						openPlayer( std::string szPlayerId );
		/**
		@brief 关闭当前打开的扬声器。
		@return 操作结果，NO_ERR表示无错误。
		*/
		int						closePlayer();

		/**
		@brief 打开屏幕分享(指定窗口)。
		@param [in] hWnd 所要捕获的窗口句柄。
		@param [in] fps 捕获帧率,取值范围[MIN_SCREEN_VIDEO_CAPTURE_FPS-MAX_SCREEN_VIDEO_CAPTURE_FPS],具体参考MIN_SCREEN_VIDEO_CAPTURE_FPS和MAX_SCREEN_VIDEO_CAPTURE_FPS两个宏的定义。
		@return 操作结果，NO_ERR表示无错误。
		@remark 传入的参数(fps)可能会经过sdk内部调整，并通过引用方式传回给调用者，实际分享使用的fps以传回值为准;
		*/
		int						openScreenShare( HWND hWnd, uint32& fps );
		/**
		@brief 打开屏幕共享(指定区域)。
		@param [in] left/top/right/bottom 所要捕获屏幕画面的区域的左上角坐标(left, top)和右下角坐标(right, bottom)，它们是以屏幕的左上角坐标为原点的。
		@param [in] fps 捕获帧率，取值范围[MIN_SCREEN_VIDEO_CAPTURE_FPS-MAX_SCREEN_VIDEO_CAPTURE_FPS]，具体参考MIN_SCREEN_VIDEO_CAPTURE_FPS和MAX_SCREEN_VIDEO_CAPTURE_FPS两个宏的定义。
		@return 操作结果，NO_ERR表示无错误。
		@remark 传入的参数可能会经过sdk内部细微的调整，并通过引用方式传回给调用者，实际的分享区域以传回的值为准;
		*/
		int						openScreenShare( uint32& left, uint32& top, uint32& right, uint32& bottom, uint32& fps );
		/**
		@brief 屏幕分享过程中,动态修改屏幕分享的区域。
		@param [in] left/top/right/bottom 所要捕获屏幕画面的区域的左上角坐标(left, top)和右下角坐标(right, bottom)，它们是以屏幕的左上角坐标为原点的。
		@return 操作结果，NO_ERR表示无错误。
		@remark 传入的参数可能会经过sdk内部细微的调整，并通过引用方式传回给调用者，实际的分享区域以传回的值为准;
		@note 此接口只有在打开了指定区域的屏幕共享时才有效,其他状态下将会返回ERR_WRONG_STATE错误;
		*/
		int						changeScreenShareSize( uint32& left, uint32& top, uint32& right, uint32& bottom );
		/**
		@brief 关闭屏幕共享。
		@return 操作结果，NO_ERR表示无错误。
		@remark 指定窗口的屏幕分享和指定区域的屏幕分享都调用此接口来关闭.
		*/
		int						closeScreenShare();

		/**
		@brief 开始推流。
		@param [in] pushOption 推流配置选项。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		@remark 推流成功的回调函数中，sdk会传回TIMStreamRsp结构，此结构中包含了频道ID(channel_id)，在停止推流时，业务侧需要传入此频道ID.
		*/
		void					startPushStream( const iLivePushOption& pushOption, Type<TIMStreamRsp&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );
		/**
		@brief 停止推流。
		@param [in] channelId 停止推流的频道ID，SDK在startPushStream()函数的回调中传回给业务侧此频道ID。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					stopPushStream( uint64 channelId, SuccessCalllback suc, ErrorCallback err, void* data );

		/**
		@brief 开始录制。
		@param [in] recordOption 录制配置选项。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					startRecordVideo( const iLiveRecordOption& recordOption, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 停止录制。
		@param [in] suc 成功的回调函数；
		@param [in] err 失败的回调函数；
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		@remark 停止录制成功回调，返回录制视频文件的ID列表; 业务侧开起自动录制时，将返回空列表，用户可直接到后台查询。
		*/
		void					stopRecordVideo( Type<std::list<std::string>&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );
		/**
		@brief 获取当前摄像头状态
		@return true:打开 false：关闭
		*/
		bool					getCurCameraState();
		/**
		@brief 获取当前麦克风状态
		@return true:打开 false：关闭
		*/
		bool					getCurMicState();
		/**
		@brief 获取当前扬声器状态
		@return true:打开 false：关闭
		*/
		bool					getCurPlayerState();
		/**
		@brief 获取当前屏幕分享状态
		@return true:打开 false：关闭
		*/
		E_ScreenShareState		getScreenShareState();
		/**
		@brief 获取当前推流状态
		@return true:打开 false：关闭
		*/
		bool					getPushStreamState();
		/**
		@brief 获取当前视频录制状态
		@return true:打开 false：关闭
		*/
		bool					getRecordState();

	private:
		iLiveRoomMgr();
		~iLiveRoomMgr();

		void					ResetAllState();
		int						SetupAVRoom();

		void					CommentViewList(bool isCancelView);
		void					UpdateViewList(std::vector<std::string>& identifierList, std::vector<View>& viewList);

		void					OnEnterAVRoomSuc();
		void					OnEnterAVRoomErr(int code, const char* desc);

		void					OnQuitAVRoomComplete();

		static void				OnCreateIMGroupSuccess(const char* group_id, void* data);
		static void				OnCreateIMGroupError(int code, const char* desc, void* data);

		static void				OnJoinIMGroupSuccess(void* data);
		static void				OnJoinIMGroupError(int code, const char* desc, void* data);

		static void				OnQuitIMGroupSuccess(void* data);
		static void				OnQuitIMGroupError(int code, const char* desc, void* data);

		static void				OnAudioDeviceOperationCallback(AVDeviceMgr *pAudMgr, AVDevice::DeviceOperation oper, const std::string &deviceId, int retCode, void *pCustomData);
		static void				OnAudioDeviveDetectNotify(AVDeviceMgr* device_mgr, DetectedDeviceInfo& info, bool*pbSelect, void* custom_data);

		static void				OnVideoDeviceOperationCallback(AVDeviceMgr *pVidMgr, AVDevice::DeviceOperation oper, const std::string &deviceId, int retCode, void *pCustomData);
		static void				OnVideoDeviceChangeCallback(AVDeviceMgr *pVidMgr, void *pCustomData);

		static void				OnRequestViewListCompleteCallback(std::vector<std::string> identifierList, std::vector<View> viewList, int32 result, const std::string& error_info, void *pCustomData);
		static void				OnCancelViewListCompleteCallback(std::vector<std::string> identifierList, std::vector<View> viewList, int32 result, const std::string& error_info, void *pCustomData);
		static void				OnCancelAllViewCompleteCallback(int32 result, const std::string& error_info, void* custom_data);

		static void				OnChangeAuthCompleteCallback(int32 result, const std::string& error_info, void* custom_data);
		static void				OnChangeRoleCompleteCallback(int32 result, const std::string& error_info, void* custom_data);
	
	private:
		//IM
		TIMNewGroupInfoHandle		m_handleTIMNewGroupInfo;

		TIMCreateGroupCB			m_timCreateGroupCB;
		TIMCommCB					m_timJoinGroupCB;
		TIMCommCB					m_timQuitGroupCB;

		SendC2CMessageCB			m_sendC2CMessageCB;
		SendGroupMessageCB			m_sendGroupMessageCB;
		StartPushStreamCB			m_startPushStreamCB;
		StopPushStreamCB			m_stopPushStreamCB;
		StartRecordCB				m_startRecordCB;
		StopRecordCB				m_stopRecordCB;

		//AV
		E_EnterRoomType				m_EnterRoomType;

		AVRoomMultiDelegate			m_AVRoomMultiDelegate;
		
		iLiveRoomOption				m_roomOption;
		iLivePushOption				m_pushOption;
		iLiveRecordOption			m_recordOption;
		
		std::string					m_szCurCameraId;
		std::string					m_szCurMicId;
		std::string					m_szCurPlayerId;

		bool						m_bCurCameraState;
		bool						m_bCurMicState;
		bool						m_bCurPlayerState;
		E_ScreenShareState			m_eScreenShareState;
		bool						m_bPushStreamState;
		bool						m_bRecordState;

		std::vector<sRequestPair>	m_curRequestViews;

		AVRoomMulti*				m_pRoom;
		AVDeviceMgr*				m_pAudMgr;
		AVDeviceMgr*				m_pVidMgr;
		AVAudioCtrl*				m_pAudCtrl;
		AVVideoCtrl*				m_pVidCtrl;
		AVLocalScreenVideoDevice*	m_pLocalScreenVideoDevice;

		AVSupportVideoPreTreatment::PreTreatmentFun	m_pPreTreatmentFun;
		void*										m_pPreTreatmentFunData;

		AVSupportVideoPreview::PreviewCallback	m_pLocalVideoCB;
		void*									m_pLocalVideoData;

		AVSupportVideoPreview::PreviewCallback	m_pRemoteVideoCB;
		void*									m_pRemoteVideoData;

		//业务侧传入的回调函数指针
		SuccessCalllback			m_pCreateRoomSuccessCB;
		ErrorCallback				m_pCreateRoomErrorCB;
		void*						m_pCreateRoomData;

		SuccessCalllback			m_pJoinRoomSuccessCB;
		ErrorCallback				m_pJoinRoomErrorCB;
		void*						m_pJoinRoomData;

		SuccessCalllback			m_pQuitRoomSuccessCB;
		ErrorCallback				m_pQuitRoomErrorCB;
		void*						m_pQuitRoomData;

		SuccessCalllback			m_pSendC2CMsgSucCB;
		ErrorCallback				m_pSendC2CMsgErrCB;
		void*						m_pSendC2CMsgData;

		SuccessCalllback			m_pSendGroupMsgSucCB;
		ErrorCallback				m_pSendGroupMsgErrCB;
		void*						m_pSendGroupMsgData;

		SuccessCalllback			m_pRequestViewListSucCB;
		ErrorCallback				m_pRequestViewListErrCB;
		void*						m_pRequestViewListData;

		SuccessCalllback			m_pCancelViewListSucCB;
		ErrorCallback				m_pCancelViewListErrCB;
		void*						m_pCancelViewListData;

		SuccessCalllback			m_pCancelAllViewSucCB;
		ErrorCallback				m_pCancelAllViewErrCB;
		void*						m_pCancelAllViewData;

		SuccessCalllback			m_pChangeAuthoritySucCB;
		ErrorCallback				m_pChangeAuthorityErrCB;
		void*						m_pChangeAuthorityData;

		SuccessCalllback			m_pChangeRoleSucCB;
		ErrorCallback				m_pChangeRoleErrCB;
		void*						m_pChangeRoleData;

		Type<TIMStreamRsp&>::VlaueSuccessCallback	m_pStartPushStreamSucCB;
		ErrorCallback								m_pStartPushStreamErrCB;
		void*										m_pStartPushStreamData;

		SuccessCalllback			m_pStopPushStreamSucCB;
		ErrorCallback				m_pStopPushStreamErrCB;
		void*						m_pStopPushStreamData;

		SuccessCalllback			m_pStartRecordVideoSucCB;
		ErrorCallback				m_pStartRecordVideoErrCB;
		void*						m_pStartRecordVideoData;

		Type<std::list<std::string>&>::VlaueSuccessCallback	m_pStopRecordVideoSucCB;
		ErrorCallback										m_pStopRecordVideoErrCB;
		void*												m_pStopRecordVideoData;
	};
}

#endif //iLiveRoomMgr_h_