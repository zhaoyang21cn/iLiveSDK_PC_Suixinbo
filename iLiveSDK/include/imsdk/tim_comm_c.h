#ifndef _TIM_COMM_C_H_
#define _TIM_COMM_C_H_

#if defined(_MSC_VER) && (_MSC_VER < 1600)
	typedef signed char       int8_t;
	typedef signed short      int16_t;
	typedef signed int        int32_t;
	typedef unsigned char     uint8_t;
	typedef unsigned short    uint16_t;
	typedef unsigned int      uint32_t;
	typedef signed __int64       int64_t;
	typedef unsigned __int64     uint64_t;
#else
	#include <stdint.h>
#endif


#ifdef _WIN32
#define TIM_DECL __declspec(dllexport) 
#else 
#define TIM_DECL 
#endif



extern "C" 
{
	/**
	* 网络连接状态
	*/
	enum TIMNetworkStatus 
	{
		TIM_NETWORK_STATUS_CONNECTED = 1, //已连接
		TIM_NETWORK_STATUS_DISCONNECTED = 2, //链接断开
	};

	enum TIMConversationType {
		kCnvInvalid,
		kCnvC2C,
		kCnvGroup,
		kCnvSysem,
	};

	enum TIMMsgPriority              //标识消息的优先级，数字越大优先级越低
	{
		kMsgPriorityHigh = 1,        // 优先级最高，一般为红包或者礼物消息
		kMsgPriorityNormal = 2,      // 表示优先级次之，建议为普通消息
		kMsgPriorityLow = 3,         // 建议为点赞消息等
		kMsgPriorityLowest = 4       // 优先级最低，一般为成员进退群通知(后台下发)
	};

	enum TIMElemType {
		kElemInvalid,
		kElemText,
		kElemImage,
		kElemSound,
		kElemFile,
		kElemCustom,
		kElemFace,
		kElemLocation,
		kElemGroupTips,
		kElemGroupReport,
		kElemProfileChange,
		kElemFriendChange,
		kElemVideo,
	};

	typedef enum _TIMImageType
	{
		kOriginalImage = 0,
		kThumbImage,
		kLargeImage,
	}TIMImageType;

	typedef enum _E_TIM_IMAGE_COMPRESS_TYPE
	{
		TIM_IMAGE_COMPRESS_ORIGIN = 0x00, //原图(不压缩）
		TIM_IMAGE_COMPRESS_HIGH = 0x01, //高压缩率：图片较小，默认值
		TIM_IMAGE_COMPRESS_LOW = 0x02,//低压缩：高清图发送(图片较大)
	}TIM_IMAGE_COMPRESS_TYPE;

	typedef enum _E_TIM_IMAGE_COMPRESS_LEVEL
	{
		TIM_IMAGE_COMPRESS_LEVEL_NONE= 0x00, //原图(不压缩）
	}TIM_IMAGE_COMPRESS_LEVEL;

	enum TIMLogLevel
	{
		klogNone = 0,
		kLogError,
		kLogWarn,
		kLogInfo,
		kLogDebug
	};

	enum TIMOfflinePushFlag
	{
		TIM_OFFLINE_PUSH_DEFAULT = 0,
		TIM_OFFLINE_PUSH_NO_PUSH
	};

	typedef enum _E_TIMGroupPendencyHandleResult
	{
		TIMGroupPendencyRejected = 0,
		TIMGroupPendencyConfirmed = 1,
	}TIMGroupPendencyHandleResult;

	typedef struct _TIMUser_c
	{
		char* account_type;
		char* app_id_at_3rd;
		char* identifier;
		char* stiny_id;
		uint64_t tiny_id;
	}TIMUserInfo;

	typedef void (*CBOnSuccess) (void* data);
	typedef void (*CBOnError) (int code, const char* desc, void* data);

	typedef struct _TIMCallBack_c
	{
		CBOnSuccess OnSuccess;
		CBOnError	OnError;
		void*		data;
	}TIMCommCB;

	typedef void (*CBRequestOnSuccess) (const char* buf, uint32_t len, void* data);
	typedef void (*CBRequestOnError) (int code, const char* desc, void* data);

	typedef struct _TIMRequestCallBack_c
	{
		CBRequestOnSuccess  OnSuccess;
		CBRequestOnError	OnError;
		void*		data;
	}TIMRequestCB;

	typedef void (*CBConnOnConnected) (void* data);
	typedef void (*CBConnOnDisconnected) (void* data);

	typedef struct _TIMConnCallBack_c
	{
		CBConnOnConnected		OnConnected;
		CBConnOnDisconnected	OnDisconnected;
		void* data;
	}TIMConnCB;

	typedef void (*CBKickOffline) (void* data);
	typedef struct _TIMKickOfflineCallBack_c
	{
		CBKickOffline OnKickOffline;
		void* data;
	}TIMForceOfflineCB;

	typedef void(*CBUserSigExpired) (void* data);
	typedef struct _TIMUserSigExpiredCallBack_c
	{
		CBUserSigExpired OnUserSigExpired;
		void* data;
	}TIMUserSigExpiredCB;

	typedef void* TIMConversationHandle;

	typedef void* TIMProfileHandle;
	typedef void* TIMGroupMemberInfoHandle;

	typedef void* TIMBatchOprDetailInfoHandle;
	TIMBatchOprDetailInfoHandle CloneBatchOprDetailInfoHandle(TIMBatchOprDetailInfoHandle handle);
	void DestroyBatchOprDetailInfoHandle(TIMBatchOprDetailInfoHandle handle);
	uint32_t GetSuccNum4BatchOprDetailInfoHandle(TIMBatchOprDetailInfoHandle handle);
	uint32_t GetFailNum4BatchOprDetailInfoHandle(TIMBatchOprDetailInfoHandle handle);
	int		GetDetailErrcode4BatchOprDetailInfoHandleByIdx(TIMBatchOprDetailInfoHandle handle, uint32_t idx);
	int		GetDetailID4BatchOprDetailInfoHandleByIdx(TIMBatchOprDetailInfoHandle handle, uint32_t idx, char* id, uint32_t* len);
	int		GetDetailErrMsg4BatchOprDetailInfoHandleByIdx(TIMBatchOprDetailInfoHandle handle, uint32_t idx, char* id, uint32_t* len);

	typedef void(*CBBatchOprOnSuccess) (void* data);
	typedef void(*CBBatchOprOnError) (int code, const char* desc, TIMBatchOprDetailInfoHandle handle, void* data);
	typedef struct _TIMBBatchOprCallBack_c
	{
		CBBatchOprOnSuccess OnSuccess;
		CBBatchOprOnError	OnError;
		void*		data;
	}TIMBBatchOprCB;
};

#endif
