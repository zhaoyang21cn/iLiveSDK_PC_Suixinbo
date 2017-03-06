#ifndef iLiveSDK_h_
#define iLiveSDK_h_

#include <imsdk/tim.h>
#include <imsdk/tim_comm.h>
#include <avsdk/av_context.h>
#include <ilivesdk/iLiveCommon.h>

namespace ilivesdk
{
	using namespace imcore;
	using namespace tencent::av;

	/**
	@brief iLiveSDK对象代表着一个SDK运行实例。
	@note 使用iLiveSDK前，必须调用initSdk()函数初始化SDK。
	*/
	class iLiveAPI iLiveSDK
	{
		class ForceOfflineCallBack : public TIMForceOfflineCallBack
		{
		public:
			virtual void OnForceOffline() override;
		};

	public:
		/**
		@brief 获取单例对象。
		@return 单例对象
		*/
		static iLiveSDK*	getInstance();

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
		ForceOfflineCallBack m_forceOfflineCB;

		HMODULE							m_hMoude;
		PROC_AVAPI_GetVersion			m_funcGetVersion;
		PROC_AVAPI_CreateContext		m_funcCreateContext;	
		PROC_AVAPI_EnableCrashReport	m_funcEnableCrashReport;
	};
}

#endif //iLiveSDK_h_