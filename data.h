#pragma once
#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
using namespace std;

//ǰ������
typedef struct AlternateListNode AlternateListNode, * AlternateListNodePtr;
typedef struct AccountInfoNode AccountInfoNode, * AccountInfo;

//վ����Ϣ��Ԫ,˳���
typedef struct {
	string Station_Name;	//վ������
	short int Tickets;	//Ʊ��ֵ/����
	int STIme_Offset;	//վ�㷢��ʱ�������ʼ��վ����ʱ��Ĳ�ֵ
}StationNode, * StationInfo;

//�г��򲹶��ж���
typedef struct AlternateListQueue {
	AlternateListNodePtr front;		//��ͷָ�룬ָ��ͷ��㣬���к򲹲���ʱ�Ӷ�ͷȡ�򲹶���������Ϊfront->next; front->next=front->next->next;
	AlternateListNodePtr rear;		//��βָ�룬���г����µĺ򲹶���ʱ�Ӷ�β���
}AlternateListQueue;

//�г���Ϣ������
typedef struct TrainNode {
	string ID;	//�г���
	StationInfo info;	//վ��+��Ϣ�������Ա�ʽ�洢
	short int Passengers_Capacity, Station_Num; //�˿�����,վ������
	int Begin_Time;	//�״η���ʱ��
	AlternateListQueue AQ; // �򲹶���α����
	struct TrainNode* next;
}TrainNode, * TrainList;

//����������Ա���
typedef struct SearchResultNode {
	TrainNode* p;	//�������Ҫ����г����ָ��
	short int Station_B, Station_E;	//��������ʱ��Ӧվ����±�
	int Start_Time, End_Time;
	short int Remaining_Tickets; //��������վ��֮���ʣ��Ʊ��
}SearchResultNode,*SearchList;

//���������˳���
typedef struct {
	SearchList SRL;	//ָ�����Ա��ָ��
	int length;	//���Ա��Ѵ��Ԫ�ظ������������Ա����������
}SearchResult;

//�˳�����Ϣ��˳���
typedef struct PassengerInfoNode {
	string name;	//����
	string gender;	//�Ա�
	string PhoneN;	//�绰����
	string IC;	//���֤��
}PassengerInfoNode, * PassengerInfo;

//�˳�������Ϣ������
typedef struct IndentInfoNode {
	int OrderID;	//������
	PassengerInfoNode* passenger;	//�˿���Ϣ��ָ��
	TrainNode* Train;	//�����г���ָ��
	short int Station_B, Station_E;	//����վ���յ�վ���±�
	int Start_Time, End_Time;	//����ʱ�䣬�ִ�ʱ��
	string Insurance; //�Ƿ��б���
	short int Order_Tickets_Num;	//������Ʊ������Ϊ1
	struct IndentInfoNode* next;
}IndentInfoNode, * IndentInfo;

//�򲹶�����Ϣ������
typedef struct WaitListNode {
	int WaitID; //�򲹶�����
	AccountInfoNode* Owner;	//ָ��򲹶��������ߵ�ָ��
	vector<PassengerInfoNode*> passengers; //�˿���Ϣ��ָ��
	vector<string> Insurance;//�����������˿���Ϣһһ��Ӧ
	TrainNode* Train;	//���г���ָ��
	short int Station_B, Station_E;	  //����վ���յ�վ���±�
	int Start_Time, End_Time;	//����ʱ�䣬�ִ�ʱ��
	short int Wait_Tickets_Num;	//�򲹳�Ʊ��
	bool WaitFlag; //�򲹱�־ true->���ں���.... false->�򲹳ɹ�
	struct WaitListNode* next;	
}WaitListNode,* WaitList;

//�г���α���н�㶨�� 
typedef struct AlternateListNode {
	WaitListNode* q;  //ָ���˻��еĺ���Ϣ
	AlternateListNode* next; //ָ���г���һ������Ϣ
}AlternateListNode, * AlternateListNodePtr;

//�˻���Ϣ������
typedef struct AccountInfoNode {
	string Account;	//�˺�
	string password;	//����
	PassengerInfo A_P;	//�˳�����Ϣ
	IndentInfo A_I;	//�˳�������Ϣ
	WaitList A_W; //�򲹶�����Ϣ
	short int IndentInfo_Num;	//�˳���������
	short int Waitlist_Num;		//�򲹶�������
	short int PassengerInfo_Num;	//�˳�����Ϣ����
	struct AccountInfoNode* next;
}AccountInfoNode, * AccountInfo;

#endif

