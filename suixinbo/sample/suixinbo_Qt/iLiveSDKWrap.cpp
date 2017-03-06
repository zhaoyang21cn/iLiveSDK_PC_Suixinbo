#include "stdafx.h"
#include "iLiveSDKWrap.h"

iLiveSDKWrap::iLiveSDKWrap()
{

}

iLiveSDKWrap::~iLiveSDKWrap()
{

}

iLiveSDKWrap* iLiveSDKWrap::getInstance()
{
	static iLiveSDKWrap instance;
	return &instance;
}

int iLiveSDKWrap::initSdk( const int appId, const int accountType )
{
	return iLiveSDK::getInstance()->initSdk(appId, accountType);
}

void iLiveSDKWrap::destroy()
{
	iLiveSDK::getInstance()->destroy();
}

void iLiveSDKWrap::setForceOfflineCallback( ForceOfflineCallback cb )
{
	iLiveLoginMgr::getInstance()->setForceOfflineCallback(cb);
}

void iLiveSDKWrap::setGroupMessageCallBack( GropuMessageCallback cb )
{
	iLiveRoomMgr::getInstance()->setGroupMessageCallBack(cb);
}

void iLiveSDKWrap::setC2CMessageCallBack( C2CMessageCallback cb )
{
	iLiveRoomMgr::getInstance()->setC2CMessageCallBack(cb);
}

void iLiveSDKWrap::setSysemMessageCallback( SysemMessageCallback cb )
{
	iLiveRoomMgr::getInstance()->setSysemMessageCallback(cb);
}

void iLiveSDKWrap::setLocalVideoCallBack( AVSupportVideoPreview::PreviewCallback pLocalVideoCB, void* pCustomData )
{
	iLiveRoomMgr::getInstance()->setLocalVideoCallBack(pLocalVideoCB, pCustomData);
}

void iLiveSDKWrap::setRemoteVideoCallBack( AVSupportVideoPreview::PreviewCallback pRemoteVideoCB, void* pCustomData )
{
	iLiveRoomMgr::getInstance()->setRemoteVideoCallBack(pRemoteVideoCB, pCustomData);
}

void iLiveSDKWrap::LiveLogin( const std::string szUserId, const std::string szUserSig, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveLoginMgr::getInstance()->iLiveLogin(szUserId, szUserSig, suc, err, data);
}

void iLiveSDKWrap::LiveLogout( SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveLoginMgr::getInstance()->iLiveLogout(suc, err, data);
}

void iLiveSDKWrap::createRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->createRoom(roomOption, suc, err, data);
}

void iLiveSDKWrap::joinRoom( const iLiveRoomOption& roomOption, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->joinRoom(roomOption, suc, err, data);
}

void iLiveSDKWrap::quitRoom( SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->quitRoom(suc, err, data);
}

void iLiveSDKWrap::requestViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->requestViewList(identifiers, views, suc, err, data);
}

void iLiveSDKWrap::cancelViewList( const std::vector<std::string>& identifiers, const std::vector<View>& views, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->cancelViewList(identifiers, views, suc, err, data);
}

void iLiveSDKWrap::cancelAllView( SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->cancelAllView(suc, err, data);
}

void iLiveSDKWrap::sendC2CMessage( const std::string dstUser, TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->sendC2CMessage(dstUser, message, suc, err, data);
}

void iLiveSDKWrap::sendGroupMessage( TIMMessage& message, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->sendGroupMessage(message, suc, err, data);
}

void iLiveSDKWrap::startRecordVideo( const iLiveRecordOption& recordOption, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->startRecordVideo(recordOption, suc, err, data);
}

void iLiveSDKWrap::stopRecordVideo( ilivesdk::Type<std::list<std::string>&>::VlaueSuccessCallback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->stopRecordVideo(suc, err, data);
}

void iLiveSDKWrap::startPushStream( const iLivePushOption& pushOption, ilivesdk::Type<TIMStreamRsp&>::VlaueSuccessCallback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->startPushStream(pushOption, suc, err, data);
}

void iLiveSDKWrap::stopPushStream( uint64 channelId, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->stopPushStream( channelId, suc, err, data);
}

void iLiveSDKWrap::changeAuthority( uint64 authBits, const std::string& authBuffer, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->changeAuthority(authBits, authBuffer, suc, err, data);
}

void iLiveSDKWrap::changeRole( const std::string& szControlRole, SuccessCalllback suc, ErrorCallback err, void* data )
{
	iLiveRoomMgr::getInstance()->changeRole(szControlRole, suc, err, data);
}

int iLiveSDKWrap::SetSkinSmoothGrade( int grade )
{
	return iLiveRoomMgr::getInstance()->SetSkinSmoothGrade(grade);
}

int iLiveSDKWrap::SetSkinWhitenessGrade( int grade )
{
	return iLiveRoomMgr::getInstance()->SetSkinWhitenessGrade(grade);
}

int iLiveSDKWrap::getCameraList( std::vector< std::pair<std::string/*id*/, std::string/*name*/> >& cameraList )
{
	return iLiveRoomMgr::getInstance()->getCameraList(cameraList);
}

int iLiveSDKWrap::openCamera(std::string szCameraId)
{
	return iLiveRoomMgr::getInstance()->openCamera(szCameraId);
}

int iLiveSDKWrap::closeCamera()
{
	return iLiveRoomMgr::getInstance()->closeCamera();
}

int iLiveSDKWrap::openMic()
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

int iLiveSDKWrap::closeMic()
{
	return iLiveRoomMgr::getInstance()->closeMic();
}

int iLiveSDKWrap::openPlayer()
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

int iLiveSDKWrap::closePlayer()
{
	return iLiveRoomMgr::getInstance()->closePlayer();
}

int iLiveSDKWrap::openScreenShare( HWND hWnd, uint32& fps )
{
	return iLiveRoomMgr::getInstance()->openScreenShare(hWnd, fps);
}

int iLiveSDKWrap::openScreenShare( uint32& left, uint32& top, uint32& right, uint32& bottom, uint32& fps )
{
	return iLiveRoomMgr::getInstance()->openScreenShare(left, top, right, bottom, fps);
}

int iLiveSDKWrap::changeScreenShareSize( uint32& left, uint32& top, uint32& right, uint32& bottom )
{
	return iLiveRoomMgr::getInstance()->changeScreenShareSize(left, top, right, bottom);
}

int iLiveSDKWrap::closeScreenShare()
{
	return iLiveRoomMgr::getInstance()->closeScreenShare();
}

bool iLiveSDKWrap::getCurCameraState()
{
	return iLiveRoomMgr::getInstance()->getCurCameraState();
}

bool iLiveSDKWrap::getCurMicState()
{
	return iLiveRoomMgr::getInstance()->getCurMicState();
}

bool iLiveSDKWrap::getCurPlayerState()
{
	return iLiveRoomMgr::getInstance()->getCurPlayerState();
}

E_ScreenShareState iLiveSDKWrap::getScreenShareState()
{
	return iLiveRoomMgr::getInstance()->getScreenShareState();
}

bool iLiveSDKWrap::getPushStreamState()
{
	return iLiveRoomMgr::getInstance()->getPushStreamState();
}

bool iLiveSDKWrap::getRecordState()
{
	return iLiveRoomMgr::getInstance()->getRecordState();
}
