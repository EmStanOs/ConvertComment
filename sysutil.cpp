#include"sysutil.h"

FILE* OpenFile(char* filename, const char* mode)
{
	FILE* fp = fopen(filename, mode);
	if (fp == nullptr)
		ERR_EXIT("OpenFile Error.");
	return fp;
}
void  CloseFile(FILE* fp)
{
	fclose(fp);
}

void WriteDoubleChar(char ch, FILE* fp)
{
	fputc(ch, fp);
	fputc(ch, fp);
}

void WriteDoubleChar(char ch1, char ch2, FILE* fp)
{
	fputc(ch1, fp);
	fputc(ch2, fp);
}

void WriteChar(char ch, FILE* fp)
{
	fputc(ch, fp);
}

void MenuStart(char* src_file, char* dest_file)
{
	system("title 注释转换工具");
	system("mode con cols=36 lines=10");
	system("color 34");
	memset(src_file, 0, sizeof(src_file));
	memset(dest_file, 0, sizeof(dest_file));
	printf("***********注释转换工具************\n");

	printf("* input src  file:>");
	scanf("%s", src_file);
	printf("* input dest file:>");
	scanf("%s", dest_file);
}
void MenuEnd()
{
	int count = 18;
	while (count-- > 0)
	{
		printf("》");
		Sleep(500);
	}
	printf("\n");
	printf("*************转换完成**************\n");
}