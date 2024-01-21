#pragma once
#ifndef DATA_H
#define DATA_H
#include <string>
#include <vector>
using namespace std;

//前置声明
typedef struct AlternateListNode AlternateListNode, * AlternateListNodePtr;
typedef struct AccountInfoNode AccountInfoNode, * AccountInfo;

//站点信息表单元,顺序表
typedef struct {
	string Station_Name;	//站点名称
	short int Tickets;	//票数值/余座
	int STIme_Offset;	//站点发车时间相对于始发站发车时间的差值
}StationNode, * StationInfo;

//列车候补队列定义
typedef struct AlternateListQueue {
	AlternateListNodePtr front;		//队头指针，指向头结点，进行候补操作时从队头取候补订单，操作为front->next; front->next=front->next->next;
	AlternateListNodePtr rear;		//队尾指针，该列车有新的候补订单时从队尾入队
}AlternateListQueue;

//列车信息，链表
typedef struct TrainNode {
	string ID;	//列车号
	StationInfo info;	//站点+信息，以线性表方式存储
	short int Passengers_Capacity, Station_Num; //乘客容量,站点数量
	int Begin_Time;	//首次发车时间
	AlternateListQueue AQ; // 候补订单伪队列
	struct TrainNode* next;
}TrainNode, * TrainList;

//搜索结果线性表结点
typedef struct SearchResultNode {
	TrainNode* p;	//保存符合要求的列车结点指针
	short int Station_B, Station_E;	//保存搜索时对应站点的下标
	int Start_Time, End_Time;
	short int Remaining_Tickets; //保存上述站点之间的剩余票数
}SearchResultNode,*SearchList;

//搜索结果，顺序表
typedef struct {
	SearchList SRL;	//指向线性表的指针
	int length;	//线性表已存放元素个数，不是线性表最大容量！
}SearchResult;

//乘车人信息，顺序表
typedef struct PassengerInfoNode {
	string name;	//姓名
	string gender;	//性别
	string PhoneN;	//电话号码
	string IC;	//身份证号
}PassengerInfoNode, * PassengerInfo;

//乘车订单信息，链表
typedef struct IndentInfoNode {
	int OrderID;	//订单号
	PassengerInfoNode* passenger;	//乘客信息的指针
	TrainNode* Train;	//乘坐列车的指针
	short int Station_B, Station_E;	//出发站，终点站的下标
	int Start_Time, End_Time;	//出发时间，抵达时间
	string Insurance; //是否有保险
	short int Order_Tickets_Num;	//订购车票数，均为1
	struct IndentInfoNode* next;
}IndentInfoNode, * IndentInfo;

//候补订单信息，链表
typedef struct WaitListNode {
	int WaitID; //候补订单号
	AccountInfoNode* Owner;	//指向候补订单所有者的指针
	vector<PassengerInfoNode*> passengers; //乘客信息的指针
	vector<string> Insurance;//保险情况，与乘客信息一一对应
	TrainNode* Train;	//候补列车的指针
	short int Station_B, Station_E;	  //出发站，终点站的下标
	int Start_Time, End_Time;	//出发时间，抵达时间
	short int Wait_Tickets_Num;	//候补车票数
	bool WaitFlag; //候补标志 true->正在候补中.... false->候补成功
	struct WaitListNode* next;	
}WaitListNode,* WaitList;

//列车候补伪队列结点定义 
typedef struct AlternateListNode {
	WaitListNode* q;  //指向账户中的候补信息
	AlternateListNode* next; //指向列车下一个候补信息
}AlternateListNode, * AlternateListNodePtr;

//账户信息，链表
typedef struct AccountInfoNode {
	string Account;	//账号
	string password;	//密码
	PassengerInfo A_P;	//乘车人信息
	IndentInfo A_I;	//乘车订单信息
	WaitList A_W; //候补订单信息
	short int IndentInfo_Num;	//乘车订单个数
	short int Waitlist_Num;		//候补订单个数
	short int PassengerInfo_Num;	//乘车人信息个数
	struct AccountInfoNode* next;
}AccountInfoNode, * AccountInfo;

#endif

