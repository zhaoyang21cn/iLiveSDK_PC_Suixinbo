## 一 下载Demo
点击下载[PC Demo](https://github.com/zhaoyang21cn/iLiveSDK_PC_Demos)的代码。代码里包含一个示例：<br/>
1. 随心播代码在suixinbo目录下。演示了包括界面和后台交互的完整的直播流程。

## 二 安装Qt环境
随心播使用的是QT做界面库,在vs2010下开发的，所以需要先安装Qt 5.0.0,方可编译运行；可以去Qt的官网下载，也可以[点击这里下载](http://dldir1.qq.com/hudongzhibo/git/Qt/Qt_5.0.0.zip);下载解压后，文件目录如下，<br/>
![](http://mc.qcloudimg.com/static/img/00d8b25ddf3160c0673327568cd559fc/image.png)<br/>
先安装Qt5.0.0，再安装vs2010的Qt开发插件;安装完成后，重启VS2010，即可在vs的菜单栏中看到Qt菜单,如下图,<br/>
![](http://mc.qcloudimg.com/static/img/3422fe8496cd39d1b7d6c2b418460765/image.png)<br/>
此时,在Qt-->Qt Option菜单中可以查看本机已经安装的Qt版本，如下图,<br/>
![](http://mc.qcloudimg.com/static/img/435adc9eeb163e34bc4e602acfc900a1/image.png)<br/>
如果没有任何可用版本，点击add添加前面安装的Qt目录即可;至此，Qt安装完成;

## 三 运行
suixinbo_run.zip为已经编译好的可执行包，解压后，直接双击suixinbo_Qt.exe即可运行;如果用户需要自己编译，需要按照上面第二步所示先安装vs2010及Qt环境;编译中若出现以下错误,<br/>
![](http://mc.qcloudimg.com/static/img/c26848a45381ec52be2f119651dfedd0/image.png)<br/>
解决方法如下,<br>
suixinbo_Qt项目上右键-->Qt Project Settings-->Version-->选择本机上安装的Qt5.0.0版本,如下图,<br/>
![](http://mc.qcloudimg.com/static/img/b4a713a90cf513f0173c5bc556a1a09c/image.png)

## 四 集成到开发者自己的代码工程里

## 五 库类介绍


