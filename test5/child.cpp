#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
using namespace std;

int main()
{
    bool rc = 0;
    char InBuffer[50] = "";
    char OutBuffer[50] = "";
    DWORD BytesRead;

    int err = 0;

    while (1)
    {
        strcpy(InBuffer, "");
        strcpy(OutBuffer, "");
        cout << "�������ӽ���Ҫ���͵�����\n" << endl;
        cin >> InBuffer;
        rc = strcmp(InBuffer, "end");
        if (rc == 0)
        {
            rc = CallNamedPipe("\\\\.\\pipe\\myPipe", InBuffer, sizeof(InBuffer), OutBuffer,
                sizeof(OutBuffer), &BytesRead, NMPWAIT_USE_DEFAULT_WAIT);
            break;
        }
            
                
        rc = WaitNamedPipe("\\\\.\\pipe\\myPipe", NMPWAIT_WAIT_FOREVER);
        if (rc == 0)
        {
            err = GetLastError();
            cout << "�ܵ��ȴ�ʧ��,err = \n" << err << endl;
            exit(1);
        }
        else
        {
            cout << "�ܵ��ȴ��ɹ�!\n" << endl;
        }
        rc = CallNamedPipe("\\\\.\\pipe\\myPipe", InBuffer, sizeof(InBuffer), OutBuffer,
            sizeof(OutBuffer), &BytesRead, NMPWAIT_USE_DEFAULT_WAIT);
        rc = strcmp(OutBuffer, "end");
        if (rc == 0)
        {
            break;
        }
        
        if (rc == 0)
        {
            err = GetLastError();
            cout << "�ܵ�����ʧ��,err = \n" << err << endl;
            exit(1);
        }
        else
        {
            cout << "�ܵ����ӳɹ�\n ��ȡ����:\n" << OutBuffer << endl;
        }
    }


    cout << "�ܵ�����!\n" << endl;
    system("pause");
    return 0;

}