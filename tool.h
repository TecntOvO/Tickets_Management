#pragma once
#ifndef TOOL_H
#define TOOL_H
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void printCentered(const char* str, int width);	//printf������ʾ
void printCentered(string str, int width);
const char* TranslateIntToChar(int integer);//��Vector<int>ת��Ϊconst char*
const char* TranslateTimeToChar(int time);//��ʽ��ʱ��
void Split(const string& str, vector<string>& vstr, const char& split);	//�ַ����ָ��
string GetPasswordInput();	//����������Ϣ
bool TranslateToInt(vector<string>& vstr, vector<int>& intNumbers);	//��ȡ�ַ��������е�Ԫ�أ����ַ������Ǵ�����ʱ����false
int ChooseInput();	//���ڲ˵�ѡ���Ӧ��ֵ��Ŀ������,���Ǵ���ֵ����-1
bool IsChildVector(const vector<int>& a, const vector<int>& b);	//���vector�����Ӽ� �ж�a�Ƿ�Ϊb���Ӽ�

#endif // !TOOL_H
