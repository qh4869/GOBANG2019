//测试文件
//测试文件
#include "macro.h"

void test()
{
	//程序测试部分
	ifstream fin("input.txt");  // 已有输入文件
	ofstream fout("output.txt");  //输出文件
	streambuf *cinbackup;
	streambuf *coutbackup;

	coutbackup = cout.rdbuf(fout.rdbuf());  //用 rdbuf() 重新定向
	cinbackup = cin.rdbuf(fin.rdbuf());  //用 rdbuf() 重新定向
	cout << "Hello world" << endl;   //去文件也
	//char line[100];
	//cin >> line;  //从input.txt文件读入
	//cout << line << endl;  //写入 output.txt
						   // restore standard streambuf   
	//cin.rdbuf(cinbackup);  // 取消，恢复键盘输入
	//cout.rdbuf(coutbackup);  //取消，恢复屏幕输出
							 //测试部分结束

}
