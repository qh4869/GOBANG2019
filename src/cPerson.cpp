#include "cRole.h"

using namespace std;

void cPerson::CmdInput()
{
	while (1)
	{
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "������������������λ��:";
			cin.clear();//�����־λ
			cin.sync();//���������
		}
		if (((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O')))
			break;
		else
			cout << "���벻�����������꣬���������������λ��:";
	}
}

//���������������
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
	cout << "�����������λ��:";
	CmdInput();
	Char2Position();
}

void cPlayer1::SetFromScreen()
{
	cout << "�����1���������λ��:";
	CmdInput();
	Char2Position();
}

void cPlayer2::SetFromScreen()
{
	cout << "�����2���������λ��:";
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
			cout << "�����Ѿ��������ˣ�";
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