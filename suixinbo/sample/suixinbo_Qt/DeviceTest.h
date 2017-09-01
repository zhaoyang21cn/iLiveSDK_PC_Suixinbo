#ifndef DEVICETEST_H
#define DEVICETEST_H

#include <QDialog>
#include "ui_DeviceTest.h"

class DeviceTest : public QDialog
{
	Q_OBJECT

public:
	DeviceTest(QWidget *parent = 0);
	~DeviceTest();

	static void OnDeviceOperation(E_DeviceOperationType oper, int retCode, void* data);
	static void OnCameraVideo(const LiveVideoFrame* video_frame, void* data);
	static void OnDeviceDetect(void* data);

protected:
	void showEvent(QShowEvent *event) override;
	void closeEvent(QCloseEvent *event) override;

private slots:
	void on_btnCamera_clicked();
	
	void on_btnMic_clicked();
	void on_hsMicVol_valueChanged(int value);
	void on_sbMicVol_valueChanged(int value);

	void on_btnPlayer_clicked();
	void on_hsPlayerVol_valueChanged(int value);
	void on_sbPlayerVol_valueChanged(int value);

	void on_vsSkinSmooth_valueChanged(int value);
	void on_sbSkinSmooth_valueChanged(int value);
	void on_vsSkinWhite_valueChanged(int value);
	void on_sbSkinWhite_valueChanged(int value);

private:
	void updateCameraList();
	void updateCameraState();
	void openCamera();
	void closeCamera();
	
	void updateMicList();
	void updateMicState();
	void updateMicVol();
	void openMic();
	void closeMic();

	void updatePlayerList();
	void updatePlayerState();
	void updatePlayerVol();
	void openPlayer();
	void closePlayer();

private:
	Ui::DeviceTest m_ui;

	int m_nCurCameraIndex, m_nCurMicIndex, m_nCurPlayerIndex;
	Vector< Pair<String/*id*/, String/*name*/> > m_cameraList;
	Vector< Pair<String/*id*/, String/*name*/> > m_micList;
	Vector< Pair<String/*id*/, String/*name*/> > m_playerList;

	bool m_bStoped;
};

#endif // DEVICETEST_H
