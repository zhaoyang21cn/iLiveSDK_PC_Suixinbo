#ifndef __TIM_INT_MANAGER_H__
#define __TIM_INT_MANAGER_H__

#include <list>

#include "tim_comm.h"

namespace imcore {

enum E_TIMStreamEncode
{
    //请求FLV编码的视频流URL
    HLS = 0x01,
    //请求HLS编码的视频流URL
    FLV = 0x02,
	//同时请求HLS和FLV编码的视频流URL
    HLS_AND_FLV = 0x03,
	//RAW码流
	RAW = 0X04,
	//RTMP
	RTMP = 0X05,
	//HLS AND RTMP
	HLS_AND_RTMP = 0X06,
};

enum E_TIMSDKType
{
	SDKType_Normal = 0x01, // 普通开发sdk
	SDKType_IOTCamara,	   // 普通物联摄像头sdk
	SDKType_CoastCamara,   // 滨海摄像头sdk
};

enum RateType
{
	RATE_TYPE_ORIGINAL = 0,//原始码率
	RATE_TYPE_550 = 10,//标清码率550K
	RATE_TYPE_900 = 20,//高清码率900K
};

struct TIMLiveUrl
{
    int encode_type; //视频流编码类型
    std::string url; //视频流播放URL
	RateType rate_type; //码率档位信息
};

struct TIMStreamRsp
{
	TIMStreamRsp(): channel_id(0){}
	std::list<TIMLiveUrl> urls;
	uint64_t channel_id;
	uint32_t tape_task_id; //录制标记为录制的时候带回录制task_id有效
};

struct TIMRoomInfo
{
	TIMRoomInfo():relation_id(0), room_id(0) {}
	int relation_id; // 讨论组ID
	int room_id;	 // 房间ID
};

struct TIMRecordParam
{
	TIMRecordParam()
		:class_id(0)
		, is_transcode(false)
		, is_screenshot(false)
		, is_watermark(false)
		, sdk_type(SDKType_Normal)
		, record_data_type(0)
		, record_type(0){}
	std::string filename;				//录制后的文件名
	int class_id;				 		//视频分类ID
	bool is_transcode;					//是否转码
	bool is_screenshot;				 	//是否截图
	bool is_watermark;					//是否打水印
	std::list<std::string> tags;	 	//视频标签列表
	E_TIMSDKType	sdk_type;
	uint32_t		record_data_type; //录制的数据类型：0.摄像头视频 1.辅流
	uint32_t		record_type; //录制本身的类型：0.Record Video Media File 1.Record Audio Media File纯音频
};



struct TIMStreamParam
{
	TIMStreamParam()
		:encode(HLS), sdk_type(SDKType_Normal), push_data_type(0), tape_flag(0), watermark_flag(0){}
	E_TIMStreamEncode encode;
	E_TIMSDKType sdk_type;
	std::string channel_name;
	std::string channel_desc;
	std::string channel_password;
	uint32_t	push_data_type; //推流的数据类型 0:摄像头 1：辅流 
	uint32_t	tape_flag;//推流是否录制 0.默认不录制  1.录制 启动推流的时候携带
	uint32_t	watermark_flag;//水印标记: 0.默认不带水印 1.带水印；启动推流可选；默认原始码率
	uint32_t	watermark_id;//水印id: 0.默认水印,其他水印ID需要通过控制台接口去获取;
	std::vector<RateType> rpt_rate_type;//支持多码率观看；启动推流可选。默认原始码率
};

class TIM_DECL TIMIntManager {
public:
	static TIMIntManager &get();
	TIMIntManager();
	uint64_t tiny_id();
	void Init(TIMCallBack *cb);
	void Uninit(TIMCallBack *cb);
	void UserIdToTinyId(std::list<TIMUser> &reqList, TIMValueCallBack<const std::list<TIMUser> &> *cb, uint64_t timeout = 5000);
    void TinyIdToUserId(std::list<uint64_t> &tinyids, TIMValueCallBack<const std::list<TIMUser> &> *cb, uint64_t timeout = 5000);
	void MultiVideoApp(const std::string &req, TIMValueCallBack<const std::string &> *cb, uint64_t timeout = 5000);
	void MultiVideoInfo(const std::string &req, TIMValueCallBack<const std::string &> *cb, uint64_t timeout = 5000);
	void RequestSharpSvr(uint64_t touin, const std::string &req, TIMValueCallBack<const std::string &> *cb, uint64_t timeout = 5000);
	void ResponseSharpSvr(uint64_t touin, const std::string &req, TIMValueCallBack<const std::string &> *cb, uint64_t timeout = 5000);
	void SetSharpSvrPushCallBack(TIMValueCallBack<const std::string &> *cb);
	TIMValueCallBack<const std::string &> *GetSharpSvrPushCallBack();
	void SetSharpSvrRspCallBack(TIMValueCallBack<const std::string &> *cb);
	TIMValueCallBack<const std::string &> *GetSharpSvrRspCallBack();
	void Request(const std::string &cmd, const std::string &req, TIMValueCallBack<const std::string &> *cb, uint64_t timeout = 5000);

	bool ready();

	 /**
     * 发起开始推流请求
     *
     * @room_info			房间信息
     * @para				推流参数
     * @param cb         在onSuccess参数中返回分享用的url列表, 详见liveUrl
     */
	void RequestMultiVideoStreamerStart(const TIMRoomInfo& room_info, const TIMStreamParam& para, TIMValueCallBack<TIMStreamRsp&> *cb);
	  /**
     * 发起结束推流请求
     *
	 * @room_info			房间信息
	 * @para				推流参数
	 * @channel_ids			RequestMultiVideoStreamerStart 返回的channel_id
     * @param cb			回调返回
     */
	void RequestMultiVideoStreamerStop(const TIMRoomInfo& room_info, const TIMStreamParam& para, const std::list<uint64_t>& channel_ids, TIMCallBack *cb);
	   /**
     * 发起开始录制请求
     *
	 * @room_info			房间信息
	 * @para				录制参数
     * @param cb
     */
	void RequestMultiVideoRecorderStart(const TIMRoomInfo& room_info, const TIMRecordParam& para, TIMCallBack* cb);
	   /**
     * 发起结束录制请求
     *
     * @param relation_id   讨论组ID
     * @param room_id	    房间ID
     * @param signature		签名
     * @param cb
     */
	void RequestMultiVideoRecorderStop(const TIMRoomInfo& room_info, const TIMRecordParam& para, TIMValueCallBack<std::list<std::string>&> *cb);


	/**
	 *  发送多人音视频邀请
	 *
	 *  @param bussType 业务类型
	 *  @param authType 鉴权类型
	 *  @param authid  鉴权ID
	 *  @param requestType:
	 *  1-----发起发发起音视频邀请
		2-----发起方取消音视频邀请
		3-----接收方接受音视频邀请
		4-----接收方拒绝音视频邀请
	 *  @param receivers  向这些人发送邀请
	 */
	void RequestVideoInvitation(int bussType, int authType, int auth_id, int requestType, std::list<TIMUser>& receivers, TIMCallBack* cb);

    /**
     * 发起质量上报请求(internal)
     * @param type 业务类型
     * @param data 模块自定义的上报内容
     * @param cb 回调接口
     */
	void RequestQualityReport(int type, std::string& data, TIMCallBack* cb);

	/**
	* 音视频请求测速
	*
	* @param bussi_type 业务类型
	* @param auth_type  鉴权类型
	* @param cb         回调接口
	*/
	void RequestMeasureSpeed(uint16_t bussi_type, uint16_t auth_type, TIMCallBack* cb);
private:
	bool ready_;
};

}

#endif
