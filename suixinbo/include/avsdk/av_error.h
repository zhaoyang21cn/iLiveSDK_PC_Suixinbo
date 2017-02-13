#pragma once


#include "av_ref_count.h"
#include <string>

namespace tencent {
namespace av {

// 成功。
const int32 AV_OK = 0;

/*
名称：AV_ERR_FAIL
取值：1
含义：一般错误。
原因：具体原因需要通过分析日志等来定位。
方案：分析日志。
*/
const int32 AV_ERR_FAIL = 1;

// 基础共用相关(1001 to 1100)

/*
名称：AV_ERR_REPETITIVE_OPERATION
取值：1001
含义：重复操作。
原因：已经在进行某种操作，再次去做同样的操作，则会产生这个错误。如已经在进入房间过程中，再去做进入房间的操作，就会产生这个错误。
方案：等待上一个操作完成后再进行下一个操作。
*/
const int32 AV_ERR_REPETITIVE_OPERATION = 1001;
static const char AV_ERR_INFO_REPETITIVE_OPERATION[] = "repetitive operation";

/*
名称：AV_ERR_EXCLUSIVE_OPERATION
取值：1002
含义：互斥操作。
原因：已经在进行某种操作，再次去做同类型的其他操作，则会产生这个错误。如在进入房间过程中，去做退出房间的操作，就会产生这个错误。
方案：等待上一个操作完成后再进行下一个操作。
*/
const int32 AV_ERR_EXCLUSIVE_OPERATION = 1002;
static const char AV_ERR_EXCLUSIVE_OPERATION_INFO[] = "exclusive operation";


/*
名称：AV_ERR_HAS_IN_THE_STATE
取值：1003
含义：已处于所要状态。
原因：对象已经处于所要状态，无需再操作。如设备已经打开，再次去打开，就返回这个错误码。
方案：由于已经处于所要状态，可以认为该操作已经成功，当作成功来处理。
*/
const int32 AV_ERR_HAS_IN_THE_STATE = 1003;
static const char AV_ERR_HAS_IN_THE_STATE_INFO[] = "just in the state";


/*
名称：AV_ERR_INVALID_ARGUMENT
取值：1004
含义：错误参数。
原因：调用SDK接口时，传入错误的参数，则会产生这个错误。如进入房间时，传入的房间类型不正确，就会产生这个错误。
方案：详细阅读API文档，搞清楚每个接口的每个参数的有效取值范围，确认哪些参数没有按照规范来取值，保证传入参数的正确性并进行相应的预防处理。
*/
const int32 AV_ERR_INVALID_ARGUMENT = 1004;
static const char AV_ERR_INVALID_ARGUMENT_INFO[] = "invalid argument";


/*
名称：AV_ERR_TIMEOUT
取值：1005
含义：操作超时。
原因：进行某个操作，在规定的时间内，还未返回操作结果，则会产生这个错误。多数情况下，涉及到信令传输的、且网络出问题的情况下，才容易产生这个错误。如执行进入房间操作时，30s后还没有返回进入房间操作完成的结果的话，就会产生这个错误。
方案：确认网络是否有问题，并尝试重试。
*/
const int32 AV_ERR_TIMEOUT = 1005;
static const char AV_ERR_TIMEOUT_INFO[] = "waiting timeout, please check your network";


/*
名称：AV_ERR_NOT_IMPLEMENTED
取值：1006
含义：功能未实现。
原因：调用SDK接口时，如果相应的功能还未支持，则会产生这个错误。
方案：暂不支持该功能，找其他替代方案。
*/
const int32 AV_ERR_NOT_IMPLEMENTED = 1006;
static const char AV_ERR_NOT_IMPLEMENTED_INFO[] = "function not implemented";


/*
名称：AV_ERR_NOT_ON_MAIN_THREAD
取值：1007
含义：没有在主线程中调用。
原因：大部分的SDK接口要求在主线程调用，如果业务侧调用SDK接口时，没有在主线程调用，则会产生这个错误。
方案：修改业务侧逻辑，确保在主线程调用SDK接口。
*/
const int32 AV_ERR_NOT_ON_MAIN_THREAD = 1007;
static const char AV_ERR_INFO_NOT_ON_MAIN_THREAD[] = "not on the main thread";

/*
名称：AV_ERR_RESOURCE_IS_OCCUPIED
取值：1008
含义：资源被占用。
原因：当需要用到某种资源，如摄像头、屏幕等，而这些资源已经被占用了，则会产生这个错误。
方案：确认具体要用到哪些资源，及这样资源被谁占用了，确保在正确的时机使用SDK相关功能以保证资源使用不冲突。
*/
const int32 AV_ERR_RESOURCE_IS_OCCUPIED = 1008;
static const char AV_ERR_RESOURCE_IS_OCCUPIED_INFO[] = "resource is occupied";

const int32 AV_ERR_CODE_FAIL                = 1009; ///< 编码失败
static const char AV_ERR_INFO_CODE_FAIL[]   = "code failed";

const int32 AV_ERR_DECODE_FAIL              = 1010; ///< 解码失败
static const char AV_ERR_INFO_DECODE_FAIL[] = "decode failed";

//enum Error {

//CONTEXT相关(1101 to 1200)
const int32  AV_ERR_CONTEXT_NOT_START = 1101; ///< AVContext没有启动
static const char AV_ERR_INFO_CONTEXT_NOT_START[] = "AVContext did not start";

const int32  AV_ERR_CONTEXT_NOT_STOP = 1102; ///< AVContext没有停止
static const char AV_ERR_INFO_CONTEXT_NOT_STOP[] = "AVContext did not stop";

//房间相关(1201 to 1300)
const int32  AV_ERR_ROOM_NOT_EXIST = 1201;///< 房间不存在。
static const char AV_ERR_ROOM_NOT_EXIST_INFO[] = "room not exist";

const int32  AV_ERR_ROOM_NOT_EXITED = 1202;///< 房间未退出。
static const char AV_ERR_ROOM_NOT_EXITED_INFO[] = "room not exited";

//设备相关(1301 to 1400)
const int32  AV_ERR_DEVICE_NOT_EXIST = 1301;///< 设备不存在。
static const char AV_ERR_DEVICE_NOT_EXIST_INFO[] = "device not exist";

//成员相关(1401 to 1500)
const int32  AV_ERR_ENDPOINT_NOT_EXIST = 1401;///< 房间成员不存在。
static const char AV_ERR_ENDPOINT_NOT_EXIST_INFO[] = "the endpoint not exist";

const int32  AV_ERR_ENDPOINT_HAS_NOT_VIDEO = 1402;///< 该成员没有上视频。
static const char AV_ERR_ENDPOINT_HAS_NOT_VIDEO_INFO[] = "the endpoint has no video";

//APPLogic相关(1501 to 1600)
const int32  AV_ERR_TINYID_TO_OPENID_FAILED = 1501;///< tiny id转换至identifier失败。
static const char AV_ERR_TINYID_TO_OPENID_FAILED_INFO[] = "failed to turn tiny id to identifier";

const int32  AV_ERR_OPENID_TO_TINYID_FAILED = 1502;///< identifier转换至tiny id失败。
static const char AV_ERR_OPENID_TO_TINYID_FAILED_INFO[] = "failed to turn identifier to tiny id";

#ifdef WIN32
//设备测试相关(1601 to 1700)
const int32  AV_ERR_DEVICE_TEST_NOT_EXIST = 1601;///< AVDeviceTest不存在。
static const char AV_ERR_DEVICE_TEST_NOT_EXIST_INFO[] = "AVDeviceTest not exist";

const int32  AV_ERR_DEVICE_TEST_NOT_STOPPED = 1602;///< AVDeviceTest未结束。
static const char AV_ERR_DEVICE_TEST_NOT_STOPPED_INFO[] = "AVDeviceTest not stopped";
#endif

//切换房间功能的状态码
const int32 AV_ERR_NOT_TRY_NEW_ROOM = 2001; ///< 没有尝试进入新房间，将停留在旧房间
static const char AV_ERR_NOT_TRY_NEW_ROOM_INFO[] = "not try new and stay in old room";

const int32 AV_ERR_TRY_NEW_ROOM_FAILED = 2002; ///< 尝试进入新房间，但失败了，旧房间也将关闭
static const char AV_ERR_TRY_NEW_ROOM_FAILED_INFO[] = "failed to enter new room and also exited old room";

//其他模块错误
/*********服务器错误**********/
const int32  AV_ERR_SERVER_FAIL = 10001; ///< 服务器返回一般错误
static const char AV_ERR_SERVER_FAIL_INFO[] = "server response error";

const int32  AV_ERR_SERVER_NO_PERMISSION = 10003; ///< 没有权限
static const char AV_ERR_SERVER_NO_PERMISSION_INFO[] = "server refused because of no permission";

const int32  AV_ERR_SERVER_REQUEST_ROOM_ADDRESS_FAIL = 10004; ///< 进房间获取房间地址失败
static const char AV_ERR_SERVER_REQUEST_ROOM_ADDRESS_FAIL_INFO[] = "request room server address failed";

const int32  AV_ERR_SERVER_CONNECT_ROOM_FAIL = 10005; ///< 进房间连接房间失败
static const char AV_ERR_SERVER_CONNECT_ROOM_FAIL_INFO[] = "connect room server failed";

const int32  AV_ERR_SERVER_FREE_FLOW_AUTH_FAIL = 10006; ///< 免流情况下，免流签名校验失败，导致进房获取房间地址失败
static const char AV_ERR_SERVER_FREE_FLOW_AUTH_FAIL_INFO[] = "free flow signature failed";
    
    
/*********imsdk错误**********/
const int32  AV_ERR_IMSDK_FAIL  = 6999;
static const char AV_ERR_IMSDK_FAIL_INFO[] = "imsdk return failed";

const int32  AV_ERR_IMSDK_TIMEOUT  = 7000;
static const char AV_ERR_IMSDK_TIMEOUT_INFO[] = "imsdk waiting timeout";

const int32  AV_ERR_UNKNOWN = 65536; ///< 未知错误
static const char AV_ERR_INFO_UNKNOWN[] = "unknown error";
//};

} // namespace av
} // namespace tencent
