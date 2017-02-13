#pragma once

#include "av_common.h"
#include "av_device.h"

namespace tencent {
namespace av {

/**
@brief 设备管理器的封装类。

@details AVContext::StartContext()执行成功之后，App可以：
  - 通过AVContext::GetAudioDeviceMgr()获得音频对应的AVDeviceMgr对象；
  - 通过AVContext::GetVideoDeviceMgr()获得视频对应的AVDeviceMgr对象。
*/
class AV_EXPORT AVDeviceMgr {
protected:
    virtual ~AVDeviceMgr() {}

public:
    /**
    @brief SetDeviceOperationCallback()的回调函数。

    @details 此函数是和SetDeviceOperationCallback()一起使用的回调函数，用来异步返回设备操作的执行结果。
      大部分设备操作都包含异步执行流程。为了避免App设置大量的异步回调，SDK统一把所有设备的异步回调集中到一起。

    @param device_mgr 执行设备操作的AVDeviceMgr对象。
    @param operation 设备操作类型，详情见DeviceOperation的定义。
    @param device_id 操作对应的设备Id。
    @param result 错误码。
    @param custom_data 值等于调用SetDeviceOperationCallback()时的入参custom_data。

    @todo 说明哪些设备操作会触发这个回调。
    */
    typedef void (*DeviceOperationCallback)(AVDeviceMgr* device_mgr, AVDevice::DeviceOperation oper,
                                            const std::string& device_id,
                                            int32 result, void* custom_data);

    /**
    @brief 设置设备操作回调。

    @details App可以通过设置设备操作回调，在回调函数中获得设备操作的执行结果。

    @param [in] device_operation_callback 函数指针，指向App定义的回调函数，NULL表示取消回调。
    @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。
    */
    virtual void SetDeviceOperationCallback(DeviceOperationCallback device_operation_callback,
                                            void* custom_data = NULL) = 0;

    /**
    @brief SetDeviceChangeCallback()的回调函数。

    @details 此函数是和SetDeviceChangeCallback()一起使用的回调函数，用来通知App发生设备变更。

    @param device_mgr 发生设备变更的AVDeviceMgr对象。
    @param custom_data 值等于调用SetDeviceOperationCallback()时的入参custom_data。
    */
    typedef void (*DeviceChangeCallback)(AVDeviceMgr* device_mgr, void* custom_data);

    /**
    @brief 设置设备变更回调。

    @details App可以通过设置设备变更回调，在回调函数中处理设备变更。

    @param [in] device_change_callback 函数指针，指向App定义的回调函数，NULL表示取消回调。
    @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。

    @todo 补充说明何时会触发设备变更通知，如何处理设备变更通知。
    */
    virtual void SetDeviceChangeCallback(DeviceChangeCallback device_change_callback, void* custom_data = NULL) = 0;

    /**
    @brief SetDeviceDetectNotify()的回调函数。

    @details 此函数是和SetDeviceDetectNotify()一起使用的回调函数，用来通知App发生设备热插拔的通知。

    @param device_mgr 发生设备变更的AVDeviceMgr对象。
    @param info       热插拔的设备信息 具体可以查看DetectedDeviceInfo。
    @param pbSelect   当新插入设备时，这个值表示是否自动选上新的设备。
    当拔除设备时，这个值指的是第一个设备是否自动选上。
    这里可以根据info.isUsedDevice和info.isNewDevice做处理，如果这两个都是true的话，就代表当前使用的设备被拔掉。
    @param custom_data 值等于调用SetDeviceOperationCallback()时的入参custom_data。
    */
    typedef void (*OnDeviveDetectNotify)(AVDeviceMgr* device_mgr, DetectedDeviceInfo& info, bool* pbSelect,
                                         void* custom_data);
    /**

    @brief 设置设备热插拔通知回调。

    @details App可以通过设置设备热插拔通知回调，在回调函数中处理设备变更。注意当前仅PC和音频设备支持。
    当进入房间后，mic或扬声器插拔会触发这个回调。

    @param [in] notify 函数指针，指向App定义的回调函数，NULL表示取消回调。详细的说明请参考OnDeviveDetectNotify的注释
    @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。

    */
    virtual void SetDeviceDetectNotify(OnDeviveDetectNotify notify, void* custom_data = NULL) = 0;


    /**
    @brief 打开所有选中的输入设备。

    @details 同步返回结果。如果没有特别需要，App不需要调用此接口。平时在进入房间之后，SDK内部
        默认会打开所有选中的设备。

    @param [in] is_enable true打开，false关闭。
    */
    virtual void EnableInputDevice(bool is_enable = true) = 0;

    /**
    @brief 打开所有选中的输出设备。

    @details 同步返回结果。如果没有特别需要，App不需要调用此接口。平时在进入房间之后，SDK内部
      默认会打开所有选中的设备。

    @param [in] is_enable true打开，false关闭。
    */
    virtual void EnableOutputDevice(bool is_enable = true) = 0;

    /**
    @brief 输入设备是否打开。

    @return true表示打开，false表示没打开。
    */
    virtual bool IsInputDeviceEnabled() = 0;

    /**
    @brief 输出设备是否打开。

    @return true表示打开，false表示没打开。
    */
    virtual bool IsOutputDeviceEnabled() = 0;

    /**
    @brief 获得输入设备数量。

    @return 输入设备数量。
    */
    virtual int32 GetInputDeviceCount() = 0;

    /**
    @brief 获得输入设备。

    @param [in] index 设备索引，不能超过GetInputDeviceCount()。

    @return 成功返回AVDevice对象，超出索引返回NULL。
    */
    virtual AVDevice* GetInputDevice(int32 index) = 0;

    /**
    @brief 获得输出设备数量。

    @return 输出设备数量。
    */
    virtual int32 GetOutputDeviceCount() = 0;

    /**
    @brief 获取输出设备。

    @param [in] index 设备索引，不能超过GetOutputDeviceCount()。

    @return 成功返回AVDevice对象，超出索引返回NULL。
    */
    virtual AVDevice* GetOutputDevice(int32 index) = 0;

    /**
    @brief 选中/取消选中输入设备。

    @details 同步返回结果。App调用此方法选中/取消设备，SDK会自动在合适的时机打开/关闭设备。
      这里的时机主要分两种情况：
      - 未进入房间时，选中/取消选中设备不会产生任何变化。
      - 进入房间后，选中/取消选中设备会进行对应的打开/关闭设备。

      结果会通过SetDeviceOperationCallback()传入的device_change_callback进行通知。

    @param device_id 设备Id。
    @param [in] is_select true选中，false取消选中。

    @return AV_OK表示成功，其他返回值表示失败：
    */
    virtual int32 SelectInputDevice(const std::string& device_id, bool is_select = true) = 0;

    /**
    @brief 选中/取消选中输出设备。

    @details 同步返回结果。App调用此方法选中/取消设备，SDK会自动在合适的时机打开/关闭设备。
      这里的时机主要分两种情况：
      - 未进入房间时，选中/取消选中设备不会产生任何变化。
      - 进入房间后，选中/取消选中设备会进行对应的打开/关闭设备。

    结果会通过SetDeviceOperationCallback()传入的device_change_callback进行通知。

    @param device_id 设备Id。
    @param [in] is_select true选中，false取消选中。

    @return AV_OK表示成功，其他返回值表示失败。
    */
    virtual int32 SelectOutputDevice(const std::string& device_id, bool is_select = true) = 0;

    /**
    @brief 清空已选设备。

    @param is_output true停用输出设备，false停用输入设备。
    */
    virtual void ClearSelectedDevice(bool is_output) = 0;

    /**
    @brief 获得处于选中状态的输入设备数量。

    @return 输入设备数量。
    */
    virtual int32 GetSelectedInputDeviceCount() = 0;

    /**
    @brief 获取处于选中状态的输入设备。

    @param [in] index 设备索引。

    @return 成功返回索引对应的设备，否则返回NULL。
    */
    virtual AVDevice* GetSelectedInputDevice(int32 index) = 0;

    /**
    @brief 获取处于选中状态的输出设备数量。

    @return 输出设备数量。
    */
    virtual int32 GetSelectedOutputDeviceCount() = 0;

    /**
    @brief 获得处于选中状态的输出设备。

    @param index 设备索引。

    @return 成功则返回索引对应的设备，否则返回NULL。
    */
    virtual AVDevice* GetSelectedOutputDevice(int32 index) = 0;

    /**
    @brief 根据设备ID获取设备。

    @param [in] device_id 设备Id。

    @return 如果存在对应ID的设备，则返回设备，否则返回NULL。
    */
    virtual AVDevice* GetDeviceById(const std::string& device_id) = 0;

    /**
    @brief 根据设备类型获取设备。

    @param [in] device_type 设备类型。
    @param [out] device_array 设备列表。

    @return device_array对应的size。

    @remark device_array的内存由SDK内部分配，App在使用完device_array应该释放对应的内存。
    */
    virtual int32 GetDeviceByType(const std::string& device_type, AVDevice** device_array[]) = 0;

    /**
     @brief 根据设备ID获取设备状态。

     @param [in] device_id 设备id。

     @return 设备对应的状态。
     AV_AUDIO_CLOSE                 = 0,
     AV_AUDIO_OPEN                  = 1,
     AV_AUDIO_OPREATIING            = 2,
     AV_AUDIO_DEVICE_NOT_EXIST      = 3,
     */
    virtual int32 GetDeviceState(const std::string& device_id) = 0;
};

} // namespace av
} // namespace tencent