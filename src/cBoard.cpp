#include "cBoard.h"
using namespace std;

void cBoard::SetAtTable(int i, int j, int TableState)
{
	aTable[i][j] = TableState;
}

int cBoard::GetAtTable(int i, int j)
{
	return aTable[i][j];
}

cBoard::cBoard()
{
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
			aTable[i][j] = EMPTY;
}

void cBoard::RefreshScreen(int iPositioni, int iPosintionj)
{
	int i, j;
	system("cls");//命令行清屏
	cout << "              五子棋  Made By QH" << endl;
	cout << "=================================================" << endl;
	for (i = 0; i<15; i++)
	{
		cout << '\t';
		if (i<10)
			cout << i;
		else
			cout << (char)(i + 55);
		for (j = 0; j<15; j++)
		{
			if (aTable[i][j] == BLACK && !(i == iPositioni && j == iPosintionj))
				cout << "●";
			else if (aTable[i][j] == BLACK && i == iPositioni && j == iPosintionj)
				cout << "▲";
			else if (aTable[i][j] == WHITE && !(i == iPositioni && j == iPosintionj))
				cout << "○";
			else if (aTable[i][j] == WHITE && i == iPositioni && j == iPosintionj)
				cout << "△";
			else if (i == 0 && j == 0)
				cout << "┏";
			else if (i == 0 && j == 14)
				cout << "┓";
			else if (i == 0)
				cout << "┳";
			else if (i == 14 && j == 0)
				cout << "┗";
			else if (i == 14 && j == 14)
				cout << "┛";
			else if (i == 14)
				cout << "┻";
			else if (j == 0)
				cout << "┣";
			else if (j == 14)
				cout << "┫";
			else
				cout << "╋";

		}
		cout << endl;
	}
	cout << '\t';
	cout << "  A B C D E F G H I J K L M N O " << endl;
	cout << "=================================================" << endl;
}

//判断该位置有无棋子
int cBoard::WhetherEmpty(int i, int j)
{
	if (aTable[i][j] == EMPTY)
		return YEMPTY;
	else
		return NEMPTY;
}

void cBoard::SetToZero()
{
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
			aTable[i][j] = EMPTY;
}