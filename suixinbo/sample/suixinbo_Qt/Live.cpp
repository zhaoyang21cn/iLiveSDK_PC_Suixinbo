#include "stdafx.h"
#include "Live.h"

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
	m_ui.sbFPS->setValue(m_fps);

	m_nRoomSize = 0;

	m_pTimer = new QTimer(this);
	m_pDelayUpdateTimer = new QTimer(this);
	m_pFillFrameTimer = new QTimer(this);

	m_nCurSelectedMember = -1;

	m_pMenuInviteInteract = new QMenu(this);
	QAction* pActInviteInteract = new QAction( QString::fromLocal8Bit("连线"), m_pMenuInviteInteract );
	m_pMenuInviteInteract->addAction(pActInviteInteract);
	m_pMenuCancelInteract = new QMenu(this);
	QAction* pActCancelInteract = new QAction( QString::fromLocal8Bit("断开"), m_pMenuInviteInteract );
	m_pMenuCancelInteract->addAction(pActCancelInteract);

	m_ui.cbRecordDataType->addItem( FromBits("主路(摄像头/自定义采集)"), QVariant(E_RecordCamera) );
	m_ui.cbRecordDataType->addItem( FromBits("辅路(屏幕分享)"), QVariant(E_RecordScreen) );
	m_ui.cbRecordDataType->setCurrentIndex(0);

	m_ui.cbPushDataType->addItem( FromBits("主路(摄像头/自定义采集)"), QVariant(E_PushCamera) );
	m_ui.cbPushDataType->addItem( FromBits("辅路(屏幕分享)"), QVariant(E_PushScreen) );
	m_ui.cbPushDataType->setCurrentIndex(0);

	m_ui.cbPushEncodeType->addItem(FromBits("HLS"), QVariant(HLS) );
	m_ui.cbPushEncodeType->addItem(FromBits("RTMP"),QVariant(RTMP) );
	m_ui.cbPushEncodeType->setCurrentIndex(0);

	m_channelId = 0;

	m_bIsRequesting = false;
	m_pRequestViewsTimer = new QTimer(this);

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
	connect( m_ui.btnSendGroupMsg, SIGNAL(clicked()), this, SLOT(OnBtnSendGroupMsg()) );
	connect( m_ui.btnStartRecord, SIGNAL(clicked()), this, SLOT(OnBtnStartRecord()) );
	connect( m_ui.btnStopRecord, SIGNAL(clicked()), this, SLOT(OnBtnStopRecord()) );
	connect( m_ui.btnStartPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStartPushStream()) );
	connect( m_ui.btnStopPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStopPushStream()) );
	connect( m_ui.btnPraise, SIGNAL(clicked()), this, SLOT(OnBtnPraise()) );
	connect( m_ui.hsPlayerVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsPlayerVol(int)) );
	connect( m_ui.sbPlayerVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbPlayerVol(int)) );
	connect( m_ui.hsMicVol, SIGNAL(valueChanged(int)), this, SLOT(OnHsMicVol(int)) );
	connect( m_ui.sbMicVol, SIGNAL(valueChanged(int)), this, SLOT(OnSbMicVol(int)) );
	connect( m_ui.vsSkinSmooth, SIGNAL(valueChanged(int)), this, SLOT(OnVsSkinSmoothChanged(int)) );
	connect( m_ui.sbSkinSmooth, SIGNAL(valueChanged(int)), this, SLOT(OnSbSkinSmoothChanged(int)) );
	connect( m_ui.vsSkinWhite, SIGNAL(valueChanged(int)), this, SLOT(OnVsSkinWhiteChanged(int)) );
	connect( m_ui.sbSkinWhite, SIGNAL(valueChanged(int)), this, SLOT(OnSbSkinWhiteChanged(int)) );
	connect( m_pTimer, SIGNAL(timeout()), this, SLOT(OnHeartBeatTimer()) );
	connect( m_pDelayUpdateTimer, SIGNAL(timeout()), this, SLOT(OnDelayUpdateTimer()) );
	connect( m_pFillFrameTimer, SIGNAL(timeout()), this, SLOT(OnFillFrameTimer()) );
	connect( pActInviteInteract, SIGNAL(triggered()), this, SLOT(OnActInviteInteract()) );
	connect( pActCancelInteract, SIGNAL(triggered()), this, SLOT(OnActCancelInteract()) );
	connect( m_pRequestViewsTimer, SIGNAL(timeout()), this, SLOT(OnRequestViewsTimer()) );
}

Live::~Live()
{

}

void Live::setRoomUserType( E_RoomUserType userType )
{
	m_userType = userType;
	m_ui.SkinGB->setVisible(false);
	m_ui.btnOpenPlayer->setEnabled(true);
	m_ui.btnClosePlayer->setEnabled(false);
	m_ui.cameraGB->setEnabled(true);
	m_ui.externalCaptureGB->setEnabled(true);
	updatePlayerVol();
	updateMicVol();
	switch(m_userType)
	{
	case E_RoomUserCreator:
		{
			m_ui.cameraGB->setVisible(true);
			m_ui.btnOpenCamera->setEnabled(true);
			m_ui.btnCloseCamera->setEnabled(false);
			updateCameraList();

			m_ui.externalCaptureGB->setVisible(true);
			m_ui.btnOpenExternalCapture->setEnabled(true);
			m_ui.btnCloseExternalCapture->setEnabled(false);

			m_ui.microphoneGB->setVisible(true);
			m_ui.btnOpenMic->setEnabled(true);
			m_ui.btnCloseMic->setEnabled(false);

			m_ui.screenShareGB->setVisible(true);
			m_ui.sbFPS->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(false);

			m_ui.recordGB->setVisible(true);
			m_ui.pushStreamGB->setVisible(true);
			updatePushAndRecordStateUI();

			m_ui.lbPraiseNum->setVisible(true);
			m_ui.btnPraise->setVisible(false);

			this->setWindowTitle( QString::fromLocal8Bit("主播") );
			break;
		}
	case E_RoomUserJoiner:
		{
			m_ui.cameraGB->setVisible(true);
			m_ui.btnOpenCamera->setEnabled(true);
			m_ui.btnCloseCamera->setEnabled(false);
			updateCameraList();

			m_ui.externalCaptureGB->setVisible(true);
			m_ui.btnOpenExternalCapture->setEnabled(true);
			m_ui.btnCloseExternalCapture->setEnabled(false);

			m_ui.microphoneGB->setVisible(true);
			m_ui.btnOpenMic->setEnabled(true);
			m_ui.btnCloseMic->setEnabled(false);

			m_ui.screenShareGB->setVisible(true);
			m_ui.sbFPS->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(false);

			m_ui.recordGB->setVisible(false);
			m_ui.pushStreamGB->setVisible(false);

			m_ui.lbPraiseNum->setVisible(false);
			m_ui.btnPraise->setVisible(true);

			this->setWindowTitle( QString::fromLocal8Bit("连麦者") );
			break;
		}
	case E_RoomUserWatcher:
		{
			m_ui.cameraGB->setVisible(false);
			m_ui.externalCaptureGB->setVisible(false);
			m_ui.microphoneGB->setVisible(false);
			m_ui.screenShareGB->setVisible(false);
			this->setWindowTitle( QString::fromLocal8Bit("观众") );
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

void Live::updatePushAndRecordStateUI()
{
	if ( iLiveSDKWrap::getInstance()->getCurCameraState() || iLiveSDKWrap::getInstance()->getExternalCaptureState() || iLiveSDKWrap::getInstance()->getScreenShareState() )
	{
		m_ui.pushStreamGB->setEnabled(true);
		m_ui.recordGB->setEnabled(true);
	}
	else
	{
		if ( iLiveSDKWrap::getInstance()->getRecordState() )
		{
			OnBtnStopRecord();
		}
		if ( iLiveSDKWrap::getInstance()->getPushStreamState() )
		{
			OnBtnStopPushStream();
		}
		m_ui.pushStreamGB->setEnabled(false);
		m_ui.recordGB->setEnabled(false);
		return;
	}

	if ( iLiveSDKWrap::getInstance()->getRecordState() )//录制中
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

	if( iLiveSDKWrap::getInstance()->getPushStreamState() )//推流中
	{
		m_ui.btnStartPushStream->setEnabled(false);
		m_ui.btnStopPushStream->setEnabled(true);
		m_ui.cbPushDataType->setEnabled(false);
		m_ui.cbPushEncodeType->setEnabled(false);
		QString szUrl;
		for (std::list<TIMLiveUrl>::iterator iter = m_pushUrls.begin(); iter != m_pushUrls.end(); ++iter)
		{
			szUrl += QString::fromStdString( iter->url ) + "\n";
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
}

void Live::dealMessage( const TIMMessage& msg )
{
	std::string szSender = msg.GetSender();
	int nCount = msg.GetElemCount();
	for (int i = 0; i < nCount; ++i)
	{
		TIMElem* pElem = msg.GetElem(i);
		switch( pElem->type() )
		{
		case kElemText:
			{
				QString szShow = QString::fromStdString( szSender + ": " );
				addMsgLab( szShow + pElem->GetTextElem()->content().c_str() );
				break;
			}
		case kElemCustom:
			{
				std::string szExt = pElem->GetCustomElem()->ext();
				//if (szExt==LiveNoti) //当前版本暂不启用此信令标记,待三个平台一起启用
				{
					std::string szDate = pElem->GetCustomElem()->data();
					parseCusMessage(szSender, szDate);
				}
				break;
			}
		case kElemImage:
			break;
		case kElemFace:
			break;
		case kElemGroupTips: //群事件消息: TIM_GROUP_TIPS_TYPE_INVITE等类型
			break;
		case kElemGroupReport://群系统消息: TIM_GROUP_SYSTEM_DELETE_GROUP_TYPE(群解散)、TIM_GROUP_SYSTEM_ADD_GROUP_REQUEST_TYPE(申请加群)等类型
			break;
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
	case AVIMCMD_Multi_Host_Invite: //观众收到连线邀请
		{
			QMessageBox::StandardButton ret = QMessageBox::question(this, QString::fromLocal8Bit("邀请"), QString::fromLocal8Bit("主播邀请你上麦，是否接受?") );
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
	case AVIMCMD_Multi_Interact_Join: //主播收到观众接受连线请求的回复
		{
			sxbRoomIdList(); //重新请求列表
			break;
		}
	case AVIMCMD_Multi_Interact_Refuse://主播收到观众拒绝连线请求的回复
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
			ShowTips( FromBits("主播退出房间"), FromBits("主播已经退出房间,点击确认退出房间."), this );
			close();
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

void Live::startTimer()
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

void Live::OnMemStatusChange( AVRoomMulti::EndpointEventId event_id, std::vector<std::string> identifier_list, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	switch(event_id)
	{
	case AVRoomMulti::EVENT_ID_ENDPOINT_ENTER:
		{
			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_EXIT:
		{
			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO:
		{
			std::vector<View> views;
			for (size_t i=0; i<identifier_list.size(); ++i)
			{
				View view;
				view.video_src_type = VIDEO_SRC_TYPE_CAMERA;
				view.size_type = VIEW_SIZE_TYPE_BIG;
				views.push_back(view);
			}
			pLive->addRequestViews(identifier_list, views);
			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO:
		{
			std::vector<View> views;
			for (size_t i=0; i<identifier_list.size(); ++i)
			{
				View view;
				view.video_src_type = VIDEO_SRC_TYPE_SCREEN;
				view.size_type = VIEW_SIZE_TYPE_BIG;
				views.push_back(view);
			}
			pLive->addRequestViews(identifier_list, views);
			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO:
		{
			pLive->freeCameraVideoRenders(identifier_list);
			break;
		}
	case AVRoomMulti::EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO:
		{
			pLive->freeScreenVideoRender();
			break;
		}
	}
}

void Live::OnSemiAutoRecvCameraVideo( std::vector<std::string> identifier_list, void* data )
{
	
}

void Live::OnSemiAutoRecvScreenVideo( std::vector<std::string> identifier_list, void* data )
{

}

void Live::OnSemiAutoRecvMediaFileVideo( std::vector<std::string> identifier_list, void* data )
{

}

void Live::OnRoomDisconnect( int32 reason, std::string errorinfo, void* data )
{
	
}

void Live::OnLocalVideo( VideoFrame* video_frame, void* custom_data )
{
	Live* pLive = reinterpret_cast<Live*>(custom_data);

	if(video_frame->desc.src_type == VIDEO_SRC_TYPE_SCREEN)
	{
		pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if (video_frame->desc.src_type == VIDEO_SRC_TYPE_CAMERA)
	{
		pLive->m_pLocalCameraRender->DoRender(video_frame);
	}
}

void Live::OnRemoteVideo( VideoFrame* video_frame, void* custom_data )
{
	Live* pLive = reinterpret_cast<Live*>(custom_data);
	if (video_frame->desc.src_type == VIDEO_SRC_TYPE_SCREEN)
	{
		pLive->m_pScreenShareRender->DoRender(video_frame);
	}
	else if(video_frame->desc.src_type == VIDEO_SRC_TYPE_CAMERA)
	{
		VideoRender* pRender = pLive->getVideoRender(video_frame->identifier);
		if (pRender)
		{
			pRender->DoRender(video_frame);
		}
		else
		{
			iLiveLog_e("suixinbo", "Render is not enough.");
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
	int nRet = iLiveSDKWrap::getInstance()->openCamera(m_cameraList[ndx].first);
	if (nRet==NO_ERR)
	{
		m_ui.SkinGB->setVisible(true);
		m_ui.btnCloseCamera->setEnabled(true);
		m_ui.externalCaptureGB->setEnabled(false);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenCamera->setEnabled(true);
		ShowCodeErrorTips( nRet, "Open Camera Failed.", this );
	}
}

void Live::OnBtnCloseCamera()
{
	m_ui.btnCloseCamera->setEnabled(false);
	int nRet = iLiveSDKWrap::getInstance()->closeCamera();
	if (nRet==0)
	{
		m_ui.SkinGB->setVisible(false);
		m_ui.btnOpenCamera->setEnabled(true);
		m_ui.externalCaptureGB->setEnabled(true);
		m_pLocalCameraRender->update();
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnCloseCamera->setEnabled(true);
		ShowErrorTips( "Close Camera Failed.", this );
	}
}

void Live::OnBtnOpenExternalCapture()
{
	m_ui.btnOpenExternalCapture->setEnabled(false);
	m_ui.btnCloseExternalCapture->setEnabled(true);
	int nRet = iLiveSDKWrap::getInstance()->openExternalCapture();
	if (nRet == NO_ERR )
	{
		m_pFillFrameTimer->start(66); // 帧率1000/66约等于15
		m_ui.cameraGB->setEnabled(false);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenExternalCapture->setEnabled(true);
		m_ui.btnCloseExternalCapture->setEnabled(false);
		ShowCodeErrorTips(nRet, FromBits("打开自定义采集失败"), this );
	}
	return;
}

void Live::OnBtnCloseExternalCapture()
{
	m_ui.btnOpenExternalCapture->setEnabled(true);
	m_ui.btnCloseExternalCapture->setEnabled(false);
	int nRet = iLiveSDKWrap::getInstance()->closeExternalCapture();
	if (nRet == NO_ERR )
	{
		m_pFillFrameTimer->stop();
		m_pLocalCameraRender->update();
		m_ui.cameraGB->setEnabled(true);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenExternalCapture->setEnabled(false);
		m_ui.btnCloseExternalCapture->setEnabled(true);
		ShowCodeErrorTips(nRet, FromBits("关闭自定义采集失败"), this );
	}
	return;
}

void Live::OnBtnOpenMic()
{
	m_ui.btnOpenMic->setEnabled(false);
	int nRet = iLiveSDKWrap::getInstance()->openMic();
	if (nRet==0)
	{		
		m_ui.btnCloseMic->setEnabled(true);
		updateMicVol();
	}
	else
	{
		m_ui.btnOpenMic->setEnabled(true);
		ShowErrorTips( "Open Mic Failed.", this );
	}
}

void Live::OnBtnCloseMic()
{
	m_ui.btnCloseMic->setEnabled(false);
	int nRet = iLiveSDKWrap::getInstance()->closeMic();
	if (nRet==0)
	{
		m_ui.btnOpenMic->setEnabled(true);
		updateMicVol();
	}
	else
	{
		m_ui.btnCloseMic->setEnabled(true);
		ShowErrorTips( "Close Mic Failed.", this );
	}
}

void Live::OnBtnOpenPlayer()
{
	m_ui.btnOpenPlayer->setEnabled(false);
	int nRet = iLiveSDKWrap::getInstance()->openPlayer();
	if (nRet==0)
	{		
		m_ui.btnClosePlayer->setEnabled(true);
		updatePlayerVol();
	}
	else
	{
		m_ui.btnOpenPlayer->setEnabled(true);
		ShowErrorTips( "Open Player Failed.", this );
	}
}

void Live::OnBtnClosePlayer()
{
	m_ui.btnClosePlayer->setEnabled(false);
	int nRet = iLiveSDKWrap::getInstance()->closePlayer();
	if (nRet==0)
	{		
		m_ui.btnOpenPlayer->setEnabled(true);
		updatePlayerVol();
	}
	else
	{
		m_ui.btnClosePlayer->setEnabled(true);
		ShowErrorTips( "Close Player Failed.", this );
	}
}

void Live::OnBtnOpenScreenShareArea()
{
	m_x0 = m_ui.sbX0->value();
	m_y0 = m_ui.sbY0->value();
	m_x1 = m_ui.sbX1->value();
	m_y1 = m_ui.sbY1->value();
	m_fps= m_ui.sbFPS->value();
	int nRet = iLiveSDKWrap::getInstance()->openScreenShare(m_x0, m_y0, m_x1, m_y1, m_fps);
	if (nRet==0)
	{
		updatePushAndRecordStateUI();
		updateScreenShareUI();
	}
	else
	{
		if (nRet==1008)
		{
			ShowErrorTips( FromBits("房间内只允许一个用户打开屏幕分享"), this );
		}
		else
		{
			ShowCodeErrorTips( nRet, "Open Screen Share Failed.", this );
		}
	}
}

void Live::OnBtnOpenScreenShareWnd()
{
	m_fps= m_ui.sbFPS->value();
	int nRet = iLiveSDKWrap::getInstance()->openScreenShare( (HWND)this->winId(), m_fps );//这里演示分享直播界面窗口
	if (nRet==0)
	{
		updatePushAndRecordStateUI();
		updateScreenShareUI();
	}
	else
	{
		if (nRet==1008)
		{
			ShowErrorTips( FromBits("房间内只允许一个用户打开屏幕分享"), this );
		}
		else
		{
			ShowCodeErrorTips( nRet, "Open Screen Share Failed.", this );
		}
	}
}

void Live::OnBtnUpdateScreenShare()
{
	m_x0 = m_ui.sbX0->value();
	m_y0 = m_ui.sbY0->value();
	m_x1 = m_ui.sbX1->value();
	m_y1 = m_ui.sbY1->value();

	int nRet = iLiveSDKWrap::getInstance()->changeScreenShareSize( m_x0, m_y0, m_x1, m_y1 );
	if (nRet==NO_ERR)
	{
		updateScreenShareUI();
	}
	else
	{
		ShowCodeErrorTips( nRet, "changeScreenShareAreaSize failed.", this );
	}
}

void Live::OnBtnCloseScreenShare()
{
	int nRet = iLiveSDKWrap::getInstance()->closeScreenShare();
	if (nRet==0)
	{
		m_pScreenShareRender->update();
		updateScreenShareUI();
		updatePushAndRecordStateUI();
	}
	else
	{
		updateScreenShareUI();
		ShowErrorTips( "Close Screen Share Failed.", this );
	}
}

void Live::OnBtnSendGroupMsg()
{
	QString szText = m_ui.teEditText->toPlainText();
	m_ui.teEditText->setPlainText("");
	if ( szText.isEmpty() )
	{
		return;
	}

	TIMMessage message;
	//文字
	TIMTextElem textElem;
	textElem.set_content( szText.toStdString() );
	message.AddElem(&textElem);
	
	addMsgLab( QString::fromLocal8Bit("我说： ") + szText );
	iLiveSDKWrap::getInstance()->sendGroupMessage(  message, OnSendGroupMsgSuc, OnSendGroupMsgErr, this );
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
	
	m_recordOpt.filename = fileName.toStdString();
	m_recordOpt.record_data_type = (ilivesdk::E_RecordDataType)m_ui.cbRecordDataType->itemData( m_ui.cbRecordDataType->currentIndex() ).value<int>();
	iLiveSDKWrap::getInstance()->startRecordVideo(m_recordOpt, OnStartRecordVideoSuc, OnStartRecordVideoErr, this);
}

void Live::OnBtnStopRecord()
{
	iLiveSDKWrap::getInstance()->stopRecordVideo( OnStopRecordSuc, OnStopRecordVideoErr, this);
}

void Live::OnBtnStartPushStream()
{
	m_pushOpt.channel_name = g_pMainWindow->getUserId().toStdString();
	m_pushOpt.channel_desc = g_pMainWindow->getUserId().toStdString();
	m_pushOpt.push_data_type = (E_PushDataType)m_ui.cbPushDataType->itemData( m_ui.cbPushDataType->currentIndex() ).value<int>();
	m_pushOpt.encode = (E_TIMStreamEncode)m_ui.cbPushEncodeType->itemData( m_ui.cbPushEncodeType->currentIndex() ).value<int>();
	iLiveSDKWrap::getInstance()->startPushStream( m_pushOpt, OnStartPushStreamSuc, OnStartPushStreamErr, this );
}

void Live::OnBtnStopPushStream()
{
	iLiveSDKWrap::getInstance()->stopPushStream(m_channelId, OnStopPushStreamSuc, OnStopPushStreamErr, this);
}

void Live::OnBtnPraise()
{
	sendGroupCustomCmd( AVIMCMD_Praise, g_pMainWindow->getUserId() );
	addMsgLab( g_pMainWindow->getUserId()+FromBits("点赞") );
}

void Live::OnHsPlayerVol( int value )
{
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.sbPlayerVol->setValue(value);
	m_ui.sbPlayerVol->blockSignals(false);

	iLiveSDKWrap::getInstance()->setPlayerVolume(value);
}

void Live::OnSbPlayerVol( int value )
{
	m_ui.hsPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->setValue(value);
	m_ui.hsPlayerVol->blockSignals(false);

	iLiveSDKWrap::getInstance()->setPlayerVolume(value);
}

void Live::OnHsMicVol( int value )
{
	m_ui.sbMicVol->blockSignals(true);
	m_ui.sbMicVol->setValue(value);
	m_ui.sbMicVol->blockSignals(false);

	iLiveSDKWrap::getInstance()->setMicVolume(value);
}

void Live::OnSbMicVol( int value )
{
	m_ui.hsMicVol->blockSignals(true);
	m_ui.hsMicVol->setValue(value);
	m_ui.hsMicVol->blockSignals(false);

	iLiveSDKWrap::getInstance()->setMicVolume(value);
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

void Live::OnHeartBeatTimer()
{
	sxbHeartBeat();
	sxbRoomIdList();
}

void Live::OnRequestViewsTimer()
{
	if (m_bIsRequesting)
	{
		return;
	}
	m_bIsRequesting = true;
	iLiveSDKWrap::getInstance()->requestViewList(m_toRequestIdentifiers, m_toRequestViews, OnRequestViewListSuc, OnRequestViewListErr, this);
	m_toRequestIdentifiers.clear();
	m_toRequestViews.clear();
}

void Live::OnDelayUpdateTimer()
{
	m_pDelayUpdateTimer->stop();
	this->update();
}

void Live::OnFillFrameTimer()
{
	//////////////////////////////////////////////////
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

	VideoFrame frame;
	frame.data = (uint8*)bitmap.bmBits;	
	frame.data_size = bitmap.bmWidth * bitmap.bmHeight * 3;
	frame.desc.color_format = COLOR_FORMAT_RGB24;
	frame.desc.width = bitmap.bmWidth;
	frame.desc.height = bitmap.bmHeight;
	frame.desc.rotate = 0;

	int nRet = iLiveSDKWrap::getInstance()->fillExternalCaptureFrame(frame);
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

void Live::closeEvent( QCloseEvent* event )
{
	m_ui.liMsgs->clear();
	freeAllCameraVideoRender();	
	stopTimer();
	if ( m_pFillFrameTimer->isActive() )
	{
		m_pFillFrameTimer->stop();
	}
	if (m_userType==E_RoomUserCreator)//主播退出房间需要向随心播服务器上报退出房间
	{
		sendQuitRoom();
		sxbCreatorQuitRoom();
	}
	else//观众和连麦观众只需要向随心播服务器上报自己的ID
	{
		sxbWatcherOrJoinerQuitRoom();
	}
	g_pMainWindow->setUseable(true);

	event->accept();
}

void Live::updateCameraList()
{
	iLiveSDKWrap::getInstance()->getCameraList(m_cameraList);
	m_ui.cbCamera->clear();
	for(int i=0; i<m_cameraList.size(); ++i)
	{
		m_ui.cbCamera->addItem( QString::fromStdString(m_cameraList[i].second) );
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
	m_pLocalCameraRender->exitFullScreen();
	m_pScreenShareRender->exitFullScreen();
	m_pLocalCameraRender->recoverRender();
	m_pScreenShareRender->recoverRender();
	for (int i=0; i<MaxVideoRender; ++i)
	{
		m_pRemoteVideoRenders[i]->exitFullScreen();
		m_pRemoteVideoRenders[i]->recoverRender();
		m_arrRemoteIdentifiers[i] = "";
		m_bRemoteVideoRenderFrees[i] = true;
	}
}

void Live::freeScreenVideoRender()
{
	m_pScreenShareRender->update();
	updateLater();
}

void Live::addMsgLab( QString msg )
{
	m_ui.liMsgs->addItem( new QListWidgetItem(msg) );
	m_ui.liMsgs->setCurrentRow( m_ui.liMsgs->count()-1 );
}

void Live::addRequestViews( const std::vector<std::string>& identifiers, const std::vector<View>& views )
{
	assert(identifiers.size() == views.size());
	for (int i=0; i<identifiers.size(); ++i)
	{
		m_toRequestIdentifiers.push_back(identifiers[i]);
		m_toRequestViews.push_back(views[i]);
	}
	if ( !m_pRequestViewsTimer->isActive() )
	{
		m_pRequestViewsTimer->start(0);
	}
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

void Live::updateScreenShareUI()
{
	m_ui.sbX0->blockSignals(true);
	m_ui.sbY0->blockSignals(true);
	m_ui.sbX1->blockSignals(true);
	m_ui.sbY1->blockSignals(true);
	m_ui.sbFPS->blockSignals(true);
	m_ui.sbX0->setValue(m_x0);
	m_ui.sbY0->setValue(m_y0);
	m_ui.sbX1->setValue(m_x1);
	m_ui.sbY1->setValue(m_y1);
	m_ui.sbFPS->setValue(m_fps);
	m_ui.sbX0->blockSignals(false);
	m_ui.sbY0->blockSignals(false);
	m_ui.sbX1->blockSignals(false);
	m_ui.sbY1->blockSignals(false);
	m_ui.sbFPS->blockSignals(false);

	E_ScreenShareState state = iLiveSDKWrap::getInstance()->getScreenShareState();
	switch(state)
	{
	case E_ScreenShareNone:
		{
			m_ui.sbX0->setEnabled(true);
			m_ui.sbY0->setEnabled(true);
			m_ui.sbX1->setEnabled(true);
			m_ui.sbY1->setEnabled(true);
			m_ui.sbFPS->setEnabled(true);
			m_ui.btnOpenScreenShareArea->setEnabled(true);
			m_ui.btnOpenScreenShareWnd->setEnabled(true);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(false);
			break;
		}
	case E_ScreenShareWnd:
		{
			m_ui.sbX0->setEnabled(false);
			m_ui.sbY0->setEnabled(false);
			m_ui.sbX1->setEnabled(false);
			m_ui.sbY1->setEnabled(false);
			m_ui.sbFPS->setEnabled(false);
			m_ui.btnOpenScreenShareArea->setEnabled(false);
			m_ui.btnOpenScreenShareWnd->setEnabled(false);
			m_ui.btnUpdateScreenShare->setEnabled(false);
			m_ui.btnCloseScreenShare->setEnabled(true);
			break;
		}
	case E_ScreenShareArea:
		{
			m_ui.sbX0->setEnabled(true);
			m_ui.sbY0->setEnabled(true);
			m_ui.sbX1->setEnabled(true);
			m_ui.sbY1->setEnabled(true);
			m_ui.sbFPS->setEnabled(false);
			m_ui.btnOpenScreenShareArea->setEnabled(false);
			m_ui.btnOpenScreenShareWnd->setEnabled(false);
			m_ui.btnUpdateScreenShare->setEnabled(true);
			m_ui.btnCloseScreenShare->setEnabled(true);
			break;
		}
	default:
		{
			break;
		}
	}
}

void Live::updatePlayerVol()
{
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->blockSignals(true);

	uint32 uVol = iLiveSDKWrap::getInstance()->getPlayerVolume();
	m_ui.sbPlayerVol->setValue(uVol);
	m_ui.hsPlayerVol->setValue(uVol);

	m_ui.sbPlayerVol->blockSignals(false);
	m_ui.hsPlayerVol->blockSignals(false);

	if ( iLiveSDKWrap::getInstance()->getCurPlayerState() )
	{
		m_ui.sbPlayerVol->setEnabled(true);
		m_ui.hsPlayerVol->setEnabled(true);
	}
	else
	{
		m_ui.sbPlayerVol->setEnabled(false);
		m_ui.hsPlayerVol->setEnabled(false);
	}	
}

void Live::updateMicVol()
{
	m_ui.sbMicVol->blockSignals(true);
	m_ui.hsMicVol->blockSignals(true);

	uint32 uVol = iLiveSDKWrap::getInstance()->getMicVolume();
	m_ui.sbMicVol->setValue(uVol);
	m_ui.hsMicVol->setValue(uVol);

	m_ui.sbMicVol->blockSignals(false);
	m_ui.hsMicVol->blockSignals(false);

	if ( iLiveSDKWrap::getInstance()->getCurMicState() )
	{
		m_ui.sbMicVol->setEnabled(true);
		m_ui.hsMicVol->setEnabled(true);
	}
	else
	{
		m_ui.sbMicVol->setEnabled(false);
		m_ui.hsMicVol->setEnabled(false);
	}
}

void Live::sendInviteInteract()
{
	sendC2CCustomCmd( m_roomMemberList[m_nCurSelectedMember].szID, AVIMCMD_Multi_Host_Invite, "", OnSendInviteInteractSuc, OnSendInviteInteractErr, this );
}

void Live::sendCancelInteract()
{
	sendGroupCustomCmd( AVIMCMD_Multi_CancelInteract, m_roomMemberList[m_nCurSelectedMember].szID );
}

void Live::OnSendInviteInteractSuc(void* data)
{
	postCusEvent( g_pMainWindow, new Event(E_CESendInviteInteract, 0, "") );
}

void Live::OnSendInviteInteractErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CESendInviteInteract, code, desc) );
}

void Live::acceptInteract()
{
	iLiveChangeAuthority(AUTH_BITS_DEFAULT, "");
	iLiveChangeRole(LiveGuest);
}

void Live::refuseInteract()
{
	//通知主播拒绝连麦
	sendC2CCustomCmd( g_pMainWindow->getCurRoomInfo().szId, AVIMCMD_Multi_Interact_Refuse, g_pMainWindow->getUserId() );
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
	sendC2CCustomCmd( g_pMainWindow->getCurRoomInfo().szId, AVIMCMD_Multi_Interact_Join, g_pMainWindow->getUserId() );
}

void Live::exitInteract()
{
	iLiveChangeAuthority(AUTH_BITS_JOIN_ROOM|AUTH_BITS_RECV_AUDIO|AUTH_BITS_RECV_CAMERA_VIDEO|AUTH_BITS_RECV_SCREEN_VIDEO, "");
	iLiveChangeRole(Guest);
}

void Live::OnExitInteract()
{
	if ( m_ui.btnCloseCamera->isEnabled() )
	{
		OnBtnCloseCamera();
	}
	if ( m_ui.btnCloseMic->isEnabled() )
	{
		OnBtnCloseMic();
	}
	if ( m_ui.btnCloseScreenShare->isEnabled() )
	{
		OnBtnCloseScreenShare();
	}
	setRoomUserType(E_RoomUserWatcher);
	
	//身份变化后，立即心跳上报身份，并重新请求房间成员列表
	sxbHeartBeat();
	sxbRoomIdList();
}

void Live::sendQuitRoom()
{
	sendGroupCustomCmd( AVIMCMD_ExitLive, g_pMainWindow->getUserId() );
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
	varmap.insert( "cover", "" );//TODO PC随心播暂不支持直播封面上传,所以暂时上传为空，后续加上
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
		iLiveLog_e( "suixinbo", "Sui xin bo heartbeat failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
	}
}

void Live::OnSxbRoomIdList( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		iLiveLog_e( "suixinbo", "Suixinbo get Room id list failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
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
		iLiveLog_e( "suixinbo", "Suixinbo report record video failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
		return ;
	}
}

void Live::iLiveQuitRoom()
{
	iLiveSDKWrap::getInstance()->quitRoom(OnQuitRoomSuc, OnQuitRoomErr, this);
}

void Live::iLiveChangeAuthority( uint64 authBits, const std::string& authBuffer )
{
	iLiveSDKWrap::getInstance()->changeAuthority(authBits, authBuffer, OnChangeAuthoritySuc, OnChangeAuthorityErr, this);
}

void Live::iLiveChangeRole( const std::string& szControlRole )
{
	iLiveSDKWrap::getInstance()->changeRole(szControlRole, OnChangeRoleSuc, OnChangeRoleErr, this);
}

int Live::iLiveSetSkinSmoothGrade( int grade )
{
	return iLiveSDKWrap::getInstance()->SetSkinSmoothGrade(grade);
}

int Live::iLiveSetSkinWhitenessGrade( int grade )
{
	return iLiveSDKWrap::getInstance()->SetSkinWhitenessGrade(grade);
}

void Live::OnQuitRoomSuc( void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	postCusEvent( g_pMainWindow, new Event(E_CEQuitRoom, 0, "") );
}

void Live::OnQuitRoomErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEQuitRoom, code, desc) );
}

void Live::OnChangeAuthoritySuc( void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEChangeAuth, 0, "") );
}

void Live::OnChangeAuthorityErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEChangeAuth, code, desc) );
}

void Live::OnChangeRoleSuc( void* data )
{
	
}

void Live::OnChangeRoleErr( int code, const std::string& desc, void* data )
{
	
}

void Live::OnRequestViewListSuc( void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	postCusEvent( g_pMainWindow, new Event(E_CERequestViewList, 0, "") );
	if ( pLive->m_toRequestIdentifiers.empty() )
	{
		pLive->m_pRequestViewsTimer->stop();
	}
	pLive->m_bIsRequesting = false;
}

void Live::OnRequestViewListErr( int code, const std::string& desc, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_bIsRequesting = false;
	pLive->m_pRequestViewsTimer->stop();
	postCusEvent( g_pMainWindow, new Event(E_CERequestViewList, code, desc) );
}

void Live::OnSendGroupMsgSuc( void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CESendGroupMsg, 0, "") );
}

void Live::OnSendGroupMsgErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CESendGroupMsg, code, desc) );
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
	sendInviteInteract();
}

void Live::OnActCancelInteract()
{
	RoomMember& roomber = m_roomMemberList[m_nCurSelectedMember];
	roomber.userType = E_RoomUserWatcher;
	updateMemberList();

	sendCancelInteract();
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
	postCusEvent( g_pMainWindow, new Event(E_CEStartRecordVideo, 0, "") );
}

void Live::OnStartRecordVideoErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEStartRecordVideo, code, desc) );
}

void Live::OnStopRecordSuc( std::list<std::string>& value, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	postCusEvent( g_pMainWindow, new Event(E_CEStopRecordVideo, 0, "") );
	pLive->sxbReportrecord();
}

void Live::OnStopRecordVideoErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEStopRecordVideo, code, desc) );
}

void Live::OnStartPushStreamSuc( TIMStreamRsp& value, void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_channelId = value.channel_id;
	pLive->m_pushUrls = value.urls;
	postCusEvent( g_pMainWindow, new Event(E_CEStartPushStream, 0, "") );
}

void Live::OnStartPushStreamErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEStartPushStream, code, desc) );
}

void Live::OnStopPushStreamSuc( void* data )
{
	Live* pLive = reinterpret_cast<Live*>(data);
	pLive->m_channelId = 0;
	pLive->m_pushUrls.clear();
	postCusEvent( g_pMainWindow, new Event(E_CEStopPushStream, 0, "") );
}

void Live::OnStopPushStreamErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEStopPushStream, code, desc) );
}

