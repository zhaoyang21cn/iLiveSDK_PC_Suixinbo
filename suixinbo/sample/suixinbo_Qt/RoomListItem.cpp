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

void RoomListItem::sxbWatcherAuthPrivMap()
{
	QVariantMap varmap;
	varmap.insert("identifier", g_pMainWindow->getUserId());
	varmap.insert("pwd", g_pMainWindow->getUserPassword());
	varmap.insert("appid", QString::number(SuixinboAppid));
	varmap.insert("accounttype", SuixinboAccountType);
	varmap.insert("roomnum", m_room.info.roomnum);
	varmap.insert("privMap", qint64(AUTH_BITS_DEFAULT) );
	SxbServerHelper::request(varmap, "account", "authPrivMap", OnSxbWatcherAuthPrivMap, this);
}

void RoomListItem::OnSxbWatcherJoinRoom( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	RoomListItem* pRoomListItem = reinterpret_cast<RoomListItem*>(pCusData);

	if (errorCode==E_SxbOK)
	{
		pRoomListItem->sxbWatcherAuthPrivMap();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pRoomListItem, FromBits("观众加入房间失败") );
		g_pMainWindow->setUseable(true);
	}
}

void RoomListItem::OnSxbWatcherAuthPrivMap(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData)
{
	RoomListItem* pRoomListItem = reinterpret_cast<RoomListItem*>(pCusData);

	if (datamap.contains("userSig"))
	{
		g_pMainWindow->setUserSig( datamap.value("userSig").toString() );
	}
	if (datamap.contains("token"))
	{
		g_pMainWindow->setToken( datamap.value("token").toString() );
	}
	if (datamap.contains("privMapEncrypt"))
	{
		pRoomListItem->m_room.info.privateMapKey = datamap.value("privMapEncrypt").toString();
	}

	if (errorCode==E_SxbOK)
	{
		pRoomListItem->iLiveJoinRoom();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pRoomListItem, FromBits("获取authBuffer失败") );
	}
}

void RoomListItem::iLiveJoinRoom()
{
	GetILive()->setLocalVideoCallBack(Live::OnLocalVideo, g_pMainWindow->getLiveView());
	GetILive()->setDeviceOperationCallback(Live::OnDeviceOperation, g_pMainWindow->getLiveView());
	GetILive()->setDeviceDetectCallback(Live::OnDeviceDetect, g_pMainWindow->getLiveView());
	iLiveRoomOption roomOption;
	roomOption.audioCategory = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//互动直播场景
	roomOption.roomId = m_room.info.roomnum;
	//roomOption.authBits = AUTH_BITS_JOIN_ROOM|AUTH_BITS_RECV_AUDIO|AUTH_BITS_RECV_CAMERA_VIDEO|AUTH_BITS_RECV_SCREEN_VIDEO;
	roomOption.controlRole = Guest;
	roomOption.memberStatusListener = Live::OnMemStatusChange;
	roomOption.roomDisconnectListener = Live::OnRoomDisconnect;
	roomOption.privateMapKey = String(m_room.info.privateMapKey.toStdString().data(), m_room.info.privateMapKey.toStdString().length());
	//roomOption.qualityParamCallback = Live::OnQualityParamCallback;
	roomOption.data = g_pMainWindow->getLiveView();
	GetILive()->joinRoom( roomOption, OniLiveJoinRoomSuc, OniLiveJoinRoomErr, this );
}

void RoomListItem::OniLiveJoinRoomSuc( void* data )
{
	RoomListItem* pRoomListItem = reinterpret_cast<RoomListItem*>(data);
	g_pMainWindow->setCurRoomIdfo(pRoomListItem->m_room);
	pRoomListItem->sendWatcherJoinRoom();

	Live* pLive = g_pMainWindow->getLiveView();
	pLive->setRoomID(pRoomListItem->m_room.info.roomnum);
	pLive->setRoomUserType(E_RoomUserWatcher);
	pLive->StartTimer();
	pLive->show();
}

void RoomListItem::OniLiveJoinRoomErr( int code, const char *desc, void* data )
{
	RoomListItem* pThis = reinterpret_cast<RoomListItem*>(data);
	ShowCodeErrorTips(code, desc, pThis, "Join iLive Room Error.");
	g_pMainWindow->setUseable(true);
}


void RoomListItem::sendWatcherJoinRoom()
{
	g_sendGroupCustomCmd( AVIMCMD_EnterLive, g_pMainWindow->getUserId() );
}