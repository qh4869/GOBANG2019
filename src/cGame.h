#pragma once
#include "cBoard.h"
#include "cRole.h"
#include "macro.h"
#include <iostream>
#include <cstdlib>

class cGame
{
private:
	int GameMode;// PLAYERVSPLAYER or PLAYERVSAI
	int WhoNext;// PLAYER or AI for Mode PLAYERVSAI; PLAYER1 or PLAYER2 for Mode PLAYERVSPLAYER
	int PlayerColor;// BLACK or WHITE for PLAYER or PLAYER1
	int result;// 1 BLACK胜不禁手 2 WHITE胜不禁手 3 FORBIDDEN黑色禁手白色胜 0平局
	cBoard oBoard;// 棋盘
	cRole* pRole1;// 角色1指针
	cRole* pRole2;// 角色2指针

public:
	cGame();
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
	int Gaming();//游戏对战中
	int ShowResult();//输出游戏结果，并询问是否继续下一盘1代表继续 0 代表不继续
};
