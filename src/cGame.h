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
	int result;// 1 BLACKʤ������ 2 WHITEʤ������ 3 FORBIDDEN��ɫ���ְ�ɫʤ 0ƽ��
	cBoard oBoard;// ����
	cRole* pRole1;// ��ɫ1ָ��
	cRole* pRole2;// ��ɫ2ָ��

public:
	cGame();
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
	int Gaming();//��Ϸ��ս��
	int ShowResult();//�����Ϸ�������ѯ���Ƿ������һ��1������� 0 ��������
};
