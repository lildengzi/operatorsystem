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
        cout << "创建管道失败. err = \n" << err << endl;
        exit(1);
    }
    else
    {
        cout << "创建管道成功!\n" << endl; 
    }
    while (TRUE)
    {
        rc = ConnectNamedPipe(hPipeHandle1, NULL);
        if (rc == 0)
        {
            err = GetLastError();
            cout << "管道链接失败. err = \n" << err << endl;
            exit(2);
        }
        else
        {
            cout << "管道链接成功!\n" << endl; 
        }
        strcpy(InBuffer, "");
        strcpy(OutBuffer, "");
        
        rc = ReadFile(hPipeHandle1, InBuffer, sizeof(InBuffer), &BytesRead, NULL);
        if (rc == 0 && BytesRead == 0)
        {
            err = GetLastError();
            cout << "管道读取数据失败,err = \n" << err << endl;
            exit(2);
        }
        else
        {
            cout << "管道读取数据成功，读取内容:\n" << InBuffer << endl; 
        }

        rc = strcmp(InBuffer, "end");
        if (rc == 0)
        {
            break;
        }
        cout << "请输入想发送的数据:\n" << endl;
        cin >> OutBuffer;

        rc = WriteFile(hPipeHandle1, OutBuffer, sizeof(OutBuffer), &BytesWrite, NULL);
        if (rc == 0)
        {
            cout << "管道写入数据失败\n" << endl;
        }
        else
        {
            cout << "管道写入数据成功\n" << endl;
        }
        
        DisconnectNamedPipe(hPipeHandle1);
        rc = strcmp(OutBuffer, "end");
        if (rc == 0)
        {
            break;
        }
        
    }
    cout << "管道结束!\n" << endl;
    CloseHandle(hPipeHandle1);
    system("pause");
    return 0;
}