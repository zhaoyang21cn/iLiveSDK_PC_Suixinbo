#ifndef MessageCallBack_h_
#define MessageCallBack_h_

#include <imsdk/tim_msg.h>

#define ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT 0x800
#define ILVLIVE_IMCMD_CUSTOM_UP_LIMIT 0x900

#define LiveNoti "LiveNotification" //自定义信令标记

enum E_CustomCmd
{
	AVIMCMD_None,               // 无事件：0

	AVIMCMD_EnterLive,          // 用户加入直播, Group消息 ： 1
	AVIMCMD_ExitLive,           // 用户退出直播, Group消息 ： 2
	AVIMCMD_Praise,             // 点赞消息, Demo中使用Group消息 ： 3
	AVIMCMD_Host_Leave,         // 主播或互动观众离开, Group消息 ： 4
	AVIMCMD_Host_Back,          // 主播或互动观众回来, Group消息 ： 5

	AVIMCMD_Multi = ILVLIVE_IMCMD_CUSTOM_LOW_LIMIT,  // 多人互动消息类型 ： 2048

	AVIMCMD_Multi_Host_Invite,          // 多人主播发送邀请消息, C2C消息 ： 2049
	AVIMCMD_Multi_CancelInteract,       // 已进入互动时，断开互动，Group消息，带断开者的imUsreid参数 ： 2050
	AVIMCMD_Multi_Interact_Join,        // 多人互动方收到AVIMCMD_Multi_Host_Invite多人邀请后，同意，C2C消息 ： 2051
	AVIMCMD_Multi_Interact_Refuse,      // 多人互动方收到AVIMCMD_Multi_Invite多人邀请后，拒绝，C2C消息 ： 2052
};

void sendC2CCustomCmd( QString dstUser, E_CustomCmd userAction, QString actionParam, SuccessCalllback suc = NULL, ErrorCallback err = NULL, void* data = NULL );
void sendGroupCustomCmd( E_CustomCmd userAction, QString actionParam, SuccessCalllback suc = NULL, ErrorCallback err = NULL, void* data = NULL );

class MessageCallBack
{
public:
	static void OnGropuMessage( const TIMMessage& msg );
	static void OnC2CMessage( const TIMMessage& msg );

	static 	QQueue<TIMMessage>	ms_messageQueue;
};

#endif//MesageCallBack_h_