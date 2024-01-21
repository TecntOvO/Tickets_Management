#pragma once
#ifndef INDENTS_ACCOUNTS_H
#define INDENTS_ACCOUNTS_H

#include <vector>
#include "TrainConsole.h"

using namespace std;

//订单和账户管理
class Indents_Accounts {
private:
	AccountInfoNode* LocateAccount(string A);	//链表查找
	AccountInfo AL = nullptr;	//指向存放所有用户信息单链表头结点的指针
	AccountInfoNode* CurrentA;	//指向当前登录用户的指针
	vector<TrainNode*> ChangedTrain;	//保存修改过的列车
public:
	friend class TrainConsole;



	void Regist();	//注册账号
	bool Login();	//登录账号
	void Change_Password(); //修改密码
	void Regist_AdM();	//添加测试账号

	void AddPessenger();  //添加乘车人信息
	void ChangePessenger(); //修改乘车人信息
	void DeletePessenger();	//删除乘车人信息
	void PassengerShow(int offset); //显示所有乘车人信息
	void PassengerExist(string Selected_ID, const vector<int>& numbers_passenger,vector<int>& numbers_passenger_existed);	//判断乘车人是否已经在所选列车中了
	void AddOrder(vector<int>& PassengerNumbers, vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ); // 添加订单
	void AddOrder(WaitListNode* s);
	void AddWaitOrder(const vector<int>& PassengerNumbers, const vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ); //添加候补订单
	void Indents_Show(int OrderID);
	void Indents_Wait_Show(int WaitID);
	void DeleteOrder(TrainConsole& TC_OBJ);
	int GetPassengerNum();
	void Indents_Wait_Show_Detailed(int WaitID);

};

#endif // !INDENTS_ACCOUNTS_H

