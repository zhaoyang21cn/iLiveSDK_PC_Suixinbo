#ifndef iLiveRecordOption_h_
#define iLiveRecordOption_h_

#include <ilivesdk/iLiveCommon.h>

namespace ilivesdk
{
	/**
	@brief 录制数据类型 
	*/
	enum E_RecordDataType
	{
		E_RecordCamera = 0, ///< 录制摄像头
		E_RecordScreen,		///< 录制辅流(屏幕分享)
	};

	/**
	@brief 录制配置项。
	@details 录制操作需要传入此类型的参数。
	*/
	struct iLiveRecordOption
	{
		/**
		@brief 构造函数，初始化成员变量值。
		*/
		iLiveRecordOption()
			:record_data_type(E_RecordCamera)
			,filename("")
			,class_id(0)
		{
		}

		E_RecordDataType record_data_type; ///< 录制的数据类型,参见E_RecordDataType定义。
		std::string		 filename;		  ///< 录制后的文件名。
		int				 class_id;		  ///< 视频分类ID(暂无效)。
	};
}

#endif //iLiveRecordOption_h_