#ifndef iLivePushOption_h_
#define iLivePushOption_h_

#include <imsdk/tim_int.h>

namespace ilivesdk
{
	/**
	@brief 推流数据类型
	*/
	enum E_PushDataType
	{
		E_PushCamera = 0,///< 摄像头
		E_PushScreen,	 ///< 辅流(屏幕分享)
	};

	/**
	@brief 推流配置项。
	@details 推流操作需要传入此类型的参数。
	*/
	struct iLivePushOption
	{
		/**
		@brief 构造函数，初始化成员变量。
		*/
		iLivePushOption()
			:push_data_type(E_PushCamera)
			,encode(imcore::HLS)
		{
		}

		std::string					channel_name;///< 频道名称.
		std::string					channel_desc;///< 频道描述.
		E_PushDataType				push_data_type;///< 推送数据类型，参见E_PushDataType定义.
		imcore::E_TIMStreamEncode	encode;///< 推流数据编码方式，参见E_TIMStreamEncode定义.
	};
}

#endif//iLivePushOption_h_