#pragma once
#include "cBoard.h"
#include "cManager.h"
#include "macro.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
//角色类派生人类和AI类
//人类派生出与电脑对决的玩家0类、互相PK的玩家1类和玩家2类
class cRole
{
protected:
	int row;
	int column;

public:
	int GetAtRow();
	int GetAtColumn();
};
 
class cAI : public cRole
{
protected:
	int AIChart[15][15];
	int PlayerChart[15][15];
	int AddChart[15][15];

public:
	cAI();
	void RefreshChart(cBoard, int, int);
	int SearchForBestPosition();
	void SetBothChartsZero(int, int);
};
class cPerson : public cRole
{
protected:
	char PositionInput[3];

public:
	virtual void SetFromScreen() = 0;
    void Char2Position();
	void SetAtPosition();
};

class cPlayer0 : public cPerson
{
public:
	virtual void SetFromScreen();
};

class cPlayer1 : public cPerson
{
public:
	virtual void SetFromScreen();
};

class cPlayer2 : public cPerson
{
public:
	virtual void SetFromScreen();
};