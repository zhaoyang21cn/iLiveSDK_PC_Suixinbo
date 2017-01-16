#ifndef _TIM_GROUP_C_H_
#define _TIM_GROUP_C_H_

#include "tim_comm_c.h"
#include "tim_msg_c.h"

#define TIM_PRIVATE_GROUP "Private"
#define TIM_PUBLIC_GROUP  "Public"
#define TIM_CHATROOM_GROUP "ChatRoom"
#define TIM_AVCHATROOM_GROUP "AVChatRoom"

//操作失败
#define TIM_GROUP_MEMBER_STATUS_FAIL 0
//操作成功
#define TIM_GROUP_MEMBER_STATUS_SUCC 1

extern "C"
{
//handle
	//扩展字段相关 handle
	typedef void* TIMGroupCustomInfoHandle;

	//创建新群相关信息 handle
	typedef void* TIMNewGroupMemberInfoHandle;
	typedef void* TIMNewGroupInfoHandle;
	
	//获取群信息相关选项
	typedef void* TIMGetGroupDetailInfoOptionHandle;
	typedef void* TIMGetGroupMemberInfoOptionHandle;
	typedef void* TIMGetGroupPendencyOptHandle;

	//修改群信息相关选项
	typedef void* TIMModifyGroupMemberInfoOptionHandle;
	typedef void* TIMModifyGroupBaseInfoOptionHandle;

	//接口回调返回相关信息
	typedef void* TIMGroupBaseInfoHandle;
	typedef void* TIMGroupDetailInfoHandle;
	typedef void* TIMGroupMemberResultHandle;
	typedef void* TIMGroupPendencyItemHandle;
	typedef void* TIMGroupPendencyMetaHandle;

//struct and const num

	typedef enum _E_TIMGetGroupBaseInfoFlag
	{
		kGetNone =			0x00,
		kGetGroupName =		0x01,
		kGetCreateTime =	0x01 << 1,
		kGetOwnerUin =		0x01 << 2,
		kGetInfoSeq =		0x01 << 3,
		kGetLastInfoTime =	0x01 << 4,
		kGetNextMsgSeq =	0x01 << 5,
		kGetLastMsgTime =	0X01 << 6,
		kGetAppId =			0x01 << 7,
		kGetMemberNum =		0x01 << 8,
		kGetMaxMemberNum =	0x01 << 9,
		kGetNotification =	0x01 << 10,
		kGetIntroDuction =	0x01 << 11,
		kGetFaceUrl =		0x01 << 12,
		kGetAddOpton =		0x01 << 13,
		kGetGroupType =		0x01 << 14,
		kGetGroupLastMsg =  0x01 << 15,
		kGetGroupBaseInfoOnlineNum = 0x01 << 16,
		kGetGroupBaseInfoVisible = 0x01 << 17,
		kGetGroupBaseInfoSearchable = 0x01 << 18
	}TIMGetGroupBaseInfoFlag;

	typedef enum _E_TIMGetGroupMemInfoFlag
	{
		kJionTime	= 0x01,
		kMsgFlag	= 0x01 << 1,
		kRole		= 0x01 << 3,
		kShutupUntill= 0x01 << 4,
		kNameCard	= 0x01 << 5,
	}TIMGetGroupMemInfoFlag;

	typedef enum _E_TIMGetGroupMemRoleFilter
	{
		kGetGroupMemberAll = 0x00,
		kGetGroupMemRoleOwner = 0x01,
		kGetGroupMemRoleAdmin = 0x01 << 1,
		kGetGroupMemRoleCommon_member = 0x01 << 2,
	}TIMGetGroupMemRoleFilter;

	typedef enum _E_TIMModifyGroupMemberFlag
	{
		kModifyMsgFlag = 0x01,		// 消息屏蔽选项（0：接收；1，拒绝）. 最小权限: ROOT    自己可以修改
		kModifyRole = 0x01 << 1,	// 群内身份：300表示设置其为管理员.  最小权限: ROOT    自己不可修改
		kModifyShutupTime = 0x01 << 2,  // 禁言时间,单位:秒.           最小权限: 管理员  自己不可修改
		kModifyNameCard = 0x01 << 3 // 群名片
	}TIMModifyGroupMemberFlag;

	typedef enum _T_TIMModifyGroupFlag
	{
		kModifyNone	=			0x00,
		kModifyGroupName =		0x01,
		kModifyNotification =	0x01 << 1,
		kModifyIntroduction =	0x01 << 2,
		kModifyFaceUrl =		0x01 << 3,
		kModifyAddOption =		0x01 << 4,  // 申请加群选项：0禁止加入；1需要审批；2随意加入；
		kModifyMaxMmeberNum =	0x01 << 5,  // 最大群成员数量（仅ROOT可以操作）
		kModifyGroupVisible =	0x01 << 6,	// 设置群是否可见
		kModifyGroupSearchable = 0x01 << 7, // 设置群是否可被搜索
	}TIMModifyGroupFlag;

	//加群选项
	typedef enum _E_TIMGroupAddOpt
	{
		TIM_GROUP_ADD_FORBID    = 0, //禁止加群
		TIM_GROUP_ADD_AUTH		= 1, //需要管理员审批
		TIM_GROUP_ADD_ANY       = 2, // 任何人可以加入
	}TIMGroupAddOpt;

	typedef enum _E_TIMGroupMemRoleFilter
	{
		TIMGroupMemberAll		= 0x00,
		TIMGroupMemRoleOwner	= 0x01,
		TIMGroupMemRoleAdmin	= 0x01 << 1,
		TIMGroupMemRoleCommon_member = 0x01 << 2,
	}TIMGroupMemRoleFilter;

	typedef enum _E_TIMGroupPendencyType
	{
		TIMGroupApplyJoinPendency = 0,	//请求加群：0
		TIMGroupInvitePendency = 1,		//邀请加群：1
		TIMGroupBothPendency = 2,		//邀请和请求的：2
	}TIMGroupPendencyType;

	typedef enum _E_TIMGroupPendencyHandleFlag
	{
		TIMGroupPendencyFlagUndecide = 0,
		TIMGroupPendencyFlagOtherDecide = 1,
		TIMGroupPendencyFlagOperatorDecide = 2,
	}TIMGroupPendencyHandleFlag;

	typedef enum _E_TIMComStatus{ 
		kNotSet = 0, 
		kClose = 1, 
		kOpen = 2 
	}TIMComStatus;

// handle operation
	TIM_DECL TIMGroupCustomInfoHandle CreateGroupCustomInfoHandle();
	TIM_DECL void DestroyGroupCustomInfoHandle(TIMGroupCustomInfoHandle handle);
	TIM_DECL TIMGroupCustomInfoHandle CloneGroupCustomInfoHandle(TIMGroupCustomInfoHandle handle);
	//value 长度限制512字节
	TIM_DECL bool AddGroupCustomInfo(TIMGroupCustomInfoHandle handle, const char* key, const uint32_t key_len, const char* value, const uint32_t value_len);
	TIM_DECL uint32_t GetGroupCustomInfoNum(TIMGroupCustomInfoHandle handle);
	TIM_DECL int GetGroupCustomInfo(TIMGroupCustomInfoHandle handle, char* key, uint32_t key_len, char* value, uint32_t* value_len);
	TIM_DECL int GetGroupCustomInfoByIndex(TIMGroupCustomInfoHandle handle, int index, char* key, uint32_t* key_len, char* value, uint32_t* value_len);
	

	TIM_DECL TIMNewGroupMemberInfoHandle CreateNewGroupMemberInfoHandle();
	TIM_DECL void DestroyNewGroupMemberInfoHandle(TIMNewGroupMemberInfoHandle handle);
	TIM_DECL void SetNewGroupMemberInfoIdentifier(TIMNewGroupMemberInfoHandle handle, const char* identifier);
	TIM_DECL void SetNewGroupMemberInfoMemberRole(TIMNewGroupMemberInfoHandle handle, int member_role);
	TIM_DECL void SetNewGroupMemberInfoCustomInfo(TIMNewGroupMemberInfoHandle handle, TIMGroupCustomInfoHandle custom_info);

	TIM_DECL TIMNewGroupInfoHandle CreateNewGroupInfoHandle();
	TIM_DECL void DestroyNewGroupInfoHandle(TIMNewGroupInfoHandle handle);
	TIM_DECL void SetNewGroupInfoGroupType(TIMNewGroupInfoHandle handle, const char* group_type);
	TIM_DECL void SetNewGroupInfoGroupName(TIMNewGroupInfoHandle handle, const char* group_name, const uint32_t name_len);
	TIM_DECL void SetNewGroupInfoGroupMembers(TIMNewGroupInfoHandle handle, TIMNewGroupMemberInfoHandle* members, const uint32_t num);
	TIM_DECL void SetNewGroupInfoGroupNotification(TIMNewGroupInfoHandle handle, const char* notification, const uint32_t nofi_len);
	TIM_DECL void SetNewGroupInfoGroupIntroduction(TIMNewGroupInfoHandle handle, const char* introduction, const uint32_t intro_len);
	TIM_DECL void SetNewGroupInfoFaceUrl(TIMNewGroupInfoHandle handle, const char* face_url, const uint32_t face_url_len);
	TIM_DECL void SetNewGroupInfoId(TIMNewGroupInfoHandle handle, const char* id);
	TIM_DECL void SetNewGroupInfoAddOption(TIMNewGroupInfoHandle handle, const TIMGroupAddOpt opt);
	TIM_DECL void SetNewGroupInfoMaxMemberNum(TIMNewGroupInfoHandle handle, const uint32_t max_member_num);
	TIM_DECL void SetNewGroupInfoGroupCustomInfo(TIMNewGroupInfoHandle handle, TIMGroupCustomInfoHandle custom_info_handle);

	TIM_DECL TIMGetGroupDetailInfoOptionHandle CreateGetGroupDetailInfoOptionHandle();
	TIM_DECL void DestoryGetGroupDetailInfoOptionHandle(TIMGetGroupDetailInfoOptionHandle handle);
	TIM_DECL int SetFlag4GetGroupDetailInfoOptionHandle(TIMGetGroupDetailInfoOptionHandle handle, TIMGetGroupBaseInfoFlag flag);
	TIM_DECL int SetCustomInfo4GetGroupDetailnfoOptionHandle(TIMGetGroupDetailInfoOptionHandle handle, TIMGroupCustomInfoHandle custom_info_handle);
	TIM_DECL int SetGroups4GetGroupDetailInfoOptionHandle(TIMGetGroupDetailInfoOptionHandle handle, char** group_id, uint32_t group_num);

	TIM_DECL TIMGetGroupMemberInfoOptionHandle CreateGetGroupMemberInfoOptionHandle();
	TIM_DECL void DestroyGetGroupMemberInfoOptionHandle(TIMGetGroupMemberInfoOptionHandle handle);
	TIM_DECL void SetGroupMemFilter4GetGroupMemberInfoOptionHandle(TIMGetGroupMemberInfoOptionHandle handle, TIMGetGroupMemRoleFilter filter);
	TIM_DECL int SetGroupMember4GetGroupMemberInfoOptionHandle(TIMGetGroupMemberInfoOptionHandle handle, char** members_id, uint32_t member_num);
	TIM_DECL int SetCustomInfo4GetGroupMemberInfoOptionHandle(TIMGetGroupDetailInfoOptionHandle handle, TIMGroupCustomInfoHandle custom_info_handle);
	TIM_DECL int SetGroupID4GetGroupMemberInfoOptionHandle(TIMGetGroupMemberInfoOptionHandle handle, char* group_id);
	TIM_DECL int SetFlag4GetGroupMemberInfoOptionHandle(TIMGetGroupMemberInfoOptionHandle handle, TIMGetGroupMemInfoFlag flag);

	TIM_DECL TIMModifyGroupMemberInfoOptionHandle CreateModifyGroupMemberInfoOptionHandle();
	TIM_DECL void DestroyModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle);
	TIM_DECL int SetGroupID4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, char* group_id);
	TIM_DECL int SetMemberID4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, char* member_id);
	TIM_DECL int SetFlag4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, TIMModifyGroupMemberFlag flag);
	TIM_DECL int SetMsgFlag4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, uint32_t flag);
	TIM_DECL int SetRole4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, uint32_t role);
	TIM_DECL int SetShutupTime4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, uint32_t time);
	TIM_DECL int SetNameCard4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, const char* name_card, uint32_t len);
	TIM_DECL int SetCustomInfo4ModifyGroupMemberInfoOptionHandle(TIMModifyGroupMemberInfoOptionHandle handle, TIMGroupCustomInfoHandle custom_info_handle);

	TIM_DECL TIMModifyGroupBaseInfoOptionHandle CreateModifyGroupBaseInfoOptionHandle();
	TIM_DECL void DestroyModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle);
	TIM_DECL int SetGroupId4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, char* group_id);
	TIM_DECL int SetFlag4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, TIMModifyGroupFlag flag);
	TIM_DECL int SetGroupName4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, char* group_name);
	TIM_DECL int SetNotification4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, const char* notification, uint32_t nofi_len);
	TIM_DECL int SetIntroduction4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, const char* introduction, uint32_t intro_len);
	TIM_DECL int SetFaceUrl4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, const char* face_url, uint32_t face_url_len);
	TIM_DECL int SetVisuableFlag4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, TIMComStatus flag);
	TIM_DECL int SetSearchableFlag4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, TIMComStatus flag);
	//申请加群选项：0禁止加入；1需要审批；2随意加入；
	TIM_DECL int SetAddOption4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, const TIMGroupAddOpt add_option);
	TIM_DECL int SetMaxMemberNum4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, uint32_t max_member_num);
	TIM_DECL int SetCustomInfo4ModifyGroupBaseInfoOptionHandle(TIMModifyGroupBaseInfoOptionHandle handle, TIMGroupCustomInfoHandle custom_info_handle);

	TIM_DECL TIMGroupMemberResultHandle CreateGroupMemberResultHandle();
	TIM_DECL void DestroyGroupMemberResultHandle(TIMGroupMemberResultHandle handle);
	TIM_DECL TIMGroupMemberResultHandle CloneGroupMemberResultHandle(TIMGroupMemberResultHandle handle);
	TIM_DECL int GetGroupMemberResultID(TIMGroupMemberResultHandle handle, char* id, uint32_t* len);
	TIM_DECL uint32_t GetGroupMemberResult(TIMGroupMemberResultHandle handle);
	TIM_DECL void SetGroupMemberResultID(TIMGroupMemberResultHandle handle, const char* open_id);
	TIM_DECL void SetGroupMemberResult(TIMGroupMemberResultHandle handle, uint32_t result);

	TIM_DECL TIMGroupBaseInfoHandle CreateGroupBaseInfoHandle();
	TIM_DECL void DestroyGroupBaseInfoHandle(TIMGroupBaseInfoHandle handle);
	TIM_DECL TIMGroupBaseInfoHandle CloneGroupBaseInfoHandle(TIMGroupBaseInfoHandle handle);
	//群组ID
	TIM_DECL int GetGroupBaseInfoID(TIMGroupBaseInfoHandle handle, char* id, uint32_t* len);
	//群名字
	TIM_DECL int GetGroupBaseInfoName(TIMGroupBaseInfoHandle handle, char* name, uint32_t* len);
	//群类型
	TIM_DECL int GetGroupBaseInfoType(TIMGroupBaseInfoHandle handle, char* type, uint32_t* len);
	//自己的消息屏蔽位 0：接收；1：屏蔽
	TIM_DECL uint32_t GetGroupBaseInfoMsgFlag(TIMGroupBaseInfoHandle handle);

	TIM_DECL TIMGroupDetailInfoHandle CreateGroupDetailInfoHandle();
	TIM_DECL void DestroyGroupDetailInfoHandle(TIMGroupDetailInfoHandle handle);
	// 群组Id
	TIM_DECL int GetGroupDetailInfoID(TIMGroupDetailInfoHandle handle, char* id, uint32_t* len);
	// 群名
	TIM_DECL int GetGroupDetailInfoName(TIMGroupDetailInfoHandle handle, char* name, uint32_t* len);
	// 创建人
	TIM_DECL int GetGroupDetailInfoOwner(TIMGroupDetailInfoHandle handle, char* owner, uint32_t* len);
	// 群公告
	TIM_DECL int GetGroupDetailInfoNotification(TIMGroupDetailInfoHandle handle, char* buf, uint32_t* len);
	// 群简介
	TIM_DECL int GetGroupDetailInfoIntroduction(TIMGroupDetailInfoHandle handle, char* buf, uint32_t* len);
	TIM_DECL int GetGroupDetailInfoFaceURL(TIMGroupDetailInfoHandle handle, char* url, uint32_t* len);
	// 群组类型
	TIM_DECL int GetGroupDetailInfoType(TIMGroupDetailInfoHandle handle, char* type, uint32_t* len);
	TIM_DECL uint32_t GetGroupDetailInfoCreateTime(TIMGroupDetailInfoHandle handle);
	// 最近一次修改资料时间
	TIM_DECL uint32_t GetGroupDetailInfoLastInfoTime(TIMGroupDetailInfoHandle handle);
	// 最近一次发消息时间
	TIM_DECL uint32_t GetGroupDetailInfoLastMsgTime(TIMGroupDetailInfoHandle handle);
	// 群成员数量
	TIM_DECL uint32_t GetGroupDetailInfoMemberNum(TIMGroupDetailInfoHandle handle);
	TIM_DECL uint32_t GetGroupDetailInfoMaxMemberNum(TIMGroupDetailInfoHandle handle);
	TIM_DECL uint32_t GetGroupDetailInfoOnlineNum(TIMGroupDetailInfoHandle handle);
	TIM_DECL TIMComStatus GetGroupDetailInfoVisiableFlag(TIMGroupDetailInfoHandle handle);
	TIM_DECL TIMComStatus GetGroupDetailInfoSearchableFlag(TIMGroupDetailInfoHandle handle);
	TIM_DECL TIMGroupCustomInfoHandle GetGroupDetailInfoCustomInfo(TIMGroupDetailInfoHandle handle);
	TIM_DECL TIMMessageHandle CloneMessageHandleFromGroupDetailInfo(TIMGroupDetailInfoHandle handle);

	TIM_DECL TIMGroupMemberInfoHandle CreateGroupMemberInfoHandle();
	TIM_DECL void DestroyGroupMemberInfoHandle(TIMGroupMemberInfoHandle handle);
	//群成员ID
	TIM_DECL int GetGroupMemberID(TIMGroupMemberInfoHandle handle, char* id, uint32_t* len);
	//加入群组时间
	TIM_DECL uint32_t GetGroupMemberInfoJoinTime(TIMGroupMemberInfoHandle handle);
	//成员类型
	TIM_DECL uint32_t GetGroupMemberInfoRole(TIMGroupMemberInfoHandle handle);
	TIM_DECL uint32_t GetGroupMemberInfoMsgFlag(TIMGroupMemberInfoHandle handle);
	TIM_DECL uint32_t GetGroupMemberInfoShutupTime(TIMGroupMemberInfoHandle handle);
	TIM_DECL int GetGroupMemberInfoNameCard(TIMGroupMemberInfoHandle handle, char* name_card, uint32_t* len);
	TIM_DECL TIMGroupCustomInfoHandle GetGroupMemberInfoCustomInfo(TIMGroupMemberInfoHandle handle);

	TIM_DECL TIMGetGroupPendencyOptHandle CreateGetGroupPendencyOptHandle();
	TIM_DECL void DestroyGetGroupPendencyOptHandle(TIMGetGroupPendencyOptHandle opt);
	TIM_DECL int SetStartTime4GetGroupPendencyOptHandle(TIMGetGroupPendencyOptHandle opt, uint64_t start_time);
	TIM_DECL int SetMaxCount4GetGroupPendencyOptHandle(TIMGetGroupPendencyOptHandle opt, uint32_t max);

	//拉取起点时戳 单位：ms 未0时全部拉完
	TIM_DECL TIMGroupPendencyMetaHandle CloneGroupPendencyMetaHandle(TIMGroupPendencyMetaHandle meta);
	TIM_DECL void DestroyGroupPendencyMetaHandle(TIMGroupPendencyMetaHandle meta);
	TIM_DECL uint64_t GetNextStartTime4GroupPendencyMetaHandle(TIMGroupPendencyMetaHandle meta);
	//已读时戳 单位:ms
	TIM_DECL uint64_t GetReportTimeStamp4GroupPendencyMetaHandle(TIMGroupPendencyMetaHandle meta);
	TIM_DECL uint32_t GetUnreadCount4GroupPendencyMetaHandle(TIMGroupPendencyMetaHandle meta);

	TIM_DECL TIMGroupPendencyItemHandle CloneGroupPendencyItemHandle(TIMGroupPendencyItemHandle handle);
	TIM_DECL void DestroyGroupPendencyItemHandle(TIMGroupPendencyItemHandle handle);
	TIM_DECL int GetGroupId4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* id, uint32_t* id_len);
	//获取申请者ID
	TIM_DECL int GetReqId4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* id, uint32_t* id_len);
	//获取判决者ID
	TIM_DECL int GetRspId4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* id, uint32_t* id_len);
	//未决请求时间 单位:ms
	TIM_DECL uint64_t GetTime4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle);
	TIM_DECL TIMGroupPendencyType GetPendencyType4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle);
	TIM_DECL TIMGroupPendencyHandleFlag GetHandleFlag4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle);
	TIM_DECL TIMGroupPendencyHandleResult GetHandleResult4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle);

	TIM_DECL int GetApplyInviteMsg4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* msg, uint32_t* msg_len);
	TIM_DECL int GetReqUserData4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* data, uint32_t* data_len);
	TIM_DECL int GetApprovalMsg4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* msg, uint32_t* msg_len);
	TIM_DECL int GetRspUserData4GroupPendencyItemHandle(TIMGroupPendencyItemHandle handle, char* data, uint32_t* data_len);

// callback for interface
	typedef void (*CBCreateGroupOnSuccess) (const char* group_id, void* data);
	typedef void (*CBCreateGroupOnError) (int code, const char* desc, void* data);
	typedef struct _TIMCallBack_CreateGroup
	{
		CBCreateGroupOnSuccess OnSuccess;
		CBCreateGroupOnError OnError;
		void* data;
	}TIMCreateGroupCB;

	typedef void (*CBDeleteGroupMemberOnSuccess) (TIMGroupMemberResultHandle* handle_array, uint32_t array_size, void* data);
	typedef void (*CBDeleteGroupMemberOnError) (int, const char*, void* data);

	typedef struct _TIMCallBack_DeleteGroupMember
	{
		CBDeleteGroupMemberOnSuccess OnSuccess;
		CBDeleteGroupMemberOnError OnError;
		void* data;
	}TIMDeleteGroupMemberCB;

	typedef TIMDeleteGroupMemberCB TIMInviteGroupMemberCB;

	typedef void (*CBGetGroupListOnSuccess) (TIMGroupBaseInfoHandle* handle_array, uint32_t array_size, void* data);
	typedef void (*CBGetGroupListOnError) (int code, const char* desc, void* data);

	typedef struct _TIMCallBack_GetGroupList
	{
		CBGetGroupListOnSuccess OnSuccess;
		CBGetGroupListOnError OnError;
		void* data;
	}TIMGetGroupListCB;


	typedef void (*CBGetGroupDetailInfoOnSuccess) (TIMGroupDetailInfoHandle* handle_array, uint32_t array_size, void* data);
	typedef void (*CBGetGroupDetailInfoOnError) (int code, const char* desc, void* data);

	typedef struct _TIMCallBack_GetGroupDetailInfo
	{
		CBGetGroupDetailInfoOnSuccess OnSuccess;
		CBGetGroupDetailInfoOnError OnError;
		void* data;
	}TIMGetGroupDetailInfoCB;

	typedef void (*CBGetGroupMemberInfoOnSuccess) (TIMGroupMemberInfoHandle* handle_array, uint32_t array_size, void* data);
	typedef void (*CBGetGroupMemberInfoOnError) (int code, const char* desc, void* data);

	typedef void(*CBGetGroupMemberInfoOnSuccessV2) (uint64_t next_seq, TIMGroupMemberInfoHandle* handle_array, uint32_t array_size, void* data);
	typedef void(*CBGetGroupMemberInfoOnErrorV2) (int code, const char* desc, void* data);

	typedef struct _TIMCallBack_GetGroupMemberInfo
	{
		CBGetGroupMemberInfoOnSuccess OnSuccess;
		CBGetGroupMemberInfoOnError OnError;
		void* data;
	}TIMGetGroupMemberInfoCB;

	typedef struct _TIMCallBack_GetGroupMemberInfoV2
	{
		CBGetGroupMemberInfoOnSuccessV2 OnSuccess;
		CBGetGroupMemberInfoOnErrorV2 OnError;
		void* data;
	}TIMGetGroupMemberInfoCBV2;

	typedef void(*CBSearcgGroupByNameOnSuccess) (uint64_t total_num, TIMGroupDetailInfoHandle* handle_array, uint32_t array_size, void* data);
	typedef void(*CBSearcgGroupByNameOnError) (int code, const char* desc, void* data);

	typedef struct _TIMCallBack_SearcgGroupByName
	{
		CBSearcgGroupByNameOnSuccess OnSuccess;
		CBSearcgGroupByNameOnError OnError;
		void* data;
	}TIMSearcgGroupByNameCB;

	typedef void(*CBGetGroupPendencyOnSuccess)(TIMGroupPendencyMetaHandle meta, TIMGroupPendencyItemHandle* items, uint32_t item_size, void* data);
	typedef void(*CBGetGroupPendencyOnError)(int code, const char* desc, void* data);
	typedef struct _TIMCallBack_GetGroupPendency
	{
		CBGetGroupPendencyOnSuccess OnSuccess;
		CBGetGroupPendencyOnError OnError;
		void* data;
	}TIMGetGroupPendencyCB;

//GROUPS INTERFACE
	/**
	Description:	创建群组
	@param	[in]	group_type		群组
	@param	[in]	members			成员ID数组
	@param	[in]	members_count	成员个数
	@param	[in]	group_name		群组名
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMCreateGroup(const char* group_type, const char** members, uint32_t members_count, const char* group_name, TIMCreateGroupCB* callback);
	/**
	Description:	创建指定属性群组
	@param	[in]	handle		创建群指定属性
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMCreateGroupV2(TIMNewGroupInfoHandle handle, TIMCreateGroupCB* callback);

	/**
	Description:	解散群组
	@param	[in]	groupid		群组ID
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMDeleteGroup(const char* groupid, TIMCommCB * callback);
	/**
	Description:	删除群组成员 
	@param	[in]	groupid		群组ID
	@param	[in]	members		群成员ID
	@param	[in]	members_count	群成员个数
	@param	[in]	reason			踢人原因描述
	@param	[in]	reason_len		原因长度
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMDeleteGroupMember(const char* groupid, const char** members, uint32_t members_count, const char* reason, uint32_t reason_len, TIMDeleteGroupMemberCB* callback);
	/**
	Description:	邀请用户入群
	@param	[in]	groupid			群ID
	@param	[in]	members			成员ID数组
	@param	[in]	members_count	成员个数
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMInviteGroupMember(const char* groupid, const char** members, uint32_t members_count, TIMInviteGroupMemberCB* callback);

	/**
	Description:	申请加入群组
	@param	[in]	groupid		群组ID
	@param	[in]	hello_msg	申请消息
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMApplyJoinGroup(const char* groupid, const char* hello_msg, TIMCommCB* callback);
	/**
	Description:	退出群组
	@param	[in]	groupid		群组ID	
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMQuitGroup(const char* groupid, TIMCommCB* callback);
	/**
	Description:	获取加入的群组列表
	@param	[in]	callback 回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetGroupList(TIMGetGroupListCB *callback);
	/**
	Description:	获取群组资料
	@param	[in]	groupids	群组ID数组
	@param	[in]	group_num	群组ID个数
	@param	[in]	flag		群信息标记位
	@param	[in]	custom		群扩展信息
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetGroupPublicInfo(const char** groupids, const uint32_t group_num, const TIMGetGroupBaseInfoFlag flag, TIMGroupCustomInfoHandle custom, TIMGetGroupDetailInfoCB *callback);
	/**
	Description:	修改群名
	@param	[in]	groupid		群ID
	@param	[in]	groupname	修改后的群名
	@param	[in]	name_len	修改后的群名长度
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupName(const char* groupid, const char* groupname, uint32_t name_len, TIMCommCB * callback);
	/**
	Description:	修改群简介 
	@param	[in]	groupid			群ID
	@param	[in]	introduction	群简介
	@param	[in]	introduction_len群简介长度
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupIntroduction(const char* groupid, const char* introduction, uint32_t introduction_len, TIMCommCB * callback);
	/**
	Description:	修改群公告
	@param	[in]	groupid			群ID
	@param	[in]	notification	群公告
	@param	[in]	notification_len群公告长度
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupNotification(const char* groupid, const char* notification, uint32_t notification_len, TIMCommCB * callback);
	/**
	Description:	修改群头像
	@param	[in]	groupid			群ID
	@param	[in]	face_url		群头像URL
	@param	[in]	face_url_len	群头像URL长度
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupFaceUrl(const char* groupid, const char* face_url, uint32_t face_url_len, TIMCommCB * callback);
	/**
	Description:	修改加群选项
	@param	[in]	groupid		群ID
	@param	[in]	opt			加群选项
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupAddOpt(const char* groupid, const TIMGroupAddOpt opt, TIMCommCB * callback);
	/**
	Description:	转让群组
	@param	[in]	groupid		群组ID
	@param	[in]	new_owner_id	新群主ID
	@param	[in]	callback		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupOwner(const char* groupid, const char* new_owner_id, TIMCommCB* callback);

	TIM_DECL void TIMModifyGroupDatilInfoV2(TIMModifyGroupBaseInfoOptionHandle opt, TIMCommCB * callback);
 	/**
 	Description:	获取群信息
 	@param	[in]	groupids		群组ID数组
 	@param	[in]	groupid_count	群组ID个数
 	@param	[in]	cb				回调
 	@return			void
 	@exception      none
 	*/
 	TIM_DECL void TIMGetGroupDetailInfo(const char** groupids, uint32_t groupid_count, TIMGetGroupDetailInfoCB * cb);
	TIM_DECL void TIMGetGroupDetailInfoV2(TIMGetGroupDetailInfoOptionHandle opt, TIMGetGroupDetailInfoCB * cb);
 	/**
 	Description:	获取群成员列表 
 	@param	[in]	groupid	群组ID
 	@param	[in]	cb		回调
 	@return			void
 	@exception      none
 	*/
 	TIM_DECL void TIMGetGroupMembers(const char* groupid, TIMGetGroupMemberInfoCB *cb);
	TIM_DECL void TIMGetGroupMembersV2(const char* groupid, TIMGetGroupMemInfoFlag flag, TIMGroupCustomInfoHandle custom, uint64_t next_seq, TIMGetGroupMemberInfoCBV2 *cb);
	/**
	Description:	获取指定类型成员
	@param	[in]	groupid		群ID
	@param	[in]	flag		获取标志使能位
	@param	[in]	role_filter	filter标志 （拉取全部 只群组 只管理员 只普通成员）
	@param	[in]	custom		群成员自定义信息标志
	@param	[in]	next_seq	拉取seq 用户翻页
	@param	[in]	cb
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetGroupMembersByFilter(const char* groupid, TIMGetGroupMemInfoFlag flag, TIMGroupMemRoleFilter role_filter, TIMGroupCustomInfoHandle custom, uint64_t next_seq, TIMGetGroupMemberInfoCBV2 *cb);
	/**
	Description:	修改群员信息
	@param	[in]	opt			修改群员信息选项
	@param	[in]	callback	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMModifyGroupMemberInfo(TIMModifyGroupMemberInfoOptionHandle opt, TIMCommCB * callback);
	/**
	Description:	通过名称信息获取群资料（可指定字段拉取）
	@param	[in]	name		群名
	@param	[in]	name_len	群名长度
	@param	[in]	flag		要获取的群基本信息flag
	@param	[in]	custom		要获取的群扩展信息
	@param	[in]	page_num	分页号
	@param	[in]	num_perpage	每页群组数目
	@param	[in]	cb			回调
	@return			TIM_DECL void
	@exception      none
	*/
	TIM_DECL void TIMSearchGroupByName(const char* name, uint32_t name_len, TIMGetGroupBaseInfoFlag flag, TIMGroupCustomInfoHandle custom, 
		uint32_t page_num, uint32_t num_perpage, TIMSearcgGroupByNameCB* cb);

	/**
	Description:	拉取群未决相关信息
	@param	[in]	opt			拉取群未决相关选项
	@param	[in]	callback
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetGroupPendency(TIMGetGroupPendencyOptHandle opt, TIMGetGroupPendencyCB* callback);
	/**
	Description:	上报群未决已读
	@param	[in]	report_time	上报已读时间戳
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGroupPendencyReport(uint64_t report_time, TIMCommCB* cb);
	/**
	Description:	处理群未决请求
	@param	[in]	pendency_item_handle	未决条目
	@param	[in]	result					审批结果
	@param	[in]	approval_msg			审批信息
	@param	[in]	msg_len					审批信息长
	@param	[in]	user_data				审批自定义数据
	@param	[in]	data_len				审批自定义数据长度
	@param	[in]	cb						回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGroupHandlePendency(TIMGroupPendencyItemHandle pendency_item_handle, TIMGroupPendencyHandleResult result, const char* approval_msg, uint32_t msg_len, const char* user_data, uint32_t data_len, TIMCommCB* cb);
};

#endif

