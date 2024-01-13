# Simple football game

## 介绍
- OpenGL实现碰撞AI球类游戏 足球太复杂了 没时间搞。

## 效果

- 球碰到边界时反弹
- 球碰到球员时反弹且由于重量不同 会被推开加速
- 球进入球门时得分
- 鼠标控制人类球员移动（只有一个）
- 电脑控制AI球员移动（可以有多个 max 5）
- AI球员 防守 进攻 随机游走

## 运行

- 环境：20.04.1-Ubuntu, 系统库： glfw GLEW GL SOIL
- 编译运行：cmake -B build && cmake --build build && ./football

## Sample Imgs
![image](resources/imgs/football-2024-01-13_22.23.34.mkv.png)
![image](resources/imgs/football-2024-01-13_22.23.34.mkv-1.png)
![image](resources/imgs/football-2024-01-13_22.23.34.mkv-2.png)