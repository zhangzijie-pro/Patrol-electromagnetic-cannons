# 定义模型
import torch
import torch.nn as nn
import torchvision.models as models

class CustomResNet(nn.Module):
    def __init__(self):
        super(CustomResNet, self).__init__()
        self.resnet = models.resnet18(pretrained=True)
        self.resnet.fc = nn.Linear(self.resnet.fc.in_features, 1)  # 二分类任务

    def forward(self, x):
        return torch.sigmoid(self.resnet(x))

model = CustomResNet()
