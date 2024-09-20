# Esp32-cam Folder Guide

#### 运行esp32-cam代码使用[Arduino](./Ardrino.md)

- data: 存放图像
- Collect_Images_for_EdgeImpulse: 目前实现收集图像s
- torch_model: pytorch训练模型,由于训练结果较大并且范围太过于大,暂存备用
- check.cpp: esp32 --usart--> STM32  实现报文的包装伪代码逻辑


``` bash
返回报文格式: [0xAA,0xAA,0x01,x,y,w,h,0x01,0x00] 9字节
    防止其余HC设备发送相同频率的信号串台，加入一个简易的双重验证

1: head: 2字节      判断0xAA == 0xAA
2: data: 5字节      { 1:是否有人体; x,y,w,h: 人体相对的坐标 }
3: tail: 2字节      (0x01) && (!0x00)

```

#### 训练模型的简易思路和方式来源于 https://www.youtube.com/watch?v=bZIKVaD3dRk
#### 使用https://studio.edgeimpulse.com/来训练模型
#### 训练集来自于网络下载和拍摄内容(70%-30%)