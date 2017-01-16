#ifndef  _TIM_C_H_
#define _TIM_C_H_

#include "tim_comm_c.h"
#include "tim_conv_c.h"
#include "tim_msg_c.h"
#include "tim_status_c.h"


extern "C" 
{
	TIM_DECL int	TIMSwitchEnv(int env);
	TIM_DECL void	TIMSetEnv(int env);
	TIM_DECL int	TIMEnv();
	/**
	Description:	设置接入模式
	@param	[in]	mode	1 – IM连接模式 / 0或不调用此接口 – 只登陆模式 
	@return			void
	@exception      none
	*/
	TIM_DECL void	TIMSetMode(int mode);
	TIM_DECL int	TIMMode();
	TIM_DECL int	TIMSetSdkAPPId(int sdk_app_id);
	/**
	Description:	设置SDK日志和其他SDK所写文件的生成路径
	@param	[in]	path	路径
	@return			void
	@exception      none
	*/
	TIM_DECL void	TIMSetPath(const char* path);
	TIM_DECL int	TIMGetPath(char* path, uint32_t* len);
	TIM_DECL void	TIMSetLogLevel(TIMLogLevel level);
	TIM_DECL void	TIMSetLogPrint(bool flag);
	TIM_DECL bool	TIMGetLogPrint();
	TIM_DECL TIMLogLevel TIMGetLogLevel();
	
	TIM_DECL int	TIMReady();

	/**
	Description:	初始化SDK
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int	TIMInit();

	/**
	Description:	解初始化SDK 卸载DLL或退出进程前需调用
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int	TIMUninit();

	/**
	Description:	登录IM云
	@param	[in]	sdk_app_id		应用SDKAPPID
	@param	[in]	tim_user		用户信息
	@param	[in]	user_sig		用户密钥
	@param	[in]	callback		登录回调
	@return			int	0
	@exception      none
	*/
	TIM_DECL int	TIMLogin(int sdk_app_id, const TIMUserInfo *tim_user, const char* user_sig, TIMCommCB *callback);
	/**
	Description:	登出IM云
	@param	[in]	callback		用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void	TIMLogout(TIMCommCB *callback);


	/**
	Description:	获取会话个数
	@return			uint64_t 回话个数
	@exception      none
	*/
	TIM_DECL uint64_t	TIMGetConversationCount();
	/**
	Description:	获取会话句柄
	@param	[in]	handle		会话句柄
	@param	[in]	type		会话类型
	@param	[in]	peer		会话对方ID(如类型为群类型，则ID为群ID)
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int		TIMGetConversation(TIMConversationHandle handle, TIMConversationType type, const char* peer);
	/**
	Description:	删除会话
	@param	[in]	type	会话类型，kCnvC2C 表示单聊 kCnvGroup 表示群聊
	@param	[in]	peer	用户identifier 或者 群组Id
	@return			bool	TRUE:删除成功  FALSE:删除失败
	@exception      none
	*/
	TIM_DECL bool		TIMDeleteConversation(TIMConversationType type, const char* peer);
	/**
	Description:	删除会话和消息
	@param	[in]	type	会话类型，kCnvC2C 表示单聊 kCnvGroup 表示群聊
	@param	[in]	peer	用户identifier 或者 群组Id
	@return			bool	TRUE:删除成功  FALSE:删除失败
	@exception      none
	*/
	TIM_DECL bool		TIMDeleteConversationAndMsgs(TIMConversationType type, const char* peer);
	TIM_DECL int		TIMGetConversationByIndex(TIMConversationHandle handle, uint64_t index);
	TIM_DECL void		TIMUploadLogFile(const char* filename, const char* tag);
	/**
	Description:	禁用存储
	@return			void
	@exception      none
	*/
	TIM_DECL void		TIMDisableStorage();
	/**
	Description:	登录时禁止拉取最近联系人列表
	@return			void
	@exception      none
	*/
	TIM_DECL void		TIMDisableRecentContact();
	/**
	Description:	禁用自动已读上报（如果禁用，开发者必须显式调用回话的已读上报）
	@return			TIM_DECL void
	@exception      none
	*/
	TIM_DECL void		TIMDisableAutoReport();

	/**
	Description:	设置用户新消息回调函数
	@param	[in]	callback	新消息回调函数
	@return			void
	@exception      none
	*/
	TIM_DECL void			TIMSetMessageCallBack(TIMMessageCB *callback);
	TIM_DECL TIMMessageCB *	TIMGetMessageCallBack();

	TIM_DECL void		TIMSetConnCallBack(TIMConnCB *callback);
	TIM_DECL TIMConnCB*	TIMGetConnCallBack();

	TIM_DECL void		TIMSetKickOfflineCallBack(TIMForceOfflineCB* callback);
	TIM_DECL TIMForceOfflineCB* TIMGetKickOfflineCallBack();

	TIM_DECL void		TIMSetUserSigExpiredCallBack(TIMUserSigExpiredCB* callback);
	TIM_DECL TIMUserSigExpiredCB* TIMGetUserSigExpiredCallBack();

	TIM_DECL void		TIMSetStatusChangeCallBack(TIMStatusChangeCB *callback);
	TIM_DECL TIMStatusChangeCB* TIMGetStatusChangeCallBack();

	TIM_DECL void TIMSetGroupEventListener(TIMGroupEventListener* callback);
	TIM_DECL TIMGroupEventListener* TIMGetGroupEventListener();

	TIM_DECL TIMNetworkStatus TIMGetNetWorkStatus();
	TIM_DECL int64_t TIMGetServerTimeDiff();

	// return 如果登陆返回用户的identifier，如果未登录返回非零
	TIM_DECL int TIMGetLoginUser(char* id, uint32_t* len);

	TIM_DECL const char*TIMGetSDKVersion();

	TIM_DECL void TIMSendBatchC2CMsg(const char** ids, uint32_t num, TIMMessageHandle msg_handle, TIMBBatchOprCB* callback);

};


#endif