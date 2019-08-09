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
	//命令行清屏
	#ifdef _WIN32
    system("cls");
    #elif defined __APPLE__
    system("clear");
    #endif

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

//裁判函数考虑禁手
//返回值：1 BLACK胜不禁手 2 WHITE胜不禁手 3 FORBIDDEN黑色禁手白色胜 0无人胜
//有关禁手看文件夹的图片
int cBoard::referee(const int x, const int y)
{
	int result = 0;//裁判结果
	//--------------------------------------白棋判断（没有禁手）-------------------------------
	if (GetAtTable(x, y) == WHITE)
	{
		int FirstSame[8];//相连同色棋子个数，
		int FirstEmpty[8];//两侧空白个数
		int i;
		//赋初值
		for (i = 0; i < 8; i++)
		{
			FirstSame[i] = 0;
			FirstEmpty[i] = 0;
		}
		int xNow, yNow;
		//向上搜索
		for (xNow = x - 1; xNow >= 0 && GetAtTable(xNow, y) == WHITE; xNow--, FirstSame[0]++);
		//右上搜索
		for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == WHITE; xNow--, yNow++, FirstSame[1]++);
		//向右搜索
		for (yNow = y + 1; yNow <= 14 && GetAtTable(x, yNow) == WHITE; yNow++, FirstSame[2]++);
		//向右下搜索
		for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == WHITE; xNow++, yNow++, FirstSame[3]++);
		//向下搜索
		for (xNow = x + 1; xNow <= 14 && GetAtTable(xNow, y) == WHITE; xNow++, FirstSame[4]++);
		//向左下搜索
		for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == WHITE; xNow++, yNow--, FirstSame[5]++);
		//向左搜索
		for (yNow = y - 1; yNow >= 0 && GetAtTable(x, yNow) == WHITE; yNow--, FirstSame[6]++);
		//左上搜索
		for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == WHITE; xNow--, yNow--, FirstSame[7]++);

		for (i = 0; i < 4; i++)
		{
			if (FirstSame[i] + FirstSame[i + 4] >= 4)//五个以上相连
				result = WHITE;
		}
	}
	//---------------------------黑棋判断（有禁手，参考网上递归算法）------------------------------------------
	else
	{
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
		for (xNow = x - 1; xNow >= 0 && GetAtTable(xNow, y) == BLACK; xNow--, FirstSame[0]++);
		for (; xNow >= 0 && GetAtTable(xNow, y) == EMPTY; xNow--, FirstEmpty[0]++);
		temp_x = xNow;
		for (xNow = temp_x; xNow >= 0 && GetAtTable(xNow, y) == WHITE; xNow--, SecondDiff[0]++);
		for (xNow = temp_x; xNow >= 0 && GetAtTable(xNow, y) == BLACK; xNow--, SecondSame[0]++);
		for (; xNow >= 0 && GetAtTable(xNow, y) == EMPTY; xNow--, SecondEmpty[0]++);
		for (; xNow >= 0 && GetAtTable(xNow, y) == BLACK; xNow--, ThirdSame[0]++);


		//右上搜索
		for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, FirstSame[1]++);
		for (; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, FirstEmpty[1]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == WHITE; xNow--, yNow++, SecondDiff[1]++);
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, SecondSame[1]++);
		for (; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, SecondEmpty[1]++);
		for (; xNow >= 0 && yNow <= 14 && GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, ThirdSame[1]++);


		//向右搜索
		for (yNow = y + 1; yNow <= 14 && GetAtTable(x, yNow) == BLACK; yNow++, FirstSame[2]++);
		for (; yNow <= 14 && GetAtTable(x, yNow) == EMPTY; yNow++, FirstEmpty[2]++);
		temp_y = yNow;
		for (yNow = temp_y; yNow <= 14 && GetAtTable(x, yNow) == WHITE; yNow++, SecondDiff[2]++);
		for (yNow = temp_y; yNow <= 14 && GetAtTable(x, yNow) == BLACK; yNow++, SecondSame[2]++);
		for (; yNow <= 14 && GetAtTable(x, yNow) == EMPTY; yNow++, SecondEmpty[2]++);
		for (; yNow <= 14 && GetAtTable(x, yNow) == BLACK; yNow++, ThirdSame[2]++);


		//向右下搜索
		for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, FirstSame[3]++);
		for (; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, FirstEmpty[3]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == WHITE; xNow++, yNow++, SecondDiff[3]++);
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, SecondSame[3]++);
		for (; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, SecondEmpty[3]++);
		for (; xNow <= 14 && yNow <= 14 && GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, ThirdSame[3]++);


		//向下搜索
		for (xNow = x + 1; xNow <= 14 && GetAtTable(xNow, y) == BLACK; xNow++, FirstSame[4]++);
		for (; xNow <= 14 && GetAtTable(xNow, y) == EMPTY; xNow++, FirstEmpty[4]++);
		temp_x = xNow;
		for (xNow = temp_x; xNow <= 14 && GetAtTable(xNow, y) == WHITE; xNow++, SecondDiff[4]++);
		for (xNow = temp_x; xNow <= 14 && GetAtTable(xNow, y) == BLACK; xNow++, SecondSame[4]++);
		for (; xNow <= 14 && GetAtTable(xNow, y) == EMPTY; xNow++, SecondEmpty[4]++);
		for (; xNow <= 14 && GetAtTable(xNow, y) == BLACK; xNow++, ThirdSame[4]++);


		//向左下搜索
		for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, FirstSame[5]++);
		for (; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, FirstEmpty[5]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == WHITE; xNow++, yNow--, SecondDiff[5]++);
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, SecondSame[5]++);
		for (; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, SecondEmpty[5]++);
		for (; xNow <= 14 && yNow >= 0 && GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, ThirdSame[5]++);

		//向左搜索
		for (yNow = y - 1; yNow >= 0 && GetAtTable(x, yNow) == BLACK; yNow--, FirstSame[6]++);
		for (; yNow >= 0 && GetAtTable(x, yNow) == EMPTY; yNow--, FirstEmpty[6]++);
		temp_y = yNow;
		for (yNow = temp_y; yNow >= 0 && GetAtTable(x, yNow) == WHITE; yNow--, SecondDiff[6]++);
		for (yNow = temp_y; yNow >= 0 && GetAtTable(x, yNow) == BLACK; yNow--, SecondSame[6]++);
		for (; yNow >= 0 && GetAtTable(x, yNow) == EMPTY; yNow--, SecondEmpty[6]++);
		for (; yNow >= 0 && GetAtTable(x, yNow) == BLACK; yNow--, ThirdSame[6]++);

		//左上搜索
		for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, FirstSame[7]++);
		for (; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, FirstEmpty[7]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == WHITE; xNow--, yNow--, SecondDiff[7]++);
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, SecondSame[7]++);
		for (; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, SecondEmpty[7]++);
		for (; xNow >= 0 && yNow >= 0 && GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, ThirdSame[7]++);

		//五连
		for (i = 0; i < 4; i++)
		{
			if (FirstSame[i] + FirstSame[i + 4] == 4)
				result = BLACK;
		}

		//禁手分析
		int threecount = 0;//活三计数
		int fourcount = 0;//冲四、活四计数

		for (i = 0; i < 4; i++)
		{
			if (FirstSame[i] + FirstSame[i + 4] >= 5)//长连
				result = FORBIDDEN;

			else if (FirstSame[i] + FirstSame[i + 4] == 3)//四连,可能会形成冲四或者活四
			{
				//冲四或者活四判断
				bool isFour = false;
				if (FirstEmpty[i] > 0)
				{
					if (KeyPointCheck(x, y, FirstSame[i], i) == true)//满足关键点不禁手的条件
						isFour = true;
				}

				if (FirstEmpty[i + 4] > 0)
				{
					if (KeyPointCheck(x, y, FirstSame[i], i) == true)
						isFour = true;
				}
				if (isFour)
					fourcount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 2)//三连,可能会形成冲四或者活三
			{
				//冲四检查
				if (FirstEmpty[i] == 1 && SecondSame[i] == 1)
					if (KeyPointCheck(x, y, FirstSame[i], i))
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1)
					if (KeyPointCheck(x, y, FirstSame[i + 4], i + 4))
						fourcount++;

				//活三检查
				//    ecaXXXbdf
				//这个是禁手里最不好想清楚的，条件里面应该有重复的地方，不过这样写应该最好理解
				if ((FirstEmpty[i] >= 1 && FirstEmpty[i + 4] >= 1) && //ab是空白
					(FirstEmpty[i] >= 2 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] == 1 && SecondDiff[i] >= 1 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] >= 2 && FirstEmpty[i + 4] == 1 && SecondDiff[i + 4] >= 2) &&//cd不能是黑棋，也不能同时是白色
					(FirstEmpty[i] == 1 || FirstEmpty[i] == 2 && SecondSame[i] == 0 || FirstEmpty[i] >= 3) &&//如果ac都空，则e不可以是黑棋
					(FirstEmpty[i + 4] == 1 || FirstEmpty[i + 4] == 2 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 3))//如果bd空，则f不可以是黑棋
					if (KeyPointCheck(x, y, FirstSame[i], i) == true && KeyPointCheck(x, y, FirstSame[i + 4], i + 4) == true)//ab不是禁手
						threecount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 1)//二连，可能形成冲四和活三
			{
				//冲四检查
				if (FirstEmpty[i] == 1 && SecondSame[i] == 2)
					if (KeyPointCheck(x, y, FirstSame[i], i) == true)
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2)
					if (KeyPointCheck(x, y, FirstSame[i + 4], i + 4) == true)
						fourcount++;

				//活三检查
				//   bmXXaXnc
				//注意 X_XX_X 不是活三！
				//然而 X_XXX_X 四四禁手！
				if ((FirstEmpty[i] == 1 && SecondSame[i] == 1) && //a点是空白
					(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//n点必须是空白，c点不能是黑棋
					(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//m点必须是空白，b点不能是黑棋
					if (KeyPointCheck(x, y, FirstSame[i], i) == true)
						threecount++;
				if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1) && //a点是空白
					(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//n点必须是空白，c点不能是黑棋
					(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//m点必须是空白，b点不能是黑棋
					if (KeyPointCheck(x, y, FirstSame[i + 4], i + 4) == true)
						threecount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 2 == 0)//单独一子，可能会形成冲四和活三
			{
				//冲四检查
				if (FirstEmpty[i] == 1 && SecondSame[i] == 3)
					if (KeyPointCheck(x, y, FirstSame[i], i) == true)
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 3)
					if (KeyPointCheck(x, y, FirstSame[i + 4], i + 4) == true)
						fourcount++;

				//活三检查
				//   bmXXaXnc
				if ((FirstEmpty[i] == 1 && SecondSame[i] == 2) &&//a点是空白
					(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//m必须是空白，b点不是黑子
					(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//n必须是空白，c不是黑棋
					if (KeyPointCheck(x, y, FirstSame[i], i) == true)
						threecount++;
				if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2) &&//a点是空白
					(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//m必须是空白，b点不是黑子
					(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//n必须是空白，c不是黑棋
					if (KeyPointCheck(x, y, FirstSame[i + 4], i + 4) == true)
						threecount++;
			}
		}
		//根据统计的结果判断禁手,长连在前面
		if (fourcount > 1)
			result = FORBIDDEN;
		else if (threecount > 1)
			result = FORBIDDEN;
	}

	return result;
}

//关键点检测，判断构成活三，冲四，活四的必要条件之一
//即，关键点是否是禁手的点，如果禁手的话，那就不能构成活三，冲四，活四
//其实就是递归调用裁判函数，其中有一些调用之前的准备工作
//例如假活三
bool cBoard::KeyPointCheck(const int x, const int y, int FirstSame, int direction)
{
	int KeyX, KeyY;
	//先计算关键点的坐标
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

	//关键点处先下棋并判断是否禁手,注意是形参变化不会影响整个棋盘
	SetAtTable(KeyX, KeyY, BLACK);
	if (referee(KeyX, KeyY) == FORBIDDEN)//如果禁手
		return false;//不构成
	else
		return true;//构成活三、活四、冲四
}