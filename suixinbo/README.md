# 随心播

## 简介：
PC随心播是基于iLiveSDK设计的简单直播demo,使用Qt作为界面库，实现了直播软件的基本功能，登录、注册、创建房间(主播)、加入房间(观众)、点赞、邀请上麦等功能；Android、IOS、PC三个平台的随心播实现了互通;目的是供用户作为使用iLiveSDK的参考;

## 随心播运行
  点击[这里](http://dldir1.qq.com/hudongzhibo/git/iLiveSDK_PC_Suixinbo/suixinbo_run.zip)可以下载随心播编译好的可运行包，解压后，双击suixinbo_Qt.exe即可运行;

## 随心播编译

### QT开发环境配置
PC版本的随心播使用的是Qt做界面库开发的，所以需要先安装Qt,以及vs上进行Qt开发的插件,方可编译运行，下面以vs2015为例。

* Qt安装

Qt安装包,可以去Qt的[官网](http://download.qt.io/archive/qt/)下载对应VS版本的Qt，如下图,
![](https://mc.qcloudimg.com/static/img/dcaba630803943f425c0f40f9b5b59bd/pic.png)
名字为" qt-opensource-windows-x86-msvc2015-5.8.0.exe"的即为支持vs2015的安装包,进行下载安装。其中“msvc2015”表示支持vs2015的版本，x86表示32位版本的Qt(目前iLiveSDK只支持32位，所以，这里也必须下载32位版本的Qt,即时您的计算机系统是64位)；

* Qt开发插件安装

vs2010之后的版本，可以直接在VS中进行安装，操作步骤如下图,
![](https://mc.qcloudimg.com/static/img/e669d4451aca22173f8bf2ad67a894ab/pic.png)
![](https://mc.qcloudimg.com/static/img/da49e7fd3f853bfed5814369811188ed/pic.png)
此时，重启vs，菜单栏中将会出现如下菜单项,
![](https://mc.qcloudimg.com/static/img/cb5b67ec89f573185a5ce7fbbd85ac9a/pic.png)
此时，在vs中配置Qt目录，配置方法为，<br/>
"Qt VS Tools"菜单项-->Qt Options-->add-->选择Qt安装目录，如下图，
![](https://mc.qcloudimg.com/static/img/a6bfa24ca0c3ef8d39a289a4a120f4c0/pic.png)
增加好后，点击确定，如下图，
![](https://mc.qcloudimg.com/static/img/c5aacc84343bb566097960e1dd595339/pic.png)

注意:<br/>
VS2010下，直接在VS中搜索找不到Qt插件，需要在Qt官网下载Qt插件，或者从[这里](http://dldir1.qq.com/hudongzhibo/git/Qt/Qt_5.0.0.zip)下载Qt5.0.0及vs2010插件,然后进行手动安装；

### 随心播项目编译
使用VS打开suixinbo\sample目录下的suixinbo.sln，如果是vs2010之后的vs版本，会提示升级项目配置，点击"确定"；然后，在项目suixinbo_Qt上右键-->Qt Project Settings-->配置项目使用的Qt版本，配置好后，如下图,
![](https://mc.qcloudimg.com/static/img/1580d6b0287ea3ac8a88d81ee4d917c1/pic.png)
此时即可编译运行随心播了;

