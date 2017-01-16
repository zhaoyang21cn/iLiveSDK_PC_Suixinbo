#pragma once
#include "NetworkHelper.h"

enum E_SxbServerRelpy
{
	E_SxbOK,
	E_SxbTimeOut,//³¬Ê±
	E_SxbNetReplyError,
	E_SxbJsonParseError,//Json½âÎö´íÎó
};

typedef void (*SxbRecFun)(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

class SxbServerHelper
{
public:
	static void request( QVariantMap varmap, QString svc, QString cmd, SxbRecFun receiver, void* data );

private:
	SxbServerHelper(const QString& url, const QString& content, SxbRecFun receiver, void* data);
	~SxbServerHelper();
	void doRequest();

	static void OnNetworkReply(int errCode, const QByteArray& bytes, void* pCusData);

private:
	QString	  m_url;
	QString	  m_content;
	SxbRecFun m_receiver;
	void*	  m_pCusdata;
};

