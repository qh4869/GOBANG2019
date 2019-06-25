#include "cRole.h"

cAI::cAI()
{
	int i, j;
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
		{
			PlayerChart[i][j] = 0;
			AIChart[i][j] = 0;
		}
}


void cAI::RefreshChart(cBoard oBoard, int PlayerColor, int type)
{
	int ColorNow;
	if (PlayerColor == BLACK && type == PLAYER || PlayerColor == WHITE && type == AI)//�������ͱ�
		ColorNow = BLACK;
	else
		ColorNow = WHITE;
	int(*aChart)[15] = AIChart;
	if (type == AI)
	{
		aChart = AIChart;
		ColorNow = PlayerColor % 2 + 1;
	}
	else if (type == PLAYER)
	{
		aChart = PlayerChart;
		ColorNow = PlayerColor;
	}
	cManager oManager;//ֻ����һ�²��к���

	int x, y;

	for (x = 0; x < 15; x++)
	{
		for (y = 0; y < 15; y++)
		{
			if (oBoard.WhetherEmpty(x, y) == NEMPTY)
			{
				aChart[x][y] = 0;
				continue;
			}
			oBoard.SetAtTable(x, y, ColorNow);//�°���������Ӱ��֮���жϻ������ĳ��ĵĵݹ�
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
			for (xNow = x - 1; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow--, FirstSame[0]++);
			for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, FirstEmpty[0]++);
			temp_x = xNow;
			for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow % 2 + 1; xNow--, SecondDiff[0]++);
			for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow--, SecondSame[0]++);
			for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, SecondEmpty[0]++);
			for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow--, ThirdSame[0]++);


			//��������
			for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow++, FirstSame[1]++);
			for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, FirstEmpty[1]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow--, yNow++, SecondDiff[1]++);
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow++, SecondSame[1]++);
			for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, SecondEmpty[1]++);
			for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow++, ThirdSame[1]++);


			//��������
			for (yNow = y + 1; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow++, FirstSame[2]++);
			for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, FirstEmpty[2]++);
			temp_y = yNow;
			for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow % 2 + 1; yNow++, SecondDiff[2]++);
			for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow++, SecondSame[2]++);
			for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, SecondEmpty[2]++);
			for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow++, ThirdSame[2]++);


			//����������
			for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow++, FirstSame[3]++);
			for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, FirstEmpty[3]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow++, yNow++, SecondDiff[3]++);
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow++, SecondSame[3]++);
			for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, SecondEmpty[3]++);
			for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow++, ThirdSame[3]++);


			//��������
			for (xNow = x + 1; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow++, FirstSame[4]++);
			for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, FirstEmpty[4]++);
			temp_x = xNow;
			for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow % 2 + 1; xNow++, SecondDiff[4]++);
			for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow++, SecondSame[4]++);
			for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, SecondEmpty[4]++);
			for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow++, ThirdSame[4]++);


			//����������
			for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow--, FirstSame[5]++);
			for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, FirstEmpty[5]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow++, yNow--, SecondDiff[5]++);
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow--, SecondSame[5]++);
			for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, SecondEmpty[5]++);
			for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow--, ThirdSame[5]++);

			//��������
			for (yNow = y - 1; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow--, FirstSame[6]++);
			for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, FirstEmpty[6]++);
			temp_y = yNow;
			for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow % 2 + 1; yNow--, SecondDiff[6]++);
			for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow--, SecondSame[6]++);
			for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, SecondEmpty[6]++);
			for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow--, ThirdSame[6]++);

			//��������
			for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow--, FirstSame[7]++);
			for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, FirstEmpty[7]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow--, yNow--, SecondDiff[7]++);
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow--, SecondSame[7]++);
			for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, SecondEmpty[7]++);
			for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow--, ThirdSame[7]++);

			//����
			int fivecount = 0;
			for (i = 0; i < 4; i++)
			{
				if (FirstSame[i] + FirstSame[i + 4] == 4)
					fivecount++;
			}

			//���ַ���
			int sthreecount = 0;//���ؼ����������
			int dthreecount = 0;//˫�ؼ������
			int hfourcount = 0;//���ļ��� 
			int cfourcount = 0;//���ļ���
			int longcount = 0;

			for (i = 0; i < 4; i++)
			{
				if (FirstSame[i] + FirstSame[i + 4] >= 5)//����
					longcount++;

				else if (FirstSame[i] + FirstSame[i + 4] == 3)//����,���ܻ��γɳ��Ļ��߻���
				{
					//���Ļ����ж�
					bool isFour1 = false;
					bool isFour2 = false;
					if (FirstEmpty[i] > 0)
					{
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)//����ؼ��㲻���ֵ�����
							isFour1 = true;
					}

					if (FirstEmpty[i + 4] > 0)
					{
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							isFour2 = true;
					}
					if (isFour1 == true && isFour2 == true)
						hfourcount++;
					else if (isFour1 == true && isFour2 == false || isFour1 == false && isFour2 == true)
						cfourcount++;
				}

				else if (FirstSame[i] + FirstSame[i + 4] == 2)//����,���ܻ��γɳ��Ļ��߻���
				{
					//���ļ��
					if (FirstEmpty[i] == 1 && SecondSame[i] == 1)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i))
							cfourcount++;
					if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4))
							cfourcount++;

					//�������
					//    ecaXXXbdf
					//����ǽ��������������ģ���������Ӧ�����ظ��ĵط�����������дӦ��������
					if ((FirstEmpty[i] >= 1 && FirstEmpty[i + 4] >= 1) && //ab�ǿհ�
						(FirstEmpty[i] >= 2 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] == 1 && SecondDiff[i] >= 1 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] >= 2 && FirstEmpty[i + 4] == 1 && SecondDiff[i + 4] >= 2) &&//cd�����Ǻ��壬Ҳ����ͬʱ�ǰ�ɫ
						(FirstEmpty[i] == 1 || FirstEmpty[i] == 2 && SecondSame[i] == 0 || FirstEmpty[i] >= 3) &&//���ac���գ���e�������Ǻ���
						(FirstEmpty[i + 4] == 1 || FirstEmpty[i + 4] == 2 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 3))//���bd�գ���f�������Ǻ���
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true && oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)//ab���ǽ���
							dthreecount++;
				}

				else if (FirstSame[i] + FirstSame[i + 4] == 1)//�����������γɳ��ĺͻ���
				{
					//���ļ��
					if (FirstEmpty[i] == 1 && SecondSame[i] == 2)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							cfourcount++;
					if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							cfourcount++;

					//�������
					//   bmXXaXnc
					//ע�� X_XX_X ���ǻ�����
					//Ȼ�� X_XXX_X ���Ľ��֣�
					if ((FirstEmpty[i] == 1 && SecondSame[i] == 1) && //a���ǿհ�
						(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//n������ǿհף�c�㲻���Ǻ���
						(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//m������ǿհף�b�㲻���Ǻ���
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							sthreecount++;
					if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1) && //a���ǿհ�
						(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//n������ǿհף�c�㲻���Ǻ���
						(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//m������ǿհף�b�㲻���Ǻ���
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							sthreecount++;
				}

				else if (FirstSame[i] + FirstSame[i + 4] == 2 == 0)//����һ�ӣ����ܻ��γɳ��ĺͻ���
				{
					//���ļ��
					if (FirstEmpty[i] == 1 && SecondSame[i] == 3)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							cfourcount++;
					if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 3)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							cfourcount++;

					//�������
					//   bmXXaXnc
					if ((FirstEmpty[i] == 1 && SecondSame[i] == 2) &&//a���ǿհ�
						(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//m�����ǿհף�b�㲻�Ǻ���
						(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//n�����ǿհף�c���Ǻ���
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							sthreecount++;
					if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2) &&//a���ǿհ�
						(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//m�����ǿհף�b�㲻�Ǻ���
						(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//n�����ǿհף�c���Ǻ���
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							sthreecount++;
				}
			}
			int adjsamemax = 0;//һȦ����ͬ��ɫ���ֵ
			for (i = 0; i < 4; i++)
			{
				if (FirstSame[i] + FirstSame[i + 4] > adjsamemax)
					adjsamemax = FirstSame[i] + FirstSame[i + 4];
			}
			if (ColorNow == BLACK)//�н���
			{
				if (adjsamemax == 0)
					aChart[x][y] = 1;
				if (adjsamemax == 1)
					aChart[x][y] = 10;
				if (x == 7 && y == 7)//���λ�����û���£���û�и��ŵ�ѡ���£����Ծͻ���������
					aChart[x][y] = 15;
				if (adjsamemax == 2)
					aChart[x][y] = 100;
				if (sthreecount > 0)
					aChart[x][y] = 500;
				if (cfourcount > 0 || dthreecount > 0)
					aChart[x][y] = 1000;
				if (hfourcount > 0 || hfourcount + cfourcount == 1 && sthreecount + dthreecount == 1)
					aChart[x][y] = 10000;
				if (longcount > 0 || hfourcount + cfourcount > 1 || sthreecount + dthreecount > 1)//����
					aChart[x][y] = 0;
				if (fivecount > 0)//����Ϊ��
					aChart[x][y] = 100000;
			}
			else if (ColorNow == WHITE)//û�н���
			{
				if (adjsamemax == 0)
					aChart[x][y] = 1;
				if (adjsamemax == 1)
					aChart[x][y] = 10;
				if (x == 7 && y == 7)//���λ�����û���£���û�и��ŵ�ѡ���£����Ծͻ���������
					aChart[x][y] = 15;
				if (adjsamemax == 2)
					aChart[x][y] = 100;
				if (sthreecount > 0)
					aChart[x][y] = 500;
				if (cfourcount > 0 || dthreecount > 0)
					aChart[x][y] = 1000;
				if (hfourcount > 0 || hfourcount + cfourcount + dthreecount + sthreecount > 1)
					aChart[x][y] = 10000;
				if (fivecount > 0 || longcount > 0)
					aChart[x][y] = 100000;
			}
			oBoard.SetAtTable(x, y, EMPTY);//��֮ǰ�����������ó���
		}
	}
}

int cAI::SearchForBestPosition()
{
	int i, j;
	int maxnum, x, y;//���ֵ������
	double RandomNumber;
	maxnum = 0;
	srand(unsigned(time(0)));
	for (i = 0; i<15; i++)
		for (j = 0; j<15; j++)
		{
			AddChart[i][j] = AIChart[i][j] + PlayerChart[i][j];
			if (AddChart[i][j] > maxnum)
			{
				maxnum = AddChart[i][j];
				x = i;
				y = j;
			}
			else if (AddChart[i][j] == maxnum)
			{
				RandomNumber = (double)rand() / (RAND_MAX);
				if (RandomNumber < 0.15)//�������һ��
				{
					x = i;
					y = j;
				}
			}
		}
	if (maxnum == 0)//û�еط���������
		return -1;
	row = x;
	column = y;
	return 0;
}

void cAI::SetBothChartsZero(int x, int y)
{
	AIChart[x][y] = 0;
	PlayerChart[x][y] = 0;
}
