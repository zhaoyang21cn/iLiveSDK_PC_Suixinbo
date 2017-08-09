#include "stdafx.h"

void g_sendC2CCustomCmd( QString dstUser, E_CustomCmd userAction, QString actionParam, iLiveSucCallback suc /*= NULL*/, iLiveErrCallback err /*= NULL*/, void* data /*= NULL */ )
{
	QVariantMap varmap;
	varmap.insert("userAction", (int)userAction);
	varmap.insert("actionParam", actionParam);
	QJsonDocument doc;
	doc.setObject( QJsonObject::fromVariantMap(varmap) );

	Message message;
	MessageCustomElem *cusElem = new MessageCustomElem(QString( doc.toJson() ).toStdString().c_str(), LiveNoti);
	message.elems.push_back(cusElem);
	GetILive()->sendC2CMessage( dstUser.toStdString().c_str(), message, suc, err, data );
}

void g_sendGroupCustomCmd( E_CustomCmd userAction, QString actionParam, iLiveSucCallback suc /*= NULL*/, iLiveErrCallback err /*= NULL*/, void* data /*= NULL */ )
{
	QVariantMap varmap;
	varmap.insert( "userAction", (int)userAction );
	varmap.insert( "actionParam", actionParam );
	QJsonDocument doc;
	doc.setObject( QJsonObject::fromVariantMap(varmap) );

	Message message;
	MessageCustomElem *cusElem = new MessageCustomElem(QString( doc.toJson() ).toStdString().c_str(), LiveNoti);
	message.elems.push_back(cusElem);
	GetILive()->sendGroupMessage( message, suc, err, data );
}
