#include "stdafx.h"
#include "MessageCallBack.h"

QQueue<TIMMessage> MessageCallBack::ms_messageQueue;

void MessageCallBack::OnNewMessage( const std::vector<TIMMessage> &msgs )
{
	iLiveLog_d("OnNewMessage");
	for (uint32 i=0; i<msgs.size(); ++i)
	{
		ms_messageQueue.push_back( msgs[i] );
	}
	postCusEvent( g_pMainWindow, new Event(E_CERecMsg, 0, "") );
}

void ForceOfflineCallBack::OnForceOffline()
{
	g_pMainWindow->OnForceOffline();
}
