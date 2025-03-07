#include<stdio.h>
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
	
	if(CreateProcess(".\\child.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &sui, &pi))
	{
		printf("已创建一个子进程\n");
		for (int i = 1; i <= 100; i++)
		{
			sum = sum + i; // 求1-100之和
			Sleep(5);	   // 延迟时间5ms
			printf("Now, sum = %d\n", sum);
		}
		WaitForSingleObject(pi.hProcess, 5000); // 一直等下去直到进程结束
		FILE *fp = fopen("D:\\test.txt", "r");
		fread(content, sizeof(char), 100, fp); // 设置读取文件内容的相关参数
		printf("子进程创建的文件内容如下:\n\n%s\n\n", content);
		fclose(fp);
	}
	else
	printf("创建子进程失败\n");
	printf("实验结束！");
	system("pause");
	return 0;
}