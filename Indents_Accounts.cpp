#include "Indents_Accounts.h"
#include "data.h"
#include "menu.h"
#include "tool.h"
#include <conio.h>

#define MAXPASSENGER 20	//����ÿ���˺������ӵĳ˳�����Ϣ����
int TotalOrderID = 1, TotalWaitID = 1;
//�������
AccountInfoNode* Indents_Accounts::LocateAccount(string A) {
	if (!AL->next) return nullptr;
	AccountInfoNode* p = AL->next;
	while (p && p->Account != A) {
		p = p->next;
	}
	return p;
}

//ע���˺�
void Indents_Accounts::Regist() {
	if (!AL) {
		//����ͷ���
		AL = new AccountInfoNode;
		AL->next = nullptr;
	}
	AccountInfoNode* User = new AccountInfoNode;
	string Account;

	while (true) {
		cout << "�������˺�:";
		cin >> Account;

		//�ж��˺ų����Ƿ�Ϸ�
		if (Account.size() < 7 || Account.size() > 11) {
			cout << "�˺ų���Ӧ�ò�����7λ�Ҳ�����11λ��" << endl;
			continue;
		}
		//�жϵ�ǰ�˺��Ƿ��Ѿ�����
		if (LocateAccount(Account)) {
			cout << "���˺��Ѿ�����!" << endl;
			continue;
		}

		User->Account = Account;	//д���˺�
		cout << "����������:";
		cin >> User->password;	//д������

		//������Ϣ����ͷ����ʼ��
		User->A_I = new IndentInfoNode;
		User->A_I->next = nullptr;
		User->A_I->Train = nullptr;
		User->A_I->passenger = nullptr;
		User->IndentInfo_Num = 0;

		//�򲹶�����Ϣ����ͷ����ʼ��
		User->A_W = new WaitListNode;
		User->A_W->next = nullptr;
		User->A_W->Owner = nullptr;
		User->Waitlist_Num = 0;

		//�˳�����Ϣ���Ա��ʼ��
		User->A_P = new PassengerInfoNode[MAXPASSENGER];
		User->PassengerInfo_Num = 0;

		//ǰ�巨����������
		User->next = AL->next;
		AL->next = User;

		cout << "ע��ɹ���"<<endl;
		_sleep(1*1000);
		
		return;//�˳�ѭ��
	}

}

//��Ӳ����˺�
void Indents_Accounts::Regist_AdM() {
	if (!AL) {
		//����ͷ���
		AL = new AccountInfoNode;
		AL->next = nullptr;
	}
	AccountInfoNode* User = new AccountInfoNode;
	User->Account = "yilijuan";	//д���˺�
	User->password = "yilijuan007";	//д������
	//������Ϣ����ͷ����ʼ��
	User->A_I = new IndentInfoNode;
	User->A_I->next = nullptr;
	User->IndentInfo_Num = 0;
	//�򲹶�����Ϣ����ͷ����ʼ��
	User->A_W = new WaitListNode;
	User->A_W->next = nullptr;
	User->A_W->Owner = nullptr;
	User->Waitlist_Num = 0;
	//�˳�����Ϣ���Ա��ʼ��
	User->A_P = new PassengerInfoNode[MAXPASSENGER];
	User->PassengerInfo_Num = 3;
	User->A_P[0].name = "����";
	User->A_P[0].gender = "��";
	User->A_P[0].IC = "123456789123456789";
	User->A_P[0].PhoneN = "12312312312";
	User->A_P[1].name = "����";
	User->A_P[1].gender = "Ů";
	User->A_P[1].IC = "123456789987654321";
	User->A_P[1].PhoneN = "12332112332";
	User->A_P[2].name = "������";
	User->A_P[2].gender = "Ů";
	User->A_P[2].IC = "123123456456123456";
	User->A_P[2].PhoneN = "15010150150";
	//ǰ�巨����������
	User->next = AL->next;
	AL->next = User;

	AccountInfoNode* User1 = new AccountInfoNode;
	User1->Account = "zhouyun";	//д���˺�
	User1->password = "zhouyun";	//д������
	//������Ϣ����ͷ����ʼ��
	User1->A_I = new IndentInfoNode;
	User1->A_I->next = nullptr;
	User1->IndentInfo_Num = 0;
	//�򲹶�����Ϣ����ͷ����ʼ��
	User1->A_W = new WaitListNode;
	User1->A_W->Owner = nullptr;
	User1->A_W->next = nullptr;
	User1->Waitlist_Num = 0;
	//�˳�����Ϣ���Ա��ʼ��
	User1->A_P = new PassengerInfoNode[MAXPASSENGER];
	User1->PassengerInfo_Num = 2;
	User1->A_P[0].name = "���¾���";
	User1->A_P[0].gender = "��";
	User1->A_P[0].IC = "441522200333333111";
	User1->A_P[0].PhoneN = "13617529920";
	User1->A_P[1].name = "��������";
	User1->A_P[1].gender = "Ů";
	User1->A_P[1].IC = "441886222222121002";
	User1->A_P[1].PhoneN = "12321212322";
	//ǰ�巨����������
	User1->next = AL->next;
	AL->next = User1;

	AccountInfoNode* User2 = new AccountInfoNode;
	User2->Account = "xudongkai";	//д���˺�
	User2->password = "xudongkai";	//д������
	//������Ϣ����ͷ����ʼ��
	User2->A_I = new IndentInfoNode;
	User2->A_I->next = nullptr;
	User2->IndentInfo_Num = 0;
	//�򲹶�����Ϣ����ͷ����ʼ��
	User2->A_W = new WaitListNode;
	User2->A_W->Owner = nullptr;
	User2->A_W->next = nullptr;
	User2->Waitlist_Num = 0;
	//�˳�����Ϣ���Ա��ʼ��
	User2->A_P = new PassengerInfoNode[MAXPASSENGER];
	User2->PassengerInfo_Num = 2;
	User2->A_P[0].name = "������";
	User2->A_P[0].gender = "��";
	User2->A_P[0].IC = "4415222003000000";
	User2->A_P[0].PhoneN = "1361752000";
	User2->A_P[1].name = "��槼�";
	User2->A_P[1].gender = "Ů";
	User2->A_P[1].IC = "12300622211122";
	User2->A_P[1].PhoneN = "12321212322";
	//ǰ�巨����������
	User2->next = AL->next;
	AL->next = User2;
}

// ��¼�˺�
bool Indents_Accounts::Login() {
	string Account, password;
	int attempts = 3;

	while (true) {
		cout << "�������˺�(����Q/q�˳�):";
		string Account;
		cin >> Account;
		if (Account == "Q" || Account == "q") {
			// �û���;�˳�
			return false;
		}
		// �����˺��Ƿ����
		AccountInfoNode* ptr = LocateAccount(Account);
		if (!ptr) {
			cout << "�˺Ų����ڣ���ע����������롣\n";
			_sleep(1 * 1000);
			continue;
		}
		while (true) {
			printf("����������(ʣ��%d�λ���,����C/c���������˺�)��", attempts);
			password = GetPasswordInput();
			if (password == "C" || password == "c") {
				break;
			}
			// ��������Ƿ�ƥ��
			if (ptr->password == password) {
				cout << "��¼�ɹ�!\n";
				CurrentA = ptr;
				_sleep(1 * 1000);
				return true;
			}
			else {
				attempts--;
				if (attempts == 0) {
					cout << "���Դ��������꣬��¼ʧ�ܡ�";
					_sleep(1 * 1000);
					return false;
				}
			}
		}

	}

}

//��ӳ˳�����Ϣ
void Indents_Accounts::AddPessenger() {
	if (CurrentA->PassengerInfo_Num == MAXPASSENGER)
	{
		cout << "�˳��������Ѵ�����(20)" << endl;
		_sleep(1 * 1000);
	}
	else
	{
		while (true) {
			system("cls");
			PassengerShow(-1);	//��ʾ��ǰ���г˳�����Ϣ
			PassengerInfoNode* Temp = CurrentA->A_P + CurrentA->PassengerInfo_Num;
			string name, gender, PhoneN, IC;
			cout << "������˳�������(����Q/q�˳�):";
			cin >> name;
			if (name == "Q" || name == "q")return;
			while (name.length() < 4 || name.length() > 10) {
				cout << "����ȷ����˳�������:";
				cin >> name;
			}
			cout << "������˳����Ա�:";
			cin >> gender;
			cout << "������˳��˵绰����:";
			cin >> PhoneN;
			while (PhoneN.length() != 11) {
				cout << "����ȷ����˳��˵绰����:";
				cin >> PhoneN;
			}
			cout << "������˳������֤��:";
			cin >> IC;
			while (IC.length() != 18) {
				cout << "����ȷ����˳������֤��:";
				cin >> IC;
			}
			Temp->name = name;
			Temp->gender = gender;
			Temp->PhoneN = PhoneN;
			Temp->IC = IC;
			CurrentA->PassengerInfo_Num++;
			cout << "��ӳɹ���" << endl;
			_sleep(1 * 1000);
		}
	}

}

//�޸ĳ˳�����Ϣ
void Indents_Accounts::ChangePessenger() {
	while (true) {
		int Order;
		system("cls");
		PassengerShow(-1);  //��ʾ��ǰ���г˳�����Ϣ
		cout << "������Ҫ�޸���Ϣ�ĳ˳��˵����(����0�˳�):";
		Order = ChooseInput();
		if (Order == 0) {
			break;
		}
		else if (Order > CurrentA->PassengerInfo_Num || Order < 0) {
			cout << "������������������:";
			_sleep(1 * 1000);
		}
		else {
			PassengerInfoNode* Temp = CurrentA->A_P + (Order - 1);
			bool Circle = true;  //ѭ����־
			while (Circle) {
				system("cls");
				PassengerShow(Order - 1);
				int choose;
				cout << "��ѡ��Ҫ�޸ĵ���Ŀ:1:���� 2:�Ա� 3:�绰���� 4:���֤��(����0������һ��) >>";
				choose=ChooseInput();
				switch (choose)
				{
				case 0:
					Circle = false;
					break;
				case 1: {
					string name;
					cout << "������˳�������:";
					cin >> name;
					if (name == "Q" || name == "q")return;
					while (name.length() < 2 || name.length() > 11) {
						cout << "����ȷ����˳�������:";
						cin >> name;
					}
					Temp->name = name;
				}
					  break;
				case 2: {
					cout << "������˳����Ա�:";
					cin >> Temp->gender;
				}
					  break;
				case 3: {
					string PhoneN;
					cout << "������˳��˵绰����:";
					cin >> PhoneN;
					while (PhoneN.length() != 11) {
						cout << "����ȷ����˳��˵绰����:";
						cin >> PhoneN;
					}
					Temp->PhoneN = PhoneN;
				}
					  break;
				case 4: {
					string IC;
					cout << "������˳������֤����:";
					cin >> IC;
					while (IC.length() != 18) {
						cout << "����ȷ����˳������֤��:";
						cin >> IC;
					}
					Temp->IC = IC;
				}
					  break;
				default:
					cout << "�����������������룡";
					_sleep(1 * 1000);
					break;
				}
			}
		}
	}

}

//ɾ���˳�����Ϣ
void Indents_Accounts::DeletePessenger() {
	if (CurrentA->PassengerInfo_Num == 0) {
		cout << "���ĳ˳�����ϢΪ��!";
		_sleep(1 * 1000);
	}
	else {
		while (true)
		{
			system("cls");
			PassengerShow(-1);
			int num;
			cout << "������Ҫɾ���ĳ˳������(����0�˳�)";
			cin >> num;
			if (num == 0) return;
			else {
				for (int i = num - 1;i < CurrentA->PassengerInfo_Num;i++) {
					CurrentA->A_P[i] = CurrentA->A_P[i + 1];
				}
				CurrentA->PassengerInfo_Num--;
			}
			cout << "ɾ���ɹ���";
			_sleep(1 * 1000);
		}
	}

}

//�жϳ˳����Ƿ��Ѿ�����ѡ�г�����
void Indents_Accounts::PassengerExist(string Selected_ID, const vector<int>& numbers_passenger, vector<int>& numbers_passenger_existed) {
	numbers_passenger_existed.clear();
	IndentInfoNode* p = CurrentA->A_I->next;
	if (p) {
		for (int i = 0;i < numbers_passenger.size();i++) {
			while (p) {
				if (p->Train->ID==Selected_ID&&(&(CurrentA->A_P[numbers_passenger[i]-1]) == p->passenger)) {
					numbers_passenger_existed.push_back(numbers_passenger[i]);
					break;
				}
				p = p->next;
			}
			p = CurrentA->A_I->next;
		}
	}

}

// ��Ӷ���
void Indents_Accounts::AddOrder(vector<int>& PassengerNumbers, vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ) {
	for (int i = 0;i < PassengerNumbers.size();i++) {
		IndentInfoNode* p = new IndentInfoNode;
		p->OrderID = TotalOrderID++;
		p->passenger = &(CurrentA->A_P[PassengerNumbers[i] - 1]);
		for (int j = 0;j < TC_OBJ.SL.length;j++) {
			if (TC_OBJ.SL.SRL[j].p->ID == Selected_ID) {
				p->Train = TC_OBJ.SL.SRL[j].p;
				p->Station_B = TC_OBJ.SL.SRL[j].Station_B;
				p->Station_E = TC_OBJ.SL.SRL[j].Station_E;
				p->Start_Time = TC_OBJ.SL.SRL[j].Start_Time;
				p->End_Time = TC_OBJ.SL.SRL[j].End_Time;
				break;
			}
		}
		p->Order_Tickets_Num = 1;
		int j = 0;
		for (;j < InsuranceNumbers.size();j++) {
			if (InsuranceNumbers[j] == PassengerNumbers[i]) {
				p->Insurance = "��";
				break;
			}
		}
		if (j >= InsuranceNumbers.size()) {
			p->Insurance = "��";
		}
		CurrentA->IndentInfo_Num++;
		//ǰ�巨��ӽ��
		p->next = CurrentA->A_I->next;
		CurrentA->A_I->next = p;
	}
}

// ��Ӷ��� �ع�����
void Indents_Accounts::AddOrder(WaitListNode* s) {
	for (int i = 0;i < s->passengers.size();i++) {
		IndentInfoNode* p = new IndentInfoNode;
		p->OrderID = TotalOrderID++;
		p->passenger = s->passengers[i];
		p->Train = s->Train;
		p->Station_B = s->Station_B;
		p->Station_E = s->Station_E;
		p->Start_Time = s->Start_Time;
		p->End_Time = s->End_Time;
		p->Order_Tickets_Num = 1;
		p->Insurance = s->Insurance[i];
		s->Owner->IndentInfo_Num++;
		//ǰ�巨��ӽ��
		p->next = s->Owner->A_I->next;
		s->Owner->A_I->next = p;
	}
	for (int i = s->Station_B;i <= s->Station_E;i++) {
		s->Train->info[i].Tickets -= s->passengers.size();
	}
}

//��Ӻ򲹶���
void Indents_Accounts::AddWaitOrder(const vector<int>& PassengerNumbers, const vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ) {
	WaitListNode* p = new WaitListNode;	//�����˻��򲹶������
	p->WaitID =TotalWaitID++;	//�򲹶����Ŵ���
	p->Wait_Tickets_Num = PassengerNumbers.size();	//Ʊ������
	p->Owner = CurrentA;	//�����߷���
	for (int i = 0;i < PassengerNumbers.size();i++) {
		p->passengers.push_back(&(CurrentA->A_P[PassengerNumbers[i] - 1]));	//�˿���Ϣд��
		int j = 0;

		//�������д��
		for (;j < InsuranceNumbers.size();j++) {
			if (InsuranceNumbers[j] == PassengerNumbers[i]) {
				p->Insurance.push_back("��");
				break;
			}
		}
		if (j >= InsuranceNumbers.size()) {
			p->Insurance.push_back("��");
		}
	}
	if (p->Insurance.size() != p->passengers.size()) {
		cout << "�򲹶����˳�����Ϣ�뱣�����������ƥ�䣡����"<<endl;
	}
	p->WaitFlag = true;	//��״������
	for (int j = 0;j < TC_OBJ.SL.length;j++) {
		if (TC_OBJ.SL.SRL[j].p->ID == Selected_ID) {
			p->Train = TC_OBJ.SL.SRL[j].p;
			p->Station_B = TC_OBJ.SL.SRL[j].Station_B;
			p->Station_E = TC_OBJ.SL.SRL[j].Station_E;
			p->Start_Time = TC_OBJ.SL.SRL[j].Start_Time;
			p->End_Time = TC_OBJ.SL.SRL[j].End_Time;

			//�г��򲹶������
			AlternateListNode* t = new AlternateListNode;
			t->q = p;
			t->next = NULL;
			TC_OBJ.SL.SRL[j].p->AQ.rear->next = t;	//��β���
			TC_OBJ.SL.SRL[j].p->AQ.rear = t;
			break;
		}
	}
	CurrentA->Waitlist_Num++;
	//ǰ�巨��ӽ��
	p->next = CurrentA->A_W->next;
	CurrentA->A_W->next = p;
}

//��ʾ����
void Indents_Accounts::Indents_Show(int OrderID) {
	Order_Info_Title();
	Order_Info_Line(CurrentA->A_I->next, OrderID);
}


//��ʾ�򲹶���
void Indents_Accounts::Indents_Wait_Show(int WaitID) {
	WaitOrder_Info_Title();
	WaitOrder_Info_Line(CurrentA->A_W->next, WaitID);
}

//��ʾ�򲹶���������ϸ��
void Indents_Accounts::Indents_Wait_Show_Detailed(int WaitID) {
	WaitOrder_Info_Line_Detailed(CurrentA->A_W->next, WaitID);
}

//ɾ������
void Indents_Accounts::DeleteOrder(TrainConsole& TC_OBJ) {
	ChangedTrain.clear();
	while (true) {
		if (CurrentA->IndentInfo_Num == 0) {
			cout << "�޶�������Ʊ��";
			_sleep(1 * 1000);
			return;
		}
		system("cls");
		Indents_Show(0);
		cout << "1:���ն�������Ʊ(һ����һƱ) 2:�����ֻ�����Ʊ(���˶�Ʊ) 3:�˳� >>";
		int choose;
		choose = ChooseInput();
		switch (choose)
		{
		case 1:
		{
			bool Circle1 = true;
			while (Circle1) {
				system("cls");
				Indents_Show(0);
				int Order;
				cout << "��������Ҫ��Ʊ�Ķ�����(����0�˳�)>>";
				Order = ChooseInput();
				if (Order == 0) {
					Circle1 = false;
					continue;
				}
				else if (Order<0) {
					cout << "�����������������룡";
					_sleep(1 * 1000);
					continue;
				}
				else {
					IndentInfoNode* p = CurrentA->A_I->next, * p_PRE= CurrentA->A_I;
					while (p && p->OrderID!=Order) {
						p_PRE = p;
						p = p->next;
					}
					if (p) {
						system("cls");
						Indents_Show(Order);
						string ConfirmDelect;
						while (ConfirmDelect!="��"&&ConfirmDelect!="��") {
							cout << "������������ʧ����������ȷ��Ҫɾ���ö�����?(�ǻ��) >>";
							cin >> ConfirmDelect;
						}
						if (ConfirmDelect == "��") {
							TC_OBJ.TrainInfoChange(p, 1, 1);	//�������������޸��г���Ϣ
							p_PRE->next = p->next;
							int i = 0;
							for (;i < ChangedTrain.size();i++) {
								if (ChangedTrain[i] == p->Train) break;
							}
							if (i >= ChangedTrain.size())	ChangedTrain.push_back(p->Train);
							delete p;
							CurrentA->IndentInfo_Num--;
						}
						else if (ConfirmDelect == "��") continue;
					}
					else {
						cout << "�����������������룡";
						_sleep(1 * 1000);
						continue;
					}

				}
			}
		}
		break;
		case 2:
		{
			bool Circle1 = true;
			while (Circle1) {
				string PhoneN;
				cout << "������˳��˵绰����(����0�˳�):";
				cin >> PhoneN;
				while (PhoneN.length() != 11&& PhoneN!="0") {
					cout << "����ȷ����˳��˵绰����(����0�˳�):";
					cin >> PhoneN;
				}
				if (PhoneN == "0") break;
				system("cls");
				IndentInfoNode* p = CurrentA->A_I->next;
				bool ExistOrder = false;
				Order_Info_Title();
				while (p) {
					if (p->passenger->PhoneN == PhoneN) {
						Order_Info_Line(CurrentA->A_I->next, p->OrderID);
						ExistOrder = true;
					}
					p = p->next;
				}
				if (!ExistOrder) {
					Order_Info_Line(CurrentA->A_I->next, -1);
					cout << "�������������";
					getch();
				}
				else {
					string ConfirmDelect;
					while (ConfirmDelect != "��" && ConfirmDelect != "��") {
						cout << "������������ʧ��������������ȷ��Ҫɾ����Щ������?(�ǻ��) >>";
						cin >> ConfirmDelect;
					}
					if (ConfirmDelect == "��") {
						p = CurrentA->A_I;
						while (p->next) {
							if (p->next->passenger->PhoneN == PhoneN) {
								IndentInfoNode* t = p->next;
								p->next = t->next;
								TC_OBJ.TrainInfoChange(t, 1, 1);
								int i = 0;
								for (;i < ChangedTrain.size();i++) {
									if (ChangedTrain[i] == t->Train) break;
								}
								if(i>= ChangedTrain.size())	ChangedTrain.push_back(t->Train);
								delete t;
								CurrentA->IndentInfo_Num--;
							}
							else {
								p = p->next;
							}

						}
						Circle1 = false;
					}
					else if (ConfirmDelect == "��") {
						Circle1 = false;
					}
				}
			}
		}
		break;
		case 3: {// �˳�
			return;
		}
		break;
		default:
		{
			cout << "�����������������룡";
			_sleep(1 * 1000);
		}
			break;
		}

	}
}

//�޸�����
void Indents_Accounts::Change_Password() {

	string Old_Password, New_Password;
	while (1) {
		cout << "������ԭ���루����Q/q�˳���:";
		Old_Password = GetPasswordInput();
		if (Old_Password == "q" || Old_Password == "Q") {
			return;
		}
		if (Old_Password == CurrentA->password) {
			cout << "�����������루����Q/q�˳���:";
			New_Password = GetPasswordInput();
			if (New_Password == "q" || New_Password == "Q") {
				return;
			}
			else {
				CurrentA->password = New_Password;
				cout << "�޸ĳɹ�" << endl;
				_sleep(2 * 1000);
				return;
			}
		}
		system("cls");
		Main_Menu();
	}


}

//��ʾ���г˳�����Ϣ offser->-1:��ʾ���г˳�����Ϣ 0...n:��ʾ�ض��˳�����Ϣ
void Indents_Accounts::PassengerShow(int offset)
{
	system("cls");
	Passenger_Info_Title();
	if (CurrentA->PassengerInfo_Num == 0) {
		cout << "                             �˳�����ϢΪ�գ�                                  "<< endl;
	}
	else Passenger_Info_Line(CurrentA, offset);
}

int Indents_Accounts::GetPassengerNum() {
	return CurrentA->PassengerInfo_Num;
}