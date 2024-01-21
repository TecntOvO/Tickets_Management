#pragma once
#ifndef TRAINCONSOLE_H
#define TRAINCONSOLE_H
#include "data.h"

//列车管理
class TrainConsole {
private:
	TrainList TL = nullptr;	//指向存放所有列车信息单链表的头结点的指针
	SearchResult SL;
public:
	friend class Indents_Accounts;
	void LoadTrainInfo();	//初始化列车信息
	void TrainInfoChange(const string& ID, const string& Station_B, const string& Station_E, int Operation, int Tickets_Num);
	void TrainInfoChange(IndentInfoNode* p, int Operation, int Tickets_Num);
	int TrainSearch(const string& Station_B, const string& Station_E);	//搜索符合要求的列车
	void ResultShow(int Condition, int Order);
	int Tickets_Selected_ID(string Selected_ID);
	void AddWaitOrder_TC(vector<WaitList>& ps, string Selected_ID);
	void AssignWaitTicket(Indents_Accounts& IA_OBJ);
};

#endif // !TRAINCONSOLE_H

