#ifndef iLiveSDKWrap_h_
#define iLiveSDKWrap_h_

#include <ilivesdk/iLiveLog.h>
#include <ilivesdk/iLiveSDK.h>
#include <ilivesdk/iLiveLoginMgr.h>
#include <ilivesdk/iLiveRoomMgr.h>

using ilivesdk::SuccessCalllback;
using ilivesdk::ErrorCallback;
using ilivesdk::iLiveRoomOption;
using ilivesdk::iLiveRecordOption;
using ilivesdk::iLivePushOption;
using ilivesdk::E_ScreenShareState;

#pragma comment(lib, "iLiveSDK.lib")

class iLiveSDKWrap
{
public:
	static iLiveSDKWrap* getInstance();

	int initSdk(const int appId, const int accountType);///< 初始化sdk
	void destroy();

	void SetForceOfflineCallback(TIMForceOfflineCallBack* cb);
	void SetMessageCallBack( TIMMessageCallBack *cb );
	void setLocalVideoCallBack( AVSupportVideoPreview::PreviewCallback pLocalVideoCB, void* pCustomData );
	void setRemoteVideoCallBack( AVSupportVideoPreview::PreviewCallback pRemoteVideoCB, void* pCustomData );//设置远程视频回调,需要在进入房间前调用

	void LiveLogin ( const std::string szUserId, const std::string szUserSig, SuccessCalllback suc, ErrorCallback err, void* data );///< 登录
	void LiveLogout( SuccessCalllback suc, ErrorCallback err, void* data );///< 登出

	void createRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
	void joinRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data );
	void quitRoom( SuccessCalllback suc, ErrorCallback err, void* data );

	void requestViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
	void cancelViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data );
	void cancelAllView( SuccessCalllback suc, ErrorCallback err, void* data );

	void sendC2CMessage( const std::string dstUser, TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );
	void sendGroupMessage( TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data );

	void startRecordVideo( const iLiveRecordOption& recordOption, SuccessCalllback suc, ErrorCallback err, void* data );
	void stopRecordVideo( ilivesdk::Type<std::list<std::string>&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );

	void startPushStream( const iLivePushOption& pushOption, ilivesdk::Type<TIMStreamRsp&>::VlaueSuccessCallback suc, ErrorCallback err, void* data );
	void stopPushStream( uint64 channelId, SuccessCalllback suc, ErrorCallback err, void* data );

	void changeAuthority( uint64 authBits, const std::string& authBuffer, SuccessCalllback suc, ErrorCallback err, void* data );
	void changeRole( const std::string& szControlRole, SuccessCalllback suc, ErrorCallback err, void* data );

	int SetSkinSmoothGrade(int grade);
	int SetSkinWhitenessGrade(int grade);

	int getCameraList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> >& cameraList );
	int	openCamera(std::string szCameraId);
	int closeCamera();

	int openMic();
	int closeMic();

	int openPlayer();
	int closePlayer();

	int openScreenShare( HWND hWnd, uint32& fps );
	int openScreenShare( uint32& left, uint32& top, uint32& right, uint32& bottom, uint32& fps );
	int changeScreenShareSize( uint32& left, uint32& top, uint32& right, uint32& bottom );
	int closeScreenShare();

	bool getCurCameraState();
	bool getCurMicState();
	bool getCurPlayerState();
	E_ScreenShareState getScreenShareState();
	bool getPushStreamState();
	bool getRecordState();

private:
	iLiveSDKWrap();
	~iLiveSDKWrap();
};


#endif //iLiveSDKWrap_h_