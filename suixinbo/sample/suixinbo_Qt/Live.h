#ifndef Live_h_
#define Live_h_

#include "ui_Live.h"
#include "VideoRender.h"
using imcore::TIMLiveUrl;

#define MaxVideoRender 3
#define MaxShowMembers 50

enum E_RoomUserType
{
	E_RoomUserInvalid = -1,
	E_RoomUserWatcher, //观众
	E_RoomUserCreator, //主播
	E_RoomUserJoiner,  //连麦者
};

struct RoomMember
{
	QString szID;
	E_RoomUserType userType;
};

class Live : public QDialog
{
	Q_OBJECT
public:
	Live(QWidget * parent = 0, Qt::WindowFlags f = 0);
	virtual ~Live();

	void setRoomUserType(E_RoomUserType userType);
	void ChangeRoomUserType();
	void updatePushAndRecordStateUI();

	void dealMessage(const TIMMessage& msg);
	void parseCusMessage(const std::string& sender,std::string msg);
	void dealCusMessage(const std::string& sender, int nUserAction, QString szActionParam);
	
	void startTimer();
	void stopTimer();

	void updateLater(int msec = 2000);

	static void OnMemStatusChange(AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data);
	static void OnSemiAutoRecvCameraVideo(std::vector<std::string> identifier_list, void* data);
	static void OnRoomDisconnect(int reason, void* data);

	static void OnLocalVideo(VideoFrame* video_frame, void* custom_data);
	static void OnRemoteVideo(VideoFrame* video_frame, void* custom_data);

private slots:
	void OnBtnOpenCamera();
	void OnBtnCloseCamera();
	void OnBtnOpenMic();
	void OnBtnCloseMic();
	void OnBtnOpenPlayer();
	void OnBtnClosePlayer();
	void OnBtnOpenScreenShare();
	void OnBtnCloseScreenShare();
	void OnBtnSendGroupMsg();
	void OnBtnStartRecord();
	void OnBtnStopRecord();
	void OnBtnStartPushStream();
	void OnBtnStopPushStream();
	void OnBtnPraise();
	void OnTimer();
	void OnRequestViewsTimer();
	void OnDelayUpdateTimer();
	void OnMemberListMenu(QPoint point);
	void OnActInviteInteract();
	void OnActCancelInteract();	
	void OnVideoRenderFullScreen(VideoRender* pRender);
	void OnExitVideoRenderFullScreen(VideoRender* pRender);

protected:
	void closeEvent(QCloseEvent* event) override;

private:
	void getCameraList();
	VideoRender* getVideoRender(std::string szIdentifier);
	void freeCameraVideoRenders(std::vector<std::string> arrNeedFreeRenders);
	void freeAllCameraVideoRender();
	void freeScreenVideoRender();

	void addMsgLab(QString msg);

	void addRequestViews(const std::vector<std::string>& identifiers, const std::vector<View>& views);

	void updateMemberList();

	void sendInviteInteract();//主播向普通观众发出连线邀请
	void sendCancelInteract();//主播向连线中的观众发出断线命令
	static void OnSendInviteInteractSuc(void* data);
	static void OnSendInviteInteractErr(int code, const std::string& desc, void* data);

	void acceptInteract();//普通观众接受连线邀请
	void refuseInteract();//普通观众拒绝连线邀请
	void OnAcceptInteract();

	void exitInteract();//连麦观众执行主播发出的断线命令
	void OnExitInteract();

	void sendQuitRoom();//主播发送退出房间信令

	void sxbCreatorQuitRoom();
	void sxbWatcherOrJoinerQuitRoom();
	void sxbHeartBeat();
	void sxbRoomIdList();
	void sxbReportrecord();
	static void OnSxbCreatorQuitRoom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbWatcherOrJoinerQuitRoom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbHeartBeat(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbRoomIdList(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbReportrecord(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

	void iLiveQuitRoom();
	void iLiveChangeAuthority(uint64 authBits, const std::string& authBuffer);
	void iLiveChangeRole(const std::string& szControlRole);
	static void OnQuitRoomSuc(void* data);
	static void OnQuitRoomErr(int code, const std::string& desc, void* data);
	static void OnChangeAuthoritySuc(void* data);
	static void OnChangeAuthorityErr(int code, const std::string& desc, void* data);
	static void OnChangeRoleSuc(void* data);
	static void OnChangeRoleErr(int code, const std::string& desc, void* data);

	static void OnRequestViewListSuc(void* data);
	static void OnRequestViewListErr(int code, const std::string& desc, void* data);

	static void OnSendGroupMsgSuc(void* data);
	static void OnSendGroupMsgErr(int code, const std::string& desc, void* data);

	static void OnStartRecordVideoSuc(void* data);
	static void OnStartRecordVideoErr(int code, const std::string& desc, void* data);

	static void OnStopRecordSuc(std::list<std::string>& value, void* data);
	static void OnStopRecordVideoErr(int code, const std::string& desc, void* data);

	static void OnStartPushStreamSuc(TIMStreamRsp& value, void* data);
	static void OnStartPushStreamErr(int code, const std::string& desc, void* data);

	static void OnStopPushStreamSuc(void* data);
	static void OnStopPushStreamErr(int code, const std::string& desc, void* data);

private:
	Ui::Live		m_ui;
	
	E_RoomUserType  m_userType;

	VideoRender*	m_pLocalCameraRender;
	VideoRender*	m_pScreenShareRender;

	std::vector< std::pair<std::string/*id*/, std::string/*name*/> > m_cameraList;

	std::vector<std::string> m_arrRemoteIdentifiers;
	VideoRender*			 m_pRemoteVideoRenders[MaxVideoRender];	
	bool					 m_bRemoteVideoRenderFrees[MaxVideoRender];

	int					m_nRoomSize;
	QVector<RoomMember> m_roomMemberList;

	QTimer*			m_pTimer;
	QTimer*			m_pDelayUpdateTimer;
	
	int				m_nCurSelectedMember;
	QMenu*			m_pMenuInviteInteract;
	QMenu*			m_pMenuCancelInteract;

	QString					m_inputRecordName;
	iLiveRecordOption		m_recordOpt;
	iLivePushOption			m_pushOpt;
	uint64					m_channelId;
	std::list<TIMLiveUrl>	m_pushUrls;

	QTimer*						m_pRequestViewsTimer;
	bool						m_bIsRequesting;
	std::vector<std::string>	m_toRequestIdentifiers;
	std::vector<View>			m_toRequestViews;
};

#endif//Live_h_