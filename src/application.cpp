#include "cBoard.h"
#include "cManager.h"
#include "cRole.h"
#include "macro.h"


void main()
{
	/*�����ļ�,testfile���ǰ�ľ�ŵ�ȫ�־Ϳ�������
	void test();
	test();*/

	//�����򲿷�
	cManager oManager;
	cBoard oBoard;

	oManager.ModeChoice();

	while (oManager.Gaming(oBoard) == 1)//����һ��
	{
		oBoard.SetToZero();
		oManager.ModeChoice();
	}
}