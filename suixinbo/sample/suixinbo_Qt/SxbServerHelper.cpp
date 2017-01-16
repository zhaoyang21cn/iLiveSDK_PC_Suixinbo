#include "StdAfx.h"
#include "SxbServerHelper.h"

SxbServerHelper::SxbServerHelper( const QString& url, const QString& content, SxbRecFun receiver, void* data )
{
	m_url = url;
	m_content = content;
	m_receiver = receiver;
	m_pCusdata = data;
}

SxbServerHelper::~SxbServerHelper()
{
	
}

void SxbServerHelper::request( QVariantMap varmap, QString svc, QString cmd, SxbRecFun receiver, void* data )
{
	QString szUrl =  g_pMainWindow->getServerUrl() + "?svc=" + svc+ "&cmd=" + cmd;
	QJsonDocument jsondoc;
	jsondoc.setObject( QJsonObject::fromVariantMap(varmap) );
	QString szContent = jsondoc.toJson();
	SxbServerHelper* p = new SxbServerHelper(szUrl, szContent, receiver, data);
	p->doRequest();
}

void SxbServerHelper::doRequest()
{
	iLiveLog_d( "Send:\n%s", m_content.toUtf8().data() );
	NetworkHelper::post( m_url, m_content, OnNetworkReply, this );
}

void SxbServerHelper::OnNetworkReply( int errCode, const QByteArray& bytes, void* pCusData )
{
	SxbServerHelper* pSxbServerHelper = reinterpret_cast<SxbServerHelper*>(pCusData);
	
	if (!pSxbServerHelper->m_receiver)
	{
		delete pSxbServerHelper;
		return;
	}

	if (errCode==E_NetTimeOut)
	{
		pSxbServerHelper->m_receiver(E_SxbTimeOut, "Not received reply unitl timeout.", QVariantMap(), pSxbServerHelper->m_pCusdata);
	}
	else if (errCode==E_NetReplyError)
	{
		pSxbServerHelper->m_receiver(E_SxbNetReplyError, "Network reply error.", QVariantMap(), pSxbServerHelper->m_pCusdata);
	}
	else if (errCode==E_NetOK)
	{
		iLiveLog_d( "Receive: %s ", bytes.data() );
		
		//解析接收到的json
		QJsonParseError json_error;
		QJsonDocument parse_doucment = QJsonDocument::fromJson(bytes, &json_error);
		if( json_error.error == QJsonParseError::NoError && parse_doucment.isObject() )
		{
			QJsonObject obj = parse_doucment.object();
			QVariantMap varmap = obj.toVariantMap();

			int errorCode = E_SxbJsonParseError;
			QString errorInfo;
			QVariantMap datamap;
			if (varmap.contains("errorCode"))
			{
				errorCode = varmap.value("errorCode").toInt();
			}
			if (varmap.contains("errorInfo"))
			{
				errorInfo = varmap.value("errorInfo").toString();
			}
			if (varmap.contains("data"))
			{
				datamap = varmap.value("data").toMap();
			}
			pSxbServerHelper->m_receiver(errorCode, errorInfo, datamap, pSxbServerHelper->m_pCusdata);
		}
		else
		{
			pSxbServerHelper->m_receiver(E_SxbJsonParseError, "Josn parse error.", QVariantMap(), pSxbServerHelper->m_pCusdata);
		}
	}
	delete pSxbServerHelper;
}

