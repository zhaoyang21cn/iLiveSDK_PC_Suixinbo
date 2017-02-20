#ifndef iLiveSDK_h_
#define iLiveSDK_h_

#include <imsdk/tim.h>
#include <imsdk/tim_comm.h>
#include <avsdk/av_context.h>
#include <ilivesdk/iLiveCommon.h>
using imcore::TIMMessageCallBack;
using imcore::TIMConnCallBack;
using imcore::TIMForceOfflineCallBack;
using imcore::TIMManager;
using tencent::av::AVContext;

namespace ilivesdk
{
	/**
	@brief iLiveSDK对象代表着一个SDK运行实例。
	@note 使用iLiveSDK前，必须调用initSdk()函数初始化SDK。
	*/
	class iLiveAPI iLiveSDK
	{
	public:
		/**
		@brief 获取单例对象。
		@return 单例对象
		*/
		static iLiveSDK*	getInstance();

		/**
		@brief 设置收到IM消息时的回调。
		@details 收到IM消息时，会调用此函数设置的回调。
		@param [in] cb 回调接口的指针;
		@note 允许在initSdk()之后再设置此回调;
		*/
		void				SetMessageCallBack(TIMMessageCallBack *cb);//收到消息的回调，可以在initSdk之后调用
		/**
		@brief 设置IM连接和断开服务器的回调。
		@param [in] cb 回调接口的指针;
		@note 如果要设置此回调，必须在initSdk()之前设置此回调，否则无效;
		*/
		void				SetConnCallBack(TIMConnCallBack* cb);
		/**
		@brief 设置被挤下线的回调。
		@param [in] cb 回调接口的指针;
		@note 如果要设置此回调，必须在initSdk()之前设置此回调，否则无效;
		*/
		void				SetForceOfflineCallback(TIMForceOfflineCallBack* cb);
		/**
		@brief 初始化iLiveSDK。
		@note 使用iLiveSDK前，必须调用此函数初始化SDK。
		@param [in] appId 腾讯为每个接入方分配的账号id
		@param [in] accountType 腾讯为每个接入方分配的账号类型
		@return 返回操作结果,成功则返回NO_ERR
		*/
		int					initSdk(const int appId, const int accountType);
		/**
		@brief 释放内部资源,程序退出时需要调用。
		@remark 此函数会清理7天前的iLiveSDK日志文件。
		*/
		void				destroy();
		/**
		@brief 获取TIMManager类单例对象。
		@details 用户可以获取TIMManager对象，从而进行一些自定义设置;
		@return 返回TIMManager单例对象的引用;
		*/
		TIMManager&			getTIMManager();
		/**
		@brief 获取AppId。
		@details 获取在初始化函数中传入的appId
		@return 返回appId
		*/
		int					getAppId();
		/**
		@brief 获取App的账号类型。
		@details 获取在初始化函数中传入的accountType
		@return 返回accountType
		*/
		int					getAccountType();
		/**
		@brief 获取AVContext对象。
		@details 获取AVContext对象;
		@return 返回iLiveSDK内部创建和维护的AVContext对象指针;
		*/
		AVContext*			getAVContext();
		/**
		@brief 获取版本号。
		@return 返回版本号字符串;
		*/
		const char*			getVersion();

	private:
		iLiveSDK();
		~iLiveSDK();

	private:
		int					m_appId;
		int					m_accountType;
		AVContext*			m_pAVContext;
		std::string			m_szVersion;

		HMODULE							m_hMoude;
		PROC_AVAPI_GetVersion			m_funcGetVersion;
		PROC_AVAPI_CreateContext		m_funcCreateContext;	
		PROC_AVAPI_EnableCrashReport	m_funcEnableCrashReport;
	};
}

#endif //iLiveSDK_h_