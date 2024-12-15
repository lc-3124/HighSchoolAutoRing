#include <cstdio>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <thread>  // 引入线程库，用于实现真正的非阻塞操作
#include <mutex>  // 引入互斥锁，用于线程间对共享资源（如时间向量）的安全访问
#include <iostream>

// sysAPI模块
#include <windows.h>
#include <unistd.h>

#include <chrono>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

const char* nircmdPath = "D:\\shit\\nircmd\\nircmd.exe"; 

void SetVolumeToMaxUsingSystemCommand()
{
    // 构建调用nircmd设置音量为最大的命令字符串
    std::string command = std::string(nircmdPath) + " setsysvolume 65535";
}

// 结构体用于传递弹窗相关参数，方便内部统一管理
struct MessageBoxParams {
    const char* title;
    const char* message;
    int time_sec;
};

// 内部使用的窗口过程函数，处理窗口相关消息
LRESULT CALLBACK InternalWndProc(HWND, UINT, WPARAM, LPARAM);

// 高度封装的非阻塞延迟关闭弹窗函数
// 高度封装的非阻塞延迟关闭弹窗函数
void ArDelayCloseBox(const char* title, const char* message, int time_sec) {
    MessageBoxParams params = { title, message, time_sec };
    std::thread closeThread([params]() {
        static const char* className = "MyMessageBoxClass";
        // 单例模式确保窗口类只注册一次，提高效率并避免重复注册问题
        static bool classRegistered = false;
        if (!classRegistered) {
            WNDCLASS wc = {};
            wc.lpfnWndProc = InternalWndProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = className;
            RegisterClass(&wc);
            classRegistered = true;
        }

        // 创建窗口
        HWND hWnd = CreateWindowEx(0, className, params.title, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 500, 1, NULL, NULL, GetModuleHandle(NULL), NULL);
        if (hWnd!= NULL) {
            // 在窗口中显示消息内容
            HDC hdc = GetDC(hWnd);
            RECT rect;
            GetClientRect(hWnd, &rect);
            DrawTextA(hdc, params.message, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            ReleaseDC(hWnd, hdc);

            // 显示窗口
            ShowWindow(hWnd, SW_SHOW);

            // 设置窗口为前台窗口，获取焦点
            SetForegroundWindow(hWnd);

            // 记录开始时间，用于判断延迟时间
            auto startTime = std::chrono::steady_clock::now();

            // 消息循环，处理窗口消息并检测延迟时间
            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                // 计算经过时间
                auto currentTime = std::chrono::steady_clock::now();
                auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                if (elapsedSeconds >= params.time_sec) {
                    // 达到延迟时间，关闭窗口
                    DestroyWindow(hWnd);
                    break;
                }
            }
        }
    });
    if (closeThread.joinable()) {
        closeThread.detach();
    }
}
// 内部使用的窗口过程函数的实现，处理基本窗口消息
LRESULT CALLBACK InternalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}


// 非阻塞MessageBox
// 同样利用线程来实现，使得弹出消息框不阻塞主线程继续执行
//这个函数正常 
void ArNbMessageBox(const char* title, const char* message, int icon) {
    std::thread msgThread([title, message, icon]() {
        MessageBoxA(NULL, message, title, icon);
    });
    msgThread.detach();
}

///媒体播放器封装,这个函数正常 
void ArPlayMusic(std::string Path){
 std::string command1 = "open \"";
 std::string command2 = "\" type mpegvideo alias myMusic";
 std::string command = command1 + Path + command2;           
			mciSendString(command.c_str(), NULL, 0, NULL);
            mciSendString("play myMusic", NULL, 0, NULL); 
}

struct TimeDelayDHS_struct
{
    int Day = 0;
    int Hour = 0;
    int Minute = 0;
    int Second = 0;
    std::string Path = "ybjc.mp3";
};

// std 模块

// 用于保存时间数据的向量，存储不同时刻的时间戳，方便后续时间间隔等计算
std::vector<time_t> ArTimeSaves; 
// 可以根据具体需求添加对 TimeTable 的注释，说明其用途，此处假设它也是用于时间相关记录的向量（示例中未体现其使用场景）
TimeDelayDHS_struct TimeTable[100]; 

// 互斥锁，确保在多线程环境下对 ArTimeSaves 向量的读写操作是线程安全的
std::mutex timeSavesMutex;  

// 初始化时间保存向量的大小
void initTimeSaves(int max) {
    ArTimeSaves.resize(max);
}

// 获取当前时间，返回time_t类型数据
time_t ArGetTime() {
 return std::time(nullptr);
}

// 获取时间间隔，返回现在的时间减去index索引ArTimeSaves的差，同时更新ArTimeSaves.at(index)的值
// 使用互斥锁保证多线程环境下对共享向量的安全读写
time_t ArGetDelay(int index) {
    std::lock_guard<std::mutex> guard(timeSavesMutex);  // 自动加锁和解锁

        time_t now = time(nullptr);
        time_t old_time = ArTimeSaves.at(index);
        ArTimeSaves.at(index) = now;
        return now - old_time;
    
}

// 转换time_t时间间隔到TimeDelayDHS_struct类型，用来计算时间之差
void ArTurnToDhs(TimeDelayDHS_struct &DHSinstance) {
    std::time_t secondsAsTimeT = DHSinstance.Second;
    std::tm localTimeInfo = *std::localtime(&secondsAsTimeT);
    DHSinstance.Day = localTimeInfo.tm_yday;  // 使用tm_yday获取从年初到当前日期的天数
    DHSinstance.Hour = localTimeInfo.tm_hour;
    DHSinstance.Minute = localTimeInfo.tm_min;
    DHSinstance.Second = localTimeInfo.tm_sec;
}
