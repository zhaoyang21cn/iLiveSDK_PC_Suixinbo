#pragma once

#include "av_common.h"

namespace tencent {
namespace av {

/**
@brief 音视频设备封装类的基类。

@details AVDevice提供了一系列操作和访问设备的接口。
  App总是通过AVContext的设备管理器来获取设备对象，无需手动创建/销毁AVDevice对象。

@todo Start()/Stop()/SetInfo()/SetSelect()是要删掉的。
@todo 有了GetInfo()，其他接口可以进一步精简。
*/
class AV_EXPORT AVDevice {
protected:
    virtual ~AVDevice() {}

public:
    /// 设备操作类型。
    enum DeviceOperation {
        DEVICE_OPERATION_UNKNOWN    = 0, ///< 默认值，无意义。
        DEVICE_OPERATION_OPEN       = 1, ///< 打开设备。
        DEVICE_OPERATION_CLOSE      = 2, ///< 关闭设备。
    };

    /// 设备基本信息。
    struct Info {
        /// 默认构造函数。
        Info() {}

        /// 拷贝构造函数。
        Info(const Info& other) {
            string_id = other.string_id;
            name = other.name;
            description = other.description;
        }

        virtual ~Info() {}

        std::string string_id; ///< 设备Id，可以作为多个设备间的唯一标识。
        std::string name; ///< 设备名称。
        std::string description; ///< 设备描述。
    };

    /**
    @brief 获得当前设备Id。

    @return 返回当前设备的Id。

    @remark 摄像头类Id为设备名，其他虚拟设备Id和Type同名。
    */
    virtual const std::string& GetId() const = 0;

    /**
    @brief 获得当前设备类型。

    @return 返回当前设备类型。

    @remark 设备类型是一个字符串，以下是几种典型设备的宏定义类型。

    @todo 补充宏定义的注释"\\video\\camera"、"\\media_file"、"\\audio\\mic"、"\\audio\\player"
    */
    virtual const std::string& GetType() const = 0;

    /**
    @brief 获取设备信息。

    @return 返回设备信息，详情见Info的定义。
    */
    virtual const Info& GetInfo() const = 0;

    /**
    @brief 设置设备信息。

    @remark 内部使用。
    */
    virtual void SetInfo(const Info& info) = 0;

    /**
    @brief 判断设备是否处于选中状态。

    @return false表示设备没有被选中，否则表示被选中。

    @remark 处于选中状态的设备会在音视频会话中使用。
    */
    virtual bool IsSelected() const = 0;

    /**
    @brief 选中设备

    @remark 处于选中状态的设备会在音视频会话中使用。
    */
    virtual void SetSelect(bool is_select = true) = 0;
};

} // namespace av
} // namespace tencent