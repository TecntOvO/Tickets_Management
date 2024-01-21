#include <fstream>
#include <vector>
#include "TrainConsole.h"
#include "Indents_Accounts.h"
#include "data.h"
#include "tool.h"
#include "menu.h"

#define BYBEGINTIME 0	//按照出发时间排序
#define BYTICKETS 1	//按照剩余车票数排序
#define BYTIME 2	//按照乘坐时长排序
#define BYREACHTIME 3	//按照抵达时间排序
#define DECENDING 0 //降序
#define ASCENDING 1	//升序

//初始化列车信息
void TrainConsole::LoadTrainInfo() {
	int Train_COUNT = 0;	//记录列车数，用于创建保存搜索结果的线性表
	//创建头结点
	TL = new TrainNode;
	TL->next = nullptr;
	TL->info = nullptr;
	//读取csv文件并开始创建单链表
	ifstream File("TrainInfo.csv", ios::in);
	string LineS;
	//getline(File, LineS);	//跳过第一行

	//循环创建链表结点和写入信息
	while (1) {
		getline(File, LineS);
		if (LineS == "") break;
		Train_COUNT++;
		vector<string> LineV;
		Split(LineS, LineV, ',');
		TrainNode* s = new TrainNode;
		s->ID = LineV[0];	//写入列车号
		s->Passengers_Capacity = stoi(LineV[1]);	//写入乘客容量
		s->Begin_Time = stoi(LineV[2]);	//写入发车时间
		s->Station_Num = LineV.size() - 3;	//写入站点数量
		s->info = new StationNode[LineV.size() - 3];	//创建站点线性表

		for (int i = 3;i < LineV.size();i++) {
			vector<string> StationV;
			Split(LineV[i], StationV, '-');
			s->info[i - 3].Station_Name = StationV[0];	//写入站点名称
			s->info[i - 3].Tickets = s->Passengers_Capacity;	//写入站点票数值/余座
			s->info[i - 3].STIme_Offset = stoi(StationV[1]);	//写入站点发车时间相对于始发站发车时间的差值
		}
		// 初始化列车的候补队列
		s->AQ.front = s->AQ.rear = new AlternateListNode;
		s->AQ.front->q = NULL;
		s->AQ.front->next = nullptr;

		//前插法链接结点
		s->next = TL->next;
		TL->next = s;
	}
	SL.SRL = new SearchResultNode[Train_COUNT];	//初始化搜索结果的线性表
	SL.length = 0;
}

//搜索符合条件的列车	Station_B->出发站名称 Station_E->终点站名称
int TrainConsole::TrainSearch(const string& Station_B, const string& Station_E) {
	SL.length = 0;	//“清空”搜索结果的线性表
	TrainNode* p = TL->next;
	//遍历整个列车信息链表
	while (p) {
		for (int i = 0;i < p->Station_Num - 1;i++) {
			if (p->info[i].Station_Name == Station_B) {
				for (int j = i + 1;j < p->Station_Num;j++) {	//终点站一定在出发站之后，估j=i+1
					if (p->info[j].Station_Name == Station_E) {
						SL.SRL[SL.length].p = p;	//保存符合条件列车的指针
						SL.SRL[SL.length].Station_B = i;	//保存出发站在该列车站点线性表中的下标
						SL.SRL[SL.length].Station_E = j;	//保存终点站在该列车站点线性表中的下标
						SL.SRL[SL.length].Start_Time = p->Begin_Time + p->info[i].STIme_Offset;	//保存出发站出发时间
						SL.SRL[SL.length].End_Time = p->Begin_Time + p->info[j].STIme_Offset;	//保存终点站抵达时间
						//计算剩余票数
						int Remaining_Tickets;
						for (int a = i;a < j;a++) {	//不能包含终点站的座位数，估是小于而非小于等于
							if (a == i) Remaining_Tickets = p->info[a].Tickets;
							else {
								if (p->info[a].Tickets < Remaining_Tickets) {
									Remaining_Tickets = p->info[a].Tickets;
								}
							}
						}
						SL.SRL[SL.length].Remaining_Tickets = Remaining_Tickets;	//保存该列车从出发站到终点站的剩余票数
						SL.length++;
						break;
					}
				}
				break;
			}
		}
		p = p->next;
	}
	return SL.length;
}

//显示结果 Condition->排序条件 Order->排序顺序
void TrainConsole::ResultShow(int Condition, int Order) {
	system("cls");
	Train_Info_Title();
	SearchList Temp = SL.SRL;	
	if (SL.length == 0) {
		cout << "                                404:未找到结果                                          \n\n";
		return;
	}
	//按照出发时间排序
	if (Condition == BYBEGINTIME) {
		int m = SL.length - 1, flag = 1;
		while (m > 0 && flag == 1) {
			flag = 0;
			for (int j = 0;j < m;j++) {
				if (Temp[j].Start_Time < Temp[j + 1].Start_Time) {
					SearchResultNode t = Temp[j];
					Temp[j] = Temp[j + 1];
					Temp[j + 1] = t;
					flag = 1;
				}
			}
			m--;
		}

	}

	//按照剩余票数排序
	else if (Condition == BYTICKETS) {
		int m = SL.length - 1, flag = 1;
		while (m > 0 && flag == 1) {
			flag = 0;
			for (int j = 0;j < m;j++) {
				if (Temp[j].Remaining_Tickets < Temp[j + 1].Remaining_Tickets) {
					SearchResultNode t = Temp[j];
					Temp[j] = Temp[j + 1];
					Temp[j + 1] = t;
					flag = 1;
				}
			}
			m--;
		}
	}

	//按照乘坐时长排序
	else if (Condition == BYTIME) {
		int m = SL.length - 1, flag = 1;
		while (m > 0 && flag == 1) {
			flag = 0;
			for (int j = 0;j < m;j++) {
				if ((Temp[j].Start_Time - Temp[j].End_Time) < (Temp[j + 1].Start_Time - Temp[j + 1].End_Time)) {
					SearchResultNode t = Temp[j];
					Temp[j] = Temp[j + 1];
					Temp[j + 1] = t;
					flag = 1;
				}
			}
			m--;
		}
	}

	//按照抵达时间排序
	else if (Condition == BYREACHTIME) {
		int m = SL.length - 1, flag = 1;
		while (m > 0 && flag == 1) {
			flag = 0;
			for (int j = 0;j < m;j++) {
				if (Temp[j].End_Time < Temp[j + 1].End_Time) {
					SearchResultNode t = Temp[j];
					Temp[j] = Temp[j + 1];
					Temp[j + 1] = t;
					flag = 1;
				}
			}
			m--;
		}
	}

	//降序
	if (Order == DECENDING) {
		for (int i = 0;i < SL.length;i++) {
			Train_Info_Line(Temp[i]);
		}
	}

	//升序
	else if (Order == ASCENDING) {
		for (int i = SL.length - 1;i >= 0;i--) {
			Train_Info_Line(Temp[i]);
		}
	}
}

//判断所选列车号的列车是否存在以及是否有票
int TrainConsole::Tickets_Selected_ID(string Selected_ID)
{
	int i = 0;
	SearchList Temp = SL.SRL;
	while (i < SL.length && Selected_ID != SL.SRL[i].p->ID) i++; //先判断 i < SL.length

	// 判断输入的列车号是否合法(是否在给出的范围内)
	if (i >= SL.length)
	{
		return -1;
	}
	// 返回所选列车站点间票数
	else
	{
		return Temp[i].Remaining_Tickets;
	}
}

//修改列车信息 ID->列车号 Operation->1增加/0减少车票 Tickers_Num->要减去的票数
void TrainConsole::TrainInfoChange(const string& ID,const string& Station_B, const string& Station_E, int Operation, int Tickets_Num) {
	TrainNode* p = TL->next;	//先让p指向第一个列车结点;
	while (p && p->ID != ID)p = p->next;	//找到ID为所给ID的列车的指针
	if (p) {
		int i = 0,j;
		//找到对应站点的下标
		for (;i <p->Station_Num-1;i++)
		{
			if (p->info[i].Station_Name == Station_B) {
				for (j = i + 1;j < p->Station_Num;j++) {
					if (p->info[j].Station_Name == Station_E) {
						break;
					}
				}
				break;
			}
		}

		//修改票数
		for (int m = i;m <= j;m++) {
			if (Operation) {
				p->info[m].Tickets += Tickets_Num;
			}
			else {
				p->info[m].Tickets -= Tickets_Num;
			}
		}
	}
}

//修改列车信息 p->指向订单的指针 Operation->1增加/0减少车票 Tickers_Num->要减去的票数
void TrainConsole::TrainInfoChange(IndentInfoNode* p,int Operation, int Tickets_Num) {
	if (p) {
		//修改票数
		for (int m = p->Station_B;m <= p->Station_E;m++) {
			if (Operation) {
				p->Train->info[m].Tickets += Tickets_Num;
			}
			else {
				p->Train->info[m].Tickets -= Tickets_Num;
			}
		}
	}
}

//候补分配
void TrainConsole::AssignWaitTicket(Indents_Accounts& IA_OBJ) {
	for(int i=0;i<IA_OBJ.ChangedTrain.size();i++)  //第i个被退票的列车
	{
		AlternateListNode* Temp = IA_OBJ.ChangedTrain[i]->AQ.front->next,*Temp_PRE= IA_OBJ.ChangedTrain[i]->AQ.front;
		int Tickets_Num; //对应中间站的剩余最低票数

		while(Temp) //遍历列车的候补订单列表
		{
			// 根据候补订单的站点 遍历列车站点 找到 Tickets_Num 然后与乘车人数量进行比较
			for(int j= Temp->q->Station_B;j< Temp->q->Station_E;j++)
			{
				if (j == Temp->q->Station_B) Tickets_Num = IA_OBJ.ChangedTrain[i]->info[j].Tickets;
				else if(IA_OBJ.ChangedTrain[i]->info[j].Tickets < Tickets_Num)
					Tickets_Num = IA_OBJ.ChangedTrain[i]->info[j].Tickets;
			}
			if(Temp->q->passengers.size() <= Tickets_Num) {
				Temp->q->WaitFlag = false; //修改账户中的对应候补订单的候补状态为“候补成功”
				IA_OBJ.AddOrder(Temp->q);	//根据候补订单添加乘车订单
				Temp_PRE->next = Temp->next;	//将该结点移出候补队列
				if (Temp == IA_OBJ.ChangedTrain[i]->AQ.rear) IA_OBJ.ChangedTrain[i]->AQ.rear = IA_OBJ.ChangedTrain[i]->AQ.front;	//删除队列最后一个元素的特殊处理
				delete Temp;	
				Temp = Temp_PRE->next;
			}
			else {
				Temp_PRE = Temp;
				Temp = Temp->next; //更新Temp，用于遍历下一个候补订单
			}

		}
	}

	/* 
	1.传入退票订单信息
	2.遍历被退票的列车的候补订单列表 找到第一个符合条件的候补订单 WaitListNode
	条件：①候补订单 所涉及的站点 是 退票所涉及站点 的子集
		  ②候补订单中的乘车人数量 小于 因退票而产生的车票
	3.根据 WaitListNode* q; 找到账户中的候补订单 并改变候补状态
	4.从列车候补订单中移除此候补订单
	*/
}