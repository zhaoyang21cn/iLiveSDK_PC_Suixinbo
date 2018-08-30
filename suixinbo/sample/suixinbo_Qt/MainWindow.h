#ifndef MainWnd_h_
#define MainWnd_h_

#include "ui_MainWindow.h"
#include "Live.h"
#include "Register.h"
#include "RoomListItem.h"
#include "DeviceTest.h"

#define OnePageCout 10

enum E_LoginState
{
	E_InvalidState = -1,
	E_Logout,
	E_Logining,
	E_Login,
};

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
	QString getUserId();
	QString	getServerUrl();
	QString getToken();
	E_LoginState getLoginState();
	Live*	getLiveView();

	void setCurRoomIdfo(const Room& roominfo);
	const Room& getCurRoomInfo();
	void increasePraise();

	void setUseable(bool bUseable);
	void OnForceOffline();

private:
	void initSDK();	
	void readConfig();
	void saveConfig();
	void connectSignals();
	void switchLoginState(E_LoginState state);
	static void onForceOffline();

	void clearShowRoomList();
	void updatePageNum();
	void updateRoomList();

	//业务侧服务器相关操作
	void sxbLogin();
	void sxbLogout();
	void sxbCreateRoom();
	void sxbReportroom();
	void sxbCreatorJoinRoom();//主播加入房间
	void sxbRoomList();
	static void OnSxbLogin(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbLogout(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbCreateRoom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbReportroom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbCreatorJoinRoom(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);
	static void OnSxbRoomList(int errorCode, QString errorInfo, QVariantMap datamap, void* pCusData);

	void picDown(QString userId, QString url); //下载图片
	static void OnPicDown(int errorCode, QString errorInfo, QString picPath, void* pCusData);//下载图片回调

	//iLiveSDK相关操作
 	void iLiveLogin();
 	void iLiveLogout();
	void iLiveCreateRoom();
	static void OniLiveLoginSuccess(void* data);
	static void OniLiveLoginError(int code, const char *desc, void* data);
	static void OniLiveLogoutSuccess(void* data);
	static void OniLiveLogoutError(int code, const char *desc, void* data);
	static void OniLiveCreateRoomSuc(void* data);
	static void OniLiveCreateRoomErr(int code, const char *desc, void* data);
	
	static void OnStartDeviceTestSuc(void* data);
	static void OnStartDeviceTestErr(int code, const char *desc, void* data);

protected:
	void closeEvent(QCloseEvent* event) override;

private slots:
	void onBtnLogin();
	void onBtnRegister();
	void onBtnBeginLive();
	void onBtnRefreshLiveList();
	void onBtnLastPage();
	void onBtnNextPage();
	void on_btnDeviceTest_clicked();

private:
	Ui::MainWindow		m_ui;
	
	QSettings*			m_pSetting;
	int					m_nAppId;
	QString				m_szServerUrl;

	E_LoginState		m_eLoginState;

	QString				m_szUserId;
	QString				m_szUserPassword;
	QString				m_szUserSig;
	QString				m_szUserToken;

	Register*			m_pRegister;
	Live*				m_pLive;
	DeviceTest*			m_pDeviceTest;

	int					m_nCurrentPage;
	int					m_nTotalPage;

	QVector<Room>		m_showRooms;
	RoomListItem*		m_pRoomListItem[OnePageCout];

	Room				m_curRoomInfo;
};

#endif //MainWnd_h_