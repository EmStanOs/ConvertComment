#include"convertcomment.h"

int main(int argc, char* argv[])
{
	char src_file[MAX_FILENAME_SIZE];
	char dest_file[MAX_FILENAME_SIZE];
	MenuStart(src_file, dest_file);

	FILE* fpIn = OpenFile(src_file, "r");
	FILE* fpOut = OpenFile(dest_file, "w");

	//×¢ÊÍ×ª»»¹ý³Ì
	ConvertComment(fpIn, fpOut);

	CloseFile(fpIn);
	CloseFile(fpOut);

	MenuEnd();

	return 0;
}