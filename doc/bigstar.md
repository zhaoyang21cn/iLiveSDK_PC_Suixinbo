## 大咖模式
大咖模式，是指先创建房间，主播和观众不分先后顺序加入房间;<br/>

1. 创建IM群组:<br/>
	首先，需要创建IM群组，管理员可以在PC、Android、IOS、WEB_IE、业务侧后台中的任意一个平台上进行IM群组的创建;
	这里推荐由业务侧服务器调用IM SDK的RESTAPI进行IM的创建和解散,见[RESTAPI文档](https://cloud.tencent.com/document/product/269/4029)
	
2. 主播和观众加入房间:<br/>
	主播和观众此时可以不分先后顺序加入房间，他们都调用iLiveSDK的joinRoom()接口，这里加入房间的iLiveRoomOption中需要填写groupId字段，表示要加入房间对于的IM群组ID，
	而且，所有人都需要有创建AV房间的权限，即authBits字段需要包含AUTH_BITS_CREATE_ROOM(权限位具体设置方法参考随心播),此时，第一个进入房间的人，会创建av房间，所有人退出av房间后，
	sdk会自动解散av房间;注意,此时主播和观众都不能调用createRoom()进行创建房间，会返回对应错误码;
	
3. 解散IM群组:<br/>
	业务侧服务器检测到房间内已经没人了，如随心播是通过心跳维护房间内成员的，此时，业务侧可以调用Rest API进行IM群组的解散;
	