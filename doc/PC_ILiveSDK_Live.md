# iLiveSDK直播流程图：

![](http://mc.qcloudimg.com/static/img/06d2fb5027be53492249d4b81bd2f5a5/image.png)

# 1 初始化iLiveSDK
在应用启动时初始化iLiveSDK。

|接口名|接口描述|
|---|---|
|iinitSdk |iLiveSDK内部初始化，告知AppId.|

|参数类型|参数名|说明|
|---|---|---|
|int|appId|传入业务方appid|
|int|accountType|传入业务方 accountType|

*示例：
```c++
	int nRet = iLiveSDK::getInstance()->initSdk(appid, AccountType);
	if (nRet != ilivesdk::NO_ERR)
	{
		//初始化失败
	}
```
