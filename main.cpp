#include <conio.h>
#include "ArConfig.cpp"
#include <iostream>
#include <windows.h>

// ����һ��ȫ�ֱ������ڼ�¼console���ڵ���ʾ״̬����ʼ��Ϊ����
BOOL g_isConsoleVisible = FALSE; 

// �л�console������ʾ����״̬�ĺ���ʵ��
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

// ��ѭ��ȡʱ�䣬��ʱ������Ƶ�����ﲻ�漰���߳� 
void loop()
{
    while (1)
    {
        // �ӳ�0.5�룬��ֹ��Դ���Ĺ��� 
        Sleep(500);
        
        // ���F8���Ƿ񱻰���
        if (GetAsyncKeyState(VK_F8) && (GetAsyncKeyState(VK_F8) & 0x8000)) {
            ToggleConsoleVisibility();
            // �����ӳ٣�����һ�ΰ�����δ������ɸ���ʵ����������ӳ�ʱ����
            Sleep(80); 
        }
        
        // ��ȡʱ�䲢��ת����DHS��ʽ 
        time_t nowtime = ArGetTime();
        TimeDelayDHS_struct Form;
        Form.Second = nowtime;
        ArTurnToDhs(Form);
        
        // ����ʱ��ע����������ʱ���Ƿ��Ǻ����ע�� 
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
				ArDelayCloseBox("��⵽ʱ���Ǻϣ���Ƶ������������", " ", 5);
                Sleep(1000*6);
            }
        }
    }
}

int main()
{
	
    Arinit();

    // ����console����
    HWND consoleWnd = GetConsoleWindow();
    if (consoleWnd!= NULL) {
        ShowWindow(consoleWnd, SW_HIDE);
        g_isConsoleVisible = FALSE;
    }
    
    
    std::cout << "����Լ��ʱ���Ƿ���ȷ����������⣬���޸��ļ����±��룺\n"; 
    
    for (int i = 0; i < MAXTIMES; i++)
    {
        std::cout << i << "��: "
            << TimeTable[i].Hour
            << ":" << TimeTable[i].Minute
            << ":" << TimeTable[i].Second
            << " - " << TimeTable[i].Path << "\n";
    }
    
    // ������ʾ 
    ArDelayCloseBox("�Զ�����ϵͳ�Ѿ��ɹ�����!", "����", 3);
    Sleep(3000);
    ArDelayCloseBox("����Գ���<F8>���������Դ��ڣ�<F7>�������Լ�","����",3);    
    loop();
    system("pause");
}
