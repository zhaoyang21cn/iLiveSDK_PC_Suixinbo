# iLiveSDK常见问题

## win32控制台程序收不到回调
iLiveSDK的回调依赖windows消息循环来抛回主线程,所以,程序中必须要有消息循环,且主线程不能阻塞，才能收到sdk的回调,即在main函数的末尾加上消息循环，如下,

```c++
MSG msg;
while( GetMessage(&msg, NULL, 0, 0) )
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}
```

## 收到打开摄像头事件，却收不到视频数据回调
建议用户在后台SPEAR上将“实时通信”模式改为“互动直播”模式，“实时通信”模式长时间未维护，可能有不稳定因素;

## 主播打开系统声音采集，连麦观众会听到自己的声音
打开系统声音采集接口openSystemVoiceInput()会采集整个系统的声音，主播端就会把连麦观众的声音也采集进去，所以，连麦观众会听到自己的回声;主播打开系统声音采集一般是为了伴奏，openSystemVoiceInput()接口有一个缺省参数，可以指定进程名字，这样就会只采集指定进程的声音;

## 指定某些窗口进行屏幕分享，采集不到窗口画面
有些应用程序的窗口，是直接使用DX\OpenGL进行绘制的，如，一些视频播放器等，sdk调用windows的接口会抓不到图像数据，属正常现象；如果一定要分享此类窗口，只能调用指定区域的屏幕分享，从显卡层抓取图像数据;

## 主播端上行分辨率和观众端收到的下行分辨率不一致
问题: 在腾讯云SPEAR上配置主播分辨率640\*368，主播收到的本地画面回调是640\*480，观众收到的画面是640\*368；<br/>
原因: windows上的摄像头一般不支持640\*368分辨率采集，主播端会按照摄像头最接近的分辨率(640\*480)采集,服务器收到上行数据后，会裁剪到SPEAR配置的分辨率(640\*368)下发给观众端;同样情况的分辨率还有960\*540，本地回调分辨是1024\*576;<br/>
解决办法: 在SPEAR上配置除640\*368、960\*540之外的分辨率；

## VS2010下编译随心播报错
VS2010+Qt5.0.0编译随心播，报错如下图，是因为Qt无法识别中文路径，需要将项目拷贝到非中文路径下;<br/>
![](https://main.qcloudimg.com/raw/c17c15775c21cd3d6624f150abfd19b3.png)

## Qt项目发布问题
Qt项目在发布程序时，需要将使用到的Qt库一并带上，比如下图错误，就是因为缺少platforms下的qwindows.dll,
![](https://mc.qcloudimg.com/static/img/d02789098baddec63c21cd7102793805/image.png)
<br/>此时，可以将qt安装目录下的platforms文件夹拷贝到运行目录下,具体做法参考[随心播的运行包](http://dldir1.qq.com/hudongzhibo/git/iLiveSDK_PC_Suixinbo/suixinbo_run.zip);
如果是Qt比较新的版本(如5.8.0)，qt自带了部署工具windeployqt.exe，使用方法如下图,<br/>
![](https://mc.qcloudimg.com/static/img/a5a569f419220aa4b161697bd8126fec/image.png)
<br/>
此命令，即可将指定exe依赖的所有qt库复制到exe所在目录;
