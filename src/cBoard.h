#pragma once
#include "macro.h"
#include <iostream>
#include <cstdlib>

class cBoard
{
private:
	int aTable[15][15];

public:
	int GetAtTable(int, int);
	void SetAtTable(int, int, int);
	cBoard();
	//关键点检测，判断构成活三，冲四，活四的必要条件之一
	bool KeyPointCheck(const int x, const int y, int adjsame,int direction);
	int referee(const int, const int); //裁判函数
	void SetToZero();
	void RefreshScreen(int iPositioni = -1, int iPosintionj = -1);
	int WhetherEmpty(int, int);
};
