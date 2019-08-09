#include "cGame.h"

using namespace std;

void cGame::SetAtGameMode(int mode)
{
	GameMode = mode;
}

int cGame::GetATGameMode()
{
	return GameMode;
}

void cGame::WhoFirst(int who)
{
	WhoNext = who;
}

void cGame::fnExchange()
{
	WhoNext = WhoNext % 2 + 1;
}

int cGame::GetAtWhoNext()
{
	return WhoNext;
}
void cGame::SetAtPlayerColor(int color)
{
	PlayerColor = color;
}

int cGame::GetAtPlayerColor()
{
	return PlayerColor;
}

/*-------------
@fun ���캯��
@input ��Ϸģʽ������Ⱥ���
--------------*/
cGame::cGame()
{
	system("cls");
	int ModeInput;
	//������Ϸģʽ
	cout << "��Ϸģʽѡ��1��ҶԵ��ԣ�2��Ҷ����" << endl;
	cout << "����������ѡ��:";
	while (1)
	{
		while (!(cin >> ModeInput))
		{
			cout << "�����������������:";
			cin.clear();//�����־λ
			cin.sync();
		}
		if (ModeInput == PLAYERVSAI || ModeInput == PLAYERVSPLAYER)
			break;
		else
			cout << "�����������������:";
	}
	GameMode = ModeInput;

	//������ҵ�������ɫ
	if (GameMode == PLAYERVSAI)
		cout << endl << "�������ѡ��1��ɫ��2��ɫ" << endl;
	else
		cout << endl << "���1����ѡ��1��ɫ��2��ɫ" << endl;
	cout << "����������ѡ��:";
	while (1)
	{
		while (!(cin >> ModeInput))
		{
			cout << "�����������������:";
			cin.clear();//�����־λ
			cin.sync();
		}
		if (ModeInput == BLACK || ModeInput == WHITE)
			break;
		else
			cout << "�����������������:";
	}
	PlayerColor = ModeInput;
	if (PlayerColor == BLACK)
		WhoNext = 1;
	else
		WhoNext = 2;

	cin.sync();// ֮ǰ�������ڻ�������������һ���س����������һ����������

	// ��ɫָ���ʼ��
	if (GameMode==PLAYERVSAI){
		pRole1 = new cPlayer0;
		pRole2 = new cAI;
	}
	else{
		pRole1 = new cPlayer1;
		pRole2 = new cPlayer2;
	}
}

/*------------------
@fun �����������ͷ��ڴ�
--------------------*/
cGame::~cGame()
{
	delete pRole1;
	delete pRole2;
}

//����1 ���������һ��
//����0 �����˳�
int cGame::Gaming()
{
	oBoard.RefreshScreen();
	while (1)
	{
		if (WhoNext == ROLE1)// PLAYER or PLAYER1
		{
			pRole1->SetAtPosition(oBoard, PlayerColor);
			oBoard.SetAtTable(pRole1->GetAtRow(), pRole1->GetAtColumn(), PlayerColor);
			oBoard.RefreshScreen(pRole1->GetAtRow(), pRole1->GetAtColumn());
			fnExchange();
			result = oBoard.referee(pRole1->GetAtRow(), pRole1->GetAtColumn());
			if (result)
				break;
		}
		else if (WhoNext == ROLE2)// AI or PLAYER2
		{
			pRole2->SetAtPosition(oBoard, PlayerColor);
			oBoard.SetAtTable(pRole2->GetAtRow(), pRole2->GetAtColumn(), PlayerColor % 2 + 1);
			oBoard.RefreshScreen(pRole2->GetAtRow(), pRole2->GetAtColumn());
			fnExchange();
			result = oBoard.referee(pRole2->GetAtRow(), pRole2->GetAtColumn());
			if (result)
				break;
		}
	}
	return ShowResult();
}

int cGame::ShowResult()
{
	//����������
	if (result == BLACK)
	{
		if (GameMode == PLAYERVSPLAYER)
		{
			if (PlayerColor == BLACK)
				cout << "���1��ʤ" << endl;
			else
				cout << "���2��ʤ" << endl;
		}
		if (GameMode == PLAYERVSAI)
		{
			if (PlayerColor == BLACK)
				cout << "��һ�ʤ" << endl;
			else
				cout << "���Ի�ʤ" << endl;
		}
	}
	else if (result == WHITE)
	{
		if (GameMode == PLAYERVSPLAYER)
		{
			if (PlayerColor == BLACK)
				cout << "���2��ʤ" << endl;
			else
				cout << "���1��ʤ" << endl;
		}
		if (GameMode == PLAYERVSAI)
		{
			if (PlayerColor == BLACK)
				cout << "���Ի�ʤ" << endl;
			else
				cout << "��һ�ʤ" << endl;
		}
	}
	else if (result == FORBIDDEN)
	{
		if (GameMode == PLAYERVSPLAYER)
		{
			if (PlayerColor == BLACK)
				cout << "���1���֣����2��ʤ" << endl;
			else
				cout << "���2���֣����1��ʤ" << endl;
		}
		if (GameMode == PLAYERVSAI)
		{
			if (PlayerColor == BLACK)
				cout << "��ҽ��֣����Ի�ʤ" << endl;
			else
				cout << "���Խ��֣���һ�ʤ" << endl;//��Ӧ�ó���
		}
	}
	else if (result == EQUAL)
	{
		cout << "ƽ��" << endl;
	}
	char again;
	cout << "��Ҫ����һ����(Y/N)" << endl;
	again = cin.get();
	cin.clear();
	cin.sync();
	if (again == 'Y' || again == 'y')
		return 1;
	else
		return 0;
}
