#pragma once
#include "NetworkHelper.h"

enum E_PicDownRelpy
{
	E_PicDownOK,
	E_PicDownTimeOut,//超时
	E_PicDownNetReplyError,
	E_PicDownUrlOrFileNameNULL,//传入的url或者fileName是空
	E_PicDownOpenFileError,//打开文件失败
};

typedef void (*PicDownFun)(int errorCode, QString errorInfo, QString picPath, void* pCusData);

class PicDownHelper
{
public:
	static void setPicPath(QString path);
	static QString getPicPath();
	static void getPic( const QString& url, const QString& fileName, PicDownFun receiver, void* data );
	static bool clearPicCache();

private:
	PicDownHelper(const QString& url, const QString& fileName, PicDownFun receiver, void* data);
	~PicDownHelper();

	void doGetPic();
	static void OnNetworkReply(int errCode, const QByteArray& bytes, void* pCusData);
	static bool	createTempDir();

private:
	static QString ms_picPath;//下载的图片保存路径

	QString		m_url;
	QString		m_fileName;
	PicDownFun	m_receiver;
	void*		m_pCusdata;
};

