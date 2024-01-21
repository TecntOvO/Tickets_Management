#pragma once
#ifndef TOOL_H
#define TOOL_H
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void printCentered(const char* str, int width);	//printf居中显示
void printCentered(string str, int width);
const char* TranslateIntToChar(int integer);//将Vector<int>转化为const char*
const char* TranslateTimeToChar(int time);//格式化时间
void Split(const string& str, vector<string>& vstr, const char& split);	//字符串分割函数
string GetPasswordInput();	//保护输入信息
bool TranslateToInt(vector<string>& vstr, vector<int>& intNumbers);	//提取字符串容器中的元素，当字符串不是纯数字时返回false
int ChooseInput();	//用于菜单选择对应数值项目输入用,不是纯数值返回-1
bool IsChildVector(const vector<int>& a, const vector<int>& b);	//检测vector容器子集 判断a是否为b的子集

#endif // !TOOL_H
