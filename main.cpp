#include "data.h"
#include "menu.h"
#include "tool.h"
#include "TrainConsole.h"
#include "Indents_Accounts.h"
#include <conio.h>

#define BYBEGINTIME 0	//按照出发时间排序
#define BYTICKETS 1	//按照剩余车票数排序
#define BYTIME 2	//按照乘坐时长排序
#define BYREACHTIME 3	//按照抵达时间排序
#define DECENDING 0 //降序
#define ASCENDING 1	//升序

//购买车票
void Buy_Tickets(Indents_Accounts IA_OBJ, TrainConsole TC_OBJ) {
	while (true) {
		system("cls");
		string Station_B, Station_E;
		int Condition[4] = { BYBEGINTIME,BYTICKETS,BYTIME,BYREACHTIME };
		int Order[2] = { DECENDING,ASCENDING };
		int Condition_choose = 0;	//保存所选排序方法
		int Order_choose = 0;	//保存所选排序顺序
		int Remaining_Tickets;	//保存所选列车的剩余车票数

		//输入出发站
		cout << "请输入出发站(输入Q/q退出)：";
		cin >> Station_B;
		if (Station_B == "Q" || Station_B == "q")	return;

		//输入终点站
		cout << "请输入终点站：";
		cin >> Station_E;
		int Train_Num = TC_OBJ.TrainSearch(Station_B, Station_E);	//搜索并返回符合条件的列车数

		//选车循环
		bool Circle = true;
		while (Circle) {
			system("cls");

			TC_OBJ.ResultShow(Condition[Condition_choose], Order[Order_choose]);	//按照规定方法排序显示列车信息
			
			//选择功能
			int choose;
			cout << "1:购买车票 2:按照发车时间排序 3:按照抵达时间排序 4:按照剩余票数排序 5:按照乘车时长排序 6:返回上一级\n>>";
			choose = ChooseInput();
			switch (choose)
			{
			case 1:// 购买车票
			{
				if (Train_Num == 0) {
					cout << "无符合列车可供选择" << endl;
					_sleep(1 * 1000);
				}
				else {
					//购票循环
					bool Circle1 = true;
					while (Circle1) {
						string Entry_insurance,Selected_ID;
						vector<string> numbers_passenger_str, numbers_insurance_str;
						vector<int> numbers_passenger, numbers_insurance,numbers_passenger_existed;
						int Selected_Wait = 3;

						//选择要乘坐的列车
						while (true) {
							cout << "请输入列车号:";
							cin >> Selected_ID;

							// 判断所选列车是否有票 -1为搜索结果中没有该车辆
							Remaining_Tickets = TC_OBJ.Tickets_Selected_ID(Selected_ID);
							if (Remaining_Tickets == -1) {
								cout << "输入列车号有误，请重新输入!" << endl;
								_sleep(1 * 1000);
							}
							else if (Remaining_Tickets == 0) {
								while (true) {
									cout << Selected_ID << "列车暂时没有车票，您可以 1：候补订票 2：返回 >>" ;
									Selected_Wait = ChooseInput();
									if (Selected_Wait != 1 && Selected_Wait != 2) {
										cout << "输入有误！请重新输入！"<<endl;
										_sleep(1 * 1000);
									}
									else break;
								}
								break;
							}
							else break;
						}
						if (Selected_Wait == 2) {
							Circle1 = false;
							continue;
						}
						//从已有账户乘车人中添加要乘坐该趟列车的乘车人
						while (true) {
							string Entry;
							numbers_passenger.clear();	//清空容器
							system("cls");
							IA_OBJ.PassengerShow(-1);	//显示所有乘车人信息

							cout << "请选择乘车人(填写序号，以，分隔，输入0添加乘车人)：";
							cin >> Entry;
							if (Entry == "0") {
								IA_OBJ.AddPessenger();	//添加乘客
							}
							else {
								bool IsNum;

								//以英文逗号分隔
								if (Entry.find(',') != -1) {
									Split(Entry, numbers_passenger_str, ',');	//检测输入内容中是否有英文逗号
									IsNum = TranslateToInt(numbers_passenger_str, numbers_passenger);	//拆分内容并尝试将各部分转化为整数
									if (IsNum) {
										//候补情况
										if (Selected_Wait == 1) {
											if (numbers_passenger.size() > 9)
											{
												cout << "所选乘车人数量为" << numbers_passenger.size() << "超过候补订单乘车人数量不超过9人的限制，请重新选择！";
												_sleep(1 * 1000);
											}
											else {
												IA_OBJ.PassengerExist(Selected_ID, numbers_passenger, numbers_passenger_existed);	//判断乘车人中是否有已经持有该列车车票的
												if (numbers_passenger_existed.size() == 0) {
													for (int i = 0;i < numbers_passenger.size();i++) {
														if (numbers_passenger[i] > IA_OBJ.GetPassengerNum()) {	
															cout << "输入有误，请重新输入!" << endl;
															_sleep(1 * 1000);
															continue;
														}
													}
													break;
												}
												else if(numbers_passenger_existed.size() == 1) {
													cout << "序号为" << numbers_passenger_existed[0] << "的乘车人已经持有该列车车票，请重新选择！";
													_sleep(1 * 1000);
												}
												else {
													cout << "序号为";
													for (int i = 0;i < numbers_passenger_existed.size();i++) {
														cout << numbers_passenger_existed[i] << ',';
													}
													cout << "\b \b" << "的乘客已经持有该列车车票，请重新选择！";
													_sleep(1 * 1000);
												}
											}
										}
										//正常购买情况
										else 
										{
											if (numbers_passenger.size() > Remaining_Tickets)
											{
												cout << "所选乘车人数量为" << numbers_passenger.size() << "超过剩余票数" << Remaining_Tickets << "，请重新选择！";
												_sleep(1 * 1000);
											}
											else {
												IA_OBJ.PassengerExist(Selected_ID, numbers_passenger, numbers_passenger_existed);
												if (numbers_passenger_existed.size() == 0) {
													for (int i = 0;i < numbers_passenger.size();i++) {
														if (numbers_passenger[i] > IA_OBJ.GetPassengerNum()) {
															cout << "输入有误，请重新输入!" << endl;
															_sleep(1 * 1000);
															continue;
														}
													}
													break;
												}
												else if (numbers_passenger_existed.size() == 1) {
													cout << "序号为" << numbers_passenger_existed[0] << "的乘车人已经持有该列车车票，请重新选择！";
													_sleep(1 * 1000);
												}
												else {
													cout << "序号为";
													for (int i = 0;i < numbers_passenger_existed.size();i++) {
														cout << numbers_passenger_existed[i] << ',';
													}
													cout << "\b \b" << "的乘客已经持有该列车车票，请重新选择！";
													_sleep(1 * 1000);
												}
											}
										}
									}
									else {
										cout << "输入有误，请重新输入!" << endl;
										_sleep(1 * 1000);
									}
								}
								//其它情况
								else {
									try
									{
										numbers_passenger.push_back(stoi(Entry));	//尝试将输入内容直接转化为整数
										IA_OBJ.PassengerExist(Selected_ID, numbers_passenger, numbers_passenger_existed);
										if (numbers_passenger_existed.size() == 0)break;
										else if (numbers_passenger_existed.size() == 1) {
											cout << "序号为" << numbers_passenger_existed[0] << "的乘车人已经持有该列车车票，请重新选择！";
											_sleep(1 * 1000);
										}
										else {
											cout << "序号为";
											for (int i = 0;i < numbers_passenger_existed.size();i++) {
												cout << numbers_passenger_existed[i] << ',';
											}
											cout << "\b \b" << "的乘客已经持有该列车车票，请重新选择！";
											_sleep(1 * 1000);
										}
									}
									catch (const invalid_argument)
									{
										cout << "输入有误，请重新输入!" << endl;
										_sleep(1 * 1000);
									}
									catch (const out_of_range)
									{
										cout << "输入有误，请重新输入!" << endl;
										_sleep(1 * 1000);
									}
								}							
							}
						}

						//为乘车人购买保险
						while (true) {
							numbers_insurance.clear();	//清空容器
							bool IsNum,IsChild;
							cout << "请选择要购买保险的乘车人(填入序号，以,分隔,输入0全不购买)：";
							cin >> Entry_insurance;
							if (Entry_insurance != "0") {

								//以英文逗号分隔
								if (Entry_insurance.find(',') != -1) {
									Split(Entry_insurance, numbers_insurance_str, ',');
									IsNum = TranslateToInt(numbers_insurance_str, numbers_insurance);	//判断所选乘车人是否为前一选择乘车人中的
									if (IsNum)break;
									else {
										cout << "输入有误，请重新输入!" << endl;
										_sleep(1 * 1000);
									}
								}

								//其它情况
								else {
									try
									{
										numbers_insurance.push_back(stoi(Entry_insurance));
										IsChild = IsChildVector(numbers_insurance, numbers_passenger);	//判断所选乘车人是否为前一选择乘车人中的
										if(IsChild)	break;
										else {
											cout << "输入有误，请重新输入!" << endl;
											_sleep(1 * 1000);
										}	
									}
									catch (const invalid_argument)
									{
										cout << "输入有误，请重新输入!" << endl;
										_sleep(1 * 1000);
									}
									catch (const out_of_range)
									{
										cout << "输入有误，请重新输入!" << endl;
										_sleep(1 * 1000);
									}
								}
							}
							else break;
						}

						//候补订票
						if(Selected_Wait==1) 
						{
							IA_OBJ.AddWaitOrder(numbers_passenger, numbers_insurance, Selected_ID, TC_OBJ);
							cout << "添加候补订单成功！" << endl;
							_sleep(1 * 1000);
						}

						//购买车票
						else if(Selected_Wait==3) 
						{
							//添加订单
							IA_OBJ.AddOrder(numbers_passenger, numbers_insurance, Selected_ID, TC_OBJ);

							//修改列车信息
							TC_OBJ.TrainInfoChange(Selected_ID, Station_B, Station_E,0, numbers_passenger.size());

							//更新搜索结果信息
							Train_Num = TC_OBJ.TrainSearch(Station_B, Station_E);
							cout << "购买成功!" << endl;
							_sleep(1 * 1000);
						}

						bool Circle2 = true;
						while (Circle2) {
							cout << "1:继续买票 2:查看乘车订单 3:查看候补订单 4:退出 >>";
							int choose1;
							choose1 = ChooseInput();
							switch (choose1)
							{
							case 1:
								Circle2 = false;
								Circle1 = false;
								break;
							case 2:
							{
								system("cls");
								IA_OBJ.Indents_Show(0);
								cout << "按任意键返回购票界面 >>";
								getch();
								Circle2 = false;
								Circle1 = false;
							}
							break;
							case 3:
							{
								system("cls");
								IA_OBJ.Indents_Wait_Show(0);
								int Wait;
								cout << "输入对应订单号查看详情，输入0返回上一级 >>";
								Wait = ChooseInput();
								if (Wait == 0) {
									Circle2 = false;
									Circle1 = false;
									continue;
								}
								else if (Wait < 0) {
									cout << "输入有误，请重新输入！";
									_sleep(1 * 1000);
									continue;
								}
								else {
									system("cls");
									IA_OBJ.Indents_Wait_Show_Detailed(Wait);
									cout << "按任意键返回购票界面 >>";
									getch();
									Circle2 = false;
									Circle1 = false;
								}
							}
							break;
							case 4:
								return;
								break;
							default:
								cout << "输入有误，请重新输入！" << endl;
								_sleep(1 * 1000);
								break;
							}
						}
					}

				}
			}
			break;
			case 2: //按照发车时间排序
			{
				if (Condition_choose == 0) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 0;
			}
			 break;
			case 3:	//按照抵达时间排序
			{
				if (Condition_choose == 3) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 3;
			}
			break;
			case 4:	//按照剩余票数排序
			{ 
				if (Condition_choose == 1) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 1;
			}
			break;
			case 5: //按照乘车时长排序
			{ 
				if (Condition_choose == 2) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 2;
			}
				  break;
			case 6:	//返回上一级
				Circle = false;
				break;
			default:
				cout << "输入有误，请重新输入!";
				_sleep(1 * 1000);
				break;
			}
		}
	}
}


int main() {
	Indents_Accounts IA_OBJ;
	TrainConsole TC_OBJ;
	IA_OBJ.Regist_AdM();
	TC_OBJ.LoadTrainInfo();
	while (1) {
		system("cls");
		Start_Menu();
		int choose;
		cout << "请输入1/2/3:";
		choose = ChooseInput();
		switch (choose)
		{
		case 1: //注册
			IA_OBJ.Regist();
			break;
		case 2: //登录
			if (IA_OBJ.Login()) {
				bool Main_Circle = true;
				while (Main_Circle) {
					system("cls");
					Main_Menu();
					int choose;
					cout << "请输入1/2/3/4/5:";
					choose = ChooseInput();
					switch (choose)
					{
					case 1:	//购买车票
						Buy_Tickets(IA_OBJ, TC_OBJ);
						break;
					case 2:	//乘车人管理
					{
						bool Circle = true;
						while (Circle)
						{
							system("cls");
							IA_OBJ.PassengerShow(-1);
							//展示所有乘车人信息
							cout << "1:添加乘车人信息 2:修改乘车人信息 3:删除乘车人信息 4:返回上一级 >>";
							int choose;
							cin >> choose;
							switch (choose)
							{
							case 1:	//添加乘车人
								IA_OBJ.AddPessenger();
								break;
							case 2:	//修改乘车人信息
								IA_OBJ.ChangePessenger();
								break;
							case 3:	//删除乘车人
								IA_OBJ.DeletePessenger();
								break;
							case 4: //退出
								Circle = false;
								break;
							default:
								break;
							}
						}
					}
					break;
					case 3: //订单管理
					{
						bool Circle = true;
						while (Circle) {
							//目前先直接显示订单，后面做了候补的再分显示乘车订单还是候补订单
							system("cls");
							cout << "请选择您要查看的订单种类:\n1:乘车订单  2：候补订单 3：退出 >>" << endl;
							int choose;
							choose = ChooseInput();
							switch (choose)
							{
							case 1:
							{
								bool Circle1 = true;
								while (Circle1) {
									system("cls");
									IA_OBJ.Indents_Show(0); //显示订单
									int choose1;
									cout << "1:退票  2：返回上一级 >>";
									cin >> choose1;
									switch (choose1) {
									case 1:// 退票

										IA_OBJ.DeleteOrder(TC_OBJ); //删除订单
										TC_OBJ.AssignWaitTicket(IA_OBJ);	//候补操作
										break;
									case 2://退出
										Circle1 = false;
										break;
									}
								}
							}
							break;
							case 2:
							{
								bool Circle1 = true;
								while (Circle1) {
									system("cls");
									IA_OBJ.Indents_Wait_Show(0);
									int Wait;
									cout << "输入对应订单号查看详情，输入0返回上一级 >>";
									Wait = ChooseInput();
									if (Wait == 0) {
										Circle1 = false;
										continue;
									}

									else if (Wait < 0) {
										cout << "输入有误，请重新输入！";
										_sleep(1 * 1000);
										continue;
									}

									else {
										system("cls");
										IA_OBJ.Indents_Wait_Show_Detailed(Wait);
										cout << "按任意键返回";
										getch();
									}
								}
							}
							break;
							case 3:
								Circle = false;
								break;
							default:
								cout << "输入有误，请重新输入！";
								_sleep(1 * 1000);
								break;
							}

						}
					}
					break;
					case 4:	//修改密码
						IA_OBJ.Change_Password();
						break;
					case 5:	//登出
						Main_Circle = false;
						break;
					default:
						cout << "输入错误";
						_sleep(1 * 1000);
						break;
					}
				}
			}
			break;
		case 3:
			return 0;
		default:
			cout << "输入错误";
			_sleep(2 * 1000);
			break;
		}
	}
}