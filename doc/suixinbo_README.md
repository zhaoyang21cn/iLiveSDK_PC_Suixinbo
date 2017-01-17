
简介：PC随心播是基于iLiveSDK设计的简单直播demo,使用Qt作为界面库，实现了直播软件的基本功能，登录、注册、创建房间(主播)、加入房间(观众)、点赞、邀请上麦等功能；Android、IOS、PC三个平台的随心播实现了互通;目的是供用户作为使用iLiveSDK的参考;

# 随心播

## 随心播运行
  suixinbo_run.zip即为已经编译好的可执行包，解压后，直接双击运行suixinbo_Qt.exe即可；

## 随心播编译

### QT环境安装
PC版本的随心播使用的是QT做界面库开发的，所以需要先安装Qt 5.0.0,方可编译运行；可以去Qt的官网下载，也可以[点击这里下载](http://dldir1.qq.com/hudongzhibo/git/Qt/Qt_5.0.0.zip);下载解压后，文件目录如下，<br/>
![](QtDir)<br/>
先安装Qt5.0.0，再安装vs2010的Qt开发插件;安装完成后，重启VS2010，即可在vs的菜单栏中看到Qt菜单,如下图,<br/>
![](QtMenu)<br/>
此时,在Qt-->Qt Option菜单中可以查看本机已经安装的Qt版本，如下图![](Qtversion)<br/>
如果没有任何可用版本，点击add添加前面安装的Qt目录即可;至此，Qt安装完成;

### 随心播项目编译
使用vs2010打开suixinbo\sample目录下的suixinbo.sln,将suixinbo_Qt设为启动项目;Ctrl+F5编译执行随心播;如果出现以下错误,<br/>
![](noVersion)<br/>
解决方法如下,<br>
suixinbo_Qt项目上右键-->Qt Project Settings-->Version-->选择本机上安装的Qt5.0.0版本,如下图,<bt/>
![](version)
