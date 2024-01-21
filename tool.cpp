#include "tool.h"
#include <conio.h>
#include "data.h"

//printf居中显示
void printCentered(const char *str,int width) {
	int length = strlen(str);
	int spaces = (width - length) / 2;
	printf("%*s%s%*s|", spaces, "", str, width - spaces - length, "");
}

//printf居中显示 重载函数
void printCentered(string str, int width) {
	int length = str.length();
	int spaces = (width - length) / 2;
	printf("%*s%s%*s|", spaces, "", str.c_str(), width - spaces - length, "");
}

//将Vector<int>转化为const char*
const char* TranslateIntToChar(int integer) {
	char* itc = (char*) malloc(6 * sizeof(char));
	snprintf(itc, 6, "%d", integer);
	return itc;
}

//格式化时间
const char* TranslateTimeToChar(int time){
	//传入以min为单位的时间
	int hour = time / 60;
	int minute = time % 60;
	char* formattedTime = (char *) malloc(6*sizeof(char)); //动态分配内存

	// 格式化小时
	if(hour<10) snprintf(formattedTime, 6, "0%d:",hour);
	else snprintf(formattedTime,6,"%d:",hour);

	//格式化分钟
	if(minute<10) snprintf(formattedTime+3, 3, "0%d",minute);
	else snprintf(formattedTime+3,3,"%d",minute);

	return formattedTime;
}

//字符串分割函数
void Split(const string& str, vector<string>& vstr, const char& split) {
	vstr.clear();
	istringstream iss(str);
	string unit;
	while (getline(iss, unit, split)) {
		vstr.push_back(unit);
	}
}

//提取字符串容器中的元素，当字符串不是纯数字时返回false
bool TranslateToInt(vector<string>& vstr, vector<int>& intNumbers){
	intNumbers.clear();
	bool IsPureNum =true;
	// 遍历字符串向量并转换每个元素
	for (const string& str : vstr) {
		try {
			// 使用 stoi 将字符串转换为整数，并添加到整数向量中
			intNumbers.push_back(stoi(str));
		}
		catch (const invalid_argument) {
			// 处理无法转换为整数的字符串
			//cerr << "Invalid argument: " << str << endl;
			IsPureNum = false;
		}
		catch (const out_of_range) {
			// 处理转换结果超出 int 范围的字符串
			//cerr << "Out of range: " << str << endl;
			IsPureNum = false;
		}
	}
	return IsPureNum;
}

//用于菜单选择对应数值项目输入用,不是存数值返回-1
int ChooseInput() {
	string entry;
	cin >> entry;
	for (const char& str :entry) {
		if (!isdigit(str)) {
			return -1;
		}
	}
	return stoi(entry);
}

//保护输入信息
string GetPasswordInput() {
	string password;
	char ch;
	while (true) {
		ch = getch(); // 使用 getch() 从控制台获取字符，实现密码输入时的隐藏效果
		if (ch == 13) {
			// 回车键，结束输入
			break;
		}
		else if (ch == 8) {
			// 退格键，删除上一个字符
			if (password.length() > 0) {
				cout << "\b \b"; // 退格符和空格用于覆盖前一个字符
				password.pop_back();
			}
		}
		else {
			// 其他字符，添加到密码中并打印*
			cout << "*";
			password.push_back(ch);
		}
	}
	cout << endl; // 换行
	return password;
}

//检测vector容器子集 判断a是否为b的子集
bool IsChildVector(const vector<int>& a, const vector<int>& b) {
	int j;
	for (int i = 0;i < a.size();i++) {
		j = 0;
		for (;j < b.size();j++) {
			if (a[i] == b[j])	break;
		}
		if (j >= b.size()) return false;
	}
	return true;
}


