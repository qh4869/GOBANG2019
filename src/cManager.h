#pragma once
#include "cBoard.h"
#include "cRole.h"
#include "macro.h"
#include <iostream>
#include <cstdlib>

class cManager
{
private:
	int GameMode;
	int WhoNext;
	int PlayerColor;
	int result;//裁判函数的返回值

public:
	void SetAtGameMode(int);
	int GetATGameMode();
	void WhoFirst(int);
	void fnExchange();//交换下一步下棋的玩家
	int GetAtWhoNext();
	void SetAtPlayerColor(int);
	int GetAtPlayerColor();
	void ModeChoice();
	int referee(cBoard, const int, const int);//裁判函数
	bool KeyPointCheck(cBoard oBoard, const int x, const int y, int adjsame, int direction);
	int Gaming(cBoard&);//游戏对战中
	int ShowResult();//输出游戏结果，并询问是否继续下一盘1代表继续 0 代表不继续
};
