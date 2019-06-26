#include "cBoard.h"
#include "cManager.h"
#include "cRole.h"
#include "macro.h"


int main()
{
    system("chcp 65001");// 命令行编码改为utf-8

	/*测试文件,testfile里的前四句放到全局就可以用了
	void test();
	test();*/

	//主程序部分
	cManager oManager;
	cBoard oBoard;

	oManager.ModeChoice();

	while (oManager.Gaming(oBoard) == 1)//再来一盘
	{
		oBoard.SetToZero();
		oManager.ModeChoice();
	}

	return 0;
}
