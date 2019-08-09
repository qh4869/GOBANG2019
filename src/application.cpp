#include "cGame.h"

int main()
{

	/*测试文件,testfile里的前四句放到全局就可以用了
	void test();
	test();*/

	//主程序部分
	bool WhetherAgain = false;
	do{
		cGame* pGame = new cGame;
		WhetherAgain = pGame->Gaming();
		delete pGame;
	}while(WhetherAgain);

	return 0;
}
