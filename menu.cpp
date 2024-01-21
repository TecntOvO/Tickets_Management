#include "menu.h"
#include "data.h"
#include "tool.h"

#include <iomanip>

//启动菜单
void Start_Menu() {
	cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "*                 欢迎使用12306             *" << endl;
	cout << "*                  1:注册                   *" << endl;
	cout << "*                  2:登录                   *" << endl;
	cout << "*                  3:退出                   *" << endl;
	cout << "* * * * * * * * * * * * * * * * * * * * * * *" << endl;
}

//主菜单
void Main_Menu() {
	cout << "* * * * * * * * * * * * * * * * * * * * * * * *" << endl;
	cout << "*                 主菜单                      *" << endl;
	cout << "*                1:购买车票                   *" << endl;
	cout << "*                2:乘车人管理                 *" << endl;
	cout << "*                3:订单管理                   *" << endl;
	cout << "*                4:修改密码                   *" << endl;
	cout << "*                5.登出                       *" << endl;
	cout << "* * * * * * * * * * * * * * * * * * * * * * * *" << endl;
}

//列车信息表头
void Train_Info_Title() {
	printf("----------------------------------------------------------------------------------------\n");
	printCentered("列车号", 10);
	printCentered("乘客定额", 10);
	printCentered("出发站", 10);
	printCentered("终点站", 10);
	printCentered("出发时间", 10);
	printCentered("抵达时间", 10);
	printCentered("乘车时长", 10);
	printCentered("剩余票数", 10);
	printf("\n");
	printf("----------------------------------------------------------------------------------------\n");
}

//列车信息表项
void Train_Info_Line(SearchResultNode Result) {
	string Station_B = Result.p->info[Result.Station_B].Station_Name;
	string Station_E = Result.p->info[Result.Station_E].Station_Name;
	printCentered(Result.p->ID, 10);
	printCentered(TranslateIntToChar(Result.p->Passengers_Capacity), 10);
	printCentered(Station_B, 10);
	printCentered(Station_E, 10);
	printCentered(TranslateTimeToChar(Result.Start_Time), 10);
	printCentered(TranslateTimeToChar(Result.End_Time), 10);
	printCentered(TranslateTimeToChar(Result.End_Time - Result.Start_Time), 10);
	printCentered(TranslateIntToChar(Result.Remaining_Tickets), 10);
	printf("\n");
	printf("----------------------------------------------------------------------------------------\n");
}

//乘车人信息表头
void Passenger_Info_Title() {
	printf("--------------------------------------------------------------\n");
	printCentered("序号", 8);
	printCentered("姓名", 10);
	printCentered("性别", 6);
	printCentered("电话号码", 13);
	printCentered("身份证号", 20);
	printf("\n");
	printf("--------------------------------------------------------------\n");
}


//乘车人信息表项
void Passenger_Info_Line(AccountInfoNode* A,int offset) {
	if (offset == -1) {
		int i = 0;
		while (i<A->PassengerInfo_Num)
		{
			printCentered(TranslateIntToChar(i+1), 8);
			printCentered(A->A_P[i].name, 10);
			printCentered(A->A_P[i].gender, 6);
			printCentered(A->A_P[i].PhoneN, 13);
			printCentered(A->A_P[i].IC, 20);
			printf("\n");
			printf("--------------------------------------------------------------\n");
			i++;
		}
	}
	else {
		printCentered(TranslateIntToChar(offset + 1), 8);
		printCentered(A->A_P[offset].name, 10);
		printCentered(A->A_P[offset].gender, 6);
		printCentered(A->A_P[offset].PhoneN, 13);
		printCentered(A->A_P[offset].IC, 20);
		printf("\n");
		printf("--------------------------------------------------------------\n");
	}
}

//订单信息表头
void Order_Info_Title(){

	printCentered("订单号", 8);
	printCentered("乘客姓名", 10);
	printCentered("保险情况", 10);
	printCentered("订购票数", 10);
	printCentered("列车号", 10);
	printCentered("出发站", 10);
	printCentered("终点站", 10);
	printCentered("出发时间", 10);
	printCentered("抵达时间", 10);
	printf("\n");
	printf("-------------------------------------------------------------------------------------------------\n");
	/*
	cout  << setw(8) << "订单号" << setw(3) << '|' << setw(8) << "乘客姓名" << setw(3) << '|' << setw(8) << "保险情况"
	<< setw(3) << '|' << setw(8) << "订购票数" << setw(3) << '|' << setw(8) << "列车号" << setw(3) << '|' << setw(8) 
	<< "出发站" << setw(3) << '|' << setw(8) << "终点站" << setw(3) << '|' << setw(8) << "出发时间" << setw(3) << '|' 
	<< setw(8) << "抵达时间"  << endl;
	*/

	
}

//订单信息表项 i->0 显示全部订单 1....n 对应订单号订单
void Order_Info_Line(IndentInfoNode* Node,int OrderID){
	IndentInfoNode* p = Node;
	if (!p||OrderID<0) {
		printf("                                           未找到订单！                                          \n");
	}
	else if (OrderID == 0) {
		while (p)
		{
			printCentered(TranslateIntToChar(p->OrderID), 8);
			printCentered(p->passenger->name, 10);
			printCentered(p->Insurance, 10);
			printCentered(TranslateIntToChar(p->Order_Tickets_Num), 10);
			printCentered(p->Train->ID, 10);
			printCentered(p->Train->info[p->Station_B].Station_Name, 10);
			printCentered(p->Train->info[p->Station_E].Station_Name, 10);
			printCentered(TranslateTimeToChar(p->Start_Time), 10);
			printCentered(TranslateTimeToChar(p->End_Time), 10);
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------\n");
			p = p->next;
		}
	}
	else if (OrderID > 0) {
		while (p && p->OrderID != OrderID)p = p->next;
		if (p) {
			printCentered(TranslateIntToChar(p->OrderID), 8);
			printCentered(p->passenger->name, 10);
			printCentered(p->Insurance, 10);
			printCentered(TranslateIntToChar(p->Order_Tickets_Num), 10);
			printCentered(p->Train->ID, 10);
			printCentered(p->Train->info[p->Station_B].Station_Name, 10);
			printCentered(p->Train->info[p->Station_E].Station_Name, 10);
			printCentered(TranslateTimeToChar(p->Start_Time), 10);
			printCentered(TranslateTimeToChar(p->End_Time), 10);
			printf("\n");
			printf("-------------------------------------------------------------------------------------------------\n");
		}
		else {
			printf("                                           未找到订单！                                          \n");
		}
	}


		//------------------------------------------ 探 索 进 程 ------------------------------------------
		// 不许删 

		/*
		printf("  %-6d| %-8s    |   %-6s |   %-6d |   %-6s |   %-6s |   %-6s |    %02d:%02d   |    %02d:%02d   \n",
		p->OrderID, p->passenger->name.c_str(), p->Insurance.c_str(), p->Order_Tickets_Num, p->Train->ID.c_str(), p->Train->info[p->Station_B].Station_Name.c_str(),
		p->Train->info[p->Station_E].Station_Name.c_str(), p->Start_Time / 60, p->Start_Time % 60,  p->End_Time / 60, p->End_Time % 60);
		*/

		/*
		cout << setfill(' ') << setw(8) << Node->OrderID << setw(3) << '|' << setw(8) << Node->passenger->name << setw(3) << '|' << setw(8) << Node->Insurance
		<< setw(3) << '|' << setw(8) << Node->Order_Tickets_Num << setw(3) << '|' << setw(8) << Node->Train->ID << setw(3) << '|' << setw(8)
		<< Node->Train->info[Node->Station_B].Station_Name << setw(3) << '|' << setw(8) << Node->Train->info[Node->Station_E].Station_Name
		<< setw(3) << '|' << setfill('0') << setw(2) << Node->Start_Time / 60 << setfill(' ')<< setw(2) << ':'  << setfill('0') << setw(2)
		<< Node->Start_Time % 60 << setw(3) << '|' << setfill('0')<< setw(2) << Node->End_Time / 60 << setfill(' ') << setw(2) << ':'
		<< setfill('0') << setw(2) << Node->End_Time % 60 << setfill(' ') << endl;
		*/	
}

//候补订单信息表头
void WaitOrder_Info_Title() {
	printf("                                       候补订单                                       \n");
	printf("--------------------------------------------------------------------------------------\n");
	printCentered("订单号", 8);
	printCentered("订购票数", 10);
	printCentered("列车号", 10);
	printCentered("出发站", 10);
	printCentered("终点站", 10);
	printCentered("出发时间", 10);
	printCentered("抵达时间", 10);
	printCentered("候补情况", 10);
	printf("\n");
	printf("--------------------------------------------------------------------------------------\n");
}

//候补订单信息表项 i->0 显示全部订单 1....n 对应订单号订单
void WaitOrder_Info_Line(WaitListNode* Node,int WaitID) {
	WaitListNode* p = Node;
	if (!p|| WaitID <0) {
		printf("                                           未找到订单！                                          \n");
	}
	else if (WaitID == 0) {
		while (p)
		{
			printCentered(TranslateIntToChar(p->WaitID), 8);
			printCentered(TranslateIntToChar(p->Wait_Tickets_Num), 10);
			printCentered(p->Train->ID, 10);
			printCentered(p->Train->info[p->Station_B].Station_Name, 10);
			printCentered(p->Train->info[p->Station_E].Station_Name, 10);
			printCentered(TranslateTimeToChar(p->Start_Time), 10);
			printCentered(TranslateTimeToChar(p->End_Time), 10);
			if (p->WaitFlag) {
				printCentered("正在候补中", 10);
			}
			else {
				printCentered("候补成功", 10);
			}
			printf("\n");
			printf("--------------------------------------------------------------------------------------\n");
			p = p->next;
		}
	}
	else if (WaitID > 0) {
		while (p && p->WaitID != WaitID)p = p->next;
		if (p) {
			printCentered(TranslateIntToChar(p->WaitID), 8);
			printCentered(TranslateIntToChar(p->Wait_Tickets_Num), 10);
			printCentered(p->Train->ID, 10);
			printCentered(p->Train->info[p->Station_B].Station_Name, 10);
			printCentered(p->Train->info[p->Station_E].Station_Name, 10);
			printCentered(TranslateTimeToChar(p->Start_Time), 10);
			printCentered(TranslateTimeToChar(p->End_Time), 10);
			if (p->WaitFlag) {
				printCentered("正在候补中", 10);
			}
			else {
				printCentered("候补成功", 10);
			}
			printf("\n");
			printf("--------------------------------------------------------------------------------------\n");
		}
		else {
			printf("                                           未找到订单！                                          \n");
		}
	}

}

//候补订单信息表 详细版 1....n 对应订单号订单
void WaitOrder_Info_Line_Detailed(WaitListNode* Node,int WaitID) {
	WaitListNode* p = Node;
	if (WaitID <= 0) {
		printf("                        候补订单 %d 详情                            \n", WaitID);
		printf("------------------------------------------------------------------\n");
		printf("                          未找到订单！                              \n");
	}
	else {
		while (p && p->WaitID != WaitID)p = p->next; {
			if (p) {
					//订单概要
					printf("                        候补订单 %d 详情                            \n", WaitID);
					printf("------------------------------------------------------------------\n");
					printCentered("列车号", 10);
					printCentered(p->Train->ID, 10);
					printCentered("出发站", 10);
					printCentered(p->Train->info[p->Station_B].Station_Name, 10);
					printCentered("终点站", 10);
					printCentered(p->Train->info[p->Station_E].Station_Name, 10);
					printf("\n");
					printf("------------------------------------------------------------------\n");
					printCentered("出发时间", 10);
					printCentered(TranslateTimeToChar(p->Start_Time), 10);
					printCentered("抵达时间", 10);
					printCentered(TranslateTimeToChar(p->End_Time), 10);
					printCentered("候补情况", 10);
					if (p->WaitFlag) {
						printCentered("正在候补中", 10);
					}
					else {
						printCentered("候补成功", 10);
					}
					printf("\n");
					printf("------------------------------------------------------------------\n");
					printCentered("乘车人姓名", 15);
					printCentered("性别", 8);
					printCentered("电话号码", 18);
					printCentered("身份证号", 21);
					printf("\n------------------------------------------------------------------\n");
					for (int j = 0;j < p->Wait_Tickets_Num; j++)
					{
						printCentered(p->passengers[j]->name, 15);
						printCentered(p->passengers[j]->gender, 8);
						printCentered(p->passengers[j]->PhoneN, 18);
						printCentered(p->passengers[j]->IC, 21);
						printf("\n");
						printf("------------------------------------------------------------------\n");
					}
			}
			else {
				printf("                        候补订单 %d 详情                            \n", WaitID);
				printf("-------------------------------------------------------------------\n");
				printf("                          未找到订单！                              \n");
			}
		}
	}
}