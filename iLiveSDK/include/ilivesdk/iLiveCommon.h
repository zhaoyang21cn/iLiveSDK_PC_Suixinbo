#ifndef iLiveCommon_h_
#define iLiveCommon_h_

#include <string>
#include <map>
#include <Windows.h>
#include <assert.h>

#pragma comment(lib, "libtim.lib")

#ifdef iLiveSDKImpl
	#define iLiveAPI __declspec(dllexport)
#else
	#define iLiveAPI __declspec(dllimport)
#endif

namespace ilivesdk
{
	/**
	@brief iLiveSDK错误码集合
	*/
	enum E_iLiveError
	{
		INVALID_INTETER_VALUE   = -1,   ///< 无效的整型返回值(通用)
		NO_ERR                  = 0,    ///< 成功
		ERR_IM_NOT_READY        = 8001, ///< IM模块未就绪或未加载
		ERR_AV_NOT_READY        = 8002, ///< AV模块未就绪或未加载
		ERR_NO_ROOM             = 8003, ///< 无有效的房间
		ERR_ALREADY_EXIST       = 8004, ///< 目标已存在
		ERR_NULL_POINTER        = 8005, ///< 空指针错误
		ERR_ENTER_AV_ROOM_FAIL  = 8006, ///< 进入AV房间失败
		ERR_USER_CANCEL         = 8007, ///< 用户取消
		ERR_WRONG_STATE         = 8008, ///< 状态异常
		ERR_SDK_FAILED          = 8020, ///< iLiveSDK处理失败(通用)
		ERR_INVALID_PARAM       = 8021, ///< 无效的参数
		ERR_NOT_FOUND           = 8022, ///< 无法找到目标
		ERR_NOT_SUPPORT         = 8023, ///< 请求不支持
		ERR_ALREADY_STATE       = 8024, ///< 状态已到位(一般为重复调用引起)
		ERR_KICK_OUT            = 8050, ///< 被踢下线
		ERR_EXPIRE              = 8051, ///< 票据过期(需更新票据userSig)
	};

	/**
	@brief 成功带值回调函数指针类型的封装。
	*/
	template <typename T>
	struct Type
	{
		/**
		@brief 通用的成功带值回调函数指针类型;
		@param [in] value 操作成功，SDK返回给业务侧响应类型的值;
		@param [in] data SDK传回业务侧自定义的数据指针;
		*/
		typedef void (*VlaueSuccessCallback)(T value, void* data);
	};
	/**
	@brief 通用的成功回调函数指针类型;
	@param [in] data SDK传回业务侧自定义的数据指针;
	*/
	typedef void (*SuccessCalllback)(void* data);
	/**
	@brief 通用的失败回调函数指针类型;
	@param [in] code 错误码
	@param [in] desc 错误原因描述
	@param [in] data SDK传回业务侧自定义的数据指针;
	*/
	typedef void (*ErrorCallback)(int code, const std::string& desc, void* data);
}

#endif//iLiveCommon_h_
