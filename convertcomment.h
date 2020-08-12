#ifndef _CONVERT_COMMENT_H_
#define _CONVERT_COMMENT_H_

#include"common.h"
#include"sysutil.h"

//ת�������Լ�״̬����������
int ConvertComment(FILE* inputfile, FILE* outputfile);
void EventPro(char ch);
void EventProAtNo(char ch);
void EventProAtC(char ch);
void EventProAtCpp(char ch);
void EventProAtStr(char ch);

//״̬����
typedef enum
{
	NO_COMMENT_STATE,
	C_COMMENT_STATE,
	CPP_COMMENT_STATE,
	STR_STATE,
	END_STATE
}STATE_ENUM;

//״̬������
typedef struct
{
	FILE* inputfile;
	FILE* outputfile;
	STATE_ENUM ulstate;
}State_Manchine;

/////////////////////////////////////////////////////
//����ȫ��״̬������
extern State_Manchine g_state;
/////////////////////////////////////////////////////


#endif /*_CONVERT_COMMENT_H_*/