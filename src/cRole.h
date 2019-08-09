#pragma once
#include "macro.h"
#include <iostream>
#include <ctime>
#include "cBoard.h"
#include <cstdlib>
#include <math.h>
#include <cstring>
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
	virtual void SetAtPosition(cBoard oBoard, int PlayerColor) = 0;// ������λ��д��row��column��
};

class cAI : public cRole
{
protected:
	int AIChart[15][15];
	int PlayerChart[15][15];
	int AddChart[15][15];

public:
	cAI();
	void AIAlgorithm(cBoard oBoard, int PlayerColor, int type);
	int SearchForBestPosition();
	virtual void SetAtPosition(cBoard oBoard, int PlayerColor);
	void SetBothChartsZero(int, int);
};

class cPerson : public cRole
{
protected:
	char PositionInput[3];

public:
	virtual void SetFromScreen() = 0;
	void CmdInput();
    void Char2Position();
	virtual void SetAtPosition(cBoard oBoard, int PlayerColor);
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
