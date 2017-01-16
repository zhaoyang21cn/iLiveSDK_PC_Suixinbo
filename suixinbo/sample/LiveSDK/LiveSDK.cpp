#include "LiveSDK.h"
using namespace ilivesdk;

namespace livesdk
{
	LiveSDK::LiveSDK()
	{

	}

	LiveSDK::~LiveSDK()
	{

	}

	LiveSDK* LiveSDK::getInstance()
	{
		static LiveSDK instance;
		return &instance;
	}

	int LiveSDK::initSdk( const int appId, const int accountType )
	{
		return iLiveSDK::getInstance()->initSdk(appId, accountType);
	}

	void LiveSDK::destroy()
	{
		iLiveSDK::getInstance()->destroy();
	}

	void LiveSDK::SetForceOfflineCallback( TIMForceOfflineCallBack* cb )
	{
		iLiveSDK::getInstance()->SetForceOfflineCallback(cb);
	}

	void LiveSDK::SetMessageCallBack( TIMMessageCallBack *cb )
	{
		iLiveSDK::getInstance()->SetMessageCallBack(cb);
	}

	void LiveSDK::setLocalVideoCallBack( AVSupportVideoPreview::PreviewCallback pLocalVideoCB, void* pCustomData )
	{
		iLiveRoomMgr::getInstance()->setLocalVideoCallBack(pLocalVideoCB, pCustomData);
	}

	void LiveSDK::setRemoteVideoCallBack( AVSupportVideoPreview::PreviewCallback pRemoteVideoCB, void* pCustomData )
	{
		iLiveRoomMgr::getInstance()->setRemoteVideoCallBack(pRemoteVideoCB, pCustomData);
	}

	void LiveSDK::LiveLogin( const std::string szUserId, const std::string szUserSig, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveLoginMgr::getInstance()->iLiveLogin(szUserId, szUserSig, suc, err, data);
	}

	void LiveSDK::LiveLogout( SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveLoginMgr::getInstance()->iLiveLogout(suc, err, data);
	}

	void LiveSDK::createRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->createRoom(roomOption, suc, err, data);
	}

	void LiveSDK::joinRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->joinRoom(roomOption, suc, err, data);
	}

	void LiveSDK::quitRoom( SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->quitRoom(suc, err, data);
	}

	int LiveSDK::requestViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		return iLiveRoomMgr::getInstance()->requestViewList(identifiers, views, suc, err, data);
	}

	int LiveSDK::cancelViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		return iLiveRoomMgr::getInstance()->cancelViewList(identifiers, views, suc, err, data);
	}

	int LiveSDK::cancelAllView( SuccessCalllback suc, ErrorCallback err, void* data )
	{
		return iLiveRoomMgr::getInstance()->cancelAllView(suc, err, data);
	}

	void LiveSDK::sendC2CMessage( const std::string dstUser, TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->sendC2CMessage(dstUser, message, suc, err, data);
	}

	void LiveSDK::sendGroupMessage( TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->sendGroupMessage(message, suc, err, data);
	}

	void LiveSDK::startRecordVideo( const iLiveRecordOption& recordOption, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->startRecordVideo(recordOption, suc, err, data);
	}

	void LiveSDK::stopRecordVideo( ilivesdk::Type<std::list<std::string>&>::VlaueSuccessCallback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->stopRecordVideo(suc, err, data);
	}

	void LiveSDK::startPushStream( const iLivePushOption& pushOption, ilivesdk::Type<TIMStreamRsp&>::VlaueSuccessCallback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->startPushStream(pushOption, suc, err, data);
	}

	void LiveSDK::stopPushStream( uint64 channelId, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->stopPushStream( channelId, suc, err, data);
	}

	void LiveSDK::changeAuthority( uint64 authBits, const std::string& authBuffer, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->changeAuthority(authBits, authBuffer, suc, err, data);
	}

	void LiveSDK::changeRole( const std::string& szControlRole, SuccessCalllback suc, ErrorCallback err, void* data )
	{
		iLiveRoomMgr::getInstance()->changeRole(szControlRole, suc, err, data);
	}

	int LiveSDK::getCameraList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> >& cameraList )
	{
		return iLiveRoomMgr::getInstance()->getCameraList(cameraList);
	}

	int LiveSDK::openCamera(std::string szCameraId)
	{
		return iLiveRoomMgr::getInstance()->openCamera(szCameraId);
	}

	int LiveSDK::closeCamera()
	{
		return iLiveRoomMgr::getInstance()->closeCamera();
	}

	int LiveSDK::openMic()
	{
		std::vector< std::pair<std::string/*id*/, std::string/*name*/> > micList;
		int nRet = iLiveRoomMgr::getInstance()->getMicList(micList);
		if (nRet==NO_ERR)
		{
			std::string szMicID = micList[0].first;
			nRet = iLiveRoomMgr::getInstance()->openMic(szMicID);
		}
		return nRet;
	}

	int LiveSDK::closeMic()
	{
		return iLiveRoomMgr::getInstance()->closeMic();
	}

	int LiveSDK::openPlayer()
	{
		std::vector< std::pair<std::string/*id*/, std::string/*name*/> > playerList;
		int nRet = iLiveRoomMgr::getInstance()->getPlayerList(playerList);
		if (nRet==NO_ERR)
		{
			std::string szPlayerID = playerList[0].first;
			nRet = iLiveRoomMgr::getInstance()->openPlayer(szPlayerID);
		}
		return nRet;
	}

	int LiveSDK::closePlayer()
	{
		return iLiveRoomMgr::getInstance()->closePlayer();
	}

	int LiveSDK::openScreenShare(const uint32 left, const uint32 top, const uint32 right, const uint32 bottom, const uint32 fps)
	{
		return iLiveRoomMgr::getInstance()->openScreenShare(left, top, right, bottom, fps);
	}

	int LiveSDK::closeScreenShare()
	{
		return iLiveRoomMgr::getInstance()->closeScreenShare();
	}

	bool LiveSDK::getCurCameraState()
	{
		return iLiveRoomMgr::getInstance()->getCurCameraState();
	}

	bool LiveSDK::getCurMicState()
	{
		return iLiveRoomMgr::getInstance()->getCurMicState();
	}

	bool LiveSDK::getCurPlayerState()
	{
		return iLiveRoomMgr::getInstance()->getCurPlayerState();
	}

	bool LiveSDK::getScreenShareState()
	{
		return iLiveRoomMgr::getInstance()->getScreenShareState();
	}

	bool LiveSDK::getPushStreamState()
	{
		return iLiveRoomMgr::getInstance()->getPushStreamState();
	}

	bool LiveSDK::getRecordState()
	{
		return iLiveRoomMgr::getInstance()->getRecordState();
	}
}

