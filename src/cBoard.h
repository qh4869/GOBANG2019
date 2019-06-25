#pragma once
#include "macro.h"
#include <process.h>
#include <iostream>
class cBoard
{
private:
	int aTable[15][15];

public:
	int GetAtTable(int, int);
	void SetAtTable(int, int, int);
	cBoard();
	void SetToZero();
	void RefreshScreen(int iPositioni = -1, int iPosintionj = -1);
	int WhetherEmpty(int, int);
};