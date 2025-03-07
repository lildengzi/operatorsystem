#include<Windows.h>
#include <iostream>
using namespace std;

int main()
{
	STARTUPINFO sui;
	ZeroMemory(&sui, sizeof(sui));
	sui.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	int sum = 0;
	char content[100] = "";
	
	if(CreateProcess(".\\child2.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &sui, &pi))
	{
		printf("?????????????\n");
		HANDLE hEvent = CreateEvent(NULL, FALSE, TRUE, "myEvent");
        ResetEvent(hEvent);

        DWORD flag = WaitForSingleObject(hEvent, 10000);
        if (WAIT_FAILED == flag)
        {
            cout << "??????" << endl;
        }
        else if(WAIT_OBJECT_0 == flag)
        {
            cout << "??????" << endl;
        }
        else if (WAIT_TIMEOUT == flag)
        {
            cout << "??????" << endl;
        }
	}
	else printf("????????????\n");
	
    printf("????????");
	system("pause");
	return 0;
}
