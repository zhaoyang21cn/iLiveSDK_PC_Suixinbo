# 默认Spear配置使用说明

## 简介
通常情况下，sdk登录时，会从腾讯云后台拉取Spear配置；但是，在网络不稳定情况下,可能拉取Spear配置失败,这种情况，用户可以指定默认Spear配置;

## 使用方法

1. 拼spear配置地址:
```
http://conf.voice.qcloud.com/index.php?sdk_appid=1400028285&interface=Voice_Conf_Download&platform=1
//实际操作时，注意修改url中sdk_appid与platform(0--pc/web, 1--ios, 2--android, 4--mac)的值
```

2. 拿第1步地址到浏览器中访问，即可拿到腾讯云Spear配置的json字符串,例如,
```json
{
	"data": {
		"biz_id": 1400027849,
		"conf": [{
			"audio": {
				"aec": 1,
				"agc": 1,
				"ans": 1,
				"anti_dropout": 1,
				"au_scheme": 1,
				"channel": 1,
				"codec_prof": 4129,
				"frame": 20,
				"kbps": 30,
				"max_antishake_max": 1000,
				"max_antishake_min": 400,
				"min_antishake": 80,
				"sample_rate": 16000,
				"silence_detect": 1
			},
			"is_default": 0,
			"net": {
				"rc_anti_dropout": 1,
				"rc_init_delay": 250,
				"rc_max_delay": 900
			},
			"role": "LiveMaster",
			"type": 0,
			"video": {
				"anti_dropout": 0,
				"codec_prof": 5,
				"format": 1,
				"format_fix_height": 720,
				"format_fix_width": 1280,
				"format_max_height": -1,
				"format_max_width": -1,
				"fps": 30,
				"fqueue_time": -1,
				"live_adapt": 0,
				"maxkbps": 3000,
				"maxqp": -1,
				"minkbps": 2000,
				"minqp": -1,
				"qclear": 1,
				"small_video_upload": 0
			}
		}, {
			"audio": {
				"aec": 1,
				"agc": 1,
				"ans": 1,
				"anti_dropout": 1,
				"au_scheme": 1,
				"channel": 1,
				"codec_prof": 4129,
				"frame": 20,
				"kbps": 30,
				"max_antishake_max": 1000,
				"max_antishake_min": 400,
				"min_antishake": 80,
				"sample_rate": 16000,
				"silence_detect": 1
			},
			"is_default": 0,
			"net": {
				"rc_anti_dropout": 1,
				"rc_init_delay": 250,
				"rc_max_delay": 1000
			},
			"role": "LiveGuest",
			"type": 0,
			"video": {
				"anti_dropout": 0,
				"codec_prof": 5,
				"format": -2,
				"format_fix_height": 480,
				"format_fix_width": 640,
				"format_max_height": -1,
				"format_max_width": -1,
				"fps": 20,
				"fqueue_time": -1,
				"live_adapt": 0,
				"maxkbps": 1600,
				"maxqp": -1,
				"minkbps": 1200,
				"minqp": -1,
				"qclear": 1,
				"small_video_upload": 0
			}
		}, {
			"audio": {
				"aec": 1,
				"agc": 1,
				"ans": 1,
				"anti_dropout": 1,
				"au_scheme": 1,
				"channel": 1,
				"codec_prof": 4129,
				"frame": 20,
				"kbps": 30,
				"max_antishake_max": 1000,
				"max_antishake_min": 400,
				"min_antishake": 80,
				"sample_rate": 16000,
				"silence_detect": 1
			},
			"is_default": 0,
			"net": {
				"rc_anti_dropout": 1,
				"rc_init_delay": 1000,
				"rc_max_delay": 2000
			},
			"role": "Guest",
			"type": 0,
			"video": {
				"anti_dropout": 0,
				"codec_prof": 5,
				"format": 2,
				"format_fix_height": 480,
				"format_fix_width": 640,
				"format_max_height": -1,
				"format_max_width": -1,
				"fps": 25,
				"fqueue_time": -1,
				"live_adapt": 0,
				"maxkbps": 800,
				"maxqp": -1,
				"minkbps": 800,
				"minqp": -1,
				"qclear": 1,
				"small_video_upload": 0
			}
		}],
		"platform": 0,
		"scheme": 4,
		"sequence": 686
	},
	"errmsg": "success.",
	"retcode": 0
}
```

3. 对应sdkappid, windows平台下各角色的spear配置即为上述json数据conf标签对应的数组；例如，我们需要将Guest的配置设置为默认Spear配置，在上一步所得字符串中找到角色为Guest的一项，即为:
```json
{
	"audio": {
		"aec": 1,
		"agc": 1,
		"ans": 1,
		"anti_dropout": 1,
		"au_scheme": 1,
		"channel": 1,
		"codec_prof": 4129,
		"frame": 20,
		"kbps": 30,
		"max_antishake_max": 1000,
		"max_antishake_min": 400,
		"min_antishake": 80,
		"sample_rate": 16000,
		"silence_detect": 1
	},
	"is_default": 0,
	"net": {
		"rc_anti_dropout": 1,
		"rc_init_delay": 1000,
		"rc_max_delay": 2000
	},
	"role": "Guest",
	"type": 0,
	"video": {
		"anti_dropout": 0,
		"codec_prof": 5,
		"format": 2,
		"format_fix_height": 480,
		"format_fix_width": 640,
		"format_max_height": -1,
		"format_max_width": -1,
		"fps": 25,
		"fqueue_time": -1,
		"live_adapt": 0,
		"maxkbps": 800,
		"maxqp": -1,
		"minkbps": 800,
		"minqp": -1,
		"qclear": 1,
		"small_video_upload": 0
	}
}
```

4. 调用sdk的登录接口login()时,将上一步所得字符串传入spearCfg参数即可;

## 测试验证

为了进行验证，可以通过修改hosts文件，让系统无法访问conf.voice.qcloud.com拉取spear配置，具体做法为:<br/>
用记事本打开C:\Windows\System32\drivers\etc目录下的hosts文件，在最末尾加上一行
```
127.0.0.1	conf.voice.qcloud.com
```
此时,ping conf.voice.qcloud.com,将会是127.0.0.1地址响应，如下图所示,<br/>
![](https://mc.qcloudimg.com/static/img/6f901bcc483d7fb2e3ce15a9541f2632/2.png)
<br/>即已经无法访问conf.voice.qcloud.com拉取Spear配置了,此时即可运行程序验证是否为指定配置;

## 注意事项
程序使用配置的优先顺序为: <br/>
拉取的spear配置 > 本地缓存的默认配置 > 添加的默认配置 > AVSDK自带的默认配置（直播场景）
<br/>所以，在测试前，如果程序运行目录下，有“av_control_config_1400027849.config”类似的缓存配置文件，需要将此文件删除;
