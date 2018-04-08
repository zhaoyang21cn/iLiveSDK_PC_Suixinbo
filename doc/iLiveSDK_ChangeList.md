## PC_iLiveSDK_ChangeList

###### V1.8.2.0(2018-04-08)
* 更新avsdk 1.9.8.2;
* 视频播放支持到720p;
* 允许指定创建房间所用的IM群类型;
* 登录接口增加默认spear配置参数;
* 去掉SkinBeauty.dll(此dll经常被360杀掉);

###### V1.8.1.10(2018-02-09)
* 获取设备列表为空时，统一返回错误码ERR_NOT_FOUND(8022);
* 增加获取麦克风\扬声器动态音量接口(getMicDynamicVolume\getPlayerDynamicVolume);
* SDK内部优化;

###### V1.8.1.6(2017-12-29)
* SDK默认不使用硬编解功能(解决偶现上下行异常问题);
* api接口注释修正;

###### V1.8.1.5(2017-12-21)
* 修正sdk不兼容xp系统问题;

###### V1.8.1.0(2017-12-11)
* 水印功能完善(增加setWaterMark接口，可以支持主路和辅路水印设置);
* BUG修正(打开关闭摄像头，偶现crash问题);

###### V1.8.0.0(2017-12-06)
* 升级到avsdk 1.9.6;
* 美颜功能优化;
* 增加房间内音频白名单功能;

###### V1.7.4.2(2017-12-04)
* 解决在部分电脑上无法获取摄像头列表问题;

###### V1.7.4.0(2017-11-27)
* iLiveRoomOption中增加硬编解码开关字段(enableHwEnc\enableHwDec\enableHwScreenEnc\enableHwScreenDec);
* 房间内直播质量数据详细化,[接口有改动](https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/iLiveSDK/README.md);

###### V1.7.3.0(2017-11-13)
* 增加跨房连麦接口;

###### V1.7.2.0(2017-11-06)
* 视频渲染模块，带角度的帧会花屏----BUG修正;
* 停止推流、停止录制接口,无法指定主路\辅路----BUG修正([接口有改动](https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/iLiveSDK/README.md));
* 推流接口参数配置，增加recordId(“客户端手动推流，自动录制”时，录制文件在后台可以用recordId来识别)，增加字段pushSvrType(推流server类型)，在当前版本中使用默认值。

###### V1.7.1.2(2017-10-30)
* 增加视频渲染模块;
* 增加本地视频录制接口;
* 增加音频数据回调接口;
* 增加测速接口;
* 系统声音采集，允许只采集某个进程的声音;
* 代码优化及bug修正(生成stats_report_pb_file_name_1509354510类型临时文件问题、大咖模式收不到群消息问题);

###### V1.7.0.0(2017-09-25)
* 升级到avsdk 1.9.5;
* 支持大咖模式(先创建房间，主播和观众不分先后顺序加入房间,[使用说明](https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/doc/bigstar.md));

###### V1.5.2.3(2017-09-13)
* 修正iLiveSDK接收消息时，偶现crash问题;
* 收到被踢下线回调时，sdk没有恢复到登出状态----bug修正;

###### V1.5.2.2(2017-09-12)
* 修正IM偶现crash问题;
* 增加网络连接监听接口(用于解决登录时偶现6012网络超时问题);

###### V1.5.2.1(2017-09-07)
* 断网重连后，无法加入房间----BUG修正;
* 断网重连后，需要1分钟左右才能开始接受消息----BUG修正
* IM偶现Crash问题----BUG修正;

###### V1.5.2.0(2017-09-01)
* 消息增加时间字段;
* 消息增加表情类型;
* 增加设备测试接口(允许进入房间前打开摄像头\麦克风\扬声器进行测试);
* SDK错误码规则统一;

###### V1.5.1.1(2017-08-10)
* RoomOption默认权限修改为拥有所有权限;
* 针对用户的反馈SDK内部做相应优化;

###### V1.5.1.0(2017-08-09)
* 增加权限配置功能,用户可以直接以连麦观众身份加入房间[(更新说明)](https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/iLiveSDK/README.md);
* 增加获取直播质量参数接口;
* 增加发送接收图片功能;
* 增加水印功能;
* 增加设备插拔监听接口;
* 增加设置sdk日志目录接口;
* 增加获取本地C2C历史消息接口;
* 增加纯音频推流录制功能;
* 代码优化及bug修正;

###### V1.5.0.0(2017-07-26)
* 升级到avsdk1.9.1;
* 增加文件播放功能;
* 所有设备操作修改为异步回调方式[(更新说明)](https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/iLiveSDK/README.md);
* 日志内容优化，日志文件统一生成到txsdklog目录下，日志定期清理;
* 修正遗留bug;

###### V1.4.1.0(2017-07-11)
* 修正1.4.0的bug;
* 增加系统声音采集功能;

###### V1.4.0.0(2017-07-03)
iLiveSDK接口重构,大大降低了sdk的接入难度，主要以下几方面优化,
* 支持VS的各个版本接入;
* 所有接口在主线程中进行回调;
* 用户不再需要手动请求画面,sdk可以自动请求画面;
* 美颜功能优化，大大提升美颜质量;

###### V1.3.1.0(2017-03-13)
* 增加自定义采集功能;
* 增加麦克风和扬声器音量控制接口;
* 内部优化;

###### V1.3.0.0(2017-03-06)
* 错误码优化;
* 命名空间优化;
* bug修正: 异常退出房间后，再次登录，会收到之前所在房间的消息;为修正此bug，对接口进行了如下修改: <br/>
	(1) SetConnCallBack()接口去掉;<br/>
	(2) SetForceOfflineCallback()接口移动到iLiveLoginMgr类里;<br/>
	(3) SetMessageCallBack()分解为setGroupMessageCallBack()、setC2CMessageCallBack()、setSysemMessageCallback()三个接口，并放到iLiveRoomMgr里面;

###### V1.2.2.0(2017-02-27)
* 代码注释修正;
* 内部实现优化;

###### V1.2.1.0(2017-02-20)
* iLiveSDK日志文件规范化;
* iLiveSDK自动清理日志文件(7天前);
* 增加屏幕分享指定窗口句柄的接口;
* iLiveRoomOption结构修改:<br/>
	(1) 增加m_autoRecvScreenListener成员;<br/>
	(2) 增加m_autoRecvMediaFileListener成员;<br/>
	(3) m_autoRecvListener成员改名为m_autoRecvCameraListener;<br/>

###### V1.2.0.0(2017-02-13)
* 更新avsdk1.8.5;
* 增加美白、美颜、屏幕分享过程中动态修改分享区域大小接口;
* 接口变动:<br/>
	(1) iLiveRoomOption.h: iLiveRoomDisconnectListener 函数指针添加errorinfo字段;<br/>
	(2) iLiveRoomOption.h: iLiveRoomOption结构体添加字段screen_recv_mode;<br/>
	(3) iLiveRoomMgr.h: requestViewList、cancelViewList、cancelAllView 接口返回值由int改为void;<br/>
	(4) iLiveRoomMgr.h: 增加changeScreenShareSize接口;<br/>
	(5) iLiveRoomMgr.h: openScreenShare接口参数改为引用方式;<br/>

###### V1.0.0.0(2017-01-16)
* iLiveSDK第一个版本，实现互动直播主线流程以及主要接口的封装,并与已有的Android、IOS平台实现互通;
* 主线流程：包括注册，登录，创建房间，加入房间，退出房间，推流、录制;
* 主要接口：请求/取消画面，相机，麦克风，扬声器相关操作，角色、权限修改，群组消息、C2C消息收发，推流、录制相关操作;
