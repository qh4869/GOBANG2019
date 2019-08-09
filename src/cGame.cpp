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

	if (GameMode == PLAYERVSPLAYER)
	{
		cPlayer1 oPlayer1;
		cPlayer2 oPlayer2;
		while (1)
		{
			if (WhoNext == PLAYER1)
			{
				oPlayer1.SetAtPosition();
				while (oBoard.WhetherEmpty(oPlayer1.GetAtRow(), oPlayer1.GetAtColumn()) == NEMPTY)
				{
					cout << "�����Ѿ��������ˣ�";
					oPlayer1.SetAtPosition();
				}
				oBoard.SetAtTable(oPlayer1.GetAtRow(), oPlayer1.GetAtColumn(), PlayerColor);
				oBoard.RefreshScreen(oPlayer1.GetAtRow(), oPlayer1.GetAtColumn());
				fnExchange();//������һ������Ľ�ɫ
				result = oBoard.referee(oPlayer1.GetAtRow(), oPlayer1.GetAtColumn());
				if (result)
					break;

			}
			else if (WhoNext == PLAYER2)
			{
				oPlayer2.SetAtPosition();
				while (oBoard.WhetherEmpty(oPlayer2.GetAtRow(), oPlayer2.GetAtColumn()) == NEMPTY)
				{
					cout << "�����Ѿ��������ˣ�";
					oPlayer2.SetAtPosition();
				}
				oBoard.SetAtTable(oPlayer2.GetAtRow(), oPlayer2.GetAtColumn(), PlayerColor % 2 + 1);
				oBoard.RefreshScreen(oPlayer2.GetAtRow(), oPlayer2.GetAtColumn());
				fnExchange();
				result = oBoard.referee(oPlayer2.GetAtRow(), oPlayer2.GetAtColumn());
				if (result)
					break;
			}
		}
	}
	else if (GameMode == PLAYERVSAI)
	{
		cPlayer0 oPlayer0;
		cAI oAI;
		while (1)
		{
			if (WhoNext == PLAYER)
			{
				oPlayer0.SetAtPosition();
				while (oBoard.WhetherEmpty(oPlayer0.GetAtRow(), oPlayer0.GetAtColumn()) == NEMPTY)
				{
					cout << "�����Ѿ��������ˣ�";
					oPlayer0.SetAtPosition();
				}
				oBoard.SetAtTable(oPlayer0.GetAtRow(), oPlayer0.GetAtColumn(), PlayerColor);
				oBoard.RefreshScreen(oPlayer0.GetAtRow(), oPlayer0.GetAtColumn());
				fnExchange();
				result = oBoard.referee(oPlayer0.GetAtRow(), oPlayer0.GetAtColumn());
				if (result)
					break;
			}
			else if (WhoNext == AI)
			{
				oAI.AIAlgorithm(oBoard, PlayerColor, AI);
				oAI.AIAlgorithm(oBoard, PlayerColor, PLAYER);
				if (oAI.SearchForBestPosition() == -1)//û�еط����������ˣ�����
				{
					result = EQUAL;
					break;
				}
				oBoard.SetAtTable(oAI.GetAtRow(), oAI.GetAtColumn(), PlayerColor % 2 + 1);
				oBoard.RefreshScreen(oAI.GetAtRow(), oAI.GetAtColumn());
				fnExchange();
				result = oBoard.referee(oAI.GetAtRow(), oAI.GetAtColumn());
				if (result)
					break;
			}
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
	char c;
	cout << "��Ҫ����һ����(Y/N)" << endl;
	again = cin.get();
	do {
		c = cin.get();
	} while (c != '\n');
	if (again == 'Y' || again == 'y')
		return 1;
	else
		return 0;
}
