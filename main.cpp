#include <conio.h>
#include "ArConfig.cpp"
#include <iostream>
#include <windows.h>

// 定义一个全局变量用于记录console窗口的显示状态，初始化为隐藏
BOOL g_isConsoleVisible = FALSE; 

// 切换console窗口显示隐藏状态的函数实现
void ToggleConsoleVisibility() {
    HWND consoleWnd = GetConsoleWindow();
    if (consoleWnd!= NULL) {
        if (g_isConsoleVisible) {
            ShowWindow(consoleWnd, SW_HIDE);
            g_isConsoleVisible = FALSE;
        }
        else {
            ShowWindow(consoleWnd, SW_SHOW);
            g_isConsoleVisible = TRUE;
        }
    }
}

// 轮循读取时间，适时播放音频，这里不涉及多线程 
void loop()
{
    while (1)
    {
        // 延迟0.5秒，防止资源消耗过度 
        Sleep(500);
        
        // 检测F8键是否被按下
        if (GetAsyncKeyState(VK_F8) && (GetAsyncKeyState(VK_F8) & 0x8000)) {
            ToggleConsoleVisibility();
            // 短暂延迟，避免一次按键多次触发（可根据实际情况调整延迟时长）
            Sleep(80); 
        }
        
        // 获取时间并且转换成DHS形式 
        time_t nowtime = ArGetTime();
        TimeDelayDHS_struct Form;
        Form.Second = nowtime;
        ArTurnToDhs(Form);
        
        // 遍历时间注册表，检测现在时间是否吻合相关注册 
        for (int index = 0; index < MAXTIMES; index++)
        {
            if (TimeTable[index].Hour == Form.Hour
                && TimeTable[index].Minute == Form.Minute
                && TimeTable[index].Second == Form.Second)
            {
            SetVolumeToMaxUsingSystemCommand();
                //ArPlayMusic(TimeTable[index].Path);
                std::string cmd ;
                cmd += "D:";
                cmd += TimeTable[index].Path;
                system(cmd.c_str());
				ArDelayCloseBox("检测到时间吻合，音频，启动！！！", " ", 5);
                Sleep(1000*6);
            }
        }
    }
}

int main()
{
	
    Arinit();

    // 隐藏console窗口
    HWND consoleWnd = GetConsoleWindow();
    if (consoleWnd!= NULL) {
        ShowWindow(consoleWnd, SW_HIDE);
        g_isConsoleVisible = FALSE;
    }
    
    
    std::cout << "你可以检查时间是否正确，如果有问题，请修改文件重新编译：\n"; 
    
    for (int i = 0; i < MAXTIMES; i++)
    {
        std::cout << i << "号: "
            << TimeTable[i].Hour
            << ":" << TimeTable[i].Minute
            << ":" << TimeTable[i].Second
            << " - " << TimeTable[i].Path << "\n";
    }
    
    // 启动提示 
    ArDelayCloseBox("自动打铃系统已经成功启动!", "测试", 3);
    Sleep(3000);
    ArDelayCloseBox("你可以长按<F8>来启动调试窗口，<F7>播放器自检","测试",3);    
    loop();
    system("pause");
}
