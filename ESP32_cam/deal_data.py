from PIL import Image
import os

image_size = (400 x 296)

# 定义原始图片所在的文件夹和目标文件夹
source_folder = 'data'
target_folder = 'data_resized'

# 创建目标文件夹，如果它不存在的话
if not os.path.exists(target_folder):
    os.makedirs(target_folder)

# 定义要处理的子文件夹
subfolders = ['person', 'no_person']

# 遍历每个子文件夹
for subfolder in subfolders:
    # 定义完整的源文件夹路径和目标文件夹路径
    full_source_path = os.path.join(source_folder, subfolder)
    full_target_path = os.path.join(target_folder, subfolder)

    # 如果目标子文件夹不存在，则创建它
    if not os.path.exists(full_target_path):
        os.makedirs(full_target_path)

    # 遍历源文件夹中的所有文件
    for filename in os.listdir(full_source_path):
        # 检查文件是否是图片（这里我们假设图片文件有以下几种常见的后缀）
        if filename.lower().endswith(('.png', '.jpg', '.jpeg', '.bmp', '.gif')):
            # 打开图片
            img_path = os.path.join(full_source_path, filename)
            img = Image.open(img_path)

            # 调整图片大小
            img_resized = img.resize(image_size)

            # 保存调整后的图片到目标文件夹
            img_resized.save(os.path.join(full_target_path, filename))

print("所有图片处理完成，并保存在", target_folder, "文件夹中。")