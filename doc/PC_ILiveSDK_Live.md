# iLiveSDK直播流程图：

![](http://mc.qcloudimg.com/static/img/06d2fb5027be53492249d4b81bd2f5a5/image.png)

# 1 初始化iLiveSDK
在应用启动时初始化iLiveSDK。

|接口名|接口描述|
|---|---|
|initSdk|iLiveSDK内部初始化，告知appId.|

|参数类型|参数名|说明|
|---|---|---|
|int|appId|传入业务方appid|
|int|accountType|传入业务方 accountType|

* 示例：
```c++
int nRet = iLiveSDK::getInstance()->initSdk(appid, AccountType);
if (nRet != ilivesdk::NO_ERR)
{
	//初始化失败
}
```
# 2 账号登录
PC版iLiveSDK目前仅支持独立模式。

|接口名|接口描述|
|---|---|
|iLiveLogin|独立模式登录到腾讯云后台|

|参数类型|参数名|说明|
|---|---|---|
|string |szUserId|用户在独立模式下注册的帐号|
|string |szUserSig|用户在业务方后台获取到的签名|
|SuccessCalllback|suc|登录成功回调|
| ErrorCallback |err|登录失败回调|
|  void * |data |用户自定义的数据的指针，在成功和失败的回调函数中原封不动地返回 |


