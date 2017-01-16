#ifndef _TIM_CONV_C_H_
#define _TIM_CONV_C_H_

#include "tim_comm_c.h"
#include "tim_msg_c.h"

typedef void* TIMDraftHandle;
extern "C"
{
	TIM_DECL TIMConversationHandle	CreateConversation();
	TIM_DECL void					DestroyConversation(TIMConversationHandle handle);
	TIM_DECL TIMDraftHandle			CreateDraft();
	TIM_DECL void					DestroyDraft(TIMDraftHandle handle);
	TIM_DECL void					SetDraftElems(TIMDraftHandle handle, TIMMsgElemHandle* elems, uint32_t num);
	TIM_DECL void					SetDraftText(TIMDraftHandle handle, const char* text, uint32_t len);
	TIM_DECL int					GetDraftElems(TIMDraftHandle handle, TIMMsgElemHandle* elems, uint32_t* num);
	TIM_DECL int					GetDraftText(TIMDraftHandle handle, char* text, uint32_t* len);



	/**
	Description:	发送普通消息
	@param	[in]	conv_handle		conversation handle
	@param	[in]	msg_handle		msg handle
	@param	[in]	callback		用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void SendMsg(TIMConversationHandle conv_handle, TIMMessageHandle msg_handle, TIMCommCB *callback);
	/**
	Description:	发送红包消息
	@param	[in]	conv_handle		conversation handle
	@param	[in]	msg_handle		msg handle
	@param	[in]	callback		用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void SendRedPacketMsg(TIMConversationHandle conv_handle, TIMMessageHandle msg_handle, TIMCommCB *callback);
	
	/**
	Description:	发送点赞消息
	@param	[in]	conv_handle		conversation handle
	@param	[in]	msg_handle		msg handle
	@param	[in]	callback		用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void SendLikeMsg(TIMConversationHandle conv_handle, TIMMessageHandle msg_handle, TIMCommCB *callback);

	/**
	Description:	发送在线消息（服务器不保存消息）
	@param	[in]	conv_handle		conversation handle
	@param	[in]	msg_handle		msg handle
	@param	[in]	callback		用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void SendOnlineMsg(TIMConversationHandle conv_handle, TIMMessageHandle msg_handle, TIMCommCB *callback);
	TIM_DECL int  SaveMsg(TIMConversationHandle conv_handle, TIMMessageHandle msg_handle, const char* sender, bool readed);
	/**
	Description:	导入历史消息
	@param	[in]	conv_handle	conversation handle
	@param	[in]	msg_handles msg handle数组
	@param	[in]	msg_num		msg个数
	@return			int	0：成功 非0：失败
	@exception      none
	*/
	TIM_DECL int	ImportMsgs(TIMConversationHandle conv_handle, TIMMessageHandle* msg_handles, uint32_t msg_num);
	/**
	Description:	获取会话消息
	@param	[in]	conv_handle	TIMConversationHandle
	@param	[in]	count		获取数量
	@param	[in]	last_msg	上次最后一条消息
	@param	[in]	callback	用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void GetMsgs(TIMConversationHandle conv_handle, int count, TIMMessageHandle last_msg, TIMGetMsgCB * callback);
	/**
	Description:	同步获取最后N条消息
	@param	[in]	conv_handle	TIMConversationHandle
	@param	[in\out]count		获取个数
	@param	[in]	last_msg	上次最后一条消息
	@param	[in]	msgs		TIMMessageHandle buffer
	@return			int
	@exception      none
	*/
	TIM_DECL int  GetMsgsFromCache(TIMConversationHandle conv_handle, int* count, TIMMessageHandle last_msg, TIMMessageHandle* msgs);
	TIM_DECL void GetMsgsForward(TIMConversationHandle conv_handle, int count, TIMMessageHandle from_msg, TIMGetMsgCB * callback);
	/**
	Description:	获取本地会话消息
	@param	[in]	conv_handle	TIMConversationHandle
	@param	[in]	count		获取数量
	@param	[in]	last_msg	上次最后一条消息
	@param	[in]	callback	用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void GetLocalMsgs(TIMConversationHandle conv_handle, int count, TIMMessageHandle last_msg, TIMGetMsgCB * callback);
	TIM_DECL void DeleteLocalMsg(TIMConversationHandle conv_handle, TIMCommCB *callback);
	/**
	Description:	已读上报 ImSDK会把比last_read_msg时间更早的消息标记为已读消息
	@param	[in]	conv_handle		TIMConversationHandle
	@param	[in]	last_read_msg	上报已读的消息
	@return			void
	@exception      none
	*/
	TIM_DECL void SetReadMsg(TIMConversationHandle conv_handle, TIMMessageHandle last_read_msg);
 	/**
 	Description:	获取当前会话中未读消息的数量
 	@param	[in]	conv_handle	TIMConversationHandle
 	@return			uint64_t	未读数
 	@exception      none
 	*/
 	TIM_DECL uint64_t GetUnreadMessageNum(TIMConversationHandle conv_handle);

	TIM_DECL int GetConversationPeer(TIMConversationHandle conv_handle, char* buf, uint32_t* len);
	TIM_DECL const TIMConversationType GetConversationType(TIMConversationHandle conv_handle);

	TIM_DECL void SetConversationPeer(TIMConversationHandle conv_handle, const char* peer);
	TIM_DECL void SetConversationType(TIMConversationHandle conv_handle, const TIMConversationType type);

	/**
	Description:	设置会话草稿
	@param	[in]	conv_handle
	@param	[in]	draft	草稿内容	
	@param	[in]	draft_len	草稿长度
	@return			TIM_DECL void
	@exception      none
	*/
	TIM_DECL void SetConversationDraft(TIMConversationHandle conv_handle, TIMDraftHandle draft );

	//TIM_DECL void SetConversationDraft(TIMConversationHandle conv_handle, TIMMsgElemHandle, uint32_t draft_len);

	/**
	Description:	获取会话草稿
	@param	[in]	conv_handle
	@param	[in]	draft	草稿内容
	@param	[in/out]	len		草稿长度
	@return			TIM_DECL int
	@exception      none
	*/
	TIM_DECL int GetConversationDraft(TIMConversationHandle conv_handle, TIMDraftHandle draft);

	/**
	Description:	禁用会话存储
	@param	[in]	conv_handle
	@return			TIM_DECL void
	@exception      none
	*/
	TIM_DECL void DisableConversationStorage(TIMConversationHandle conv_handle);
};



#endif