#pragma once

#include "basictypes.h"

namespace tencent {
namespace av {

#define AV_ERROR(label, value) AV_ERR_##label = value,

/*
错误码表:名称/值/含义/原因/解决方案建议

******************************************客户端错误******************************************
名称：AV_ERR_FAILED
取值：1
含义：一般错误
原因：具体原因需要通过分析日志等来定位。
方案：分析日志。

名称：AV_ERR_REPEATED_OPERATION
取值：1001
含义：重复操作
原因：已经在进行某种操作，再次去做同样的操作，则会产生这个错误。如已经在进入房间过程中，再去做进入房间的操作，就会产生这个错误。
方案：等待上一个操作完成后再进行下一个操作。

备注：
操作类别主要有：AVContext类、房间类、设备类、成员类。
. AVContext类型的操作：StartContext/StopContext。
. 房间类型的操作：EnterRoom/ExitRoom。
. 设备类型的操作：打开/关闭某个设备。
. 成员类型的操作：请求画面/取消画面。

名称：AV_ERR_EXCLUSIVE_OPERATION
取值：1002
含义：互斥操作
原因：已经在进行某种操作，再次去做同类型的其他操作，则会产生这个错误。如在进入房间过程中，去做退出房间的操作，就会产生这个错误。
方案：等待上一个操作完成后再进行下一个操作。

名称：AV_ERR_HAS_IN_THE_STATE
取值：1003
含义：已处于所要状态
原因：对象已经处于某种状态，再去做使得它进入这种状态的操作时，则会产生这个错误。如已经在房间中，再去做进入房间的操作，就会产生这个错误。
方案：由于已经处于所要状态，可以认为该操作已经成功，当作成功来处理。

名称：AV_ERR_INVALID_ARGUMENT
取值：1004
含义：错误参数
原因：调用SDK接口时，传入错误的参数，则会产生这个错误。如进入房间时，传入的房间类型不正确，就会产生这个错误。
方案：详细阅读API文档，搞清楚每个接口的每个参数的有效取值范围，确认哪些参数没有按照规范来取值，保证传入参数的正确性并进行相应的预防处理。

名称：AV_ERR_TIMEOUT
取值：1005
含义：超时
原因：进行某个操作，在规定的时间内，还未返回操作结果，则会产生这个错误。多数情况下，涉及到信令传输的、且网络出问题的情况下，才容易产生这个错误。如执行进入房间操作时，30s后还没有返回进入房间操作完成的结果的话，就会产生这个错误。
方案：确认网络是否有问题，并尝试重试。

名称：AV_ERR_NOT_IMPLEMENTED
取值：1006
含义：未实现
原因：调用SDK接口时，如果相应的功能还未支持，则会产生这个错误。
方案：暂不支持该功能，找其他替代方案。

名称：AV_ERR_NOT_IN_MAIN_THREAD
取值：1007
含义：不在主线程
原因：SDK对外接口要求在主线程执行，如果业务侧调用SDK接口时，没有在主线程调用，则会产生这个错误。
方案：修改业务侧逻辑，确保在主线程调用SDK接口。

名称：AV_ERR_RESOURCE_IS_OCCUPIED
取值：1008
含义：资源被占用
原因：当需要用到某种资源，如摄像头、屏幕等，而这些资源已经被占用了，则会产生这个错误。
方案：确认具体要用到哪些资源，及这样资源被谁占用了，确保在正确的时机使用SDK相关功能以保证资源使用不冲突。

名称：AV_ERR_CONTEXT_NOT_EXIST
取值：1101
含义：AVContext对象未处于CONTEXT_STATE_STARTED状态
原因：当AVContext对象未处于CONTEXT_STATE_STARTED状态，去调用需要处于这个状态才允许调用的接口时，则会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_CONTEXT_NOT_STOPPED
取值：1102
含义：AVContext对象未处于CONTEXT_STATE_STOPPED状态
原因：当AVContext对象未处于CONTEXT_STATE_STOPPED状态，去调用需要处于这个状态才允许调用的接口时，则会产生这个错误。如不在这种状态下，去调用AVContext::DestroyContext时，就会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_ROOM_NOT_EXIST
取值：1201
含义：AVRoom对象未处于ROOM_STATE_ENTERED状态
原因：当AVRoom对象未处于ROOM_STATE_ENTERED状态，去调用需要处于这个状态才允许调用的接口时，则会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_ROOM_NOT_EXITED
取值：1202
含义：AVRoom对象未处于ROOM_STATE_EXITED状态
原因：当AVRoom对象未处于ROOM_STATE_EXITED状态，去调用需要处于这个状态才允许调用的接口时，则会产生这个错误。如不在这种状态下，去调用AVContext::StopContext时，就会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_DEVICE_NOT_EXIST
取值：1301
含义：设备不存在
原因：当设备不存在或者设备初始化未完成时，去使用设备，则会产生这个错误。
方案：确认设备是否真的存在，确保设备id填写的正确性，确保在设备初始化成功后再去使用设备。

名称：AV_ERR_ENDPOINT_NOT_EXIST
取值：1401
含义：AVEndpoint对象不存在
原因：当成员没有在发语音或视频时，去获取它的AVEndpoint对象时，就可能产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_ENDPOINT_HAS_NOT_VIDEO
取值：1402
含义：成员没有发视频
原因：当成员没有在发视频时，去做需要成员发视频的相关操作时，就可能产生这个错误。如当某个成员没有发送视频时，去请求他的画面，就会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_TINYID_TO_OPENID_FAILED
取值：1501
含义：tinyid转identifier失败
原因：当收到某个成员信息更新的信令时，需要去把tinyid转成identifier，如果IMSDK库相关逻辑存在问题、网络存在问题等，则会产生这个错误。
方案：确认网络是否存在问题，查看日志确认IMSDK相关逻辑是否存在问题。

名称：AV_ERR_OPENID_TO_TINYID_FAILED
取值：1502
含义：identifier转tinyid失败
原因：当调用StartContext接口时，需要去把identifier转成tinyid，如果IMSDK库相关逻辑存在问题、网络存在问题、没有处于登录态时等，则会产生这个错误。
方案：确认网络是否存在问题，查看日志确认IMSDK相关逻辑是否存在问题，确认已经成功调用IMSDK的登录接口。

名称：AV_ERR_DEVICE_TEST_NOT_EXIST
取值：1601
含义：AVDeviceTest对象未处于DEVICE_TEST_STATE_STARTED状态
原因：当AVDeviceTest对象未处于DEVICE_TEST_STATE_STARTED状态，去调用需要处于这个状态才允许调用的接口时，则会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_DEVICE_TEST_NOT_STOPPED
取值：1602
含义：AVDeviceTest对象未处于DEVICE_TEST_STATE_STOPPED状态
原因：当AVDeviceTest对象未处于DEVICE_TEST_STATE_STOPPED状态，去调用需要处于这个状态才允许调用的接口时，则会产生这个错误。如不在这种状态下，去调用AVContext::StopContext时，就会产生这个错误。
方案：修改业务侧逻辑，确保调用SDK接口的时机的正确性。

名称：AV_ERR_INVITE_FAILED
取值：1801
含义：发送邀请失败
原因：发送邀请时产生的失败。
方案：邀请模块只是用于DEMO演示方便用，对外暂不支持邀请功能，所以业务侧不需要处理这些错误码。

名称：AV_ERR_ACCEPT_FAILED
取值：1802
含义：接受邀请失败
原因：接受邀请时产生的失败。
方案：邀请模块只是用于DEMO演示方便用，对外暂不支持邀请功能，所以业务侧不需要处理这些错误码。

名称：AV_ERR_REFUSE_FAILED
取值：1803
含义：拒绝邀请失败
原因：拒绝邀请时产生的失败。
方案：邀请模块只是用于DEMO演示方便用，对外暂不支持邀请功能，所以业务侧不需要处理这些错误码。

******************************************后台错误******************************************
名称：AV_ERR_SERVER_FAILED
取值：10001
含义：一般错误
原因：具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_INVALID_ARGUMENT
取值：10002
含义：错误参数
原因：调用SDK接口时，或SDK内部发送信令给后台时，传了错误的参数，具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。
方案：确保调用SDK接口时所传的参数的正确性。分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_NO_PERMISSION
取值：10003
含义：没有权限
原因：没有权限使用某个功能，具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。如进入房间时所带的签名错误或过期，就会产生这个错误。
方案：确保在设置正确的权限参数后才去使用相应的功能。分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_TIMEOUT
取值：10004
含义：超时
原因：具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_ALLOC_RESOURCE_FAILED
取值：10005
含义：资源不够
原因：执行某些操作时，需要分配更多的资源(如内存)失败了，或者超过最大的资源限制(如超过最大的房间成员人数)，则会产生这个错误。
方案：具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。  分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_ID_NOT_IN_ROOM
取值：10006
含义：不在房间内
原因：在不在房间内时，去执行某些操作，则会产生这个错误。具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_NOT_IMPLEMENT
取值：10007
含义：未实现
原因：调用SDK接口时，如果相应的功能还未支持，则会产生这个错误。
方案：暂不支持该功能，找其他替代方案。

名称：AV_ERR_SERVER_REPEATED_OPERATION
取值：10008
含义：重复操作
原因：具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_ROOM_NOT_EXIST
取值：10009
含义：房间不存在
原因：房间不存在时，去执行某些操作，则会产生这个错误。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_ENDPOINT_NOT_EXIST
取值：10010
含义：成员不存在
原因：某个成员不存在时，去执行该成员相关的操作，则会产生这个错误。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

名称：AV_ERR_SERVER_INVALID_ABILITY
取值：10011
含义：错误能力
原因：具体原因需要通过分析日志确认后台返回给客户端的真正错误码才能知道。
方案：分析日志，获取后台返回给客户端的真正错误码，并联系后台同事协助解决。

*/

/**
@brief 常见错误码集合。

@details 常见错误码集合。
*/
enum Error {
  AV_OK = 0, ///< 成功

  /*********客户端错误**********/
  AV_ERR_FAILED = 1,///< 一般错误。

  //基础共用相关(1001 to 1100)
  AV_ERR_REPEATED_OPERATION = 1001,///< 重复操作。已经在进行某种操作，再次去做同样的操作，则返回这个错误。
  AV_ERR_EXCLUSIVE_OPERATION = 1002,///< 互斥操作。已经在进行某种操作，再次去做同类型的其他操作，则返回这个错误。
  AV_ERR_HAS_IN_THE_STATE = 1003,///< 已经处于所要状态，无需再操作。如设备已经打开，再次去打开，就返回这个错误码。
  AV_ERR_INVALID_ARGUMENT = 1004,///< 错误参数。
  AV_ERR_TIMEOUT = 1005,///< 操作超时。
  AV_ERR_NOT_IMPLEMENTED = 1006,///< 功能未实现。
  AV_ERR_NOT_IN_MAIN_THREAD = 1007,///< 不在主线程中执行操作。
  AV_ERR_RESOURCE_IS_OCCUPIED = 1008,///< 资源被占用。


  //CONTEXT相关(1101 to 1200)
  AV_ERR_CONTEXT_NOT_EXIST = 1101,///< AVContext不存在。
  AV_ERR_CONTEXT_NOT_STOPPED = 1102,///< AVContext未结束。

  //房间相关(1201 to 1300)
  AV_ERR_ROOM_NOT_EXIST = 1201,///< 房间不存在。
  AV_ERR_ROOM_NOT_EXITED = 1202,///< 房间未退出。

  //设备相关(1301 to 1400)
  AV_ERR_DEVICE_NOT_EXIST = 1301,///< 设备不存在。

  //成员相关(1401 to 1500)
  AV_ERR_ENDPOINT_NOT_EXIST = 1401,///< 房间成员不存在。
  AV_ERR_ENDPOINT_HAS_NOT_VIDEO = 1402,///< 该成员没有上视频。

  //APPLogic相关(1501 to 1600)
  AV_ERR_TINYID_TO_OPENID_FAILED = 1501,///< tiny id转换至identifier失败。
  AV_ERR_OPENID_TO_TINYID_FAILED = 1502,///< identifier转换至tiny id失败。

#ifdef WIN32
  //设备测试相关(1601 to 1700)
  AV_ERR_DEVICE_TEST_NOT_EXIST = 1601,///< AVDeviceTest不存在。
  AV_ERR_DEVICE_TEST_NOT_STOPPED = 1602,///< AVDeviceTest未结束。
#endif

  //邀请模块(1801 to 1900)。注意：邀请模块只是用于DEMO演示方便用，对外暂不支持邀请功能，所以业务侧不需要处理这些错误码。
  AV_ERR_INVITE_FAILED = 1801,///< 发送邀请失败。
  AV_ERR_ACCEPT_FAILED = 1802,///< 接受邀请失败。
  AV_ERR_REFUSE_FAILED = 1803, ///< 拒绝邀请失败。


  //其他错误
  /*********服务器错误**********/
  AV_ERR_SERVER_FAILED = 10001, ///< 服务器内部错误
  AV_ERR_SERVER_INVALID_ARGUMENT = 10002, ///< 服务器内部错误
  AV_ERR_SERVER_NO_PERMISSION = 10003, ///< 服务器内部错误
  AV_ERR_SERVER_TIMEOUT = 10004, ///< 服务器内部错误
  AV_ERR_SERVER_ALLOC_RESOURCE_FAILED = 10005, ///< 服务器内部错误
  AV_ERR_SERVER_ID_NOT_IN_ROOM = 10006, ///< 服务器内部错误
  AV_ERR_SERVER_NOT_IMPLEMENT = 10007, ///< 服务器内部错误
  AV_ERR_SERVER_REPEATED_OPERATION = 10008, ///< 服务器内部错误
  AV_ERR_SERVER_ROOM_NOT_EXIST = 10009, ///< 服务器内部错误
  AV_ERR_SERVER_ENDPOINT_NOT_EXIST = 10010, ///< 服务器内部错误
  AV_ERR_SERVER_INVALID_ABILITY = 10011, ///< 服务器内部错误
  AV_ERR_SERVER_UNKNOWN = 10999, ///<服务器未知错误

  //TODO
  //IMSDK内部错误
  ///*
  //ERR_SUCC = 0,
  AV_ERR_IMSDK_PARSE_RESPONSE_FAILED            = 6001,
  AV_ERR_IMSDK_SERIALIZE_REQ_FAILED             = 6002,
  AV_ERR_IMSDK_NO_SUCC_RESULT                   = 6003,
  AV_ERR_IMSDK_INVALID_CONVERSATION             = 6004,
  AV_ERR_IMSDK_LOADMSG_FAILED                   = 6005,
  AV_ERR_IMSDK_FILE_TRANS_AUTH_FAILED           = 6006,
  AV_ERR_IMSDK_FILE_TRANS_NO_SERVER             = 6007,
  AV_ERR_IMSDK_FILE_TRANS_UPLOAD_FAILED         = 6008,
  AV_ERR_IMSDK_FILE_TRANS_DOWNLOAD_FAILED       = 6009,
  AV_ERR_IMSDK_HTTP_REQ_FAILED                  = 6010,
  AV_ERR_IMSDK_TO_USER_INVALID                  = 6011,
  AV_ERR_IMSDK_REQUEST_TIMEOUT                  = 6012,
  AV_ERR_IMSDK_SDK_NOT_INITIALIZED              = 6013,
  AV_ERR_IMSDK_SDK_NOT_LOGGED_IN                = 6014,
  AV_ERR_IMSDK_IN_PROGESS                       = 6015,
  AV_ERR_IMSDK_UNKNOWN							= 6999,
  //*/
  /*
   * 网络错误
   */
  AV_ERR_SOCKET_TIMEOUT = 10201, ///< 服务器内部错误
  AV_ERR_UNKNOWN = 65536, ///< 无效值
};

} // namespace av
} // namespace tencent