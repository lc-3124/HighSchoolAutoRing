#include <cstdio>
#include <chrono>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <thread>  // �����߳̿⣬����ʵ�������ķ���������
#include <mutex>  // ���뻥�����������̼߳�Թ�����Դ����ʱ���������İ�ȫ����
#include <iostream>

// sysAPIģ��
#include <windows.h>
#include <unistd.h>

#include <chrono>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

const char* nircmdPath = "D:\\shit\\nircmd\\nircmd.exe"; 

void SetVolumeToMaxUsingSystemCommand()
{
    // ��������nircmd��������Ϊ���������ַ���
    std::string command = std::string(nircmdPath) + " setsysvolume 65535";
}

// �ṹ�����ڴ��ݵ�����ز����������ڲ�ͳһ����
struct MessageBoxParams {
    const char* title;
    const char* message;
    int time_sec;
};

// �ڲ�ʹ�õĴ��ڹ��̺����������������Ϣ
LRESULT CALLBACK InternalWndProc(HWND, UINT, WPARAM, LPARAM);

// �߶ȷ�װ�ķ������ӳٹرյ�������
// �߶ȷ�װ�ķ������ӳٹرյ�������
void ArDelayCloseBox(const char* title, const char* message, int time_sec) {
    MessageBoxParams params = { title, message, time_sec };
    std::thread closeThread([params]() {
        static const char* className = "MyMessageBoxClass";
        // ����ģʽȷ��������ֻע��һ�Σ����Ч�ʲ������ظ�ע������
        static bool classRegistered = false;
        if (!classRegistered) {
            WNDCLASS wc = {};
            wc.lpfnWndProc = InternalWndProc;
            wc.hInstance = GetModuleHandle(NULL);
            wc.lpszClassName = className;
            RegisterClass(&wc);
            classRegistered = true;
        }

        // ��������
        HWND hWnd = CreateWindowEx(0, className, params.title, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 500, 1, NULL, NULL, GetModuleHandle(NULL), NULL);
        if (hWnd!= NULL) {
            // �ڴ�������ʾ��Ϣ����
            HDC hdc = GetDC(hWnd);
            RECT rect;
            GetClientRect(hWnd, &rect);
            DrawTextA(hdc, params.message, -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            ReleaseDC(hWnd, hdc);

            // ��ʾ����
            ShowWindow(hWnd, SW_SHOW);

            // ���ô���Ϊǰ̨���ڣ���ȡ����
            SetForegroundWindow(hWnd);

            // ��¼��ʼʱ�䣬�����ж��ӳ�ʱ��
            auto startTime = std::chrono::steady_clock::now();

            // ��Ϣѭ������������Ϣ������ӳ�ʱ��
            MSG msg;
            while (GetMessage(&msg, NULL, 0, 0) > 0) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                // ���㾭��ʱ��
                auto currentTime = std::chrono::steady_clock::now();
                auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();
                if (elapsedSeconds >= params.time_sec) {
                    // �ﵽ�ӳ�ʱ�䣬�رմ���
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
// �ڲ�ʹ�õĴ��ڹ��̺�����ʵ�֣��������������Ϣ
LRESULT CALLBACK InternalWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}


// ������MessageBox
// ͬ�������߳���ʵ�֣�ʹ�õ�����Ϣ���������̼߳���ִ��
//����������� 
void ArNbMessageBox(const char* title, const char* message, int icon) {
    std::thread msgThread([title, message, icon]() {
        MessageBoxA(NULL, message, title, icon);
    });
    msgThread.detach();
}

///ý�岥������װ,����������� 
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

// std ģ��

// ���ڱ���ʱ�����ݵ��������洢��ͬʱ�̵�ʱ������������ʱ�����ȼ���
std::vector<time_t> ArTimeSaves; 
// ���Ը��ݾ���������Ӷ� TimeTable ��ע�ͣ�˵������;���˴�������Ҳ������ʱ����ؼ�¼��������ʾ����δ������ʹ�ó�����
TimeDelayDHS_struct TimeTable[100]; 

// ��������ȷ���ڶ��̻߳����¶� ArTimeSaves �����Ķ�д�������̰߳�ȫ��
std::mutex timeSavesMutex;  

// ��ʼ��ʱ�䱣�������Ĵ�С
void initTimeSaves(int max) {
    ArTimeSaves.resize(max);
}

// ��ȡ��ǰʱ�䣬����time_t��������
time_t ArGetTime() {
 return std::time(nullptr);
}

// ��ȡʱ�������������ڵ�ʱ���ȥindex����ArTimeSaves�Ĳͬʱ����ArTimeSaves.at(index)��ֵ
// ʹ�û�������֤���̻߳����¶Թ��������İ�ȫ��д
time_t ArGetDelay(int index) {
    std::lock_guard<std::mutex> guard(timeSavesMutex);  // �Զ������ͽ���

        time_t now = time(nullptr);
        time_t old_time = ArTimeSaves.at(index);
        ArTimeSaves.at(index) = now;
        return now - old_time;
    
}

// ת��time_tʱ������TimeDelayDHS_struct���ͣ���������ʱ��֮��
void ArTurnToDhs(TimeDelayDHS_struct &DHSinstance) {
    std::time_t secondsAsTimeT = DHSinstance.Second;
    std::tm localTimeInfo = *std::localtime(&secondsAsTimeT);
    DHSinstance.Day = localTimeInfo.tm_yday;  // ʹ��tm_yday��ȡ���������ǰ���ڵ�����
    DHSinstance.Hour = localTimeInfo.tm_hour;
    DHSinstance.Minute = localTimeInfo.tm_min;
    DHSinstance.Second = localTimeInfo.tm_sec;
}
