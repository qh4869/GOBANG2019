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
	system("cls");//命令行清屏
	int ModeInput;
	char c;//cin.sync() and fflush(stdin) do not work with Visual Studio 2015
	//输入游戏模式
	cout << "游戏模式选择：1玩家对电脑，2玩家对玩家" << endl;
	cout << "请输入您的选择:";
	while (!(cin >> ModeInput))
	{
		cout << "输入错误，请重新输入:";
		do {
			c = getchar();
		} while (c != '\n');
		cin.clear();//清除标志位
	}
	while (ModeInput != PLAYERVSAI && ModeInput != PLAYERVSPLAYER)
	{
		cout << "输入错误，请重新输入:";
		while (!(cin >> ModeInput))
		{
			cout << "输入错误，请重新输入:";
			do {
				c = getchar();
			} while (c != '\n');
			cin.clear();//清除标志位
		}
	}
	GameMode = ModeInput;

	//输入玩家的棋子颜色
	if (GameMode == PLAYERVSAI)
		cout << endl << "玩家棋子选择：1黑色，2白色" << endl;
	else
		cout << endl << "玩家1棋子选择：1黑色，2白色" << endl;
	cout << "请输入您的选择:";
	while (!(cin >> ModeInput))
	{
		cout << "输入错误，请重新输入:";
		do {
			c = getchar();
		} while (c != '\n');
		cin.clear();//清除标志位
	}
	while (ModeInput != BLACK && ModeInput != WHITE)
	{
		cout << "输入错误，请重新输入:";
		while (!(cin >> ModeInput))
		{
			cout << "输入错误，请重新输入:";
			do {
				c = getchar();
			} while (c != '\n');
			cin.clear();//清除标志位
		}
	}
	PlayerColor = ModeInput;
	if (PlayerColor == BLACK)
		WhoNext = 1;
	else
		WhoNext = 2;

	char temp[4];
	cin.getline(temp, 3);//之前的输入在缓冲区里留下了一个回车，所以这里停不下来
}

//裁判函数考虑禁手
//返回值：1 BLACK胜不禁手 2 WHITE胜不禁手 3 FORBIDDEN黑色禁手白色胜 0无人胜
//有关禁手看文件夹的图片
int cManager::referee(cBoard oBoard, const int x, const int y)
{
	int result = 0;//裁判结果
	//--------------------------------------白棋判断（没有禁手）-------------------------------
	if (oBoard.GetAtTable(x, y) == WHITE)
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
		for (xNow = x - 1; xNow >= 0 && oBoard.GetAtTable(xNow, y) == WHITE; xNow--, FirstSame[0]++);
		//右上搜索
		for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow++, FirstSame[1]++);
		//向右搜索
		for (yNow = y + 1; yNow <= 14 && oBoard.GetAtTable(x, yNow) == WHITE; yNow++, FirstSame[2]++);
		//向右下搜索
		for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow++, FirstSame[3]++);
		//向下搜索
		for (xNow = x + 1; xNow <= 14 && oBoard.GetAtTable(xNow, y) == WHITE; xNow++, FirstSame[4]++);
		//向左下搜索
		for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow--, FirstSame[5]++);
		//向左搜索
		for (yNow = y - 1; yNow >= 0 && oBoard.GetAtTable(x, yNow) == WHITE; yNow--, FirstSame[6]++);
		//左上搜索
		for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow--, FirstSame[7]++);

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
		for (xNow = x - 1; xNow >= 0 && oBoard.GetAtTable(xNow, y) == BLACK; xNow--, FirstSame[0]++);
		for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, FirstEmpty[0]++);
		temp_x = xNow;
		for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == WHITE; xNow--, SecondDiff[0]++);
		for (xNow = temp_x; xNow >= 0 && oBoard.GetAtTable(xNow, y) == BLACK; xNow--, SecondSame[0]++);
		for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow--, SecondEmpty[0]++);
		for (; xNow >= 0 && oBoard.GetAtTable(xNow, y) == BLACK; xNow--, ThirdSame[0]++);


		//右上搜索
		for (xNow = x - 1, yNow = y + 1; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, FirstSame[1]++);
		for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, FirstEmpty[1]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow++, SecondDiff[1]++);
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, SecondSame[1]++);
		for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow++, SecondEmpty[1]++);
		for (; xNow >= 0 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow++, ThirdSame[1]++);


		//向右搜索
		for (yNow = y + 1; yNow <= 14 && oBoard.GetAtTable(x, yNow) == BLACK; yNow++, FirstSame[2]++);
		for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, FirstEmpty[2]++);
		temp_y = yNow;
		for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == WHITE; yNow++, SecondDiff[2]++);
		for (yNow = temp_y; yNow <= 14 && oBoard.GetAtTable(x, yNow) == BLACK; yNow++, SecondSame[2]++);
		for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow++, SecondEmpty[2]++);
		for (; yNow <= 14 && oBoard.GetAtTable(x, yNow) == BLACK; yNow++, ThirdSame[2]++);


		//向右下搜索
		for (xNow = x + 1, yNow = y + 1; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, FirstSame[3]++);
		for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, FirstEmpty[3]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow++, SecondDiff[3]++);
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, SecondSame[3]++);
		for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow++, SecondEmpty[3]++);
		for (; xNow <= 14 && yNow <= 14 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow++, ThirdSame[3]++);


		//向下搜索
		for (xNow = x + 1; xNow <= 14 && oBoard.GetAtTable(xNow, y) == BLACK; xNow++, FirstSame[4]++);
		for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, FirstEmpty[4]++);
		temp_x = xNow;
		for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == WHITE; xNow++, SecondDiff[4]++);
		for (xNow = temp_x; xNow <= 14 && oBoard.GetAtTable(xNow, y) == BLACK; xNow++, SecondSame[4]++);
		for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == EMPTY; xNow++, SecondEmpty[4]++);
		for (; xNow <= 14 && oBoard.GetAtTable(xNow, y) == BLACK; xNow++, ThirdSame[4]++);


		//向左下搜索
		for (xNow = x + 1, yNow = y - 1; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, FirstSame[5]++);
		for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, FirstEmpty[5]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow++, yNow--, SecondDiff[5]++);
		for (xNow = temp_x, yNow = temp_y; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, SecondSame[5]++);
		for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow++, yNow--, SecondEmpty[5]++);
		for (; xNow <= 14 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow++, yNow--, ThirdSame[5]++);

		//向左搜索
		for (yNow = y - 1; yNow >= 0 && oBoard.GetAtTable(x, yNow) == BLACK; yNow--, FirstSame[6]++);
		for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, FirstEmpty[6]++);
		temp_y = yNow;
		for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == WHITE; yNow--, SecondDiff[6]++);
		for (yNow = temp_y; yNow >= 0 && oBoard.GetAtTable(x, yNow) == BLACK; yNow--, SecondSame[6]++);
		for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == EMPTY; yNow--, SecondEmpty[6]++);
		for (; yNow >= 0 && oBoard.GetAtTable(x, yNow) == BLACK; yNow--, ThirdSame[6]++);

		//左上搜索
		for (xNow = x - 1, yNow = y - 1; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, FirstSame[7]++);
		for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, FirstEmpty[7]++);
		temp_x = xNow;
		temp_y = yNow;
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == WHITE; xNow--, yNow--, SecondDiff[7]++);
		for (xNow = temp_x, yNow = temp_y; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, SecondSame[7]++);
		for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == EMPTY; xNow--, yNow--, SecondEmpty[7]++);
		for (; xNow >= 0 && yNow >= 0 && oBoard.GetAtTable(xNow, yNow) == BLACK; xNow--, yNow--, ThirdSame[7]++);

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
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)//满足关键点不禁手的条件
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

			else if (FirstSame[i] + FirstSame[i + 4] == 2)//三连,可能会形成冲四或者活三
			{
				//冲四检查
				if (FirstEmpty[i] == 1 && SecondSame[i] == 1)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i))
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4))
						fourcount++;

				//活三检查
				//    ecaXXXbdf
				//这个是禁手里最不好想清楚的，条件里面应该有重复的地方，不过这样写应该最好理解
				if ((FirstEmpty[i] >= 1 && FirstEmpty[i + 4] >= 1) && //ab是空白
					(FirstEmpty[i] >= 2 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] == 1 && SecondDiff[i] >= 1 && FirstEmpty[i + 4] >= 2 || FirstEmpty[i] >= 2 && FirstEmpty[i + 4] == 1 && SecondDiff[i + 4] >= 2) &&//cd不能是黑棋，也不能同时是白色
					(FirstEmpty[i] == 1 || FirstEmpty[i] == 2 && SecondSame[i] == 0 || FirstEmpty[i] >= 3) &&//如果ac都空，则e不可以是黑棋
					(FirstEmpty[i + 4] == 1 || FirstEmpty[i + 4] == 2 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 3))//如果bd空，则f不可以是黑棋
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true && KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)//ab不是禁手
						threecount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 1)//二连，可能形成冲四和活三
			{
				//冲四检查
				if (FirstEmpty[i] == 1 && SecondSame[i] == 2)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						fourcount++;

				//活三检查
				//   bmXXaXnc
				//注意 X_XX_X 不是活三！
				//然而 X_XXX_X 四四禁手！
				if ((FirstEmpty[i] == 1 && SecondSame[i] == 1) && //a点是空白
					(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//n点必须是空白，c点不能是黑棋
					(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//m点必须是空白，b点不能是黑棋
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						threecount++;
				if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 1) && //a点是空白
					(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//n点必须是空白，c点不能是黑棋
					(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//m点必须是空白，b点不能是黑棋
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						threecount++;
			}

			else if (FirstSame[i] + FirstSame[i + 4] == 2 == 0)//单独一子，可能会形成冲四和活三
			{
				//冲四检查
				if (FirstEmpty[i] == 1 && SecondSame[i] == 3)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						fourcount++;
				if (FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 3)
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
						fourcount++;

				//活三检查
				//   bmXXaXnc
				if ((FirstEmpty[i] == 1 && SecondSame[i] == 2) &&//a点是空白
					(SecondEmpty[i] == 1 && ThirdSame[i] == 0 || SecondEmpty[i] >= 2) &&//m必须是空白，b点不是黑子
					(FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 0 || FirstEmpty[i + 4] >= 2))//n必须是空白，c不是黑棋
					if (KeyPointCheck(oBoard, x, y, FirstSame[i], i) == true)
						threecount++;
				if ((FirstEmpty[i + 4] == 1 && SecondSame[i + 4] == 2) &&//a点是空白
					(SecondEmpty[i + 4] == 1 && ThirdSame[i + 4] == 0 || SecondEmpty[i + 4] >= 2) &&//m必须是空白，b点不是黑子
					(FirstEmpty[i] == 1 && SecondSame[i] == 0 || FirstEmpty[i] >= 2))//n必须是空白，c不是黑棋
					if (KeyPointCheck(oBoard, x, y, FirstSame[i + 4], i + 4) == true)
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
bool cManager::KeyPointCheck(cBoard oBoard, const int x, const int y, int FirstSame, int direction)
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
	oBoard.SetAtTable(KeyX, KeyY, BLACK);
	if (referee(oBoard, KeyX, KeyY) == FORBIDDEN)//如果禁手
		return false;//不构成
	else
		return true;//构成活三、活四、冲四
}

//返回1 代表继续下一盘
//返回0 代表退出
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
					cout << "这里已经有棋子了，";
					oPlayer1.SetAtPosition();
				} 
				oBoard.SetAtTable(oPlayer1.GetAtRow(), oPlayer1.GetAtColumn(), PlayerColor);
				oBoard.RefreshScreen(oPlayer1.GetAtRow(), oPlayer1.GetAtColumn());
				fnExchange();//交换下一次下棋的角色
				result = referee(oBoard, oPlayer1.GetAtRow(), oPlayer1.GetAtColumn());
				if (result)
					break;

			}
			else if (WhoNext == PLAYER2)
			{
				oPlayer2.SetAtPosition();
				while (oBoard.WhetherEmpty(oPlayer2.GetAtRow(), oPlayer2.GetAtColumn()) == NEMPTY)
				{
					cout << "这里已经有棋子了，";
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
					cout << "这里已经有棋子了，";
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
				if (oAI.SearchForBestPosition() == -1)//没有地方可以下棋了，和棋
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
	char c;
	cout << "想要再来一盘吗？(Y/N)" << endl;
	again = cin.get();
	do {
		c = cin.get();
	} while (c != '\n');
	if (again == 'Y' || again == 'y')
		return 1;
	else
		return 0;
}