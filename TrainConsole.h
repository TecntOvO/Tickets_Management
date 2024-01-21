#pragma once
#ifndef TRAINCONSOLE_H
#define TRAINCONSOLE_H
#include "data.h"

//�г�����
class TrainConsole {
private:
	TrainList TL = nullptr;	//ָ���������г���Ϣ�������ͷ����ָ��
	SearchResult SL;
public:
	friend class Indents_Accounts;
	void LoadTrainInfo();	//��ʼ���г���Ϣ
	void TrainInfoChange(const string& ID, const string& Station_B, const string& Station_E, int Operation, int Tickets_Num);
	void TrainInfoChange(IndentInfoNode* p, int Operation, int Tickets_Num);
	int TrainSearch(const string& Station_B, const string& Station_E);	//��������Ҫ����г�
	void ResultShow(int Condition, int Order);
	int Tickets_Selected_ID(string Selected_ID);
	void AddWaitOrder_TC(vector<WaitList>& ps, string Selected_ID);
	void AssignWaitTicket(Indents_Accounts& IA_OBJ);
};

#endif // !TRAINCONSOLE_H

