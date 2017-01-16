#ifndef Event_h_
#define Event_h_

enum E_CustomEvent
{
	E_CELogin = QEvent::User+1,
	E_CELogout,
	E_CECreateRoom,
	E_CEJoinRoom,
	E_CEQuitRoom,
	E_CERequestViewList,
	E_CECancelViewList,
	E_CESendGroupMsg,
	E_CERecMsg,
	E_CEChangeAuth,
	E_CESendInviteInteract,
	E_CEStartRecordVideo,
	E_CEStopRecordVideo,
	E_CEStartPushStream,
	E_CEStopPushStream,
	E_CEForceOffline,
};

struct Event : public QEvent
{
	Event( E_CustomEvent eventType, int errCode, const std::string& szDesc );

	int code;
	std::string desc;
};

void postCusEvent(QObject *receiver, Event* event );

#endif//Event_h_