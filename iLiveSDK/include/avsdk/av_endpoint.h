#pragma once

#include "av_common.h"

namespace tencent {
namespace av {

/**
@brief 房间成员类。

@details 房间成员对象由SDK侧负责创建和销毁，业务侧不能创建和销毁它们，只能通过获取成员对象引用来使用它们。

@remark 建议业务侧不要一直持有成员对象引用，即显式地把成员对象引用保存到另一个容器，可以只在需要的时候再去重新获取它们即可。因为随着成员加入和退出房间，SDK侧会自动创建和销毁成员对象，如果业务侧一直持有成员对象引用，则可能持有的是一个已经被销毁的对象的引用，而使用这样的错误的引用很可能导致程序异常。
*/
class AV_EXPORT AVEndpoint {
protected:
    virtual ~AVEndpoint() {}

public:
    /// 房间成员信息。
    struct Info {
        Info()
            : sdk_version(0)
            , terminal_type(0)
            , has_audio(false)
            , is_mute(false)
            , has_camera_video(false)
            , has_screen_video(false)
            , has_media_video(false) {
        }

        virtual ~Info() {}

        std::string identifier; ///< 成员id。
        uint32 sdk_version; ///< SDK版本号。
        uint32 terminal_type; ///< 终端类型。
        bool has_audio; ///< 是否有发音频。
        bool is_mute; ///< 是否屏蔽这个成员的音频。这边的屏蔽是指会接收他的音频流，但不把其音频流送去解码和播放，也就听不到他的声音。
        bool has_camera_video; ///< 是否有发来自摄像头或外部视频捕获设备的视频。
        bool has_screen_video; ///< 是否有发来自屏幕的视频。
        bool has_media_video; ///< 是否有发来自播片的视频。
    };

    /**
    @brief RequestViewList()的回调函数。

    @brief RequestViewList()的回调函数，用来返回RequestViewList()的异步操作结果。

    @param identifier_list 成员id列表。
    @param view_list 视频画面参数列表。
    @param ret_code 返回码。
    @param custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。

    */
    typedef void (*RequestViewListCompleteCallback)(std::vector<std::string> identifier_list, std::vector<View> view_list,
            int32 result, const std::string& error_info, void* custom_data);

    /**
    @brief CancelAllView()的回调函数。

    @brief CancelAllView()的回调函数，用来返回CancelAllView()的异步操作结果。

    @param ret_code 返回码。
    @param custom_data 业务侧自定义的参数，会在执行回调函数时原封不动地返回给业务侧。由于回调函数通常是某个类的静态函数，可以通过该参数指定当前所对应的类的具体对象。
    */
    typedef void (*CancelAllViewCompleteCallback)(int32 result, const std::string& error_info, void* custom_data);

    /**
    @brief 获得成员id。

    @return 返回成员id。
    */
    virtual const std::string& GetId() const = 0;

    /**
    @brief 获得成员信息。

    @return 返回成员信息。
    */
    virtual const Info& GetInfo() const = 0;

    /**
    @brief 屏蔽成员音频。

    @details 屏蔽成员音频。这边的屏蔽是指会接收他的音频流，但不把其音频流送去解码和播放，也就听不到他的声音。

    @param is_mute 是否屏蔽。

    @return true表示操作成功，false表示操作失败。

    @remark 不支持控制房间其他成员是否发送音频，只支持控制是否屏蔽它们的音频。
    */
    virtual bool MuteAudio(bool is_mute = false) = 0;

    /**
    @brief 是否已屏蔽音频。

    @return true表示是，false表示否。
    */
    virtual bool IsAudioMute() = 0;

    /**
    @brief 是否正在发音频。

    @details 是否正在发音频。

    @return true表示是，false表示否。
    */
    virtual bool HasAudio() = 0;

    /**
    @brief 是否正在发来自摄像头或外部视频捕获设备的视频。

    @details 是否正在发来自摄像头或外部视频捕获设备的视频。

    @return true表示是，false表示否。
    */
    virtual bool HasCameraVideo() = 0;

    /**
    @brief 是否正在发来自屏幕的视频。

    @details 是否正在发来自屏幕的视频。

    @return true表示是，false表示否。
    */
    virtual bool HasScreenVideo() = 0;


    virtual bool HasMediaVideo() = 0;

	

};

} // namespace av
} // namespace tencent
