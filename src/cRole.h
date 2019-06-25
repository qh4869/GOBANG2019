#pragma once
#include "cBoard.h"
#include "cManager.h"
#include "macro.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <math.h>
//��ɫ�����������AI��
//��������������ԶԾ������0�ࡢ����PK�����1������2��
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