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
        cout << "请输入子进程要发送的数据\n" << endl;
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
            cout << "管道等待失败,err = \n" << err << endl;
            exit(1);
        }
        else
        {
            cout << "管道等待成功!\n" << endl;
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
            cout << "管道链接失败,err = \n" << err << endl;
            exit(1);
        }
        else
        {
            cout << "管道链接成功\n 读取内容:\n" << OutBuffer << endl;
        }
    }


    cout << "管道结束!\n" << endl;
    system("pause");
    return 0;

}