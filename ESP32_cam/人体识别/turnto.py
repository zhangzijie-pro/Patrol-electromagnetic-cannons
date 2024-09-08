import torch.nn as nn
import torchvision.models as models
import torch
import numpy as np

class CustomResNet(nn.Module):
    def __init__(self):
        super(CustomResNet, self).__init__()
        self.resnet = models.resnet18(pretrained=True)
        self.resnet.fc = nn.Linear(self.resnet.fc.in_features, 1)  # 二分类任务

    def forward(self, x):
        return torch.sigmoid(self.resnet(x))

model = CustomResNet()

# 加载模型权重（state_dict）
state_dict = torch.load('model.pth', map_location=torch.device('cpu'))
model.load_state_dict(state_dict)

# 遍历模型中的所有参数
weights_dict = {}
for name, param in model.named_parameters():
    weights_dict[name] = param.detach().cpu().numpy()

# 简单量化权重（将浮点数转为 8 位整数表示）
quantized_weights_dict = {}
for name, weights in weights_dict.items():
    # 量化到 8 位整数（0-255）
    quantized_weights_dict[name] = (weights * 255).astype(np.uint8)


def save_weights_to_header(quantized_weights_dict, header_file='model_weights.h'):
    with open(header_file, 'w') as f:
        f.write('#ifndef MODEL_WEIGHTS_H\n')
        f.write('#define MODEL_WEIGHTS_H\n\n')

        for layer_name, weights in quantized_weights_dict.items():
            # 将权重转换为 C 语言数组
            f.write(f'// Weights for layer {layer_name}\n')
            f.write(f'const unsigned char {layer_name}_weights[] = {{\n')

            # 将权重写入文件
            flattened_weights = weights.flatten()
            for i, weight in enumerate(flattened_weights):
                if i % 12 == 0:  # 每行最多显示12个元素
                    f.write('\n')
                f.write(f'{weight}, ')

            f.write('\n};\n\n')

        f.write('#endif // MODEL_WEIGHTS_H\n')


# 保存量化后的权重为 .h 文件
save_weights_to_header(quantized_weights_dict)

