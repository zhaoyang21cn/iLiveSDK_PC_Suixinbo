#include "stdafx.h"
#include "Live.h"
#include "json/json.h"
#include "MixStreamHelper.h"

Live::Live( QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
	:QDialog(parent, f)
{
	m_ui.setupUi(this);

	m_userType =  E_RoomUserInvalid;

	m_pLocalCameraRender = new VideoRender(this);
	m_pScreenShareRender = new VideoRender(this);
	m_ui.layoutLocalVideo->addWidget(m_pLocalCameraRender);
	m_ui.layoutScreenShare->addWidget(m_pScreenShareRender);
	connect( m_pLocalCameraRender, SIGNAL(applyFullScreen(VideoRender*)), this, SLOT(OnVideoRenderFullScreen(VideoRender*)) );
	connect( m_pLocalCameraRender, SIGNAL(exitFullScreen(VideoRender*)), this, SLOT(OnExitVideoRenderFullScreen(VideoRender*)) );
	connect( m_pScreenShareRender, SIGNAL(applyFullScreen(VideoRender*)), this, SLOT(OnVideoRenderFullScreen(VideoRender*)) );
	connect( m_pScreenShareRender, SIGNAL(exitFullScreen(VideoRender*)), this, SLOT(OnExitVideoRenderFullScreen(VideoRender*)) );

	for(int i=0; i<MaxVideoRender; ++i)
	{
		m_arrRemoteIdentifiers.push_back("");
		m_pRemoteVideoRenders[i] = new VideoRender(this);	
		m_bRemoteVideoRenderFrees[i] = true;
		connect( m_pRemoteVideoRenders[i], SIGNAL(applyFullScreen(VideoRender*)), this, SLOT(OnVideoRenderFullScreen(VideoRender*)) );
		connect( m_pRemoteVideoRenders[i], SIGNAL(exitFullScreen(VideoRender*)), this, SLOT(OnExitVideoRenderFullScreen(VideoRender*)) );
	}
	m_ui.layoutRemoteVideo0->addWidget(m_pRemoteVideoRenders[0]);
	m_ui.layoutRemoteVideo1->addWidget(m_pRemoteVideoRenders[1]);
	m_ui.layoutRemoteVideo2->addWidget(m_pRemoteVideoRenders[2]);

	m_x0 = 0;
	m_y0 = 0;
	m_fps = 10;
	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	m_x1 = screenRect.width();
	m_y1 = screenRect.height();
	m_ui.sbX0->setValue(m_x0);
	m_ui.sbY0->setValue(m_y0);
	m_ui.sbX1->setValue(m_x1);
	m_ui.sbY1->setValue(m_y1);

	m_n64Pos = 0;
	m_n64MaxPos = 0;
	updatePlayMediaFileProgress();

	m_nRoomSize = 0;

	m_pTimer = new QTimer(this);
	m_pDelayUpdateTimer = new QTimer(this);
	m_pFillFrameTimer = new QTimer(this);
	m_pPlayMediaFileTimer = new QTimer(this);

	m_nCurSelectedMember = -1;

	m_pMenuInviteInteract = new QMenu(this);
	QAction* pActInviteInteract = new QAction( QString::fromLocal8Bit("连麦"), m_pMenuInviteInteract );
	m_pMenuInviteInteract->addAction(pActInviteInteract);
	m_pMenuCancelInteract = new QMenu(this);
	QAction* pActCancelInteract = new QAction( QString::fromLocal8Bit("断开"), m_pMenuInviteInteract );
	m_pMenuCancelInteract->addAction(pActCancelInteract);

	m_channelId = 0;

	m_bRoomDisconnectClose = false;

	m_bRecording = false;
	m_bPushing = false;

	connect( m_ui.btnOpenCamera, SIGNAL(clicked()), this, SLOT(OnBtnOpenCamera()) );
	connect( m_ui.btnCloseCamera, SIGNAL(clicked()), this, SLOT(OnBtnCloseCamera()) );
	connect( m_ui.btnOpenExternalCapture, SIGNAL(clicked()), this, SLOT(OnBtnOpenExternalCapture()) );
	connect( m_ui.btnCloseExternalCapture, SIGNAL(clicked()), this, SLOT(OnBtnCloseExternalCapture()) );
	connect( m_ui.btnOpenMic, SIGNAL(clicked()), this, SLOT(OnBtnOpenMic()) );
	connect( m_ui.btnCloseMic, SIGNAL(clicked()), this, SLOT(OnBtnCloseMic()) );
	connect( m_ui.btnOpenPlayer, SIGNAL(clicked()), this, SLOT(OnBtnOpenPlayer()) );
	connect( m_ui.btnClosePlayer, SIGNAL(clicked()), this, SLOT(OnBtnClosePlayer()) );
	connect( m_ui.btnOpenScreenShareArea, SIGNAL(clicked()), this, SLOT(OnBtnOpenScreenShareArea()) );
	connect( m_ui.btnOpenScreenShareWnd, SIGNAL(clicked()), this, SLOT(OnBtnOpenScreenShareWnd()) );
	connect( m_ui.btnUpdateScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnUpdateScreenShare()) );
	connect( m_ui.btnCloseScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnCloseScreenShare()) );
	connect( m_ui.btnOpenSystemVoiceInput, SIGNAL(clicked()), this, SLOT(OnBtnOpenSystemVoiceInput()) );
	connect( m_ui.btnCloseSystemVoiceInput, SIGNAL(clicked()), this, SLOT(OnBtnCloseSystemVoiceInput()) );
	connect( m_ui.btnSendGroupMsg, SIGNAL(clicked()), this, SLOT(OnBtnSendGroupMsg()) );
	connect( m_ui.btnStartRecord, SIGNAL(clicked()), this, SLOT(OnBtnStartRecord()) );
	connect( m_ui.btnStopRecord, SIGNAL(clicked()), this, SLOT(OnBtnStopRecord()) );
	connect( m_ui.btnStartPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStartPushStream()) );
	connect( m_ui.btnStopPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStopPushStream()) );
	connect( m_ui.btnPraise, SIGNAL(clicked()), this, SLOT(OnBtnPraise()) );
	connect( m_ui.btnSelectMediaFile, SIGNAL(clicked()), this, SLOT(OnBtnSelectMediaFile()) );
	connect( m_ui.btnPlayMediaFile, SIGNAL(clicked()), this, SLOT(OnBtnPlayMediaFile()) );
	connect( m_ui.btnStopMediaFile, SIGNAL(clicked()), this, SLOT(OnBtnStopMediaFile()) );
	connect( m_ui.hsPlayerVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsPlayerVol(int)) );
	connect( m_ui.sbPlayerVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbPlayerVol(int)) );
	connect( m_ui.hsMicVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsMicVol(int)) );
	connect( m_ui.sbMicVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbMicVol(int)) );
	connect( m_ui.hsSystemVoiceInputVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsSystemVoiceInputVol(int)) );
	connect( m_ui.sbSystemVoiceInputVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbSystemVoiceInputVol(int)) );
	connect( m_ui.vsSkinSmooth, SIGNAL(valueChanged(int)), this, SLOT(OnVsSkinSmoothChanged(int)) );
	connect( m_ui.sbSkinSmooth, SIGNAL(valueChanged(int)), this, SLOT(OnSbSkinSmoothChanged(int)) );
	connect( m_ui.vsSkinWhite, SIGNAL(valueChanged(int)), this, SLOT(OnVsSkinWhiteChanged(int)) );
	connect( m_ui.sbSkinWhite, SIGNAL(valueChanged(int)), this, SLOT(OnSbSkinWhiteChanged(int)) );
	connect( m_ui.hsMediaFileRate, SIGNAL(valueChanged(int)), this, SLOT(OnHsMediaFileRateChanged(int)) );
	connect( m_pTimer, SIGNAL(timeout()), this, SLOT(OnHeartBeatTimer()) );
	connect( m_pDelayUpdateTimer, SIGNAL(timeout()), this, SLOT(OnDelayUpdateTimer()) );
	connect( m_pFillFrameTimer, SIGNAL(timeout()), this, SLOT(OnFillFrameTimer()) );
	connect( m_pPlayMediaFileTimer, SIGNAL(timeout()), this, SLOT(OnPlayMediaFileTimer()) );
	connect( pActInviteInteract, SIGNAL(triggered()), this, SLOT(OnActInviteInteract()) );
	connect( pActCancelInteract, SIGNAL(triggered()), this, SLOT(OnActCancelInteract()) );	
}

void Live::setRoomID( int roomID )
{
	m_ui.sbRoomID->setValue(roomID);
	mRoomId = roomID;
}

void Live::setRoomUserType( E_RoomUserType userType )
{
	m_userType = userType;
	m_ui.SkinGB->setVisible(false);
	updateMsgs();
	updateCameraGB();
	updatePlayerGB();
	updateExternalCaptureGB();
	updateMicGB();
	updateScreenShareGB();
	updateSystemVoiceInputGB();
	updateMediaFilePlayGB();
	updateRecordGB();
	updatePushStreamGB();
	switch(m_userType)
	{
	case E_RoomUserCreator:
		{
			this->setWindowTitle( QString::fromLocal8Bit("主播") );
			m_ui.cameraGB->setVisible(true);
			m_ui.externalCaptureGB->setVisible(true);
			m_ui.microphoneGB->setVisible(true);
			m_ui.screenShareGB->setVisible(true);
			m_ui.SystemVoiceInputGB->setVisible(true);
			m_ui.MediaFileGB->setVisible(true);
			m_ui.recordGB->setVisible(true);
			m_ui.pushStreamGB->setVisible(true);
			m_ui.lbPraiseNum->setVisible(true);
			m_ui.btnPraise->setVisible(false);
			if ( m_ui.cbCamera->count() > 0 ) OnBtnOpenCamera();//主播创建房间后，自动打开摄像头
			break;
		}
	case E_RoomUserJoiner:
		{
			this->setWindowTitle( QString::fromLocal8Bit("连麦者") );
			m_ui.cameraGB->setVisible(true);
			m_ui.externalCaptureGB->setVisible(true);
			m_ui.microphoneGB->setVisible(true);
			m_ui.screenShareGB->setVisible(true);
			m_ui.SystemVoiceInputGB->setVisible(true);
			m_ui.MediaFileGB->setVisible(true);
			m_ui.recordGB->setVisible(false);
			m_ui.pushStreamGB->setVisible(false);
			m_ui.lbPraiseNum->setVisible(false);
			m_ui.btnPraise->setVisible(true);
			break;
		}
	case E_RoomUserWatcher:
		{
			this->setWindowTitle( QString::fromLocal8Bit("观众") );
			m_ui.cameraGB->setVisible(false);
			m_ui.externalCaptureGB->setVisible(false);
			m_ui.microphoneGB->setVisible(false);
			m_ui.screenShareGB->setVisible(false);
			m_ui.SystemVoiceInputGB->setVisible(false);
			m_ui.MediaFileGB->setVisible(false);
			m_ui.recordGB->setVisible(false);
			m_ui.pushStreamGB->setVisible(false);
			m_ui.lbPraiseNum->setVisible(false);
			m_ui.btnPraise->setVisible(true);
			break;
		}
	}
}

void Live::ChangeRoomUserType()
{
	if (m_userType==E_RoomUserWatcher)
	{
		OnAcceptInteract();
	}
	else if(m_userType==E_RoomUserJoiner)
	{
		OnExitInteract();
	}
}

void Live::dealMessage( const Message& message )
{
	std::string szSender = message.sender.c_str();	
	for (int i = 0; i < message.elems.size(); ++i)
	{
		MessageElem *pElem = message.elems[i];
		switch( pElem->type )
		{
		case TEXT:
			{
				QString szShow = QString::fromStdString( szSender + ": " );
				MessageTextElem *elem = dynamic_cast<MessageTextElem*>(pElem);
				addMsgLab( szShow + elem->content.c_str() );
				break;
			}
		case CUSTOM:
			{
				MessageCustomElem *elem = dynamic_cast<MessageCustomElem*>(pElem);
				std::string szExt = elem->ext.c_str();
				//if (szExt==LiveNoti) //当前版本暂不启用此信令标记,待三个平台一起启用
				{
					std::string szDate = elem->data.c_str();
					parseCusMessage(szSender, szDate);
				}
				break;
			}
		default:
			break;
		}
	}
}

void Live::parseCusMessage( const std::string& sender, std::string msg )
{
	QString qmsg = QString::fromStdString(msg);
	QJsonDocument doc = QJsonDocument::fromJson( qmsg.toLocal8Bit() );
	if (doc.isObject())
	{
		QJsonObject obj = doc.object();
		QVariantMap varmap = obj.toVariantMap();
		int nUserAction = AVIMCMD_None;
		QString szActionParam;
		if ( varmap.contains("userAction") )
		{
			nUserAction = varmap.value("userAction").toInt();
		}
		if ( varmap.contains("actionParam") )
		{
			szActionParam = varmap.value("actionParam").toString();
		}
		dealCusMessage( sender, nUserAction, szActionParam);
	}
}

void Live::dealCusMessage( const std::string& sender, int nUserAction, QString szActionParam )
{
	switch(nUserAction)
	{
	case AVIMCMD_Multi_Host_Invite: //观众收到连麦邀请
		{
			if ( sender != g_pMainWindow->getCurRoomInfo().szId.toStdString() )//过滤下非主播发过来的信令
			{
				break;
			}
			QMessageBox::StandardButton ret = QMessageBox::question(this, FromBits("邀请"), FromBits("主播邀请你上麦，是否接受?") );
			if ( ret == QMessageBox::Yes )
			{
				acceptInteract();
			}
			else
			{
				refuseInteract();
			}
			break;
		}
	case AVIMCMD_Multi_CancelInteract: //观众收到下线命令
		{
			if ( m_userType==E_RoomUserJoiner && szActionParam==g_pMainWindow->getUserId() ) //被命令下麦的连麦者
			{
				exitInteract();
			}
			else
			{
				updateLater();
			}
			break;
		}
	case AVIMCMD_Multi_Interact_Join: //主播收到观众接受连麦请求的回复
		{
			sxbRoomIdList(); //重新请求列表
			break;
		}
	case AVIMCMD_Multi_Interact_Refuse://主播收到观众拒绝连麦请求的回复
		{
			ShowTips( FromBits("提示"), szActionParam+FromBits("拒绝了你的连麦请求."), this);
			break;
		}
	case AVIMCMD_EnterLive:
		{
			int i;
			for (i=0; i<m_roomMemberList.size(); ++i)
			{
				if (m_roomMemberList[i].szID==szActionParam)
				{
					break;
				}
			}
			if ( i==m_roomMemberList.size() )
			{
				RoomMember roomMember;
				roomMember.szID = szActionParam;
				roomMember.userType = E_RoomUserWatcher;
				m_roomMemberList.push_back(roomMember);
				m_nRoomSize++;
				updateMemberList();
			}
			addMsgLab( QString::fromStdString(sender)+FromBits("加入房间") );
			break;
		}
	case AVIMCMD_ExitLive:
		{
			if (m_userType != E_RoomUserCreator)
			{
				close();
				ShowTips( FromBits("主播退出房间"), FromBits("主播已经退出房间."), g_pMainWindow );
			}
			break;
		}
	case AVIMCMD_Praise:
		{
			if (m_userType==E_RoomUserCreator)
			{
				g_pMainWindow->increasePraise();
				m_ui.lbPraiseNum->setText( FromBits("点赞数: ")+QString::number(g_pMainWindow->getCurRoomInfo().info.thumbup) );
			}
			addMsgLab( szActionParam+FromBits("点赞+1") );
			break;
		}
	default:
		break;
	}
}

void Live::StartTimer()
{
	sxbRoomIdList();
	m_pTimer->start(10000); //随心播后台要求10秒上报一次心跳
}

void Live::stopTimer()
{
	m_pTimer->stop();
}

void Live::updateLater(int msec)
{
	m_pDelayUpdateTimer->start(msec);
}

void Live::OnMemStatusChange( E_EndpointEventId event_id, const Vector<String> &ids, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	switch(event_id)
	{
	case EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO:
		{
			std::vector<std::string> list;
			for (auto i = ids.begin(); i != ids.end(); ++i)
			{
				list.push_back( std::string(i->c_str()) );
			}
			pLive->freeCameraVideoRenders(list);
			break;
		}
	case EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO:
	case EVENT_ID_ENDPOINT_NO_MEDIA_VIDEO:
		{
			pLive->freeScreenVideoRender();
			break;
		}
	default:
		break;
	}
}

void Live::OnRoomDisconnect( int reason, const char *errorinfo, void* data )
{
	Live* pThis = reinterpret_cast<Live*>(data);
	pThis->m_bRoomDisconnectClose = true;
	pThis->close();
	ShowCodeErrorTips( reason, errorinfo, pThis, FromBits("已被强制退出房间.") );
}

void Live::OnDeviceDetect( void* data )
{
	Live* pThis = reinterpret_cast<Live*>(data);
	pThis->updateCameraGB();
	pThis->updateMicGB();
	pThis->updatePlayerGB();
}

void Live::OnLocalVideo( const LiveVideoFrame* video_frame, void* custom_data )
{
	Live* pLive = reinterpret_cast<Live*>(custom_data);

	if(video_frame->desc.srcType == VIDEO_SRC_TYPE_SCREEN || video_frame->desc.srcType == VIDEO_SRC_TYPE_MEDIA)
	{
		pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if (video_frame->desc.srcType == VIDEO_SRC_TYPE_CAMERA)
	{
		pLive->m_pLocalCameraRender->DoRender(video_frame);
	}
}

void Live::OnRemoteVideo( const LiveVideoFrame* video_frame, void* custom_data )
{
	Live* pLive = reinterpret_cast<Live*>(custom_data);
	if (video_frame->desc.srcType == VIDEO_SRC_TYPE_SCREEN || video_frame->desc.srcType == VIDEO_SRC_TYPE_MEDIA)
	{
		pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if(video_frame->desc.srcType == VIDEO_SRC_TYPE_CAMERA)
	{
		VideoRender* pRender = pLive->getVideoRender(video_frame->identifier.c_str());
		if (pRender)
		{
			pRender->DoRender(video_frame);
		}
		else
		{
			//iLiveLog_e("suixinbo", "Render is not enough.");
		}
	}
}

void Live::OnMessage( const Message& msg, void* data )
{
	Live* pThis = reinterpret_cast<Live*>(data);
	if ( pThis->isVisible() )
	{
		pThis->dealMessage(msg);
	}
}

void Live::OnDeviceOperation( E_DeviceOperationType oper, int retCode, void* data )
{
	Live* pThis = reinterpret_cast<Live*>(data);
	switch(oper)
	{
	case E_OpenCamera:
		{
			pThis->OnOpenCameraCB(retCode);
			break;
		}
	case E_CloseCamera:
		{
			pThis->OnCloseCameraCB(retCode);
			break;
		}
	case E_OpenExternalCapture:
		{
			pThis->OnOpenExternalCaptureCB(retCode);
			break;
		}
	case E_CloseExternalCapture:
		{
			pThis->OnCloseExternalCaptureCB(retCode);
			break;
		}
	case E_OpenMic:
		{
			pThis->OnOpenMicCB(retCode);
			break;
		}
	case E_CloseMic:
		{
			pThis->OnCloseMicCB(retCode);
			break;
		}
	case E_OpenPlayer:
		{
			pThis->OnOpenPlayerCB(retCode);
			break;
		}
	case E_ClosePlayer:
		{
			pThis->OnClosePlayerCB(retCode);
			break;
		}
	case E_OpenScreenShare:
		{
			pThis->OnOpenScreenShareCB(retCode);
			break;
		}
	case E_CloseScreenShare:
		{
			pThis->OnCloseScreenShareCB(retCode);
			break;
		}
	case E_OpenSystemVoiceInput:
		{
			pThis->OnOpenSystemVoiceInputCB(retCode);
			break;
		}
	case E_CloseSystemVoiceInput:
		{
			pThis->OnCloseSystemVoiceInputCB(retCode);
			break;
		}
	case E_OpenPlayMediaFile:
		{
			pThis->OnOpenPlayMediaFileCB(retCode);
			break;
		}
	case E_ClosePlayMediaFile:
		{
			pThis->OnClosePlayMediaFileCB(retCode);
			break;
		}
	}
}

void Live::OnBtnOpenCamera()
{
	if (m_cameraList.size()==0)
	{
		ShowErrorTips( FromBits("无可用的摄像头."), this );
		return;
	}
	m_ui.btnOpenCamera->setEnabled(false);
	int ndx = m_ui.cbCamera->currentIndex();
	GetILive()->openCamera(m_cameraList[ndx].first.c_str());
}

void Live::OnBtnCloseCamera()
{
	m_ui.btnCloseCamera->setEnabled(false);
	GetILive()->closeCamera();
}

void Live::OnBtnOpenExternalCapture()
{
	m_ui.btnOpenExternalCapture->setEnabled(false);
	GetILive()->openExternalCapture();
}

void Live::OnBtnCloseExternalCapture()
{
	m_ui.btnCloseExternalCapture->setEnabled(false);
	GetILive()->closeExternalCapture();
}

void Live::OnBtnOpenMic()
{
	m_ui.btnOpenMic->setEnabled(false);
	
	Vector< Pair<String/*id*/, String/*name*/> > micList;
	int nRet = GetILive()->getMicList(micList);
	if (nRet != NO_ERR)
	{
		m_ui.btnOpenMic->setEnabled(true);
		ShowCodeErrorTips(nRet, "get Mic List Failed.", this );
		return;
	}
	GetILive()->openMic(micList[0].first);
}

void Live::OnBtnCloseMic()
{
	m_ui.btnCloseMic->setEnabled(false);
	GetILive()->closeMic();
}

void Live::OnBtnOpenPlayer()
{
	m_ui.btnOpenPlayer->setEnabled(false);
	Vector< Pair<String, String> > playerList;
	int nRet = GetILive()->getPlayerList(playerList);
	if (nRet!=NO_ERR)
	{
		m_ui.btnOpenPlayer->setEnabled(true);
		ShowCodeErrorTips(nRet, "Get Player List Failed.", this );
		return;
	}
	GetILive()->openPlayer( playerList[0].first );
}

void Live::OnBtnClosePlayer()
{
	m_ui.btnClosePlayer->setEnabled(false);
	GetILive()->closePlayer();
}

void Live::OnBtnOpenScreenShareArea()
{
	m_ui.btnOpenScreenShareArea->setEnabled(false);
	m_x0 = m_ui.sbX0->value();
	m_y0 = m_ui.sbY0->value();
	m_x1 = m_ui.sbX1->value();
	m_y1 = m_ui.sbY1->value();
	GetILive()->openScreenShare(m_x0, m_y0, m_x1, m_y1, m_fps);
}

void Live::OnBtnOpenScreenShareWnd()
{
	m_ui.btnOpenScreenShareWnd->setEnabled(false);
	
	HWND hwnd = WndList::GetSelectWnd();
	if ( !hwnd )
	{
		m_ui.btnOpenScreenShareWnd->setEnabled(true);
		return;
	}
	GetILive()->openScreenShare( hwnd, m_fps );
}

void Live::OnBtnUpdateScreenShare()
{
	m_ui.btnUpdateScreenShare->setEnabled(false);
	
	m_x0 = m_ui.sbX0->value();
	m_y0 = m_ui.sbY0->value();
	m_x1 = m_ui.sbX1->value();
	m_y1 = m_ui.sbY1->value();

	int nRet = GetILive()->changeScreenShareSize( m_x0, m_y0, m_x1, m_y1 );
	if (nRet != NO_ERR)
	{
		m_ui.btnUpdateScreenShare->setEnabled(true);
		ShowCodeErrorTips( nRet, "changeScreenShareAreaSize failed.", this );
		return;
	}
	updateScreenShareGB();
}

void Live::OnBtnCloseScreenShare()
{
	m_ui.btnCloseScreenShare->setEnabled(false);
	GetILive()->closeScreenShare();
}

void Live::OnBtnOpenSystemVoiceInput()
{
	m_ui.btnOpenSystemVoiceInput->setEnabled(false);
	GetILive()->openSystemVoiceInput();
}

void Live::OnBtnCloseSystemVoiceInput()
{
	m_ui.btnCloseSystemVoiceInput->setEnabled(false);
	GetILive()->closeSystemVoiceInput();
}

void Live::OnBtnSendGroupMsg()
{
	QString szText = m_ui.teEditText->toPlainText();
	m_ui.teEditText->setPlainText("");
	if ( szText.isEmpty() )
	{
		return;
	}

	Message msg;
	MessageTextElem *elem = new MessageTextElem(String(szText.toStdString().c_str()));
	msg.elems.push_back(elem);
	addMsgLab( QString::fromLocal8Bit("我说：") + szText );
	GetILive()->sendGroupMessage(  msg, OnSendGroupMsgSuc, OnSendGroupMsgErr, this );
}

void Live::OnBtnStartRecord()
{
	bool bClickedOK;
	m_inputRecordName = QInputDialog::getText( this, FromBits("录制文件名"),FromBits("请输入录制文件名"), QLineEdit::Normal, "", &bClickedOK );
	if (!bClickedOK)//用户点击了取消按钮
	{
		return;
	}
	if ( m_inputRecordName.isEmpty() )
	{
		ShowErrorTips( FromBits("录制文件名不能为空"), this );
		return;
	}	
	//随心播后台要求录制文件名统一格式"sxb_用户id_用户传入的文件名"
	QString fileName = "sxb_";
	fileName += g_pMainWindow->getUserId();
	fileName += "_";
	fileName += m_inputRecordName;
	
	m_recordOpt.fileName = fileName.toStdString().c_str();
	m_recordOpt.recordDataType = (E_RecordDataType)m_ui.cbRecordDataType->itemData( m_ui.cbRecordDataType->currentIndex() ).value<int>();
	GetILive()->startRecord(m_recordOpt, OnStartRecordVideoSuc, OnStartRecordVideoErr, this);
}

void Live::OnBtnStopRecord()
{
	GetILive()->stopRecord( OnStopRecordSuc, OnStopRecordVideoErr, this);
}

void Live::OnBtnStartPushStream()
{
	m_pushOpt.pushDataType = (E_PushDataType)m_ui.cbPushDataType->itemData( m_ui.cbPushDataType->currentIndex() ).value<int>();
	m_pushOpt.encode = (E_iLiveStreamEncode)m_ui.cbPushEncodeType->itemData( m_ui.cbPushEncodeType->currentIndex() ).value<int>();
	m_pushOpt.recordFileType = RecordFile_NONE;
	GetILive()->startPushStream( m_pushOpt, OnStartPushStreamSuc, OnStartPushStreamErr, this );
}

void Live::OnBtnStopPushStream()
{
	GetILive()->stopPushStream(m_channelId, OnStopPushStreamSuc, OnStopPushStreamErr, this);
}

void Live::OnBtnPraise()
{
	g_sendGroupCustomCmd( AVIMCMD_Praise, g_pMainWindow->getUserId() );
	addMsgLab( g_pMainWindow->getUserId()+FromBits("点赞") );
}

void Live::OnBtnSelectMediaFile()
{
	QString szMediaPath = QFileDialog::getOpenFileName( this, FromBits("请选择播放的视频文件"), "", FromBits("视频文件(*.aac *.ac3 *.amr *.ape *.mp3 *.flac *.midi *.wav *.wma *.ogg *.amv *.mkv *.mod *.mts *.ogm *.f4v *.flv *.hlv *.asf *.avi *.wm *.wmp *.wmv *.ram *.rm *.rmvb *.rpm *.rt *.smi *.dat *.m1v *.m2p *.m2t *.m2ts *.m2v *.mp2v *.tp *.tpr *.ts *.m4b *.m4p *.m4v *.mp4 *.mpeg4 *.3g2 *.3gp *.3gp2 *.3gpp *.mov *.pva *.dat *.m1v *.m2p *.m2t *.m2ts *.m2v *.mp2v *.pss *.pva *.ifo *.vob *.divx *.evo *.ivm *.mkv *.mod *.mts *.ogm *.scm *.tod *.vp6 *.webm *.xlmv)") );
	if ( !szMediaPath.isEmpty() )
	{
		m_ui.edMediaFilePath->setText(szMediaPath);
	}
}

void Live::OnBtnPlayMediaFile()
{
	E_PlayMediaFileState state = GetILive()->getPlayMediaFileState();
	if ( state == E_PlayMediaFileStop )//停止->播放
	{
		doStartPlayMediaFile();
	}
	else if ( state==E_PlayMediaFilePlaying ) //播放->暂停
	{
		doPausePlayMediaFile();
	}
	else if ( state==E_PlayMediaFilePause )//暂停->恢复播放
	{
		doResumePlayMediaFile();
	}
}

void Live::OnBtnStopMediaFile()
{
	E_PlayMediaFileState state = GetILive()->getPlayMediaFileState();
	if (state == E_PlayMediaFileStop)
	{
		return;
	}
	doStopPlayMediaFile();
}

void Live::OnHsPlayerVol( int value )
{
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.sbPlayerVol->setValue(value);
	m_ui.sbPlayerVol->blockSignals(false);

	GetILive()->setPlayerVolume(value);
}

void Live::OnSbPlayerVol( int value )
{
	m_ui.hsPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->setValue(value);
	m_ui.hsPlayerVol->blockSignals(false);

	GetILive()->setPlayerVolume(value);
}

void Live::OnHsMicVol( int value )
{
	m_ui.sbMicVol->blockSignals(true);
	m_ui.sbMicVol->setValue(value);
	m_ui.sbMicVol->blockSignals(false);

	GetILive()->setMicVolume(value);
}

void Live::OnSbMicVol( int value )
{
	m_ui.hsMicVol->blockSignals(true);
	m_ui.hsMicVol->setValue(value);
	m_ui.hsMicVol->blockSignals(false);

	GetILive()->setMicVolume(value);
}

void Live::OnHsSystemVoiceInputVol( int value )
{
	m_ui.sbSystemVoiceInputVol->blockSignals(true);
	m_ui.sbSystemVoiceInputVol->setValue(value);
	m_ui.sbSystemVoiceInputVol->blockSignals(false);

	GetILive()->setSystemVoiceInputVolume(value);
}

void Live::OnSbSystemVoiceInputVol( int value )
{
	m_ui.hsSystemVoiceInputVol->blockSignals(true);
	m_ui.hsSystemVoiceInputVol->setValue(value);
	m_ui.hsSystemVoiceInputVol->blockSignals(false);

	GetILive()->setSystemVoiceInputVolume(value);
}

void Live::OnVsSkinSmoothChanged( int value )
{
	m_ui.sbSkinSmooth->blockSignals(true);
	m_ui.sbSkinSmooth->setValue(value);
	m_ui.sbSkinSmooth->blockSignals(false);
	iLiveSetSkinSmoothGrade(value);
}

void Live::OnSbSkinSmoothChanged( int value )
{
	m_ui.vsSkinSmooth->blockSignals(true);
	m_ui.vsSkinSmooth->setValue(value);
	m_ui.vsSkinSmooth->blockSignals(false);
	iLiveSetSkinSmoothGrade(value);
}

void Live::OnVsSkinWhiteChanged( int value )
{
	m_ui.sbSkinWhite->blockSignals(true);
	m_ui.sbSkinWhite->setValue(value);
	m_ui.sbSkinWhite->blockSignals(false);
	iLiveSetSkinWhitenessGrade(value);
}

void Live::OnSbSkinWhiteChanged( int value )
{
	m_ui.vsSkinWhite->blockSignals(true);
	m_ui.vsSkinWhite->setValue(value);
	m_ui.vsSkinWhite->blockSignals(false);
	iLiveSetSkinWhitenessGrade(value);
}

void Live::OnHsMediaFileRateChanged( int value )
{
	int nRet = GetILive()->setPlayMediaFilePos(value);
	if (nRet != NO_ERR)
	{
		ShowCodeErrorTips(nRet, FromBits("设置播放进度失败"), this);
	}
}

void Live::OnHeartBeatTimer()
{
	sxbHeartBeat();
	sxbRoomIdList();
}

void Live::OnDelayUpdateTimer()
{
	m_pDelayUpdateTimer->stop();
	this->update();
}

void Live::OnFillFrameTimer()
{
	////////////////////////////////////////////////
	//这里演示自定义采集，读取一张本地图片，每一帧都传入此图片作为输入数据
	HBITMAP hbitmap = (HBITMAP)LoadImageA(NULL, "ExternalCapture.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION );
	if (!hbitmap)
	{
		return;
	}

	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap );

	/////////////////输出文字到图片上start////////////////
	HDC hDC = GetDC( (HWND)(this->winId()) );
	HDC hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC, hbitmap);

	char chFont[20];
	HFONT hfont = CreateFontA( 100, 0, 0, 0, 400, 0, 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,	DEFAULT_QUALITY, DEFAULT_PITCH|FF_DONTCARE, chFont);
	
	SelectObject(hMemDC, hfont);
	TextOutA( hMemDC, 0, 0, "这是自定义采集的画面", strlen("这是自定义采集的画面") );

	DeleteObject(hfont);
	DeleteObject(hMemDC);
	ReleaseDC( (HWND)(this->winId()), hDC );
	/////////////////输出文字到图片上end////////////////

	LiveVideoFrame frame;
	frame.data = (uint8*)bitmap.bmBits;	
	frame.dataSize = bitmap.bmWidth * bitmap.bmHeight * 3;
	frame.desc.colorFormat = COLOR_FORMAT_RGB24;
	frame.desc.width = bitmap.bmWidth;
	frame.desc.height = bitmap.bmHeight;
	frame.desc.rotate = 0;

	int nRet = GetILive()->fillExternalCaptureFrame(frame);
	if (nRet!=NO_ERR)
	{
		m_pFillFrameTimer->stop();
		if (nRet != NO_ERR)
		{
			ShowCodeErrorTips( nRet, FromBits("自定义采集视频输入出错"), this );
		}
	}

	DeleteObject(hbitmap);
}

void Live::OnPlayMediaFileTimer()
{
	int nRet = GetILive()->getPlayMediaFilePos(m_n64Pos, m_n64MaxPos);
	if (nRet == NO_ERR)
	{
		if (m_n64Pos >= m_n64MaxPos)
		{
			int nRet = GetILive()->restartMediaFile();
			if (nRet != NO_ERR)
			{
				m_pPlayMediaFileTimer->stop();
				ShowErrorTips( FromBits("自动重播失败"), this );
			}
		}
		updatePlayMediaFileProgress();
	}
	else
	{
		//Just do nothing.
	}
}

void Live::closeEvent( QCloseEvent* event )
{
	if ( !m_bRoomDisconnectClose )
	{
		if (m_userType==E_RoomUserCreator)//主播退出房间需要向随心播服务器上报退出房间
		{
			sendQuitRoom();
			sxbCreatorQuitRoom();
		}
		else//观众和连麦观众只需要向随心播服务器上报自己的ID
		{
			sxbWatcherOrJoinerQuitRoom();
		}
	}
	else
	{
		g_pMainWindow->setUseable(true);
	}
	m_bRecording = false;
	m_bPushing = false;
	m_bRoomDisconnectClose = false;
	m_szMsgs = "";
	freeAllCameraVideoRender();	
	stopTimer();
	if ( m_pFillFrameTimer->isActive() )
	{
		m_pFillFrameTimer->stop();
	}
	if ( m_pPlayMediaFileTimer->isActive() )
	{
		m_pPlayMediaFileTimer->stop();
	}
	event->accept();
}

void Live::updateCameraList()
{
	GetILive()->getCameraList(m_cameraList);
	m_ui.cbCamera->clear();
	for(int i=0; i<m_cameraList.size(); ++i)
	{
		m_ui.cbCamera->addItem( QString::fromStdString(m_cameraList[i].second.c_str()) );
	}
	m_ui.cbCamera->setCurrentIndex(0);
}

VideoRender* Live::getVideoRender( std::string szIdentifier )
{
	for(int i=0; i<MaxVideoRender; ++i)
	{
		if (m_arrRemoteIdentifiers[i]==szIdentifier)
		{
			return m_pRemoteVideoRenders[i];
		}
	}
	for(int i=0; i<MaxVideoRender; ++i)
	{
		if (m_bRemoteVideoRenderFrees[i])
		{
			m_bRemoteVideoRenderFrees[i] = false;
			m_arrRemoteIdentifiers[i] = szIdentifier;
			return m_pRemoteVideoRenders[i];
		}
	}
	return NULL;
}

void Live::freeCameraVideoRenders( std::vector<std::string> arrNeedFreeRenders )
{
	for (size_t i=0; i<arrNeedFreeRenders.size(); ++i)
	{
		for (size_t j = 0; j<m_arrRemoteIdentifiers.size(); ++j)
		{
			std::string str1 = m_arrRemoteIdentifiers[j];
			std::string str2 = arrNeedFreeRenders[i];
			if (str1 == str2)
			{
				m_arrRemoteIdentifiers[j] = "";
				m_bRemoteVideoRenderFrees[j] = true;
				m_pRemoteVideoRenders[j]->update();
			}
		}
	}
	updateLater();
}

void Live::freeAllCameraVideoRender()
{
	m_pLocalCameraRender->Clear();
	m_pScreenShareRender->Clear();
	m_pLocalCameraRender->exitFullScreen();
	m_pScreenShareRender->exitFullScreen();
	m_pLocalCameraRender->recoverRender();
	m_pScreenShareRender->recoverRender();
	for (int i=0; i<MaxVideoRender; ++i)
	{
		m_pRemoteVideoRenders[i]->Clear();
		m_pRemoteVideoRenders[i]->exitFullScreen();
		m_pRemoteVideoRenders[i]->recoverRender();
		m_arrRemoteIdentifiers[i] = "";
		m_bRemoteVideoRenderFrees[i] = true;
	}
}

void Live::freeScreenVideoRender()
{
	m_pScreenShareRender->Clear();
	m_pScreenShareRender->update();
	updateLater();
}

void Live::addMsgLab( QString msg )
{
	const int nMaxLen = 2000;
	m_szMsgs += msg;
	m_szMsgs += "\n";
	if ( m_szMsgs.length() > nMaxLen )
	{
		m_szMsgs = m_szMsgs.right(nMaxLen);
	}
	updateMsgs();
}

void Live::updateMemberList()
{
	m_ui.sbTotalMemNum->setValue(m_nRoomSize);
	m_ui.liMembers->clear();
	for (int i=0; i<m_roomMemberList.size(); ++i)
	{
		RoomMember& member = m_roomMemberList[i];
		QString szShowName = member.szID;
		switch(member.userType)
		{
		case E_RoomUserJoiner:
			szShowName += QString::fromLocal8Bit("(连麦)");
			break;
		case E_RoomUserCreator:
			szShowName += QString::fromLocal8Bit("(主播)");
			break;
		case E_RoomUserWatcher:
			break;
		}
		m_ui.liMembers->addItem( new QListWidgetItem(szShowName) );
	}
}

void Live::updateMsgs()
{
	m_ui.teMsgs->setPlainText( m_szMsgs );
	QTextCursor cursor = m_ui.teMsgs->textCursor();
	cursor.movePosition(QTextCursor::End);
	m_ui.teMsgs->setTextCursor(cursor);
}

void Live::updateCameraGB()
{
	if ( GetILive()->getExternalCaptureState() )
	{
		m_ui.cameraGB->setEnabled(false);
	}
	else
	{
		m_ui.cameraGB->setEnabled(true);
	}

	if ( GetILive()->getCurCameraState() )
	{
		m_ui.btnOpenCamera->setEnabled(false);
		m_ui.btnCloseCamera->setEnabled(true);
	}
	else
	{
		m_ui.btnOpenCamera->setEnabled(true);
		m_ui.btnCloseCamera->setEnabled(false);
		updateCameraList();
	}
}

void Live::updatePlayerGB()
{
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->blockSignals(true);

	if ( GetILive()->getCurPlayerState() )
	{
		m_ui.sbPlayerVol->setEnabled(true);
		m_ui.hsPlayerVol->setEnabled(true);
		uint32 uVol = GetILive()->getPlayerVolume();
		m_ui.sbPlayerVol->setValue(uVol);
		m_ui.hsPlayerVol->setValue(uVol);
		m_ui.btnOpenPlayer->setEnabled(false);
		m_ui.btnClosePlayer->setEnabled(true);
	}
	else
	{
		m_ui.sbPlayerVol->setValue(0);
		m_ui.hsPlayerVol->setValue(0);
		m_ui.sbPlayerVol->setEnabled(false);
		m_ui.hsPlayerVol->setEnabled(false);
		m_ui.btnOpenPlayer->setEnabled(true);
		m_ui.btnClosePlayer->setEnabled(false);
	}

	m_ui.sbPlayerVol->blockSignals(false);
	m_ui.hsPlayerVol->blockSignals(false);
}

void Live::updateExternalCaptureGB()
{
	if ( GetILive()->getCurCameraState() )
	{
		m_ui.externalCaptureGB->setEnabled( false );
	}
	else
	{
		m_ui.externalCaptureGB->setEnabled( true );
	}

	if ( GetILive()->getExternalCaptureState() )
	{
		m_ui.btnOpenExternalCapture->setEnabled(false);
		m_ui.btnCloseExternalCapture->setEnabled(true);
	}
	else
	{
		m_ui.btnOpenExternalCapture->setEnabled(true);
		m_ui.btnCloseExternalCapture->setEnabled(false);
	}
}

void Live::updateMicGB()
{
	m_ui.sbMicVol->blockSignals(true);
	m_ui.hsMicVol->blockSignals(true);

	if ( GetILive()->getCurMicState() )
	{
		m_ui.sbMicVol->setEnabled(true);
		m_ui.hsMicVol->setEnabled(true);
		uint32 uVol = GetILive()->getMicVolume();
		m_ui.sbMicVol->setValue(uVol);
		m_ui.hsMicVol->setValue(uVol);
		m_ui.btnOpenMic->setEnabled(false);
		m_ui.btnCloseMic->setEnabled(true);
	}
	else
	{
		m_ui.sbMicVol->setValue(0);
		m_ui.hsMicVol->setValue(0);
		m_ui.sbMicVol->setEnabled(false);
		m_ui.hsMicVol->setEnabled(false);
		m_ui.btnOpenMic->setEnabled(true);
		m_ui.btnCloseMic->setEnabled(false);
	}

	m_ui.sbMicVol->blockSignals(false);
	m_ui.hsMicVol->blockSignals(false);
}

void Live::updateScreenShareGB()
{
	if ( GetILive()->getPlayMediaFileState() != E_PlayMediaFileStop )
	{
		m_ui.screenShareGB->setEnabled(false);
	}
	else
	{
		m_ui.screenShareGB->setEnabled(true);
	}

	m_ui.sbX0->blockSignals(true);
	m_ui.sbY0->blockSignals(true);
	m_ui.sbX1->blockSignals(true);
	m_ui.sbY1->blockSignals(true);
	m_ui.sbX0->setValue(m_x0);
	m_ui.sbY0->setValue(m_y0);
	m_ui.sbX1->setValue(m_x1);
	m_ui.sbY1->setValue(m_y1);
	m_ui.sbX0->blockSignals(false);
	m_ui.sbY0->blockSignals(false);
	m_ui.sbX1->blockSignals(false);
	m_ui.sbY1->blockSignals(false);

	E_ScreenShareState state = GetILive()->getScreenShareState();
	switch( state )
	{
	case E_ScreenShareNone:
		{
			m_ui.sbX0->setEnabled(true);
			m_ui.sbY0->setEnabled(true);
			m_ui.sbX1->setEnabled(true);
			m_ui.sbY1->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnOpenScreenShareWnd->setEnabled(true);
			m_ui.btnCloseScreenShare->setEnabled(false);
			break;
		}
	case E_ScreenShareArea:
		{
			m_ui.sbX0->setEnabled(true);
			m_ui.sbY0->setEnabled(true);
			m_ui.sbX1->setEnabled(true);
			m_ui.sbY1->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(false);
			m_ui.btnUpdateScreenShare->setEnabled(true);
			m_ui.btnOpenScreenShareWnd->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(true);
			break;
		}
	case E_ScreenShareWnd:
		{
			m_ui.sbX0->setEnabled(false);
			m_ui.sbY0->setEnabled(false);
			m_ui.sbX1->setEnabled(false);
			m_ui.sbY1->setEnabled(false);
			m_ui.btnOpenScreenShareArea->setEnabled(false);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnOpenScreenShareWnd->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(true);
			break;
		}
	}
}

void Live::updateSystemVoiceInputGB()
{
	m_ui.sbSystemVoiceInputVol->blockSignals(true);
	m_ui.hsSystemVoiceInputVol->blockSignals(true);

	if ( GetILive()->getCurSystemVoiceInputState() )
	{
		m_ui.sbSystemVoiceInputVol->setEnabled(true);
		m_ui.hsSystemVoiceInputVol->setEnabled(true);
		uint32 uVol = GetILive()->getSystemVoiceInputVolume();
		m_ui.sbSystemVoiceInputVol->setValue(uVol);
		m_ui.hsSystemVoiceInputVol->setValue(uVol);
		m_ui.btnOpenSystemVoiceInput->setEnabled(false);
		m_ui.btnCloseSystemVoiceInput->setEnabled(true);
	}
	else
	{
		m_ui.sbSystemVoiceInputVol->setValue(0);
		m_ui.hsSystemVoiceInputVol->setValue(0);
		m_ui.sbSystemVoiceInputVol->setEnabled(false);
		m_ui.hsSystemVoiceInputVol->setEnabled(false);
		m_ui.btnOpenSystemVoiceInput->setEnabled(true);
		m_ui.btnCloseSystemVoiceInput->setEnabled(false);
	}

	m_ui.sbSystemVoiceInputVol->blockSignals(false);
	m_ui.hsSystemVoiceInputVol->blockSignals(false);
}

void Live::updateMediaFilePlayGB()
{
	if ( GetILive()->getScreenShareState() != E_ScreenShareNone )
	{
		m_ui.MediaFileGB->setEnabled(false);
	}
	else
	{
		m_ui.MediaFileGB->setEnabled(true);
	}

	E_PlayMediaFileState state = GetILive()->getPlayMediaFileState();
	switch(state)
	{
	case E_PlayMediaFileStop:
		{
			m_ui.btnSelectMediaFile->setEnabled(true);
			m_ui.btnPlayMediaFile->setText( FromBits("播放") );
			m_ui.btnPlayMediaFile->setEnabled(true);
			m_ui.btnStopMediaFile->setEnabled(false);
			m_n64MaxPos = 0;
			m_n64Pos = 0;
			updatePlayMediaFileProgress();
			break;
		}
	case E_PlayMediaFilePlaying:
		{
			m_ui.btnSelectMediaFile->setEnabled(false);
			m_ui.btnPlayMediaFile->setText( FromBits("暂停") );
			m_ui.btnPlayMediaFile->setEnabled(true);
			m_ui.btnStopMediaFile->setEnabled(true);
			break;
		}
	case E_PlayMediaFilePause:
		{
			m_ui.btnSelectMediaFile->setEnabled(false);
			m_ui.btnPlayMediaFile->setText( FromBits("播放") );
			m_ui.btnPlayMediaFile->setEnabled(true);
			m_ui.btnStopMediaFile->setEnabled(true);
			break;
		}
	}
}

void Live::updateRecordGB()
{
	int nRecordDataTypeIndex = m_ui.cbRecordDataType->currentIndex();
	m_ui.cbRecordDataType->clear();

	if ( (!GetILive()->getCurCameraState()) && (!GetILive()->getExternalCaptureState()) 
		&& (!GetILive()->getScreenShareState()) && (!GetILive()->getPlayMediaFileState()) )
	{
		m_ui.recordGB->setEnabled(false);
		return;
	}

	m_ui.recordGB->setEnabled(true);
	if ( m_bRecording )
	{
		m_ui.btnStartRecord->setEnabled(false);
		m_ui.btnStopRecord->setEnabled(true);
		m_ui.cbRecordDataType->setEnabled(false);
	}
	else
	{
		m_ui.btnStartRecord->setEnabled(true);
		m_ui.btnStopRecord->setEnabled(false);
		m_ui.cbRecordDataType->setEnabled(true);
	}

	if ( GetILive()->getCurCameraState() || GetILive()->getExternalCaptureState() )
	{
		m_ui.cbRecordDataType->addItem( FromBits("主路(摄像头/自定义采集)"), QVariant(E_RecordCamera) );
	}
	if ( GetILive()->getScreenShareState() || GetILive()->getPlayMediaFileState() )
	{
		m_ui.cbRecordDataType->addItem( FromBits("辅路(屏幕分享/文件播放)"), QVariant(E_RecordScreen) );
	}
	nRecordDataTypeIndex = iliveMin( m_ui.cbRecordDataType->count()-1, iliveMax(0, nRecordDataTypeIndex) );
	m_ui.cbRecordDataType->setCurrentIndex( nRecordDataTypeIndex );
}

void Live::updatePushStreamGB()
{
	int nPushDataTypeIndex = m_ui.cbPushDataType->currentIndex();
	int nPushEncodeTypeIndex = m_ui.cbPushEncodeType->currentIndex();
	m_ui.cbPushDataType->clear();
	m_ui.cbPushEncodeType->clear();
	m_ui.tePushStreamUrl->setPlainText("");

	if ( (!GetILive()->getCurCameraState()) && (!GetILive()->getExternalCaptureState()) 
		&& (!GetILive()->getScreenShareState()) && (!GetILive()->getPlayMediaFileState()) )
	{
		m_ui.pushStreamGB->setEnabled(false);
		return;
	}

	m_ui.pushStreamGB->setEnabled(true);
	if( m_bPushing )
	{
		m_ui.btnStartPushStream->setEnabled(false);
		m_ui.btnStopPushStream->setEnabled(true);
		m_ui.cbPushDataType->setEnabled(false);
		m_ui.cbPushEncodeType->setEnabled(false);
		QString szUrl;
		for (std::list<LiveUrl>::iterator iter = m_pushUrls.begin(); iter != m_pushUrls.end(); ++iter)
		{
			szUrl += QString::fromStdString( iter->url.c_str() ) + "\n";
		}
		m_ui.tePushStreamUrl->setPlainText(szUrl);
	}
	else
	{
		m_ui.btnStartPushStream->setEnabled(true);
		m_ui.btnStopPushStream->setEnabled(false);
		m_ui.cbPushDataType->setEnabled(true);
		m_ui.cbPushEncodeType->setEnabled(true);
		m_ui.tePushStreamUrl->setPlainText("");
	}

	if ( GetILive()->getCurCameraState() || GetILive()->getExternalCaptureState() )
	{
		m_ui.cbPushDataType->addItem( FromBits("主路(摄像头/自定义采集)"), QVariant(E_PushCamera) );
	}
	if ( GetILive()->getScreenShareState() || GetILive()->getPlayMediaFileState() )
	{
		m_ui.cbPushDataType->addItem( FromBits("辅路(屏幕分享/文件播放)"), QVariant(E_PushScreen) );
	}
	m_ui.cbPushEncodeType->addItem(FromBits("HLS"), QVariant(HLS) );
	m_ui.cbPushEncodeType->addItem(FromBits("RTMP"),QVariant(RTMP) );
	nPushDataTypeIndex = iliveMin( m_ui.cbPushDataType->count()-1, iliveMax(0, nPushDataTypeIndex) );
	nPushEncodeTypeIndex = iliveMin( m_ui.cbPushEncodeType->count()-1, iliveMax(0, nPushEncodeTypeIndex) );
	m_ui.cbPushDataType->setCurrentIndex( nPushDataTypeIndex );
	m_ui.cbPushEncodeType->setCurrentIndex( nPushEncodeTypeIndex );
}

void Live::updatePlayMediaFileProgress()
{
	m_ui.hsMediaFileRate->blockSignals(true);
	m_ui.lbMediaFileRate->setText( getTimeStrBySeconds(m_n64Pos) + "/" + getTimeStrBySeconds(m_n64MaxPos) );
	m_ui.hsMediaFileRate->setMinimum(0);
	m_ui.hsMediaFileRate->setMaximum(m_n64MaxPos);
	m_ui.hsMediaFileRate->setValue(m_n64Pos);
	int nStep = m_n64MaxPos/40;
	nStep = nStep<1?1:nStep;
	m_ui.hsMediaFileRate->setSingleStep(nStep);
	m_ui.hsMediaFileRate->setPageStep(nStep);
	m_ui.hsMediaFileRate->blockSignals(false);
}

void Live::doStartPlayMediaFile()
{
	QString szMediaPath = m_ui.edMediaFilePath->text();

	if ( szMediaPath.isEmpty() )
	{
		ShowErrorTips( FromBits("请先选择要播放的文件"), this );
		return;
	}

	QFile file(szMediaPath);
	if ( !file.exists() )
	{
		ShowErrorTips( FromBits("指定的文件不存在，请重新选择"), this );
		return;
	}

	if ( !GetILive()->isValidMediaFile( szMediaPath.toStdString().c_str() ) )
	{
		ShowErrorTips( FromBits("不支持播放所选文件,请重新选择."), this );
		return;
	}

	GetILive()->openPlayMediaFile( szMediaPath.toStdString().c_str() );
}

void Live::doPausePlayMediaFile()
{
	int nRet = GetILive()->pausePlayMediaFile();
	if (nRet == NO_ERR)
	{
		m_pPlayMediaFileTimer->stop();
		m_ui.btnPlayMediaFile->setText( FromBits("播放") );
	}
	else
	{
		ShowCodeErrorTips(nRet, FromBits("暂停播放出错"), this);
	}
}

void Live::doResumePlayMediaFile()
{
	int nRet = GetILive()->resumePlayMediaFile();
	if (nRet==NO_ERR)
	{
		m_pPlayMediaFileTimer->start(1000);
		m_ui.btnPlayMediaFile->setText( FromBits("暂停") );
	}
	else
	{
		ShowCodeErrorTips(nRet, FromBits("恢复播放出错"), this);
	}
}

void Live::doStopPlayMediaFile()
{
	GetILive()->closePlayMediaFile();
}

void Live::doAutoStopRecord()
{
	if ( m_bRecording )
	{
		int nRecordDataTypeIndex = m_ui.cbRecordDataType->currentIndex();
		E_RecordDataType eSelectedType = (E_RecordDataType)m_ui.cbRecordDataType->itemData(nRecordDataTypeIndex).value<int>();
		switch(eSelectedType)
		{
		case E_RecordCamera:
			{
				if ( (!GetILive()->getCurCameraState()) && (!GetILive()->getExternalCaptureState()) )
				{
					OnBtnStopRecord();
				}
				break;
			}
		case E_RecordScreen:
			{
				if ( (!GetILive()->getScreenShareState()) && (!GetILive()->getPlayMediaFileState()) )
				{
					OnBtnStopRecord();
				}
				break;
			}
		}
	}
	else
	{
		updateRecordGB();
	}
}

void Live::doAutoStopPushStream()
{
	if ( m_bPushing )
	{
		int nPushDataTypeIndex = m_ui.cbPushDataType->currentIndex();
		E_PushDataType eSelectedType = (E_PushDataType)m_ui.cbPushDataType->itemData(nPushDataTypeIndex).value<int>();
		switch(eSelectedType)
		{
		case E_PushCamera:
			{
				if ( (!GetILive()->getCurCameraState()) && (!GetILive()->getExternalCaptureState()) )
				{
					OnBtnStopPushStream();
				}
				break;
			}
		case E_PushScreen:
			{
				if ( (!GetILive()->getScreenShareState()) && (!GetILive()->getPlayMediaFileState()) )
				{
					OnBtnStopPushStream();
				}
				break;
			}
		}
	}
	else
	{
		updatePushStreamGB();
	}
}

void Live::OnOpenCameraCB( const int& retCode )
{
	updateCameraGB();
	updateExternalCaptureGB();
	updateRecordGB();
	updatePushStreamGB();
	if (retCode == NO_ERR)
	{
		m_ui.SkinGB->setVisible(true);
	}
	else
	{
		ShowCodeErrorTips( retCode, "Open Camera Failed.", this );
	}
}

void Live::OnCloseCameraCB( const int& retCode )
{
	updateCameraGB();
	updateExternalCaptureGB();
	doAutoStopRecord();
	doAutoStopPushStream();
	if (retCode == NO_ERR)
	{
		m_ui.SkinGB->setVisible(false);
		m_pLocalCameraRender->update();
	}
	else
	{
		ShowCodeErrorTips( retCode, "Close Camera Failed.", this );
	}
}

void Live::OnOpenExternalCaptureCB( const int& retCode )
{
	updateExternalCaptureGB();
	updateCameraGB();
	updateRecordGB();
	updatePushStreamGB();
	if (retCode == NO_ERR)
	{
		m_pFillFrameTimer->start(66); // 帧率1000/66约等于15
	}
	else
	{
		ShowCodeErrorTips(retCode, FromBits("打开自定义采集失败"), this );
	}
}

void Live::OnCloseExternalCaptureCB( const int& retCode )
{
	updateExternalCaptureGB();
	updateCameraGB();
	doAutoStopRecord();
	doAutoStopPushStream();
	if (retCode == NO_ERR)
	{
		m_pFillFrameTimer->stop();
		m_pLocalCameraRender->update();
	}
	else
	{
		ShowCodeErrorTips(retCode, FromBits("关闭自定义采集失败"), this );
	}
}

void Live::OnOpenMicCB( const int& retCode )
{
	updateMicGB();
	if (retCode != NO_ERR)
	{
		ShowCodeErrorTips(retCode, "Open Mic Failed.", this );
	}
}

void Live::OnCloseMicCB( const int& retCode )
{
	updateMicGB();
	if (retCode != NO_ERR)
	{
		ShowCodeErrorTips( retCode, "Close Mic Failed.", this );
	}
}

void Live::OnOpenPlayerCB( const int& retCode )
{
	updatePlayerGB();
	if (retCode != NO_ERR)
	{
		ShowCodeErrorTips(retCode, "Open Player Failed.", this );
	}
}

void Live::OnClosePlayerCB( const int& retCode )
{
	updatePlayerGB();
	if (retCode != NO_ERR)
	{
		ShowCodeErrorTips( retCode, "Close Player Failed.", this );
	}
}

void Live::OnOpenScreenShareCB( const int& retCode )
{
	updateScreenShareGB();
	updateMediaFilePlayGB();
	updateRecordGB();
	updatePushStreamGB();
	if (retCode != NO_ERR )
	{
		if( retCode == 1002 )
		{
			ShowErrorTips( FromBits("屏幕分享和文件播放不能同时打开."), this );
		}
		else if (retCode == 1008)
		{
			ShowErrorTips( FromBits("房间内其他成员已经占用辅路视频."), this );
		}
		else
		{
			ShowCodeErrorTips( retCode, FromBits("打开屏幕分享失败."), this );
		}
	}
}

void Live::OnCloseScreenShareCB( const int& retCode )
{
	updateScreenShareGB();
	updateMediaFilePlayGB();
	doAutoStopRecord();
	doAutoStopPushStream();
	if (retCode == NO_ERR)
	{
		m_pScreenShareRender->update();
	}
	else
	{
		ShowCodeErrorTips( retCode, "Close Screen Share Failed.", this );
	}
}

void Live::OnOpenSystemVoiceInputCB( const int& retCode )
{
	updateSystemVoiceInputGB();
	if (retCode != NO_ERR)
	{
		ShowCodeErrorTips(retCode, "Open System Voice Input Failed.", this );
	}
}

void Live::OnCloseSystemVoiceInputCB( const int& retCode )
{
	updateSystemVoiceInputGB();
	if (retCode != NO_ERR)
	{
		ShowCodeErrorTips( retCode, "Close SystemVoiceInput Failed.", this );
	}
}

void Live::OnOpenPlayMediaFileCB( const int& retCode )
{
	updateMediaFilePlayGB();
	updateScreenShareGB();
	updateRecordGB();
	updatePushStreamGB();
	if (retCode == NO_ERR)
	{
		m_pPlayMediaFileTimer->start(1000);
	}
	else if( retCode == 1002 )
	{
		ShowErrorTips( FromBits("屏幕分享和文件播放不能同时打开"), this );
	}
	else if( retCode == 1008 )
	{
		ShowErrorTips( FromBits("房间内其他成员已经占用辅路视频"), this );
	}
	else
	{
		ShowCodeErrorTips( retCode, FromBits("打开文件播放出错."), this );
	}
}

void Live::OnClosePlayMediaFileCB( const int& retCode )
{
	updateMediaFilePlayGB();
	updateScreenShareGB();
	doAutoStopRecord();
	doAutoStopPushStream();
	if (retCode == NO_ERR)
	{
		m_pPlayMediaFileTimer->stop();
		m_pScreenShareRender->update();
	}
	else
	{
		ShowCodeErrorTips(retCode, FromBits("关闭文件播放出错"), this);
	}
}

void Live::sendInviteInteract()
{
	g_sendC2CCustomCmd( m_roomMemberList[m_nCurSelectedMember].szID, AVIMCMD_Multi_Host_Invite, "", OnSendInviteInteractSuc, OnSendInviteInteractErr, this );
}

void Live::sendCancelInteract()
{
	g_sendGroupCustomCmd( AVIMCMD_Multi_CancelInteract, m_roomMemberList[m_nCurSelectedMember].szID );
}

void Live::OnSendInviteInteractSuc(void* data)
{
	//ShowTips( FromBits("邀请成功"), FromBits("成功发出邀请，等待观众接受上麦."), reinterpret_cast<Live*>(data) );
}

void Live::OnSendInviteInteractErr( const int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Send Invite Interact Error.");
}

void Live::acceptInteract()
{
	iLiveChangeRole(LiveGuest);
}

void Live::refuseInteract()
{
	//通知主播拒绝连麦
	g_sendC2CCustomCmd( g_pMainWindow->getCurRoomInfo().szId, AVIMCMD_Multi_Interact_Refuse, g_pMainWindow->getUserId() );
}

void Live::OnAcceptInteract()
{
	setRoomUserType(E_RoomUserJoiner);
	OnBtnOpenCamera();
	OnBtnOpenMic();

	//身份变为连麦用户后，马上心跳上报自己身份变化,并重新拉取房间成员列表
	sxbHeartBeat();
	sxbRoomIdList();
	//接受连麦后，通知主播
	g_sendC2CCustomCmd( g_pMainWindow->getCurRoomInfo().szId, AVIMCMD_Multi_Interact_Join, g_pMainWindow->getUserId() );
}

void Live::exitInteract()
{
	iLiveChangeRole(Guest);
}

void Live::OnExitInteract()
{
	if ( m_ui.btnCloseCamera->isEnabled() )
	{
		OnBtnCloseCamera();
	}
	if ( m_ui.btnCloseExternalCapture->isEnabled() )
	{
		OnBtnCloseExternalCapture();
	}
	if ( m_ui.btnCloseMic->isEnabled() )
	{
		OnBtnCloseMic();
	}
	if ( m_ui.btnCloseScreenShare->isEnabled() )
	{
		OnBtnCloseScreenShare();
	}
	if ( m_ui.btnCloseSystemVoiceInput->isEnabled() )
	{
		OnBtnCloseSystemVoiceInput();
	}
	if ( m_ui.btnStopMediaFile )
	{
		OnBtnStopMediaFile();
	}
	setRoomUserType(E_RoomUserWatcher);
	
	//身份变化后，立即心跳上报身份，并重新请求房间成员列表
	sxbHeartBeat();
	sxbRoomIdList();
}

void Live::sendQuitRoom()
{
	g_sendGroupCustomCmd( AVIMCMD_ExitLive, g_pMainWindow->getUserId() );
}

void Live::sxbCreatorQuitRoom()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "type", "live" );
	SxbServerHelper::request(varmap, "live", "exitroom", OnSxbCreatorQuitRoom, this);
}

void Live::sxbWatcherOrJoinerQuitRoom()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "id", g_pMainWindow->getUserId() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "role", (int)m_userType );//成员0 主播1 上麦成员2
	varmap.insert( "operate", 1);//进入房间0  退出房间1
	SxbServerHelper::request(varmap, "live", "reportmemid", OnSxbWatcherOrJoinerQuitRoom, this);
}

void Live::sxbHeartBeat()
{
	QVariantMap varmap;
	varmap.insert("token", g_pMainWindow->getToken());
	varmap.insert("roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum);
	varmap.insert("role", (int)m_userType); //0 观众 1 主播 2 上麦观众
	if(m_userType==E_RoomUserCreator)
	{
		varmap.insert("thumbup", g_pMainWindow->getCurRoomInfo().info.thumbup);
	}
	SxbServerHelper::request(varmap, "live", "heartbeat", OnSxbHeartBeat, this);
}

void Live::sxbRoomIdList()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "index", 0 );
	varmap.insert( "size", MaxShowMembers );
	SxbServerHelper::request(varmap, "live", "roomidlist", OnSxbRoomIdList, this);
}

void Live::sxbReportrecord()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "roomnum", g_pMainWindow->getCurRoomInfo().info.roomnum );
	varmap.insert( "uid", g_pMainWindow->getCurRoomInfo().szId );//主播名
	varmap.insert( "name", m_inputRecordName );//用户输入的录制名
	varmap.insert( "type", 0 );//预留字段，暂填0
	varmap.insert( "cover", "" );//PC随心播暂不支持直播封面上传,所以暂时上传为空，后续加上
	SxbServerHelper::request(varmap, "live", "reportrecord", OnSxbReportrecord, this);
}

void Live::OnSxbCreatorQuitRoom( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode==E_SxbOK)
	{
		pLive->iLiveQuitRoom();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pLive, FromBits("主播退出房间失败") );
	}
}

void Live::OnSxbWatcherOrJoinerQuitRoom( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);
	
	if (errorCode==E_SxbOK || errorCode==10010)//成功或者房间已经不存在
	{
		pLive->iLiveQuitRoom();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pLive, FromBits("观众退出房间失败") );
	}
}

void Live::OnSxbHeartBeat( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		//iLiveLog_e( "suixinbo", "Sui xin bo heartbeat failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
	}
}

void Live::OnSxbRoomIdList( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		//iLiveLog_e( "suixinbo", "Suixinbo get Room id list failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
		return ;
	}

	if (datamap.contains("total"))
	{
		pLive->m_nRoomSize = datamap.value("total").toInt();
	}
	if (datamap.contains("idlist"))
	{
		pLive->m_roomMemberList.clear();
		QVariantList idlist = datamap.value("idlist").toList();
		for (int i=0; i<idlist.size(); ++i)
		{
			QVariantMap idmap = idlist[i].toMap();
			RoomMember member;
			if (idmap.contains("id"))
			{
				member.szID = idmap.value("id").toString();

			}
			if (idmap.contains("role"))
			{
				member.userType = (E_RoomUserType)idmap.value("role").toInt();
			}
			pLive->m_roomMemberList.push_back(member);
		}
		pLive->updateMemberList();
	}	
}

void Live::OnSxbReportrecord( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		//iLiveLog_e( "suixinbo", "Suixinbo report record video failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
		return ;
	}
}

void Live::iLiveQuitRoom()
{
	GetILive()->quitRoom(OnQuitRoomSuc, OnQuitRoomErr, this);
}

void Live::iLiveChangeRole( const std::string& szControlRole )
{
	GetILive()->changeRole(szControlRole.c_str(), OnChangeRoleSuc, OnChangeRoleErr, this);
}

int Live::iLiveSetSkinSmoothGrade( int grade )
{
	return GetILive()->setSkinSmoothGrade(grade);
}

int Live::iLiveSetSkinWhitenessGrade( int grade )
{
	return GetILive()->setSkinWhitenessGrade(grade);
}

void Live::OnQuitRoomSuc( void* data )
{
	Room roominfo = g_pMainWindow->getCurRoomInfo();
	roominfo.szId = "";
	roominfo.info.thumbup = 0;
	g_pMainWindow->setCurRoomIdfo(roominfo);
	g_pMainWindow->setUseable(true);
}

void Live::OnQuitRoomErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Quit iLive Room Error.");
}

void Live::OnChangeRoleSuc( void* data )
{
	reinterpret_cast<Live*>(data)->ChangeRoomUserType();
}

void Live::OnChangeRoleErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, FromBits(desc), reinterpret_cast<Live*>(data), "Change Role Error.");
}

void Live::OnSendGroupMsgSuc( void* data )
{

}

void Live::OnSendGroupMsgErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Send Group Message Error.");
}

void Live::OnMemberListMenu( QPoint point )
{
	if ( m_userType != E_RoomUserCreator )
	{
		return;
	}
	m_nCurSelectedMember = m_ui.liMembers->currentRow();
	if ( m_nCurSelectedMember>=0 && m_nCurSelectedMember<m_roomMemberList.size() )
	{
		RoomMember& roomMember = m_roomMemberList[m_nCurSelectedMember];
		if (roomMember.userType==E_RoomUserWatcher)
		{
			m_pMenuInviteInteract->exec( QCursor::pos() );
		}
		else if(roomMember.userType==E_RoomUserJoiner)
		{
			m_pMenuCancelInteract->exec( QCursor::pos() );
		}
	}
}

void Live::OnActInviteInteract()
{
	m_nCurSelectedMember = m_ui.liMembers->currentRow();
	if ( m_nCurSelectedMember >= 0 || m_nCurSelectedMember < m_ui.liMembers->count() )
	{
		sendInviteInteract();
	}
}

void Live::OnActCancelInteract()
{
	m_nCurSelectedMember = m_ui.liMembers->currentRow();
	if ( m_nCurSelectedMember >= 0 || m_nCurSelectedMember < m_ui.liMembers->count() )
	{
		RoomMember& roomber = m_roomMemberList[m_nCurSelectedMember];
		roomber.userType = E_RoomUserWatcher;
		updateMemberList();

		sendCancelInteract();
	}
}

void Live::OnVideoRenderFullScreen( VideoRender* pRender )
{
	pRender->recoverRender();
	pRender->enterFullScreen();
	if (m_pLocalCameraRender!=pRender)
	{
		m_pLocalCameraRender->pauseRender();
		m_pLocalCameraRender->exitFullScreen();
	}
	if (m_pScreenShareRender!=pRender)
	{
		m_pScreenShareRender->pauseRender();
		m_pScreenShareRender->exitFullScreen();
	}
	for (int i=0; i<MaxVideoRender; ++i)
	{
		if (m_pRemoteVideoRenders[i]!=pRender)
		{
			m_pRemoteVideoRenders[i]->pauseRender();
			m_pRemoteVideoRenders[i]->exitFullScreen();
		}
	}
}

void Live::OnExitVideoRenderFullScreen( VideoRender* pRender )
{
	m_pLocalCameraRender->recoverRender();
	m_pLocalCameraRender->exitFullScreen();
	m_pScreenShareRender->recoverRender();
	m_pScreenShareRender->exitFullScreen();
	for (int i=0; i<MaxVideoRender; ++i)
	{
		m_pRemoteVideoRenders[i]->recoverRender();
		m_pRemoteVideoRenders[i]->exitFullScreen();
	}
}

void Live::OnStartRecordVideoSuc( void* data )
{
	Live* pThis = reinterpret_cast<Live*>(data);
	pThis->m_bRecording = true;
	pThis->updateRecordGB();
}

void Live::OnStartRecordVideoErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Start Record Video Error.");
}

void Live::OnStopRecordSuc( Vector<String>& value, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_bRecording = false;
	pLive->updateRecordGB();
	pLive->sxbReportrecord();
}

void Live::OnStopRecordVideoErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Stop Record Video Error.");
}

void Live::OnStartPushStreamSuc( PushStreamRsp &value, void *data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_bPushing = true;
	pLive->m_channelId = value.channelId;
	for (auto i = value.urls.begin(); i != value.urls.end(); ++i)
	{
		pLive->m_pushUrls.push_back(*i);
	}
	pLive->updatePushStreamGB();
}

void Live::OnStartPushStreamErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Start Push Stream Error.");
}

void Live::OnStopPushStreamSuc( void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_bPushing = false;
	pLive->m_channelId = 0;
	pLive->m_pushUrls.clear();
	pLive->updatePushStreamGB();
}

void Live::OnStopPushStreamErr( int code, const char *desc, void* data )
{
	ShowCodeErrorTips(code, desc, reinterpret_cast<Live*>(data), "Stop Push Stream Error.");
}


void Live::on_btnMix_clicked()
{
	std::vector<std::pair<std::string, bool>> list;
	//aux
	if (m_pScreenShareRender != nullptr && !m_pScreenShareRender->getId().empty())
	{
		std::pair<std::string, bool> id(m_pScreenShareRender->getId(), true);		
		list.push_back(id);
	}
	//local camera
	if (m_pLocalCameraRender != nullptr && !m_pLocalCameraRender->getId().empty())
	{
		std::pair<std::string, bool> id(m_pLocalCameraRender->getId(), false);		
		list.push_back(id);
	}

	//remote camera
	for (sizet i = 0; i < m_arrRemoteIdentifiers.size(); ++i)
	{
		if (m_arrRemoteIdentifiers[i].empty()) continue;
		std::pair<std::string, bool> id(m_arrRemoteIdentifiers[i], false);		
		list.push_back(id);
	}
	
	if (list.size() < 2)
	{
		ShowErrorTips( FromBits("至少有两路流才可以进行混流!"), this );
	}
	else
	{
		MixStreamHelper helper(list, QString("45eeb9fc2e4e6f88b778e0bbd9de3737"), mRoomId, this);
		helper.doRequest();
	}
}

void Live::onMixStream(std::string streamCode)
{
	std::stringstream ss;
	ss << "ffplay rtmp://8525.liveplay.myqcloud.com/live/" << streamCode;	
	std::string url = ss.str();
	
	system(url.c_str());
}

