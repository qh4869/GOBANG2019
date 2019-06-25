#include "cManager.h"

using namespace std;

void cManager::SetAtGameMode(int mode)
{
	GameMode = mode;
}

int cManager::GetATGameMode()
{
	return GameMode;
}

void cManager::WhoFirst(int who)
{
	WhoNext = who;
}

void cManager::fnExchange()
{
	WhoNext = WhoNext % 2 + 1;
}

int cManager::GetAtWhoNext()
{
	return WhoNext;
}
void cManager::SetAtPlayerColor(int color)
{
	PlayerColor = color;
}

int cManager::GetAtPlayerColor()
{
	return PlayerColor;
}


void cManager::ModeChoice()
{
	system("cls");//����������
	int ModeInput;
	char c;//cin.sync() and fflush(stdin) do not work with Visual Studio 2015
	//������Ϸģʽ
	cout << "��Ϸģʽѡ��1��ҶԵ��ԣ�2��Ҷ����" << endl;
	cout << "����������ѡ��:";
	while (!(cin >> ModeInput))
	{
		cout << "�����������������:";
		do {
			c = getchar();
		} while (c != '\n');
		cin.clear();//�����־λ
	}
	while (ModeInput != PLAYERVSAI && ModeInput != PLAYERVSPLAYER)
	{
		cout << "�����������������:";
		while (!(cin >> ModeInput))
		{
			cout << "�����������������:";
			do {
				c = getchar();
			} while (c != '\n');
			cin.clear();//�����־λ
		}
	}
	GameMode = ModeInput;

	//������ҵ�������ɫ
	if (GameMode == PLAYERVSAI)
		cout << endl << "�������ѡ��1��ɫ��2��ɫ" << endl;
	else
		cout << endl << "���1����ѡ��1��ɫ��2��ɫ" << endl;
	cout << "����������ѡ��:";
	while (!(cin >> ModeInput))
	{
		cout << "�����������������:";
		do {
			c = getchar();
		} while (c != '\n');
		cin.clear();//�����־λ
	}
	while (ModeInput != BLACK && ModeInput != WHITE)
	{
		cout << "�����������������:";
		while (!(cin >> ModeInput))
		{
			cout << "�����������������:";
			do {
				c = getchar();
			} while (c != '\n');
			cin.clear();//�����־λ
		}
	}
	PlayerColor = ModeInput;
	if (PlayerColor == BLACK)
		WhoNext = 1;
	else
		WhoNext = 2;

	char temp[4];
	cin.getline(temp, 3);//֮ǰ�������ڻ�������������һ���س�����������ͣ������
}

//���к������ǽ���
//����ֵ��1 BLACKʤ������ 2 WHITEʤ������ 3 FORBIDDEN��ɫ���ְ�ɫʤ 0����ʤ
//�йؽ��ֿ��ļ��е�ͼƬ
int cManager::referee(cBoard oBoard, const int x, const int y)
{
	int result = 0;//���н��
	//--------------------------------------�����жϣ�û�н��֣�-------------------------------
	if (oBoard.GetAtTable(x, y) == WHITE)
	{
		int FirstSame[8];//����ͬɫ���Ӹ�����
		int FirstEmpty[8];//����հ׸���
		int i;
		//����ֵ
		for (i = 0; i < 8; i++)
		{
			FirstSame[i] = 0;
			FirstEmpty[i] = 0;
		}
		int xNow, yNow;
		//��������
		for (xNow = x - 1; xNow >= 0 && oBoard.GetAtTable(xNow, y) == WHITE; xNow--, FirstSame[0]++);
		//��������
		for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow++, FirstSame[1]++);
		//��������
		for (yNow = y + 1; yNow <= 14 && oBoard.GetAtTable(x, yNow) == WHITE; yNow++, FirstSame[2]++);
		//����������
		for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow++, FirstSame[3]++);
		//��������
		for (xNow = x + 1; xNow <= 14 && oBoard.GetAtTable(xNow, y) == WHITE; xNow++, FirstSame[4]++);
		//����������
		for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow--, FirstSame[5]++);
		//��������
		for (yNow = y - 1; yNow >= 0 && oBoard.GetAtTable(x, yNow) == WHITE; yNow--, FirstSame[6]++);
		//��������
		for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow--, FirstSame[7]++);

		for (i = 0; i < 4; i++)
		{
			if (FirstSame[i] + FirstSame[i + 4] >= 4)//�����������
				result = WHITE;
		}
	}
	//---------------------------�����жϣ��н��֣��ο����ϵݹ��㷨��------------------------------------------
	else
	{
		//������Щ��Ҫͳ�Ƶı������ڽ����ж���ȫ�����õõ�
		int FirstSame[8];//����ͬɫ���Ӹ�����
		int FirstEmpty[8];//����հ׸���
		int SecondSame[8];//�հ�֮��ͬɫ���Ӹ���,��
		int SecondDiff[8];//�հ�֮����ɫ���Ӹ���,��
		int SecondEmpty[8];//����+�հ�+���� ֮��Ŀհ׸���
		int ThirdSame[8];//����+�հ�+����+�հ� ֮�����ĸ���

		int i;
		//����ֵ
		for (i = 0; i < 8; i++)
		{
			FirstSame[i] = 0;
			FirstEmpty[i] = 0;
			SecondSame[i] = 0;
			SecondDiff[i] = 0;
			SecondEmpty[i] = 0;
			ThirdSame[i] = 0;
		}

		int xNow, yNow;
		int temp_x, temp_y;
		//��������
		for (xNow = x - 1; xNow >= 0 && oBoard.GetAtTable(xNow, y) == BLACK; xNow--, FirstSame[0]++);
		for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, FirstEmpty[0]++);
		temp_x = xNow;
		for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == WHITE; xNow--, SecondDiff[0]++);
		for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == BLACK; xNow--, SecondSame[0]++);
		for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, SecondEmpty[0]++);
		for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == BLACK; xNow--, ThirdSame[0]++);


		//��������
		for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, FirstSame[1]++);
		for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, FirstEmpty[1]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow++, SecondDiff[1]++);
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, SecondSame[1]++);
		for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, SecondEmpty[1]++);
		for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, ThirdSame[1]++);


		//��������
		for (yNow = y + 1; yNow <= 14 && oBoard.GetAtTable(x, yNow) == BLACK; yNow++, FirstSame[2]++);
		for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, FirstEmpty[2]++);
		temp_y = yNow;
		for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == WHITE; yNow++, SecondDiff[2]++);
		for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == BLACK; yNow++, SecondSame[2]++);
		for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, SecondEmpty[2]++);
		for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == BLACK; yNow++, ThirdSame[2]++);


		//����������
		for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, FirstSame[3]++);
		for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, FirstEmpty[3]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow++, SecondDiff[3]++);
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, SecondSame[3]++);
		for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, SecondEmpty[3]++);
		for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, ThirdSame[3]++);


		//��������
		for (xNow = x + 1; xNow <= 14 && oBoard.GetAtTable(xNow, y) == BLACK; xNow++, FirstSame[4]++);
		for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, FirstEmpty[4]++);
		temp_x = xNow;
		for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == WHITE; xNow++, SecondDiff[4]++);
		for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == BLACK; xNow++, SecondSame[4]++);
		for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, SecondEmpty[4]++);
		for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == BLACK; xNow++, ThirdSame[4]++);


		//����������
		for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, FirstSame[5]++);
		for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, FirstEmpty[5]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow--, SecondDiff[5]++);
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, SecondSame[5]++);
		for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, SecondEmpty[5]++);
		for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, ThirdSame[5]++);

		//��������
		for (yNow = y - 1; yNow >= 0 && oBoard.GetAtTable(x, yNow) == BLACK; yNow--, FirstSame[6]++);
		for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, FirstEmpty[6]++);
		temp_y = yNow;
		for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == WHITE; yNow--, SecondDiff[6]++);
		for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == BLACK; yNow--, SecondSame[6]++);
		for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, SecondEmpty[6]++);
		for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == BLACK; yNow--, ThirdSame[6]++);

		//��������
		for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, FirstSame[7]++);
		for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, FirstEmpty[7]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow--, SecondDiff[7]++);
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, SecondSame[7]++);
		for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, SecondEmpty[7]++);
		for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, ThirdSame[7]++);

		//����
		for (i = 0; i < 4; i++)
		{
			if (FirstSame[i] + FirstSame[i + 4] == 4)
				result = BLACK;
		}

		//���ַ���
		int threecount = 0;//��������
		int fourcount = 0;//���ġ����ļ��� 

		for (i = 0; i < 4; i++)
		{
			if (FirstSame[i] + FirstSame[i + 4] >= 5)//����
				result = FORBIDDEN;

			else if (FirstSame[i] + FirstSame[i + 4] == 3)//����,���ܻ��γɳ��Ļ��߻���
			{
				//���Ļ��߻����ж�
				bool isFour = false;
				if (FirstEmpty[i] > 0)
				{
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)//����ؼ��㲻���ֵ�����
						isFour = true;
				}

				if (FirstEmpty[i + 4] > 0)
				{
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						isFour = true;
				}
				if (isFour)
					fourcount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 2)//����,���ܻ��γɳ��Ļ��߻���
			{
				//���ļ��
				if (FirstEmpty[i] == 1 && SecondSame[i] == 1)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i))
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4))
						fourcount++;

				//�������
				//    ecaXXXbdf
				//����ǽ��������������ģ���������Ӧ�����ظ��ĵط�����������дӦ��������
				if ((FirstEmpty[i] >= 1 && FirstEmpty[i + 4] >= 1) && //ab�ǿհ�
					(FirstEmpty[i] >= 2 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] == 1 && SecondDiff[i] >= 1 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] >= 2 && FirstEmpty[i + 4] == 1 && SecondDiff[i + 4] >= 2) &&//cd�����Ǻ��壬Ҳ����ͬʱ�ǰ�ɫ
					(FirstEmpty[i] == 1 || FirstEmpty[i] == 2 && SecondSame[i] == 0 || FirstEmpty[i] >= 3) &&//���ac���գ���e�������Ǻ���
					(FirstEmpty[i + 4] == 1 || FirstEmpty[i + 4] == 2 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 3))//���bd�գ���f�������Ǻ���
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true && KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)//ab���ǽ���
						threecount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 1)//�����������γɳ��ĺͻ���
			{
				//���ļ��
				if (FirstEmpty[i] == 1 && SecondSame[i] == 2)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						fourcount++;

				//�������
				//   bmXXaXnc
				//ע�� X_XX_X ���ǻ�����
				//Ȼ�� X_XXX_X ���Ľ��֣�
				if ((FirstEmpty[i] == 1 && SecondSame[i] == 1) && //a���ǿհ�
					(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//n������ǿհף�c�㲻���Ǻ���
					(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//m������ǿհף�b�㲻���Ǻ���
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						threecount++;
				if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1) && //a���ǿհ�
					(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//n������ǿհף�c�㲻���Ǻ���
					(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//m������ǿհף�b�㲻���Ǻ���
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						threecount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 2 == 0)//����һ�ӣ����ܻ��γɳ��ĺͻ���
			{
				//���ļ��
				if (FirstEmpty[i] == 1 && SecondSame[i] == 3)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 3)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						fourcount++;

				//�������
				//   bmXXaXnc
				if ((FirstEmpty[i] == 1 && SecondSame[i] == 2) &&//a���ǿհ�
					(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//m�����ǿհף�b�㲻�Ǻ���
					(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//n�����ǿհף�c���Ǻ���
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						threecount++;
				if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2) &&//a���ǿհ�
					(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//m�����ǿհף�b�㲻�Ǻ���
					(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//n�����ǿհף�c���Ǻ���
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						threecount++;
			}
		}
		//����ͳ�ƵĽ���жϽ���,������ǰ��
		if (fourcount > 1)
			result = FORBIDDEN;
		else if (threecount > 1)
			result = FORBIDDEN;
	}
	
	return result;
}

//�ؼ����⣬�жϹ��ɻ��������ģ����ĵı�Ҫ����֮һ
//�����ؼ����Ƿ��ǽ��ֵĵ㣬������ֵĻ����ǾͲ��ܹ��ɻ��������ģ�����
//��ʵ���ǵݹ���ò��к�����������һЩ����֮ǰ��׼������
//����ٻ���
bool cManager::KeyPointCheck(cBoard oBoard, const int x, const int y, int FirstSame, int direction)
{
	int KeyX, KeyY;
	//�ȼ���ؼ��������
	switch (direction)
	{
	case 0:
		KeyX = x - FirstSame - 1;
		KeyY = y;
		break;
	case 1:
		KeyX = x - FirstSame - 1;
		KeyY = y + FirstSame + 1;
		break;
	case 2:
		KeyX = x;
		KeyY = y + FirstSame + 1;
		break;
	case 3:
		KeyX = x + FirstSame + 1;
		KeyY = y + FirstSame + 1;
		break;
	case 4:
		KeyX = x + FirstSame + 1;
		KeyY = y;
		break;
	case 5:
		KeyX = x + FirstSame + 1;
		KeyY = y - FirstSame - 1;
		break;
	case 6:
		KeyX = x;
		KeyY = y - FirstSame - 1;
		break;
	case 7:
		KeyX = x - FirstSame - 1;
		KeyY = y - FirstSame - 1;
		break;
	}

	//�ؼ��㴦�����岢�ж��Ƿ����,ע�����βα仯����Ӱ����������
	oBoard.SetAtTable(KeyX, KeyY, BLACK);
	if (referee(oBoard, KeyX, KeyY) == FORBIDDEN)//�������
		return false;//������
	else
		return true;//���ɻ��������ġ�����
}

//����1 ���������һ��
//����0 �����˳�
int cManager::Gaming(cBoard& oBoard)
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
				result = referee(oBoard, oPlayer1.GetAtRow(), oPlayer1.GetAtColumn());
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
				result = referee(oBoard, oPlayer2.GetAtRow(), oPlayer2.GetAtColumn());
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
				result = referee(oBoard, oPlayer0.GetAtRow(), oPlayer0.GetAtColumn());
				if (result)
					break;
			}
			else if (WhoNext == AI)
			{
				oAI.RefreshChart(oBoard, PlayerColor, AI);
				oAI.RefreshChart(oBoard, PlayerColor, PLAYER);
				if (oAI.SearchForBestPosition() == -1)//û�еط����������ˣ�����
				{
					result = EQUAL;
					break;
				}
				oBoard.SetAtTable(oAI.GetAtRow(), oAI.GetAtColumn(), PlayerColor % 2 + 1);
				oBoard.RefreshScreen(oAI.GetAtRow(), oAI.GetAtColumn());
				fnExchange();
				result = referee(oBoard, oAI.GetAtRow(), oAI.GetAtColumn());
				if (result)
					break;
			}
		}
	}
	return ShowResult();
}

int cManager::ShowResult()
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