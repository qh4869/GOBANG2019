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
	int result;//���к����ķ���ֵ

public:
	void SetAtGameMode(int);
	int GetATGameMode();
	void WhoFirst(int);
	void fnExchange();//������һ����������
	int GetAtWhoNext();
	void SetAtPlayerColor(int);
	int GetAtPlayerColor();
	void ModeChoice();
	int referee(cBoard, const int, const int);//���к���
	bool KeyPointCheck(cBoard oBoard, const int x, const int y, int adjsame, int direction);
	int Gaming(cBoard&);//��Ϸ��ս��
	int ShowResult();//�����Ϸ�������ѯ���Ƿ������һ��1������� 0 ��������
};
