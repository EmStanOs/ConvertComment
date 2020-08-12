#include"convertcomment.h"

State_Manchine g_state; /*全局状态机变量*/
static STATE_ENUM pre_global_state; /*先前状态机处理状态*/

int ConvertComment(FILE* inputfile, FILE* outputfile)
{
	if (inputfile == nullptr || outputfile == nullptr)
		ERR_EXIT("Argument Error.");

	//////////////////////////////////////////////////////
	//初始化状态机
	g_state.inputfile = inputfile;
	g_state.outputfile = outputfile;
	g_state.ulstate = NO_COMMENT_STATE;

	char ch{};
	while (g_state.ulstate != END_STATE)
	{
		ch = fgetc(g_state.inputfile);
		EventPro(ch);
	}
	return  0;
}

void EventPro(char ch)
{
	switch (g_state.ulstate)
	{
	case NO_COMMENT_STATE:
		EventProAtNo(ch);
		break;
	case C_COMMENT_STATE:
		EventProAtC(ch);
		break;
	case CPP_COMMENT_STATE:
		EventProAtCpp(ch);
		break;
	case STR_STATE:
		EventProAtStr(ch);
		break;
	default:
		ERR_EXIT("State Error.");
		break;
	}
}

void EventProAtNo(char ch)
{
	char nextch{};
	switch (ch)
	{
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/') // C++ Comment start
		{
			WriteDoubleChar('/', '*', g_state.outputfile);
			g_state.ulstate = CPP_COMMENT_STATE;
		}
		else if (nextch == '*') /* C */
		{
			WriteDoubleChar('/', '*', g_state.outputfile);
			g_state.ulstate = C_COMMENT_STATE;
		}
		break;
	case EOF:
		g_state.ulstate = END_STATE;
		break;

	case '"':
		WriteChar(ch, g_state.outputfile);
		pre_global_state = g_state.ulstate;
		g_state.ulstate = STR_STATE;
		break;
	default:
		WriteChar(ch, g_state.outputfile);
		break;
	}
}

void EventProAtC(char ch)
{
	char nextch{};
	switch (ch)
	{
	case '*':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')     /* C注释结束*/
		{
			WriteDoubleChar('*', '/', g_state.outputfile);
			g_state.ulstate = NO_COMMENT_STATE;
		}
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')    /*  //  */
		{
			WriteDoubleChar(' ', g_state.outputfile);
		}
		break;
	case '"':
		WriteChar(ch, g_state.outputfile);
		pre_global_state = g_state.ulstate;
		g_state.ulstate = STR_STATE;
		break;
	default:
		WriteChar(ch, g_state.outputfile);
		break;
	}
}

void EventProAtCpp(char ch)
{
	char nextch{};
	switch (ch)
	{
	case EOF:
		WriteDoubleChar('*', '/', g_state.outputfile);
		g_state.ulstate = END_STATE;
		break;
	case '\n':
		WriteDoubleChar('*', '/', g_state.outputfile);
		WriteChar(ch, g_state.outputfile);
		g_state.ulstate = NO_COMMENT_STATE;
		break;
	case '/':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/' || nextch == '*')  //     //
		{
			WriteDoubleChar(' ', g_state.outputfile);
		}
		break;
	case '*':
		nextch = fgetc(g_state.inputfile);
		if (nextch == '/')    //   */
		{
			WriteDoubleChar(' ', g_state.outputfile);
		}
		else
		{
			WriteDoubleChar('*', nextch, g_state.outputfile);
		}
		break;
	case '"':
		WriteChar('"', g_state.outputfile);
		pre_global_state = g_state.ulstate;
		g_state.ulstate = STR_STATE;
		break;
	default:
		WriteChar(ch, g_state.outputfile);
		break;

	}
}

void EventProAtStr(char ch)
{
	switch (ch)
	{
	case '"':
		WriteChar(ch, g_state.outputfile);
		g_state.ulstate = pre_global_state;
		break;
	case EOF:
		if (pre_global_state == CPP_COMMENT_STATE)
		{
			WriteDoubleChar('*', '/', g_state.outputfile);
		}
		else if (pre_global_state == C_COMMENT_STATE)
		{
		}
		g_state.ulstate = END_STATE;
		break;
	case '\n':
		if (pre_global_state == CPP_COMMENT_STATE)
		{
			g_state.ulstate = pre_global_state;
		}
		break;
	default:
		WriteChar(ch, g_state.outputfile);
		break;
	}
}