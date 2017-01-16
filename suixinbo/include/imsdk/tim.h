#ifndef __TIM_MANAGER_H__
#define __TIM_MANAGER_H__

#include "tim_comm.h"
#include "tim_conv.h"
#include "tim_msg.h"

namespace imcore {


class TIM_DECL TIMManager {
public:
	TIMManager();
	static TIMManager &get();
	int SwitchEnv(int env);
	void set_env(int env);
	int env();
	void set_mode(int mode);
	int mode();
	void set_path(const std::string &path);
	const std::string &path() const;
	void set_log_level(TIMLogLevel level);
	TIMLogLevel get_log_level();
	void set_log_print(bool enable_flag);
	bool get_log_print();
	int ready();
	void set_svr_time_diff(int64_t diff);
	int64_t svr_time_diff() const;

	int Init();
	int Uninit();
	void Login(int sdk_app_id, 
			const TIMUser &tim_user, const std::string &user_sig, TIMCallBack *cb);
	void Logout(TIMCallBack *cb);
	TIMConversation GetConversation(TIMConversationType type, const std::string &peer);
	bool DeleteConversation(TIMConversationType type, const std::string &peer);
	bool DeleteConversationAndMsgs(TIMConversationType type, const std::string &peer);
	uint64_t GetConversationCount();
	TIMConversation GetConversationByIndex(uint64_t i);
	std::vector<TIMConversation> GetConversations();
	void UploadLogFile(const std::string& filename, const std::string& tag);
	void DisableStorage();//disable msg store
	void SetRecentContactEnableFlag(bool enable);
	void DisableAutoReport();

	void SetMessageCallBack(TIMMessageCallBack *cb);
	TIMMessageCallBack *GetMessageCallBack();
	void SetConnCallBack(TIMConnCallBack *cb);
	TIMConnCallBack *GetConnCallBack();
	void SetForceOfflineCallback(TIMForceOfflineCallBack* cb);
	TIMForceOfflineCallBack* GetForceOfflineCallback();
	
	void SetUserSigExpiredCallback(TIMUserSigExpiredCallBack* cb);
	TIMUserSigExpiredCallBack* GetUserSigExpiredCallback();

	void SetStatusChangeCallback(TIMStatusChangeCallBack *cb);
	TIMStatusChangeCallBack* GetStatusChangeCallback();
	void SetGroupEventCallback(void* cb);
	void* GetGroupEventCallback();
	TIMNetworkStatus GetNetWorkStatus();
	//if login return id; else return ""
	const std::string& GetLoginUser();
	const char* GetVersion();

	void SendBatchC2CMsg(std::vector<std::string>&ids, TIMMessage& msg, TIMSendBatchCallBack* callback);

private:
	int env_;
	int mode_;
	int ready_;
	int64_t svr_time_diff_;
	std::string path_;
	bool log_print_;
	TIMLogLevel log_level_;
	TIMMessageCallBack *msg_cb_;
	TIMConnCallBack *conn_cb_;
	TIMForceOfflineCallBack* offline_cb_;
	TIMUserSigExpiredCallBack* user_sig_expired_cb_;
	TIMStatusChangeCallBack *status_change_cb_;
	void* group_event_cb_;
};

}

#endif
