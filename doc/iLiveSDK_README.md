# iLiveSDK集成

1. 将iLiveSDK文件夹复制到解决方案文件(.sln文件)所在的目录;
2. 添加include目录:<br/>
	在项目的附加包含目录中添加include目录, $(SolutionDir)iLiveSDK\include,如下图,<br/>
![](http://mc.qcloudimg.com/static/img/3ab82b780f87b8749813f028a904ea0e/image.png)
3. 添加库目录:<br/>
	在项目的附加库目录中添加lib文件所在目录,$(SolutionDir)iLiveSDK\libs,如下图,<br/>
![](https://mc.qcloudimg.com/static/img/413972c28bbaa2fbf4028b19e38ab0c2/pic.png)
4. 包含头文件:<br/>
	在项目中包含头文件(通常是预编译头中),并使用相关命名空间，加载动态库的lib文件,代码如下，

	```C++
	#include "iLive.h"
	using namespace ilive;
	#pragma comment(lib, "iLiveSDK.lib")
	```

5. 拷贝dll文件到项目工作目录:<br/>
	将libs目录下的所有dll文件复制到项目的工作目录下; 对于VS项目，如下图方式查看工作目录,
	![](https://mc.qcloudimg.com/static/img/e0c7c73d7096bed303ca4df5bf0abe98/pic.png)

6. 验证是否配置成功:<br/>
	调用GetILive()->getVersion(),输出返回值，查看当前iLiveSDK的版本号;




