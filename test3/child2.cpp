#include<Windows.h>
#include<iostream>
using namespace std;

int main()
{
    HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, TRUE, "myEvent");
    Sleep(1000);

    char ch;
    cout << "信号事件确认" << endl;
    cin >> ch;
    if(ch == 'y')
    {
        SetEvent(hEvent);
    }
    
    Sleep(1000);
    system("pause");
    return 0;
}