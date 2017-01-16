#ifndef _TIM_MSG_C_H_
#define _TIM_MSG_C_H_


#include "tim_comm_c.h"

// 消息发送中
#define TIM_MSG_STATUS_SENDING 1
// 消息发送成功
#define TIM_MSG_STATUS_SEND_SUCC 2
// 消息发送失败
#define TIM_MSG_STATUS_SEND_FAIL 3
// 消息被删除
#define TIM_MSG_STATUS_HAS_DELETED 4
// 消息为本地导入消息
#define TIM_MSG_STATUS_LOCAL_IMPORTED 5

#define TIM_MSG_FLAG_NONE		0
#define TIM_MSG_FLAG_GAP		1
#define TIM_MSG_FLAG_DELETED	2


extern "C"
{
	typedef void* TIMOfflineInfoHandle;
	typedef void* TIMMessageHandle;
	/**
	Description:	用户新消息回调函数
	@param	[in]	handles		TIMMessageHandle 数组指针
	@param	[in]	msg_num		TIMMessageHandle 数组大小
	@param	[in]	data		用户自定义数据
	@return			void
	@exception      none
	*/
	typedef void (*CBOnNewMessage) (TIMMessageHandle* handles, uint32_t msg_num, void* data);
	typedef struct _TIMMessageCB_C
	{
		CBOnNewMessage OnNewMessage;
		void* data;
	}TIMMessageCB;

	typedef void (*CBGetMsgOnSuccess) (TIMMessageHandle* handle_array, int size, void* data);
	typedef void (*CBGetMsgOnError) (int code, const char* desc, void* data);
	typedef struct _TIMGetMsgCallBack_c
	{
		CBGetMsgOnSuccess OnSuccess;
		CBGetMsgOnError OnError;
		void* data;
	}TIMGetMsgCB;

	typedef void(*CBGetMsgDataOnSuccess) (const char* buf, uint32_t len, void* data);
	typedef void(*CBGetMsgDataOnError) (int code, const char* desc, void* data);

	typedef struct _TIMGetMsgDataCallBack_c
	{
		CBGetMsgDataOnSuccess  OnSuccess;
		CBGetMsgDataOnError	OnError;
		void*		data;
	}TIMGetMsgDataCB;



	typedef void* TIMMsgElemHandle;
	typedef void* TIMMsgTextElemHandle;
	typedef void* TIMMsgImageElemHandle;
	typedef void* TIMMsgCustomElemHandle;
	typedef void* TIMMsgFaceElemHandle;
	typedef void* TIMMsgSoundElemHandle; 
	typedef void* TIMMsgFileElemHandle;
	typedef void* TIMMsgGroupTipsElemHandle; //For Only Recv Group Tips Msg
	typedef void* TIMMsgGroupReportElemHandle;//For Only Recv Group Report Msg
	typedef void* TIMMsgSNSSystemElemHandle; //SNS关系链变更系统通知
	typedef void* TIMMsgProfileSystemElemHandle; //资料变更系统通知
	typedef void* TIMMsgVideoElemHandle;//视频消息

	TIM_DECL TIMOfflineInfoHandle CreateTIMTIMOfflineInfo();
	TIM_DECL void DestroyTIMTIMOfflineInfo(TIMOfflineInfoHandle handle);
	TIM_DECL int GetExt4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, char* ext, uint32_t* len);
	TIM_DECL int GetSound4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, char* sound, uint32_t* len);
	TIM_DECL int GetDesc44TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, char* desc, uint32_t* len);
	TIM_DECL TIMOfflinePushFlag GetFlag4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle);

	TIM_DECL void SetExt4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, const char* ext, uint32_t len);
	TIM_DECL void SetDesc4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, const char* desc, uint32_t len);
	TIM_DECL void SetSound4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, const char* sound, uint32_t len);
	TIM_DECL void SetFlag4TIMTIMOfflineInfo(TIMOfflineInfoHandle handle, TIMOfflinePushFlag flag);

	
	TIM_DECL TIMMessageHandle	CreateTIMMessage();
	TIM_DECL int				DestroyTIMMessage(TIMMessageHandle handle);
	TIM_DECL TIMMessageHandle	CloneTIMMessage(TIMMessageHandle handle);
	TIM_DECL int				AddElem(TIMMessageHandle msg, TIMMsgElemHandle elem);
	/**
	Description:	获取Message中包含的elem个数
	@param	[in]	handle		消息句柄
	@return			int			elem个数
	@exception      none
	*/
	TIM_DECL int				GetElemCount(TIMMessageHandle handle);
	/**
	Description:	获取Message中包含的指定elem句柄
	@param	[in]	handle		消息句柄
	@param	[in]	index		elem索引
	@return			TIMMsgElemHandle	elem句柄
	@exception      none
	*/
	TIM_DECL TIMMsgElemHandle	GetElem(TIMMessageHandle handle, int index);
	TIM_DECL int GetConversationFromMsg(TIMConversationHandle conv, TIMMessageHandle msg);
	/**
	Description:	当前消息的时间戳
	@param	[in]	handle	TIMMessageHandle
	@return			uint32_t	时间戳
	@exception      none
	*/
	TIM_DECL uint32_t			GetMsgTime(TIMMessageHandle handle);
	/**
	Description:	是否发送方
	@param	[in]	handle	TIMMessageHandle
	@return			bool	TRUE 表示是发送消息    FALSE 表示是接收消息
	@exception      none
	*/
	TIM_DECL bool				IsMsgFromSelf(TIMMessageHandle handle);
	/**
	Description:	是否已读
	@param	[in]	handle	TIMMessageHandle
	@return			bool	已读标志
	@exception      none
	*/
	TIM_DECL bool				IsMsgRead(TIMMessageHandle handle);
	/**
	Description:	获取消息状态
	@param	[in]	handle TIMMessageHandle
	@return			int
	@exception      none
	*/
	TIM_DECL int				GetMsgStatus(TIMMessageHandle handle);
	TIM_DECL uint64_t			GetMsgFlag(TIMMessageHandle handle);
	/**
	Description:	获取发送方
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	buf		发送方ID buffer
	@param	[in]	len		发送方ID 长
	@return			int		0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int				GetMsgSender(TIMMessageHandle handle, char* buf, uint32_t* len);
	/**
	Description:	消息Id 最大长度30
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	id		id buffer
	@param	[in\out]len		id 长度
	@return			int		0:成功
	@exception      none
	*/
	TIM_DECL int				GetMsgID(TIMMessageHandle handle, char* id, uint32_t* len);
	/**
	Description:	删除消息：注意这里仅修改状态
	@param	[in]	handle	TIMMessageHandle
	@return			bool	TRUE 成功
	@exception      none
	*/
	TIM_DECL bool				RemoveMsg(TIMMessageHandle handle);
	/**
	Description:	从本地数据库删除消息：注意群组消息通过getMessage接口会从svr同步到本地
	@param	[in]	handle	TIMMessageHandle
	@return			bool	TRUE 成功
	@exception      none
	*/
	TIM_DECL bool				DelMsgFromStorage(TIMMessageHandle handle);
	/**
	Description:	获取CustomInt
	@param	[in]	handle	TIMMessageHandle
	@return			int		CustomInt
	@exception      none
	*/
	TIM_DECL int				GetMsgCustomInt(TIMMessageHandle handle);
	/**
	Description:	获取CustomData
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	str		CustomData buffer
	@param	[in]	len		CustomData 长度
	@return			int		0:成功 非0:失败
	@exception      none	
	*/
	TIM_DECL int				GetMsgCustomStr(TIMMessageHandle handle, char* str, uint32_t* len);
	/**
	Description:	设置自定义数据，默认为0
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	custom	自定义数据
	@return			bool	TRUE 成功
	@exception      none
	*/
	TIM_DECL bool				SetMsgCustomInt(TIMMessageHandle handle, int custom);
	/**
	Description:	设置自定义数据，默认为""
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	custom	CustomData buffer
	@param	[in]	len		CustomData 长度
	@return			bool	TRUE 成功
	@exception      none
	*/
	TIM_DECL bool				SetMsgCustomStr(TIMMessageHandle handle, const char* custom, uint32_t len);
	/**
	Description:	获取消息uniqueId
	@param	[in]	handle		TIMMessageHandle
	@return			uint64_t	uniqueId
	@exception      none
	*/
	TIM_DECL uint64_t			GetMsgUniqueID(TIMMessageHandle handle);
	/**
	Description:	获取发送者资料
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	profile	发送者资料 目前只有字段：identifier、nickname、faceURL、customInfo
	@return			int		0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int				GetSenderProfile(TIMMessageHandle handle, TIMProfileHandle profile);
	/**
	Description:	获取发送者群内资料
	@param	[in]	handle	TIMMessageHandle
	@param	[in]	member_profile	发送者群内资料 目前只有字段：member、nameCard、role、customInfo
	@return			int		0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int				GetSenderGroupMemberProfile(TIMMessageHandle handle, TIMGroupMemberInfoHandle member_profile);

	/**
	Description:	将该消息转为本地消息， 用于导入历史消息
					（该操作永久改变消息状态）
	@param	[in]	handle
	@return			bool	TRUE：成功 FALSE:失败
	@exception      none
	*/
	TIM_DECL bool	ConvertMsgStatusToLocalImported(TIMMessageHandle handle);
	/**
	Description:	设置本地消息的时戳，仅用于本地消息
	@param	[in]	handle
	@param	[in]	time	时戳
	@return			bool	TRUE：成功 FALSE:失败
	@exception      none
	*/
	TIM_DECL bool SetMsgTimestamp(TIMMessageHandle handle, uint32_t time);
	/**
	Description:	设置本地消息的发送方ID，仅用于本地消息
	@param	[in]	handle
	@param	[in]	id		用户ID
	@return			bool	TRUE：成功 FALSE:失败
	@exception      none
	*/
	TIM_DECL bool SetMsgSender(TIMMessageHandle handle, const char* id);

	/**
	Description:	获取消息优先级
	@param	[in]	handle	
	@return			TIMMsgPriority 优先级
	@exception      none
	*/
	TIM_DECL TIMMsgPriority GetMsgPriority(TIMMessageHandle handle);

	/**
	Description:	设置消息优先级
	@param	[in]	handle
	@param	[in]	priority	优先级
	@return			TIM_DECL void
	@exception      none
	*/
	TIM_DECL void SetMsgPriority(TIMMessageHandle handle, TIMMsgPriority priority);

	/**
	Description:	获取消息通知类型的接口
	@param	[in]	handle
	@return			int 0:RecvAndNotify 1:NotRecv 2:RecvNotNotify
	@exception      none
	*/
	TIM_DECL int GetMsgRecvFlag(TIMMessageHandle handle);

	/**
	Description:	设置消息离线信息
	@param	[in]	handle
	@param	[in]	offline
	@return			TIM_DECL bool
	@exception      none
	*/
	TIM_DECL bool SetMsgOfflinePushInfo(TIMMessageHandle handle, TIMOfflineInfoHandle offline);

	/**
	Description:	获取消息离线信息
	@param	[in]	handle
	@param	[in]	offline
	@return			TIM_DECL int
	@exception      none
	*/
	TIM_DECL int	GetMsgOfflinePushInfo(TIMMessageHandle handle, TIMOfflineInfoHandle offline);

	TIM_DECL TIMMsgTextElemHandle	CreateMsgTextElem();
	TIM_DECL TIMMsgImageElemHandle	CreateMsgImageElem();
	TIM_DECL TIMMsgImageElemHandle	CloneMsgImageElem(TIMMsgImageElemHandle handle);
	TIM_DECL TIMMsgCustomElemHandle CreateCustomElemHandle();

	/**
	Description:	创建FaceElemHandle
	@return			TIMMsgFaceElemHandle
	@exception      none
	*/
	TIM_DECL TIMMsgFaceElemHandle	CreateFaceElemHandle();
	TIM_DECL TIMMsgSoundElemHandle	CreateSoundElemHandle();
	TIM_DECL TIMMsgFileElemHandle	CreateFileElemHandle();
	TIM_DECL TIMMsgVideoElemHandle	CreateVideoElemHandle();
	
	TIM_DECL void					DestroyElem(TIMMsgElemHandle handle);
	TIM_DECL void					SetElemType(TIMMsgElemHandle handle, TIMElemType type);
	TIM_DECL TIMElemType			GetElemType(TIMMsgElemHandle handle);

	TIM_DECL void	SetContent(TIMMsgTextElemHandle handle, const char* content);
	TIM_DECL uint32_t	GetContentLen(TIMMsgTextElemHandle handle);
	TIM_DECL int	GetContent(TIMMsgTextElemHandle handle, char* content, uint32_t* len);

	typedef void* TIMImageHandle;
	/**
	Description:	获取图片规格
	@param	[in]	handle	TIMImageHandle
	@return			TIMImageType	图片规格，有三种Thumb、Large、Original，分别代表缩略图、大图、原图
	@exception      none
	*/
	TIM_DECL TIMImageType	GetImageType(TIMImageHandle handle);
	/**
	Description:	获取图片大小
	@param	[in]	handle		TIMImageHandle
	@return			uint32_t	大小
	@exception      none
	*/
	TIM_DECL uint32_t	GetImageSize(TIMImageHandle handle);
	/**
	Description:	获取图片高度
	@param	[in]	handle		TIMImageHandle
	@return			uint32_t	图片高度
	@exception      none
	*/
	TIM_DECL uint32_t	GetImageHeight(TIMImageHandle handle);
	/**
	Description:	获取图片宽度
	@param	[in]	handle		TIMImageHandle
	@return			uint32_t	图片宽度
	@exception      none
	*/
	TIM_DECL uint32_t	GetImageWidth(TIMImageHandle handle);
	TIM_DECL uint32_t	GetImageURLLen(TIMImageHandle handle);
	TIM_DECL int		GetImageURL(TIMImageHandle handle, char* url, uint32_t* len);
	/**
	Description:	获取图片
	@param	[in]	handle		TIMImageHandle
	@param	[in]	filename	文件名	
	@param	[in]	cb			用户回调
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int		GetImageFile(TIMImageHandle handle, char* filename, TIMCommCB* cb);

	TIM_DECL int		GetImageElemUUID(TIMMsgImageElemHandle handle, char* buf, uint32_t* len);
	TIM_DECL int		GetImageElemTaskID(TIMMsgImageElemHandle handle);
	TIM_DECL bool		CancelImageElemUploading(TIMMsgImageElemHandle handle);
	TIM_DECL int		GetImageUploadingProgress(TIMMsgImageElemHandle handle);
	TIM_DECL int		GetImageElemFormat(TIMMsgImageElemHandle handle);
	/**
	Description:	获取图片路径（接受消息时不需要关注）
	@param	[in]	handle	TIMMsgImageElemHandle
	@param	[in]	path	路径buffer
	@param	[in\out]len		路径长度
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int		GetImageElemPath(TIMMsgImageElemHandle handle, char* path, uint32_t* len);
	/**
	Description:	设置发送图片路径
	@param	[in]	handle	TIMMsgImageElemHandle
	@param	[in]	path	路径
	@param	[in]	len		路径长度
	@return			void	
	@exception      none
	*/
	TIM_DECL void		SetImageElemPath(TIMMsgImageElemHandle handle, const char* path, uint32_t len);
	TIM_DECL void		SetImageCompressLeval(TIMMsgImageElemHandle handle, const TIM_IMAGE_COMPRESS_TYPE leval);
	/**
	Description:	获取包含Image的个数
	@param	[in]	handle		TIMMsgImageElemHandle
	@return			uint32_t	Image个数
	@exception      none
	*/
	TIM_DECL uint32_t	GetImageNum(TIMMsgImageElemHandle handle);
	/**
	Description:	获取ImageElem包含的ImageHandle
	@param	[in]	handle	TIMMsgImageElemHandle
	@param	[in]	images	image handle的buffer
	@param	[in]	num		image个数
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int		GetImages(TIMMsgImageElemHandle handle, TIMImageHandle* images, uint32_t* num);


	TIM_DECL uint32_t	GetCustomElemDataLen(TIMMsgCustomElemHandle handle);
	TIM_DECL int		GetCustomElemData(TIMMsgCustomElemHandle handle, char* date, uint32_t* len);
	TIM_DECL void		SetCustomElemData(TIMMsgCustomElemHandle handle, const char* date, uint32_t len);
	TIM_DECL int		GetCustomElemDesc(TIMMsgCustomElemHandle handle, char* desc, uint32_t* len);
	TIM_DECL void		SetCustomElemDesc(TIMMsgCustomElemHandle handle, const char* desc, uint32_t len);
	TIM_DECL int		GetCustomElemExt(TIMMsgCustomElemHandle handle, char* ext, uint32_t* len);
	TIM_DECL void		SetCustomElemExt(TIMMsgCustomElemHandle handle, const char* ext, uint32_t len);
	TIM_DECL int		GetCustomElemSound(TIMMsgCustomElemHandle handle, char* sound, uint32_t* len);
	TIM_DECL void		SetCustomElemSound(TIMMsgCustomElemHandle handle, const char* sound, uint32_t len);


	/**
	Description:	获取表情索引（用户自定义）
	@param	[in]	handle		FaceElemHandle
	@return			int			索引
	@exception      none
	*/
	TIM_DECL int		GetFaceElemIndex(TIMMsgFaceElemHandle handle);
	/**
	Description:	获取用户自定义数据长度
	@param	[in]	handle		FaceElemHandle
	@return			uint32_t	用户自定义数据长度
	@exception      none
	*/
	TIM_DECL uint32_t	GetFaceElemDataLen(TIMMsgFaceElemHandle handle);
	/**
	Description:	获取用户自定义数据
	@param	[in]	handle		FaceElemHandle
	@param	[in]	date		用户自定义数据Buffer
	@param	[in\out]len			用户自定义数据长度
	@return			int 0:成功 非0:失败
	@exception      none
	*/
	TIM_DECL int		GetFaceElemData(TIMMsgFaceElemHandle handle, char* date, uint32_t* len);
	/**
	Description:	设置表情索引
	@param	[in]	handle		FaceElemHandle
	@param	[in]	index		索引
	@return			void
	@exception      none
	*/
	TIM_DECL void		SetFaceElemIndex(TIMMsgFaceElemHandle handle, int index);
	/**
	Description:	设置表情自定于数据
	@param	[in]	handle		FaceElemHandle
	@param	[in]	date		用户自定义数据Buffer
	@param	[in]	len			用户自定义数据长度
	@return			void
	@exception      none
	*/
	TIM_DECL void		SetFaceElemIndexData(TIMMsgFaceElemHandle handle, const char* date, uint32_t len);

	/**
	Description:	设置语音数据
	@param	[in]	handle	TIMMsgSoundElemHandle
	@param	[in]	data	语音二进制数据
	@param	[in]	len		语音数据长度
	@return			void
	@exception      none
	*/
	TIM_DECL void		SetSoundElemData(TIMMsgSoundElemHandle handle, const char* data, uint32_t len);
	/**
	Description:	设置语音文件路径（设置path时，优先上传语音文件）
	@param	[in]	handle	TIMMsgSoundElemHandle
	@param	[in]	path	文件路径
	@param	[in]	len		路径长度
	@return			void
	@exception      none
	*/
	TIM_DECL void		SetSoundElemPath(TIMMsgSoundElemHandle handle, const char* path, uint32_t len);
	/**
	Description:	设置语音长度（秒），发送消息时设置
	@param	[in]	handle		TIMMsgSoundElemHandle
	@param	[in]	duration	时长
	@return			void
	@exception      none
	*/
	TIM_DECL void		SetSoundElemDuration(TIMMsgSoundElemHandle handle, const uint32_t duration);
	/**
	Description:	获取语音长度（秒）
	@param	[in]	handle		TIMMsgSoundElemHandle
	@return			uint32_t	时长	
	@exception      none
	*/
	TIM_DECL uint32_t	GetSoundElemDuration(TIMMsgSoundElemHandle handle);
	TIM_DECL int		GetSoundElemUUID(TIMMsgSoundElemHandle handle, char* id, uint32_t* id_len);
	/**
	Description:	获取语音数据
	@param	[in]	handle	TIMMsgSoundElemHandle
	@param	[in]	cb		用户回调
	@return			void
	@exception      none
	*/
	TIM_DECL void		GetSoundFromSoundElem(TIMMsgSoundElemHandle handle, TIMGetMsgDataCB* cb);

	TIM_DECL void		SetFileElemFileName(TIMMsgFileElemHandle handle, const char* name, uint32_t name_len);
	TIM_DECL int		GetFileElemFileName(TIMMsgFileElemHandle handle, char* name, uint32_t* name_len);
	TIM_DECL void		SetFileElemFilePath(TIMMsgFileElemHandle handle, const char* path, uint32_t path_len);
	TIM_DECL void		SetFileElemData(TIMMsgFileElemHandle handle, const char* data, uint32_t data_len);
	TIM_DECL int		GetFileElemUUID(TIMMsgFileElemHandle handle, char* id, uint32_t* len);
	TIM_DECL void		GetFileFromFileElem(TIMMsgFileElemHandle handle, TIMGetMsgDataCB* cb);
	
	typedef void* TIMVideoHandle;
	TIM_DECL int		GetUUIDFromTIMVideo(TIMVideoHandle handle, char* id, uint32_t* len);
	TIM_DECL int		GetVideoTypeFromTIMVideo(TIMVideoHandle handle, char* type, uint32_t* len);
	TIM_DECL void		SetVideoTypeFroTIMVideo(TIMVideoHandle handle, const char* type, uint32_t len);
	TIM_DECL int		GetVideoSizeFromTIMVideo(TIMVideoHandle handle);
	TIM_DECL int		GetVideoDurationFromTIMVideo(TIMVideoHandle handle);
	TIM_DECL void		SetVideoDurationFromTIMVideo(TIMVideoHandle handle, int duration);
	TIM_DECL void		GetVideoFromTIMVideo(TIMVideoHandle handle, const char* video_path, uint32_t path_len, TIMCommCB* cb);

	typedef void* TIMSnapshotHandle;
	TIM_DECL int		GetUUIDFromTIMSnapshot(TIMSnapshotHandle handle, char* id, uint32_t* len);
	TIM_DECL int		GetSnapshotTypeFromTIMSnapshot(TIMSnapshotHandle handle, char* type, uint32_t* len);
	TIM_DECL void		SetSnapshotTypeForTIMSnapshot(TIMSnapshotHandle handle, const char* type, uint32_t len);
	TIM_DECL int		GetSnapshotSizeForTIMSnapshot(TIMSnapshotHandle handle);
	TIM_DECL int		GetSnapshotWidthFromTIMSnapshot(TIMSnapshotHandle handle);
	TIM_DECL void		SetSnapshotWidthForTIMSnapshot(TIMSnapshotHandle handle, int width);
	TIM_DECL int		GetSnapshotHeightFromTIMSnapshot(TIMSnapshotHandle handle);
	TIM_DECL void		SetSnapshotHeightForTIMSnapshot(TIMSnapshotHandle handle, int height);
	TIM_DECL void		GetSnapshotFromTIMSnapshot(TIMVideoHandle handle, const char* snapshot_path, uint32_t path_len, TIMCommCB* cb);

	TIM_DECL uint32_t	GetVideoElemTask(TIMMsgVideoElemHandle handle);
	TIM_DECL void		SetVideoElemVideoFilePath(TIMMsgVideoElemHandle handle, const char* path, uint32_t file_path_len);
	TIM_DECL void		SetVideoElemSnapshotPath(TIMMsgVideoElemHandle handle, const char* path, uint32_t file_path_len);
	TIM_DECL TIMVideoHandle		GetVideoFromVideoElem(TIMMsgVideoElemHandle handle);
	TIM_DECL TIMSnapshotHandle	GetSnapshotFromVideoElem(TIMMsgVideoElemHandle handle);
	TIM_DECL int		GetVideoUploadingProcess(TIMMsgVideoElemHandle handle);
	
	

	typedef void* TIMGroupChangeInfoHandle;

#define TIM_GROUP_INFO_CHAGE_TYPE_GROUP_NAME	0x1 //群名更改
#define TIM_GROUP_INFO_CHAGE_TYPE_INTRODUCTION	0x2 //群简介更改
#define	TIM_GROUP_INFO_CHAGE_TYPE_NOTIFACTION	0x3 //群通知更改
#define TIM_GROUP_INFO_CHAGE_TYPE_FACE_URL		0x4 //群头像更改
#define TIM_GROUP_INFO_CHAGE_TYPE_OWNER			0x5 //群主更改

	TIM_DECL int	  GetGroupChangeInfoType(TIMGroupChangeInfoHandle handle);
	TIM_DECL uint32_t GetGroupChangeInfoLen(TIMGroupChangeInfoHandle handle);
	TIM_DECL uint32_t GetGroupChangeInfo(TIMGroupChangeInfoHandle handle, char* info, uint32_t *len);

	typedef void* TIMGroupMemberInfoChangeHanlde;
	TIM_DECL int GetGroupMemberChangeInfoID(TIMGroupMemberInfoChangeHanlde handle, char* id, uint32_t * len);
	TIM_DECL uint32_t TIMGetGroupMemberChangeInfoShutTime(TIMGroupMemberInfoChangeHanlde handle);

	typedef void* TIMGroupTipsUserInfoHandle;
	TIM_DECL int GetGroupTipsUserInfoID(TIMGroupTipsUserInfoHandle handle, char* id, uint32_t * len);

	typedef enum _E_TIM_GROUPTIPS_TYPE
	{
		TIM_GROUP_TIPS_TYPE_INVITE              = 0x01, //邀请加入群
		TIM_GROUP_TIPS_TYPE_QUIT_GRP            = 0x02, //退出群
		TIM_GROUP_TIPS_TYPE_KICKED              = 0x03, //踢出群 
		TIM_GROUP_TIPS_TYPE_SET_ADMIN           = 0x04, //设置管理员
		TIM_GROUP_TIPS_TYPE_CANCEL_ADMIN        = 0x05, //取消管理员
		TIM_GROUP_TIPS_TYPE_INFO_CHANGE         = 0x06, //群资料变更
		TIM_GROUP_TIPS_TYPE_MEMBER_INFO_CHANGE  = 0x07, //群成员资料变更 
	}E_TIM_GROUPTIPS_TYPE;

	typedef void(*CBGroupTipsEventHandleProc) (TIMMsgGroupTipsElemHandle group_tips_elems, void* data);

	typedef struct _TIMCallBack_GroupUpdateCB
	{
		CBGroupTipsEventHandleProc OnGroupTipsEvent;
		void* data;
	}TIMGroupEventListener;

	TIM_DECL TIMMsgGroupTipsElemHandle CloneGroupTipsElem(TIMMsgGroupTipsElemHandle handle);
	TIM_DECL void DestroyGroupTipsElem(TIMMsgGroupTipsElemHandle handle);
	//群Tips类型
	TIM_DECL E_TIM_GROUPTIPS_TYPE	GetGroupTipsInfoType(TIMMsgGroupTipsElemHandle handle);
	//群ID
	TIM_DECL int	GetGroupTipsInfoGroupID(TIMMsgGroupTipsElemHandle handle, char* id, uint32_t * len);
	//变更下发时间
	TIM_DECL uint32_t	GetGroupTipsInfoTime(TIMMsgGroupTipsElemHandle handle);
	//群名
	TIM_DECL int	GetGroupTipsInfoGroupName(TIMMsgGroupTipsElemHandle handle, char* group_name, uint32_t * len);
	//操作人ID
	TIM_DECL int	GetGroupTipsInfoOperatorID(TIMMsgGroupTipsElemHandle handle, char* id, uint32_t * len);
	//被操作人列表
	TIM_DECL uint32_t	GetGroupTipsInfoUsersNum(TIMMsgGroupTipsElemHandle handle);
	TIM_DECL int	GetGroupTipsInfoUsers(TIMMsgGroupTipsElemHandle handle, TIMGroupTipsUserInfoHandle* handles, uint32_t* num);
	//群信息变更列表
	TIM_DECL uint32_t	GetGroupTipsInfoGroupChangeInfoNum(TIMMsgGroupTipsElemHandle handle);
	TIM_DECL int	GetGroupTipsInfoGroupChangeInfo(TIMMsgGroupTipsElemHandle handle, TIMGroupChangeInfoHandle* handles, uint32_t* num);
	//群成员变更列表
	TIM_DECL uint32_t	GetGroupTipsInfoMemberChangeInfoNum(TIMMsgGroupTipsElemHandle handle);
	TIM_DECL int	GetGroupTipsInfoMemberChangeInfo(TIMMsgGroupTipsElemHandle handle, TIMGroupMemberInfoChangeHanlde* handles, uint32_t* num);
	//操作人profile
	TIM_DECL int	GetProfile4GroupTipsInfo(TIMMsgGroupTipsElemHandle handle, TIMProfileHandle profile);
	//操作人group member info
	TIM_DECL int	GetGroupMemberInfo4GroupTips(TIMMsgGroupTipsElemHandle handle, TIMGroupMemberInfoHandle member_info);
	//获取变更profile
	TIM_DECL uint32_t	GetChangeUserProfileCount4GroupTips(TIMMsgGroupTipsElemHandle handle);
	TIM_DECL int	GetChangeUserProfile4GroupTipsByID(TIMMsgGroupTipsElemHandle handle, const char* id, TIMProfileHandle profile);
	TIM_DECL int GetChangeUserProfile4GroupTipsByIndex(TIMMsgGroupTipsElemHandle handle, uint32_t idx, char* id, uint32_t* len, TIMProfileHandle profile);

	TIM_DECL uint32_t GetChangeMemberInfoCount4GroupTips(TIMMsgGroupTipsElemHandle handle);
	TIM_DECL int	GetChangeMemberInfo4GroupTipsByID(TIMMsgGroupTipsElemHandle handle, const char* id, TIMGroupMemberInfoHandle profile);
	TIM_DECL int	GetChangeMemberInfo4GroupTipsByIndex(TIMMsgGroupTipsElemHandle handle, uint32_t idx, char* id, uint32_t* len, TIMGroupMemberInfoHandle profile);
	// 获取变更平台
	TIM_DECL int	GetPlatform4GroupTipsInfo(TIMMsgGroupTipsElemHandle handle, char* platform, uint32_t* len);
	
	//群系统消息类型
	typedef enum _E_TIM_GROUP_SYSTEM_TYPE
	{
		TIM_GROUP_SYSTEM_ADD_GROUP_REQUEST_TYPE		= 0x01, //申请加群请求（只有管理员会收到）
		TIM_GROUP_SYSTEM_ADD_GROUP_ACCEPT_TYPE      = 0x02,//申请加群被同意（只有申请人能够收到）
		TIM_GROUP_SYSTEM_ADD_GROUP_REFUSE_TYPE      = 0x03,//申请加群被拒绝（只有申请人能够收到）
		TIM_GROUP_SYSTEM_KICK_OFF_FROM_GROUP_TYPE	= 0x04,//被管理员踢出群（只有被踢的人能够收到）
		TIM_GROUP_SYSTEM_DELETE_GROUP_TYPE			= 0x05,//群被解散（全员能够收到）
		TIM_GROUP_SYSTEM_CREATE_GROUP_TYPE			= 0x06,//创建群消息（创建者能够收到）
		TIM_GROUP_SYSTEM_INVITED_TO_GROUP_TYPE		= 0x07,//邀请加群（被邀请者能够收到）
		TIM_GROUP_SYSTEM_QUIT_GROUP_TYPE			= 0x08,//主动退群（主动退群者能够收到）
		TIM_GROUP_SYSTEM_GRANT_ADMIN_TYPE			= 0x09,//设置管理员(被设置者接收)
		TIM_GROUP_SYSTEM_CANCEL_ADMIN_TYPE			= 0x0a,//取消管理员(被取消者接收)
		TIM_GROUP_SYSTEM_REVOKE_GROUP_TYPE			= 0x0b,//群已被回收(全员接收)
		TIM_GROUP_SYSTEM_INVITED_NEED_CONFIRM		= 0x0c,//邀请加群(只有被邀请者会接收到)
		TIM_GROUP_SYSTEM_INVITED_CONFIRMED			= 0x0d,//邀请加群被同意(只有发出邀请者会接收到)
		TIM_GROUP_SYSTEM_INVITED_REJECTED			= 0x0e,//邀请加群被拒绝(只有发出邀请者会接收到)
		TIM_GROUP_SYSTEM_CUSTOM_INFO				= 0xff,//用户自定义通知(默认全员接收)
	}E_TIM_GROUP_SYSTEM_TYPE;

	//操作类型
	TIM_DECL E_TIM_GROUP_SYSTEM_TYPE	GetGroupReportType(TIMMsgGroupReportElemHandle handle);
	//群组Id
	TIM_DECL int	GetGroupReportID(TIMMsgGroupReportElemHandle handle, char* id, uint32_t* len);
	//群组名
	TIM_DECL int	GetGroupReportName(TIMMsgGroupReportElemHandle handle, char* group_name, uint32_t* len);
	//操作人
	TIM_DECL int	GetGroupReportOperatorID(TIMMsgGroupReportElemHandle handle, char* id, uint32_t* len);
	//操作理由
	TIM_DECL int	GetGroupReportRemarkInfoLen(TIMMsgGroupReportElemHandle handle);
	TIM_DECL int	GetGroupReportRemarkInfo(TIMMsgGroupReportElemHandle handle, char* remark_info, uint32_t* len);
	//用户自定义通知
	TIM_DECL uint32_t GetGroupReportUserDataLen(TIMMsgGroupReportElemHandle handle);
	TIM_DECL int	GetGroupReportUserData(TIMMsgGroupReportElemHandle handle, char* user_data, uint32_t* len);
	//操作人profile
	TIM_DECL int	GetProfile4GroupReport(TIMMsgGroupReportElemHandle handle, TIMProfileHandle profile);
	//操作人group member info
	TIM_DECL int	GetGroupMemberInfo4GroupReport(TIMMsgGroupReportElemHandle handle, TIMGroupMemberInfoHandle member_info);
	// 获取变更平台
	TIM_DECL int	GetPlatform4GroupReport(TIMMsgGroupReportElemHandle handle, char* platform, uint32_t* len);

	//审批入群申请 或审批被拉入群申请
	// 0x00:拒绝入群
	// 0x01:同意入群
	TIM_DECL int HandleJoinRequest(TIMMsgGroupReportElemHandle handle, TIMGroupPendencyHandleResult result, 
									const char* approval_msg, uint32_t msg_len, 
									const char* user_data, uint32_t data_len, 
									TIMCommCB* cb);

	//关系链变更消息类型
	typedef enum _E_TIM_SNS_SYSTEM_TYPE
	{
		TIM_SNS_SYSTEM_ADD_FRIEND = 0x01,//添加好友系统通知
		TIM_SNS_SYSTEM_DEL_FRIEND = 0x02,//删除好友系统通知
		TIM_SNS_SYSTEM_ADD_FRIEND_REQ = 0x03,//好友申请系统通知
		TIM_SNS_SYSTEM_DEL_FRIEND_REQ = 0x04,//删除未决请求通知
		TIM_SNS_SYSTEM_ADD_BLACKLIST = 0x05,//黑名单添加
		TIM_SNS_SYSTEM_DEL_BLACKLIST = 0x06,//黑名单删除
		TIM_SNS_SYSTEM_PENDENCY_REPORT = 0x07, //未决已读上报
		TIM_SNS_SYSTEM_SNS_PROFILE_CHANGE = 0x08, //好友数据更新
		TIM_SNS_SYSTEM_ADD_RECOMMEND = 0x09, //推荐数据增加
		TIM_SNS_SYSTEM_DEL_RECOMMEND = 0x0a, //推荐数据删除
		TIM_SNS_SYSTEM_ADD_DECIDE = 0x0b, //已决增加
		TIM_SNS_SYSTEM_DEL_DECIDE = 0x0c, //已决删除
		TIM_SNS_SYSTEM_RECOMMEND_REPORT = 0x0d, //推荐已读上报
		TIM_SNS_SYSTEM_DECIDE_REPORT = 0x0e, //已决已读上报
	}E_TIM_SNS_SYSTEM_TYPE;

	typedef void* TIMMsgSNSChangeInfoHandle;
	TIM_DECL int GetID4SNSChangeInfoHandle(TIMMsgSNSChangeInfoHandle handle, char* id, uint32_t* len);
	TIM_DECL int GetNick4SNSChangeInfoHandle(TIMMsgSNSChangeInfoHandle handle, char* nick, uint32_t* len);
	TIM_DECL int GetAddWord4SNSChangeInfoHandle(TIMMsgSNSChangeInfoHandle handle, char* word, uint32_t* len);
	TIM_DECL int GetAddSource4SNSChangeInfoHandle(TIMMsgSNSChangeInfoHandle handle, char* source, uint32_t* len);
	TIM_DECL int GetRemark4SNSChangeInfoHandle(TIMMsgSNSChangeInfoHandle handle, char* remark, uint32_t* len);

	TIM_DECL E_TIM_SNS_SYSTEM_TYPE GetType4SNSSystemElem(TIMMsgSNSSystemElemHandle handle);
	TIM_DECL uint32_t GetChangeInfoNum4SNSSystemElem(TIMMsgSNSSystemElemHandle handle);
	TIM_DECL int GetChangeInfo4SNSSystemElem(TIMMsgSNSSystemElemHandle elem_handle, TIMMsgSNSChangeInfoHandle* info_handle, uint32_t* num);
	//仅TIM_SNS_SYSTEM_PENDENCY_REPORT
	TIM_DECL uint64_t GetPendencyReportTimestamp4SNSSystemElem(TIMMsgSNSSystemElemHandle elem_handle);
	//仅TIM_SNS_SYSTEM_RECOMMEND_REPORT
	TIM_DECL uint64_t GetRecommendReportTimestamp4SNSSystemElem(TIMMsgSNSSystemElemHandle elem_handle);
	//仅TIM_SNS_SYSTEM_DECIDE_REPORT 有效
	TIM_DECL uint64_t GetDecideReportTimestamp4SNSSystemElem(TIMMsgSNSSystemElemHandle elem_handle);
	
	typedef enum _E_TIM_PROFILE_SYSTEM_TYPE
	{
		TIM_PROFILE_SYSTEM_FRIEND_PROFILE_CHANGE = 0x01,//好友资料变更
	}E_TIM_PROFILE_SYSTEM_TYPE;

	TIM_DECL E_TIM_PROFILE_SYSTEM_TYPE GetType4ProfileProfileSystemElemHandle(TIMMsgProfileSystemElemHandle handle);
	TIM_DECL int GetID4ProfileProfileSystemElemHandle(TIMMsgProfileSystemElemHandle handle, char* id, uint32_t* len);
	TIM_DECL int GetNick4ProfileProfileSystemElemHandle(TIMMsgProfileSystemElemHandle handle, char* nick, uint32_t* len);
};
#endif



	