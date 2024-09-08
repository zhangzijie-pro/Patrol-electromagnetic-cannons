# 训练模型区分有无人体存在

## 文件构成
- data 文件夹：图片
- - person 文件夹：图片中包含有人的
- - no_person 文件夹：图片中没有人的
- data_resized: 进行处理的图片模拟esp32-cam拍照
- deal_data.py: 处理图片 
- init.py: 初始化和预处理
- model.py：定义模型
- train.py：训练模型
- val.py：验证模型
- turnto.py: 将pth -> .h
- README.md：本文件
- model_train_person.pth: 训练结果
- model_weights.h: 转化后的.h
