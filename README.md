# ImGui-Hexagram-Effect
基于ImGui的可配置六芒星动效组件，支持位置调节、自动旋转、循环缩放、渐变颜色自定义。

## 功能特性
- ✅ 可视化参数调节（中心点、大小、旋转、缩放、渐变）
- ✅ 粉紫→青色默认渐变，支持自定义起始/结束色
- ✅ 分层渐变渲染，细腻度可调节
- ✅ 可选自动旋转（支持顺时针/逆时针）
- ✅ 可选循环缩放动效

## 依赖环境
- ImGui 1.80+
- C++11及以上
- 支持的渲染后端（OpenGL/DirectX/Vulkan等，与ImGui兼容即可）

## 使用方法
1. 将 `HexagramEffect.cpp` 加入你的项目
2. 初始化 `HexagramSettings` 结构体（可修改默认参数）
3. 在ImGui渲染循环中调用两个核心函数：
   ```cpp
   // 绘制六芒星动效（需传入ImDrawList）
   RenderHexagramEffect(设置, draw);
   // 显示设置面板（在ImGui窗口中调用）
   DrawHexagramSettingsPanel(设置);
