#include "pch.h"
#include <iostream>
#include "mainfunction.h"
#include "subfunction.h"
using namespace std;

void showwelcome(void)
{
	cout << "**********************************" << endl;
	cout << "*      ��ӭʹ��ͼ�����ϵͳ      *"<<endl;
	cout << "*          �汾��copy           *"<<endl;
	cout << "**********************************"<<endl;
}

short showmenu(void)
{
	short selected = 0;
	cout << "****��ѡ����Ҫʹ�õ�ģ��****" << endl;
	cout << "******1--ͼ��ά��******" << endl;
	cout << "******2--ͼ�����******" << endl;
	cout << "******3--��Աά��******" << endl;
	cout << "******0--�˳�******" << endl;
	cout << "******��ѡ��******";
	cin >> selected;
	while(selected>3 || selected<0){
		cout << "****ѡ�����������ѡ��****";
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
			cout << "******ͼ�����******" << endl;
			cout <<"****��ѡ����Ҫִ�еĹ���:****"<<endl;
			cout << "******1--¼��******" << endl;
			cout << "******2--ɾ��******" << endl;
			cout << "******3--��ѯ******" << endl;
			cout << "******4--�޸�******" << endl;
			cout << "******5--�б�******" << endl;
			cout << "******0--�˳�******" << endl;
			cout << "******��ѡ��******";
			cin >> selected;
			while (selected>5 || selected<0) {
				cout << "****ѡ�����������ѡ��****";
				cin >> selected;
			}
			break;
		case 2:
			cout << "******ͼ�����******" << endl;
			cout << "****��ѡ����Ҫִ�еĹ���:****" << endl;
			cout << "******1--����******" << endl;
			cout << "******2--����******" << endl;
			cout << "******0--�˳�******" << endl;
			cout << "******��ѡ��******";
			cin >> selected;
			while (selected > 2 || selected < 0) {
				cout << "****ѡ�����������ѡ��****";
				cin >> selected;
			}
			if (selected != _QUIT_)//���õ��Ӻ�����lendbook��case 6(1+5);returnbook��case 7(2+5)
				selected += 5;
			break;
		case 3:
			cout << "******��Ա����******" << endl;
			cout << "****��ѡ����Ҫִ�еĹ���:****" << endl;
			cout << "******1--ע��******" << endl;
			cout << "******2--ע��******" << endl;
			cout << "******3--��ѯ******" << endl;
			cout << "******4--�޸�******" << endl;
			cout << "******5--�б�******" << endl;
			cout << "******0--�˳�******" << endl;
			cout << "******��ѡ��******";
			cin >> selected;
			while (selected > 5 || selected < 0) {
				cout << "****ѡ�����������ѡ��****";
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
		//ͼ�����ɾ�Ĳ��б�
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
        //���黹��
		case 6:
			rtn = lendbook();
			break;
		case 7:
			rtn = returnbook();
			break;
		
		//��Ա����ɾ�Ĳ��б�
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

