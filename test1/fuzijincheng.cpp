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
		printf("�Ѵ���һ���ӽ���\n");
		for (int i = 1; i <= 100; i++)
		{
			sum = sum + i; // ��1-100֮��
			Sleep(5);	   // �ӳ�ʱ��5ms
			printf("Now, sum = %d\n", sum);
		}
		WaitForSingleObject(pi.hProcess, 5000); // һֱ����ȥֱ�����̽���
		FILE *fp = fopen("D:\\test.txt", "r");
		fread(content, sizeof(char), 100, fp); // ���ö�ȡ�ļ����ݵ���ز���
		printf("�ӽ��̴������ļ���������:\n\n%s\n\n", content);
		fclose(fp);
	}
	else
	printf("�����ӽ���ʧ��\n");
	printf("ʵ�������");
	system("pause");
	return 0;
}