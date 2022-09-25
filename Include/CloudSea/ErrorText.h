#pragma once

#include<cstdio>

#define ERRORTEXT(ERR_STR) FILE* ErrorFile = fopen("Error.txt", "a+t");\
if (!ErrorFile)\
{\
	perror("\n"); \
		system("pause"); \
		return EOF; \
}\
fprintf(ErrorFile, "Date:%s Time:%s Line:%d File:%s ",\
	__DATE__, __TIME__, __LINE__, __FILE__);\
fprintf(ErrorFile, ERR_STR);\
fclose(ErrorFile);\
ErrorFile = NULL;// '\'后必须有下一行