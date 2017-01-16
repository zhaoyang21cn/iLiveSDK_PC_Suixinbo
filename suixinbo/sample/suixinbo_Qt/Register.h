#ifndef Register_h_
#define Register_h_

#include "ui_Register.h"

class Register : public QDialog
{
	Q_OBJECT
public:
	Register(QWidget * parent = 0, Qt::WindowFlags f = 0);
	virtual ~Register();

private slots:
	void onBtnRegister();

private:
	void sxbRegister();
	static void OnRegister(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

private:
	Ui::Register m_ui;
};

#endif//Register_h_