import numpy as np
import matplotlib.pyplot as plt
import random

# 设置雷达的参数
distance_between_centers = 5  # 雷达图圆心距离原点的距离，单位为cm
max_distance = 6.5  # 最大探测距离，单位为m
distance_step = 0.5  # 每个距离门的大小，单位为m
num_zones = int(max_distance / distance_step)  # 区间数
angle_range = 75  # 雷达扫描角度，±75度


# 随机生成目标点，确保目标位于重叠范围
def generate_random_target_in_overlap():
    # 目标必须位于重叠区域
    # 距离：随机生成1到最大探测距离
    distance = random.uniform(1, max_distance)
    # 角度：必须在两个雷达的交合部分，也就是雷达1和雷达2探测的±75度重叠部分
    angle = random.uniform(-angle_range, angle_range)  # 保持目标在雷达探测角度范围内
    # 区间：根据距离计算在哪个区间
    zone = int(distance / distance_step) + 1
    return distance, angle, zone


# 绘制雷达图，只保留一二象限
def plot_radar(ax, center_x, title):
    ax.set_aspect('equal')
    ax.set_xlim(-max_distance + center_x, max_distance + center_x)
    ax.set_ylim(0, max_distance)

    # 画雷达的扫描线和圆圈
    for r in np.arange(0, max_distance + distance_step, distance_step):
        circle = plt.Circle((center_x, 0), r, color='gray', fill=False)
        ax.add_artist(circle)

    # 画出雷达的扫描角度区域（±75度）
    angles = np.linspace(-angle_range, angle_range, 100)
    for angle in angles:
        radian = np.deg2rad(angle)
        x = center_x + max_distance * np.cos(radian)
        y = max_distance * np.sin(radian)
        if y >= 0:  # 只保留一二象限部分
            ax.plot([center_x, x], [0, y], color='lightgray', linestyle='--', lw=0.5)

    # 绘制雷达中心
    ax.scatter(center_x, 0, color='red', s=100, label=f'{title} Center')


# 绘制目标点
def plot_target(ax, center_x, distance, angle_deg, zone, target_label, color='blue'):
    angle_rad = np.deg2rad(angle_deg)
    x = center_x + distance * np.cos(angle_rad)
    y = distance * np.sin(angle_rad)
    ax.scatter(x, y, color=color, s=100, label=f'{target_label}')
    ax.text(x, y, f'Zone {zone}, {distance:.2f}m', color=color)


# 创建图像
fig, ax = plt.subplots(figsize=(8, 8))

# 雷达1（位于原点左侧5cm）
center_x1 = -distance_between_centers / 10.0  # 将cm转换为m
plot_radar(ax, center_x1, "Radar 1 (Left)")

# 雷达2（位于原点右侧5cm）
center_x2 = distance_between_centers / 10.0  # 将cm转换为m
plot_radar(ax, center_x2, "Radar 2 (Right)")

# 生成两个目标点，确保位于雷达的交合区域
target_distance, target_angle, target_zone = generate_random_target_in_overlap()

# 绘制目标点，位于重叠区域
plot_target(ax, center_x1, target_distance, target_angle, target_zone, "Target in Overlap", color='green')
plot_target(ax, center_x2, target_distance, target_angle, target_zone, "Target in Overlap", color='green')

# 添加原点
ax.scatter(0, 0, color='black', s=200, label='Central Origin')

# 添加图例
ax.legend(loc='upper right')

# 显示图像
plt.title("Radar Overlap in First and Second Quadrant")
plt.xlabel("Distance (m)")
plt.ylabel("Distance (m)")
plt.grid(True)
plt.show()
