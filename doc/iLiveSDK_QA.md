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

## Qt项目发布问题
Qt项目在发布程序时，需要将使用到的Qt库一并带上，比如下图错误，就是因为缺少platforms下的qwindows.dll,
![](https://mc.qcloudimg.com/static/img/d02789098baddec63c21cd7102793805/image.png)
此时，可以将qt安装目录下的platforms文件夹拷贝到运行目录下,具体做法参考[随心播的运行包](http://dldir1.qq.com/hudongzhibo/git/iLiveSDK_PC_Suixinbo/suixinbo_run.zip);
如果是Qt比较新的版本(如5.8.0)，qt自带了部署工具windeployqt.exe，使用方法如下图,
![](https://mc.qcloudimg.com/static/img/a5a569f419220aa4b161697bd8126fec/image.png)
此命令，即可将指定exe依赖的所有qt库复制到exe所在目录;