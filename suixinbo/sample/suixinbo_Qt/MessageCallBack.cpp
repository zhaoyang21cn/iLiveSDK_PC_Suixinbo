#include "stdafx.h"
#include "MessageCallBack.h"

void sendC2CCustomCmd( QString dstUser, E_CustomCmd userAction, QString actionParam, SuccessCalllback suc /*= NULL*/, ErrorCallback err /*= NULL*/, void* data /*= NULL */ )
{
	QVariantMap varmap;
	varmap.insert("userAction", (int)userAction);
	varmap.insert("actionParam", actionParam);
	QJsonDocument doc;
	doc.setObject( QJsonObject::fromVariantMap(varmap) );

	TIMMessage message;
	imcore::TIMCustomElem cusElem;
	cusElem.set_ext(LiveNoti);
	cusElem.set_data( QString( doc.toJson() ).toStdString() );
	message.AddElem(&cusElem);
	iLiveSDKWrap::getInstance()->sendC2CMessage( dstUser.toStdString(), message, suc, err, data );
}

void sendGroupCustomCmd( E_CustomCmd userAction, QString actionParam, SuccessCalllback suc /*= NULL*/, ErrorCallback err /*= NULL*/, void* data /*= NULL */ )
{
	QVariantMap varmap;
	varmap.insert( "userAction", (int)userAction );
	varmap.insert( "actionParam", actionParam );
	QJsonDocument doc;
	doc.setObject( QJsonObject::fromVariantMap(varmap) );

	TIMMessage message;
	imcore::TIMCustomElem cusElem;
	cusElem.set_ext(LiveNoti);
	cusElem.set_data( QString( doc.toJson() ).toStdString() );
	message.AddElem(&cusElem);
	iLiveSDKWrap::getInstance()->sendGroupMessage( message, suc, err, data );
}

QQueue<TIMMessage> MessageCallBack::ms_messageQueue;

void MessageCallBack::OnNewMessage( const std::vector<TIMMessage> &msgs )
{
	for (uint32 i=0; i<msgs.size(); ++i)
	{
		ms_messageQueue.push_back( msgs[i] );
	}
	postCusEvent( g_pMainWindow, new Event(E_CERecMsg, 0, "") );
}

void ForceOfflineCallBack::OnForceOffline()
{
	g_pMainWindow->OnForceOffline();
}

