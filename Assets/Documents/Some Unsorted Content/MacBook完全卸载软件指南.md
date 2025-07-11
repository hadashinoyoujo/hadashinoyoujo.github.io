# MacBook完全卸载软件指南

以下内容来源于删除Alfred 5 时，DeepSeek给我的建议，亲测有效。



## 第一步

如果你是通过 **Homebrew** 安装的 Alfred 5，除了常规卸载步骤外，还需要清理 Homebrew 相关的文件。以下是完整卸载指南：

---

### **1. 通过 Homebrew 卸载 Alfred**
在终端运行以下命令，卸载 Alfred 及其关联服务：
```bash
brew uninstall alfred
```

---

### **2. 删除 Homebrew 相关配置文件**
Homebrew 安装的软件可能会留下配置文件或缓存，需手动清理：
#### **(1) 删除 Alfred 的 Homebrew 缓存**
```bash
brew cleanup alfred
```
此命令会清理 Homebrew 下载的 Alfred 安装包缓存。

#### **(2) 检查是否残留 Cellar 文件**
Homebrew 的 `Cellar` 目录是软件安装位置，检查是否有 Alfred 残留：
```bash
ls /usr/local/Cellar/alfred
# 或（如果是 Apple Silicon 芯片）
ls /opt/homebrew/Cellar/alfred
```
如果有残留文件，手动删除：
```bash
rm -rf /usr/local/Cellar/alfred
# 或（Apple Silicon）
rm -rf /opt/homebrew/Cellar/alfred
```

---

### **3. 删除 Alfred 的用户配置文件（同常规卸载）**
即使通过 Homebrew 安装，用户配置文件仍存储在标准位置，需手动删除：
```bash
# 主配置文件夹（工作流、设置等）
rm -rf ~/Library/Application\ Support/Alfred

# 缓存文件
rm -rf ~/Library/Caches/com.runningwithcrayons.Alfred

# 偏好设置文件
rm -f ~/Library/Preferences/com.runningwithcrayons.Alfred.plist

# 日志文件（可选）
rm -rf ~/Library/Logs/Alfred
```

---

### **4. 移除 Alfred 的辅助权限**
1. 打开 **系统设置** → **隐私与安全性** → **辅助功能**。
2. 在列表中找到 **Alfred** 并移除权限（点击 **➖**）。

---

### **5. 检查 Homebrew 依赖（可选）**
如果 Alfred 是通过 `brew cask` 安装的，可能需要清理旧版 Cask 数据：
```bash
brew autoremove
brew cleanup --prune=all
```

---

### **验证卸载是否彻底**
1. 检查 Homebrew 是否已无 Alfred 记录：
   ```bash
   brew list | grep alfred
   ```
   如果无输出，说明已卸载干净。

2. 搜索系统残留文件：
   ```bash
   sudo find / -name "*Alfred*" 2>/dev/null
   ```
   （注意：此命令可能需要管理员密码，检查输出并删除无关文件。）

---

### **总结**
通过 Homebrew 安装的 Alfred 5 需要：
1. **`brew uninstall`** 卸载主程序  
2. **清理 Homebrew 缓存和 Cellar**  
3. **删除用户配置文件**（同常规卸载）  
4. **移除系统权限**  

完成后，Alfred 5 及其所有关联数据将被彻底清除。



------

## 第二步

上述操作后，find命令找到还有残留文件，接下来的操作如下：

> [!NOTE]
>
> 我搜索系统中是否残留Alfred的文件，出现以下内容： /System/Volumes/Data/private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred-Preferences /System/Volumes/Data/private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred /System/Volumes/Data/Users/hadashinoyoujo/Library/Preferences/com.runningwithcrayons.Alfred-Preferences.plist /System/Volumes/Data/Applications/Dash.app/Contents/Resources/dashAlfredWorkflow /System/Volumes/Data/Applications/Dash.app/Contents/Resources/AlfredWorkflowIcon.png /private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred-Preferences /private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred /Users/hadashinoyoujo/Library/Preferences/com.runningwithcrayons.Alfred-Preferences.plist /Applications/Dash.app/Contents/Resources/dashAlfredWorkflow /Applications/Dash.app/Contents/Resources/AlfredWorkflowIcon.png 这些都是吗？

你列出的路径中，**部分是与 Alfred 相关的残留文件**，但也有一些是其他应用的（如 `Dash.app` 的 Alfred 工作流）。以下是分类说明和清理建议：

---

### **1. 需要删除的 Alfred 残留文件**
以下路径是 Alfred 的缓存、临时文件或配置文件，可以安全删除：
```bash
# 缓存和临时文件（macOS 系统缓存目录）
/System/Volumes/Data/private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred-Preferences
/System/Volumes/Data/private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred
/private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred-Preferences
/private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred

# 用户配置文件（Preferences）
/System/Volumes/Data/Users/hadashinoyoujo/Library/Preferences/com.runningwithcrayons.Alfred-Preferences.plist
/Users/hadashinoyoujo/Library/Preferences/com.runningwithcrayons.Alfred-Preferences.plist
```

#### **删除命令**
```bash
sudo rm -rf /private/var/folders/wl/sh_1jv9x01ddkh89y05sjjgm0000gn/C/com.runningwithcrayons.Alfred*
rm ~/Library/Preferences/com.runningwithcrayons.Alfred*.plist
```
（注意：`/private/var/folders` 是系统保护目录，需用 `sudo` 删除。）

---

### **2. 其他应用的 Alfred 工作流（无需删除）**
以下路径属于 **Dash.app**（API 文档工具）内置的 Alfred 工作流文件，与 Alfred 本身无关。如果你仍在使用 Dash，请保留：
```bash
/System/Volumes/Data/Applications/Dash.app/Contents/Resources/dashAlfredWorkflow
/System/Volumes/Data/Applications/Dash.app/Contents/Resources/AlfredWorkflowIcon.png
/Applications/Dash.app/Contents/Resources/dashAlfredWorkflow
/Applications/Dash.app/Contents/Resources/AlfredWorkflowIcon.png
```
如果已卸载 Dash，可以删除整个 `Dash.app`。

---

### **3. 额外检查**
为确保彻底清理，再检查以下目录是否有遗漏：
```bash
# 用户级残留
ls ~/Library/Application\ Support/Alfred
ls ~/Library/Caches/com.runningwithcrayons.Alfred

# 系统级残留（谨慎操作）
sudo find /Library -name "*Alfred*" 2>/dev/null
```

---

### **4. 重要提醒**
1. **系统目录操作需谨慎**：  
   `/System` 和 `/private/var` 是 macOS 系统保护目录，误删可能影响系统稳定性。建议只删除明确标记为 `com.runningwithcrayons.Alfred` 的文件。
2. **重启生效**：  
   删除后重启电脑，确保临时文件彻底清除。

---

### **总结**
- **必须删除**：`com.runningwithcrayons.Alfred` 相关的缓存和配置文件。  
- **无需删除**：`Dash.app` 的工作流文件（除非你不再用 Dash）。  
- **验证命令**：再次运行 `sudo find / -name "*Alfred*" 2>/dev/null`，确认无关键残留。  

完成以上步骤后，Alfred 5 的所有痕迹将被彻底清除。