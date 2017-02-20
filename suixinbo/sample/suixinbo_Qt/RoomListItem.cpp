#include "stdafx.h"
#include "RoomListItem.h"

RoomListItem::RoomListItem( QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
	:QWidget(parent, f)
{
	m_ui.setupUi(this);
	m_ui.btnPic->setStyleSheet("QPushButton{ border-image:url(':/res/Resources/bg.png') 0px 0px no-repeat; }");
	connect( m_ui.btnPic, SIGNAL(clicked()), this, SLOT(onBtnPic()) );
}

void RoomListItem::setRoomParam( const Room& room )
{
	m_room = room;
	m_ui.lbTitle->setText(m_room.info.title);
	m_ui.lbName->setText(m_room.szId);
	m_ui.lbType->setText(m_room.info.type);
	m_ui.lbRoomMemNum->setText( FromBits("人数: ")+ QString::number(m_room.info.memsize) );
	m_ui.lbPraiseNum->setText( FromBits("点赞: ")+ QString::number(m_room.info.thumbup) );

	QString styleSheet;
	QString filePath = PicDownHelper::getPicPath()+getFileNameByUrl(m_room.info.cover)+".jpg";
	QFile file(filePath);
	if (file.exists())
	{
		styleSheet = QString("QPushButton{ border-image:url('%1') 0px 0px no-repeat; }").arg(filePath);
	}
	else
	{
		styleSheet = QString("QPushButton{ border-image:url('%1') 0px 0px no-repeat; }").arg(":/res/Resources/bg.png");
	}
	m_ui.btnPic->setStyleSheet(styleSheet);
}

void RoomListItem::onBtnPic()
{
	if ( g_pMainWindow->getLoginState() != E_Login )
	{
		ShowErrorTips( FromBits("请先登录"), this );
		return;
	}
	g_pMainWindow->setUseable(false);
	sxbWatcherJoinRoom();
}

void RoomListItem::sxbWatcherJoinRoom()
{
	QVariantMap varmap;
	varmap.insert( "token", g_pMainWindow->getToken() );
	varmap.insert( "id", g_pMainWindow->getUserId() );
	varmap.insert( "roomnum", m_room.info.roomnum );
	varmap.insert( "role", 0 );//成员0 主播1 上麦成员2
	varmap.insert( "operate", 0);//进入房间0  退出房间1
	SxbServerHelper::request(varmap, "live", "reportmemid", OnSxbWatcherJoinRoom, this);
}

void RoomListItem::OnSxbWatcherJoinRoom( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	RoomListItem* pRoomListItem = reinterpret_cast<RoomListItem*>(pCusData);

	if (errorCode==E_SxbOK)
	{
		pRoomListItem->iLiveJoinRoom();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pRoomListItem, FromBits("观众加入房间失败") );
		g_pMainWindow->setUseable(true);
	}
}

void RoomListItem::iLiveJoinRoom()
{
	ilivesdk::iLiveRoomOption roomOption;
	roomOption.roomId = m_room.info.roomnum;
	roomOption.audio_category = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//直播场景
	roomOption.auth_buffer = "";
	roomOption.control_role = Guest;
	roomOption.video_recv_mode = VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO; //半自动模式
	roomOption.m_autoRecvCameraListener = Live::OnSemiAutoRecvCameraVideo;
	roomOption.m_autoRecvScreenListener = Live::OnSemiAutoRecvScreenVideo;
	roomOption.m_autoRecvMediaFileListener = Live::OnSemiAutoRecvMediaFileVideo;
	roomOption.m_memberStatusListener = Live::OnMemStatusChange;
	roomOption.m_roomDisconnectListener = Live::OnRoomDisconnect;
	roomOption.data = g_pMainWindow->getLiveView();
	iLiveSDKWrap::getInstance()->joinRoom( roomOption, OniLiveJoinRoomSuc, OniLiveJoinRoomErr, this );
}

void RoomListItem::OniLiveJoinRoomSuc( void* data )
{
	RoomListItem* pRoomListItem = reinterpret_cast<RoomListItem*>(data);
	g_pMainWindow->setCurRoomIdfo(pRoomListItem->m_room);
	postCusEvent( g_pMainWindow, new Event(E_CEJoinRoom, 0, "") );

	pRoomListItem->sendWatcherJoinRoom();
}

void RoomListItem::OniLiveJoinRoomErr( int code, const std::string& desc, void* data )
{
	postCusEvent( g_pMainWindow, new Event(E_CEJoinRoom, code, desc) );
}


void RoomListItem::sendWatcherJoinRoom()
{
	sendGroupCustomCmd( AVIMCMD_EnterLive, g_pMainWindow->getUserId() );
}