## 自动巡航电磁炮

### [STM32f407](./img/STM32F407ZGT6.pdf)基于智能小车控制,进行雷达检测是否存在静止或者运动人体，esp32-cam摄像头锁定目标(可选择目标: 持枪恐怖分子, 存活的所有人, 拯救人质 其他需求可在ISSUES中探讨),然后针对相对坐标发射电磁炮或者目标过多投掷其他物体


| 目录名                 | 描述                     |
|-----------------------|--------------------------|
| STM32/| [智能小车+雷达+电磁炮充电放电发射](./STM32/readme.md)|
| ESP32_cam/| [摄像头识别目标与报文解析](./ESP32_cam/guide.txt)|


### [esp32-cam](https://lastminuteengineers.com/getting-started-with-esp32-cam/)
- 模型的训练使用了[edgeimpulse](https://studio.edgeimpulse.com/studio/517258/acquisition/training?page=1)更加契合于arduino的开发
- 信息传输使用usart通信
- [引脚图](./img/ESP32S3_Pinout.png)
- 简易的识别目标的课程指南可参考: https://www.youtube.com/watch?v=bZIKVaD3dRk 或者 https://circuitdigest.com/microcontroller-projects/object-recognition-using-esp32-cam-and-edge-impulse

### 雷达模块 LD2412
- 通过串口进行自定义串口通信内容来实现不同内容
- [LD2412 pdf](./img/LD2412.pdf)

### 蓝牙部分 HC-04
- 蓝牙部分通过usart通信与stm32f4相连
- 实现手机app远程操控
- 手机app开发方式:  1.Qt安卓开发  2. java安卓开发   3. 蓝牙apk下载后自定义[下载地址](https://doc.itprojects.cn/0015-zhishi.89c51/download/lanyatiaoshiqi.apk)



### 完成以上内容会加入GPS与高德地图导航的应用来实现自动巡航去完成任务