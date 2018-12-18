# 自定义Spear配置使用必读

## 简介
通常情况下，sdk登录时，会从腾讯云后台拉取Spear配置；但是，在网络不稳定情况下,可能拉取Spear配置失败；这种情况有两种解决方案:

1、使用login()接口指定默认Spear配置，即拉不到Spear配置时，使用设置的默认角色配置，详细用法见[默认Spear配置使用说明](https://github.com/zhaoyang21cn/iLiveSDK_PC_Suixinbo/blob/master/doc/defaultSpearCfg.md);

2、使用loginWithSpear()接口，设置完整的Spear配置，从而不再从腾讯云拉取Spear配置;

相对于第一种方案，第二种方案拥有完整的Spear配置,而不是拉不到Spear配置就统一使用默认角色，所以，推荐使用第二种方案，本文档主要讲解这种方式的用法;

## 使用方法

1. 拼spear配置地址:
```
http://conf.voice.qcloud.com/index.php?sdk_appid=1400027849&interface=Voice_Conf_Download&platform=0
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

3. 调用sdk的登录接口loginWithSpear(),将上一步所得字符串传入spearCfg参数即可;

4. 判断自定义Spear配置是否设置成功:

iLiveSDK有addEventHandler()接口，可以增加事件监听；可以在登录之前使用此接口设置事件监听，调用loginWithSpear()接口登录后，将会受到onSetSpearConfigEvent()事件通知，事件通知中的result参数为NO_ERR，即表示成功;

## 注意事项
1. 请勿手动修改上面从腾讯拉取的Spear配置字符串；如果要修改角色配置，建议从腾讯云Spear控制台修改，然后重新拉取;
2. 传入SDK的Spear配置中，第一个角色将会作为默认角色；如果进房时填写的角色(iLiveRoomOption::controlRole)不存在，将会使用默认角色;
