#ifndef iLive_h_
#define iLive_h_

#include <iLiveCommon.h>
#include <iLiveString.h>
#include <iLiveVector.h>
#include <iLivePair.h>


namespace ilive
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
		ERR_NOT_LOGIN			= 8009, ///< 未登录
		ERR_ALREADY_IN_ROOM		= 8010, ///< 已在房间中
		ERR_BUSY_HERE			= 8011,	///< 内部忙(上一请求未完成)
		ERR_NET_UNDEFINE		= 8012, ///< 网络未识别或网络不可达
		ERR_SDK_FAILED          = 8020, ///< iLiveSDK处理失败(通用)
		ERR_INVALID_PARAM       = 8021, ///< 无效的参数
		ERR_NOT_FOUND           = 8022, ///< 无法找到目标
		ERR_NOT_SUPPORT         = 8023, ///< 请求不支持
		ERR_ALREADY_STATE       = 8024, ///< 状态已到位(一般为重复调用引起)
		ERR_KICK_OUT            = 8050, ///< 被踢下线
		ERR_EXPIRE              = 8051, ///< 票据过期(需更新票据userSig)
	};

	/**
	@brief 房间事件
	*/
	enum E_EndpointEventId
	{
		EVENT_ID_NONE = 0,						///< 无
		EVENT_ID_ENDPOINT_ENTER = 1,			///< 进入房间事件
		EVENT_ID_ENDPOINT_EXIT = 2,				///< 退出房间事件
		EVENT_ID_ENDPOINT_HAS_CAMERA_VIDEO = 3, ///< 有发摄像头视频事件
		EVENT_ID_ENDPOINT_NO_CAMERA_VIDEO = 4,	///< 无发摄像头视频事件
		EVENT_ID_ENDPOINT_HAS_AUDIO = 5,		///< 有发音频事件
		EVENT_ID_ENDPOINT_NO_AUDIO = 6,			///< 无发音频事件
		EVENT_ID_ENDPOINT_HAS_SCREEN_VIDEO = 7, ///< 有发屏幕视频事件
		EVENT_ID_ENDPOINT_NO_SCREEN_VIDEO = 8,	///< 无发屏幕视频事件
		EVENT_ID_ENDPOINT_HAS_MEDIA_VIDEO = 9,	///< 有播放视频事件
		EVENT_ID_ENDPOINT_NO_MEDIA_VIDEO = 10,	///< 无播放视频事件
	};

	/**
	@brief 音频场景策略
	*/
	enum E_AudioCategory
	{
		AUDIO_CATEGORY_VOICECHAT = 0,				///< VoIP模式。适合于实时音频通信场景，如实时语音通话
		AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD = 1,	///< 媒体采集与播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的主播人员
		AUDIO_CATEGORY_MEDIA_PLAYBACK = 2,			///< 媒体播放模式。适合于那些对音质要求比较高的直播场景，如主播场景中的听众
	};

	/**
	@brief IM群类型
	*/
	enum E_IMGroupType
	{
		E_Private_Group,
		E_Public_Group,
		E_ChatRoom_Group,
		E_AVChatRoom_Group,
	};

	/**
	@brief 消息类型。
	*/
	enum E_MessageElemType
	{
		TEXT,
		CUSTOM,
		IMAGE,
		FACE,
	};

	/**
	@brief 图片类型。原图是指用户发送的原始图片，尺寸和大小都保持不变；缩略图是将原图等比压缩，压缩后宽、高中较小的一个等于198像素；大图也是将原图等比压缩，压缩后宽、高中较小的一个等于720像素
	*/
	enum E_ImageType
	{
		THUMB,
		LARGE,
		ORIGINAL,
	};

	/**
	@brief 视频编码格式
	*/
	enum E_iLiveStreamEncode
	{
		HLS = 0x01,			///< 请求HLS编码的视频流URL
		FLV = 0x02,			///< 请求FLV编码的视频流URL
		RAW = 0X04,			///< RAW码流
		RTMP = 0X05,		///< RTMP
		HLS_AND_RTMP = 0X06,///< HLS AND RTMP
	};

	/**
	@brief 录制数据类型 
	*/
	enum E_RecordDataType
	{
		E_RecordCamera = 0, ///< 录制摄像头
		E_RecordScreen,		///< 录制辅流(屏幕分享/文件播放)
	};

	/**
	@brief 录制文件类型(RecordFile_NONE不录制)
	*/
	enum E_RecordFileType
	{
		RecordFile_NONE= 0x00,
		RecordFile_HLS = 0x01,
		RecordFile_FLV = 0x02,
		RecordFile_HLS_FLV = 0x03,
		RecordFile_MP4 = 0x04,
		RecordFile_HLS_MP4 = 0x05,
		RecordFile_FLV_MP4 = 0x06,
		RecordFile_HLS_FLV_MP4 = 0x07,
		RecordFile_MP3 = 0x10,
	};

	/**
	@brief 推流数据类型
	*/
	enum E_PushDataType
	{
		E_PushCamera = 0,///< 摄像头
		E_PushScreen,	 ///< 辅流(屏幕分享/文件播放)
	};

	/**
	@brief 码率档位
	*/
	enum E_RateType
	{
		RATE_TYPE_ORIGINAL = 0,	///< 原始码率
		RATE_TYPE_550 = 10,		///< 标清码率550K
		RATE_TYPE_900 = 20,		///< 高清码率900K
	};

	/**
	@brief 色彩格式。
	*/
	enum E_ColorFormat
	{
		COLOR_FORMAT_NONE = -1,		///< 无意义
		COLOR_FORMAT_I420 = 0,		///< i420格式
		COLOR_FORMAT_NV21 = 1,
		COLOR_FORMAT_NV12 = 3,
		COLOR_FORMAT_RGB16 = 7,
		COLOR_FORMAT_RGB24 = 8,		///< rgb24格式(实际内存中存放方式是BGR888)
		COLOR_FORMAT_RGB32 = 9,
		COLOR_FORMAT_RGBA  = 10,
		COLOR_FORMAT_ABGR  = 11,
		COLOR_FORMAT_YUVA8888  = 21,
	};

	/**
	@brief 屏幕共享状态。
	@details 屏幕共享状态。
	*/
	enum E_ScreenShareState
	{
		E_ScreenShareNone,	///< 未开启屏幕分享
		E_ScreenShareWnd,	///< 开启了指定窗口的共享
		E_ScreenShareArea,	///< 开启了指定区域的共享
	};

	/**
	@brief 播片状态。
	*/
	enum E_PlayMediaFileState
	{
		E_PlayMediaFileStop,	///< 停止播放
		E_PlayMediaFilePlaying,	///< 播放中
		E_PlayMediaFilePause,	///< 暂停中
	};

	/**
	@brief 视频数据类型。
	@details 视频数据类型。
	*/
	enum E_VideoSrc
	{
		VIDEO_SRC_TYPE_NONE = 0,	///< 默认值，无意义
		VIDEO_SRC_TYPE_CAMERA = 1,	///< 摄像头
		VIDEO_SRC_TYPE_SCREEN = 2,	///< 屏幕
		VIDEO_SRC_TYPE_MEDIA = 3,	///< 播片
	};

	/**
	@brief 设备操作类型
	*/
	enum E_DeviceOperationType
	{
		E_DeviceOperationNone,		///< 默认值，无意义
		E_OpenCamera,				///< 打开摄像头
		E_CloseCamera,				///< 关闭摄像头
		E_OpenExternalCapture,		///< 打开主路自定义采集
		E_CloseExternalCapture,		///< 关闭主路自定义采集
		E_OpenExternalCaptureSub,	///< 打开辅路自定义采集
		E_CloseExternalCaptureSub,	///< 关闭辅路自定义采集
		E_OpenMic,					///< 打开麦克风
		E_CloseMic,					///< 关闭麦克风
		E_OpenPlayer,				///< 打开扬声器
		E_ClosePlayer,				///< 关闭扬声器
		E_OpenScreenShare,			///< 打开屏幕分享
		E_CloseScreenShare,			///< 关闭屏幕分享
		E_OpenSystemVoiceInput,		///< 打开系统声音采集
		E_CloseSystemVoiceInput,	///< 关闭系统声音采集
		E_OpenPlayMediaFile,		///< 打开文件播放
		E_ClosePlayMediaFile,		///< 关闭文件播放
	};

	/**
	@brief 水印类型。
	@details 水印类型,就是针对哪种编码分辨率的视频设置水印。
	*/
	enum E_WaterMarkType
	{
		WATER_MARK_TYPE_NONE        = 0,
		WATER_MARK_TYPE_320_240     = 1, ///< 针对编码分辨率为320*240的视频设置水印。
		WATER_MARK_TYPE_480_360     = 2, ///< 针对编码分辨率为480*360的视频设置水印。
		WATER_MARK_TYPE_640_480     = 3, ///< 针对编码分辨率为640*480的视频设置水印。
		WATER_MARK_TYPE_640_368     = 4, ///< 针对编码分辨率为640*368的视频设置水印。
		WATER_MARK_TYPE_960_540     = 5, ///< 针对编码分辨率为960*540的视频设置水印。
		WATER_MARK_TYPE_1280_720    = 6, ///< 针对编码分辨率为1280*720的视频设置水印。
		WATER_MARK_TYPE_192_144     = 7, ///< 针对编码分辨率为192*144的视频设置水印。
		WATER_MARK_TYPE_320_180     = 8, ///< 针对编码分辨率为192*144的视频设置水印。
		WATER_MARK_TYPE_MAX,
	};

	/**
	@brief 测速通话类型。
	*/
	enum E_SPTCallType
	{
		SpeedTestCallType_Audio,		///< 纯音频
		SpeedTestCallType_AudioVideo,	///< 音视频
	};

	/**
	@brief 测速目的。
	*/
	enum E_SPTPurpose
	{
		SPTPurpose_EntTest,		///< 结束通话上报测速数据或其它一项专项白名单测速;
		SPTPurpose_UserTest,	///< 用户主动点击测速，目的是测试当前网络状况;
	};

	/**
	@brief 音频数据输入和输出类型。
	*/
	enum E_AudioDataSourceType
	{
		AUDIO_DATA_SOURCE_MIC           = 0, ///< 获取本地麦克风采集的音频数据(注意: 注册此类型回调后，即使没有打开麦克风，也会开始回调麦克风音频数据)。
		AUDIO_DATA_SOURCE_MIXTOSEND     = 1, ///< 输入额外的音频数据，与本地发送的音频数据混音后发送出去。
		AUDIO_DATA_SOURCE_SEND          = 2, ///< 获取发送方最终发送出去的音频数据。
		AUDIO_DATA_SOURCE_MIXTOPLAY     = 3, ///< 输入额外的音频数据，与本地播放的音频数据混音后给扬声器播放出来。
		AUDIO_DATA_SOURCE_PLAY          = 4, ///< 获取本地扬声器播放音频数据。
		AUDIO_DATA_SOURCE_NETSTREM      = 5, ///< 获取接收方收到的音频数据。
		AUDIO_DATA_SOURCE_VOICEDISPOSE  = 6, ///< 麦克风音频数据预处理。
		AUDIO_DATA_SOURCE_SYNCMIXTOSEND = 7, ///< 发送混音输入，实时性更高。
		AUDIO_DATA_SOURCE_AACRAWSTREAM  = 8, ///< 编码AAC数据获取，内部使用类型，暂不对外开放
		AUDIO_DATA_SOURCE_END           = 9, ///< 结束标志。
	};

	/**
	@brief 音频源类型(暂无效，预留)。
	*/
	enum E_AudioSrcType
	{
		AUDIO_SRC_TYPE_NONE			= 0,	///< 默认值，无意义。
		AUDIO_SRC_TYPE_MIC			= 1,	///< 麦克风。
		AUDIO_SRC_TYPE_ACCOMPANY	= 2,	///< 伴奏。
		AUDIO_SRC_TYPE_MIX_INPUT	= 3,	///< 混音输入。
		AUDIO_SRC_TYPE_MIX_OUTPUT	= 4,	///< 混音输出。
	};

	/**
	@brief 视频渲染方式
	*/
	enum E_RootViewType
	{
		ROOT_VIEW_TYPE_NONE = 0,	///< 默认值，无意义。
		ROOT_VIEW_TYPE_D3D	= 1,	///< Direct3D硬件加速
		ROOT_VIEW_TYPE_GDI	= 2,	///< GDI
	};

	/**
	@brief 渲染拉伸模式
	*/
	enum E_ViewMode
	{
		VIEW_MODE_NONE	= 0,		///< 默认值，无意义。
		VIEW_MODE_FIT		= 1,	///< 按照显示区域的比例进行缩放后填满区域。
		VIEW_MODE_HIDDEN	= 2,	///< 按照图像宽高的比例进行缩放后居中填充区域。
	};

	/**
	@brief 推流机器环境类型
	*/
	enum E_PushSvrType
	{
		E_CustomSupport,	///< 0: 自研
		E_CloudSupport,		///< 1: 云支持
	};

	/**
	@brief sdk通信通道类型
	*/
	enum E_ChannelMode
	{
		E_ChannelIMRestAPI,	///< IMSDKRestAPI通道,必须在进房时带上tls加密版本的privateMapKey(默认)
		E_ChannelIMSDK,		///< IMSDK通道(iLiveSDK 1.9.0之前的版本所用的通道)
	};

	/**
	@brief 自定义数据类型。
	*/
	enum E_CustomDataMode
	{
		E_CUSTOMDATA_WITH_AVDATA = 2,	///< 跟随音视频数据发送
		E_CUSTOMDATA_WITH_SEIDATA = 3,	///< 附带在视频帧的SEI段内发送，在转码后台会被以SEI段的形式插入到旁路流中，payload type为0xf3
		E_CUSTOMDATA_WITH_NALU = 4,		///< 附带在视频帧的SEI段内发送一端NALU，在转码后台会被以视频参考帧的形式插入到旁路流中
	};
	
	/**
	@brief IMSDK图片消息，图片文件格式。
	*/
	enum E_ImageFormat
	{
		E_IMAGE_FORMAT_JPG = 0x1,
		E_IMAGE_FORMAT_GIF = 0x2,
		E_IMAGE_FORMAT_PNG = 0x3,
		E_IMAGE_FORMAT_BMP = 0x4,
		E_IMAGE_FORMAT_UNKNOWN = 0xff,
	};

	/// 音视频通话的通话能力权限位。
	const uint64 AUTH_BITS_DEFAULT              = -1;			///< 所有权限。
	const uint64 AUTH_BITS_CREATE_ROOM          = 0x00000001;	///< 创建房间权限。
	const uint64 AUTH_BITS_JOIN_ROOM            = 0x00000002;	///< 加入房间的权限。
	const uint64 AUTH_BITS_SEND_AUDIO           = 0x00000004;	///< 发送音频的权限。
	const uint64 AUTH_BITS_RECV_AUDIO           = 0x00000008;	///< 接收音频的权限。
	const uint64 AUTH_BITS_SEND_CAMERA_VIDEO    = 0x00000010;	///< 发送摄像头视频的权限。
	const uint64 AUTH_BITS_RECV_CAMERA_VIDEO    = 0x00000020;	///< 接收摄像头视频的权限。
	const uint64 AUTH_BITS_SEND_SCREEN_VIDEO    = 0x00000040;	///< 发送屏幕视频的权限。
	const uint64 AUTH_BITS_RECV_SCREEN_VIDEO    = 0x00000080;	///< 接收屏幕视频的权限。

	/**
	@brief 被挤下线回调函数指针类型;
	*/
	typedef void (*ForceOfflineCallback)();

	/**
	@brief 连接网络成功函数指针类型;
	*/
	typedef void (*onNetworkCallback)();

	/**
	@brief 操作完成回调函数指针类型;
	@param [in] result 操作结果,NO_ERR表示成功
	@param [in] errInfo 错误描述
	@param [in] data 自定义指针
	*/
	typedef void (*iLiveCompleteCallback)(int result, const char *errInfo, void* data);
	
	/**
	@brief 成功带值回调函数指针类型的封装
	*/
	template <typename T>
	struct Type
	{
		/**
		@brief 通用的成功带值回调函数指针类型;
		@param [in] value 操作成功，SDK返回给业务侧响应类型的值;
		@param [in] data SDK传回业务侧自定义的数据指针;
		*/
		typedef void (*iLiveValueSuccCallback)(T value, void* data);
	};

	/**
	@brief 收到消息的回调函数指针类型。
	@param [in] msg 收到的群消息
	*/
	typedef void (*iLiveMessageCallback)( const struct Message &msg, void* data );

	/**
    @brief 视频帧预处理回调
    @param video_frame 视频帧对象。
    @param data 自定义指针
    */
	typedef void (*iLivePreTreatmentCallback)( struct LiveVideoFrame* video_frame, void* data );
	/**
    @brief 视频帧回调
    @param video_frame 视频帧对象。
    @param data 自定义指针
    */
    typedef void (*iLivePreviewCallback)( const struct LiveVideoFrame* video_frame, void* data );

	/**
	@brief 设备操作回调
	@param [in] oper 设备操作类型;
	@param [in] retCode 错误码，NO_ERR表示成功;
	@param [in] data 自定义指针;
	*/
	typedef void (*iLiveDeviceOperationCallback)(E_DeviceOperationType oper, int retCode, void* data);
	
	/**
	@brief 通用失败回调
	@param [in] code 错误码
	@param [in] desc 错误描述
	@param [in] data 自定义指针
	*/
	typedef void (*iLiveErrCallback)(const int code, const char *desc, void* data);
	/**
	@brief 通用成功回调
	@param [in] data 自定义指针
	*/
	typedef void (*iLiveSucCallback)(void* data);

	/**
	@brief SDK主动退出房间监听函数指针
	@details SDK内部会因为30s心跳包超时等原因主动退出房间，APP需要监听此退出房间事件并对该事件进行相应处理
	@param [in] reason 退出原因错误码
	@param [in] errorinfo 退出原因描述
	@param [in] data 用户自定数据指针，回调函数中原封不动传回给业务侧
	*/
	typedef void (*iLiveRoomDisconnectListener)(int reason, const char *errorInfo, void* data);
	/**
	@brief 房间内成员变化监听函数指针
	@details 当房间成员发生状态变化(如是否发音频、是否发视频等)时，会通过该函数指针通知业务侧
	@param [in] event_id 状态变化id，详见EndpointEventId的定义
	@param [in] identifier_list 发生状态变化的成员id列表
	@param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧
	*/
	typedef void (*iLiveMemStatusListener)(E_EndpointEventId eventId, const Vector<String> &ids, void* data);
	/**
	@brief 设备插拔监听函数指针
	@param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧
	*/
	typedef void (*iLiveDeviceDetectListener)(void* data);
	/**
	@brief 房间内质量报告的回调函数指针类型
	@details 在iLiveRoomOption中的参数
	@param [in] param 房间内质量参数.
	@param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧
	*/
	typedef void (*iLiveQualityParamCallback)(const struct iLiveRoomStatParam& param, void* data);

	/**
    @brief 音频数据回调函数定义。
    @param [in] audioFrame 音频数据。
    @param [in] srcType 音频数据类型。
    @param [in] data 用户自定数据类型，回调函数中原封不动传回给业务侧。
    @details 回调处理要求是非阻塞的，SDK回调时间间隔稳定在20ms左右, 在回调中阻塞过长时间会导致声音异常等问题。
	@remark 回调函数设定为专门处理数据用。函数回调在非主线程，请确保线程安全。特别是不要在回调函数中直接调用SDK接口。
    */
	typedef void (*iLiveAudioDataCallback)(struct iLiveAudioFrame* audioFrame, E_AudioDataSourceType srcType, void* data);

	/**
	@param [in] data 自定义数据。
	*/
	typedef void (*iLiveCustomDataCallback)(struct sCustomData& data);

	/**
	@brief 消息中的图片
	*/
	struct Image
	{
		/**
		@brief 图片构造方法
		@param [in] _type 图片类型
		@param [in] _size 图片文件大小
		@param [in] _width 图片宽度
		@param [in] _height 图片高度
		@param [in] _url 图片下载地址
		*/
		Image(E_ImageType _type, unsigned _size, unsigned _width, unsigned _height, String _url) : type(_type), size(_size), width(_width), height(_height), url(_url)
		{

		}
		E_ImageType type;
		unsigned size;
		unsigned height;
		unsigned width;
		String url;
	};

	/**
	@brief 消息元素基类
	*/
	struct MessageElem
	{
		E_MessageElemType type;
		MessageElem(){}
		MessageElem(const MessageElem& oth):type(oth.type){}
		virtual ~MessageElem() {}
	};

	/**
	@brief 文本消息元素
	*/
	struct MessageTextElem : public MessageElem
	{
		MessageTextElem(const String& _content)
		:content(_content)
		{
			type = TEXT;
		}
		String content;
	};

	/**
	@brief 自定义消息元素
	*/
	struct MessageCustomElem : public MessageElem
	{
		MessageCustomElem(const String& _data, const String& _ext) : data(_data), ext(_ext)
		{
			type = CUSTOM;
		}
		String data;
		String ext;
	};

	/**
	@brief 表情消息元素
	*/
	struct MessageFaceElem : public MessageElem
	{
		MessageFaceElem(int _index, const String &_data) : data(_data), index(_index)
		{
			type = FACE;
		}
		int index;
		String data;
	};

	/**
	@brief 图片消息元素
	*/
	struct MessageImageElem : public MessageElem
	{
		MessageImageElem(const String& _path) : format(E_IMAGE_FORMAT_UNKNOWN), path(_path)
		{
			type = IMAGE;
		}
		MessageImageElem(const MessageImageElem& other)
			:MessageElem(other)
		{
			format = other.format;
			path = other.path;
			for (int i = 0; i < other.images.size(); ++i)
			{
				Image *otherImg = other.images[i];
				Image *img = new Image(otherImg->type, otherImg->size, otherImg->width, otherImg->height, otherImg->url);
				images.push_back(img);
			}
		}
		~MessageImageElem()
		{
			while(images.size() > 0)
			{
				delete images.back();
				images.pop_back();
			}
		}

		E_ImageFormat format; ///< 图片文件格式，发送时不用填写，sdk自动根据文件名检测
		String path;///< 发送图片的本地地址，仅发送有效
		Vector<Image*> images;///< 接收的图片，仅接收有效
	};

	/**
	@brief 消息
	@details 一个消息内可以包含多个消息元素，按照顺序存放在vector中
	*/
	struct Message
	{
		String sender;
		uint32 time;
		Vector<MessageElem*> elems;
		
		Message()
		{
		}

		Message(const Message& other)
		{
			sender = other.sender;
			time = other.time;
			for (int i = 0; i < other.elems.size(); ++i)
			{
				const MessageElem* elem = other.elems[i];
				switch(elem->type)
				{
				case TEXT:
					{
						const MessageTextElem *otherElem = static_cast<const MessageTextElem*>(other.elems[i]);
						MessageTextElem *e = new MessageTextElem(otherElem->content);
						elems.push_back(e);
						break;
					}
				case CUSTOM:
					{
						const MessageCustomElem *otherElem = static_cast<const MessageCustomElem*>(other.elems[i]);
						MessageCustomElem *e = new MessageCustomElem(otherElem->data, otherElem->ext);
						elems.push_back(e);
						break;
					}
				case IMAGE:
					{
						const MessageImageElem *otherElem = static_cast<const MessageImageElem*>(other.elems[i]);
						MessageImageElem *e = new MessageImageElem(*otherElem);
						elems.push_back(e);
						break;
					}
				case FACE:
					{
						const MessageFaceElem *otherElem = static_cast<const MessageFaceElem*>(other.elems[i]);
						MessageFaceElem *e = new MessageFaceElem(otherElem->index, otherElem->data);
						elems.push_back(e);
						break;
					}
				}
			
			}
		}

		Message& operator=(const Message& other)
		{
			if (&other == this) return *this;
			sender = other.sender;
			time = other.time;
			for (int i = 0; i < other.elems.size(); ++i)
			{
				const MessageElem* elem = other.elems[i];
				switch(elem->type)
				{
				case TEXT:
					{
						const MessageTextElem *otherElem = static_cast<const MessageTextElem*>(other.elems[i]);
						MessageTextElem *e = new MessageTextElem(otherElem->content);
						elems.push_back(e);
						break;
					}
				case CUSTOM:
					{
						const MessageCustomElem *otherElem = static_cast<const MessageCustomElem*>(other.elems[i]);
						MessageCustomElem *e = new MessageCustomElem(otherElem->data, otherElem->ext);
						elems.push_back(e);
						break;
					}
				case IMAGE:
					{
						const MessageImageElem *otherElem = static_cast<const MessageImageElem*>(other.elems[i]);
						MessageImageElem *e = new MessageImageElem(*otherElem);
						elems.push_back(e);
						break;
					}
				case FACE:
					{
						const MessageFaceElem *otherElem = static_cast<const MessageFaceElem*>(other.elems[i]);
						MessageFaceElem *e = new MessageFaceElem(otherElem->index, otherElem->data);
						elems.push_back(e);
						break;
					}
				}
			}
			return *this;
		}

		~Message()
		{
			while(elems.size()>0)
			{
				delete elems.back();
				elems.pop_back();
			}
		}
	};
	
	/**
	@brief iLiveRoom配置项。
	@details 在创建或者加入房间时，需要先填写此结构作为参数传入;
	*/
	struct iLiveRoomOption
	{
		/**
		@brief 构造函数，初始化成员变量值。
		*/
		iLiveRoomOption()
			:audioCategory(AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD)//互动直播场景
			,roomId(0)
			,groupType(E_AVChatRoom_Group)
			,joinImGroup(true)
			,authBits(AUTH_BITS_DEFAULT)
			,autoRequestCamera(true)
			,autoRequestScreen(true)
			,autoRequestMediaFile(true)
			,timeElapse(1000)
			,enableHwEnc(false)
			,enableHwDec(false)
			,enableHwScreenEnc(false)
			,enableHwScreenDec(false)
			,roomDisconnectListener(NULL)
			,memberStatusListener(NULL)
			,deviceDetectListener(NULL)
			,qualityParamCallback(NULL)
			,data(NULL)
		{
		}

		E_AudioCategory			audioCategory;			///< 音视场景策略,详细信息见E_AudioCategory的定义.
		uint32					roomId;					///< 房间ID,由业务侧创建并维护的房间ID
		E_IMGroupType			groupType;				///< 创建房间时，所创建的IM群类型
		String					groupId;				///< IM群组ID;此字段仅大咖模式下使用;
		bool					joinImGroup;			///< 是否加入IM群组,此字段仅大咖模式下使用(默认为true，如果设置为false，需要业务侧后台将用户拉进IM群组);
		/**
		@brief 通话能力权限位;
		@details 主播应当设置为AUTH_BITS_DEFAULT,连麦观众设置为AUTH_BITS_DEFAULT & (~AUTH_BITS_CREATE_ROOM),观众设置为AUTH_BITS_JOIN_ROOM|AUTH_BITS_RECV_AUDIO|AUTH_BITS_RECV_CAMERA_VIDEO|AUTH_BITS_RECV_SCREEN_VIDEO;
		@note 1.9.0.0开始，sdk默认使用E_ChannelIMRestAPI通道，此通道模式下，authBits参数无效，应当通过privateMapKey控制权限位;参见setChannelMode接口定义.
		*/
		uint64					authBits;
		String					controlRole;			///< 角色名，web端音视频参数配置工具所设置的角色名
		String					privateMapKey;			///< 通话能力权限位的加密串
		bool					autoRequestCamera;		///< 房间内有成员打开摄像头时，是否自动请求画面;
		bool					autoRequestScreen;		///< 房间内有成员打开屏幕分享时，是否自动请求画面;
		bool					autoRequestMediaFile;	///< 房间内有成员打开播片时，是否自动请求画面;
		uint32					timeElapse;				///< sdk执行qualityParamCallback回调的时间间隔,单位毫秒(SDK内部1秒更新一次，所以,timeElapse小于1000将会被修正到1000)。
		bool					enableHwEnc;			///< 摄像头是否使用硬件编码(极速模式下，请勿使用硬编解)。
		bool					enableHwDec;			///< 摄像头是否使用硬件解码(极速模式下，请勿使用硬编解)。
		bool					enableHwScreenEnc;		///< 屏幕分享是否使用硬件编码(极速模式下，请勿使用硬编解)。
		bool					enableHwScreenDec;		///< 屏幕分享是否使用硬件解码(极速模式下，请勿使用硬编解)。
		String					bussInfo;				///< 业务侧自定义数据

		/**
		@brief SDK主动退出房间回调;
		@details 在网络断开30秒后,会收到此回调,此时已被sdk强制退出房间,所以,不要调用退出房间接口;网络重连后,需要重新创建\进入房间,参见iLiveRoomDisconnectListener定义。
		*/
		iLiveRoomDisconnectListener	roomDisconnectListener;
		/**
		@brief 房间成员事件通知，参见iLiveMemStatusListener定义。
		*/
		iLiveMemStatusListener		memberStatusListener;
		/**
		@brief 设备插拔监听回调;
		@details 当摄像头、麦克风、扬声器等设备的接入及拔出时，sdk会通过此回调通知给业务侧，收到此回调需要更新设备列表;参见iLiveDeviceDetectListener定义。
		@note 当摄像头、麦克风、扬声器等正在使用中时,收到此回调前，还会收到相应设备关闭的回调;
		@todo 此字段即将废弃，请用户使用iLive::setDeviceDetectCallback()接口设置此此回调
		*/
		Deprecated
		iLiveDeviceDetectListener	deviceDetectListener;
		/**
		@brief 质量报告的回调;
		@details 如果用户需要监听房间内直播质量,可以设置此回调，并设置timeElapse的值。参见iLiveQualityParamCallback定义。
		*/
		iLiveQualityParamCallback	qualityParamCallback;
		/**
		@brief 用户自定义数据类型，在iLiveRoomOption中指定的各个回调中原封不动返回。
		*/
		void*						data;
	};

	/**
	@brief 录制配置项。
	@details 录制操作需要传入此类型的参数。
	*/
	struct RecordOption
	{
		/**
		@brief 构造函数，初始化成员变量值。
		*/
		RecordOption()
			:recordDataType(E_RecordCamera)
			,fileName("")
			,classId(0)
		{
		}

		E_RecordDataType	recordDataType; ///< 录制的数据类型,参见E_RecordDataType定义。
		String				fileName;		///< 录制后的文件名。
		int					classId;		///< 视频分类ID(暂无效)。
	};

	/**
	@brief 推流配置项。
	@details 推流操作需要传入此类型的参数。
	*/
	struct PushStreamOption
	{
		/**
		@brief 构造函数，初始化成员变量。
		*/
		PushStreamOption()
			:pushDataType(E_PushCamera)
			,encode(HLS)
			,recordFileType(RecordFile_NONE)
			,bOnlyPushAudio(false)
			,pushSvrType(E_CloudSupport)
			,recordId(0)
		{
		}

		E_PushDataType				pushDataType;		///< 推送数据类型，参见E_PushDataType定义.
		E_iLiveStreamEncode			encode;				///< 推流数据编码方式，参见E_TIMStreamEncode定义.
		E_RecordFileType			recordFileType;		///< 推流时自动录制的文件类型，参见E_RecordFileType定义.
		/**
		@brief 是否纯音频推流
		@remark 
		1、要使用纯音频推流，需注意:<br/>
			(1)需要联系腾讯开启白名单放可使用此功能;<br/>
			(2)不能在后台开启自动推流配置项;<br/>
			(3)在开启推流前，不能有视频流(打开摄像头、屏幕分享等);<br/>
		2、 使用纯音频推流时，其他相关参数说明:<br/>
			(1)如果需要推流时自动录制文件，recordFileType需要设置为RecordFile_MP3;<br/>
			(2)使用纯音频推流时，pushDataType设置为E_PushCamera和E_PushScreen，效果一样，建议使用默认值E_PushCamera;
		*/
		bool						bOnlyPushAudio;		///< 纯音频推流,纯音频推流时，如果要录制文件，需要将recordFileType指定为RecordFile_MP3
		
		E_PushSvrType				pushSvrType;		///< 推流机器环境类型(暂时无效，使用默认值即可);
		uint32						recordId;			///< 用户自定义RecordId(对应录制视频给业务侧服务器回调的字段stream_param的cliRecoId);
	};

	/**
	@brief 推流返回url类型
	*/
	struct LiveUrl
	{
		E_iLiveStreamEncode			encodeType;	///< 视频流编码类型
		String						url;		///< 视频流播放URL
		E_RateType					rateType;	///< 码率档位信息
	};
	
	/**
	@brief 推流返回数据类型
	*/
	struct PushStreamRsp
	{
		PushStreamRsp()
			:channelId(0)
		{
		}

		Vector<LiveUrl>		urls;		///< Url列表
		uint64				channelId;	///< 频道ID,直播码模式下，始终为0;
		uint32				tapeTaskId; ///< 录制标记为录制的时候带回录制task_id有效
	};

	/**
	@brief 视频帧描述。
	@details 视频帧描述。
	*/
	struct VideoFrameDesc
	{
		VideoFrameDesc()
		: colorFormat(COLOR_FORMAT_RGB24)
		, width(0)
		, height(0)
		, externalData(false)
		, rotate(0)
		, srcType(VIDEO_SRC_TYPE_CAMERA)
		{
		}

		E_ColorFormat	colorFormat;	///< 色彩格式，详情见ColorFormat的定义。
		uint32			width;			///< 宽度，单位：像素。
		uint32			height;			///< 高度，单位：像素。
		bool			externalData;	///< 数据是否来自外部摄像头。
		E_VideoSrc		srcType;		///< 视频源类型，详情见VideoSrcType的定义。
		uint32			rotate;			///< 视频画面旋转角度，在渲染时需要考虑此角度值，0、1、2、3分别表示0°、90°、180°、270°
	};

	/**
	@brief 视频帧。
	*/
	struct LiveVideoFrame
	{
		LiveVideoFrame()
		: dataSize(0)
		, data(NULL)
		, timeStamp(0)
		{
		}

		String			identifier;	///< 视频帧所属的房间成员id。
		VideoFrameDesc	desc;		///< 视频帧描述。
		uint32			dataSize;	///< 视频帧的数据缓冲区大小，单位：字节。
		uint8*			data;		///< 视频帧的数据缓冲区，SDK内部会管理缓冲区的分配和释放。
		uint64			timeStamp;  ///< 视频帧的时间戳，SDK内部会自动填写好，utc时间，0为无效值。
	};

	/**
	@brief 直播流信息
	*/
	struct AVStream
	{
		AVStream(String id, E_VideoSrc type): id(id), srcType(type) {};
		String		id;
		E_VideoSrc	srcType;
	};

	/**
	@brief 网络运行时参数
	*/
	struct iLiveNetworkStatParam
	{
		iLiveNetworkStatParam()
			: kbpsSend(0)
			, lossRateSend(0)
			, lossRateSendUdt(0)
			, packetSend(0)
			, lossModelSend(0)

			, kbpsRecv(0)
			, lossRateRecvUdt(0)
			, lossRateRecv(0)
			, packetRecv(0)
			, unsendUdt(0)
			, interfaceIP(0)
			, interfacePort(0)
			, clientIP(0)
			, isTcp(false)
			, lossModelRecv(0)

			, cpuRateApp(0)
			, cpuRateSys(0)
			, rtt(0)

			, udtSMode(0)
			, udtRMode(0)
			, udtSendq(0)
			, udtRecvq(0)
			, udtEnable(false)
		{
		}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;

			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(kbpsSend), kbpsSend);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRateSend), lossRateSend);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRateSendUdt), lossRateSendUdt);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(packetSend), packetSend);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossModelSend), lossModelSend);

			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(kbpsRecv), kbpsRecv);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRateRecvUdt), lossRateRecvUdt);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRateRecv), lossRateRecv);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(packetRecv), packetRecv);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(unsendUdt), unsendUdt);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(interfaceIP), interfaceIP);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(interfacePort), interfacePort);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(clientIP), clientIP);
			szRet += String::Format("%s%s: %d\n", pre.c_str(), NAME(isTcp), isTcp);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossModelRecv), lossModelRecv);

			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(cpuRateApp), cpuRateApp);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(cpuRateSys), cpuRateSys);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(rtt), rtt);

			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(udtSMode), udtSMode);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(udtRMode), udtRMode);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(udtSendq), udtSendq);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(udtRecvq), udtRecvq);
			szRet += String::Format("%s%s: %d\n", pre.c_str(), NAME(udtEnable), udtEnable);

			return szRet;
		}

		uint32	kbpsSend;			///< 发包速率,单位kbps
		uint16	lossRateSend;		///< 上行丢包率，从Hello的回包中获得
		uint16	lossRateSendUdt;	///< udt后上行丢包率
		uint32	packetSend;			///< 发包速率,每秒发包的个数
		uint16	lossModelSend;		///< 上行平均连续丢包个数，从Hello的回包中获得

		uint32	kbpsRecv;			///< 收包速率,单位kbps
		uint16	lossRateRecvUdt;	///< udt后下行丢包率
		uint16	lossRateRecv;		///< 下行丢包率
		uint32	packetRecv;			///< 收包速率,每秒收包的个数
		uint32	unsendUdt;			///< udt未发送包数
		uint32	interfaceIP;		///< 接口机ip
		uint16	interfacePort;		///< 与接口机连接的端口
		uint32	clientIP;			///< 客户端ip
		bool	isTcp;				///< 是否为tcp
		uint16	lossModelRecv;		///< 下行平均连续丢包个数

		uint16	cpuRateApp;			///< App进程的CPU使用率×10000(例如：3456对应于34.56%)
		uint16	cpuRateSys;			///< 当前系统的CPU使用率×10000(例如：3456对应于34.56%)
		uint32	rtt;				///< 往返时延（Round-Trip Time），单位毫秒，统计方法：Hello SendData 的时候记一个 TickCount，Hello Reply 的时候记一个 TickCount，两者的差值为时延

		uint16	udtSMode;			///< udt发送端模式
		uint16	udtRMode;			///< udt接收端模式
		uint16	udtSendq;			///< udt发送端队列最大时间长度
		uint16	udtRecvq;			///< udt接收端队列最大时间长度
		bool	udtEnable;			///< udt switch
	};

	/**
	@brief 视频采集参数
	*/
	struct iLiveVideoCaptureParam
	{
		iLiveVideoCaptureParam():width(0), height(0), fps(0) {}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(width), width);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(height), height);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(fps), fps);
			return szRet;
		}

		uint32	width;    ///< 视频宽
		uint32	height;   ///< 视频高
		uint32	fps;      ///< 帧率
	};

	/**
	@brief GOP相关编码器设置参数
	*/
	struct iLiveVideoEncNewGOPInterParam
	{
		iLiveVideoEncNewGOPInterParam()
			: reffrmInterval(0)
			, encIFrmNum(0)
			, reqIFrmNum(0)
			, recvNACKNum(0)
			, recvFailedFrmInfNum(0)
			, lossrate2S(0)
			, weigth20SLossRate(0)
		{
		}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(reffrmInterval), reffrmInterval);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(encIFrmNum), encIFrmNum);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(reqIFrmNum), reqIFrmNum);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(recvNACKNum), recvNACKNum);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(recvFailedFrmInfNum), recvFailedFrmInfNum);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossrate2S), lossrate2S);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(weigth20SLossRate), weigth20SLossRate);
			return szRet;
		}

		uint32	reffrmInterval;     //编码器设置的参考帧跨帧个数
		uint32	encIFrmNum;
		uint32	reqIFrmNum;
		uint32	recvNACKNum;
		uint32	recvFailedFrmInfNum;
		uint32	lossrate2S;
		uint32	weigth20SLossRate;
	};

	/**
	@brief 视频编码相关参数
	*/
	struct iLiveVideoEncodeParam
	{
		iLiveVideoEncodeParam()
			: viewType(0), width(0), height(0), fps(0)
			, bitrate(0), angle(0), encodeType(0), hw(0)
		{
		}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(viewType), viewType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(width), width);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(height), height);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(fps), fps);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(bitrate), bitrate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(angle), angle);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(encodeType), encodeType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(hw), hw);

			szRet += pre + "gopparam:\n";
			szRet += gopparam.getInfoString(pre + "   ");

			return szRet;
		}

		uint32 viewType;	///< 画面类型，作为编码信息索引：0-主路画面 2-辅路
		uint32 width;       ///< 视频编码宽
		uint32 height;      ///< 视频编码高
		uint32 fps;         ///< 视频编码实时帧率×10
		uint32 bitrate;     ///< 视频编码码率(无包头)
		uint32 angle;       ///< 角度
		uint32 encodeType;	///< 视频编码类型
		uint32 hw;			///< 是否开硬件编码

		iLiveVideoEncNewGOPInterParam gopparam; //新的GOP参数
	};

	/**
	@brief 视频发送参数
	*/
	struct iLiveVideoSendParam
	{
		iLiveVideoSendParam()
			:lossRate(0)
			,iFec(0)
			,spFec(0)
			,pkt(0)
			,STnSBGainLoss12s(0)
			,STnSBDecLostMaxConcal12s(0)
			,STnSBBreakSmallBreakContiPlc12s(0)
		{
		}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRate), lossRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(iFec), iFec);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(spFec), spFec);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(pkt), pkt);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(STnSBGainLoss12s), STnSBGainLoss12s);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(STnSBDecLostMaxConcal12s), STnSBDecLostMaxConcal12s);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(STnSBBreakSmallBreakContiPlc12s), STnSBBreakSmallBreakContiPlc12s);
			return szRet;
		}

		uint32 lossRate;						///< 视频发送参数丢包率
		uint32 iFec;							///< 视频发送参数I帧fec
		uint32 spFec;							///< 视频发送参数sp帧
		uint32 pkt;								///< 视频发送包数
		uint32 STnSBGainLoss12s;				///< 人为补零、人为丢包
		uint32 STnSBDecLostMaxConcal12s;		///< 解码端统计的丢包、jitter中统计的EOS、大于一定数量的连续丢包
		uint32 STnSBBreakSmallBreakContiPlc12s;	///< 卡顿次数、可能的小卡顿次数、连续plc
	};

	/**
	@brief 视频解码相关参数
	*/
	struct iLiveVideoDecodeParam
	{
		iLiveVideoDecodeParam()
			: viewType(0)
			, width(0)
			, height(0)
			, fps(0)
			, bitrate(0)
			, hw(0)
			, codecType(0)
			, hwdecDelay(0)
		{
		}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %s\n", pre.c_str(), NAME(userId), userId.c_str());
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(viewType), viewType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(width), width);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(height), height);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(fps), fps);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(bitrate), bitrate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(hw), hw);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(codecType), codecType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(hwdecDelay), hwdecDelay);
			return szRet;
		}

		String userId;		///< 解码用户
		uint32 viewType;	///< 画面类型，作为编码信息索引：0-主路画面 2-辅路
		uint32 width;		///< 视频解码宽
		uint32 height;		///< 视频解码高
		uint32 fps;			///< 视频解码出的帧率×10
		uint32 bitrate;		///< 视频解码出的码率(无包头)
		uint32 hw;			///< 是否开启硬编解
		uint32 codecType;	///< 解码类型
		uint32 hwdecDelay;	///< 解码延迟
	};

	/**
	@brief 视频接收参数
	*/
	struct iLiveVideoRecvParam
	{
		iLiveVideoRecvParam():lossRate(0.f), dwJitterR(0), dwBRR(0){}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %.2f\n", pre.c_str(), NAME(lossRate), lossRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(dwJitterR), dwJitterR);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(dwBRR), dwBRR);
			return szRet;
		}

		float	lossRate;		///< 视频接收丢包率
		uint32	dwJitterR;		///< 视频接收抖动
		uint32	dwBRR;			///< 视频接收码率
	};

	/**
	@brief 视频下发调控参数,与在后台Spear上配置的参数相关
	*/
	struct iLiveVideoQosParam
	{
		iLiveVideoQosParam()
			: width(0), height(0), fps(0), bitrate(0), encodeType(0), minQp(0), maxQp(0)
			, fectype(0), iFecPrecent(0), spFecPrecent(0), pFecPrecent(0), iMtu(0)
			, spMtu(0), pMtu(0), iFecMinPkg(0), spFecMinPkg(0), pFecMinPkg(0), iFecMinSize(0)
			, spFecMinSize(0), pFecMinSize(0), gopType(0), gop(0), encMode(0), hw(0)
		{
		}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(width), width);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(height), height);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(fps), fps);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(bitrate), bitrate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(encodeType), encodeType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(minQp), minQp);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(maxQp), maxQp);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(fectype), fectype);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(iFecPrecent), iFecPrecent);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(spFecPrecent), spFecPrecent);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(pFecPrecent), pFecPrecent);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(iMtu), iMtu);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(spMtu), spMtu);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(pMtu), pMtu);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(iFecMinPkg), iFecMinPkg);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(spFecMinPkg), spFecMinPkg);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(pFecMinPkg), pFecMinPkg);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(iFecMinSize), iFecMinSize);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(spFecMinSize), spFecMinSize);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(pFecMinSize), pFecMinSize);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(gopType), gopType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(gop), gop);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(encMode), encMode);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(hw), hw);
			return szRet;
		}

		uint32 width;			///< 视频宽
		uint32 height;			///< 视频高
		uint32 fps;				///< 帧率
		uint32 bitrate;			///< 码率
		uint32 encodeType;		///<视频流控下发参数编码类型
		uint32 minQp;			///<视频流控下发最小质量
		uint32 maxQp;			///<视频流控下发最大质量
		uint32 fectype;			///<视频流控下发参数fec类型
		uint32 iFecPrecent;		///<视频流控下发i帧fec
		uint32 spFecPrecent;	///<视频流控下发sp帧fec
		uint32 pFecPrecent;		///<视频流控下发p帧fec
		uint32 iMtu;			///<视频流控下发参数I帧mtu
		uint32 spMtu;			///<视频流控下发参数sp帧mtu
		uint32 pMtu;			///<视频流控下发参数p帧mtu
		uint32 iFecMinPkg;		///<视频流控下发参数i帧最小包
		uint32 spFecMinPkg;		///<视频流控下发参数sp帧最小包
		uint32 pFecMinPkg;		///<视频流控下发参数p帧最小包
		uint32 iFecMinSize;		///<视频流控下发参数i帧最小包大小
		uint32 spFecMinSize;	///<视频流控下发参数sp帧最小包大小
		uint32 pFecMinSize;		///<视频流控下发参数p帧最小包大小
		uint32 gopType;			///<视频流控下发参数gop类型
		uint32 gop;				///<视频流控下发参数gop
		uint32 encMode;			///<视频流控下发编码模式
		uint32 hw;				///< 0:不启用硬件加速；1:启用硬件加速
	};

	/**
	@brief 音频采集参数
	*/
	struct iLiveAudioCaptureParam
	{
		iLiveAudioCaptureParam():sampleRate(0),channelCount(0){}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(sampleRate), sampleRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(channelCount), channelCount);
			return szRet;
		}

		uint32 sampleRate;		///< 采样率
		uint32 channelCount;	///< 通道数，1表示单声道(mono)，2表示立体声(stereo)
	};

	/**
	@brief 音频编码相关参数
	*/
	struct iLiveAudioEncodeParam
	{
		iLiveAudioEncodeParam():encodeType(0), encodeBitrate(0), vad(0){}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(encodeType), encodeType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(encodeBitrate), encodeBitrate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(vad), vad);
			return szRet;
		}

		uint32	encodeType;		///< 音频编码类型
		uint32	encodeBitrate;	///< 音频编码码率
		uint32	vad;			///< 音频编码vad参数
	};

	/**
	@brief 音频发送参数
	*/
	struct iLiveAudioSendParam
	{
		iLiveAudioSendParam():lossRate(0), FEC(0), jitter(0), sendBr(0), sendBrUdt(0){}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRate), lossRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(FEC), FEC);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(jitter), jitter);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(sendBr), sendBr);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(sendBrUdt), sendBrUdt);
			return szRet;
		}

		uint32	lossRate;		///< 音频发送丢包率
		uint32	FEC;			///< 音频发送FEC
		uint32	jitter;			///< 音频发送抖动
		uint32	sendBr;			///< 音频发送发送码率
		uint32	sendBrUdt;		///< 音频发送发送码率+header
	};

	/**
	@brief 音频解码相关参数
	*/
	struct iLiveAudioDecodeParam
	{
		iLiveAudioDecodeParam():decodeType(0),sampleRate(0),channelCount(0){}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %s\n", pre.c_str(), NAME(userId), userId.c_str());
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(decodeType), decodeType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(sampleRate), sampleRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(channelCount), channelCount);
			return szRet;
		}

		String userId;       ///< 音频解码用户
		uint32 decodeType;   ///< 音频解码类型
		uint32 sampleRate;   ///< 音频编码采样率
		uint32 channelCount; ///< 通道数，1表示单声道(mono)，2表示立体声(stereo)
	};
	
	/**
	@brief 音频接收参数
	*/
	struct iLiveAudioRecvParam
	{
		iLiveAudioRecvParam():playDelay(0), lossRate(0), recvBr(0){}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(playDelay), playDelay);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(lossRate), lossRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(recvBr), recvBr);
			return szRet;
		}

		uint32 playDelay;	///< 音频接收播放时延
		uint32 lossRate;	///< 音频接收丢包率
		uint32 recvBr;		///< 音频Receive码率
	};

	/**
	@brief 音频下发调控参数,与在后台Spear上配置的参数相关
	*/
	struct iLiveAudioQosParam
	{
		iLiveAudioQosParam()
			:sampleRate(0)
			,channelCount(0)
			,codecType(0)
			,bitrate(0)
			,aecEnable(0)
			,agcEnable(0)
			,fec(0)
			,vad(0)
			,packDuration(0)
			,recn(0)
			,recm(0)
			,audioMtu(0)
			,jitterMinDelay(0)
			,jitterMinMaxDelay(0)
			,jitterMaxMaxDelay(0)
			,jitterDropScale(0)
		{
		}
		
		/**
		@brief 将此参数结果转换为String，方便打印输出
		@param [in] pre 输出每行的前缀;
		@return 输出的String
		*/
		String getInfoString(const String& pre) const
		{
			String szRet;
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(sampleRate), sampleRate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(channelCount), channelCount);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(codecType), codecType);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(bitrate), bitrate);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(aecEnable), aecEnable);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(agcEnable), agcEnable);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(fec), fec);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(vad), vad);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(packDuration), packDuration);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(recn), recn);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(recm), recm);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(audioMtu), audioMtu);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(jitterMinDelay), jitterMinDelay);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(jitterMinMaxDelay), jitterMinMaxDelay);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(jitterMaxMaxDelay), jitterMaxMaxDelay);
			szRet += String::Format("%s%s: %u\n", pre.c_str(), NAME(jitterDropScale), jitterDropScale);
			return szRet;
		}

		uint32 sampleRate;             ///< 采样率
		uint32 channelCount;           ///< 通道数，1表示单声道(mono)，2表示立体声(stereo)
		uint32 codecType;              ///< 编码类型
		uint32 bitrate;                ///< 码率
		uint8  aecEnable;              ///< AEC功能是否开启
		uint8  agcEnable;              ///< AGC功能是否开启
		uint32 fec;                    ///< 音频流控下发fec
		uint32 vad;                    ///< 音频流控下发vad
		uint32 packDuration;          ///< 音频流控下发pack
		uint32 recn;                   ///< 音频流控下发recn
		uint32 recm;                   ///< 音频流控下发recm
		uint32 audioMtu;              ///< 音频流控下发mtu
		uint32 jitterMinDelay;       ///< Jitter的最小延时，单位毫秒
		uint32 jitterMinMaxDelay;   ///< Jitter最大延时的最小阀值
		uint32 jitterMaxMaxDelay;   ///< Jitter最大延时的最大阀值
		uint32 jitterDropScale;      ///< Jitter最大延时的损失比例，百分比eg:10%为10,50%为50
	};

	/**
	@brief 房间直播质量相关的参数
	*/
	struct iLiveRoomStatParam
	{
		iLiveRoomStatParam()
			: tickCountBegin(0)
			, tickCountEnd(0)
			, avsdkVersion("")
			, exeCpuRate(0)
			, sysCpuRate(0)
			, isAnchor(false)
			, audioCategory(0)
		{
		}

		/**
		@brief 将此参数结果转换为String，方便打印输出
		@return 输出的String
		*/
		String getInfoString() const
		{
			String szRet;

			szRet += String::Format("%s: %llu\n", NAME(tickCountBegin), tickCountBegin);
			szRet += String::Format("%s: %llu\n", NAME(tickCountEnd), tickCountEnd);

			szRet += String::Format("%s: %s\n", NAME(avsdkVersion), avsdkVersion.c_str());
			szRet += String::Format("%s: %u\n", NAME(exeCpuRate), exeCpuRate);
			szRet += String::Format("%s: %u\n", NAME(sysCpuRate), sysCpuRate);
			
			szRet += "networkParams:\n";
			szRet += networkParams.getInfoString("   ");
			
			szRet += "videoCaptureParam:\n";
			szRet += videoCaptureParam.getInfoString("   ");
			
			szRet += String::Format( "%s: %d\n", NAME(videoEncodeParams.size), videoEncodeParams.size() );
			for (int i=0; i<videoEncodeParams.size(); ++i)
			{
				szRet += String::Format("videoEncodeParams[%d]:\n", i);
				szRet += videoEncodeParams[i].getInfoString("   ");
			}

			szRet += "videoSendParam:\n";
			szRet += videoSendParam.getInfoString("   ");
			
			szRet += String::Format( "%s: %d\n", NAME(videoDecodeParams.size), videoDecodeParams.size() );
			for (int i=0; i<videoDecodeParams.size(); ++i)
			{
				szRet += String::Format("videoDecodeParams[%d]:\n", i);
				szRet += videoDecodeParams[i].getInfoString("   ");
			}

			szRet += String::Format( "%s: %d\n", NAME(videoRecvParams.size), videoRecvParams.size() );
			for (int i=0; i<videoRecvParams.size(); ++i)
			{
				szRet += String::Format("videoRecvParams[%d]:\n", i);
				szRet += videoRecvParams[i].getInfoString("   ");
			}

			szRet += String::Format("%s: %d\n", NAME(isAnchor), isAnchor);
			
			szRet += "videoMainQosParam:\n";
			szRet += videoMainQosParam.getInfoString("   ");

			szRet += "videoAuxQosParam:\n";
			szRet += videoAuxQosParam.getInfoString("   ");

			szRet += "audioCaptureParam:\n";
			szRet += audioCaptureParam.getInfoString("   ");
			
			szRet += "audioEncodeParams:\n";
			szRet += audioEncodeParams.getInfoString("   ");

			szRet += "audioSendParam:\n";
			szRet += audioSendParam.getInfoString("   ");
			
			szRet += String::Format( "%s: %d\n", NAME(audioDecodeParams.size), audioDecodeParams.size() );
			for (int i=0; i<audioDecodeParams.size(); ++i)
			{
				szRet += String::Format("audioDecodeParams[%d]:\n", i);
				szRet += audioDecodeParams[i].getInfoString("   ");
			}

			szRet += "audioRecvParam:\n";
			szRet += audioRecvParam.getInfoString("   ");
			
			szRet += "audioQosParam:\n";
			szRet += audioQosParam.getInfoString("   ");
			
			szRet += String::Format("%s: %u\n", NAME(audioCategory), audioCategory);
			
			return szRet;
		}

		uint64							tickCountBegin;		///< 统计开始时时间点，使用本地TickCount
		uint64							tickCountEnd;		///< 统计结束的时间点，使用本地TickCount

		String							avsdkVersion;		///< avsdk版本号
		uint16							exeCpuRate;			///< 应用CPU使用率×10000(例如：3456对应于34.56%)
		uint16							sysCpuRate;			///< 系统CPU使用率×10000(例如：3456对应于34.56%)
		
		iLiveNetworkStatParam			networkParams;		///<  网络层相关的统计参数

		iLiveVideoCaptureParam			videoCaptureParam;	///< 视频采集参数			
		Vector<iLiveVideoEncodeParam>	videoEncodeParams;	///< 视频编码参数
		iLiveVideoSendParam				videoSendParam;		///< 视频发送参数

		Vector<iLiveVideoDecodeParam>	videoDecodeParams;	///< 视频解码参数
		Vector<iLiveVideoRecvParam>		videoRecvParams;	///< 视频接收参数
		bool							isAnchor;			///< 是否为主播(只要有视频上行就认为是主播)

		iLiveVideoQosParam				videoMainQosParam;	///< 主路视频流控下发参数
		iLiveVideoQosParam				videoAuxQosParam;	///< 辅路视频流控下发参数

		iLiveAudioCaptureParam			audioCaptureParam;	///< 音频采集信息
		iLiveAudioEncodeParam			audioEncodeParams;	///< 音频编码参数(此参数暂时为0，后续会修正)
		iLiveAudioSendParam				audioSendParam;		///< 音频发送信息

		Vector<iLiveAudioDecodeParam>	audioDecodeParams;	///< 音频解码参数(此参数暂时为0，后续会修正)
		iLiveAudioRecvParam				audioRecvParam;		///< 音频接收信息
		iLiveAudioQosParam				audioQosParam;		///< 音频流控下发参数
		uint32							audioCategory;		///< 音频场景
	};
	
	/**
	@brief 每个IP对应的测速结果
	*/
	struct iLiveSpeedTestResult
	{
		uint32 			access_ip;		///< 接口机IP
		uint32 			access_port;	///< 接口机端口
		uint32 			clientip;		///< 客户端IP
		uint32			test_cnt;		///< 此测速包个数
		uint32			test_pkg_size;	///< 测速包大小
		uint32			avg_rtt;		///< 平均往返时延
		uint32			max_rtt;		///< 最大往返时延
		uint32			min_rtt;		///< 最小往返时延
		uint32			rtt0_50;		///< 0-50ms rtt区间个数
		uint32			rtt50_100;		///< 50-100ms rtt区间个数
		uint32			rtt100_200;		///< 100-200ms rtt区间个数
		uint32			rtt200_300;		///< 200-300ms rtt区间个数
		uint32			rtt300_700;		///< 300-700ms rtt区间个数
		uint32			rtt700_1000;	///< 700-1000ms rtt区间个数
		uint32			rtt1000;		///< 1000ms以上 rtt区间个数
		uint32			jitter0_20;		///< 网络抖动0-20ms区间个数
		uint32			jitter20_50;	///< 网络抖动20-50ms区间个数
		uint32			jitter50_100;	///< 网络抖动50-100ms区间个数
		uint32			jitter100_200;	///< 网络抖动100-200ms区间个数
		uint32			jitter200_300;	///< 网络抖动200-300ms区间个数
		uint32			jitter300_500;	///< 网络抖动300-500ms区间个数
		uint32			jitter500_800;	///< 网络抖动500-800ms区间个数
		uint32			jitter800;		///< 网络抖动大于800ms区间个数
		uint32 			t1_uploss;		///< 上行丢包率×10000(例如：1111对应于11.11%)
		uint32			t1_dwloss;		///< 下行丢包率×10000(例如：1111对应于11.11%)
		uint32			up_cons_loss0;	///< 上行连续丢包为0的次数
		uint32			up_cons_loss1;	///< 上行连续丢包为1的次数
		uint32			up_cons_loss2;	///< 上行连续丢包为2的次数
		uint32			up_cons_loss3;	///< 上行连续丢包为3的次数
		uint32			up_cons_lossb3;	///< 上行连续丢包大于3的次数
		uint32			dw_cons_loss0;	///< 下行连续丢包为0的次数
		uint32			dw_cons_loss1;	///< 下行连续丢包为1的次数
		uint32			dw_cons_loss2;	///< 下行连续丢包为2的次数
		uint32			dw_cons_loss3;	///< 下行连续丢包为3的次数
		uint32			dw_cons_lossb3;	///< 下行连续丢包大于3的次数
		uint32			up_disorder;	///< 上行乱序次数
		uint32			dw_disorder;	///< 下行乱序次数
		Vector<uint32>	up_seq;			///< 上行包序列
		Vector<uint32>	dw_seq;			///< 下行包序列
	};

	/**
	@brief 测速接口回调参数类型
	*/
	struct iLiveSpeedTestResultReport
	{
		uint64			test_id;		///< 测速id
		uint64			test_time;		///< 测试时间戳(s)
		uint64			roomid;			///< 测试房间号
		uint32			client_type;	///< 客户端类型 0:unknown  1:pc  2:android  3:iphone  4:ipad
		uint32			net_type;		///< 网络类型(始终为1): 0:无网络  1:wifi  2:2G  3:3G  4:4G  10:WAP  255:unknow
		String			net_name;		///< 运营商名字，能获取就上报,utf8(无效)
		String			wifi_name;		///< wifi ssid，能获取就上报,utf8(无效)
		double			longitude;		///< 经度(无效)
		double			latitude;		///< 纬度(无效)
		uint32			client_ip;		///< 客户端IP
		uint32			call_type;		///< 通话类型，0:纯音频，1:音视频
		uint32			sdkappid;		///< sdkappid
		uint32			test_type;		///< 测试类型: 0x1:udp  0x2:tcp  0x4:http get  0x8:http post  0x10:trace route
		Vector<iLiveSpeedTestResult>	results;	///< 测试结果列表
		uint32			net_changecnt;	///< 测速过程中网络变化次数(无效)
		uint32			access_ip;		///< 本次通话选择的accessip(无效)
		uint32			access_port;	///< 本次通话选择的access port(无效)
	};

	/**
	@brief 本地mp4录制委托基类。业务侧需要实现该基类来处理录制事件。
	*/
	struct iLiveLocalRecordDelegate
	{
		virtual ~iLiveLocalRecordDelegate(){}

		/**
        @brief 录制过程中发生错误的回调通知。
        @details 开启录制之后，在录制过程中发生错误，即回调这个方法, 并且自动停止录制。
        */
		virtual void OnError(int32 result, const String& errInf) = 0;

		/**
        @brief 保存单个录制MP4文件时的回调通知, 和是否停止录制MP4无关。
        @param [in] duration mp4文件时长，单位秒。单个MP4文件最大时长为1小时。
        @param [in] width mp4文件视频图像宽度。
        @param [in] height mp4文件视频图像高度。
        @param [in] filePath mp4文件路径。
        @details 开启录制之后，录制过程中完成一个MP4文件的录制，即回调这个方法。
                 录制过程中有可能产生多个MP4文件, 即录制过程中可能会有多次OnRecorded回调。
                 产生多个MP4文件是必要的, 原因是:<br/>
                 1. SDK由于性能考虑，没有进行二次编码，而是直接将通话中的上行码流dump下来转成MP4。<br/>
                 2. 由于通话过程中切角色, 视频参数有可能会变化，导致h264 sps pps发生改变(主要为视频分辨率改变)，从而必须重新保存。<br/>
                 3. 特别的，由于通话过程中，屏幕分享区域变化，导致h264 sps pps发生改变(主要为视频分辨率改变)，从而必须重新保存。<br/>
                 4. 考虑到码流转换mp4的时间和空间效率问题，单个文件最大时长为1小时，超过则重新保存。<br/>
                 5. 摄像头和屏幕分享会同时录制保存，也会分开录制保存，摄像头MP4文件名以"main"开头，屏幕分享MP4文件名以"sub"开头<br/>
                 6. 音频会固定转码为标准ACC (sample rate: 48000, channel: 2, bitrate: 64000),不会造成重新生成MP4的问题。<br/>
                 所以，建议业务侧尽量使用固定分辨率，固定码率等参数，避免mp4文件保存个数过多。
        */
		virtual void OnRecorded(uint32 duration, uint32 width, uint32 height, const String& filePath) = 0;
	};

	/**
	@brief 音频数据帧格式
	*/
	struct iLiveAudioFrameDesc
	{
		iLiveAudioFrameDesc()
			: sampleRate(0)
			, channelNum(0)
			, bits(0)
			, srcType(AUDIO_SRC_TYPE_NONE)
		{
		}

		uint32			sampleRate;	///< 采样率，单位：赫兹(Hz)
		uint32			channelNum;	///< 通道数，1表示单声道(mono)，2表示立体声(stereo)
		uint32			bits;		///< 音频数据位宽。SDK1.6版本暂固定为16。
		E_AudioSrcType	srcType;	///< 音频源类型。
	};

	/**
	@brief 音频数据帧
	*/
	struct iLiveAudioFrame
	{
		iLiveAudioFrame()
			: dataSize(0)
			, data(NULL)
			, timeStamp(0)
		{
		}

		String				identifier; ///< 音频帧所属的房间成员id。
		iLiveAudioFrameDesc	desc;		///< 音频帧描述。
		uint32				dataSize;	///< 音频帧的数据缓冲区大小，单位：字节。
		uint8*				data;		///< 音频帧的数据缓冲区，SDK内部会管理缓冲区的分配和释放。
		uint64				timeStamp;	///< 音频帧的时间戳，SDK内部会自动填写好，utc时间，0为无效值。
	};

	/**
	@brief 自定义数据结构
	*/
	struct sCustomData
	{
		sCustomData()
			: dataSize(0)
			, data(NULL)
			, pushMode(E_CUSTOMDATA_WITH_AVDATA)
		{
		}

		String				id;			///< 调用fillCustomData时，不需要填写，sdk会自动填充
		uint32				dataSize;
		uint8*				data; 
		E_CustomDataMode	pushMode;
	};

	/**
	@brief 接口封装抽象接口
	*/
	struct iLive
	{
		/**
		@brief 获取版本号
		@return 版本号
		*/
		virtual const char *getVersion() = 0;
		/**
		@brief 初始化
		@details 使用ilive各项功能前必须先初始化
		@param [in] appId 在腾讯云申请的sdkappid
		@param [in] accountType 在腾讯云申请的accountType
		@param [in] imSupport 是否需要聊天等即时通讯功能
		@param [in] testEnv 是否进入测试环境
		@return 返回操作结果,成功则返回NO_ERR
		*/
		virtual int init(const int appId, const int accountType, bool imSupport = true, bool testEnv = false) = 0;
		/**
		@brief 释放
		@details 使用完ilive后需要释放资源。
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@remark 此函数会清理7天前的所有日志文件(iLiveSDK、AVSDK、IMSDK)。
		*/
		virtual void release(iLiveSucCallback suc = NULL, iLiveErrCallback err = NULL, void* data = NULL) = 0;
		/**
		@brief 是否已初始化
		@return 是否已初始化
		*/
		virtual bool isInited() = 0;

		/**
		@brief 设置通道类型
		@details 设置SDK内部通道。
		老用户(2018年07月09日前接入的用户)需要调用本接口设置为E_ChannelIMSDK，才能和旧版本(1.9.0.0之前的版本)互通;
		默认通道为E_ChannelIMRestAPI,此通道下,在进房间时，必须带上tls加密版本的privateMapKey(进房时参数iLiveRoomOption的privateMapKey),
		privateMapKey生成规则参考: https://cloud.tencent.com/document/product/454/16914 文档中privateMapKey的计算方法;
		@param [in] mode 通道类型
		@param [in] host 自定义域名(目前此参数无效);
		@note 必须在登录之前调用，否则无效。
		*/
		virtual void setChannelMode(E_ChannelMode mode, const String& host = "") = 0;
		/**
		@brief 设置被踢下线监听
		@details 每个账号不能同时登录多台设备，当其他设备登录相同账号时会收到这个通知
		@param [in] cb 回调函数
		*/
		virtual void setForceOfflineCallback(ForceOfflineCallback cb) = 0;
		/**
		@brief 设置消息监听
		@param [in] cb 回调函数
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@note 当前房间所用群组之外的群消息会被sdk过滤掉;
		*/
		virtual void setMessageCallBack( iLiveMessageCallback cb, void* data ) = 0;
		/**
		@brief 设置网络连接监听
		@param [in] onConn 联网成功回调
		@param [in] onDisconn 断连回调
		@note 可以在联网成功回调后再进行登录等其他业务逻辑(此接口已废弃，不再推荐使用)
		*/
		Deprecated
		virtual void setConnListener( onNetworkCallback onConn, onNetworkCallback onDisconn ) = 0;

		/**
		@brief 设置预处理函数指针。
		@details 在视频被传输出去前，用户可以在此回调函数中做预处理;
		@param [in] pPreTreatmentFun 预处理函数指针。
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@remark 预处理函数耗时不要过久，最好控制在10ms内; 同时不能改变图像大小和图像颜色格式。
		@note SDK将在子线程中执行此回调.
		*/
		virtual void setPreTreatmentFun( iLivePreTreatmentCallback pPreTreatmentFun, void* data ) = 0;
		/**
		@brief 设置本地视频回调函数指针。
		@param [in] pLocalVideoCB 本地视频回调函数指针
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@remark 业务侧实现该回调函数，SDK向该回调函数传入本地视频相关数据，业务侧拿到数据后进行渲染显示
		*/
		virtual void setLocalVideoCallBack( iLivePreviewCallback pLocalVideoCB, void* data ) = 0;
		/**
		@brief 设置远程视频回调函数指针。
		@param [in] pRemoteVideoCB 远程视频回调函数指针
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@remark 业务侧实现该回调函数，SDK向该回调函数传入远程视频相关数据，业务侧拿到数据后进行渲染显示
		*/
		virtual void setRemoteVideoCallBack( iLivePreviewCallback pRemoteVideoCB, void* data ) = 0;
		/**
		@brief 设置设备操作回调函数指针。
		@details 摄像头、自定义采集、麦克风、扬声器、屏幕分享、系统声音采集、文件播放等设备操作结果，会通过此回调通知给业务层。
		@param [in] cb 设备操作的回调函数指针.
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		*/
		virtual	void setDeviceOperationCallback( iLiveDeviceOperationCallback cb, void* data ) = 0;
		/**
		@brief 设置设备插拔监听函数;
		@details 当摄像头、麦克风、扬声器设备的接入及拔出时，sdk会通过此回调通知给业务侧，收到此回调需要更新设备列表;参见iLiveDeviceDetectListener定义。
		@note 当摄像头、麦克风、扬声器等正在使用中时,设备被拔出，收到此回调前，还会收到相应设备关闭的回调;
		*/
		virtual void setDeviceDetectCallback( iLiveDeviceDetectListener cb, void* data ) = 0;
		/**
		@brief 设置视频回调的颜色格式;
		@details 设置视频回调(setLocalVideoCallBack()和setRemoteVideoCallBack()接口设置的回调)的视频帧颜色格式;
		@param [in] fmt 颜色格式;
		@return 操作结果，true成功，false失败;
		@note 需要在进入房间\开启设备测试之前设置,否则返回false;
		*/
		virtual bool setVideoColorFormat(E_ColorFormat fmt) = 0;

		/**
		@brief 设置接收自定义数据的回调函数
		@param [in] cb 回调函数 
		*/
		virtual void setCustomDataCallback(iLiveCustomDataCallback cb) = 0;

		/**
		@brief 登录
		@param [in] userId 用户id
		@param [in] userSig 用户签名
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@param [in] spearCfg 默认spear配置(拉不到网络配置时生效,一般适用于海外);使用详情见https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/doc/defaultSpearCfg.md
		@remark 设置默认spear配置失败时，不会回调登录失败，只会在ilivesdk日志中打印出相应错误信息;
		*/
		virtual void login(const char *userId, const char *userSig, iLiveSucCallback suc, iLiveErrCallback err, void* data, const char* spearCfg = "") = 0;
		/**
		@brief 登出
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		*/
		virtual void logout(iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief 是否已登录
		@return 是否已登录
		*/
		virtual bool isLogin() = 0;

		/**
		@brief 开始设备测试
		@details 开始设备测试后，可以在登录之后，进入房间之前，对打开摄像头、麦克风、扬声器，进行设备测试;
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@param [in] preWidth 设置打开摄像头测试时,视频帧的宽度(此参数已废弃，sdk使用摄像头支持默认宽度);
		@param [in] preHeight 设置打开摄像头测试时,视频帧的高度(此参数已废弃，sdk使用摄像头支持默认高度);
		@remark 设备测试时，美颜、美白功能可用;
		*/
		virtual void startDeviceTest(iLiveSucCallback suc, iLiveErrCallback err, void* data, int preWidth = 640, int preHeight = 480) = 0;
		/**
		@brief 停止设备测试
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@remark 在开始设备测试后，需要停止设备测试，才能进入房间，否则会返回相应错误码;
		*/
		virtual void stopDeviceTest(iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;

		/**
		@brief 是否处于设备测试状态
		@return 是否处于设备测试状态
		*/
		virtual bool isInDeviceTest() = 0;
		
		/**
		@brief 创建直播房间
		@param [in] roomOption 房间配置
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		*/
		virtual void createRoom(const iLiveRoomOption &roomOption, iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief 加入直播房间
		@param [in] roomOption 房间配置
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		*/
		virtual void joinRoom(const iLiveRoomOption& roomOption, iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief 切换房间
		@param [in] roomId 要切换到的房间id
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@remark 1、只有在房间内才能切换房间; 2、房间拥有者(主播)不能切换房间;
		*/
		virtual void switchRoom(uint32 roomId, iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief 退出直播房间
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@param [in] bQuitIM 退出房间时，是否解散群(房间拥有者)\退出群(房间加入者);
		*/
		virtual void quitRoom(iLiveSucCallback suc, iLiveErrCallback err, void* data, bool bQuitIM = true) = 0;
		/**
		@brief 是否在房间中
		@return 是否在房间中
		*/
		virtual bool isEnterRoom() = 0;

		/**
		@brief 请求一个或多个成员的视频画面
		@param [in] streams 请求的流
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		@note 
		1、requestStream操作必须等待异步回调函数执行结束后，才能进行新的requestStream操作;<br/>
		2、requestStream、cancelStream和cancelAllStream不能并发执行，即同一时刻只能进行一种操作;
		*/
		virtual void requestStream(const Vector<AVStream> &streams, iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief  取消指定用户的画面。
		@param [in] streams 取消的流
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		@note 
		1、cancelStream操作必须等待异步回调函数执行结束后，才能进行新的cancelStream操作;<br/>
		2、requestStream、cancelStream和cancelAllStream不能并发执行，即同一时刻只能进行一种操作;
		*/
		virtual void cancelStream(const Vector<AVStream> &streams, iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief 取消所有请求的视频画面。
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		@note requestStream、cancelStream和cancelAllStream不能并发执行，即同一时刻只能进行一种操作;
		*/
		virtual void cancelAllStream(iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;
		/**
		@brief 发C2C消息
		@param [in] dstUser 接收方id
		@param [in] message 要发送的消息
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		*/
 		virtual void sendC2CMessage( const char *dstUser, const Message	&message, iLiveSucCallback suc, iLiveErrCallback err, void* data ) = 0;
 		/**
		@brief 发群消息
		@param [in] message 要发送的消息
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		@note 此处发送群消息，仅限于在当前直播间中发送群消息。
		*/
		virtual void sendGroupMessage( const Message &message, iLiveSucCallback suc, iLiveErrCallback err, void* data ) = 0;

		/**
		@brief 获取本地消息
		@param [in] count 要获取的消息条数
		@param [in] user 会话的对象id
		@param [in] fromStart 从头开始拉取
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		*/
		virtual void getLocalC2CMessage( int count, const char *user, bool fromStart, Type<Vector<Message>>::iLiveValueSuccCallback suc, iLiveErrCallback err, void* data ) = 0;

		/**
		@brief 开始推流
		@param [in] pushOption 推流参数
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		*/
		virtual void startPushStream( const PushStreamOption& pushOption, Type<PushStreamRsp&>::iLiveValueSuccCallback suc, iLiveErrCallback err, void* data ) = 0;
		/**
		@brief 结束推流
		@param [in] channelId 频道id(在推流成功的的回调中返回的频道id)
		@param [in] pushDataType 要停止推流的数据类型
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		*/
		virtual void stopPushStream( uint64 channelId, E_PushDataType pushDataType, iLiveSucCallback suc, iLiveErrCallback err, void* data ) = 0;

		/**
		@brief 开始录制。
		@param [in] recordOption 录制配置选项。
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		*/
		virtual void startRecord(const RecordOption& recordOption, iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;

		/**
		@brief 停止录制。
		@param [in] recordDataType 要停止录制的数据类型
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		@remark 停止录制成功回调，返回录制视频文件的ID列表; 业务侧开起自动录制时，将返回空列表，用户可直接到后台查询。
		*/
		virtual void stopRecord(E_RecordDataType recordDataType, Type<Vector<String>&>::iLiveValueSuccCallback suc, iLiveErrCallback err, void* data) = 0;

		/**
		@brief 结束推流
		@param [in] role 角色
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		*/
		virtual void changeRole( const char *role, iLiveSucCallback suc, iLiveErrCallback err, void* data ) = 0;		 
		/**
		@brief 设置美颜程度
		@param [in] grade 美颜程度参数。grade取值范围在0-9之间，0表示美颜关闭
		@return 返回值为NO_ERR时表示成功，否则表示失败
		@note 美颜、美白功能只对本地摄像画面有效，SDK不会对自定义采集画面美颜、美白处理;
		*/
		virtual int setSkinSmoothGrade(int grade) = 0;
		/**
		@brief 设置美白程度
		@param [in] grade 美白程度参数。grade取值范围在0-9之间，0表示美白关闭
		@return 返回值为NO_ERR时表示成功，否则表示失败
		@note 美颜、美白功能只对本地摄像画面有效，SDK不会对自定义采集画面美颜、美白处理;
		*/
		virtual int setSkinWhitenessGrade(int grade) = 0;
		/**
		@brief 设置水印
		@param [in] filePath 水印文件路径;支持 BMP, GIF, JPEG, PNG, TIFF, Exif, WMF, and EMF 格式;如果传 NULL，则代表去掉水印;
		@param [in] xOffset  左上角x轴偏移,取值范围[0,1]
		@param [in] yOffset  左上角y轴偏移,取值范围[0,1]
		@param [in] fWidthRatio 水印占x轴的比例,取值范围[0,1]
		@return 返回值为NO_ERR时表示成功，否则表示失败
		@note 此接口设置的水印,只对本地摄像\屏幕分享画面有效，SDK不会对自定义采集画面设置水印;
		*/
		virtual int setWaterMark(const String& filePath, float xOffset, float yOffset, float fWidthRatio) = 0;

		/**
		@brief 获取可用摄像头列表
		@param [out] cameraList 传回获取到的摄像头列表,第一个(索引0)为系统默认设备;
		@return 操作结果,NO_ERR表示无错误;如果没有可用摄像头,返回AV_ERR_DEVICE_NOT_EXIST错误码(错误码见github上的错误码表);
		*/
		virtual int getCameraList( Vector< Pair<String/*id*/, String/*name*/> >& cameraList ) = 0;
		/**
		@brief 获取可用麦克风列表
		@param [out] micList 传回获取到的麦克风列表,第一个(索引0)为系统默认设备;
		@return 操作结果,NO_ERR表示无错误;如果没有可用麦克风,返回AV_ERR_DEVICE_NOT_EXIST错误码(错误码见github上的错误码表);
		*/
		virtual int getMicList( Vector< Pair<String/*id*/, String/*name*/> >& micList ) = 0;
		/**
		@brief 获取可用的扬声器列表
		@param [out] playerList 传回获取到的扬声器列表,第一个(索引0)为系统默认设备;
		@return 操作结果,NO_ERR表示无错误;如果没有可用扬声器,返回AV_ERR_DEVICE_NOT_EXIST错误码(错误码见github上的错误码表);
		*/
		virtual int getPlayerList( Vector< Pair<String/*id*/, String/*name*/> >& playerList ) = 0;
		/**
		@brief 获取任务栏打开的所有主窗口。
		@param [out] wndList 传回获取到的窗口列表(会过滤掉不可见窗口\无标题窗口\最小化窗状态的窗口)。
		@return 操作结果,NO_ERR表示无错误;如果没有可分享窗口,返回AV_ERR_DEVICE_NOT_EXIST错误码(错误码见github上的错误码表);
		@remark 用户可以调用此接口获取可以进行屏幕分享的窗口句柄列表,也可以自己获取;
		*/
		virtual int getWndList( Vector< Pair<HWND/*id*/, String/*name*/> >& wndList ) = 0;
		/**
		@brief 打开摄像头
		@param [in] szCameraId 通过getCameraList()函数获取的摄像头列表中的某个摄像头id
		@note 
		1、打开摄像头成功，如果用户有上传视频权限，便会自动开始上传摄像头视频;<br/>
		2、打开摄像头操作和打开自定义采集是互斥的操作;如果同时打开，会返回错误AV_ERR_EXCLUSIVE_OPERATION(错误码见github上的错误码表)
		*/
		virtual void openCamera(const String& szCameraId) = 0;
		/**
		@brief 关闭当前打开的摄像头
		*/
		virtual void closeCamera() = 0;
		/**
		@brief 打开主路自定义采集
		@note 
		1、打开自定义采集成功，如果用户有上传视频权限，用户通过fillExternalCaptureFrame()填入的每一帧画面将会通过sdk上传;<br/>
		2、打开摄像头操作和打开主路自定义采集是互斥的操作;如果同时打开，会返回错误AV_ERR_EXCLUSIVE_OPERATION(错误码见github上的错误码表);
		*/
		virtual void openExternalCapture() = 0;
		/**
		@brief 关闭主路自定义采集
		*/
		virtual void closeExternalCapture() = 0;
		/**
		@brief 外部输入主路视频数据接口。
		@return 操作结果，NO_ERR表示无错误;
		@note 
		1、目前sdk支持的VideoFrame格式只有COLOR_FORMAT_RGB24和COLOR_FORMAT_I420,如果传入的视频帧不是此两种格式，将返回ERR_NOT_SUPPORT;<br/>
		2、视频帧只能是这些辨率(176*144、192*144、320*240、480*360、640*368、640*480、960*540、1280*720、144*176、144*192、240*320、360*480、368*640、480*640、540*960、720*1280),否则返回AV_ERR_INVALID_ARGUMENT(错误码见github上的错误码表);<br/>
		3、最好按照后台SPEAR配置的视频帧率进行填充视频数据;<br/>
		4、传入的视频帧分辨率如果大于控制台SPEAR引擎配置的值，视频将会被裁剪到SPEAR配置的分辨率(主播端预览画面和观众端画面大小将会不一致);<br/>
		   如果小于控制台配置的值，将会按照传入的视频帧大小传入到观众端(即不会被放大到控制台配置的值);<br/>
		5、传入的LiveVideoFrame需要业务侧管理其生命周期，即用户需要注意frame.data字段的释放;
		*/
		virtual int fillExternalCaptureFrame( const LiveVideoFrame &frame ) = 0;
		/**
		@brief 打开辅路自定义采集
		@note 
		1、打开自定义采集成功，如果用户有上传视频权限，用户通过fillExternalCaptureFrame()填入的每一帧画面将会通过sdk上传;<br/>
		2、屏幕分享和文件播放走辅路，所以，打开辅路自定义采集和屏幕分享、文件播放是互斥的操作;如果同时打开，会返回错误AV_ERR_EXCLUSIVE_OPERATION(错误码见github上的错误码表);
		*/
		virtual void openExternalCaptureSub() = 0;
		/**
		@brief 关闭辅路自定义采集
		*/
		virtual void closeExternalCaptureSub() = 0;
		/**
		@brief 外部输入辅路视频数据接口。
		@return 操作结果，NO_ERR表示无错误;
		@note 
		1、目前sdk支持的VideoFrame格式只有COLOR_FORMAT_RGB24和COLOR_FORMAT_I420,如果传入的视频帧不是此两种格式，将返回ERR_NOT_SUPPORT;<br/>
		2、传入的LiveVideoFrame需要业务侧管理其生命周期，即用户需要注意frame.data字段的释放;
		*/
		virtual int fillExternalCaptureFrameSub( const LiveVideoFrame &frame ) = 0;

		/**
		@brief 打开麦克风。
		@param [in] szMicId 通过getMicList()函数获取的麦克风列表中的某个麦克风id。
		@note 打开麦克风成功，如果用户有上传语音权限，便会自动开始上传麦克风音频。
		*/
		virtual void openMic(const String &szMicId) = 0;
		/**
		@brief 设置麦克风增强。
		@param [in] value 设置麦克风增强,取值范围[0,100].
		@return 操作结果，NO_ERR表示无错误;
		@note 
		1、这里是麦克风增强，不是指麦克风音量,即设置为0，还是会有音频输入;
		2、只有打开了麦克风才能进行设置,否则返回ERR_WRONG_STATE;<br/>
		3、如果后台SPEAR引擎配置打开了agc(麦克风自动增益),设置值太小时，会被自动调整回来;
		*/
		virtual int	setMicVolume(int value) = 0;
		/**
		@brief 获取麦克风增强。
		@return 返回麦克风增强,未打开麦克风则返回0;
		*/
		virtual uint32 getMicVolume() = 0;
		/**
		@brief 关闭当前打开的麦克风。
		*/
		virtual void closeMic() = 0;
		/**
		@brief 获得当前麦克风动态音量。
		@return 返回当前麦克风动态音量,取值范围[0,100]; 如果未打开麦克风，返回0;
		*/
		virtual uint32 getMicDynamicVolume() = 0;
		/**
		@brief 打开扬声器。
		@param [in] szPlayerId 通过getPlayerList()函数获取的扬声器列表中的某个扬声器id。
		@note 打开扬声器成功，如果用户有接收音频权限，便会自动开始播放远端音频。
		*/
		virtual void openPlayer(const String& szPlayerId) = 0;
		/**
		@brief 设置扬声器音量。
		@param [in] value 设置扬声器的目标音量,取值范围[0,100].
		@return 操作结果，NO_ERR表示无错误;
		@note 只有打开了扬声器才能进行设置,否则返回ERR_WRONG_STATE;
		*/
		virtual int setPlayerVolume( uint32 value ) = 0;
		/**
		@brief 获取扬声器音量。
		@return 返回扬声器音量,未打开扬声器则返回0;
		*/
		virtual uint32 getPlayerVolume() = 0;
		/**
		@brief 关闭当前打开的扬声器。
		*/
		virtual void closePlayer() = 0;
		/**
		@brief 获得当前扬声器动态音量。
		@return 返回当前扬声器动态音量,取值范围[0,100];如果未打开扬声器，返回0;
		*/
		virtual uint32 getPlayerDynamicVolume() = 0;
		/**
		@brief 打开屏幕分享(指定窗口)。
		@param [in] hWnd 所要捕获的窗口句柄。如果传入的hWnd不是有效窗口句柄\窗口不可见\窗口处于最小化状态，将会返回ERR_INVALID_PARAM;
		@param [in] fps 捕获帧率,取值范围[1,10]。注意: 此参数暂无意义，sdk会根据网络情况，动态调整fps;
		@note
		屏幕分享和播片功能都是通过辅路流传输，所以屏幕分享和播片互斥使用;
		辅路流被自己占用，设备操作回调中，返回错误码AV_ERR_EXCLUSIVE_OPERATION(错误码见github上的错误码表);
		被房间内其他成员占用，设备操作回调中，返回错误码AV_ERR_RESOURCE_IS_OCCUPIED(错误码见github上的错误码表);
		*/
		virtual void openScreenShare( HWND hWnd, uint32& fps ) = 0;
		/**
		@brief 打开屏幕共享(指定区域)。
		@param [in] left/top/right/bottom 所要捕获屏幕画面的区域的左上角坐标(left, top)和右下角坐标(right, bottom)，它们是以屏幕的左上角坐标为原点的。
		@param [in] fps 捕获帧率，取值范围[1,10];注意: 此参数暂时无意义，sdk会根据网络情况，动态调整fps;
		@note
		屏幕分享和播片功能都是通过辅路流传输，所以屏幕分享和播片互斥使用;
		辅路流被自己占用，设备操作回调中，返回错误码AV_ERR_EXCLUSIVE_OPERATION(错误码见github上的错误码表);
		被房间内其他成员占用，设备操作回调中，返回错误码AV_ERR_RESOURCE_IS_OCCUPIED(错误码见github上的错误码表);
		*/
		virtual void openScreenShare( int32& left, int32& top, int32& right, int32& bottom, uint32& fps ) = 0;
		/**
		@brief 屏幕分享过程中,动态修改屏幕分享的区域。
		@param [in] left/top/right/bottom 所要捕获屏幕画面的区域的左上角坐标(left, top)和右下角坐标(right, bottom)，坐标以屏幕的左上角为原点。
		@return 操作结果，NO_ERR表示无错误。
		@remark 传入的参数可能会经过sdk内部细微的调整，并通过引用方式传回给调用者，实际的分享区域以传回的值为准;
		@note 此接口只有在打开了指定区域的屏幕共享时才有效,其他状态下将会返回ERR_WRONG_STATE错误;
		*/
		virtual int changeScreenShareSize( int32& left, int32& top, int32& right, int32& bottom ) = 0;
		/**
		@brief 关闭屏幕共享。
		@return 操作结果，NO_ERR表示无错误。
		@remark 指定窗口的屏幕分享和指定区域的屏幕分享都调用此接口来关闭.
		*/
		virtual void closeScreenShare() = 0;

		/**
		@brief 打开系统声音采集。
		@details 采集系统声音。
		@param [in] szPlayerPath 播放器地址;如果用户此参数填空或不填，表示采集系统中的所有声音;如果填入exe程序(如:酷狗、QQ音乐)所在路径,将会启动此程序，并只采集此程序的声音;
		@remark 文件播放和系统声音采集不应该同时打开，否则文件播放的声音又会被系统声音采集到，出现重音现象;
		*/
		virtual void openSystemVoiceInput(const String& szPlayerPath = "") = 0;
		/**
		@brief 关闭系统声音采集。
		*/
		virtual void closeSystemVoiceInput() = 0;
		/**
		@brief 设置系统声音采集的音量。
		@param [in] value 设置目标音量,取值范围[0,100].
		@return 操作结果，NO_ERR表示无错误;
		@note 只有打开了系统声音采集才能进行设置,否则返回ERR_WRONG_STATE;
		@remark 如果是采集整个系统声音，此音量表示绝对音量；如果是指定程序的播放，此音量为相对音量,即10为1倍，100为10倍，1为原来的1/10;
		*/
		virtual int	setSystemVoiceInputVolume( uint32 value ) = 0;
		/**
		@brief 获取系统声音采集音量。
		@return 返回系统声音采集音量,未打开则返回0;
		@remark 如果是采集整个系统声音，此音量表示绝对音量；如果是指定程序的播放，此音量为相对音量,即10为1倍，100为10倍，1为原来的1/10;
		*/
		virtual uint32 getSystemVoiceInputVolume() = 0;

		/**
		@brief 打开文件播放。
		@details 开始播放本地音频\视频文件，播放文件前，最好先调用isValidMediaFile()检查文件的可用性。
		@param [in] szMediaFile 文件路径(可以是本地文件路径，也可以是一个网络文件的url);
		@remark
		1、支持的文件类型:<br/>
		*.aac,*.ac3,*.amr,*.ape,*.mp3,*.flac,*.midi,*.wav,*.wma,*.ogg,*.amv,
		*.mkv,*.mod,*.mts,*.ogm,*.f4v,*.flv,*.hlv,*.asf,*.avi,*.wm,*.wmp,*.wmv,
		*.ram,*.rm,*.rmvb,*.rpm,*.rt,*.smi,*.dat,*.m1v,*.m2p,*.m2t,*.m2ts,*.m2v,
		*.mp2v, *.tp,*.tpr,*.ts,*.m4b,*.m4p,*.m4v,*.mp4,*.mpeg4,*.3g2,*.3gp,*.3gp2,
		*.3gpp,*.mov,*.pva,*.dat,*.m1v,*.m2p,*.m2t,*.m2ts,*.m2v,*.mp2v,*.pss,*.pva,
		*.ifo,*.vob,*.divx,*.evo,*.ivm,*.mkv,*.mod,*.mts,*.ogm,*.scm,*.tod,*.vp6,*.webm,*.xlmv。<br/>
		2、目前sdk会对大于1280*720的视频裁剪到1280*720;<br/>
		3、文件播放和系统声音采集不应该同时打开，否则文件播放的声音又会被系统声音采集到，出现重音现象;
		@note
		屏幕分享和播片功能都是通过辅路流传输，所以屏幕分享和播片互斥使用;
		辅路流被自己占用，设备操作回调中，返回错误码AV_ERR_EXCLUSIVE_OPERATION(错误码见github上的错误码表);
		被房间内其他成员占用，设备操作回调中，返回错误码AV_ERR_RESOURCE_IS_OCCUPIED(错误码见github上的错误码表);
		*/
		virtual void openPlayMediaFile( const String& szMediaFile ) = 0;
		/**
		@brief 关闭文件播放。
		*/
		virtual void closePlayMediaFile() = 0;
		/**
		@brief 从头播放文件。
		@return 操作结果，NO_ERR表示无错误。
		@note 只有在处于播放状态下(E_PlayMediaFilePlaying)，此接口才有效，否则返回ERR_WRONG_STATE;
		*/
		virtual int restartMediaFile() = 0;
		/**
		@brief 暂停播放文件。
		@return 操作结果，NO_ERR表示无错误。
		*/
		virtual int pausePlayMediaFile() = 0;
		/**
		@brief 恢复播放文件。
		@return 操作结果，NO_ERR表示无错误。
		*/
		virtual int	resumePlayMediaFile() = 0;
		/**
		@brief 设置播放文件进度。
		@param [in] n64Pos 播放位置(单位: 秒)
		@return 操作结果，NO_ERR表示无错误。
		*/
		virtual int setPlayMediaFilePos(const int64& n64Pos) = 0;
		/**
		@brief 获取播放文件进度。
		@param [out] n64Pos 当前播放位置(单位: 秒)
		@param [out] n64MaxPos 当前所播放文件的总长度(单位: 秒)
		@return 操作结果，NO_ERR表示无错误。
		*/
		virtual int getPlayMediaFilePos(int64& n64Pos, int64& n64MaxPos) = 0;
		/**
		@brief 判断文件是否可用于播放。
		@param [in] szMediaFile 要检查的视频文件.
		@return 是否可用;如果文件不存在，也会返回false;
		*/
		virtual bool isValidMediaFile(const String& szMediaFile) = 0;

		/**
		@brief 设置音视频SDK画面的水印.
		@param [in] waterMarkType 水印类型，参考E_WaterMarkType说明;
		@param [in] argbData 水印的argb格式数据;
		@param [in] width 水印宽度;
		@param [in] height 水印高度;
		@return 操作结果，NO_ERR表示无错误。
		@remark 
		1、只能在登录成功，打开主路视频(摄像头\自定义采集)之前调用此接口。<br/>
		2、为了所有画面都有水印效果，用户Spear上配置的各个分辨率都应该设置相应水印;<br/>
		3、为了性能考虑，设置了水印后，主播自己的预览画面不会显示水印，观众端才会显示水印。<br/>
		4、水印大小限制规则为: 水印宽度不大于画面宽度的1/4,高度不能大于1/6,且水印宽高都必须为2的倍数;<br/>
		5、sdk暂时只支持对主路视频设置水印,不支持对辅路设置水印;
		@todo 此接口限制较多，不推荐用户使用，建议使用setWaterMark接口;
		*/
		Deprecated
		virtual int addWaterMark(E_WaterMarkType waterMarkType, uint8* argbData, uint32 width, uint32 height) = 0;

		/**
		@brief 设置sdk的日志路径
		@return 操作结果，true成功，false失败
		@remark 为避免调用此接口前后日志打印到不同目录下,限制只能在sdk任何接口调用之前调用此接口，否则返回false;
		*/
		virtual bool setLogPath(const String& szLogPath) = 0;

		/**
		@brief 开始测速
		@details 开始测速后，sdk会对几个接口机进行测速，并将测速结果回调给业务侧
		@param [in] calltype 通话类型
		@param [in] purpose 测速目的
		@param [in] suc 成功带值回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针)
		@remark 需要在登录后，才能调用测速接口;
		*/
		virtual void startSpeedTest( E_SPTCallType calltype, E_SPTPurpose purpose, Type<iLiveSpeedTestResultReport&>::iLiveValueSuccCallback suc, iLiveErrCallback err, void* data ) = 0;
		/**
		@brief 取消测速;
		@details 开始测速后，可能需要取消测速任务，此时可以调用此接口
		@param [in] suc 成功回调
		@param [in] err 失败回调
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		*/
		virtual void cancelSpeedTest(iLiveSucCallback suc, iLiveErrCallback err, void* data) = 0;

		/**
		@brief 开始本地视频录制;
		@details 开始本地视频录制后，摄像头和屏幕分享及音频数据，会录制成mp4文件存放到本地;
		@param [in] szDir 录制文件存放的路径,如"D:/";请确保输入路径是有效的，否则会回调OnError并停止录制;
		@param [in] delegate 录制代理，录制过程中的回调将会通过此回调通知给业务侧;
		@remark 在登录后，即可调用此接口，进入房间后，打开摄像头或者屏幕分享的画面都会自动录制成本地文件;<br/>
		推荐在进房间成功回调中开始录制,在退出房间回调中结束录制，注意，这里说的退出房间包括sdk强制退出房间回调;
		*/
		virtual void startLocalRecord(const String& szDir, iLiveLocalRecordDelegate* delegate) = 0;
		/**
		@brief 停止本地视频录制;
		*/
		virtual void stopLocalRecord() = 0;

		/**
		@brief 注册指定类型的音频数据回调
		@details 注册指定类型的音频数据回调后，音频数据将会分片回调给业务侧;
		@param [in] srcType 音频数据类型
		@param [in] callback 回调函数
		@param [in] data 用户自定义数据的指针，回调函数中原封不动地传回(通常为调用类的指针);
		@return 操作结果。NO_ERR表示成功;
		@remark 必须在房间内才能注册音频数据回调,否则返回ERR_WRONG_STATE错误码;
		*/
		virtual int registAudioDataCallback(E_AudioDataSourceType srcType, iLiveAudioDataCallback callback, void* data) = 0;
		/**
		@brief 反注册具体数据类型的回调函数
		@param [in] srcType 音频数据类型
		@return 操作结果。NO_ERR表示成功;
		@remark 必须在房间内进行此操作,否则返回ERR_WRONG_STATE错误码;
		*/
		virtual int unregistAudioDataCallback(E_AudioDataSourceType srcType) = 0;
		/**
		@brief 反注册所有数据类型的回调函数
		@return 操作结果。NO_ERR表示成功;
		@remark 必须在房间内进行此操作,否则返回ERR_WRONG_STATE错误码;
		*/
		virtual int unregistAllAudioDataCallback() = 0;
		/**
		@brief 设置某类型的音频格式参数。
		@param [in] srcType 音频数据类型。
		@param [in] desc 音频数据的格式。
		@return 操作结果。NO_ERR表示成功;
		@remark 必须在房间内进行此操作,否则返回ERR_WRONG_STATE错误码;
		*/
		virtual int setAudioDataFormat(E_AudioDataSourceType srcType, const iLiveAudioFrameDesc& desc) = 0;
		/**
		@brief 获取某类型的音频格式参数。
		@param [in] srcType 音频数据类型。
		@param [out] desc 音频数据的格式。
		@return 操作结果。NO_ERR表示成功;
		@remark 必须在房间内进行此操作,否则返回ERR_WRONG_STATE错误码;
		*/
		virtual int getAudioDataFormat(E_AudioDataSourceType srcType, iLiveAudioFrameDesc& desc) = 0;

		/**
		@brief 跨房连麦
		@details 和其他房间的人连麦，双方房间里的所有人都能获取到连麦两人的视频和音频数据。
		@param [in] roomId 连麦的房间号
		@param [in] userId 连麦的用户id
		@param [in] authBuffer 跨房间连麦鉴权加密串
		@param [in] cb 操作完成的回调函数
		@param [in] data 自定义指针
		@remark 最多和另外三个房间的人连麦, 每个房间只允许有一个人参与跨房间连麦。
		*/
		virtual void linkRoom(uint32 roomId, const String& userId, const String& authBuffer, iLiveCompleteCallback cb, void* data) = 0;
		/**
		@brief 取消跨房连麦
		@details 取消所有跨房间连麦。
		@param [in] cb 操作完成的回调函数
		@param [in] data 自定义指针
		*/
		virtual void unlinkRoom(iLiveCompleteCallback cb, void* data) = 0;

		/**
		@brief 设置房间内音频数据白名单。
		@details 设置音频白名单后，将只接收白名单列表中成员的音频数据;
		@param [in] identifiers 希望接收其音频数据的成员列表;
		@return 操作结果。NO_ERR表示成功;其他值表示失败，可能是因为房间不存在,个别成员不在房间内或者转换tinyid失败等(这种情况下名单内若有成员id转换成功，仍然会被加入白名单且白名单生效)。
		@remark 每次最多设置6个成员id，超过6个将添加vector最后6个到白名单，开启白名单时，若identifiers为空，则默认丢弃任所有音频数据；每次调用，白名单将被重置为新的成员列表，而不是累加。需要定制想接收的音频数据才需要调用，不调用则默认接收房间内所有音频数据;
		*/
		virtual int requestAudioList(const Vector<String>& identifiers) = 0;
		/**
		@brief 关闭音频数据白名单。
		@details 关闭音频数据白名单后，将恢复接收房间内所有成员的音频数据;
		@return 操作结果。NO_ERR表示成功;
		*/
		virtual int cancelAudioList() = 0;

		/**
		@brief 自定义数据传输,跟随音视频数据传输
		@details 根据customData的pushMode不一样决定是向接收方发送自定义数据或是附带数据到视频的SEI段
		@param [in] data 自定义数据对象。
		@return NO_ERR 表示操作成功
		*/
		virtual int fillCustomData(const sCustomData& data) = 0;

		/**
		@brief 获取当前摄像头状态
		@return true:打开 false：关闭
		*/
		virtual bool getCurCameraState() = 0;
		/**
		@brief 获取主路自定义采集状态。
		@return true:打开 false：关闭
		*/
		virtual bool getExternalCaptureState() = 0;
		/**
		@brief 获取辅路自定义采集状态。
		@return true:打开 false：关闭
		*/
		virtual bool getExternalCaptureStateSub() = 0;
		/**
		@brief 获取当前麦克风状态
		@return true:打开 false：关闭
		*/
		virtual bool getCurMicState() = 0;
		/**
		@brief 获取当前扬声器状态
		@return true:打开 false：关闭
		*/
		virtual bool getCurPlayerState() = 0;
		/**
		@brief 获取当前屏幕分享状态
		@return 当前屏幕分享状态
		*/
		virtual E_ScreenShareState getScreenShareState() = 0;
		/**
		@brief 获取当前文件播放状态。
		@return 当前文件播放状态.
		*/
		virtual E_PlayMediaFileState getPlayMediaFileState() = 0;
		/**
		@brief 获取当前系统声音采集状态
		@return true:打开 false：关闭
		*/
		virtual bool getCurSystemVoiceInputState() = 0;
	};

	/**
	@brief 获取iLive的指针
	@return iLive的指针
	*/
	extern "C" iLiveAPI iLive* GetILive();

	/**
	@brief 视频显示view。
	@details 用于表示一路视频的显示区域和显示方式,并且会帮助APP自动做视频图像的角度旋转
	*/
	struct iLiveView
	{
		iLiveView() : mode(VIEW_MODE_NONE), exclusive(false), x(0), y(0), width(0), height(0), zorder(5){}

		E_ViewMode	mode;      ///< 渲染拉伸模式。
		bool		exclusive; ///< 是否独占整个窗口，为true时, (x, y, width, height) 等价于 (0，0，窗口宽度，窗口高度)。
		uint32		x;         ///< 显示区域左上角坐标x。
		uint32		y;         ///< 显示区域左上角坐标y。
		uint32		width;     ///< 显示区域像素宽。
		uint32		height;    ///< 显示区域像素高。
		uint32		zorder;    ///< zorder, 用于表示显示区域层级关系。
	};

	/**
	@brief 视频渲染的封装类
	@details 
		- 提供2种渲染实现：D3D和GDI
		- D3D仅支持渲染i420格式,不占用CPU资源。D3D使用条件是PC支持DirectX硬件加速。绝大部分支持，特殊模式下(比如安全模式)不支持。
		- GDI仅支持渲染RGB24格式，有明显的CPU开销。GDI无使用条件。
		- SDK内部默认优先使用D3D渲染，如果不支持，自动选择GDI;
	@remark 渲染模块多线程不安全，所有方法应该在主线程调用。
	*/
	struct iLiveRootView
	{
		/**
		@brief 初始化
		@details 通过用户传入的窗口句柄，进行初始化
		@param [in] hwnd 要渲染画面的窗口句柄
		@return 操作结果;true成功，false失败;
		*/
		virtual bool init(HWND hwnd) = 0;
		/**
		@brief 释放
		@details 在销毁iLiveRootView前，需要先释放;
		*/
		virtual void uninit() = 0;
		/**
		@brief 销毁
		*/
		virtual void destroy() = 0;
		/**
		@brief 获取当前渲染类型(D3D或GDI)
		@return 渲染类型
		*/
		virtual E_RootViewType getRootViewType() = 0;
		/**
		@brief 设置渲染窗口背景色。
		@param [in] argb 背景颜色
		*/
		virtual void setBackgroundColor(uint32 argb) = 0;
		/**
		@brief 渲染视频帧
		@details 
			- 直接在SDK视频回调中调用doRender，即可进行视频渲染。
			- 会根据角度自动做视频图像的旋转。
		@param [in] frame 要渲染的视频帧
		@remark 没有setView()不会渲染。
		*/
		virtual void doRender(const LiveVideoFrame* frame) = 0;
		/**
		@brief 获取设置的iLiveView个数。
		@return 返回设置的iLiveView的个数。
		@remark 用于遍历添加过的iLiveView。
		*/
		virtual uint32 getViewCount() = 0;
		/**
		@brief 获取指定索引的iLiveView
		@param [in] index 要获取的iLiveView索引
		@param [out] identifier 获取到的iLiveView对应的用户id
		@param [out] type 获取到的iLiveView对应的视频数据类型
		@param [out] view 获取到的iLiveView
		@return 返回获取是否成功，如果下标越界，则返回false。
		*/
		virtual bool getView(uint32 index, String& identifier, E_VideoSrc& type, iLiveView& view) = 0;
		/**
		@brief 添加iLiveView。
		@param [in] identifier 要添加iLiveView对应的用户id。
		@param [in] type 添加的iLiveView对应的视频数据类型。
		@param [in] view 要添加的iLiveView。
		@param [in] paint 是否立即刷新绘制窗口。
		@remark 
			- 如果之前添加过，则为更新iLiveView状态。
			- 慎用paint，频繁调用会导致绘制窗口闪烁，建议在必要的时候刷新。
		*/
		virtual void setView(const String& identifier, E_VideoSrc type, const iLiveView& view, bool paint = true) = 0;
		/**
		@brief 移除的iLiveView。
		@param [in] identifier 移除iLiveView对应的用户id。
		@param [in] type 移除iLiveView对应的视频数据类型。
		@param [in] paint 是否立即刷新绘制窗口。
		*/
		virtual void removeView(const String& identifier, E_VideoSrc type, bool paint = true) = 0;
		/**
		@brief 移除所有iLiveView。
		@param [in] paint 是否立即刷新绘制窗口。
		*/
		virtual void removeAllView(bool paint = true) = 0;
		/**
		@brief 是否已添加iLiveView。
		@param [in] identifier 视频源用户id
		@param [in] type 视频数据类型
		@return 是否已添加iLiveView;
		*/
		virtual bool hasView(const String& identifier, E_VideoSrc type) = 0;
	};

	/**
	@brief 创建iLiveRootView对象
	@return iLiveRootView对象指针
	*/
	extern "C" iLiveAPI iLiveRootView* iLiveCreateRootView();
}
#endif //iLive_h_