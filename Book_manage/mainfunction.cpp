#include "pch.h"
#include <iostream>
#include "mainfunction.h"
#include "subfunction.h"
using namespace std;

void showwelcome(void)
{
	cout << "**********************************" << endl;
	cout << "*      欢迎使用图书管理系统      *"<<endl;
	cout << "*          版本：copy           *"<<endl;
	cout << "**********************************"<<endl;
}

short showmenu(void)
{
	short selected = 0;
	cout << "****请选择你要使用的模块****" << endl;
	cout << "******1--图书维护******" << endl;
	cout << "******2--图书借阅******" << endl;
	cout << "******3--会员维护******" << endl;
	cout << "******0--退出******" << endl;
	cout << "******请选择：******";
	cin >> selected;
	while(selected>3 || selected<0){
		cout << "****选择错误，请重新选择：****";
		cin >> selected;
	}
	return selected;
}

short showsubmenu(short menu)
{
	int selected = 0;
	switch (menu)
	{
		case 1:
			cout << "******图书管理******" << endl;
			cout <<"****请选择你要执行的功能:****"<<endl;
			cout << "******1--录入******" << endl;
			cout << "******2--删除******" << endl;
			cout << "******3--查询******" << endl;
			cout << "******4--修改******" << endl;
			cout << "******5--列表******" << endl;
			cout << "******0--退出******" << endl;
			cout << "******请选择：******";
			cin >> selected;
			while (selected>5 || selected<0) {
				cout << "****选择错误，请重新选择：****";
				cin >> selected;
			}
			break;
		case 2:
			cout << "******图书借阅******" << endl;
			cout << "****请选择你要执行的功能:****" << endl;
			cout << "******1--借书******" << endl;
			cout << "******2--还书******" << endl;
			cout << "******0--退出******" << endl;
			cout << "******请选择：******";
			cin >> selected;
			while (selected > 2 || selected < 0) {
				cout << "****选择错误，请重新选择：****";
				cin >> selected;
			}
			if (selected != _QUIT_)//调用的子函数是lendbook是case 6(1+5);returnbook是case 7(2+5)
				selected += 5;
			break;
		case 3:
			cout << "******会员管理******" << endl;
			cout << "****请选择你要执行的功能:****" << endl;
			cout << "******1--注册******" << endl;
			cout << "******2--注销******" << endl;
			cout << "******3--查询******" << endl;
			cout << "******4--修改******" << endl;
			cout << "******5--列表******" << endl;
			cout << "******0--退出******" << endl;
			cout << "******请选择：******";
			cin >> selected;
			while (selected > 5 || selected < 0) {
				cout << "****选择错误，请重新选择：****";
				cin >> selected;
			}
			if (selected != _QUIT_) //1->8;2->9;3->10;4->11;5->12;
				selected += 7;
			break;
		default:
			selected = _QUIT_;
	}
	return selected;
}
void callsubtask(short selected)
{
	int rtn;
	switch (selected)
	{
		//图书的增删改查列表
		case 1:
			rtn = inputbook();
			break;
		case 2:
			rtn = deletebook();
			break;
		case 3:
			rtn = searchbook();
			break;
		case 4:
			rtn = modifybook();
			break;
		case 5:
			listbook();
			break;
        //借书还书
		case 6:
			rtn = lendbook();
			break;
		case 7:
			rtn = returnbook();
			break;
		
		//会员的增删改查列表
		case 8:
			rtn = inputmember();
			break;
		case 9:
			rtn = deletemember();
			break;
		case 10:
			rtn = searchmember();
			break;
		case 11:
			rtn = modifymember();
			break;
		case 12:
			listmember();
			break;
	}
}

