
简介：iLiveSDK(全称:Interactive Live SDK)整合了互动直播SDK(AVSDK)、即时通讯SDK(IMSDK)两大模块，致力于提供一套完整的音视频即时通讯解决方案，打造跨平台一对多，多对多的酷炫直播场景。iLiveSDK旨在无限可能的降低用户接入成本，从用户角度考虑问题，全方位考虑用户接入体验，并提供接入服务专业定向支持，为用户应用上线保驾护航，本文档目的在于帮助用户快速接入使用iLiveSDK，达到主播端画面本地渲染，观众端可进入房间观看主播端画面的效果。

# iLiveSDK集成和使用
## 项目配置
- 将iLiveSDK文件夹复制到解决方案文件(.sln文件)所在的目录;
- 添加include目录:
	在项目的附加包含目录中添加include目录, $(SolutionDir)iLiveSDK\include,如下图,<br/>
![](http://mc.qcloudimg.com/static/img/3ab82b780f87b8749813f028a904ea0e/image.png)
- 添加库目录:
	在项目的附加库目录中添加lib文件所在目录,$(SolutionDir)iLiveSDK\libs\$(Configuration),如下图,<br/>
![](http://mc.qcloudimg.com/static/img/0fbd938dbbf189c40e195cb60689baf4/image.png)
- 包含头文件:
	在项目中包含头文件(通常是预编译头中),并使用相关命名空间，加载动态库的lib文件,diamante如下，

```C++
	#include <ilivesdk/ilivesdk.h>
	#pragma comment(lib, "ilivesdk.lib")
	using namespace imcore;
	using namespace tencent::av;
	using namespace ilivesdk;
```

- 拷贝dll文件到exe所在目录:
	将libs\Debug目录下的所有dll文件复制到项目的Debug版本运行目录下，libs\Release目录下的所有dll文件复制到项目的Release版本运行目录下;

- 验证是否配置成功:
	调用iLiveSDK::getInstance()->getVersion(),输出返回值，查看当前iLiveSDK的版本号;

## 基本接口调用示例
### 初始化
```C++
	int nRet = iLiveSDK::getInstance()->initSdk(appid, AccountType);
	if (nRet != ilivesdk::NO_ERR)
	{
		//初始化失败
	}
```
### 登录
```C++
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

