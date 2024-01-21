#include "tool.h"
#include <conio.h>
#include "data.h"

//printf������ʾ
void printCentered(const char *str,int width) {
	int length = strlen(str);
	int spaces = (width - length) / 2;
	printf("%*s%s%*s|", spaces, "", str, width - spaces - length, "");
}

//printf������ʾ ���غ���
void printCentered(string str, int width) {
	int length = str.length();
	int spaces = (width - length) / 2;
	printf("%*s%s%*s|", spaces, "", str.c_str(), width - spaces - length, "");
}

//��Vector<int>ת��Ϊconst char*
const char* TranslateIntToChar(int integer) {
	char* itc = (char*) malloc(6 * sizeof(char));
	snprintf(itc, 6, "%d", integer);
	return itc;
}

//��ʽ��ʱ��
const char* TranslateTimeToChar(int time){
	//������minΪ��λ��ʱ��
	int hour = time / 60;
	int minute = time % 60;
	char* formattedTime = (char *) malloc(6*sizeof(char)); //��̬�����ڴ�

	// ��ʽ��Сʱ
	if(hour<10) snprintf(formattedTime, 6, "0%d:",hour);
	else snprintf(formattedTime,6,"%d:",hour);

	//��ʽ������
	if(minute<10) snprintf(formattedTime+3, 3, "0%d",minute);
	else snprintf(formattedTime+3,3,"%d",minute);

	return formattedTime;
}

//�ַ����ָ��
void Split(const string& str, vector<string>& vstr, const char& split) {
	vstr.clear();
	istringstream iss(str);
	string unit;
	while (getline(iss, unit, split)) {
		vstr.push_back(unit);
	}
}

//��ȡ�ַ��������е�Ԫ�أ����ַ������Ǵ�����ʱ����false
bool TranslateToInt(vector<string>& vstr, vector<int>& intNumbers){
	intNumbers.clear();
	bool IsPureNum =true;
	// �����ַ���������ת��ÿ��Ԫ��
	for (const string& str : vstr) {
		try {
			// ʹ�� stoi ���ַ���ת��Ϊ����������ӵ�����������
			intNumbers.push_back(stoi(str));
		}
		catch (const invalid_argument) {
			// �����޷�ת��Ϊ�������ַ���
			//cerr << "Invalid argument: " << str << endl;
			IsPureNum = false;
		}
		catch (const out_of_range) {
			// ����ת��������� int ��Χ���ַ���
			//cerr << "Out of range: " << str << endl;
			IsPureNum = false;
		}
	}
	return IsPureNum;
}

//���ڲ˵�ѡ���Ӧ��ֵ��Ŀ������,���Ǵ���ֵ����-1
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

//����������Ϣ
string GetPasswordInput() {
	string password;
	char ch;
	while (true) {
		ch = getch(); // ʹ�� getch() �ӿ���̨��ȡ�ַ���ʵ����������ʱ������Ч��
		if (ch == 13) {
			// �س�������������
			break;
		}
		else if (ch == 8) {
			// �˸����ɾ����һ���ַ�
			if (password.length() > 0) {
				cout << "\b \b"; // �˸���Ϳո����ڸ���ǰһ���ַ�
				password.pop_back();
			}
		}
		else {
			// �����ַ�����ӵ������в���ӡ*
			cout << "*";
			password.push_back(ch);
		}
	}
	cout << endl; // ����
	return password;
}

//���vector�����Ӽ� �ж�a�Ƿ�Ϊb���Ӽ�
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


