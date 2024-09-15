import torch
import torchvision.transforms as transforms
from PIL import Image
import matplotlib.pyplot as plt
import cv2
import numpy as np
import torch.nn as nn
import torchvision.models as models

class CustomResNet(nn.Module):
    def __init__(self):
        super(CustomResNet, self).__init__()
        self.resnet = models.resnet18(pretrained=True)
        self.resnet.fc = nn.Linear(self.resnet.fc.in_features, 1)  # 二分类任务

    def forward(self, x):
        return torch.sigmoid(self.resnet(x))

# 初始化模型并加载权重
model = CustomResNet()
model.load_state_dict(torch.load(r'C:\Users\lenovo\Desktop\python\data\model_train_person.pth'))
model.eval()


def preprocess_image(image_path):
    transform = transforms.Compose([
        transforms.Resize((224, 224)),  # 修改为你的输入大小
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
    ])

    image = Image.open(image_path).convert('RGB')
    image = transform(image)
    image = image.unsqueeze(0)  # 增加一个 batch 维度
    return image


input_image_path = r'C:\Users\lenovo\Desktop\python\data\data\person\6.jpg'
image = preprocess_image(input_image_path)

with torch.no_grad():
    outputs = model(image)
    prediction = outputs.item()  # 获取预测值

threshold = 0.5
detected = prediction > threshold


def draw_bbox(image_path, detected, output_path='output_image.jpg'):
    # 读取原图像
    image = cv2.imread(image_path)

    if detected:
        # 这里是示例代码，实际应用中你需要调整边框位置和大小
        h, w, _ = image.shape
        start_point = (int(w * 0.1), int(h * 0.1))
        end_point = (int(w * 0.9), int(h * 0.9))
        color = (0, 255, 0)  # 绿色边框
        thickness = 2

        # 绘制矩形框
        cv2.rectangle(image, start_point, end_point, color, thickness)

    # 保存并显示图像
    cv2.imwrite(output_path, image)
    cv2.imshow('Detected Image', image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


draw_bbox(input_image_path, detected)

