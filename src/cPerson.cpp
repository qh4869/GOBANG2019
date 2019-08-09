#include "cRole.h"

using namespace std;

void cPerson::CmdInput()
{
	while (1)
	{
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "输入错误，请输入下棋的位置:";
			cin.clear();//清除标志位
			cin.sync();//清除缓冲区
		}
		if (((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O')))
			break;
		else
			cout << "输入不符合棋盘坐标，请重新输入下棋的位置:";
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

void cPlayer0::SetFromScreen()
{
	cout << "请输入下棋的位置:";
	CmdInput();
	Char2Position();
}

void cPlayer1::SetFromScreen()
{
	cout << "请玩家1输入下棋的位置:";
	CmdInput();
	Char2Position();
}

void cPlayer2::SetFromScreen()
{
	cout << "请玩家2输入下棋的位置:";
	CmdInput();
	Char2Position();
}

void cPerson::SetAtPosition(cBoard oBoard, int PlayerColor)
{
	while (1){
		SetFromScreen();
		if (oBoard.WhetherEmpty(GetAtRow(), GetAtColumn()) == EMPTY)
			break;
		else
			cout << "这里已经有棋子了，";
	}
}

int cRole::GetAtRow()
{
	return row;
}

int cRole::GetAtColumn()
{
	return column;
}