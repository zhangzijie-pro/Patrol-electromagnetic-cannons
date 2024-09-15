# 训练模型
import torch.nn as nn
import init
import model
import torch.optim as optim
from torch.optim import lr_scheduler
import torch.onnx

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
model.model.to(device)

# 定义损失函数和优化器
criterion = nn.BCELoss()
optimizer = optim.Adam(model.model.parameters(), lr=0.001)
scheduler = lr_scheduler.StepLR(optimizer, step_size=7, gamma=0.1)

num_epochs = 10

for epoch in range(num_epochs):
    model.model.train()
    running_loss = 0.0

    for images, labels in init.train_loader:
        images, labels = images.to(device), labels.float().to(device)
        optimizer.zero_grad()

        outputs = model.model(images).squeeze()
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        running_loss += loss.item() * images.size(0)

    epoch_loss = running_loss / len(init.train_loader.dataset)
    print(f'Epoch {epoch+1}/{num_epochs}, Loss: {epoch_loss:.4f}')
    scheduler.step()

    # 评估模型
    model.model.eval()
    with torch.no_grad():
        val_loss = 0.0
        corrects = 0
        for images, labels in init.val_loader:
            images, labels = images.to(device), labels.float().to(device)
            outputs = model.model(images).squeeze()
            loss = criterion(outputs, labels)
            val_loss += loss.item() * images.size(0)
            preds = (outputs > 0.5).long()
            corrects += torch.sum(preds == labels.data)

        val_loss /= len(init.val_loader.dataset)
        val_acc = corrects.double() / len(init.val_loader.dataset)
        print(f'Validation Loss: {val_loss:.4f}, Accuracy: {val_acc:.4f}')

torch.save(model.model.state_dict(), 'model.pth')