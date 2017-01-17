#pragma once

#ifdef WIN32
#include "av_common.h"
#include "av_device.h"

namespace tencent {
namespace av {

/**
@brief 设备测试的封装类。

@details AVContext::StartContext()执行成功之后，App可以通过AVContext::GetDeviceTest()获得对应的AVDeviceTest对象。
*/
class AV_EXPORT AVDeviceTest {
  DISALLOW_EVIL_DESTRUCTIONS(AVDeviceTest)
 public:
  /**
  @brief SetDeviceOperationCallback()的回调函数。

  @details 此函数是和SetDeviceOperationCallback()一起使用的回调函数，用来异步返回设备操作的执行结果。
    大部分设备操作都包含异步执行流程。为了避免App设置大量的异步回调，SDK统一把所有设备的异步回调集中到一起。

  @param device_test 执行设备操作的AVDeviceTest对象。
  @param operation 设备操作类型，详情见DeviceOperation的定义。
  @param device_id 操作对应的设备Id。
  @param result 错误码。
  @param custom_data 值等于调用SetDeviceOperationCallback()时的入参custom_data。

  @todo 说明哪些设备操作会触发这个回调。
  */
  typedef void (*DeviceOperationCallback)(AVDeviceTest* device_test, AVDevice::DeviceOperation oper,
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
  @brief SetDeviceOperationCallback()的回调函数。

  @details 此函数是和SetDeviceOperationCallback()一起使用的回调函数，用来异步返回设备操作的执行结果。
    大部分设备操作都包含异步执行流程。为了避免App设置大量的异步回调，SDK统一把所有设备的异步回调集中到一起。

  @param device_test 执行设备操作的AVDeviceTest对象。
  @param operation 设备操作类型，详情见DeviceOperation的定义。
  @param device_id 操作对应的设备Id。
  @param result 错误码。
  @param custom_data 值等于调用SetDeviceOperationCallback()时的入参custom_data。

  @todo 说明哪些设备操作会触发这个回调。
  */
  typedef void (*DeviceDetectCallback)(AVDeviceTest* device_test, void* custom_data);

  /**
  @brief 设置设备操作回调。

  @details App可以通过设置设备操作回调，在回调函数中获得设备操作的执行结果。

  @param [in] device_operation_callback 函数指针，指向App定义的回调函数，NULL表示取消回调。
  @param [in] custom_data App指定的一个没有类型的指针，SDK会在回调函数中把该值回传给App。
  */
  virtual void SetCameraDeviceDetectCallback(DeviceDetectCallback device_detect_callback,
                                          void* custom_data = NULL) = 0;

  /**
  @brief 打开/关闭设备。

  @details 打开/关闭设备。

  @param device_id 设备Id。
  @param [in] is_enable true打开，false关闭。

  @return 返回值为AV_OK时表示已去执行系统的打开/关闭设备操作，并通过SetDeviceOperationCallback()传入的回调函数异步通知操作结果；其他返回值表示操作失败，不会执行前述的回调函数。
  */
  virtual int32 EnableDevice(const std::string& device_id, bool is_enable = true) = 0;

  /**
  @brief 根据设备ID获取设备。

  @param [in] device_id 设备Id。

  @return 如果存在对应ID的设备，则返回设备，否则返回NULL。
  */
  virtual AVDevice* GetDeviceById(const std::string& device_id) = 0;

  /**
  @brief 根据设备类型获取某种类型的设备个数。

  @param [in] device_type 设备类型。注意，支持设备测试的设备类型仅有DEVICE_MIC、DEVICE_PLAYER和DEVICE_CAMERA，也就是麦克风、扬声器和摄像头。

  @return 如果支持对应的设备类型，则返回该设备类型的设备个数，否则返回0。
  */
  virtual int32 GetDeviceCountByType(const std::string& device_type) = 0;

  /**
  @brief 根据设备类型获取设备id列表。

  @param [in] device_type 设备类型。注意，支持设备测试的设备类型仅有DEVICE_MIC、DEVICE_PLAYER和DEVICE_CAMERA，也就是麦克风、扬声器和摄像头。

  @return 该设备类型的设备id列表。
  */
  virtual std::vector<std::string> GetDeviceIdListByType(const std::string& device_type) = 0;

  /**
  @brief 根据设备类型获取设备名称列表。

  @param [in] device_type 设备类型。注意，支持设备测试的设备类型仅有DEVICE_MIC、DEVICE_PLAYER和DEVICE_CAMERA，也就是麦克风、扬声器和摄像头。

  @return 该设备类型的设备名称列表。
  */
  virtual std::vector<std::string> GetDeviceNameListByType(const std::string& device_type) = 0;

  /**
  @brief 根据设备类型获取设备。

  @param [in] device_type 设备类型。注意，支持设备测试的设备类型仅有DEVICE_MIC、DEVICE_PLAYER和DEVICE_CAMERA，也就是麦克风、扬声器和摄像头。
  @param [out] device_array 设备列表。

  @return device_array对应的size。

  @remark device_array的内存由SDK内部分配，App在使用完device_array应该释放对应的内存。
  */
  virtual int32 GetDeviceListByType(const std::string& device_type, AVDevice** device_array[]) = 0;
};
#endif
} // namespace av
} // namespace tencent