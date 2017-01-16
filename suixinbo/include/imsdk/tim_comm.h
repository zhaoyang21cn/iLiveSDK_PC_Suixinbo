#ifndef __TIM_COMM_H__
#define __TIM_COMM_H__

#include <string>
#include <sstream>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "tim_comm_c.h"

#ifdef _MSC_VER
#pragma warning ( disable : 4251 )
#pragma warning ( disable : 4996 )
#endif // _MSC_VER


namespace imcore {

class TIM_DECL TIMUser {
public:
	TIMUser(){stiny_id_ = "0"; tiny_id_ = 0;};
	TIMUser(const TIMUserInfo* user)
		:account_type_(user->account_type)
		, app_id_at_3rd_(user->app_id_at_3rd)
		, identifier_(user->identifier){}
	TIMUser(const TIMUser &o){account_type_ = o.account_type_; app_id_at_3rd_ = o.app_id_at_3rd_; identifier_ = o.identifier_; tiny_id_ = o.tiny_id_;}
	TIMUser &operator=(const TIMUser &o)
	{
		account_type_ = o.account_type_;
		app_id_at_3rd_ = o.app_id_at_3rd_;
		identifier_ = o.identifier_;
		tiny_id_ = o.tiny_id_;
		return *this;
	}
	std::string to_string()
	{
		return std::move(account_type_ + ":" + app_id_at_3rd_ + ":" + identifier_);
	}
	void	set_account_type(const std::string &uidtype) { account_type_ = uidtype; }
	const std::string&	account_type() const { return account_type_; }
	void	set_app_id_at_3rd(const std::string &appid) { app_id_at_3rd_ = appid; }
	const std::string& app_id_at_3rd() const { return app_id_at_3rd_; }
	void	set_identifier(const std::string &userid) { identifier_ = userid; }
	const std::string& identifier() const { return identifier_; }
	void	set_tiny_id(uint64_t tiny_id) {
		tiny_id_ = tiny_id;
		static char buffer[50];
		sprintf(buffer, "%llu", tiny_id);
		stiny_id_.assign(buffer);
	}

	uint64_t tiny_id() const { return tiny_id_; }
	void set_stiny_id(const std::string &stiny_id) {
		stiny_id_ = stiny_id; 
#ifndef _MSC_VER
        tiny_id_ = strtoull(stiny_id_.c_str(), NULL, 10);
#else
		tiny_id_ = _strtoui64(stiny_id_.c_str(), NULL, 10);
#endif
	}

	const std::string& stiny_id() const { return stiny_id_; }

	std::string tostring() const
	{
		std::ostringstream ss;
		ss << app_id_at_3rd_;
		return account_type_ + ":" + identifier_ + ":" + ss.str();
	}

	std::string debugstring() const
	{
		std::ostringstream ss;
		ss << tiny_id_;
		return tostring() + ":" + ss.str();
	}

	std::string account_type_;
	std::string app_id_at_3rd_;
	std::string identifier_;
	std::string stiny_id_;
	uint64_t tiny_id_;
};

class TIM_DECL TIMCallBack {
public:
	virtual ~TIMCallBack() {}
	virtual void OnSuccess() {}
	virtual void OnError(int code, const std::string &desc) {}
};

template <class T>
class TIM_DECL TIMValueCallBack {
public:
	virtual ~TIMValueCallBack() {}
	virtual void OnSuccess(T value) {}
	virtual void OnError(int code, const std::string &desc) {}
};

class TIM_DECL TIMConnCallBack {
public:
	virtual ~TIMConnCallBack() {}
	virtual void OnConnected() {}
	virtual void OnDisconnected() {}
};

class TIM_DECL TIMForceOfflineCallBack {
public:
	virtual ~TIMForceOfflineCallBack() {}
	virtual void OnForceOffline() {}
};

class TIM_DECL TIMUserSigExpiredCallBack{
public:
	virtual ~TIMUserSigExpiredCallBack() {}
	virtual void OnUserSigExpired() {}
};

class TIM_DECL TIMStatusChangeCallBack {
public:
	virtual ~TIMStatusChangeCallBack() {}
	virtual void OnStatusChange(const std::string &user_id, const std::string &user_defined) {}
};

struct TIMBatchOprDetailInfo
{
	struct TIMErrInfo
	{
		std::string id;
		int err_code;
		std::string err_msg;
	};
	TIMBatchOprDetailInfo() : succ_num(0), fail_num(0){};
	uint32_t succ_num;
	uint32_t fail_num;
	std::vector<TIMErrInfo> errs;
}; 

class TIM_DECL TIMSendBatchCallBack{
public:
	virtual ~TIMSendBatchCallBack(){}
	virtual void OnSuccess(){};
	virtual void OnError(int code, const std::string &desc, const TIMBatchOprDetailInfo* info) {};
};

}

#endif
