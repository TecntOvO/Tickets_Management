#include "Indents_Accounts.h"
#include "data.h"
#include "menu.h"
#include "tool.h"
#include <conio.h>

#define MAXPASSENGER 20	//限制每个账号最多添加的乘车人信息个数
int TotalOrderID = 1, TotalWaitID = 1;
//链表查找
AccountInfoNode* Indents_Accounts::LocateAccount(string A) {
	if (!AL->next) return nullptr;
	AccountInfoNode* p = AL->next;
	while (p && p->Account != A) {
		p = p->next;
	}
	return p;
}

//注册账号
void Indents_Accounts::Regist() {
	if (!AL) {
		//创建头结点
		AL = new AccountInfoNode;
		AL->next = nullptr;
	}
	AccountInfoNode* User = new AccountInfoNode;
	string Account;

	while (true) {
		cout << "请输入账号:";
		cin >> Account;

		//判断账号长度是否合法
		if (Account.size() < 7 || Account.size() > 11) {
			cout << "账号长度应该不少于7位且不超过11位！" << endl;
			continue;
		}
		//判断当前账号是否已经存在
		if (LocateAccount(Account)) {
			cout << "该账号已经存在!" << endl;
			continue;
		}

		User->Account = Account;	//写入账号
		cout << "请输入密码:";
		cin >> User->password;	//写入密码

		//订单信息链表头结点初始化
		User->A_I = new IndentInfoNode;
		User->A_I->next = nullptr;
		User->A_I->Train = nullptr;
		User->A_I->passenger = nullptr;
		User->IndentInfo_Num = 0;

		//候补订单信息链表头结点初始化
		User->A_W = new WaitListNode;
		User->A_W->next = nullptr;
		User->A_W->Owner = nullptr;
		User->Waitlist_Num = 0;

		//乘车人信息线性表初始化
		User->A_P = new PassengerInfoNode[MAXPASSENGER];
		User->PassengerInfo_Num = 0;

		//前插法创建单链表
		User->next = AL->next;
		AL->next = User;

		cout << "注册成功！"<<endl;
		_sleep(1*1000);
		
		return;//退出循环
	}

}

//添加测试账号
void Indents_Accounts::Regist_AdM() {
	if (!AL) {
		//创建头结点
		AL = new AccountInfoNode;
		AL->next = nullptr;
	}
	AccountInfoNode* User = new AccountInfoNode;
	User->Account = "yilijuan";	//写入账号
	User->password = "yilijuan007";	//写入密码
	//订单信息链表头结点初始化
	User->A_I = new IndentInfoNode;
	User->A_I->next = nullptr;
	User->IndentInfo_Num = 0;
	//候补订单信息链表头结点初始化
	User->A_W = new WaitListNode;
	User->A_W->next = nullptr;
	User->A_W->Owner = nullptr;
	User->Waitlist_Num = 0;
	//乘车人信息线性表初始化
	User->A_P = new PassengerInfoNode[MAXPASSENGER];
	User->PassengerInfo_Num = 3;
	User->A_P[0].name = "许栋凯";
	User->A_P[0].gender = "男";
	User->A_P[0].IC = "123456789123456789";
	User->A_P[0].PhoneN = "12312312312";
	User->A_P[1].name = "周昀";
	User->A_P[1].gender = "女";
	User->A_P[1].IC = "123456789987654321";
	User->A_P[1].PhoneN = "12332112332";
	User->A_P[2].name = "易丽娟";
	User->A_P[2].gender = "女";
	User->A_P[2].IC = "123123456456123456";
	User->A_P[2].PhoneN = "15010150150";
	//前插法创建单链表
	User->next = AL->next;
	AL->next = User;

	AccountInfoNode* User1 = new AccountInfoNode;
	User1->Account = "zhouyun";	//写入账号
	User1->password = "zhouyun";	//写入密码
	//订单信息链表头结点初始化
	User1->A_I = new IndentInfoNode;
	User1->A_I->next = nullptr;
	User1->IndentInfo_Num = 0;
	//候补订单信息链表头结点初始化
	User1->A_W = new WaitListNode;
	User1->A_W->Owner = nullptr;
	User1->A_W->next = nullptr;
	User1->Waitlist_Num = 0;
	//乘车人信息线性表初始化
	User1->A_P = new PassengerInfoNode[MAXPASSENGER];
	User1->PassengerInfo_Num = 2;
	User1->A_P[0].name = "爱新觉罗";
	User1->A_P[0].gender = "男";
	User1->A_P[0].IC = "441522200333333111";
	User1->A_P[0].PhoneN = "13617529920";
	User1->A_P[1].name = "乌拉那拉";
	User1->A_P[1].gender = "女";
	User1->A_P[1].IC = "441886222222121002";
	User1->A_P[1].PhoneN = "12321212322";
	//前插法创建单链表
	User1->next = AL->next;
	AL->next = User1;

	AccountInfoNode* User2 = new AccountInfoNode;
	User2->Account = "xudongkai";	//写入账号
	User2->password = "xudongkai";	//写入密码
	//订单信息链表头结点初始化
	User2->A_I = new IndentInfoNode;
	User2->A_I->next = nullptr;
	User2->IndentInfo_Num = 0;
	//候补订单信息链表头结点初始化
	User2->A_W = new WaitListNode;
	User2->A_W->Owner = nullptr;
	User2->A_W->next = nullptr;
	User2->Waitlist_Num = 0;
	//乘车人信息线性表初始化
	User2->A_P = new PassengerInfoNode[MAXPASSENGER];
	User2->PassengerInfo_Num = 2;
	User2->A_P[0].name = "姜子牙";
	User2->A_P[0].gender = "男";
	User2->A_P[0].IC = "4415222003000000";
	User2->A_P[0].PhoneN = "1361752000";
	User2->A_P[1].name = "苏妲己";
	User2->A_P[1].gender = "女";
	User2->A_P[1].IC = "12300622211122";
	User2->A_P[1].PhoneN = "12321212322";
	//前插法创建单链表
	User2->next = AL->next;
	AL->next = User2;
}

// 登录账号
bool Indents_Accounts::Login() {
	string Account, password;
	int attempts = 3;

	while (true) {
		cout << "请输入账号(输入Q/q退出):";
		string Account;
		cin >> Account;
		if (Account == "Q" || Account == "q") {
			// 用户中途退出
			return false;
		}
		// 查找账号是否存在
		AccountInfoNode* ptr = LocateAccount(Account);
		if (!ptr) {
			cout << "账号不存在，请注册或重新输入。\n";
			_sleep(1 * 1000);
			continue;
		}
		while (true) {
			printf("请输入密码(剩余%d次机会,输入C/c重新输入账号)：", attempts);
			password = GetPasswordInput();
			if (password == "C" || password == "c") {
				break;
			}
			// 检查密码是否匹配
			if (ptr->password == password) {
				cout << "登录成功!\n";
				CurrentA = ptr;
				_sleep(1 * 1000);
				return true;
			}
			else {
				attempts--;
				if (attempts == 0) {
					cout << "尝试次数已用完，登录失败。";
					_sleep(1 * 1000);
					return false;
				}
			}
		}

	}

}

//添加乘车人信息
void Indents_Accounts::AddPessenger() {
	if (CurrentA->PassengerInfo_Num == MAXPASSENGER)
	{
		cout << "乘车人数量已达上限(20)" << endl;
		_sleep(1 * 1000);
	}
	else
	{
		while (true) {
			system("cls");
			PassengerShow(-1);	//显示当前所有乘车人信息
			PassengerInfoNode* Temp = CurrentA->A_P + CurrentA->PassengerInfo_Num;
			string name, gender, PhoneN, IC;
			cout << "请输入乘车人姓名(输入Q/q退出):";
			cin >> name;
			if (name == "Q" || name == "q")return;
			while (name.length() < 4 || name.length() > 10) {
				cout << "请正确输入乘车人姓名:";
				cin >> name;
			}
			cout << "请输入乘车人性别:";
			cin >> gender;
			cout << "请输入乘车人电话号码:";
			cin >> PhoneN;
			while (PhoneN.length() != 11) {
				cout << "请正确输入乘车人电话号码:";
				cin >> PhoneN;
			}
			cout << "请输入乘车人身份证号:";
			cin >> IC;
			while (IC.length() != 18) {
				cout << "请正确输入乘车人身份证号:";
				cin >> IC;
			}
			Temp->name = name;
			Temp->gender = gender;
			Temp->PhoneN = PhoneN;
			Temp->IC = IC;
			CurrentA->PassengerInfo_Num++;
			cout << "添加成功！" << endl;
			_sleep(1 * 1000);
		}
	}

}

//修改乘车人信息
void Indents_Accounts::ChangePessenger() {
	while (true) {
		int Order;
		system("cls");
		PassengerShow(-1);  //显示当前所有乘车人信息
		cout << "请输入要修改信息的乘车人的序号(输入0退出):";
		Order = ChooseInput();
		if (Order == 0) {
			break;
		}
		else if (Order > CurrentA->PassengerInfo_Num || Order < 0) {
			cout << "输入有误，请重新输入:";
			_sleep(1 * 1000);
		}
		else {
			PassengerInfoNode* Temp = CurrentA->A_P + (Order - 1);
			bool Circle = true;  //循环标志
			while (Circle) {
				system("cls");
				PassengerShow(Order - 1);
				int choose;
				cout << "请选择要修改的项目:1:姓名 2:性别 3:电话号码 4:身份证号(输入0返回上一级) >>";
				choose=ChooseInput();
				switch (choose)
				{
				case 0:
					Circle = false;
					break;
				case 1: {
					string name;
					cout << "请输入乘车人姓名:";
					cin >> name;
					if (name == "Q" || name == "q")return;
					while (name.length() < 2 || name.length() > 11) {
						cout << "请正确输入乘车人姓名:";
						cin >> name;
					}
					Temp->name = name;
				}
					  break;
				case 2: {
					cout << "请输入乘车人性别:";
					cin >> Temp->gender;
				}
					  break;
				case 3: {
					string PhoneN;
					cout << "请输入乘车人电话号码:";
					cin >> PhoneN;
					while (PhoneN.length() != 11) {
						cout << "请正确输入乘车人电话号码:";
						cin >> PhoneN;
					}
					Temp->PhoneN = PhoneN;
				}
					  break;
				case 4: {
					string IC;
					cout << "请输入乘车人身份证号码:";
					cin >> IC;
					while (IC.length() != 18) {
						cout << "请正确输入乘车人身份证号:";
						cin >> IC;
					}
					Temp->IC = IC;
				}
					  break;
				default:
					cout << "输入有误，请重新输入！";
					_sleep(1 * 1000);
					break;
				}
			}
		}
	}

}

//删除乘车人信息
void Indents_Accounts::DeletePessenger() {
	if (CurrentA->PassengerInfo_Num == 0) {
		cout << "您的乘车人信息为空!";
		_sleep(1 * 1000);
	}
	else {
		while (true)
		{
			system("cls");
			PassengerShow(-1);
			int num;
			cout << "请输入要删除的乘车人序号(输入0退出)";
			cin >> num;
			if (num == 0) return;
			else {
				for (int i = num - 1;i < CurrentA->PassengerInfo_Num;i++) {
					CurrentA->A_P[i] = CurrentA->A_P[i + 1];
				}
				CurrentA->PassengerInfo_Num--;
			}
			cout << "删除成功！";
			_sleep(1 * 1000);
		}
	}

}

//判断乘车人是否已经在所选列车中了
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

// 添加订单
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
				p->Insurance = "是";
				break;
			}
		}
		if (j >= InsuranceNumbers.size()) {
			p->Insurance = "否";
		}
		CurrentA->IndentInfo_Num++;
		//前插法添加结点
		p->next = CurrentA->A_I->next;
		CurrentA->A_I->next = p;
	}
}

// 添加订单 重构函数
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
		//前插法添加结点
		p->next = s->Owner->A_I->next;
		s->Owner->A_I->next = p;
	}
	for (int i = s->Station_B;i <= s->Station_E;i++) {
		s->Train->info[i].Tickets -= s->passengers.size();
	}
}

//添加候补订单
void Indents_Accounts::AddWaitOrder(const vector<int>& PassengerNumbers, const vector<int>& InsuranceNumbers, string Selected_ID, TrainConsole& TC_OBJ) {
	WaitListNode* p = new WaitListNode;	//分配账户候补订单结点
	p->WaitID =TotalWaitID++;	//候补订单号处理
	p->Wait_Tickets_Num = PassengerNumbers.size();	//票数分配
	p->Owner = CurrentA;	//所有者分配
	for (int i = 0;i < PassengerNumbers.size();i++) {
		p->passengers.push_back(&(CurrentA->A_P[PassengerNumbers[i] - 1]));	//乘客信息写入
		int j = 0;

		//保险情况写入
		for (;j < InsuranceNumbers.size();j++) {
			if (InsuranceNumbers[j] == PassengerNumbers[i]) {
				p->Insurance.push_back("是");
				break;
			}
		}
		if (j >= InsuranceNumbers.size()) {
			p->Insurance.push_back("否");
		}
	}
	if (p->Insurance.size() != p->passengers.size()) {
		cout << "候补订单乘车人信息与保险情况数量不匹配！！！"<<endl;
	}
	p->WaitFlag = true;	//候补状况设置
	for (int j = 0;j < TC_OBJ.SL.length;j++) {
		if (TC_OBJ.SL.SRL[j].p->ID == Selected_ID) {
			p->Train = TC_OBJ.SL.SRL[j].p;
			p->Station_B = TC_OBJ.SL.SRL[j].Station_B;
			p->Station_E = TC_OBJ.SL.SRL[j].Station_E;
			p->Start_Time = TC_OBJ.SL.SRL[j].Start_Time;
			p->End_Time = TC_OBJ.SL.SRL[j].End_Time;

			//列车候补队列入队
			AlternateListNode* t = new AlternateListNode;
			t->q = p;
			t->next = NULL;
			TC_OBJ.SL.SRL[j].p->AQ.rear->next = t;	//队尾入队
			TC_OBJ.SL.SRL[j].p->AQ.rear = t;
			break;
		}
	}
	CurrentA->Waitlist_Num++;
	//前插法添加结点
	p->next = CurrentA->A_W->next;
	CurrentA->A_W->next = p;
}

//显示订单
void Indents_Accounts::Indents_Show(int OrderID) {
	Order_Info_Title();
	Order_Info_Line(CurrentA->A_I->next, OrderID);
}


//显示候补订单
void Indents_Accounts::Indents_Wait_Show(int WaitID) {
	WaitOrder_Info_Title();
	WaitOrder_Info_Line(CurrentA->A_W->next, WaitID);
}

//显示候补订单——详细版
void Indents_Accounts::Indents_Wait_Show_Detailed(int WaitID) {
	WaitOrder_Info_Line_Detailed(CurrentA->A_W->next, WaitID);
}

//删除订单
void Indents_Accounts::DeleteOrder(TrainConsole& TC_OBJ) {
	ChangedTrain.clear();
	while (true) {
		if (CurrentA->IndentInfo_Num == 0) {
			cout << "无订单可退票！";
			_sleep(1 * 1000);
			return;
		}
		system("cls");
		Indents_Show(0);
		cout << "1:按照订单号退票(一次退一票) 2:按照手机号退票(可退多票) 3:退出 >>";
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
				cout << "请输入你要退票的订单号(输入0退出)>>";
				Order = ChooseInput();
				if (Order == 0) {
					Circle1 = false;
					continue;
				}
				else if (Order<0) {
					cout << "输入有误，请重新输入！";
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
						while (ConfirmDelect!="是"&&ConfirmDelect!="否") {
							cout << "您即将被纳入失信名单，您确认要删除该订单吗?(是或否) >>";
							cin >> ConfirmDelect;
						}
						if (ConfirmDelect == "是") {
							TC_OBJ.TrainInfoChange(p, 1, 1);	//根据所给订单修改列车信息
							p_PRE->next = p->next;
							int i = 0;
							for (;i < ChangedTrain.size();i++) {
								if (ChangedTrain[i] == p->Train) break;
							}
							if (i >= ChangedTrain.size())	ChangedTrain.push_back(p->Train);
							delete p;
							CurrentA->IndentInfo_Num--;
						}
						else if (ConfirmDelect == "否") continue;
					}
					else {
						cout << "输入有误，请重新输入！";
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
				cout << "请输入乘车人电话号码(输入0退出):";
				cin >> PhoneN;
				while (PhoneN.length() != 11&& PhoneN!="0") {
					cout << "请正确输入乘车人电话号码(输入0退出):";
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
					cout << "按下任意键继续";
					getch();
				}
				else {
					string ConfirmDelect;
					while (ConfirmDelect != "是" && ConfirmDelect != "否") {
						cout << "您即将被纳入失信名单，请问您确认要删除这些订单吗?(是或否) >>";
						cin >> ConfirmDelect;
					}
					if (ConfirmDelect == "是") {
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
					else if (ConfirmDelect == "否") {
						Circle1 = false;
					}
				}
			}
		}
		break;
		case 3: {// 退出
			return;
		}
		break;
		default:
		{
			cout << "输入有误，请重新输入！";
			_sleep(1 * 1000);
		}
			break;
		}

	}
}

//修改密码
void Indents_Accounts::Change_Password() {

	string Old_Password, New_Password;
	while (1) {
		cout << "请输入原密码（输入Q/q退出）:";
		Old_Password = GetPasswordInput();
		if (Old_Password == "q" || Old_Password == "Q") {
			return;
		}
		if (Old_Password == CurrentA->password) {
			cout << "请输入新密码（输入Q/q退出）:";
			New_Password = GetPasswordInput();
			if (New_Password == "q" || New_Password == "Q") {
				return;
			}
			else {
				CurrentA->password = New_Password;
				cout << "修改成功" << endl;
				_sleep(2 * 1000);
				return;
			}
		}
		system("cls");
		Main_Menu();
	}


}

//显示所有乘车人信息 offser->-1:显示所有乘车人信息 0...n:显示特定乘车人信息
void Indents_Accounts::PassengerShow(int offset)
{
	system("cls");
	Passenger_Info_Title();
	if (CurrentA->PassengerInfo_Num == 0) {
		cout << "                             乘车人信息为空！                                  "<< endl;
	}
	else Passenger_Info_Line(CurrentA, offset);
}

int Indents_Accounts::GetPassengerNum() {
	return CurrentA->PassengerInfo_Num;
}