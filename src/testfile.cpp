//�����ļ�
//�����ļ�
#include "macro.h"

void test()
{
	//������Բ���
	ifstream fin("input.txt");  // ���������ļ�
	ofstream fout("output.txt");  //����ļ�
	streambuf *cinbackup;
	streambuf *coutbackup;

	coutbackup = cout.rdbuf(fout.rdbuf());  //�� rdbuf() ���¶���
	cinbackup = cin.rdbuf(fin.rdbuf());  //�� rdbuf() ���¶���
	cout << "Hello world" << endl;   //ȥ�ļ�Ҳ
	//char line[100];
	//cin >> line;  //��input.txt�ļ�����
	//cout << line << endl;  //д�� output.txt
						   // restore standard streambuf   
	//cin.rdbuf(cinbackup);  // ȡ�����ָ���������
	//cout.rdbuf(coutbackup);  //ȡ�����ָ���Ļ���
							 //���Բ��ֽ���

}
