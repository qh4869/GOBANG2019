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
@fun 构造函数
@input 游戏模式，玩家先后手
--------------*/
cGame::cGame()
{
	system("cls");
	int ModeInput;
	//输入游戏模式
	cout << "游戏模式选择：1玩家对电脑，2玩家对玩家" << endl;
	cout << "请输入您的选择:";
	while (1)
	{
		while (!(cin >> ModeInput))
		{
			cout << "输入错误，请重新输入:";
			cin.clear();//清除标志位
			cin.sync();
		}
		if (ModeInput == PLAYERVSAI || ModeInput == PLAYERVSPLAYER)
			break;
		else
			cout << "输入错误，请重新输入:";
	}
	GameMode = ModeInput;

	//输入玩家的棋子颜色
	if (GameMode == PLAYERVSAI)
		cout << endl << "玩家棋子选择：1黑色，2白色" << endl;
	else
		cout << endl << "玩家1棋子选择：1黑色，2白色" << endl;
	cout << "请输入您的选择:";
	while (1)
	{
		while (!(cin >> ModeInput))
		{
			cout << "输入错误，请重新输入:";
			cin.clear();//清除标志位
			cin.sync();
		}
		if (ModeInput == BLACK || ModeInput == WHITE)
			break;
		else
			cout << "输入错误，请重新输入:";
	}
	PlayerColor = ModeInput;
	if (PlayerColor == BLACK)
		WhoNext = 1;
	else
		WhoNext = 2;

	cin.sync();// 之前的输入在缓冲区里留下了一个回车，不清除第一次输入会出错

	// 角色指针初始化
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
@fun 析构函数，释放内存
--------------------*/
cGame::~cGame()
{
	delete pRole1;
	delete pRole2;
}

//返回1 代表继续下一盘
//返回0 代表退出
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
	//输出比赛结果
	if (result == BLACK)
	{
		if (GameMode == PLAYERVSPLAYER)
		{
			if (PlayerColor == BLACK)
				cout << "玩家1获胜" << endl;
			else
				cout << "玩家2获胜" << endl;
		}
		if (GameMode == PLAYERVSAI)
		{
			if (PlayerColor == BLACK)
				cout << "玩家获胜" << endl;
			else
				cout << "电脑获胜" << endl;
		}
	}
	else if (result == WHITE)
	{
		if (GameMode == PLAYERVSPLAYER)
		{
			if (PlayerColor == BLACK)
				cout << "玩家2获胜" << endl;
			else
				cout << "玩家1获胜" << endl;
		}
		if (GameMode == PLAYERVSAI)
		{
			if (PlayerColor == BLACK)
				cout << "电脑获胜" << endl;
			else
				cout << "玩家获胜" << endl;
		}
	}
	else if (result == FORBIDDEN)
	{
		if (GameMode == PLAYERVSPLAYER)
		{
			if (PlayerColor == BLACK)
				cout << "玩家1禁手，玩家2获胜" << endl;
			else
				cout << "玩家2禁手，玩家1获胜" << endl;
		}
		if (GameMode == PLAYERVSAI)
		{
			if (PlayerColor == BLACK)
				cout << "玩家禁手，电脑获胜" << endl;
			else
				cout << "电脑禁手，玩家获胜" << endl;//不应该出现
		}
	}
	else if (result == EQUAL)
	{
		cout << "平局" << endl;
	}
	char again;
	cout << "想要再来一盘吗？(Y/N)" << endl;
	again = cin.get();
	cin.clear();
	cin.sync();
	if (again == 'Y' || again == 'y')
		return 1;
	else
		return 0;
}
