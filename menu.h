#pragma once
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include "data.h"
using namespace std;

void Start_Menu();
void Main_Menu();
void Train_Info_Title();
void Train_Info_Line(SearchResultNode Result);
void Passenger_Info_Title();
void Passenger_Info_Line(AccountInfoNode* A, int offset);
void Order_Info_Title();
void Order_Info_Line(IndentInfoNode* Node,int OrderID);
void WaitOrder_Info_Title();
void WaitOrder_Info_Line(WaitListNode* Node, int WaitID);
void WaitOrder_Info_Line_Detailed(WaitListNode* Node, int WaitID);

#endif // !MENU

