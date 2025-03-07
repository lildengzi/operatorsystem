#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
using namespace std;

int main()
{
    int err;
    bool rc;
    HANDLE hPipeHandle1;

    char InBuffer[50] = "";
    char OutBuffer[50] = "";
    DWORD BytesRead, BytesWrite;

    hPipeHandle1 = CreateNamedPipe("\\\\.\\pipe\\myPipe",
    PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED | WRITE_DAC,
    PIPE_TYPE_MESSAGE | PIPE_READMODE_BYTE | PIPE_WAIT,
    1, 20, 30,
    NMPWAIT_USE_DEFAULT_WAIT,
    (LPSECURITY_ATTRIBUTES)NULL);

    if ((hPipeHandle1 == INVALID_HANDLE_VALUE) || (hPipeHandle1 == NULL))
    {
        err = GetLastError();
        cout << "�����ܵ�ʧ��. err = \n" << err << endl;
        exit(1);
    }
    else
    {
        cout << "�����ܵ��ɹ�!\n" << endl; 
    }
    while (TRUE)
    {
        rc = ConnectNamedPipe(hPipeHandle1, NULL);
        if (rc == 0)
        {
            err = GetLastError();
            cout << "�ܵ�����ʧ��. err = \n" << err << endl;
            exit(2);
        }
        else
        {
            cout << "�ܵ����ӳɹ�!\n" << endl; 
        }
        strcpy(InBuffer, "");
        strcpy(OutBuffer, "");
        
        rc = ReadFile(hPipeHandle1, InBuffer, sizeof(InBuffer), &BytesRead, NULL);
        if (rc == 0 && BytesRead == 0)
        {
            err = GetLastError();
            cout << "�ܵ���ȡ����ʧ��,err = \n" << err << endl;
            exit(2);
        }
        else
        {
            cout << "�ܵ���ȡ���ݳɹ�����ȡ����:\n" << InBuffer << endl; 
        }

        rc = strcmp(InBuffer, "end");
        if (rc == 0)
        {
            break;
        }
        cout << "�������뷢�͵�����:\n" << endl;
        cin >> OutBuffer;

        rc = WriteFile(hPipeHandle1, OutBuffer, sizeof(OutBuffer), &BytesWrite, NULL);
        if (rc == 0)
        {
            cout << "�ܵ�д������ʧ��\n" << endl;
        }
        else
        {
            cout << "�ܵ�д�����ݳɹ�\n" << endl;
        }
        
        DisconnectNamedPipe(hPipeHandle1);
        rc = strcmp(OutBuffer, "end");
        if (rc == 0)
        {
            break;
        }
        
    }
    cout << "�ܵ�����!\n" << endl;
    CloseHandle(hPipeHandle1);
    system("pause");
    return 0;
}