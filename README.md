# HighSchoolAutoRing
- 这很搞笑，我们班的广播坏了，老师让我想办法至少播放眼保健操的音频，于是我做了一个软件......
- 这个玩意可以在设定的时间`ArConfig.cpp`播放音频，精确到0.5秒
- 有良好的交互方式
- 和十分甚至九分 ( ) 的音乐

# 特点
## 因为是几个课间写的，我才没有考虑什么复杂的东西
- Mingw编译，别忘了加链接库指令
- 开发环境记事本和vim
- 使用生成式人工智能完成部分代码
- 只兼容windows  10
- 代码像屎
- 目前连续一周工作正常

# 如果你的教室广播也坏了，欢迎你clone到自己班的多媒体屏幕上

## 使用方法：
0. 如果你的作息时间和我一样，就直接在`C:\ProgramData\Microsoft\Windows\Start Menu\Programs\StartUp`中创建快捷方式指向`...\HighSchoolAutoRing\main.exe`
1. `clone`/`dowload`项目到你的机器上
2. 更改`ArConfig.cpp`的配置信息，设置`MAXTIMES`宏
3. 使用Mingw (devcpp自带的就行）进行编译

# 欢迎issue和PR,虽然我开发时间少得可怜
