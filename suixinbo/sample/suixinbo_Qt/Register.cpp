#include "stdafx.h"
#include "Register.h"

Register::Register( QWidget * parent /*= 0*/, Qt::WindowFlags f /*= 0*/ )
{
	m_ui.setupUi(this);

	connect( m_ui.btnRegister, SIGNAL(clicked()), this, SLOT(onBtnRegister()) );
}

Register::~Register()
{

}

void Register::onBtnRegister()
{
	sxbRegister();
}

void Register::sxbRegister()
{
	QString szUserName = m_ui.leUserName->text();
	QString szPassword = m_ui.lePassword->text();
	if ( szUserName.isEmpty() || szPassword.isEmpty() )
	{
		ShowErrorTips( "Please input UserName and Password", this );
		return;
	}

	QVariantMap varmap;
	varmap.insert("id",szUserName);
	varmap.insert("pwd",szPassword);
	SxbServerHelper::request( varmap, "account", "regist", OnRegister, this);
}

void Register::OnRegister( int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData )
{
	Register* pRegister = reinterpret_cast<Register*>(pCusData);
	
	if (errorCode==E_SxbOK)
	{
		ShowSucTips( "Register succeed!", pRegister );
		//pRegister->close();
	}
	else
	{
		ShowCodeErrorTips( errorCode, errorInfo, pRegister, FromBits("×¢²áÊ§°Ü") );
	}
}
