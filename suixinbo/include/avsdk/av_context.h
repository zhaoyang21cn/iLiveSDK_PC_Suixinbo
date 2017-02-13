#pragma once

#include "av_callback.h"
#include "av_common.h"
#include "av_room_multi.h"
#include "av_device_mgr.h"
#include "av_audio_ctrl.h"
#include "av_video_ctrl.h"
#include "av_spear_engine_ctrl.h"

#ifdef WIN32
#include "av_device_test.h"
#endif

namespace tencent {
namespace av {

/*
sdk_version = 1.8.5.3;
主版本号 . 子版本号 [ 修正版本号 [. 编译版本号 ]]
英文对照 : Major_Version_Number.Minor_Version_Number[Revision_Number[.Build_Number]]
示例1：1.2.0.1234
*/
#define MAJOR_VERSION   1 ///< SDK的主版本号
#define MINOR_VERSION   8 ///< SDK的子版本号
#define REVISION_NUMBER 5 ///< SDK的修订版本号

/**
@brief AVContext对象代表着一个SDK运行实例。

@details AVContext对内负责管理SDK的工作线程，控制各种内部对象的生命周期；
  对外提供了一系列的接口方法，App可以通过AVContext的成员函数进一步访问SDK的其他对象。
*/
class AV_EXPORT AVContext {
protected:
    virtual ~AVContext() {}

public:
    /**
    @brief 获得SDK的版本信息。

    @return SDK的版本号信息由四个数字组成，数字间以小数点分隔，四个数字的含义依次是：
      - 主版本号
      - 子版本号
      - 修订版本号
      - 编译版本号

    @remark SDK在特性变化和Bug修复之后，会升级版本信息重新发布。
    */
    static const char* GetVersion();

    /**
    @brief AVContext::CreateInstance()的入参。

    @details Config结构体包含了创建AVContext对象所需的配置信息。
    */
    struct StartParam {
        /// 默认构造函数。
        StartParam() {
            sdk_app_id = 0;
            engine_ctrl_type = SPEAR_ENGINE_CTRL_TYPE_CLOUD;
        }

        int32 sdk_app_id; ///< 腾讯为每个使用SDK的App分配的AppId。
        std::string account_type; ///< 腾讯为每个接入方分配的账号类型。
        std::string app_id_at3rd; ///< App使用的OAuth授权体系分配的AppId。
        std::string identifier; ///< 帐号名(用户名)。
        SpearEngineCtrlType engine_ctrl_type; ///< Spear引擎参数设置方式，默认为SPEAR_ENGINE_CTRL_TYPE_CLOUD。
    };

    /**
    @brief 创建AVContext对象。

    @details App使用SDK总是从CreateContext()开始的，该静态成员函数返回一个新的AVContext实例。

    @param [in] config 创建AVContext所需的配置信息。

    @return 成功则返回AVContext的实例指针；否则返回NULL。

    @remark
      - 创建成功之后，APP需要进一步调用StartContext()来启动AVContext对象。
      - APP必须保证AVContext实例的唯一性，同时创建多个AVContext实例可能会因为设备占用等方面的原因，出现无法预料的结果。
      - 由AVContext::CreateInstance()创建的AVContext对象必须调用AVContext::Destroy()来销毁。
    */
    static AVContext* CreateInstance();

    /**
    @brief 销毁AVContext对象。

    @details APP通过此方法来销毁由AVContext::CreateInstance()创建的AVContext对象。

    @remark APP应该设法保证AVContext::CreateInstance()和AVContext::Destroy()的配对调用。
    */
    virtual void Destroy() = 0;

    /// AVContext的状态类型。
    enum State {
        STATE_STOP = 0,     ///< 初始状态，AVContext::CreateInstance()成功之后，调用AVContext::Stop()之后均为此状态。
        STATE_START_ING,    ///< 正在启动，APP调用AVContext::Start()之后，AVContext会从STATE_STOP切换到此状态。
        STATE_START_OK,     ///< 已经启动，AVContext::Start()结束之后，AVContext会从STATE_START_ING切换到此状态。
    };
    virtual State GetState() = 0;

    /**
    @brief StartContext()的回调函数。

    @details 此函数是和StartContext()一起使用的回调函数，用来异步返回执行结果。

    @param result 错误码：
      \n AV_OK 执行成功；
      \n AV_ERROR_INITSDKFAIL 一般原因为鉴权失败。
    @param custom_data 值等于调用StartContext()时的入参custom_data。
    */
    typedef void (*StartCompleteCallback)(int32 result, const std::string& desc, void* custom_data);

    /**
    @brief 启动AVContext。

    @details AVContext::Start()是一个异步操作，内部会启动工作线程，创建各种内部对象。

    @param [in] param StartParam包含了启动AVContext所需要的各个参数。
    @param [in] callback 回调接口，SDK通过它向APP返回异步操作的结果。

    @retval AV_OK 启动成功。
    @retval 其他值 启动失败。

    @remark
      - 只有当异步操作启动成功的时候，才会通过回调函数异步返回执行结果。
      - 当异步操作启动失败的时候，直接通过StartContext()的返回值返回错误，不会再触发回调函数。
      - App收到StartCompleteCallback回调的时候，表示StartContext()执行完毕。
      - AVContext::Start()执行成功之后，App才能进一步调用AVContext的其他成员函数。
      - AVContext::Start()执行成功之后，App必须调用AVContext::Stop()来终止AVContext对象。

    @attention 以下两点约定也适用于SDK的其他异步操作接口：
      -# 只有当异步操作启动成功的时候，才会通过回调函数异步返回执行结果；
      -# 当异步操作启动失败的时候，直接通过StartContext()的返回值返回错误，不会再触发回调函数。
    */
    virtual void Start(const StartParam& param, AVCallback* callback) = 0;
    /**
    @brief 终止AVContext对象。

    @details Stop()是一个同步操作，内部会终止工作线程，销毁各种内部对象。

    @return 返回值表示操作是否成功。

    @retval AV_OK 启动成功。
    @retval 其他值 启动失败。

    @remark
      - App应该设法保证AVContext::Start()和AVContext::Stop()的配对调用；
      - AVContext::Stop()内部如果判断到当前还没退出音视频房间，会自动调用ExitRoom()；
      - AVContext::Stop()执行成功之后，App必须调用AVContext::Destroy()来销毁AVContext对象。
    */
    virtual int32 Stop() = 0;

    /**
    @brief 进入音视频房间。

    @details EnterRoom()是一个异步操作，内部会连接服务器，申请进入音视频房间。

    @param [in] room_delegate 房间委托对象：
      \n 进入多人房间，必须传递AVRoomMulti::Delegate类型的委托对象。
    @param [in] param 进入房间所需的参数：
      \n 进入多人房间，必须传递AVRoomMulti::EnterParam类型的参数。

    @return 返回值表示异步操作启动是否成功；
      异步操作执行结果通过入参room_delegate的OnEnterRoomComplete()返回。

    @retval AV_OK 启动成功。
    @retval AV_ERR_CONTEXT_NOT_STARTED StartContext()没有执行成功。
    @retval AV_ERR_ALREADY_EXISTS 没有退出上一个音视频房间。
    @retval AV_ERR_INVALID_ARGUMENT 委托或房间配置信息为空，或者委托和房间类型不匹配。

    @remark EnterRoom()必须在StartContext()执行成功之后调用才有效。
      目前同一时刻只支持进入一个音视频房间，所以：
      - 调用EnterRoom()之前，必须先退出上一个音视频房间；
      - 如果当前AVContext中已经存在一个音视频房间，调用EnterRoom()会同步返回失败。

    @attention Windows版本的SDK暂时没有开放双人音视频房间的能力。
    */
    virtual void EnterRoom(AVRoomMulti::Delegate* room_delegate, const AVRoomMulti::EnterParam& param) = 0;

    /**
      @brief 平滑切换房间。

      @details SwitchRoom()是一个异步操作，内部会在不释放音视频设备的情况下连接
               服务器切换音视频房间，此切房方案相较于此前的方案"退旧房进新房",速度上会快很多。

      @param [in] relationId 业务侧的房间id

      @return 异步操作执行结果通过入参room_delegate的OnSwitchRoomComplete()返回。
    */
    virtual void SwitchRoom(int relationId) = 0;

    /**
    @brief 退出音视频房间。

    @details ExitRoom()是一个异步操作，内部会连接服务器，申请退出音视频房间。

    @return 返回值表示异步操作启动是否成功；
      异步操作执行结果通过EnterRoom()入参room_delegate的OnRoomExitComplete()返回。

    @retval AV_OK 启动成功。
    @retval 其他值 启动失败。
    */
    virtual int ExitRoom() = 0;

    /// 获得当前房间的状态。
    virtual AVRoomMulti::State GetRoomState() = 0;

    /**
    @brief 获得AVRoom对象。

    @details EnterRoom()执行成功之后，App可以通过此成员函数获得当前音视频房间对应的AVRoom对象。

    @return 如果EnterRoom()执行成功，则返回当前音视频房间对应的AVRoom对象；否则返回NULL。
    */
    virtual AVRoomMulti* GetRoom() = 0;

    /**
    @brief 获得AVAudioCtrl对象。

    @details StartContext()执行成功之后，App可以通过此成员函数获得AVAudioCtrl对象。

    @return 如果StartContext()执行成功，则返回AVAudioCtrl对象；否则返回NULL。
    */
    virtual AVAudioCtrl* GetAudioCtrl() = 0;

    /**
    @brief 获得音频对应的AVDeviceMgr对象。

    @details StartContext()执行成功之后，App可以通过此成员函数获得音频对应的AVDeviceMgr对象。

    @return 如果StartContext()执行成功，则返回音频对应的AVDeviceMgr对象；否则返回NULL。
    */
    virtual AVDeviceMgr* GetAudioDeviceMgr() = 0;

    /**
    @brief 获得AVVideoCtrl对象。

    @details StartContext()执行成功之后，App可以通过此成员函数获得指定的AVVideoCtrl对象。

    @return 如果StartContext()执行成功，则返回指定的AVVideoCtrl对象；否则返回NULL。
    */
    virtual AVVideoCtrl* GetVideoCtrl() = 0;

    /**
    @brief 获得视频对应的AVDeviceMgr对象。

    @details StartContext()执行成功之后，App可以通过此成员函数获得视频对应的AVDeviceMgr对象。

    @return 如果StartContext()执行成功，则返回视频对应的AVDeviceMgr对象；否则返回NULL。

    */
    virtual AVDeviceMgr* GetVideoDeviceMgr() = 0;

    /**
    @brief 获得AVCloudSpearEngineCtrl对象。

    @details StartContext()执行成功之后，App可以通过此成员函数获得视频对应的AVCloudSpearEngineCtrl对象。

    @return 仅当StartContext()执行成功之后，且Spear流控引擎模式为SPEAR_ENGINE_CTRL_TYPE_CLOUD返回有效对象； 否则返回NULL。
    */
    virtual AVCloudSpearEngineCtrl* GetCloudSpearEngineCtrl() = 0;

    /**
    @brief 获得AVCustomSpearEngineCtrl对象。

    @details StartContext()执行成功之后，App可以通过此成员函数获得视频对应的AVCustomSpearEngineCtrl对象。

    @return 仅当StartContext()执行成功之后，且Spear流控引擎模式为SPEAR_ENGINE_CTRL_TYPE_CUSTOM返回有效对象； 否则返回NULL。
    */
    virtual AVCustomSpearEngineCtrl* GetCustomSpearEngineCtrl() = 0;

#ifdef WIN32
    /**
    @brief 开始设备测试。


    @param [in] start_complete_callback 函数指针，指向App定义的回调函数。
    @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。

    @return 返回值表示异步操作启动是否成功；异步操作执行结果通过回调函数返回。

    @retval AV_OK 启动成功。
    @retval 其他值 启动失败。

    @remark
      - 只有当异步操作启动成功的时候，才会通过回调函数异步返回执行结果；
      - 当异步操作启动失败的时候，直接通过StartDeviceTest()的返回值返回错误，不会再触发回调函数；
      - App收到StartCompleteCallback回调的时候，表示StartDeviceTest()执行完毕；
      - StartDeviceTest()执行成功之后，App才能通过GetAVDeviceTest()获取AVDeviceTest对象进行具体的设备测试；
      - StartDeviceTest()执行成功之后，App必须调用StopDeviceTest()来停止设备测试及释放AVDeviceTest对象。
    - 设备测试操作与房间进出操作是互斥的。在设备测试过程中，不能进入房间；如果要进入房间，必须先停止设备测试。在房间中，不能进行设备测试；如果要进行设备测试，必须先退出房间。
    @attention 以下两点约定也适用于SDK的其他异步操作接口：
      -# 只有当异步操作启动成功的时候，才会通过回调函数异步返回执行结果；
      -# 当异步操作启动失败的时候，直接通过StartDeviceTest()的返回值返回错误，不会再触发回调函数。
    */
    virtual int32 StartDeviceTest(StartCompleteCallback start_complete_callback, void* custom_data = NULL) = 0;

    /**
    @brief 停止设备测试。

    @param [in] stop_complete_callback 函数指针，指向App定义的回调函数。
    @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。

    @return 返回值表示异步操作启动是否成功；异步操作执行结果通过回调函数返回。

    @retval AV_OK 启动成功。
    @retval 其他值 启动失败。

    @remark
      - App应该设法保证StartDeviceTest()和StopDeviceTest()的配对调用；
    - 设备测试操作与房间进出操作是互斥的。在设备测试过程中，不能进入房间；如果要进入房间，必须先停止设备测试。在房间中，不能进行设备测试；如果要进行设备测试，必须先退出房间。
    */
    virtual int32 StopDeviceTest(AVClosure stop_complete_callback, void* custom_data = NULL) = 0;

    /**
    @brief 获得AVDeviceTest对象。

    @details StartDeviceTest()执行成功之后，App可以通过此成员函数获得AVDeviceTest对象。

    @return 如果StartDeviceTest()执行成功，则返回AVDeviceTest对象；否则返回NULL。
    @remark
    - 设备测试操作与房间进出操作是互斥的。在设备测试过程中，不能进入房间；如果要进入房间，必须先停止设备测试。在房间中，不能进行设备测试；如果要进行设备测试，必须先退出房间。
    */
    virtual AVDeviceTest* GetDeviceTest() = 0;

    /**
    @brief 保存音视频编码数据。

    @details StartPreservingEncData执行成功之后，SDK将会把音视频编码数据保存起来。
    */
    virtual int StartPreservingEncData(const std::string& dir) = 0;

    /**
    @brief 停止保存音视频编码数据。

    @details StopPreservingEncData执行成功之后，SDK将停止保存音视频编码数据。
    */
    virtual int StopPreservingEncData() = 0;
#endif
};

} // namespace av
} // namespace tencent
