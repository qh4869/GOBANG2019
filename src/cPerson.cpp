#include "cRole.h"

using namespace std;

//MSDN上的原话
//vs2015用sync，输入流缓冲区清除不掉
//https://blogs.msdn.microsoft.com/c/2016/04/15/visual-c-2015-update-2-bug-%E4%BF%AE%E5%A4%8D/
//cin.sync() and fflush(stdin) do not work with Visual Studio 2015
void cPlayer0::SetFromScreen()
{
	char c;
	cout << "请输入下棋的位置:";
	//cin.sync();//清除缓冲区
	cin.clear();//清除标志位
	while (!(cin.getline(PositionInput, 3)))
	{
		cout << "输入错误，请输入下棋的位置:";
		//cin.sync();//清除缓冲区
		cin.clear();//清除标志位
		do {
			c = cin.get();
		} while (c != '\n');
		
	}
	while (!(((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O'))))
	{
		cout << "输入错误，请输入下棋的位置:";
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "输入错误，请输入下棋的位置:";
			//cin.sync();//清除缓冲区
			cin.clear();//清除标志位
			do {
				c = cin.get();
			} while (c != '\n');
		}
	}
}

void cPlayer1::SetFromScreen()
{
	char c;
	cout << "请玩家1输入下棋的位置:";
	//cin.sync();//清除缓冲区
	cin.clear();//清除标志位
	while (!(cin.getline(PositionInput, 3)))
	{
		cout << "输入错误，请玩家1输入下棋的位置:";
		//cin.sync();//清除缓冲区
		cin.clear();//清除标志位
		do {
			c = cin.get();
		} while (c != '\n');
	}
	while (!(((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O'))))
	{
		cout << "输入错误，请玩家1输入下棋的位置";
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "输入错误，请玩家1输入下棋的位置:";
			//cin.sync();//清除缓冲区
			cin.clear();//清除标志位
			do {
				c = cin.get();
			} while (c != '\n');
		}
	}
}

void cPlayer2::SetFromScreen()
{
	char c;
	cout << "请玩家2输入下棋的位置:";
	//cin.sync();//清除缓冲区
	cin.clear();//清除标志位
	while (!(cin.getline(PositionInput, 3)))
	{
		cout << "输入错误，请玩家2输入下棋的位置:";
		//cin.sync();//清除缓冲区
		cin.clear();//清除标志位
		do {
			c = cin.get();
		} while (c != '\n');
	}
	while (!(((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O'))))
	{
		cout << "输入错误，请玩家2输入下棋的位置";
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "输入错误，请玩家2输入下棋的位置:";
			//cin.sync();//清除缓冲区
			cin.clear();//清除标志位
			do {
				c = cin.get();
			} while (c != '\n');
		}
	}
}

//翻译成行数和列数
inline void cPerson::Char2Position()
{
	if (PositionInput[0] >= '0'&&PositionInput[0] <= '9')
		row = PositionInput[0] - '0';
	else if (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e')
		row = PositionInput[0] - 'a' + 10;
	else if (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')
		row = PositionInput[0] - 'A' + 10;
	if (PositionInput[1] >= 'a'&&PositionInput[1] <= 'o')
		column = PositionInput[1] - 'a';
	else if (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O')
		column = PositionInput[1] - 'A';
}

void cPerson::SetAtPosition()
{
	SetFromScreen();
	Char2Position();
}

int cRole::GetAtRow()
{
	return row;
}

int cRole::GetAtColumn()
{
	return column;
}