#pragma once
const int BLACK = 1;
const int WHITE = 2;
const int EMPTY = 0;
const int PLAYERVSPLAYER = 2;
const int PLAYERVSAI = 1;
const int PLAYER = 1;
const int AI = 2;
const int PLAYER1 = 1;
const int PLAYER2 = 2;
const int YEMPTY = 0;
const int NEMPTY = 1;
const int SPE = 3;//��ʾһ�ָ�һ����������� ����:    �¡����__
const int FORBIDDEN = 3;
const int EQUAL = 4;

//�����ļ�
#include <iostream>
#include <ostream>
#include <fstream>
using namespace std;
extern ifstream fin;  // ���������ļ�
extern ofstream fout;  //����ļ�
extern streambuf *cinbackup;
extern streambuf *coutbackup;