#ifndef _TIM_FRIEND_C_H_
#define _TIM_FRIEND_C_H_

#include "tim_comm_c.h"
extern "C"
{
	typedef enum _E_TIMFriendAllowType
	{
		TIM_FRIEND_ALLOW_ANY                    = 0,//同意任何用户加好友
		TIM_FRIEND_DENY_ANY                     = 1,//拒绝任何人加好友
		TIM_FRIEND_NEED_CONFIRM                 = 2,//需要验证
	}E_TIMFriendAllowType;

	typedef enum _E_TIMFriendGenderType
	{
		TIM_GENDER_UNKOWN	= 0,
		TIM_GENDER_MALE		= 1,
		TIM_GENDER_FEMALE	= 2,
	}E_TIMFriendGenderType;

	typedef enum _E_TIMFriendResponseType
	{
	    TIM_FRIEND_RESPONSE_AGREE				= 0,//同意加好友（建立单向好友）
		TIM_FRIEND_RESPONSE_AGREE_AND_ADD		= 1,//同意加好友并加对方为好友（建立双向好友）
		TIM_FRIEND_RESPONSE_REJECT				= 2,//拒绝对方好友请求
	}E_TIMFriendResponseType;

	typedef enum _E_TIMProfileFlag
	{
		TIM_PROFILE_FLAG_NONE			= 0x00,
		TIM_PROFILE_FLAG_NICK			= 0x01, //昵称
		TIM_PROFILE_FLAG_ALLOW_TYPE		= 0x01 << 1, //好友验证方式
		TIM_PROFILE_FLAG_FACE_URL       = 0x01 << 2, //头像
		TIM_PROFILE_FLAG_REMARK         = 0x01 << 3, //好友备注
		TIM_PROFILE_FLAG_GROUP			= 0x01 << 4, //好友分组
		TIM_PROFILE_FLAG_SELF_SIGNATURE = 0X01 << 5, //个性签名
		TIM_PROFILE_FLAG_GENDER			= 0x01 << 6,
		TIM_PROFILE_FLAG_BIRTHDAY		= 0x01 << 7,
		TIM_PROFILE_FLAG_LOCATION		= 0x01 << 8,
		TIM_PROFILE_FLAG_LANGUAGE		= 0x01 << 9,
	}TIMProfileFlag;

	typedef enum _E_TIMPendencyGetType
	{
		TIM_PENDENCY_GET_COME_IN                    = 1, //别人发给我的
		TIM_PENDENCY_GET_SEND_OUT                   = 2, //我发给别人的
		TIM_PENDENCY_GET_BOTH                       = 3, //别人发给我的 和 我发给别人的
	}TIMPendencyGetType;

	typedef enum  
	{
		TIM_PAGE_DIRECTION_UP_TYPE		= 1, //向上翻页
		TIM_PAGE_DIRECTION_DOWN_TYPE	= 2, //向下翻页
	}TIMPageDirectionType;

	typedef enum  
	{
		TIM_FutureTypePendencyComeIn = 0x01, // 收到的未决请求
		TIM_FutureTypePendencySendOut = 0x02, //发出去的未决请求
		TIM_FutureTypeRecommend = 0x04, //推荐好友
		TIM_FutureTypeDeccide = 0x08, //已决好友
	}TIMFutureFriendType;

	typedef enum
	{
		TIM_FRIEND_CHECK_TYPE_UNIDIRECTION = 0x1, //单向好友
		TIM_FRIEND_CHECK_TYPE_BIDIRECTION = 0x2, //互为好友
	}TIMFriendCheckType;

	
	//好友关系类型
	typedef enum
	{
		TIM_FRIEND_RELATION_TYPE_NONE	= 0x0, //不是好友
		TIM_FRIEND_RELATION_TYPE_MY_UNI = 0x1, //对方在我的好友列表中
		TIM_FRIEND_RELATION_TYPE_OTHER_UNI = 0x2, //我在对方的好友列表中
		TIM_FRIEND_RELATION_TYPE_BOTH	= 0x3, //互为好友
	}TIMFriendRelationType;

#define TIM_FRIEND_STATUS_SUCC								0//操作成功
#define TIM_ADD_FRIEND_STATUS_IN_SELF_BLACK_LIST			30515//加好友时有效：被加好友在自己的黑名单中
#define TIM_ADD_FRIEND_STATUS_FRIEND_SIDE_FORBID_ADD		30516//加好友时有效：被加好友设置为禁止加好友
#define TIM_ADD_FRIEND_STATUS_SELF_FRIEND_FULL				30519//加好友时有效：好友数量已满
#define TIM_ADD_FRIEND_STATUS_ALREADY_FRIEND				30520//加好友时有效：已经是好友
#define TIM_ADD_FRIEND_STATUS_IN_OTHER_SIDE_BLACK_LIST		30525//加好友时有效：已被被添加好友设置为黑名单
#define TIM_ADD_FRIEND_STATUS_PENDING						30539//加好友时有效：等待好友审核同意
#define TIM_DEL_FRIEND_STATUS_NO_FRIEND						31704//删除好友时有效：删除好友时对方不是好友
#define TIM_RESPONSE_FRIEND_STATUS_NO_REQ                   30614//响应好友申请时有效：对方没有申请过好友
#define TIM_RESPONSE_FRIEND_STATUS_SELF_FRIEND_FULL			30615//响应好友申请时有效：自己的好友满
#define TIM_RESPONSE_FRIEND_STATUS_FRIEND_EXIST				30617//响应好友申请时有效：好友已经存在
#define TIM_RESPONSE_FRIEND_STATUS_OTHER_SIDE_FRIEND_FULL   30630//响应好友申请时有效：对方好友满
#define TIM_ADD_BLACKLIST_FRIEND_STATUS_IN_BLACK_LIST		31307//添加黑名单有效：已经在黑名单了
#define TIM_DEL_BLACKLIST_FRIEND_STATUS_NOT_IN_BLACK_LIST	31503//删除黑名单有效：用户不在黑名单里
#define TIM_ADD_FRIEND_GROUP_STATUS_GET_SDKAPPID_FAILED		32207//创建好友分组时有效：没有拉到SDKAppId
#define TIM_ADD_FRIEND_GROUP_STATUS_NOT_FRIEND				32216//创建好友分组时有效：要加入到好友分组中的用户不是好友
#define TIM_UPDATE_FRIEND_GROUP_STATUS_GET_SDKAPPID_FAILED	32511//更新好友分组时有效：没有拉到SDKAppId
#define TIM_UPDATE_FRIEND_GROUP_STATUS_ADD_NOT_FRIEND		32518//更新好友分组时有效：要加入到好友分组中的用户不是好友
#define	TIM_UPDATE_FRIEND_GROUP_STATUS_ADD_ALREADY_IN_GROUP	32519//更新好友分组时有效：要加入到好友分组中的好友已经在分组中
#define TIM_UPDATE_FRIEND_GROUP_STATUS_DEL_NOT_IN_GROUP		32520//更新好友分组时有效：要从好友分组中删除的好友不在好友分组中
#define TIM_UPDATE_FRIEND_GROUP_STATUS_MAX_GROUPS_EXCEED	32521//更新好友分组时有效：该好友加入的好友分组个数超过了限制，每个好友最多只能加入32个好友分组

	typedef void* TIMProfileCustomInfoHandle;
	TIM_DECL TIMProfileCustomInfoHandle CreateProfileCustomInfoHandle();
	TIM_DECL void DestroyProfileCustomInfoHandle(TIMProfileCustomInfoHandle handle);
	TIM_DECL TIMProfileCustomInfoHandle CloneProfileCustomInfoHandle(TIMProfileCustomInfoHandle handle);
	//value 长度限制256字节 key长度限制8字节
	TIM_DECL bool AddProfileCustomInfo(TIMProfileCustomInfoHandle handle, const char* key, uint32_t key_len, const char* value, uint32_t value_len);
	TIM_DECL uint32_t GetProfileCustomInfoNum(TIMProfileCustomInfoHandle handle);
	TIM_DECL int GetProfileCustomInfo(TIMProfileCustomInfoHandle handle, char* key, uint32_t key_len, char* value, uint32_t* value_len);
	TIM_DECL int GetProfileCustomInfoByIndex(TIMProfileCustomInfoHandle handle, int index, char* key, uint32_t* key_len, char* value, uint32_t* value_len);

	typedef void* TIMFriendResultHandle;
	TIM_DECL int GetID4FriendResultHandle(TIMFriendResultHandle handle, char* id, uint32_t* len);
	TIM_DECL uint64_t GetResult4FriendResultHandle(TIMFriendResultHandle handle);

	//用户资料
	TIM_DECL TIMProfileHandle CreateProfileHandle();
	TIM_DECL void DestroyProfileHandle(TIMProfileHandle handle);
	TIM_DECL TIMProfileHandle CloneProfileHandle(TIMProfileHandle handle);
	//用户identifier
	TIM_DECL void	SetID4ProfileHandle(TIMProfileHandle handle, char* id);
	TIM_DECL int	GetID4ProfileHandle(TIMProfileHandle handle, char* id_buf, uint32_t* len);
	//用户昵称 最大96字节
	TIM_DECL void SetNickName4ProfileHandle(TIMProfileHandle handle, char* nick_name, uint32_t len);
	TIM_DECL int	GetNickName4ProfileHandle(TIMProfileHandle handle, char* buf, uint32_t* len);
	//好友验证方式
	TIM_DECL void	SetAllowType4ProfileHandle(TIMProfileHandle handle, E_TIMFriendAllowType type);
	TIM_DECL E_TIMFriendAllowType	GetAllowType4ProfileHandle(TIMProfileHandle handle);
	//用户备注 最大120字节
	TIM_DECL void	SetRemark4ProfileHandle(TIMProfileHandle handle, char* remark, uint32_t len);
	TIM_DECL int	GetRemark4ProfileHandle(TIMProfileHandle handle, char* remark, uint32_t* len);
	//用户性别
	TIM_DECL E_TIMFriendGenderType	GetGenderType4ProfileHandle(TIMProfileHandle handle);
	//用户location
	TIM_DECL int	GetLocation4ProfileHandle(TIMProfileHandle handle, char* location, uint32_t* len);
	//用户language
	TIM_DECL uint32_t GetLanguage4ProfileHandle(TIMProfileHandle handle);
	//用户Birthday
	TIM_DECL uint32_t GetBirthday4ProfileHandle(TIMProfileHandle handle);
	//好友分组
	TIM_DECL uint32_t GetGroupCnt4ProfileHandle(TIMProfileHandle handle);
	TIM_DECL int	GetGroupName4ProfileHandle(TIMProfileHandle handle, uint32_t idx, char* group_name, uint32_t* len);
	//加好友wording 最大120字节
	TIM_DECL void	SetAddWord4ProfileHandle(TIMProfileHandle handle, char* word, uint32_t len);
	TIM_DECL int	GetAddWord4ProfileHandle(TIMProfileHandle handle, char* word, uint32_t* len);
	TIM_DECL void	SetAddSource4ProfileHandle(TIMProfileHandle handle, char* source);
	TIM_DECL int	GetAddSource4ProfileHandle(TIMProfileHandle handle, char* source, uint32_t* len);
	TIM_DECL void	SetFaceURL4ProfileHandle(TIMProfileHandle handle, char* faceurl, uint32_t len);
	TIM_DECL int	GetFaceURL4ProfileHandle(TIMProfileHandle handle, char* faceurl, uint32_t* len);

	TIM_DECL int GetResponse4ProfileHandle(TIMProfileHandle handle, char* response, uint32_t* len);
	TIM_DECL uint64_t GetResult4ProfileHandle(TIMProfileHandle handle);


	typedef void* TIMSelfProfileHandle;
	TIM_DECL TIMSelfProfileHandle CloneSelfProfileHandle(TIMSelfProfileHandle handle);
	TIM_DECL void DestroySelfProfileHandle(TIMSelfProfileHandle handle);
	TIM_DECL int GetNickName4SlefProfileHandle(TIMSelfProfileHandle handle, char* buf, uint32_t* len);
	TIM_DECL E_TIMFriendAllowType GetAllowType4SlefProfileHandle(TIMSelfProfileHandle handle);

	typedef void* TIMFriendProfileHandle;
	TIM_DECL TIMFriendProfileHandle CloneFriendProfileHandle(TIMFriendProfileHandle handle);
	TIM_DECL void DestroyFriendProfileHandle(TIMFriendProfileHandle handle);
	TIM_DECL int GetID4FriendProfileHandle(TIMFriendProfileHandle handle, char* id, uint32_t* len);
	TIM_DECL int GetNickName4FriendProfileHandle(TIMFriendProfileHandle handle, char* buf, uint32_t* len);
	TIM_DECL int GetRemark4FriendProfileHandle(TIMFriendProfileHandle handle, char* remark, uint32_t* len);
	TIM_DECL E_TIMFriendAllowType GetAllowType4FriendProfileHandle(TIMFriendProfileHandle handle);
	TIM_DECL int GetFaceURL4FriendProfileHandle(TIMFriendProfileHandle handle, char* faceurl, uint32_t* len);
	TIM_DECL int GetSelfSignature4FriendProfileHandle(TIMFriendProfileHandle handle, char* self_signature, uint32_t* len);
	TIM_DECL TIMProfileCustomInfoHandle GetCustomInfo4FriendProfileHandle(TIMFriendProfileHandle handle);

	typedef void* TIMFriendListElemHandle;
	TIM_DECL TIMFriendListElemHandle CloneFriendListElemHandle(TIMFriendListElemHandle handle);
	TIM_DECL void DestroyFriendListElemHandle(TIMFriendListElemHandle handle);
	TIM_DECL int GetID4FriendListElemHandle(TIMFriendListElemHandle handle, char* id, uint32_t* len);
	TIM_DECL int GetNickName4FriendListElemHandle(TIMFriendListElemHandle handle, char* buf, uint32_t* len);
	TIM_DECL int GetRemark4FriendListElemHandle(TIMFriendListElemHandle handle, char* remark, uint32_t* len);
	TIM_DECL int GetFaceURL4FriendListElemHandle(TIMFriendListElemHandle handle, char* face_url, uint32_t* len);

	typedef void* TIMAddFriendHandle;
	TIM_DECL TIMAddFriendHandle CreateAddFriendHandle();
	TIM_DECL void DestroyAddFriendHandle(TIMAddFriendHandle handle);
	TIM_DECL void SetID4AddFriendHandle(TIMAddFriendHandle handle, char* id);
	//用户昵称 最大96字节
	TIM_DECL void SetNickName4AddFriendHandle(TIMAddFriendHandle handle, char* nick_name, uint32_t len);
	//好友备注 最大120字节
	TIM_DECL void SetRemark4AddFriendHandle(TIMAddFriendHandle handle, char* remark, uint32_t len);
	//好友来源
	TIM_DECL void SetAddSource4AddFriendHandle(TIMAddFriendHandle handle, char* source);
	//加好友wording
	TIM_DECL void SetAddWord4AddFriendHandle(TIMAddFriendHandle handle, char* word, uint32_t len);

	typedef void* TIMFriendResponseHandle;
	TIM_DECL TIMFriendResponseHandle CreateFriendResponseHandle();
	TIM_DECL void DestroyFriendResponseHandle(TIMFriendResponseHandle handle);
	//用户ID
	TIM_DECL void SetID4FriendResponseHandle(TIMFriendResponseHandle handle, char* id);
	//响应类型
	TIM_DECL void SetResponseType4FriendResponseHandle(TIMFriendResponseHandle handle, E_TIMFriendResponseType type);

	typedef void* TIMSetProfileOptionHandle;
	TIM_DECL TIMSetProfileOptionHandle CreateSetProfileOptionHandle();
	TIM_DECL void DestroySetProfileOptionHandle(TIMSetProfileOptionHandle handle);
	TIM_DECL void SetFlag4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, TIMProfileFlag flag);
	TIM_DECL void SetNick4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, const char* nick, uint32_t len);
	TIM_DECL void SetAllowType4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, E_TIMFriendAllowType type);
	TIM_DECL void SetFaceURL4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, const char* faceurl, uint32_t len);
	TIM_DECL void SetSelfSignature4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, const char* self_signature, uint32_t len);
	TIM_DECL void SetGender4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, E_TIMFriendGenderType gender);
	TIM_DECL void SetBirthday4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, uint32_t birthday);
	TIM_DECL void SetLocation4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, const char* location, uint32_t len);
	TIM_DECL void SetLanguage4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, uint32_t language);
	TIM_DECL void SetCustomInfo4SetProfileOptionHandle(TIMSetProfileOptionHandle handle, TIMProfileCustomInfoHandle custom_info);

	typedef void* TIMGetProfileOptionHandle;
	TIM_DECL TIMGetProfileOptionHandle CreateGetProfileOptionHandle();
	TIM_DECL void DestroyGetProfileOptionHandle(TIMGetProfileOptionHandle handle);
	TIM_DECL void SetFlag4GetProfileOptionHandle(TIMGetProfileOptionHandle handle, TIMProfileFlag type);
	TIM_DECL void SetCustomInfo4GetProfileOptionHandle(TIMGetProfileOptionHandle handle, TIMProfileCustomInfoHandle custom_info);

	typedef void* TIMCheckFriendResultHandle;
	TIM_DECL int TIMGetID4CheckFriendResultHandle(TIMCheckFriendResultHandle handle, char* id, uint32_t* len);
	TIM_DECL uint64_t TIMGetStatus4CheckFriendResultHandle(TIMCheckFriendResultHandle handle);
	TIM_DECL TIMFriendRelationType TIMGetRelationType4CheckFriendResultHandle(TIMCheckFriendResultHandle handle);

	typedef void* TIMFriendMetaInfoHandle;
	TIM_DECL TIMFriendMetaInfoHandle CreateFriendMetaInfoHandle();
	TIM_DECL void DestroyFriendMetaInfoHandle(TIMFriendMetaInfoHandle handle);
	TIM_DECL TIMFriendMetaInfoHandle CloneFriendMetaInfoHandle(TIMFriendMetaInfoHandle handle);
	//时间戳，需要保存，下次拉取时传入，增量更新使用
	TIM_DECL void SetTimestamp4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle, const uint64_t timestamp);
	TIM_DECL uint64_t GetTimestamp4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle);
	//序列号，需要保存，下次拉取时传入，增量更新使用
	TIM_DECL void SetInfoSeq4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle, const uint64_t info_seq);
	TIM_DECL uint64_t GetInfoSeq4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle);
	//分页信息，无需保存，返回为0时结束，非0时传入再次拉取，第一次拉取时传0
	TIM_DECL void SetNextSeq4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle, const uint64_t next_seq);
	TIM_DECL uint64_t GetNextSeq4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle);
	//覆盖：为TRUE时需要重设timestamp, infoSeq, nextSeq为0，清除客户端存储，重新拉取资料
	TIM_DECL void SetRecover4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle, const bool recover);
	TIM_DECL bool GetRecover4FriendMetaInfoHandle(TIMFriendMetaInfoHandle handle);
	
	//未决请求元信息
	typedef void* TIMFriendPendencyMetaHandle;
	TIM_DECL TIMFriendPendencyMetaHandle CreateFriendPendencyMetaHandle();
	TIM_DECL void DestroyFriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle);
	/**
	*序列号，未决列表序列号
	*建议客户端保存seq和未决列表，请求时填入server返回的seq
	*如果seq是server最新的，则不返回数据
	*/
	TIM_DECL void SetSeq4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle, const uint64_t seq);
	TIM_DECL uint64_t GetSeq4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle);
	/**
	* 翻页时间戳，只用来翻页，server返回0时表示没有更多数据，第一次请求填0
	*    特别注意的是，如果server返回的seq跟填入的seq不同，翻页过程中，需要使用客户端原始seq请求，直到数据请求完毕，才能更新本地seq
	*/
	TIM_DECL void SetTimestamp4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle, const uint64_t timestamp);
	TIM_DECL uint64_t GetTimestamp4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle);

	/**
	* 每页的数量，请求时有效（建议值，server可根据需要返回或多或少，不能作为完成与否的标志）
	*/
	TIM_DECL void SetNumPerPage4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle, const uint64_t num_per_page);
	TIM_DECL uint64_t GetNumPerPage4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle);

	/**
	* 未决请求未读数量（返回有效）
	*/
	TIM_DECL uint64_t GetUnreadCnt4FriendPendencyMetaHandle(TIMFriendPendencyMetaHandle handle);
	

	//未决请求
	typedef void* TIMFriendPendencyItemHandle;
	TIM_DECL TIMFriendPendencyItemHandle CloneFriendPendencyItemHandle(TIMFriendPendencyItemHandle handle);
	TIM_DECL void DestroyFriendPendencyItemHandle(TIMFriendPendencyItemHandle handle);
	TIM_DECL int GetID4FriendPendencyItemHandle(TIMFriendPendencyItemHandle handle, char* id, uint32_t* id_len);
	//获取添加时间
	TIM_DECL uint64_t GetAddTime4FriendPendencyItemHandle(TIMFriendPendencyItemHandle handle);
	//获取来源
	TIM_DECL int GetAddSource4FriendPendencyItemHandle(TIMFriendPendencyItemHandle handle, char* add_source, uint32_t* len);
	//获取加好友附言
	TIM_DECL int GetAddWord4FriendPendencyItemHandle(TIMFriendPendencyItemHandle handle, char* add_word, uint32_t* len);
	//获取昵称
	TIM_DECL int GetNick4FriendPendencyItemHandle(TIMFriendPendencyItemHandle handle, char* nick, uint32_t* len);
	//获取未决请求类型
	TIM_DECL TIMPendencyGetType GetPendencyTypeFriendPendencyItemHandle(TIMFriendPendencyItemHandle handle);

	typedef void* TIMFriendFutureMetaHandle;
	TIM_DECL TIMFriendFutureMetaHandle CreateFriendFutureMetaHandle();
	TIM_DECL void DestroyFriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL TIMFriendFutureMetaHandle CloneFriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	// req info
	TIM_DECL void SetDirection4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, TIMPageDirectionType type);
	TIM_DECL void SetReqNum4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t reqnum);

	// for req and resp
	TIM_DECL void SetTimeStamp4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t timestamp);
	TIM_DECL uint64_t GetTimeStamp4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL void SetPendencySequence4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t seq);
	TIM_DECL uint64_t GetPendencySequence4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL void SetRecommendSequence4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t seq);
	TIM_DECL uint64_t GetRecommendSequence4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL void SetDecideSequence4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t seq);
	TIM_DECL uint64_t GetDecideSequence4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL void SetPendencyUnReadCnt4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t cnt);
	TIM_DECL uint64_t GetPendencyUnReadCnt4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL void SetRecommendUnReadCnt4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle, uint64_t cnt);
	TIM_DECL uint64_t GetRecommendUnReadCnt4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	// just for response
	TIM_DECL uint64_t GetCurrentPendencyTimestamp4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL uint64_t GetCurrentRecommendTimestamp4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);
	TIM_DECL uint64_t GetCurrentDecideTimestamp4FriendFutureMetaHandle(TIMFriendFutureMetaHandle handle);

	typedef void* TIMFriendRecommendTagsHandle;
	TIM_DECL uint32_t GetTagsNum4FriendRecommendTagsHandle(TIMFriendRecommendTagsHandle handle);
	TIM_DECL int GetTag4FriendRecommendTagsHandle(TIMFriendRecommendTagsHandle handle, char* key, uint32_t key_len, char* value, uint32_t* value_len);
	TIM_DECL int GetTagByIndex4FriendRecommendTagsHandle(TIMFriendRecommendTagsHandle handle, int index, char* key, uint32_t* key_len, char* value, uint32_t* value_len);

	typedef void* TIMFriendFutureItemHandle;
	TIM_DECL TIMFriendFutureItemHandle CloneFriendFutureItemHandle(TIMFriendFutureItemHandle handle);
	TIM_DECL void DestroyFriendFutureItemHandle(TIMFriendFutureItemHandle handle);
	TIM_DECL TIMFutureFriendType GetType4FriendFutureItemHandle(TIMFriendFutureItemHandle handle);
	//好友id
	TIM_DECL int GetID4FriendFutureItemHandle(TIMFriendFutureItemHandle handle, char* id, uint32_t* len);
	//好友资料 //handle不允许destroy
	TIM_DECL TIMProfileHandle GetProfileHandle4FriendFutureItemHandle(TIMFriendFutureItemHandle handle);
	//添加时间
	TIM_DECL uint64_t GetAddTime4FriendFutureItemHandle(TIMFriendFutureItemHandle handle);
	//来源（仅未决好友有效）
	TIM_DECL int GetAddSource4FriendFutureItemHandle(TIMFriendFutureItemHandle handle, char* source, uint32_t* len);
	//加好友附言（仅未决好友有效）
	TIM_DECL int GetAddWording4FriendFutureItemHandle(TIMFriendFutureItemHandle handle, char* wording, uint32_t* len);
	TIM_DECL TIMFriendRecommendTagsHandle GetRecommendTagsHandle44FriendFutureItemHandle(TIMFriendFutureItemHandle handle);

	typedef void* TIMFriendGroupNamesHandle;
	TIM_DECL TIMFriendGroupNamesHandle CreateFriendGroupNamesHandle();
	TIM_DECL void DestroyFriendGroupNamesHandle(TIMFriendGroupNamesHandle handle);
	TIM_DECL void AddGroupNameforFriendGroupNamesHandle(TIMFriendGroupNamesHandle handle, const char* name, uint32_t len);

	typedef void* TIMFriendGroupInfoHandle;
	TIM_DECL int GetName4FriendGroupInfoHandle(TIMFriendGroupInfoHandle handle, char* group_name, uint32_t* len);
	TIM_DECL uint64_t GetFriendsCnt4FriendGroupInfoHandle(TIMFriendGroupInfoHandle handle);
	TIM_DECL int GetFriendID4FriendGroupInfoHandle(TIMFriendGroupInfoHandle handle, uint64_t idx, char* id, uint32_t* len);

	typedef void* TIMFriendCheckInfoHandle;
	TIMFriendCheckInfoHandle CreateFriendCheckInfoHandle();
	void DestroyFriendCheckInfoHandle(TIMFriendCheckInfoHandle check_info);
	TIM_DECL void SetCheckID4FriendCheckInfoHandle(TIMFriendCheckInfoHandle check_info, const char** id, uint32_t id_num);
	TIM_DECL void SetCheckType4FriendCheckInfoHandle(TIMFriendCheckInfoHandle check_info, TIMFriendCheckType check_type);

	// callback
	typedef void (*CBFriendshipActionCallbackOnSuccess) (TIMProfileHandle* handles, uint32_t num, void* data);
	typedef void (*CBFriendshipActionCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMFriendshipActionCallback
	{
		CBFriendshipActionCallbackOnSuccess OnSuccess;
		CBFriendshipActionCallbackOnError OnError;
		void* data;
	}TIMFriendshipActionCB;

	typedef void (*CBGetSelfProfileCallbackOnSuccess) (TIMSelfProfileHandle* handles, uint32_t num, void* data);
	typedef void (*CBGetSelfProfileCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetSelfProfileCallback
	{
		CBGetSelfProfileCallbackOnSuccess OnSuccess;
		CBGetSelfProfileCallbackOnError OnError;
		void* data;
	}TIMGetSelfProfileCallback;

	typedef void (*CBGetFriendProfileCallbackOnSuccess) (TIMFriendProfileHandle* handles, uint32_t num, void* data);
	typedef void (*CBGetFriendProfileCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetFriendProfileCallback
	{
		CBGetFriendProfileCallbackOnSuccess OnSuccess;
		CBGetFriendProfileCallbackOnError OnError;
		void* data;
	}TIMGetFriendProfileCallback;

	typedef void (*CBGetFriendListCallbackOnSuccess) (TIMFriendListElemHandle* handles, uint32_t num, void* data);
	typedef void (*CBGetFriendListCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetFriendListCallback
	{
		CBGetFriendListCallbackOnSuccess OnSuccess;
		CBGetFriendListCallbackOnError OnError;
		void* data;
	}TIMGetFriendListCallback;

	typedef void (*CBGetFriendListV2CallbackOnSuccess) (TIMFriendMetaInfoHandle meta_handle, TIMFriendListElemHandle* handles, uint32_t num, void* data);
	typedef void (*CBGetFriendListV2CallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetFriendListV2Callback
	{
		CBGetFriendListV2CallbackOnSuccess OnSuccess;
		CBGetFriendListV2CallbackOnError OnError;
		void* data;
	}TIMGetFriendListV2Callback;

	typedef void (*CBAddFriendCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void (*CBAddFriendCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMAddFriendCallback
	{
		CBAddFriendCallbackOnSuccess OnSuccess;
		CBAddFriendCallbackOnError OnError;
		void* data;
	}TIMAddFriendCallback;

	typedef void (*CBDelFriendCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void (*CBDelFriendCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMDelFriendCallback
	{
		CBDelFriendCallbackOnSuccess OnSuccess;
		CBDelFriendCallbackOnError OnError;
		void* data;
	}TIMDelFriendCallback;

	typedef void (*CBFriendResponseCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void (*CBFriendResponseCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMFriendResponseCallback
	{
		CBFriendResponseCallbackOnSuccess OnSuccess;
		CBFriendResponseCallbackOnError OnError;
		void* data;
	}TIMFriendResponseCallback; 

	typedef void (*CBGetFriendPendencyListCallbackOnSuccess) (TIMFriendPendencyMetaHandle meta, TIMFriendPendencyItemHandle* handles, uint32_t num, void* data);
	typedef void (*CBGetFriendPendencyListCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetFriendPendencyListCallback
	{
		CBGetFriendPendencyListCallbackOnSuccess OnSuccess;
		CBGetFriendPendencyListCallbackOnError OnError;
		void* data;
	}TIMGetFriendPendencyListCallback;
	
	typedef void(*CBGetFriendFurtureListCallbackOnSuccess) (TIMFriendFutureMetaHandle meta, TIMFriendFutureItemHandle* handles, uint32_t num, void* data);
	typedef void(*CBGetFriendFurtureListCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetFriendFurtureListCallback
	{
		CBGetFriendFurtureListCallbackOnSuccess OnSuccess;
		CBGetFriendFurtureListCallbackOnError OnError;
		void* data;
	}TIMGetFriendFurtureListCallback;

	typedef void(*CBDelPendencyFriendCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBDelPendencyFriendCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMDelPendencyFriendCallback
	{
		CBDelPendencyFriendCallbackOnSuccess OnSuccess;
		CBDelPendencyFriendCallbackOnError OnError;
		void* data;
	}TIMDelPendencyFriendCallback;

	typedef void(*CBDelRecommendFriendCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBDelRecommendFriendCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMDelRecommendFriendCallback
	{
		CBDelRecommendFriendCallbackOnSuccess OnSuccess;
		CBDelRecommendFriendCallbackOnError OnError;
		void* data;
	}TIMDelRecommendFriendCallback;

	typedef void(*CBDelDecideFriendCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBDelDecideFriendCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMDelDecideFriendCallback
	{
		CBDelDecideFriendCallbackOnSuccess OnSuccess;
		CBDelDecideFriendCallbackOnError OnError;
		void* data;
	}TIMDelDecideFriendCallback;

	
	typedef void(*CBSearchNickNameCallbackOnSuccess) (uint64_t total_num, TIMProfileHandle* handles, uint32_t num, void* data);
	typedef void(*CBSearchNickNameCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMSearchNickNameCallback
	{
		CBSearchNickNameCallbackOnSuccess OnSuccess;
		CBSearchNickNameCallbackOnError OnError;
		void* data;
	}TIMFriendSearchNickNameCB;

	typedef void(*CBAddFriendGroupCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBAddFriendGroupCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMAddFriendGroupCallback
	{
		CBAddFriendGroupCallbackOnSuccess OnSuccess;
		CBAddFriendGroupCallbackOnError OnError;
		void* data;
	}TIMAddFriendGroupCallback;

	typedef void(*CBAddFriends2GroupCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBAddFriends2GroupCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMAddFriends2GroupCallback
	{
		CBAddFriends2GroupCallbackOnSuccess OnSuccess;
		CBAddFriends2GroupCallbackOnError OnError;
		void* data;
	}TIMAddFriends2GroupCallback;

	typedef void(*CBDelFriendsFromGroupCallbackOnSuccess) (TIMFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBDelFriendsFromGroupCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMDelFriendsFromGroupCallback
	{
		CBDelFriendsFromGroupCallbackOnSuccess OnSuccess;
		CBDelFriendsFromGroupCallbackOnError OnError;
		void* data;
	}TIMDelFriendsFromGroupCallback;

	typedef void(*CBGetFriendsGroupCallbackOnSuccess) (TIMFriendGroupInfoHandle* handles, uint32_t num, void* data);
	typedef void(*CBGetFriendsGroupCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMGetFriendsGroupGroupCallback
	{
		CBGetFriendsGroupCallbackOnSuccess OnSuccess;
		CBGetFriendsGroupCallbackOnError OnError;
		void* data;
	}TIMGetFriendsGroupGroupCallback;

	typedef void(*CBCheckFriendsGroupCallbackOnSuccess) (TIMCheckFriendResultHandle* handles, uint32_t num, void* data);
	typedef void(*CBCheckFriendsGroupCallbackOnError) (int code, const char* desc, void* data);
	typedef struct _T_TIMCheckFriendsGroupGroupCallback
	{
		CBCheckFriendsGroupCallbackOnSuccess OnSuccess;
		CBCheckFriendsGroupCallbackOnError OnError;
		void* data;
	}TIMCheckFriendsGroupGroupCallback;

	//interface
	/**
	Description:	设置自己的昵称
	@param	[in]	nick	昵称
	@param	[in]	len		昵称长度
	@param	[in]	cb		回掉
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMSetNickName(char* nick, uint32_t len, TIMCommCB * cb);
	/**
	Description:	设置好友验证方式
	@param	[in]	type	验证方式
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMSetAllowType(E_TIMFriendAllowType type, TIMCommCB * cb);
	/**
	Description:	设置自己的头像
	@param	[in]	url		头像url
	@param	[in]	url_len	url长度
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMSetFaceURL(char* url, uint32_t url_len, TIMCommCB * cb);
	/**
	Description:	设置好友备注
	@param	[in]	id		好友ID	
	@param	[in]	remark	备注	
	@param	[in]	remark_len	备注长度
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMSetFriendRemark(const char* id, const char* remark, const uint32_t remark_len, TIMCommCB * cb);
	/**
	Description:	获取自己的资料 
	@param	[in]	cb	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetSelfProfile(TIMGetSelfProfileCallback* cb);
	/**
	Description:	获取好友的资料
	@param	[in]	id		要获取的好友ID数组
	@param	[in]	num		要获取的好友个数
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetFriendProfile(const char** id, uint32_t num, TIMGetFriendProfileCallback* cb);
	/**
	Description:	获取任何人的资料
	@param	[in]	id		要获取的用户ID数组
	@param	[in]	num		要获取的用户个数
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetUserProfile(const char** id, uint32_t num, TIMGetFriendProfileCallback* cb);

	TIM_DECL void TIMSetPartialProfile(TIMSetProfileOptionHandle opt, TIMCommCB* cb);
	TIM_DECL void TIMGetPartialProfile(const char** id, uint32_t num, TIMGetProfileOptionHandle handle, TIMGetFriendProfileCallback* cb);


	// resp: sIdentifier, sNickname, sRemark
	/**
	Description:	获取所有好友
	@param	[in]	cb	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetFriendList(TIMGetFriendListCallback * cb);
	
	// req: sIdentifier, sRemark, sAddWording, sAddSource
	// resp: sIdentifier, result
	/**
	Description:	批量添加好友
	@param	[in]	handles		添加好友handle数组
	@param	[in]	num			添加好友个数
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMAddFriend(TIMAddFriendHandle* handles, uint32_t num, TIMAddFriendCallback * cb);
	// req: sIdentifier
	// resp: sIdentifier, result
	// TYPE: 1-单向好友 2-双向好友
	/**
	Description:	删除好友
	@param	[in]	type	删除类型（单向好友、双向好友）
	@param	[in]	id		要删除的好友ID数组
	@param	[in]	num		删除的好友个数
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMDelFriend(int type, char** id, uint32_t num, TIMDelFriendCallback * cb);

	// req: sIdentifier, sResponse
	// resp: sIdentifier, result
	/**
	Description:	同意/拒绝 好友申请
	@param	[in]	handles	TIMFriendResponseHandle数组
	@param	[in]	num		数组元素个数
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMFriendResponse(TIMFriendResponseHandle* handles, uint32_t num, TIMFriendResponseCallback * cb);

	// resp: sIdentifier, result
	/**
	Description:	添加用户到黑名单
	@param	[in]	id	用户ID数组
	@param	[in]	num 用户个数
	@param	[in]	cb	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMAddBlackList(const char** id, uint32_t num, TIMFriendshipActionCB * cb);
	// resp: sIdentifier, result
	/**
	Description:	把用户从黑名单删除
	@param	[in]	id	用户ID数组
	@param	[in]	num	用户个数
	@param	[in]	cb	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMDelBlackList(const char** id, uint32_t num, TIMFriendshipActionCB * cb);
	// resp: sIdentifier
	/**
	Description:	获取黑名单列表
	@param	[in]	cb	回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetBlackList(TIMFriendshipActionCB * cb);

	// resp: sNickname
	TIM_DECL void TIMSearchUserUseIdentifier(char* id, TIMFriendshipActionCB * cb);

	/**
	*  获取好友列表（可增量、分页、自定义拉取字段）
	*
	*  @param flags 设置需要拉取的字段
	*  @param custom 自定义字段（目前还不支持）
	*  @param meta 好友元信息（详见TIMFriendMetaInfo说明）
	*  @param cb   回调
	*/
	TIM_DECL void TIMGetFriendListV2(TIMProfileFlag flag, TIMProfileCustomInfoHandle custom, TIMFriendMetaInfoHandle meta, TIMGetFriendListV2Callback* cb);

	/**
	*  通过网络获取未决请求列表
	*
	*  @param meta  请求信息，详细参考TIMFriendPendencyMetaHandle
	*  @param type  拉取类型（参考TIMPendencyGetType）
	*  @param cb   回调
	*/
	TIM_DECL void TIMGetPendencyFromServer(TIMFriendPendencyMetaHandle meta, TIMPendencyGetType type, TIMGetFriendPendencyListCallback* cb);

	/**
	*  未决请求已读上报
	*
	*  @param timestamp 已读时间戳，此时间戳以前的消息都将置为已读
	*  @param cb  回调
	*/
	TIM_DECL void TIMPendencyReport(uint64_t timestamp , TIMCommCB* cb);


	/**
	*  推荐好友已读上报
	*
	*  @param timestamp 已读时间戳，此时间戳以前的消息都将置为已读
	*  @param cb  回调
	*/
	TIM_DECL void TIMRecommendReport(uint64_t timestamp, TIMCommCB* cb);

	/**
	Description:	未决请求和好友推荐拉取
	@param	[in]	flag			获取的资料标识
	@param	[in]	type			获取的类型，按位设置
	@param	[in]	custom_handle	自定义字段，（尚未实现，填NULL）
	@param	[in]	meta			请求信息，参见TIMFriendFutureMetaHandle
	@param	[in]	cb				回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetFutureFriends(TIMProfileFlag flag, TIMFutureFriendType type, TIMProfileCustomInfoHandle custom_handle, TIMFriendFutureMetaHandle meta, TIMGetFriendFurtureListCallback* cb);


	/**
	*  未决好友删除
	*
	*  @param type  未决好友类型
	*  @param id	要删除的未决好友列表
	*  @param cb	回调
	*/
	TIM_DECL void TIMDeletePendency(TIMPendencyGetType type, const char** id, uint32_t num, TIMDelPendencyFriendCallback* cb);


	/**
	*  推荐好友删除
	*
	*  @param id	要删除的推荐好友列表
	*  @param cb    回调
	*/
	TIM_DECL void TIMDeleteRecommend(const char** id, uint32_t num, TIMDelRecommendFriendCallback* cb);

	/**
	*  已决删除
	*
	*  @param id	要删除的已决列表
	*  @param cb    回调
	*/
	TIM_DECL void TIMDeleteDecide(const char** id, uint32_t num, TIMDelDecideFriendCallback * cb);

	/**
	Description:	通过昵称模糊搜索用户
	@param	[in]	nick		要搜索的昵称关键字
	@param	[in]	nick_len	用户昵称长度
	@param	[in]	page_idx	分页号
	@param	[in]	num_perpage	每页用户数目
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMSearchNickName(const char* nick, uint32_t nick_len, uint64_t page_idx, uint64_t num_perpage, TIMFriendSearchNickNameCB* cb);

	/**
	Description:	创建好友分组
	@param	[in]	handle		好友分组名称列表
	@param	[in]	friend_ids	好友ID数组
	@param	[in]	friend_num	好友个数
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMCreateFriendGroup(TIMFriendGroupNamesHandle handle, const char** friend_ids, uint32_t friend_num, TIMAddFriendGroupCallback* cb);

	/**
	Description:	删除好友分组
	@param	[in]	handle	好友分组名称列表
	@param	[in]	cb		回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMDeleteFriendGroup(TIMFriendGroupNamesHandle handle, TIMCommCB * cb);

	/**
	Description:	添加好友到某分组
	@param	[in]	group_name	好友分组名称
	@param	[in]	name_len	好友分组名长度
	@param	[in]	friend_ids  要添加到分组中的好友ID数组
	@param	[in]	friend_num	要添加到分组中的好友个数
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMAddFriends2Group(const char* group_name, uint32_t name_len, const char** friend_ids, uint32_t friend_num, TIMAddFriends2GroupCallback* cb);

	/**
	Description:	从分组中删除好友
	@param	[in]	group_name	好友分组名称
	@param	[in]	name_len	好友分组名长度
	@param	[in]	friend_ids	要从分组中删除的好友ID数组
	@param	[in]	friend_num	要从分组中删除的好友ID个数
	@param	[in]	cb			回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMDelFriendsFromGroup(const char* group_name, uint32_t name_len, const char** friend_ids, uint32_t friend_num, TIMDelFriendsFromGroupCallback* cb);

	/**
	Description:	重命名好友分组
	@param	[in]	old_name		原来的分组名
	@param	[in]	old_name_len	原来的分组名长度
	@param	[in]	new_name		新的分组名
	@param	[in]	new_name_len	新的分组名长度
	@param	[in]	cb				回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMRenameFriendGroup(const char* old_name, uint32_t old_name_len, const char* new_name, uint32_t new_name_len, TIMCommCB * cb);

	/**
	Description:	获取指定的好友分组信息
	@param	[in]	handle			好友分组名称列表
	@param	[in]	need_get_id_list是否需要获取好友列表
	@param	[in]	cb				回调
	@return			void
	@exception      none
	*/
	TIM_DECL void TIMGetFriendGroup(TIMFriendGroupNamesHandle handle, bool need_get_id_list, TIMGetFriendsGroupGroupCallback* cb);

	TIM_DECL void TIMCheckFriends(TIMFriendCheckInfoHandle check_info, TIMCheckFriendsGroupGroupCallback* cb);
}
#endif