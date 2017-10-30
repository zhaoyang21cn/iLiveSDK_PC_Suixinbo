#ifndef Util_h_
#define Util_h_

void ShowTips( const QString& title, const QString& desc, QWidget* parent = NULL );
void ShowSucTips( const QString& desc, QWidget* parent = NULL );
void ShowErrorTips( const QString& desc, QWidget* parent = NULL );
void ShowCodeErrorTips( const int code, const QString& desc, QWidget* parent = NULL, const QString& title = "Error" );

QString getFileNameByUrl(QString szUrl);

QString getTimeStrBySeconds(const int64 sec);

#endif//Util_h_
