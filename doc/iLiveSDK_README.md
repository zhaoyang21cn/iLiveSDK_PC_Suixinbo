
简介：iLiveSDK(全称:Interactive Live SDK)整合了互动直播SDK(AVSDK)、即时通讯SDK(IMSDK)两大模块，致力于提供一套完整的音视频即时通讯解决方案，打造跨平台一对多，多对多的酷炫直播场景。iLiveSDK旨在无限可能的降低用户接入成本，从用户角度考虑问题，全方位考虑用户接入体验，并提供接入服务专业定向支持，为用户应用上线保驾护航，本文档目的在于帮助用户快速接入使用iLiveSDK，达到主播端画面本地渲染，观众端可进入房间观看主播端画面的效果。

# iLiveSDK集成和使用
## 项目配置
- 将iLiveSDK文件夹复制到解决方案文件(.sln文件)所在的目录;
- 添加include目录:<br/>
	在项目的附加包含目录中添加include目录, $(SolutionDir)iLiveSDK\include,如下图,<br/>
![](http://mc.qcloudimg.com/static/img/3ab82b780f87b8749813f028a904ea0e/image.png)
- 添加库目录:<br/>
	在项目的附加库目录中添加lib文件所在目录,$(SolutionDir)iLiveSDK\libs\$(Configuration),如下图,<br/>
![](http://mc.qcloudimg.com/static/img/0fbd938dbbf189c40e195cb60689baf4/image.png)
- 包含头文件:<br/>
	在项目中包含头文件(通常是预编译头中),并使用相关命名空间，加载动态库的lib文件,代码如下，

```C++
	#include <ilivesdk/ilivesdk.h>
	#pragma comment(lib, "ilivesdk.lib")
	using namespace imcore;
	using namespace tencent::av;
	using namespace ilivesdk;
```

- 拷贝dll文件到exe所在目录:<br/>
	将libs\Debug目录下的所有dll文件复制到项目的Debug版本运行目录下，libs\Release目录下的所有dll文件复制到项目的Release版本运行目录下;

- 验证是否配置成功:<br/>
	调用iLiveSDK::getInstance()->getVersion(),输出返回值，查看当前iLiveSDK的版本号;

## 基本接口调用示例
### 设置基本回调函数
```c++
	void :OnLocalVideo( VideoFrame* video_frame, void* custom_data )
	{
		//video_frame是本地画面每一帧的数据,用户需要显示本地画面时，在此回调函数中做渲染，渲染代码可参考随心播;
	}
	void OnRemoteVideo( VideoFrame* video_frame, void* custom_data )
	{
		//video_frame是远程画面每一帧的数据,用户需要显示远程画面时，在此回调函数中做渲染，渲染代码可参考随心播;
	}
	iLiveSDK::getInstance()->SetMessageCallBack(&messageCallBack); //收到IM消息的回调;
	iLiveSDK::getInstance()->setLocalVideoCallBack(OnLocalVideo, NULL); //设置本地视频的回调函数;
	iLiveSDK::getInstance()->setRemoteVideoCallBack(OnRemoteVideo, NULL); //设置远程视频的回调函数;
```
### 初始化
```c++
	int nRet = iLiveSDK::getInstance()->initSdk(appid, AccountType);
	if (nRet != ilivesdk::NO_ERR)
	{
		//初始化失败
	}
```
### 登录
```c++
	void OniLiveLoginSuccess( void* data )
	{
		//登录成功
	}
	void OniLiveLoginError( int code, const std::string& desc, void* data )
	{
		//登录失败
	}
	iLiveSDK::getInstance()->LiveLogin(userId, userSig, OniLiveLoginSuccess, OniLiveLoginError, NULL);
```
### 创建房间(主播)
```c++
	void OniLiveCreateRoomSuc( void* data )
	{
		//创建房间成功
	}
	void OniLiveCreateRoomErr( int code, const std::string& desc, void* data )
	{
		//创建房间失败
	}
	
	iLiveRoomOption roomOption;
	roomOption.roomId = roomnum;//业务侧许保证房间id唯一性
	roomOption.auth_buffer = "";
	roomOption.control_role = "";//留空表示使用默认角色
	roomOption.audio_category = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//直播场景
	roomOption.video_recv_mode = VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO; //半自动模式
	roomOption.m_roomDisconnectListener = OnRoomDisconnect;
	roomOption.m_memberStatusListener = OnMemStatusChange;
	roomOption.m_autoRecvListener = OnSemiAutoRecvCameraVideo;
	roomOption.data = NULL;
	iLiveSDK::getInstance()->createRoom( roomOption, OniLiveCreateRoomSuc, OniLiveCreateRoomErr, NULL );
```
### 加入房间(观众)
```c++
	void OniLiveJoinRoomSuc( void* data )
	{
		//加入房间成功
	}
	void OniLiveJoinRoomErr( int code, const std::string& desc, void* data )
	{
		//加入房间失败
	}
	
	iLiveRoomOption roomOption;
	roomOption.roomId = roomnum;//要加入的房间ID	
	roomOption.auth_buffer = "";
	roomOption.control_role = "";
	roomOption.audio_category = AUDIO_CATEGORY_MEDIA_PLAY_AND_RECORD;//直播场景
	roomOption.video_recv_mode = VIDEO_RECV_MODE_SEMI_AUTO_RECV_CAMERA_VIDEO; //半自动模式
	roomOption.m_autoRecvListener = OnSemiAutoRecvCameraVideo;
	roomOption.m_memberStatusListener = OnMemStatusChange;
	roomOption.m_roomDisconnectListener = OnRoomDisconnect;
	roomOption.data = NULL;
	iLiveSDK::getInstance()->joinRoom( roomOption, OniLiveJoinRoomSuc, OniLiveJoinRoomErr, NULL );
```


