#pragma once

#include "cBoard.h"
#include "cManager.h"

class cAI
{
private:
	int AIChart[15][15][5];
	int PlayerChart[15][15][5];
	int AddChart[15][15][5];
	int AIPositionI;
	int AIPositionJ;
public:
	cAI();
	void RefreshChart(cBoard, int, int);
	void SearchForBestPosition();
	void SetBothChartsZero(int, int);
	int GetAtPositionI();
	int GetAtPositionJ();
};