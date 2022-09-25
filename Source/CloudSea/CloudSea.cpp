#define _CRT_SECURE_NO_WARNINGS 1

#include"../../Include/Library/InputLibrary/KeyBordAsyncState.h"
#include"../../Include/Library/CLibrary/CLibrary.h"
#include"../../Include/Library/Graphics/Graphics.h"
#include"../../Include/Library/Audio/Audio.h"
#include"../../Include/CloudSea/Size.h"
#include"../../Include/CloudSea/ErrorText.h"

#define PATH_UNDER_DIRAERY_M "open G:\\代码\\Cloud_Sea_\\"
#define PATH_UNDER_DIRAERY_I "G:\\代码\\Cloud_Sea_\\"

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

	mciSendString(PATH_UNDER_DIRAERY_M"src\\LoadingSRC\\audio\\BKmusic.mp3 alias LoadingBGM", 0, 0, 0);
	mciSendString("play LoadingBGM repeat", 0, 0, 0);

	{
		loadimage(&LoadingBK.image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadBK.png", Window_WIDTH, Window_HEIGHT);

		loadimage(&LoadingUP[0].image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadUP1.png", Window_WIDTH, Window_HEIGHT);
		loadimage(&LoadingUP[1].image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadUP2.png", Window_WIDTH, Window_HEIGHT);

		loadimage(&LoadingT[0].image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadT1.png", LoadingT_WIDTH, LoadingT_HEIGHT);
		loadimage(&LoadingT[1].image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadT2.png", LoadingT_WIDTH, LoadingT_HEIGHT);

		loadimage(&LoadingL[0].image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadL1.png", LoadingL_WIDTH, LoadingL_HEIGHT);
		loadimage(&LoadingL[1].image, PATH_UNDER_DIRAERY_I"src\\LoadingSRC\\image\\LoadL2.png", LoadingL_WIDTH, LoadingL_HEIGHT);
	}

	initgraph(Window_WIDTH, Window_HEIGHT);
	setbkcolor(0xFFFFFF);
	settextcolor(0x000000);
	settextstyle(20, 0 , "宋体");
	setbkmode(TRANSPARENT);
	cleardevice();
	system("pause");

	MOUSEMSG mouse_msg = { 0 };

	LoadingL[0].x = (Window_WIDTH - LoadingL_WIDTH) / 2;
	LoadingL[1].x = (Window_WIDTH - LoadingL_WIDTH) / 2;

	bool play = false;

	BeginBatchDraw();
	while (1)
	{
		FlushBatchDraw();
		cleardevice();

		if (MouseHit())
		{
			play = false;
			mouse_msg = GetMouseMsg();
			if ((mouse_msg.x >= Window_WIDTH / 2 - LoadingL_WIDTH / 2) && (mouse_msg.x <= (Window_WIDTH / 2 + LoadingL_WIDTH / 2)))
			{
				play = true;
				if (mouse_msg.mkLButton)
				{
					break;
				}
			}
		}

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

		if (play)
		{
			outtextxy(mouse_msg.x - textwidth("轻点继续") / 2,
				mouse_msg.y - textheight("轻点继续") / 2, "轻点继续");
		}
	}
	EndBatchDraw();
	mciSendString("stop LoadingBGM", 0, 0, 0);
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