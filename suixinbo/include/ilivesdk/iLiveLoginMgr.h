#ifndef iLiveLoginMgr_h_
#define iLiveLoginMgr_h_

#include <imsdk/tim_comm.h>
#include <ilivesdk/iLiveCommon.h>
using imcore::TIMCallBack;
using imcore::TIMUser;

namespace ilivesdk
{
	/**
	@brief 登录、登出的封装;
	*/
	class iLiveAPI iLiveLoginMgr
	{
		class IMLoginCallBack : public TIMCallBack
		{
		public:
			virtual void	OnSuccess();
			virtual void	OnError(int code, const std::string &desc);
		};

		class IMLogoutCallBack : public TIMCallBack
		{
		public:
			virtual void	OnSuccess();
			virtual void	OnError(int code, const std::string &desc);
		};

	public:
		/**
		@brief 获取单例对象。
		@return 单例对象
		*/
		static iLiveLoginMgr*	getInstance();
		/**
		@brief 登录
		@param [in] szUserId 用户id
		@param [in] szUserSig 用户Sig
		@param [in] suc 成功的回调函数指针
		@param [in] err 失败的回调函数指针
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					iLiveLogin( const std::string szUserId, const std::string szUserSig, SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 登出
		@param [in] suc 成功回调函数指针
		@param [in] err 失败回调函数指针
		@param [in] data 用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回;
		*/
		void					iLiveLogout( SuccessCalllback suc, ErrorCallback err, void* data );
		/**
		@brief 获取已经登录用户ID(只有登录成功后才能获取)
		@return 返回已经登录用户的ID
		*/
		std::string				getLoginId();
		/**
		@brief 获取已经登录用户Sig(只有登录成功后才能获取)
		@return 返回已经登录用户的Sig
		*/
		std::string				getUserSig();

	private:
		iLiveLoginMgr();
		void					OnIMLoginSuc();
		void					OnIMLoginErr(int code, const std::string& desc);
		void					OnIMLogoutSuc();
		void					OnIMLogoutErr(int code, const std::string& desc);

		static void				OnStartContextCompleteCallback(int result, void *pCustomData);
		
	private:
		IMLoginCallBack				m_timLoginCallback;
		IMLogoutCallBack			m_timLogoutCallBack;

		SuccessCalllback			m_pLoginSuccessCB;
		ErrorCallback				m_pLoginErrorCB;
		void*						m_pLoginData;

		SuccessCalllback			m_pLogoutSuccessCB;
		ErrorCallback				m_pLogoutErrorCB;
		void*						m_pLogoutData;

		std::string					m_szUserId;
		std::string					m_szUserSig;
	};
}


#endif //iLiveLoginMgr_h_