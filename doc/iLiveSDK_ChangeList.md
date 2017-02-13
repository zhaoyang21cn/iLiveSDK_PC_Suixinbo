## PC_iLiveSDK_ChangeList

###### V1.0.0(2017-01-16)
* iLiveSDK第一个版本，实现互动直播主线流程以及主要接口的封装,并与已有的Android、IOS平台实现互通;
* 主线流程：包括注册，登录，创建房间，加入房间，退出房间，推流、录制;
* 主要接口：请求/取消画面，相机，麦克风，扬声器相关操作，角色、权限修改，群组消息、C2C消息收发，推流、录制相关操作;

###### V1.2.0(2017-02-13)
* 更新avsdk1.8.5;
* 增加美白、美颜、屏幕分享过程中动态修改分享区域大小接口;
* 接口变动:
	(1) iLiveRoomOption.h: iLiveRoomDisconnectListener 函数指针添加errorinfo字段;
	(2) iLiveRoomOption.h: iLiveRoomOption结构体添加字段screen_recv_mode;
	(3) iLiveRoomMgr.h: requestViewList、cancelViewList、cancelAllView 接口返回值由int改为void;
	(4)	iLiveRoomMgr.h: 增加changeScreenShareSize接口;
	(5)	iLiveRoomMgr.h: openScreenShare接口参数改为引用方式;