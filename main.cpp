#include "data.h"
#include "menu.h"
#include "tool.h"
#include "TrainConsole.h"
#include "Indents_Accounts.h"
#include <conio.h>

#define BYBEGINTIME 0	//���ճ���ʱ������
#define BYTICKETS 1	//����ʣ�೵Ʊ������
#define BYTIME 2	//���ճ���ʱ������
#define BYREACHTIME 3	//���յִ�ʱ������
#define DECENDING 0 //����
#define ASCENDING 1	//����

//����Ʊ
void Buy_Tickets(Indents_Accounts IA_OBJ, TrainConsole TC_OBJ) {
	while (true) {
		system("cls");
		string Station_B, Station_E;
		int Condition[4] = { BYBEGINTIME,BYTICKETS,BYTIME,BYREACHTIME };
		int Order[2] = { DECENDING,ASCENDING };
		int Condition_choose = 0;	//������ѡ���򷽷�
		int Order_choose = 0;	//������ѡ����˳��
		int Remaining_Tickets;	//������ѡ�г���ʣ�೵Ʊ��

		//�������վ
		cout << "���������վ(����Q/q�˳�)��";
		cin >> Station_B;
		if (Station_B == "Q" || Station_B == "q")	return;

		//�����յ�վ
		cout << "�������յ�վ��";
		cin >> Station_E;
		int Train_Num = TC_OBJ.TrainSearch(Station_B, Station_E);	//���������ط����������г���

		//ѡ��ѭ��
		bool Circle = true;
		while (Circle) {
			system("cls");

			TC_OBJ.ResultShow(Condition[Condition_choose], Order[Order_choose]);	//���չ涨����������ʾ�г���Ϣ
			
			//ѡ����
			int choose;
			cout << "1:����Ʊ 2:���շ���ʱ������ 3:���յִ�ʱ������ 4:����ʣ��Ʊ������ 5:���ճ˳�ʱ������ 6:������һ��\n>>";
			choose = ChooseInput();
			switch (choose)
			{
			case 1:// ����Ʊ
			{
				if (Train_Num == 0) {
					cout << "�޷����г��ɹ�ѡ��" << endl;
					_sleep(1 * 1000);
				}
				else {
					//��Ʊѭ��
					bool Circle1 = true;
					while (Circle1) {
						string Entry_insurance,Selected_ID;
						vector<string> numbers_passenger_str, numbers_insurance_str;
						vector<int> numbers_passenger, numbers_insurance,numbers_passenger_existed;
						int Selected_Wait = 3;

						//ѡ��Ҫ�������г�
						while (true) {
							cout << "�������г���:";
							cin >> Selected_ID;

							// �ж���ѡ�г��Ƿ���Ʊ -1Ϊ���������û�иó���
							Remaining_Tickets = TC_OBJ.Tickets_Selected_ID(Selected_ID);
							if (Remaining_Tickets == -1) {
								cout << "�����г�����������������!" << endl;
								_sleep(1 * 1000);
							}
							else if (Remaining_Tickets == 0) {
								while (true) {
									cout << Selected_ID << "�г���ʱû�г�Ʊ�������� 1���򲹶�Ʊ 2������ >>" ;
									Selected_Wait = ChooseInput();
									if (Selected_Wait != 1 && Selected_Wait != 2) {
										cout << "�����������������룡"<<endl;
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
						//�������˻��˳��������Ҫ���������г��ĳ˳���
						while (true) {
							string Entry;
							numbers_passenger.clear();	//�������
							system("cls");
							IA_OBJ.PassengerShow(-1);	//��ʾ���г˳�����Ϣ

							cout << "��ѡ��˳���(��д��ţ��ԣ��ָ�������0��ӳ˳���)��";
							cin >> Entry;
							if (Entry == "0") {
								IA_OBJ.AddPessenger();	//��ӳ˿�
							}
							else {
								bool IsNum;

								//��Ӣ�Ķ��ŷָ�
								if (Entry.find(',') != -1) {
									Split(Entry, numbers_passenger_str, ',');	//��������������Ƿ���Ӣ�Ķ���
									IsNum = TranslateToInt(numbers_passenger_str, numbers_passenger);	//������ݲ����Խ�������ת��Ϊ����
									if (IsNum) {
										//�����
										if (Selected_Wait == 1) {
											if (numbers_passenger.size() > 9)
											{
												cout << "��ѡ�˳�������Ϊ" << numbers_passenger.size() << "�����򲹶����˳�������������9�˵����ƣ�������ѡ��";
												_sleep(1 * 1000);
											}
											else {
												IA_OBJ.PassengerExist(Selected_ID, numbers_passenger, numbers_passenger_existed);	//�жϳ˳������Ƿ����Ѿ����и��г���Ʊ��
												if (numbers_passenger_existed.size() == 0) {
													for (int i = 0;i < numbers_passenger.size();i++) {
														if (numbers_passenger[i] > IA_OBJ.GetPassengerNum()) {	
															cout << "������������������!" << endl;
															_sleep(1 * 1000);
															continue;
														}
													}
													break;
												}
												else if(numbers_passenger_existed.size() == 1) {
													cout << "���Ϊ" << numbers_passenger_existed[0] << "�ĳ˳����Ѿ����и��г���Ʊ��������ѡ��";
													_sleep(1 * 1000);
												}
												else {
													cout << "���Ϊ";
													for (int i = 0;i < numbers_passenger_existed.size();i++) {
														cout << numbers_passenger_existed[i] << ',';
													}
													cout << "\b \b" << "�ĳ˿��Ѿ����и��г���Ʊ��������ѡ��";
													_sleep(1 * 1000);
												}
											}
										}
										//�����������
										else 
										{
											if (numbers_passenger.size() > Remaining_Tickets)
											{
												cout << "��ѡ�˳�������Ϊ" << numbers_passenger.size() << "����ʣ��Ʊ��" << Remaining_Tickets << "��������ѡ��";
												_sleep(1 * 1000);
											}
											else {
												IA_OBJ.PassengerExist(Selected_ID, numbers_passenger, numbers_passenger_existed);
												if (numbers_passenger_existed.size() == 0) {
													for (int i = 0;i < numbers_passenger.size();i++) {
														if (numbers_passenger[i] > IA_OBJ.GetPassengerNum()) {
															cout << "������������������!" << endl;
															_sleep(1 * 1000);
															continue;
														}
													}
													break;
												}
												else if (numbers_passenger_existed.size() == 1) {
													cout << "���Ϊ" << numbers_passenger_existed[0] << "�ĳ˳����Ѿ����и��г���Ʊ��������ѡ��";
													_sleep(1 * 1000);
												}
												else {
													cout << "���Ϊ";
													for (int i = 0;i < numbers_passenger_existed.size();i++) {
														cout << numbers_passenger_existed[i] << ',';
													}
													cout << "\b \b" << "�ĳ˿��Ѿ����и��г���Ʊ��������ѡ��";
													_sleep(1 * 1000);
												}
											}
										}
									}
									else {
										cout << "������������������!" << endl;
										_sleep(1 * 1000);
									}
								}
								//�������
								else {
									try
									{
										numbers_passenger.push_back(stoi(Entry));	//���Խ���������ֱ��ת��Ϊ����
										IA_OBJ.PassengerExist(Selected_ID, numbers_passenger, numbers_passenger_existed);
										if (numbers_passenger_existed.size() == 0)break;
										else if (numbers_passenger_existed.size() == 1) {
											cout << "���Ϊ" << numbers_passenger_existed[0] << "�ĳ˳����Ѿ����и��г���Ʊ��������ѡ��";
											_sleep(1 * 1000);
										}
										else {
											cout << "���Ϊ";
											for (int i = 0;i < numbers_passenger_existed.size();i++) {
												cout << numbers_passenger_existed[i] << ',';
											}
											cout << "\b \b" << "�ĳ˿��Ѿ����и��г���Ʊ��������ѡ��";
											_sleep(1 * 1000);
										}
									}
									catch (const invalid_argument)
									{
										cout << "������������������!" << endl;
										_sleep(1 * 1000);
									}
									catch (const out_of_range)
									{
										cout << "������������������!" << endl;
										_sleep(1 * 1000);
									}
								}							
							}
						}

						//Ϊ�˳��˹�����
						while (true) {
							numbers_insurance.clear();	//�������
							bool IsNum,IsChild;
							cout << "��ѡ��Ҫ�����յĳ˳���(������ţ���,�ָ�,����0ȫ������)��";
							cin >> Entry_insurance;
							if (Entry_insurance != "0") {

								//��Ӣ�Ķ��ŷָ�
								if (Entry_insurance.find(',') != -1) {
									Split(Entry_insurance, numbers_insurance_str, ',');
									IsNum = TranslateToInt(numbers_insurance_str, numbers_insurance);	//�ж���ѡ�˳����Ƿ�Ϊǰһѡ��˳����е�
									if (IsNum)break;
									else {
										cout << "������������������!" << endl;
										_sleep(1 * 1000);
									}
								}

								//�������
								else {
									try
									{
										numbers_insurance.push_back(stoi(Entry_insurance));
										IsChild = IsChildVector(numbers_insurance, numbers_passenger);	//�ж���ѡ�˳����Ƿ�Ϊǰһѡ��˳����е�
										if(IsChild)	break;
										else {
											cout << "������������������!" << endl;
											_sleep(1 * 1000);
										}	
									}
									catch (const invalid_argument)
									{
										cout << "������������������!" << endl;
										_sleep(1 * 1000);
									}
									catch (const out_of_range)
									{
										cout << "������������������!" << endl;
										_sleep(1 * 1000);
									}
								}
							}
							else break;
						}

						//�򲹶�Ʊ
						if(Selected_Wait==1) 
						{
							IA_OBJ.AddWaitOrder(numbers_passenger, numbers_insurance, Selected_ID, TC_OBJ);
							cout << "��Ӻ򲹶����ɹ���" << endl;
							_sleep(1 * 1000);
						}

						//����Ʊ
						else if(Selected_Wait==3) 
						{
							//��Ӷ���
							IA_OBJ.AddOrder(numbers_passenger, numbers_insurance, Selected_ID, TC_OBJ);

							//�޸��г���Ϣ
							TC_OBJ.TrainInfoChange(Selected_ID, Station_B, Station_E,0, numbers_passenger.size());

							//�������������Ϣ
							Train_Num = TC_OBJ.TrainSearch(Station_B, Station_E);
							cout << "����ɹ�!" << endl;
							_sleep(1 * 1000);
						}

						bool Circle2 = true;
						while (Circle2) {
							cout << "1:������Ʊ 2:�鿴�˳����� 3:�鿴�򲹶��� 4:�˳� >>";
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
								cout << "����������ع�Ʊ���� >>";
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
								cout << "�����Ӧ�����Ų鿴���飬����0������һ�� >>";
								Wait = ChooseInput();
								if (Wait == 0) {
									Circle2 = false;
									Circle1 = false;
									continue;
								}
								else if (Wait < 0) {
									cout << "�����������������룡";
									_sleep(1 * 1000);
									continue;
								}
								else {
									system("cls");
									IA_OBJ.Indents_Wait_Show_Detailed(Wait);
									cout << "����������ع�Ʊ���� >>";
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
								cout << "�����������������룡" << endl;
								_sleep(1 * 1000);
								break;
							}
						}
					}

				}
			}
			break;
			case 2: //���շ���ʱ������
			{
				if (Condition_choose == 0) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 0;
			}
			 break;
			case 3:	//���յִ�ʱ������
			{
				if (Condition_choose == 3) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 3;
			}
			break;
			case 4:	//����ʣ��Ʊ������
			{ 
				if (Condition_choose == 1) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 1;
			}
			break;
			case 5: //���ճ˳�ʱ������
			{ 
				if (Condition_choose == 2) {
					if (Order_choose == 0)Order_choose = 1;
					else Order_choose = 0;
				}
				else Condition_choose = 2;
			}
				  break;
			case 6:	//������һ��
				Circle = false;
				break;
			default:
				cout << "������������������!";
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
		cout << "������1/2/3:";
		choose = ChooseInput();
		switch (choose)
		{
		case 1: //ע��
			IA_OBJ.Regist();
			break;
		case 2: //��¼
			if (IA_OBJ.Login()) {
				bool Main_Circle = true;
				while (Main_Circle) {
					system("cls");
					Main_Menu();
					int choose;
					cout << "������1/2/3/4/5:";
					choose = ChooseInput();
					switch (choose)
					{
					case 1:	//����Ʊ
						Buy_Tickets(IA_OBJ, TC_OBJ);
						break;
					case 2:	//�˳��˹���
					{
						bool Circle = true;
						while (Circle)
						{
							system("cls");
							IA_OBJ.PassengerShow(-1);
							//չʾ���г˳�����Ϣ
							cout << "1:��ӳ˳�����Ϣ 2:�޸ĳ˳�����Ϣ 3:ɾ���˳�����Ϣ 4:������һ�� >>";
							int choose;
							cin >> choose;
							switch (choose)
							{
							case 1:	//��ӳ˳���
								IA_OBJ.AddPessenger();
								break;
							case 2:	//�޸ĳ˳�����Ϣ
								IA_OBJ.ChangePessenger();
								break;
							case 3:	//ɾ���˳���
								IA_OBJ.DeletePessenger();
								break;
							case 4: //�˳�
								Circle = false;
								break;
							default:
								break;
							}
						}
					}
					break;
					case 3: //��������
					{
						bool Circle = true;
						while (Circle) {
							//Ŀǰ��ֱ����ʾ�������������˺򲹵��ٷ���ʾ�˳��������Ǻ򲹶���
							system("cls");
							cout << "��ѡ����Ҫ�鿴�Ķ�������:\n1:�˳�����  2���򲹶��� 3���˳� >>" << endl;
							int choose;
							choose = ChooseInput();
							switch (choose)
							{
							case 1:
							{
								bool Circle1 = true;
								while (Circle1) {
									system("cls");
									IA_OBJ.Indents_Show(0); //��ʾ����
									int choose1;
									cout << "1:��Ʊ  2��������һ�� >>";
									cin >> choose1;
									switch (choose1) {
									case 1:// ��Ʊ

										IA_OBJ.DeleteOrder(TC_OBJ); //ɾ������
										TC_OBJ.AssignWaitTicket(IA_OBJ);	//�򲹲���
										break;
									case 2://�˳�
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
									cout << "�����Ӧ�����Ų鿴���飬����0������һ�� >>";
									Wait = ChooseInput();
									if (Wait == 0) {
										Circle1 = false;
										continue;
									}

									else if (Wait < 0) {
										cout << "�����������������룡";
										_sleep(1 * 1000);
										continue;
									}

									else {
										system("cls");
										IA_OBJ.Indents_Wait_Show_Detailed(Wait);
										cout << "�����������";
										getch();
									}
								}
							}
							break;
							case 3:
								Circle = false;
								break;
							default:
								cout << "�����������������룡";
								_sleep(1 * 1000);
								break;
							}

						}
					}
					break;
					case 4:	//�޸�����
						IA_OBJ.Change_Password();
						break;
					case 5:	//�ǳ�
						Main_Circle = false;
						break;
					default:
						cout << "�������";
						_sleep(1 * 1000);
						break;
					}
				}
			}
			break;
		case 3:
			return 0;
		default:
			cout << "�������";
			_sleep(2 * 1000);
			break;
		}
	}
}