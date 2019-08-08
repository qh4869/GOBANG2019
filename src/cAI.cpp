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
	if (PlayerColor == BLACK && type == PLAYER || PlayerColor == WHITE && type == AI)//黑棋棋型表
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
	cManager oManager;//只是用一下裁判函数

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
			oBoard.SetAtTable(x, y, ColorNow);//下把棋下里，这会影响之后判断活三活四冲四的递归
			//下面这些需要统计的变量，在禁手判断中全部都用得到
			int FirstSame[8];//相连同色棋子个数，
			int FirstEmpty[8];//两侧空白个数
			int SecondSame[8];//空白之后同色棋子个数,黑
			int SecondDiff[8];//空白之后异色棋子个数,白
			int SecondEmpty[8];//黑棋+空白+黑棋 之后的空白个数
			int ThirdSame[8];//黑棋+空白+黑棋+空白 之后黑棋的个数

			int i;
			//赋初值
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

			//向上搜索
			for (xNow = x - 1; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow--, FirstSame[0]++);
			for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, FirstEmpty[0]++);
			temp_x = xNow;
			for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow % 2 + 1; xNow--, SecondDiff[0]++);
			for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow--, SecondSame[0]++);
			for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, SecondEmpty[0]++);
			for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow--, ThirdSame[0]++);


			//右上搜索
			for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow++, FirstSame[1]++);
			for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, FirstEmpty[1]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow--, yNow++, SecondDiff[1]++);
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow++, SecondSame[1]++);
			for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, SecondEmpty[1]++);
			for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow++, ThirdSame[1]++);


			//向右搜索
			for (yNow = y + 1; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow++, FirstSame[2]++);
			for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, FirstEmpty[2]++);
			temp_y = yNow;
			for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow % 2 + 1; yNow++, SecondDiff[2]++);
			for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow++, SecondSame[2]++);
			for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, SecondEmpty[2]++);
			for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow++, ThirdSame[2]++);


			//向右下搜索
			for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow++, FirstSame[3]++);
			for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, FirstEmpty[3]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow++, yNow++, SecondDiff[3]++);
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow++, SecondSame[3]++);
			for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, SecondEmpty[3]++);
			for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow++, ThirdSame[3]++);


			//向下搜索
			for (xNow = x + 1; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow++, FirstSame[4]++);
			for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, FirstEmpty[4]++);
			temp_x = xNow;
			for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow % 2 + 1; xNow++, SecondDiff[4]++);
			for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow++, SecondSame[4]++);
			for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, SecondEmpty[4]++);
			for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == ColorNow; xNow++, ThirdSame[4]++);


			//向左下搜索
			for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow--, FirstSame[5]++);
			for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, FirstEmpty[5]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow++, yNow--, SecondDiff[5]++);
			for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow--, SecondSame[5]++);
			for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, SecondEmpty[5]++);
			for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow++, yNow--, ThirdSame[5]++);

			//向左搜索
			for (yNow = y - 1; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow--, FirstSame[6]++);
			for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, FirstEmpty[6]++);
			temp_y = yNow;
			for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow % 2 + 1; yNow--, SecondDiff[6]++);
			for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow--, SecondSame[6]++);
			for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, SecondEmpty[6]++);
			for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == ColorNow; yNow--, ThirdSame[6]++);

			//左上搜索
			for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow--, FirstSame[7]++);
			for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, FirstEmpty[7]++);
			temp_x = xNow;
			temp_y = yNow;
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow % 2 + 1; xNow--, yNow--, SecondDiff[7]++);
			for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow--, SecondSame[7]++);
			for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, SecondEmpty[7]++);
			for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == ColorNow; xNow--, yNow--, ThirdSame[7]++);

			//五连
			int fivecount = 0;
			for (i = 0; i < 4; i++)
			{
				if (FirstSame[i] + FirstSame[i + 4] == 4)
					fivecount++;
			}

			//禁手分析
			int sthreecount = 0;//单关键点活三计数
			int dthreecount = 0;//双关键点活三
			int hfourcount = 0;//活四计数 
			int cfourcount = 0;//冲四计数
			int longcount = 0;

			for (i = 0; i < 4; i++)
			{
				if (FirstSame[i] + FirstSame[i + 4] >= 5)//长连
					longcount++;

				else if (FirstSame[i] + FirstSame[i + 4] == 3)//四连,可能会形成冲四或者活四
				{
					//冲四活四判断
					bool isFour1 = false;
					bool isFour2 = false;
					if (FirstEmpty[i] > 0)
					{
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)//满足关键点不禁手的条件
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

				else if (FirstSame[i] + FirstSame[i + 4] == 2)//三连,可能会形成冲四或者活三
				{
					//冲四检查
					if (FirstEmpty[i] == 1 && SecondSame[i] == 1)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i))
							cfourcount++;
					if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4))
							cfourcount++;

					//活三检查
					//    ecaXXXbdf
					//这个是禁手里最不好想清楚的，条件里面应该有重复的地方，不过这样写应该最好理解
					if ((FirstEmpty[i] >= 1 && FirstEmpty[i + 4] >= 1) && //ab是空白
						(FirstEmpty[i] >= 2 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] == 1 && SecondDiff[i] >= 1 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] >= 2 && FirstEmpty[i + 4] == 1 && SecondDiff[i + 4] >= 2) &&//cd不能是黑棋，也不能同时是白色
						(FirstEmpty[i] == 1 || FirstEmpty[i] == 2 && SecondSame[i] == 0 || FirstEmpty[i] >= 3) &&//如果ac都空，则e不可以是黑棋
						(FirstEmpty[i + 4] == 1 || FirstEmpty[i + 4] == 2 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 3))//如果bd空，则f不可以是黑棋
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true && oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)//ab不是禁手
							dthreecount++;
				}

				else if (FirstSame[i] + FirstSame[i + 4] == 1)//二连，可能形成冲四和活三
				{
					//冲四检查
					if (FirstEmpty[i] == 1 && SecondSame[i] == 2)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							cfourcount++;
					if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							cfourcount++;

					//活三检查
					//   bmXXaXnc
					//注意 X_XX_X 不是活三！
					//然而 X_XXX_X 四四禁手！
					if ((FirstEmpty[i] == 1 && SecondSame[i] == 1) && //a点是空白
						(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//n点必须是空白，c点不能是黑棋
						(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//m点必须是空白，b点不能是黑棋
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							sthreecount++;
					if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1) && //a点是空白
						(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//n点必须是空白，c点不能是黑棋
						(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//m点必须是空白，b点不能是黑棋
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							sthreecount++;
				}

				else if (FirstSame[i] + FirstSame[i + 4] == 2 == 0)//单独一子，可能会形成冲四和活三
				{
					//冲四检查
					if (FirstEmpty[i] == 1 && SecondSame[i] == 3)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							cfourcount++;
					if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 3)
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							cfourcount++;

					//活三检查
					//   bmXXaXnc
					if ((FirstEmpty[i] == 1 && SecondSame[i] == 2) &&//a点是空白
						(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//m必须是空白，b点不是黑子
						(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//n必须是空白，c不是黑棋
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
							sthreecount++;
					if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2) &&//a点是空白
						(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//m必须是空白，b点不是黑子
						(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//n必须是空白，c不是黑棋
						if (oManager.KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
							sthreecount++;
				}
			}
			int adjsamemax = 0;//一圈相邻同颜色最大值
			for (i = 0; i < 4; i++)
			{
				if (FirstSame[i] + FirstSame[i + 4] > adjsamemax)
					adjsamemax = FirstSame[i] + FirstSame[i + 4];
			}
			if (ColorNow == BLACK)//有禁手
			{
				if (adjsamemax == 0)
					aChart[x][y] = 1;
				if (adjsamemax == 1)
					aChart[x][y] = 10;
				if (x == 7 && y == 7)//这个位置如果没人下，在没有更优的选择下，电脑就会下在这里
					aChart[x][y] = 15;
				if (adjsamemax == 2)
					aChart[x][y] = 100;
				if (sthreecount > 0)
					aChart[x][y] = 500;
				if (cfourcount > 0 || dthreecount > 0)
					aChart[x][y] = 1000;
				if (hfourcount > 0 || hfourcount + cfourcount == 1 && sthreecount + dthreecount == 1)
					aChart[x][y] = 10000;
				if (longcount > 0 || hfourcount + cfourcount > 1 || sthreecount + dthreecount > 1)//禁手
					aChart[x][y] = 0;
				if (fivecount > 0)//五连为大
					aChart[x][y] = 100000;
			}
			else if (ColorNow == WHITE)//没有禁手
			{
				if (adjsamemax == 0)
					aChart[x][y] = 1;
				if (adjsamemax == 1)
					aChart[x][y] = 10;
				if (x == 7 && y == 7)//这个位置如果没人下，在没有更优的选择下，电脑就会下在这里
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
			oBoard.SetAtTable(x, y, EMPTY);//把之前假设放里的棋拿出来
		}
	}
}

int cAI::SearchForBestPosition()
{
	int i, j;
	int maxnum, x, y;//最大值和坐标
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
				if (RandomNumber < 0.15)//下棋灵活一点
				{
					x = i;
					y = j;
				}
			}
		}
	if (maxnum == 0)//没有地方可以下了
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
