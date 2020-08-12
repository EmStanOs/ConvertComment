#ifndef _CONVERT_COMMENT_H_
#define _CONVERT_COMMENT_H_

#include"common.h"
#include"sysutil.h"

//转换函数以及状态函数的声明
int ConvertComment(FILE* inputfile, FILE* outputfile);
void EventPro(char ch);
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
void EventProAtStr(char ch);

//状态定义
typedef enum
{
	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	STR_STATE,
	END_STATE
}STATE_ENUM;

//状态机定义
typedef struct
{
	FILE* inputfile;
	FILE* outputfile;
	STATE_ENUM ulstate;
}State_Manchine;

/////////////////////////////////////////////////////
//声明全局状态机变量
extern State_Manchine g_state;
/////////////////////////////////////////////////////


#endif /*_CONVERT_COMMENT_H_*/