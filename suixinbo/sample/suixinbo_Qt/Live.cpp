#include "stdafx.h"
#include "Live.h"

Live::Live( QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
	:QDialog(parent, f)
{
	//setAttribute(Qt::WA_DeleteOnClose);
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

	QDesktopWidget* desktopWidget = QApplication::desktop();
	QRect screenRect = desktopWidget->screenGeometry();
	int nScreenX = screenRect.width();
	int nScreenY = screenRect.height();
	m_ui.sbX1->setValue(nScreenX);
	m_ui.sbY1->setValue(nScreenY);

	m_nRoomSize = 0;

	m_pTimer = new QTimer(this);
	m_pDelayUpdateTimer = new QTimer(this);

	m_nCurSelectedMember = -1;

	m_pMenuInviteInteract = new QMenu(this);
	QAction* pActInviteInteract = new QAction( QString::fromLocal8Bit("连线"), m_pMenuInviteInteract );
	m_pMenuInviteInteract->addAction(pActInviteInteract);
	m_pMenuCancelInteract = new QMenu(this);
	QAction* pActCancelInteract = new QAction( QString::fromLocal8Bit("断开"), m_pMenuInviteInteract );
	m_pMenuCancelInteract->addAction(pActCancelInteract);

	m_ui.cbRecordDataType->addItem( FromBits("摄像头"), QVariant(E_RecordCamera) );
	m_ui.cbRecordDataType->addItem( FromBits("屏幕分享"), QVariant(E_RecordScreen) );
	m_ui.cbRecordDataType->setCurrentIndex(0);

	m_ui.cbPushDataType->addItem( FromBits("摄像头"), QVariant(E_PushCamera) );
	m_ui.cbPushDataType->addItem( FromBits("屏幕分享"), QVariant(E_PushScreen) );
	m_ui.cbPushDataType->setCurrentIndex(0);

	m_ui.cbPushEncodeType->addItem(FromBits("HLS"), QVariant(imcore::HLS) );
	m_ui.cbPushEncodeType->addItem(FromBits("RTMP"),QVariant(imcore::RTMP) );
	m_ui.cbPushEncodeType->setCurrentIndex(0);

	m_channelId = 0;

	m_bIsRequesting = false;
	m_pRequestViewsTimer = new QTimer(this);

	connect( m_ui.btnOpenCamera, SIGNAL(clicked()), this, SLOT(OnBtnOpenCamera()) );
	connect( m_ui.btnCloseCamera, SIGNAL(clicked()), this, SLOT(OnBtnCloseCamera()) );
	connect( m_ui.btnOpenMic, SIGNAL(clicked()), this, SLOT(OnBtnOpenMic()) );
	connect( m_ui.btnCloseMic, SIGNAL(clicked()), this, SLOT(OnBtnCloseMic()) );
	connect( m_ui.btnOpenPlayer, SIGNAL(clicked()), this, SLOT(OnBtnOpenPlayer()) );
	connect( m_ui.btnClosePlayer, SIGNAL(clicked()), this, SLOT(OnBtnClosePlayer()) );
	connect( m_ui.btnOpenScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnOpenScreenShare()) );
	connect( m_ui.btnCloseScreenShare, SIGNAL(clicked()), this, SLOT(OnBtnCloseScreenShare()) );
	connect( m_ui.btnSendGroupMsg, SIGNAL(clicked()), this, SLOT(OnBtnSendGroupMsg()) );
	connect( m_ui.btnStartRecord, SIGNAL(clicked()), this, SLOT(OnBtnStartRecord()) );
	connect( m_ui.btnStopRecord, SIGNAL(clicked()), this, SLOT(OnBtnStopRecord()) );
	connect( m_ui.btnStartPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStartPushStream()) );
	connect( m_ui.btnStopPushStream, SIGNAL(clicked()), this, SLOT(OnBtnStopPushStream()) );
	connect( m_ui.btnPraise, SIGNAL(clicked()), this, SLOT(OnBtnPraise()) );
	connect( m_pTimer, SIGNAL(timeout()), this, SLOT(OnTimer()) );
	connect( m_pDelayUpdateTimer, SIGNAL(timeout()), this, SLOT(OnDelayUpdateTimer()) );
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
	switch(m_userType)
	{
	case E_RoomUserCreator:
		{
			m_ui.cameraGB->setVisible(true);
			m_ui.btnOpenCamera->setEnabled(true);
			m_ui.btnCloseCamera->setEnabled(false);
			getCameraList();

			m_ui.microphoneGB->setVisible(true);
			m_ui.btnOpenMic->setEnabled(true);
			m_ui.btnCloseMic->setEnabled(false);

			m_ui.screenShareGB->setVisible(true);
			m_ui.btnOpenScreenShare->setEnabled(true);
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
			getCameraList();

			m_ui.microphoneGB->setVisible(true);
			m_ui.btnOpenMic->setEnabled(true);
			m_ui.btnCloseMic->setEnabled(false);

			m_ui.screenShareGB->setVisible(true);
			m_ui.btnOpenScreenShare->setEnabled(true);
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
	if ( LiveSDK::getInstance()->getCurCameraState() || LiveSDK::getInstance()->getScreenShareState() )
	{
		m_ui.pushStreamGB->setEnabled(true);
		m_ui.recordGB->setEnabled(true);
	}
	else
	{
		if ( m_ui.btnStopRecord->isEnabled() )
		{
			OnBtnStopRecord();
		}
		if ( m_ui.btnStopPushStream->isEnabled() )
		{
			OnBtnStopPushStream();
		}
		m_ui.pushStreamGB->setEnabled(false);
		m_ui.recordGB->setEnabled(false);
		return;
	}

	if ( LiveSDK::getInstance()->getRecordState() )//录制中
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

	if( LiveSDK::getInstance()->getPushStreamState() )//推流中
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
		imcore::TIMElem* pElem = msg.GetElem(i);
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
		case kElemGroupReport://群系统消息: TIM_GROUP_SYSTEM_ADD_GROUP_REQUEST_TYPE等类型
			{
				if ( isVisible() && GetGroupReportType(pElem) == TIM_GROUP_SYSTEM_DELETE_GROUP_TYPE ) //群解散
				{
					ShowTips( FromBits("主播退出房间"), FromBits("主播已经退出房间,点击确认退出房间."), this );
					close();
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
			//nothing to do
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
	iLiveLog_d("OnMemStatusChange");
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
	iLiveLog_d("OnSemiAutoRecvCameraVideo");
}

void Live::OnRoomDisconnect( int reason, void* data )
{
	iLiveLog_d("OnRoomDisconnect");
}

void Live::OnLocalVideo( VideoFrame* video_frame, void* custom_data )
{
	//iLiveLog_d("OnLocalVideo");
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
	//iLiveLog_d("OnRemoteVideo");
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
			iLiveLog_e("Render is not enough.");
		}
	}
}

void Live::OnBtnOpenCamera()
{
	//////////////////////////////////////////////////
	//PC端SDK本可以支持摄像头和屏幕分享同时打开,为了Android和ios端随心播的显示方便，
	//限制每个PC端用户只允许打开摄像头和屏幕分享之一,需要同时打开屏幕分享和摄像头
	//的用户请注释掉本段代码;
	if ( LiveSDK::getInstance()->getScreenShareState() )
	{
		ShowTips( FromBits("提示"), FromBits("请先关闭屏幕分享"), this );
		return;
	}
	//////////////////////////////////////////////////

	if (m_cameraList.size()==0)
	{
		ShowErrorTips( FromBits("无可用的摄像头."), this );
		return;
	}
	m_ui.btnOpenCamera->setEnabled(false);
	int ndx = m_ui.cbCamera->currentIndex();
	int nRet = LiveSDK::getInstance()->openCamera(m_cameraList[ndx].first);
	if (nRet==0)
	{
		m_ui.btnCloseCamera->setEnabled(true);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenCamera->setEnabled(true);
		ShowErrorTips( "Open Camera Failed.", this );
	}
}

void Live::OnBtnCloseCamera()
{
	m_ui.btnCloseCamera->setEnabled(false);
	int nRet = LiveSDK::getInstance()->closeCamera();
	if (nRet==0)
	{		
		m_ui.btnOpenCamera->setEnabled(true);
		m_pLocalCameraRender->update();
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnCloseCamera->setEnabled(true);
		ShowErrorTips( "Close Camera Failed.", this );
	}
}

void Live::OnBtnOpenMic()
{
	m_ui.btnOpenMic->setEnabled(false);
	int nRet = LiveSDK::getInstance()->openMic();
	if (nRet==0)
	{		
		m_ui.btnCloseMic->setEnabled(true);
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
	int nRet = LiveSDK::getInstance()->closeMic();
	if (nRet==0)
	{
		m_ui.btnOpenMic->setEnabled(true);
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
	int nRet = LiveSDK::getInstance()->openPlayer();
	if (nRet==0)
	{		
		m_ui.btnClosePlayer->setEnabled(true);
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
	int nRet = LiveSDK::getInstance()->closePlayer();
	if (nRet==0)
	{		
		m_ui.btnOpenPlayer->setEnabled(true);
	}
	else
	{
		m_ui.btnClosePlayer->setEnabled(true);
		ShowErrorTips( "Close Player Failed.", this );
	}
}

void Live::OnBtnOpenScreenShare()
{
	//////////////////////////////////////////////////
	//PC端SDK本可以支持摄像头和屏幕分享同时打开,为了Android和ios端随心播的显示方便，
	//限制每个PC端用户只允许打开摄像头和屏幕分享之一,需要同时打开屏幕分享和摄像头
	//的用户请注释掉本段代码;
	if ( LiveSDK::getInstance()->getCurCameraState() )
	{
		ShowTips( FromBits("提示"), FromBits("请先关闭摄像头"), this );
		return;
	}
	//////////////////////////////////////////////////

	m_ui.btnOpenScreenShare->setEnabled(false);
	int x0 = m_ui.sbX0->value();
	int y0 = m_ui.sbY0->value();
	int x1 = m_ui.sbX1->value();
	int y1 = m_ui.sbY1->value();
	int fps= m_ui.sbFPS->value();
	int nRet = LiveSDK::getInstance()->openScreenShare(x0, y0, x1, y1, fps);
	if (nRet==0)
	{		
		m_ui.btnCloseScreenShare->setEnabled(true);
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnOpenScreenShare->setEnabled(true);
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

void Live::OnBtnCloseScreenShare()
{
	m_ui.btnCloseScreenShare->setEnabled(false);
	int nRet = LiveSDK::getInstance()->closeScreenShare();
	if (nRet==0)
	{
		m_ui.btnOpenScreenShare->setEnabled(true);
		m_pScreenShareRender->update();
		updatePushAndRecordStateUI();
	}
	else
	{
		m_ui.btnCloseScreenShare->setEnabled(true);
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
	imcore::TIMTextElem textElem;
	textElem.set_content( szText.toStdString() );
	message.AddElem(&textElem);
	
	addMsgLab( QString::fromLocal8Bit("我说： ") + szText );
	LiveSDK::getInstance()->sendGroupMessage(  message, OnSendGroupMsgSuc, OnSendGroupMsgErr, this );
}

void Live::OnBtnStartRecord()
{
	bool bClickedOK;
	QString inputName = QInputDialog::getText( this, FromBits("录制文件名"),FromBits("请输入录制文件名"), QLineEdit::Normal, "", &bClickedOK );
	if (!bClickedOK)//用户点击了取消按钮
	{
		return;
	}
	if ( inputName.isEmpty() )
	{
		ShowErrorTips( FromBits("录制文件名不能为空"), this );
		return;
	}	
	//随心播后台要求录制文件名统一格式"sxb_用户id_用户传入的文件名"
	QString fileName = "sxb_";
	fileName += g_pMainWindow->getUserId();
	fileName += "_";
	fileName += inputName;
	
	m_recordOpt.filename = fileName.toStdString();
	m_recordOpt.record_data_type = (ilivesdk::E_RecordDataType)m_ui.cbRecordDataType->itemData( m_ui.cbRecordDataType->currentIndex() ).value<int>();
	LiveSDK::getInstance()->startRecordVideo(m_recordOpt, OnStartRecordVideoSuc, OnStartRecordVideoErr, this);
}

void Live::OnBtnStopRecord()
{
	LiveSDK::getInstance()->stopRecordVideo( OnStopRecordSuc, OnStopRecordVideoErr, this);
}

void Live::OnBtnStartPushStream()
{
	m_pushOpt.channel_name = g_pMainWindow->getUserId().toStdString();
	m_pushOpt.channel_desc = g_pMainWindow->getUserId().toStdString();
	m_pushOpt.push_data_type = (E_PushDataType)m_ui.cbPushDataType->itemData( m_ui.cbPushDataType->currentIndex() ).value<int>();
	m_pushOpt.encode = (imcore::E_TIMStreamEncode)m_ui.cbPushEncodeType->itemData( m_ui.cbPushEncodeType->currentIndex() ).value<int>();
	LiveSDK::getInstance()->startPushStream( m_pushOpt, OnStartPushStreamSuc, OnStartPushStreamErr, this );
}

void Live::OnBtnStopPushStream()
{
	LiveSDK::getInstance()->stopPushStream(m_channelId, OnStopPushStreamSuc, OnStopPushStreamErr, this);
}

void Live::OnBtnPraise()
{
	sendGroupCustomCmd( AVIMCMD_Praise, g_pMainWindow->getUserId() );
	addMsgLab( g_pMainWindow->getUserId()+FromBits("点赞") );
}

void Live::OnTimer()
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
	int nRet = LiveSDK::getInstance()->requestViewList(m_toRequestIdentifiers, m_toRequestViews, OnRequestViewListSuc, OnRequestViewListErr, this);
	m_toRequestIdentifiers.clear();
	m_toRequestViews.clear();
	if (nRet!=NO_ERR)
	{
		iLiveLog_e("requestViewList failed.");
		m_pRequestViewsTimer->stop();
		m_bIsRequesting = false;		
		ShowErrorTips( "requestViewList failed.", this );
	}
}

void Live::OnDelayUpdateTimer()
{
	m_pDelayUpdateTimer->stop();
	this->update();
}

void Live::closeEvent( QCloseEvent* event )
{
	m_ui.liMsgs->clear();
	freeAllCameraVideoRender();	
	stopTimer();
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

void Live::getCameraList()
{
	LiveSDK::getInstance()->getCameraList(m_cameraList);
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
		iLiveLog_e( "Sui xin bo heartbeat failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
	}
}

void Live::OnSxbRoomIdList( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Live* pLive = reinterpret_cast<Live*>(pCusData);

	if (errorCode!=E_SxbOK)
	{
		iLiveLog_e( "Suixinbo get Room Id List failed: %d %s", errorCode, errorInfo.toStdString().c_str() );
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

void Live::iLiveQuitRoom()
{
	LiveSDK::getInstance()->quitRoom(OnQuitRoomSuc, OnQuitRoomErr, this);
}

void Live::iLiveChangeAuthority( uint64 authBits, const std::string& authBuffer )
{
	LiveSDK::getInstance()->changeAuthority(authBits, authBuffer, OnChangeAuthoritySuc, OnChangeAuthorityErr, this);
}

void Live::iLiveChangeRole( const std::string& szControlRole )
{
	LiveSDK::getInstance()->changeRole(szControlRole, OnChangeRoleSuc, OnChangeRoleErr, this);
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
	iLiveLog_d("Change Role Suc.");
}

void Live::OnChangeRoleErr( int code, const std::string& desc, void* data )
{
	iLiveLog_d("Change Role Error.");
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
	if ( pLive->m_toRequestIdentifiers.empty() )
	{
		pLive->m_pRequestViewsTimer->stop();
	}
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
	postCusEvent( g_pMainWindow, new Event(E_CEStopRecordVideo, 0, "") );
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
