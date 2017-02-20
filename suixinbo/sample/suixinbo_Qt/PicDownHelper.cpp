#include "StdAfx.h"
#include "PicDownHelper.h"


QString PicDownHelper::ms_picPath = "./PicTemp/";

PicDownHelper::PicDownHelper(const QString& url, const QString& fileName, PicDownFun receiver, void* data)
{
	m_url = url;
	m_fileName = fileName;
	m_receiver = receiver;
	m_pCusdata = data;
}


PicDownHelper::~PicDownHelper()
{
}

void PicDownHelper::setPicPath( QString path )
{
	ms_picPath = path;
}

QString PicDownHelper::getPicPath()
{
	return ms_picPath;
}

void PicDownHelper::getPic( const QString& url, const QString& fileName, PicDownFun receiver, void* data )
{
	if ( url.isEmpty() || fileName.isEmpty() )
	{
		if (receiver)
		{
			receiver(E_PicDownUrlOrFileNameNULL, "url or fileName is NULL.", "", data);
		}
		return;
	}
	if ( !createTempDir() )
	{
		if (receiver)
		{
			receiver(E_PicDownUrlOrFileNameNULL, "Create temp file path error.", "", data);
		}
		return;
	}
	PicDownHelper* p = new PicDownHelper(url, fileName, receiver, data);
	p->doGetPic();
}

bool PicDownHelper::clearPicCache()
{
	QDir tempdir(ms_picPath);
	if ( tempdir.exists() )
	{
		bool bOK = tempdir.removeRecursively();
		if (!bOK)
		{
			return false;
		}
	}
	return true;
}

void PicDownHelper::doGetPic()
{
	//iLiveLog_d( "To get pic: %s", m_url.toUtf8().data() );
	NetworkHelper::get( m_url, OnNetworkReply, this );
}

void PicDownHelper::OnNetworkReply( int errCode, const QByteArray& bytes, void* pCusData )
{
	PicDownHelper* pPicDownHelper = reinterpret_cast<PicDownHelper*>(pCusData);
	if (errCode==E_NetTimeOut)
	{
		if (pPicDownHelper->m_receiver)
		{
			pPicDownHelper->m_receiver( E_PicDownTimeOut, "Not received reply unitl timeout.", "", pPicDownHelper->m_pCusdata );
		}
	}
	else if (errCode==E_NetReplyError)
	{
		if (pPicDownHelper->m_receiver)
		{
			pPicDownHelper->m_receiver( E_PicDownNetReplyError, "Network reply error.", "", pPicDownHelper->m_pCusdata);
		}
	}
	else if (errCode==E_NetOK)
	{
		QFile file( ms_picPath + pPicDownHelper->m_fileName );
		if ( file.open(QIODevice::WriteOnly|QIODevice::Truncate) )
		{
			file.write(bytes);
			file.close();
			if (pPicDownHelper->m_receiver)
			{
				pPicDownHelper->m_receiver(E_PicDownOK, "", ms_picPath+pPicDownHelper->m_fileName, pPicDownHelper->m_pCusdata);
			}
		}
		else
		{
			if (pPicDownHelper->m_receiver)
			{
				pPicDownHelper->m_receiver(E_PicDownOpenFileError, "Open file for write error.", "", pPicDownHelper->m_pCusdata);
			}
		}		
	}

	delete pPicDownHelper;
}

bool PicDownHelper::createTempDir()
{	
	QDir tempdir(ms_picPath);
	if ( !tempdir.exists() )
	{
		bool bOK = QDir::current().mkdir(ms_picPath);
		if ( !bOK )
		{
			return false;
		}
	}
	return true;
}

