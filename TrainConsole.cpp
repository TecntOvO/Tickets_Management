#include <fstream>
#include <vector>
#include "TrainConsole.h"
#include "Indents_Accounts.h"
#include "data.h"
#include "tool.h"
#include "menu.h"

#define BYBEGINTIME 0	//���ճ���ʱ������
#define BYTICKETS 1	//����ʣ�೵Ʊ������
#define BYTIME 2	//���ճ���ʱ������
#define BYREACHTIME 3	//���յִ�ʱ������
#define DECENDING 0 //����
#define ASCENDING 1	//����

//��ʼ���г���Ϣ
void TrainConsole::LoadTrainInfo() {
	int Train_COUNT = 0;	//��¼�г��������ڴ�������������������Ա�
	//����ͷ���
	TL = new TrainNode;
	TL->next = nullptr;
	TL->info = nullptr;
	//��ȡcsv�ļ�����ʼ����������
	ifstream File("TrainInfo.csv", ios::in);
	string LineS;
	//getline(File, LineS);	//������һ��

	//ѭ�������������д����Ϣ
	while (1) {
		getline(File, LineS);
		if (LineS == "") break;
		Train_COUNT++;
		vector<string> LineV;
		Split(LineS, LineV, ',');
		TrainNode* s = new TrainNode;
		s->ID = LineV[0];	//д���г���
		s->Passengers_Capacity = stoi(LineV[1]);	//д��˿�����
		s->Begin_Time = stoi(LineV[2]);	//д�뷢��ʱ��
		s->Station_Num = LineV.size() - 3;	//д��վ������
		s->info = new StationNode[LineV.size() - 3];	//����վ�����Ա�

		for (int i = 3;i < LineV.size();i++) {
			vector<string> StationV;
			Split(LineV[i], StationV, '-');
			s->info[i - 3].Station_Name = StationV[0];	//д��վ������
			s->info[i - 3].Tickets = s->Passengers_Capacity;	//д��վ��Ʊ��ֵ/����
			s->info[i - 3].STIme_Offset = stoi(StationV[1]);	//д��վ�㷢��ʱ�������ʼ��վ����ʱ��Ĳ�ֵ
		}
		// ��ʼ���г��ĺ򲹶���
		s->AQ.front = s->AQ.rear = new AlternateListNode;
		s->AQ.front->q = NULL;
		s->AQ.front->next = nullptr;

		//ǰ�巨���ӽ��
		s->next = TL->next;
		TL->next = s;
	}
	SL.SRL = new SearchResultNode[Train_COUNT];	//��ʼ��������������Ա�
	SL.length = 0;
}

//���������������г�	Station_B->����վ���� Station_E->�յ�վ����
int TrainConsole::TrainSearch(const string& Station_B, const string& Station_E) {
	SL.length = 0;	//����ա�������������Ա�
	TrainNode* p = TL->next;
	//���������г���Ϣ����
	while (p) {
		for (int i = 0;i < p->Station_Num - 1;i++) {
			if (p->info[i].Station_Name == Station_B) {
				for (int j = i + 1;j < p->Station_Num;j++) {	//�յ�վһ���ڳ���վ֮�󣬹�j=i+1
					if (p->info[j].Station_Name == Station_E) {
						SL.SRL[SL.length].p = p;	//������������г���ָ��
						SL.SRL[SL.length].Station_B = i;	//�������վ�ڸ��г�վ�����Ա��е��±�
						SL.SRL[SL.length].Station_E = j;	//�����յ�վ�ڸ��г�վ�����Ա��е��±�
						SL.SRL[SL.length].Start_Time = p->Begin_Time + p->info[i].STIme_Offset;	//�������վ����ʱ��
						SL.SRL[SL.length].End_Time = p->Begin_Time + p->info[j].STIme_Offset;	//�����յ�վ�ִ�ʱ��
						//����ʣ��Ʊ��
						int Remaining_Tickets;
						for (int a = i;a < j;a++) {	//���ܰ����յ�վ����λ��������С�ڶ���С�ڵ���
							if (a == i) Remaining_Tickets = p->info[a].Tickets;
							else {
								if (p->info[a].Tickets < Remaining_Tickets) {
									Remaining_Tickets = p->info[a].Tickets;
								}
							}
						}
						SL.SRL[SL.length].Remaining_Tickets = Remaining_Tickets;	//������г��ӳ���վ���յ�վ��ʣ��Ʊ��
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

//��ʾ��� Condition->�������� Order->����˳��
void TrainConsole::ResultShow(int Condition, int Order) {
	system("cls");
	Train_Info_Title();
	SearchList Temp = SL.SRL;	
	if (SL.length == 0) {
		cout << "                                404:δ�ҵ����                                          \n\n";
		return;
	}
	//���ճ���ʱ������
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

	//����ʣ��Ʊ������
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

	//���ճ���ʱ������
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

	//���յִ�ʱ������
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

	//����
	if (Order == DECENDING) {
		for (int i = 0;i < SL.length;i++) {
			Train_Info_Line(Temp[i]);
		}
	}

	//����
	else if (Order == ASCENDING) {
		for (int i = SL.length - 1;i >= 0;i--) {
			Train_Info_Line(Temp[i]);
		}
	}
}

//�ж���ѡ�г��ŵ��г��Ƿ�����Լ��Ƿ���Ʊ
int TrainConsole::Tickets_Selected_ID(string Selected_ID)
{
	int i = 0;
	SearchList Temp = SL.SRL;
	while (i < SL.length && Selected_ID != SL.SRL[i].p->ID) i++; //���ж� i < SL.length

	// �ж�������г����Ƿ�Ϸ�(�Ƿ��ڸ����ķ�Χ��)
	if (i >= SL.length)
	{
		return -1;
	}
	// ������ѡ�г�վ���Ʊ��
	else
	{
		return Temp[i].Remaining_Tickets;
	}
}

//�޸��г���Ϣ ID->�г��� Operation->1����/0���ٳ�Ʊ Tickers_Num->Ҫ��ȥ��Ʊ��
void TrainConsole::TrainInfoChange(const string& ID,const string& Station_B, const string& Station_E, int Operation, int Tickets_Num) {
	TrainNode* p = TL->next;	//����pָ���һ���г����;
	while (p && p->ID != ID)p = p->next;	//�ҵ�IDΪ����ID���г���ָ��
	if (p) {
		int i = 0,j;
		//�ҵ���Ӧվ����±�
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

		//�޸�Ʊ��
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

//�޸��г���Ϣ p->ָ�򶩵���ָ�� Operation->1����/0���ٳ�Ʊ Tickers_Num->Ҫ��ȥ��Ʊ��
void TrainConsole::TrainInfoChange(IndentInfoNode* p,int Operation, int Tickets_Num) {
	if (p) {
		//�޸�Ʊ��
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

//�򲹷���
void TrainConsole::AssignWaitTicket(Indents_Accounts& IA_OBJ) {
	for(int i=0;i<IA_OBJ.ChangedTrain.size();i++)  //��i������Ʊ���г�
	{
		AlternateListNode* Temp = IA_OBJ.ChangedTrain[i]->AQ.front->next,*Temp_PRE= IA_OBJ.ChangedTrain[i]->AQ.front;
		int Tickets_Num; //��Ӧ�м�վ��ʣ�����Ʊ��

		while(Temp) //�����г��ĺ򲹶����б�
		{
			// ���ݺ򲹶�����վ�� �����г�վ�� �ҵ� Tickets_Num Ȼ����˳����������бȽ�
			for(int j= Temp->q->Station_B;j< Temp->q->Station_E;j++)
			{
				if (j == Temp->q->Station_B) Tickets_Num = IA_OBJ.ChangedTrain[i]->info[j].Tickets;
				else if(IA_OBJ.ChangedTrain[i]->info[j].Tickets < Tickets_Num)
					Tickets_Num = IA_OBJ.ChangedTrain[i]->info[j].Tickets;
			}
			if(Temp->q->passengers.size() <= Tickets_Num) {
				Temp->q->WaitFlag = false; //�޸��˻��еĶ�Ӧ�򲹶����ĺ�״̬Ϊ���򲹳ɹ���
				IA_OBJ.AddOrder(Temp->q);	//���ݺ򲹶�����ӳ˳�����
				Temp_PRE->next = Temp->next;	//���ý���Ƴ��򲹶���
				if (Temp == IA_OBJ.ChangedTrain[i]->AQ.rear) IA_OBJ.ChangedTrain[i]->AQ.rear = IA_OBJ.ChangedTrain[i]->AQ.front;	//ɾ���������һ��Ԫ�ص����⴦��
				delete Temp;	
				Temp = Temp_PRE->next;
			}
			else {
				Temp_PRE = Temp;
				Temp = Temp->next; //����Temp�����ڱ�����һ���򲹶���
			}

		}
	}

	/* 
	1.������Ʊ������Ϣ
	2.��������Ʊ���г��ĺ򲹶����б� �ҵ���һ�����������ĺ򲹶��� WaitListNode
	�������ٺ򲹶��� ���漰��վ�� �� ��Ʊ���漰վ�� ���Ӽ�
		  �ں򲹶����еĳ˳������� С�� ����Ʊ�������ĳ�Ʊ
	3.���� WaitListNode* q; �ҵ��˻��еĺ򲹶��� ���ı��״̬
	4.���г��򲹶������Ƴ��˺򲹶���
	*/
}