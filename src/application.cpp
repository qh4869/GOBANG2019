#include "cGame.h"

int main()
{

	/*�����ļ�,testfile���ǰ�ľ�ŵ�ȫ�־Ϳ�������
	void test();
	test();*/

	//�����򲿷�
	bool WhetherAgain = false;
	do{
		cGame* pGame = new cGame;
		WhetherAgain = pGame->Gaming();
		delete pGame;
	}while(WhetherAgain);

	return 0;
}
