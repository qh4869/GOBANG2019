#include "cRole.h"

using namespace std;

//MSDN�ϵ�ԭ��
//vs2015��sync���������������������
//https://blogs.msdn.microsoft.com/c/2016/04/15/visual-c-2015-update-2-bug-%E4%BF%AE%E5%A4%8D/
//cin.sync() and fflush(stdin) do not work with Visual Studio 2015
void cPlayer0::SetFromScreen()
{
	char c;
	cout << "�����������λ��:";
	//cin.sync();//���������
	cin.clear();//�����־λ
	while (!(cin.getline(PositionInput, 3)))
	{
		cout << "������������������λ��:";
		//cin.sync();//���������
		cin.clear();//�����־λ
		do {
			c = cin.get();
		} while (c != '\n');
		
	}
	while (!(((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O'))))
	{
		cout << "������������������λ��:";
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "������������������λ��:";
			//cin.sync();//���������
			cin.clear();//�����־λ
			do {
				c = cin.get();
			} while (c != '\n');
		}
	}
}

void cPlayer1::SetFromScreen()
{
	char c;
	cout << "�����1���������λ��:";
	//cin.sync();//���������
	cin.clear();//�����־λ
	while (!(cin.getline(PositionInput, 3)))
	{
		cout << "������������1���������λ��:";
		//cin.sync();//���������
		cin.clear();//�����־λ
		do {
			c = cin.get();
		} while (c != '\n');
	}
	while (!(((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O'))))
	{
		cout << "������������1���������λ��";
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "������������1���������λ��:";
			//cin.sync();//���������
			cin.clear();//�����־λ
			do {
				c = cin.get();
			} while (c != '\n');
		}
	}
}

void cPlayer2::SetFromScreen()
{
	char c;
	cout << "�����2���������λ��:";
	//cin.sync();//���������
	cin.clear();//�����־λ
	while (!(cin.getline(PositionInput, 3)))
	{
		cout << "������������2���������λ��:";
		//cin.sync();//���������
		cin.clear();//�����־λ
		do {
			c = cin.get();
		} while (c != '\n');
	}
	while (!(((PositionInput[0] >= '0'&&PositionInput[0] <= '9') || (PositionInput[0] >= 'a'&&PositionInput[0] <= 'e') || (PositionInput[0] >= 'A'&&PositionInput[0] <= 'E')) && ((PositionInput[1] >= 'a'&&PositionInput[1] <= 'o') || (PositionInput[1] >= 'A'&&PositionInput[1] <= 'O'))))
	{
		cout << "������������2���������λ��";
		while (!(cin.getline(PositionInput, 3)))
		{
			cout << "������������2���������λ��:";
			//cin.sync();//���������
			cin.clear();//�����־λ
			do {
				c = cin.get();
			} while (c != '\n');
		}
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