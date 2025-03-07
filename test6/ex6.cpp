#include<iostream>
#include<Windows.h>
#include<stdlib.h>
using namespace std;

HANDLE h_Mutex;
HANDLE bufferFullSemaphore;
HANDLE bufferEmptySemaphore;
const int BUFFER_SIZE=3;
long buffer[BUFFER_SIZE] = {0};
int in = 0;
int out = 0;
int num = 0;
int seq = 1;
int num1 = 0;
int num2 = 0;
const int PRODUCER_NUM = 1;
const int CONSUMER_NUM = 2;
bool flag = true;
DWORD producerID[PRODUCER_NUM];
DWORD consumerID[CONSUMER_NUM];

void producer()
{
    while (flag)
    {
        WaitForSingleObject(bufferEmptySemaphore, INFINITE);
        WaitForSingleObject(h_Mutex,INFINITE);
        cout << "Producer is producing\n";
        cout << "Successfully produced\n";
        cout << "Product No:" << seq << endl;
        buffer[in] = seq;
        in = (in + 1)%BUFFER_SIZE;
        num = num + 1;
        seq = seq + 1;
        cout << "Producer has produced" << num << endl;
        cout << endl << endl;
        Sleep(1000);
        ReleaseMutex(h_Mutex);
        ReleaseSemaphore(bufferFullSemaphore, 1, NULL);
    }
}

void consumer1()
{
    while (flag)
    {
        WaitForSingleObject(bufferFullSemaphore, INFINITE);
        WaitForSingleObject(h_Mutex, INFINITE);
        cout << "Thread1 gets Mutex" << endl;
        cout << "Thread1 is consuming a product" << endl;
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;
        num1 = num1 + 1;
        Sleep(500);
        cout << "A product has been consumed by Thread1" << endl;
        cout << "Thread1 has consumed" << num1 << "products" << endl;
        cout << "Two threads have consumed" << num1 + num2 << endl;
        cout << "Thread1 releases Mutex\n" << endl;
        ReleaseMutex(h_Mutex);
        ReleaseSemaphore(bufferEmptySemaphore, 1, NULL); 
    }
}

void consumer2()
{
    while (flag)
    {
        WaitForSingleObject(bufferFullSemaphore, INFINITE);
        WaitForSingleObject(h_Mutex, INFINITE);
        cout << "Thread2 get Mutex" << endl;
        cout << "Thread2 is consuming a product" << endl;
        buffer[out] = 0;
        out = (out + 1) % BUFFER_SIZE;
        num2 = num2 + 1;
        Sleep(1000);
        cout << "A product has been consumed by Thread2" << endl;
        cout << "Thread2 has consumed" << num1 << "products" << endl;
        cout << "Two threads have consumed" << num1 + num2 << endl;
        cout << "Thread2 releases Mutex\n" << endl;
        ReleaseMutex(h_Mutex);
        ReleaseSemaphore(bufferEmptySemaphore, 1, NULL); 
    }
    
}

int main()
{
    cout << "本程序模拟生产者消费者问题\n\n生产者数目:1消费者数目:" << endl;
    cout << "1个生产者线程和两个消费者线程已准备就绪\n" << endl;
    cout << "消费者线程1消费时间:0.5s, 消费者线程2消费时间:1s\n" << endl;
    h_Mutex = CreateMutex(NULL, false, NULL);
    bufferFullSemaphore = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    bufferEmptySemaphore = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer, NULL, 0, &producerID[0]);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer1, NULL, 0, &consumerID[1]);
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer2, NULL, 0, &consumerID[0]);
    while (flag)
    {
        if (getchar())
        {
            flag = false;
        }
        
    }
    system("pause");
    return 0;
}