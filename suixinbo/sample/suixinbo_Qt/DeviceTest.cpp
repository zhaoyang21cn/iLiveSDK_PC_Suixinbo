#include "stdafx.h"
#include "DeviceTest.h"

DeviceTest::DeviceTest(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);

	//去掉QDialog右上角的问号按钮
	Qt::WindowFlags flags = Qt::Dialog;
	flags |= Qt::WindowCloseButtonHint;
	setWindowFlags(flags);

	m_nCurCameraIndex = 0;
	m_nCurMicIndex = 0;
	m_nCurPlayerIndex = 0;
}

DeviceTest::~DeviceTest()
{

}

void DeviceTest::OnDeviceOperation( E_DeviceOperationType oper, int retCode, void* data )
{
	DeviceTest* pThis = reinterpret_cast<DeviceTest*>(data);
	switch(oper)
	{
	case E_OpenCamera:
		{
			if(retCode != NO_ERR)
			{
				ShowCodeErrorTips(retCode, "Open camera test failed.", pThis);
			}
			else
			{
				pThis->m_ui.widRender->setView( g_pMainWindow->getUserId().toStdString().c_str(), VIDEO_SRC_TYPE_CAMERA );
			}
			pThis->m_ui.btnCamera->setEnabled(true);
			pThis->updateCameraState();
			break;
		}
	case E_CloseCamera:
		{
			if (retCode != NO_ERR)
			{
				ShowCodeErrorTips(retCode, "Close camera test failed.", pThis);
			}
			else
			{
				pThis->m_ui.widRender->remove();
			}
			pThis->m_ui.btnCamera->setEnabled(true);
			pThis->updateCameraState();
			break;
		}
	case E_OpenMic:
		{
			if(retCode != NO_ERR)
			{
				ShowCodeErrorTips(retCode, "Open mic test failed.", pThis);
			}
			pThis->m_ui.btnMic->setEnabled(true);
			pThis->updateMicState();
			pThis->updateMicVol();
			break;
		}
	case E_CloseMic:
		{
			if (retCode != NO_ERR)
			{
				ShowCodeErrorTips(retCode, "Close mic test failed.", pThis);
			}
			pThis->m_ui.btnMic->setEnabled(true);
			pThis->updateMicState();
			pThis->updateMicVol();
			break;
		}
	case E_OpenPlayer:
		{
			if(retCode != NO_ERR)
			{
				ShowCodeErrorTips(retCode, "Open player test failed.", pThis);
			}
			pThis->m_ui.btnPlayer->setEnabled(true);
			pThis->updatePlayerState();
			pThis->updatePlayerVol();
			break;
		}
	case E_ClosePlayer:
		{
			if (retCode != NO_ERR)
			{
				ShowCodeErrorTips(retCode, "Close player test failed.", pThis);
			}
			pThis->m_ui.btnPlayer->setEnabled(true);
			pThis->updatePlayerState();
			pThis->updatePlayerVol();
			break;
		}
	}
}

void DeviceTest::OnCameraVideo( const LiveVideoFrame* video_frame, void* data )
{
	DeviceTest* pThis = reinterpret_cast<DeviceTest*>(data);
	pThis->m_ui.widRender->doRender(video_frame);
}

void DeviceTest::OnDeviceDetect( void* data )
{
	DeviceTest* pThis = reinterpret_cast<DeviceTest*>(data);
	pThis->updateCameraList();
	pThis->updateMicList();
	pThis->updatePlayerList();
}

void DeviceTest::showEvent( QShowEvent *event )
{
	g_pMainWindow->setUseable(false);

	updateCameraList();
	updateCameraState();

	updateMicList();
	updateMicState();
	updateMicVol();

	updatePlayerList();
	updatePlayerState();
	updatePlayerVol();

	GetILive()->setSkinSmoothGrade( m_ui.sbSkinSmooth->value() );
	GetILive()->setSkinWhitenessGrade( m_ui.sbSkinWhite->value() );
}

void DeviceTest::closeEvent( QCloseEvent *event )
{
	m_ui.widRender->remove();
	GetILive()->setDeviceOperationCallback(NULL, NULL);
	GetILive()->setLocalVideoCallBack(NULL, NULL);
	GetILive()->stopDeviceTest(NULL, NULL, NULL);

	g_pMainWindow->setUseable(true);
}

void DeviceTest::on_btnCamera_clicked()
{
	m_ui.btnCamera->setEnabled(false);
	if ( GetILive()->getCurCameraState() )
	{
		closeCamera();
	}
	else
	{
		openCamera();
	}
}

void DeviceTest::on_btnMic_clicked()
{
	m_ui.btnMic->setEnabled(false);
	if ( GetILive()->getCurMicState() )
	{
		closeMic();
	}
	else
	{
		openMic();
	}
}

void DeviceTest::on_hsMicVol_valueChanged( int value )
{
	int nRet = GetILive()->setMicVolume(value);
	if (nRet == NO_ERR)
	{
		m_ui.sbMicVol->blockSignals(true);
		m_ui.sbMicVol->setValue(value);
		m_ui.sbMicVol->blockSignals(false);
	}
}

void DeviceTest::on_sbMicVol_valueChanged( int value )
{
	int nRet = GetILive()->setMicVolume(value);
	if (nRet == NO_ERR)
	{
		m_ui.hsMicVol->blockSignals(true);
		m_ui.hsMicVol->setValue(value);
		m_ui.hsMicVol->blockSignals(false);
	}
}

void DeviceTest::on_btnPlayer_clicked()
{
	m_ui.btnPlayer->setEnabled(false);
	if ( GetILive()->getCurPlayerState() )
	{
		closePlayer();
	}
	else
	{
		openPlayer();
	}
}

void DeviceTest::on_hsPlayerVol_valueChanged( int value )
{
	int nRet = GetILive()->setPlayerVolume(value);
	if (nRet == NO_ERR)
	{
		m_ui.sbPlayerVol->blockSignals(true);
		m_ui.sbPlayerVol->setValue(value);
		m_ui.sbPlayerVol->blockSignals(false);
	}
}

void DeviceTest::on_sbPlayerVol_valueChanged( int value )
{
	int nRet = GetILive()->setPlayerVolume(value);
	if (nRet == NO_ERR)
	{
		m_ui.hsPlayerVol->blockSignals(true);
		m_ui.hsPlayerVol->setValue(value);
		m_ui.hsPlayerVol->blockSignals(false);
	}
}

void DeviceTest::on_vsSkinSmooth_valueChanged( int value )
{
	int nRet = GetILive()->setSkinSmoothGrade(value);
	if (nRet == NO_ERR)
	{
		m_ui.sbSkinSmooth->blockSignals(true);
		m_ui.sbSkinSmooth->setValue(value);
		m_ui.sbSkinSmooth->blockSignals(false);
	}
}

void DeviceTest::on_sbSkinSmooth_valueChanged( int value )
{
	int nRet = GetILive()->setSkinSmoothGrade(value);
	if (nRet == NO_ERR)
	{
		m_ui.vsSkinSmooth->blockSignals(true);
		m_ui.vsSkinSmooth->setValue(value);
		m_ui.vsSkinSmooth->blockSignals(false);
	}
}

void DeviceTest::on_vsSkinWhite_valueChanged( int value )
{
	int nRet = GetILive()->setSkinWhitenessGrade(value);
	if (nRet == NO_ERR)
	{
		m_ui.sbSkinWhite->blockSignals(true);
		m_ui.sbSkinWhite->setValue(value);
		m_ui.sbSkinWhite->blockSignals(false);
	}
}

void DeviceTest::on_sbSkinWhite_valueChanged( int value )
{
	int nRet = GetILive()->setSkinWhitenessGrade(value);
	if (nRet == NO_ERR)
	{
		m_ui.vsSkinWhite->blockSignals(true);
		m_ui.vsSkinWhite->setValue(value);
		m_ui.vsSkinWhite->blockSignals(false);
	}
}

void DeviceTest::updateCameraList()
{
	int nRet = GetILive()->getCameraList(m_cameraList);
	if (nRet == NO_ERR)
	{
		m_ui.cbCamera->clear();
		for(int i=0; i<m_cameraList.size(); ++i)
		{
			m_ui.cbCamera->addItem( FromBits( m_cameraList[i].second.c_str() ) );
		}
		m_nCurCameraIndex = iliveClamp( m_nCurCameraIndex, 0, m_cameraList.size()-1 );
		m_ui.cbCamera->setCurrentIndex(m_nCurCameraIndex);
	}
}

void DeviceTest::updateCameraState()
{
	if ( GetILive()->getCurCameraState() )
	{
		m_ui.btnCamera->setText( FromBits("关闭摄像头") );
	}
	else
	{
		m_ui.btnCamera->setText( FromBits("打开摄像头") );
	}
}

void DeviceTest::openCamera()
{
	if (m_cameraList.size()==0)
	{
		ShowErrorTips( FromBits("无可用的摄像头."), this );
		m_ui.btnCamera->setEnabled(true);
		return;
	}
	int ndx = m_ui.cbCamera->currentIndex();
	GetILive()->openCamera( m_cameraList[ndx].first.c_str() );
}

void DeviceTest::closeCamera()
{
	GetILive()->closeCamera();
}

void DeviceTest::updateMicList()
{
	int nRet = GetILive()->getMicList(m_micList);
	if (nRet == NO_ERR)
	{
		m_ui.cbMic->clear();
		for(int i=0; i<m_micList.size(); ++i)
		{
			m_ui.cbMic->addItem( FromBits( m_micList[i].second.c_str() ) );
		}
		m_nCurMicIndex = iliveClamp( m_nCurMicIndex, 0, m_micList.size()-1 );
		m_ui.cbMic->setCurrentIndex(m_nCurMicIndex);
	}
}

void DeviceTest::updateMicState()
{
	if ( GetILive()->getCurMicState() )
	{
		m_ui.btnMic->setText( FromBits("关闭麦克风") );
		m_ui.sbMicVol->setEnabled(true);
		m_ui.hsMicVol->setEnabled(true);
	}
	else
	{
		m_ui.btnMic->setText( FromBits("打开麦克风") );
		m_ui.sbMicVol->setEnabled(false);
		m_ui.hsMicVol->setEnabled(false);
	}
}

void DeviceTest::updateMicVol()
{
	uint32 vol = GetILive()->getMicVolume();
	m_ui.sbMicVol->blockSignals(true);
	m_ui.hsMicVol->blockSignals(true);
	m_ui.sbMicVol->setValue(vol);
	m_ui.hsMicVol->setValue(vol);
	m_ui.sbMicVol->blockSignals(false);
	m_ui.hsMicVol->blockSignals(false);
}

void DeviceTest::openMic()
{
	if (m_micList.size()==0)
	{
		ShowErrorTips( FromBits("无可用的麦克风."), this );
		m_ui.btnMic->setEnabled(true);
		return;
	}
	int ndx = m_ui.cbMic->currentIndex();
	GetILive()->openMic( m_micList[ndx].first.c_str() );
}

void DeviceTest::closeMic()
{
	GetILive()->closeMic();
}

void DeviceTest::updatePlayerList()
{
	int nRet = GetILive()->getPlayerList(m_playerList);
	if (nRet == NO_ERR)
	{
		m_ui.cbPlayer->clear();
		for(int i=0; i<m_playerList.size(); ++i)
		{
			m_ui.cbPlayer->addItem( FromBits( m_playerList[i].second.c_str() ) );
		}
		m_nCurPlayerIndex = iliveClamp( m_nCurPlayerIndex, 0, m_playerList.size()-1 );
		m_ui.cbPlayer->setCurrentIndex(m_nCurPlayerIndex);
	}
}

void DeviceTest::updatePlayerState()
{
	if ( GetILive()->getCurPlayerState() )
	{
		m_ui.btnPlayer->setText( FromBits("关闭扬声器") );
		m_ui.sbPlayerVol->setEnabled(true);
		m_ui.hsPlayerVol->setEnabled(true);
	}
	else
	{
		m_ui.btnPlayer->setText( FromBits("打开扬声器") );
		m_ui.sbPlayerVol->setEnabled(false);
		m_ui.hsPlayerVol->setEnabled(false);
	}
}

void DeviceTest::updatePlayerVol()
{
	uint32 vol = GetILive()->getPlayerVolume();
	m_ui.sbPlayerVol->blockSignals(true);
	m_ui.hsPlayerVol->blockSignals(true);
	m_ui.sbPlayerVol->setValue(vol);
	m_ui.hsPlayerVol->setValue(vol);
	m_ui.sbPlayerVol->blockSignals(false);
	m_ui.hsPlayerVol->blockSignals(false);
}

void DeviceTest::openPlayer()
{
	if (m_playerList.size()==0)
	{
		ShowErrorTips( FromBits("无可用的扬声器."), this );
		m_ui.btnPlayer->setEnabled(true);
		return;
	}
	int ndx = m_ui.cbPlayer->currentIndex();
	GetILive()->openPlayer( m_playerList[ndx].first.c_str() );
}

void DeviceTest::closePlayer()
{
	GetILive()->closePlayer();
}
