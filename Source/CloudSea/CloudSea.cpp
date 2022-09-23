#define _CRT_SECURE_NO_WARNINGS 1

#include"../../Include/Library/InputLibrary/KeyBordAsyncState.h"
#include"../../Include/Library/CLibrary/CLibrary.h"

#define ERRORTEXT(ERR_STR) \
FILE* ErrorFile = fopen("Error.txt", "a+t");\
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
ErrorFile = NULL;\

bool LoadOpen()
{
	return true;
}

bool InitOpen()
{

	return true;
}

bool OpenGame(KeyBoard* key)
{
	assert(LoadOpen());
	//使用多线程优化
	assert(InitOpen());

	key->Esc = true;
	return true;
}

void GameOput()
{
	//游戏画面的显示输出
	;
}

int CloudSea(void)
{
	bool i = true;
	KeyBoard *key_board_input = (KeyBoard*)calloc(1, sizeof(KeyBoard)),
		*key_board_open_state = (KeyBoard*)calloc(1, sizeof(KeyBoard));
	if (!(key_board_input && key_board_open_state))
	{
		ERRORTEXT("NO_MEMRY\n");
		return EOF;
	}
	if (!OpenGame(key_board_open_state))
		return EOF;
	
	do {
		//输入
		keyBoardAsyncKeyState(key_board_input, key_board_open_state);

		//更新
		//	判断行为
		if (key_board_input->Esc)
		{
			ERRORTEXT("NO_ERROR\n");
			return 0;
		}

		//输出
		GameOput();

	} while (i);


	free(key_board_input);
	free(key_board_open_state);
	key_board_input = key_board_open_state = NULL;

	return EOF;
}