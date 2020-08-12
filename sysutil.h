#ifndef _SYSUTIL_H_
#define _SYSUTIL_H_

#include"common.h"

#define MAX_FILENAME_SIZE 1024

#define ERR_EXIT(m) \
	do\
	{\
		printf(m);\
		exit(1);\
	}while(0)


FILE* OpenFile( char* filename, const char* mode);
void  CloseFile(FILE* fp);

void WriteDoubleChar(char ch, FILE* fp);
void WriteDoubleChar(char ch1, char ch2, FILE* fp);
void WriteChar(char ch, FILE* fp);

void MenuStart(char* src_file, char* dest_file);
void MenuEnd();
#endif /*_SYSUTIL_H_*/