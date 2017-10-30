#include "stdafx.h"
#include "Util.h"

void ShowTips( const QString& title, const QString& desc, QWidget* parent /*= NULL */ )
{
	QMessageBox::information( parent, title, desc );
}

void ShowSucTips( const QString& desc, QWidget* parent /*= NULL*/ )
{
	QMessageBox::information( parent, "Succeed", desc );
}

void ShowErrorTips( const QString& desc, QWidget* parent /*= NULL*/ )
{
	QMessageBox::critical( parent, "Error", desc );
}

void ShowCodeErrorTips( const int code, const QString& desc, QWidget* parent /*= NULL*/, const QString& title /*= "Error"*/ )
{
	QString info;
	info += FromBits("´íÎóÂë:   ");
	info += QString::number(code);
	info += FromBits("\n´íÎóĞÅÏ¢: ");
	info += desc;
	QMessageBox::critical( parent, title, info );
}

QString getFileNameByUrl( QString szUrl )
{
	QString ret = szUrl.replace('/', '_').replace(':', '_');
	if ( ret.length()>200 )
	{
		ret = ret.right(200);
	}
	return ret;
}

QString getTimeStrBySeconds( const int64 sec )
{
	int hours = sec/3600;
	int minutes = (sec%3600)/60;
	int secs = sec%60;
	char res[16]={0};
	sprintf_s( res, 16, "%02d:%02d:%02d", hours, minutes, secs );
	return res;
}
