# 互动消息和上麦

## 1 发送消息

### 1.1 发送C2C消息

|接口名|接口描述|
|---|---|
|sendC2CMessage|发送C2C消息|

|参数类型|参数名|说明|
|---|---|---|
|string|dstUser|接收方id|
|TIMMessage|message|IM消息内容|
|SuccessCalllback|suc|发送消息成功回调|
|ErrorCallback|err|发送消息失败回调|
|void*|data|用户自定义数据的指针，在成功和失败的回调函数中原封不动地返回|

* 示例

```c++
void OnSendC2CMsgSuc( void* data )
{
  //发送C2C消息成功
}
void OnSendC2CMsgErr( int code, const std::string& desc, void* data )
{
  //发送C2C消息失败
}
TIMMessage message;
TIMTextElem textElem;
textElem.set_content( text );
message.AddElem(&textElem);
iLiveSDK::getInstance()->sendC2CMessage(  message, OnSendC2CMsgSuc, OnSendC2CMsgErr, NULL );
```

### 1.2 发送群消息
发送群消息是指发送消息到当前加入的房间内,所以必须要先加入房间;

|接口名|接口描述|
|---|---|
|sendGroupMessage|发送群消息|

|参数类型|参数名|说明|
|---|---|---|
|TIMMessage|message|消息内容|
|SuccessCalllback|suc|发送消息成功回调|
|ErrorCallback|err|发送消息失败回调|
|void*|data|用户自定义数据的指针，在成功和失败的回调函数中原封不动地返回|

* 示例

```c++
void OnSendGroupMsgSuc( void* data )
{
  //发送群消息成功
}
void OnSendGroupMsgErr( int code, const std::string& desc, void* data )
{
  //发送群消息失败
}
TIMMessage message;
TIMTextElem textElem;
textElem.set_content( text );
message.AddElem(&textElem);
iLiveSDK::getInstance()->sendGroupMessage(  message, OnSendGroupMsgSuc, OnSendGroupMsgErr, NULL );
```
