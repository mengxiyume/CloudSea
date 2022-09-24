#define _CRT_SECURE_NO_WARNINGS 1

#include"../../Include/Library/InputLibrary/KeyBordAsyncState.h"
#include"../../Include/Library/CLibrary/CLibrary.h"
#include"../../Include/Library/Graphics/Graphics.h"
#include"../../Include/CloudSea/Size.h"
#include"../../Include/CloudSea/ErrorText.h"


typedef struct Image
{
	int x;
	int y;
	int width;
	int height;
	IMAGE image;
}Image;

void PutPNG(Image* const sourse)
{
	putimage(sourse[0].x, sourse[0].y, &sourse[0].image, NOTSRCERASE);
	putimage(sourse[1].x, sourse[1].y, &sourse[1].image, SRCINVERT);
}

bool LoadOpen()
{

	Image LoadingBK = { 0 };
	Image LoadingUP[2] = { 0 };
	Image LoadingT[2] = { 0 };
	Image LoadingL[2] = { 0 };

	loadimage(&LoadingBK.image, " ../../src/image/LoadBK.png", Window_WIDTH, Window_HEIGHT);
	loadimage(&LoadingUP[0].image, " ../../src/image/LoadUP1.png", Window_WIDTH, Window_HEIGHT);
	loadimage(&LoadingUP[1].image, " ../../src/image/LoadUP2.png", Window_WIDTH, Window_HEIGHT);

	loadimage(&LoadingT[0].image, " ../../src/image/LoadT1.png", LoadingT_WIDTH, LoadingT_HEIGHT);
	loadimage(&LoadingT[1].image, " ../../src/image/LoadT2.png", LoadingT_WIDTH, LoadingT_HEIGHT);

	loadimage(&LoadingL[0].image, " ../../src/image/LoadL1.png", LoadingL_WIDTH, LoadingL_HEIGHT);
	loadimage(&LoadingL[1].image, " ../../src/image/LoadL2.png", LoadingL_WIDTH, LoadingL_HEIGHT);

	initgraph(Window_WIDTH, Window_HEIGHT);
	setbkcolor(0xFFFFFF);
	cleardevice();
	system("pause");

	LoadingL[0].x = (Window_WIDTH - LoadingL_WIDTH) / 2;
	LoadingL[1].x = (Window_WIDTH - LoadingL_WIDTH) / 2;

	BeginBatchDraw();
	while (1)
	{
		FlushBatchDraw();
		cleardevice();
		putimage(LoadingBK.x, LoadingBK.y, &LoadingBK.image);

		PutPNG(LoadingUP);
		PutPNG(LoadingL);

		if (LoadingL[0].y > -70)
		{
			LoadingL[0].y-= Loading_V;
			LoadingL[1].y-= Loading_V;
		}
		else
		{
			LoadingL[0].y = 0;
			LoadingL[1].y = 0;
		}

		PutPNG(LoadingT);
	}
	EndBatchDraw();
	closegraph();
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

void MainUI()
{
	//主界面ui


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
	

	MainUI();


	//do {
	//	//输入
	//	keyBoardAsyncKeyState(key_board_input, key_board_open_state);
	//
	//	//更新
	//	//	判断行为
	//	if (key_board_input->Esc)
	//	{
	//		ERRORTEXT("NO_ERROR\n");
	//		return 0;
	//	}
	//
	//	//输出
	//	GameOput();
	//
	//} while (i);


	free(key_board_input);
	free(key_board_open_state);
	key_board_input = key_board_open_state = NULL;

	return EOF;
}