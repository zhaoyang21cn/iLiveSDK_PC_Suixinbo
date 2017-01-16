#ifndef iLiveLog_h_
#define iLiveLog_h_
#include <ilivesdk/iLiveCommon.h>

namespace ilivesdk
{
	/**
	@brief 日志级别
	*/
	enum E_iLiveLogLevel
	{
		E_LogNone = 0,	///< 无日志
		E_LogError,		///< 错误
		E_LogWarn,		///< 警告
		E_LogInfo,		///< 信息
		E_LogDebug		///< 调试
	};

	/**
	@brief 设置日志目录。
	@param [in] szLogPath 日志目录;
	@note 默认路径为当前目录; 调用示例: SetiLiveLogPath("./log/");
	*/
	iLiveAPI void SetiLiveLogPath(std::string szLogPath);
	/**
	@brief 设置日志级别.
	@param [in] logLevel 日志级别
	@note 设置日志级别后，只有高于此级别的日志才会输出；如，日志级别为E_LogWarn时，只会打印E_LogError
	和E_LogWarn级别的日志；默认日志级别为E_LogDebug;
	*/
	iLiveAPI void SetiLiveLogLevel(E_iLiveLogLevel logLevel);

	/**
	@brief 输出Error日志信息.
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似prinf()函数.
	*/
	iLiveAPI void iLiveLog_e(const char* szFormat, ...);
	/**
	@brief 输出Error日志信息(双字节版本).
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似wprintf()函数.
	*/
	iLiveAPI void iLiveLog_e(const wchar_t* szFormat, ...);

	/**
	@brief 输出Warn日志信息.
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似prinf()函数.
	*/
	iLiveAPI void iLiveLog_w(const char* szFormat, ...);
	/**
	@brief 输出Warn日志信息(双字节版本).
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似wprintf()函数.
	*/
	iLiveAPI void iLiveLog_w(const wchar_t* szFormat, ...);

	/**
	@brief 输出Info日志信息.
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似prinf()函数.
	*/
	iLiveAPI void iLiveLog_i(const char* szFormat, ...);
	/**
	@brief 输出Info日志信息(双字节版本).
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似wprintf()函数.
	*/
	iLiveAPI void iLiveLog_i(const wchar_t* szFormat, ...);

	/**
	@brief 输出Debug日志信息.
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似prinf()函数.
	*/
	iLiveAPI void iLiveLog_d(const char* szFormat, ...);
	/**
	@brief 输出Debug日志信息(双字节版本).
	@param [in] szFormat 日志内容格式.
	@note 使用方法类似wprintf()函数.
	*/
	iLiveAPI void iLiveLog_d(const wchar_t* szFormat, ...);
}

#endif //iLiveLog_h_