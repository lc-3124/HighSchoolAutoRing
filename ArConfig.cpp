#define MAXTIMES 21
#include "ArFuncList.cpp"

// ��ʼ��������ע��ʱ��������Ϣ��TimeTable������
void Arinit() {
    initTimeSaves(100);
    // ��ʼ��TimeTable������ȷ�����㹻�ռ���ʱ��ڵ���Ϣ��������Ϊ������20��ʱ��ڵ㣬�ɰ��������С

    // �����һ���Ͽ�ʱ��Ϊ 8:18:04
    // ��¼��׼ʱ��㣬������ƥ��ʱ���߼��д�����Χ����������������
    TimeTable[0].Day = 0;
    TimeTable[0].Hour = 8;
    TimeTable[0].Minute = 18;
    TimeTable[0].Second = 4;
    // �Ͽ�����ƵΪclass.mp3
    TimeTable[0].Path = "class.mp3";

    // �����һ�ڿ��¿�ʱ��Ϊ 9:00:07
    TimeTable[1].Day = 0;
    TimeTable[1].Hour = 9;
    TimeTable[1].Minute = 0;
    TimeTable[1].Second = 7;
    TimeTable[1].Path = "class_over.mp3";

    // ����ڶ��ڿ��Ͽ�ʱ��Ϊ 9:08:04
    TimeTable[2].Day = 0;
    TimeTable[2].Hour = 9;
    TimeTable[2].Minute = 8;
    TimeTable[2].Second = 4;
    TimeTable[2].Path = "class.mp3";

    // ����ڶ��ڿ��¿�ʱ��Ϊ 9:50:07
    TimeTable[3].Day = 0;
    TimeTable[3].Hour = 9;
    TimeTable[3].Minute = 50;
    TimeTable[3].Second = 7;
    TimeTable[3].Path = "class_over.mp3";
    
    // ����ڶ��ڿ��¿�ʱ��Ϊ 10:05:07
    TimeTable[21].Day = 0;
    TimeTable[21].Hour = 10;
    TimeTable[21].Minute = 5;
    TimeTable[21].Second = 7;
    TimeTable[21].Path = "class_over.mp3";
    // ��������ڿ��Ͽ�ʱ��Ϊ 10:23:04
    TimeTable[4].Day = 0;
    TimeTable[4].Hour = 10;
    TimeTable[4].Minute = 23;
    TimeTable[4].Second = 4;
    TimeTable[4].Path = "class.mp3";

    // �����۱�����ʱ��Ϊ 11:05:22
    TimeTable[5].Day = 0;
    TimeTable[5].Hour = 11;
    TimeTable[5].Minute = 05;
    TimeTable[5].Second = 22;
    TimeTable[5].Path = "eye_exercise.mp3";

    // ������Ľڿ��Ͽ�ʱ��Ϊ 11:18:04
    TimeTable[6].Day = 0;
    TimeTable[6].Hour = 11;
    TimeTable[6].Minute = 18;
    TimeTable[6].Second = 4;
    TimeTable[6].Path = "class.mp3";

    // ������Ľڿ��¿�ʱ��Ϊ 12:00:07
    TimeTable[7].Day = 0;
    TimeTable[7].Hour = 12;
    TimeTable[7].Minute = 0;
    TimeTable[7].Second = 7;
    TimeTable[7].Path = "class_over.mp3";

    // ����Ԥ��ʱ��Ϊ 12:48:18
    TimeTable[8].Day = 0;
    TimeTable[8].Hour = 12;
    TimeTable[8].Minute = 48;
    TimeTable[8].Second = 18;
    TimeTable[8].Path = "class.mp3";

    // �����һ�ڿ��Ͽ�ʱ��Ϊ 14:08:04
    TimeTable[9].Day = 0;
    TimeTable[9].Hour = 14;
    TimeTable[9].Minute = 8;
    TimeTable[9].Second = 4;
    TimeTable[9].Path = "class.mp3";

    // �����۱�����ʱ��Ϊ 14:50:22
    TimeTable[10].Day = 0;
    TimeTable[10].Hour = 14;
    TimeTable[10].Minute = 50;
    TimeTable[10].Second = 22;
    TimeTable[10].Path = "eye_exercise.mp3";

    // ����ڶ��ڿ��Ͽ�ʱ��Ϊ 15:03:04
    TimeTable[11].Day = 0;
    TimeTable[11].Hour = 15;
    TimeTable[11].Minute = 3;
    TimeTable[11].Second = 4;
    TimeTable[11].Path = "class.mp3";

    // ����ڶ��ڿ��¿�ʱ��Ϊ 15:45:07
    TimeTable[12].Day = 0;
    TimeTable[12].Hour = 15;
    TimeTable[12].Minute = 45;
    TimeTable[12].Second = 7;
    TimeTable[12].Path = "class_over.mp3";

    // ��������ڿ��Ͽ�ʱ��Ϊ 15:53:04
    TimeTable[13].Day = 0;
    TimeTable[13].Hour = 15;
    TimeTable[13].Minute = 53;
    TimeTable[13].Second = 4;
    TimeTable[13].Path = "class.mp3";

    // ��������ڿ��¿�ʱ��Ϊ 16:35:07
    TimeTable[14].Day = 0;
    TimeTable[14].Hour = 16;
    TimeTable[14].Minute = 35;
    TimeTable[14].Second = 7;
    TimeTable[14].Path = "class_over.mp3";

    // ������Ľڿ��Ͽ�ʱ��Ϊ 16:43:04
    TimeTable[15].Day = 0;
    TimeTable[15].Hour = 16;
    TimeTable[15].Minute = 43;
    TimeTable[15].Second = 4;
    TimeTable[15].Path = "class.mp3";

    // ������Ľڿ��¿�ʱ��Ϊ 17:25:07
    TimeTable[16].Day = 0;
    TimeTable[16].Hour = 17;
    TimeTable[16].Minute = 25;
    TimeTable[16].Second = 7;
    TimeTable[16].Path = "class_over.mp3";

    // �������ڿ��Ͽ�ʱ��Ϊ 17:33:04
    TimeTable[17].Day = 0;
    TimeTable[17].Hour = 17;
    TimeTable[17].Minute = 33;
    TimeTable[17].Second = 4;
    TimeTable[17].Path = "class.mp3";

    // �������ڿ��¿�ʱ��Ϊ 18:15:07
    TimeTable[18].Day = 0;
    TimeTable[18].Hour = 18;
    TimeTable[18].Minute = 15;
    TimeTable[18].Second = 7;
    TimeTable[18].Path = "class_over.mp3";

    // ��һ������ϰ�Ͽ�ʱ��Ϊ 19:08:04��
    TimeTable[19].Day = 0;
    TimeTable[19].Hour = 19;
    TimeTable[19].Minute = 8;
    TimeTable[19].Second = 4;
    TimeTable[19].Path = "class.mp3";
}
