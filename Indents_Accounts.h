#pragma once
#ifndef INDENTS_ACCOUNTS_H
#define INDENTS_ACCOUNTS_H

#include <vector>
#include "TrainConsole.h"

using namespace std;

//�������˻�����
class Indents_Accounts {
private:
	AccountInfoNode* LocateAccount(string A);	//�������
	AccountInfo AL = nullptr;	//ָ���������û���Ϣ������ͷ����ָ��
	AccountInfoNode* CurrentA;	//ָ��ǰ��¼�û���ָ��
	vector<TrainNode*> ChangedTrain;	//�����޸Ĺ����г�
public:
	friend class TrainConsole;



	void Regist();	//ע���˺�
	bool Login();	//��¼�˺�
	void Change_Password(); //�޸�����
	void Regist_AdM();	//��Ӳ����˺�

	void AddPessenger();  //��ӳ˳�����Ϣ
	void ChangePessenger(); //�޸ĳ˳�����Ϣ
	void DeletePessenger();	//ɾ���˳�����Ϣ
	void PassengerShow(int offset); //��ʾ���г˳�����Ϣ
	void PassengerExist(string Selected_ID, const vector<int>& numbers_passenger,vector<int>& numbers_passenger_existed);	//�жϳ˳����Ƿ��Ѿ�����ѡ�г�����
	void AddOrder(vector<int>& PassengerNumbers, vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ); // ��Ӷ���
	void AddOrder(WaitListNode* s);
	void AddWaitOrder(const vector<int>& PassengerNumbers, const vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ); //��Ӻ򲹶���
	void Indents_Show(int OrderID);
	void Indents_Wait_Show(int WaitID);
	void DeleteOrder(TrainConsole& TC_OBJ);
	int GetPassengerNum();
	void Indents_Wait_Show_Detailed(int WaitID);

};

#endif // !INDENTS_ACCOUNTS_H

