#include "pch.h"
#include <iostream>
#include "subfunction.h"
using namespace std;

const char *_DATA_FILE_ = "book.dat";//图书信息文件
const char *_TEMP_FILE_ = "book.tmp";//临时文件
const char *_MEMBER_FILE_ = "member.dat";//会员信息文件
//列表信息
void listbook(void)
{
	FILE *fp;
	BOOK bk;
	fp=fopen(_DATA_FILE_,"rb");//只读的方式打开
	cout<< "ISBN    name    publisher    author    ver    price    count" << endl;
	fread(&bk, sizeof(bk), 1, fp);//接收数据的内存地址、读取的每个数据项的字节数、数据项个数、输入流
	while (!feof(fp))//判断文件是否读完
	{
		cout << bk.isbn << " " << bk.name << " " << bk.publisher << " " << bk.author << " " << bk.ver << " " << bk.price << " " << bk.count << endl;
		fread(&bk, sizeof(bk), 1, fp);
	}
	fclose(fp);
}
//录入图书
int inputbook(void)
{
	int rtn = 1;
	BOOK book;
	char check = 'N';
	FILE *fp;
	fp = fopen(_DATA_FILE_, "ab");//追加方式打开文件
	if (fp == NULL)
		fp = fopen(_DATA_FILE_,"wb");//写方式打开文件
	if (fp == NULL)
		rtn = 0;
	else
	{
		do {
			cout << "******录入图书******" << endl;
			cout << "******ISBN--******";
			cin >> book.isbn;
			cout << "******书名--******";
			cin >> book.name;
			cout << "******出版社--******";
			cin >> book.publisher;
			cout << "******作者--******";
			cin >> book.author;
			cout << "******版次--******";
			cin >> book.ver;
			cout << "******价格--******";
			cin >> book.price;
			cout << "******库存--******";
			cin >> book.count;
			cout << "******确认保存（Y/N）:******";
			cin >> check;
			if (check == 'Y')
			{
				fwrite(&book,sizeof(book),1,fp);
			}
			cout << "******继续录入吗？（Y/N）******:";
			cin >> check;
		} while (check!='N');
	}
	fclose(fp);
	return rtn;
}
//根据ISBN号查找图书
BOOK findbook(char *ISBN)
{
	BOOK book;
	bool found = false;
	FILE *fp;
	fp = fopen(_DATA_FILE_,"rb");//读方式打开文件
	if (fp != NULL)//文件打开成功
	{
		fread(&book,sizeof(book),1,fp);
		while (!feof(fp))
		{
			if (!strcmp(book.isbn, ISBN))
			{
				found = true; //strcmp的返回值是0，表示相等，1表示不相等
				break;
			}
			fread(&book,sizeof(book),1,fp);
		}
		if (!found)
			book.count = -1;//没有找到
		fclose(fp);

	}
	return book;
}
//根据ISBN号删除图书信息
int removebook(char *ISBN)
{
	BOOK book;
	FILE *fp;
	FILE *temp;
	temp = fopen(_TEMP_FILE_,"w");//写方式打开文件
	fp = fopen(_DATA_FILE_,"rb");
	if (fp != NULL)
	{
		fread(&book,sizeof(book),1,fp);
		while (!feof(fp))
		{
			if (strcmp(book.isbn, ISBN))//strcmp返回值为非0时，代表不相等
				fwrite(&book, sizeof(book), 1, temp);
			fread(&book, sizeof(book), 1, fp);
		}
		fclose(fp);
		fclose(temp);
		remove(_DATA_FILE_);//删除原数据文件
		rename(_TEMP_FILE_,_DATA_FILE_);//重命名临时文件为图书信息文件
	}
	return 1;
}
//删除图书
int deletebook(void)
{
	char check = 'N';
	int rtn = 1;
	char ISBN[12];
	BOOK book;
	do {
		cout << "******请输入ISBN:******";
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
		{
			rtn = 0;
			cout << "******没有找到！******" << endl;
		}
		else
		{
			rtn = removebook(ISBN);
			if (rtn == 0)
				cout << "******删除失败！******" << endl;//会出现删除失败的情况？
		}
		cout << "******继续吗？（Y/N）:******";
		cin >> check;
	} while (check!='N');
	return rtn;
}
//查询图书
int searchbook(void)
{
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'N';
	do {
		cout << "******请输入ISBN:******";
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
			cout << "******没找到******" << endl;
		else
		{
			cout << "******ISBN---" << book.isbn << endl;
			cout << "******name---" << book.name << endl;
			cout << "******publisher---" << book.publisher << endl;
			cout << "******author---" << book.author << endl;
			cout << "******ver---" << book.ver << endl;
			cout << "******price---" << book.price << endl;
			cout << "******count---" << book.count << endl;
		}
		cout << "******继续查询吗？（Y/N）:******";
		cin >> check;
	} while (check!='N');
	return rtn;
}
//修改图书
int modifybook(void)
{
	cout << "******修改图书******" << endl;
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'N';
	do {
		cout << "******请输入ISBN：******";
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
			cout << "******没有找到******" << endl;
		else
		{
			cout << "******ISBN---" << book.isbn << endl;
			cout << "******name---" << book.name << endl;
			cout << "******publisher---" << book.publisher << endl;
			cout << "******author---" << book.author << endl;
			cout << "******ver---" << book.ver << endl;
			cout << "******price---" << book.price << endl;
			cout << "******count---" << book.count << endl;
			cout << "******修改吗？（Y/N）：******";
			cin >> check;
			if (check == 'Y')
			{
				removebook(ISBN);//删除
				inputbook();//录入一条新数据覆盖原数据
			}
		}
		cout << "******继续吗？（Y/N）：******";
		cin >> check;
	} while (check!= 'N');
	return rtn;
}

//记录借书信息
int lendbookAct(BOOK book)
{
	int rtn = 1;
	FILE *fp;
	fp = fopen(_DATA_FILE_, "ab");
	if (fp == NULL)
		fp = fopen(_DATA_FILE_, "wb");
	if (fp == NULL)
		rtn = 0;
	else
	{
		fwrite(&book, sizeof(book), 1, fp);
	}
	fclose(fp);
	return rtn;
}

//借阅图书
int lendbook(void)
{
	cout << "******借阅图书******" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	cout << "******输入图书ISBN：******";
	cin >> ISBN;
	cout << "******输入借阅者姓名:******";
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "******图书不存在！******" << endl;
	else
	{
		member = findmember(name);
		if(member.borrow==-1)
			cout << "******会员不存在！******" << endl;
		else
		{
			if(member.borrow>3)
				cout << "******借阅超限，不能再借！******" << endl;
			else
			{
				if(book.count==0)
					cout << "******书已借完！******" << endl;
				else
				{
					member.borrow++;
					book.count--;
					if (member.isbn1[0] == '\0')//保存ISBN号到会员信息中
						strcpy(member.isbn1,book.isbn);
					else if (member.isbn2[0] == '\0')
						strcpy(member.isbn2, book.isbn);
					else
						strcpy(member.isbn3, book.isbn);
					removemember(member.name);//删除原会员信息
					memberborrow(member);//记录借阅的会员信息
					removebook(book.isbn);//删掉原图书信息
					lendbookAct(book);//记录借阅的图书信息 
				}
			}
		}

	}
	return 0;
}
//归还图书
int returnbook(void)
{
	cout << "******归还图书******" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	bool ok = false;
	cout << "******输入图书ISBN：******";
	cin >> ISBN;
	cout << "******输入借阅者姓名:******";
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "******图书不存在！******" << endl;
	else
	{
		member = findmember(name);
		if (member.borrow == -1)
			cout << "******会员不存在！******" << endl;
		else
		{
			if (!strcmp(member.isbn1, book.isbn))
			{
				member.isbn1[0] = '\0';
				ok = true;
			}
			else if (!strcmp(member.isbn2, book.isbn))
			{
				member.isbn2[0] = '\0';
				ok = true;
			}
			else if (!strcmp(member.isbn3, book.isbn))
			{
				member.isbn3[0] = '\0';
				ok = true;
			}
			else
				cout << "******该会员没有借该书******" << endl;
			if(ok)
			{
				member.borrow--;
				book.count++;
				removemember(member.name);//删除原会员信息
				memberborrow(member);//记录借阅的会员信息
				removebook(book.isbn);//删掉原图书信息
				lendbookAct(book);//记录借阅的图书信息
			}
		}
	}
	return 0;
}


//列举图书会员信息
void listmember(void)
{
	FILE *fp;
	MEMBER member;
	fp = fopen(_MEMBER_FILE_, "rb");
	cout << "姓名    地址    借阅数    isbn1     isbn2    isbn3" << endl;
	fread(&member, sizeof(member), 1, fp);
	while (!feof(fp))
	{
		cout << member.name << " " << member.address << " " << member .borrow<< " " << member .isbn1 << " " << member.isbn2 << " " << member.isbn3 <<  endl;
		fread(&member, sizeof(member), 1, fp);
	}
	fclose(fp);
}
//注册会员
int inputmember(void)
{
	cout << "注册会员" << endl;
	int rtn = 1;
	MEMBER member;
	char check = 'N';
	FILE *fp;
	fp = fopen(_MEMBER_FILE_, "ab");//追加方式打开文件
	if (fp == NULL)
		fp = fopen(_MEMBER_FILE_, "wb");//写方式打开文件
	if (fp == NULL)
		rtn = 0;
	else
	{
		do {
			cout << "录入会员" << endl;
			cout << "姓名---";
			cin >> member.name;
			cout << "地址---";
			cin >> member.address;
			member.borrow = 0;//初始化会员信息
			member.isbn1[0] = '\0';
			member.isbn2[0] = '\0';
			member.isbn3[0] = '\0';
			cout << "确认保存（Y/N）:";
			cin >> check;
			if (check == 'Y')
			{
				fwrite(&member, sizeof(member), 1, fp);
			}
			cout << "继续录入吗？（Y/N）:";
			cin >> check;
		} while (check != 'N');
	}
	fclose(fp);
	return rtn;
}
//注销会员
int deletemember(void)
{
	cout << "注销会员" << endl;
	char check = 'N';
	int rtn = 1;
	char name[20];
	MEMBER member;
	do {
		cout << "请输入姓名:";
		cin >> name;
		member = findmember(name);
		if (member.borrow ==-1)
		{
			rtn = 0;
			cout << "没有找到！" << endl;
		}
		else
		{
			rtn = removemember(name);
			if (rtn == 0)
				cout << "删除失败！" << endl;
		}
		cout << "继续吗？（Y/N）:";
		cin >> check;
	} while (check != 'N');
	return rtn;
}
//查询会员
int searchmember(void)
{
	cout << "查询会员" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'N';
	do {
		cout << "请输入姓名:";
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
			cout << "没找到" << endl;
		else
		{
			cout << "姓名---" << member.name << endl;
			cout << "地址---" << member.address << endl;
			cout << "借阅数---" << member.borrow << endl;
			cout << "isbn1---" << member.isbn1 << endl;
			cout << "isbn2---" << member.isbn2 << endl;
			cout << "isbn3---" << member.isbn3 << endl;
		}
		cout << "继续查询吗？（Y/N）:";
		cin >> check;
	} while (check != 'N');
	return rtn;
}
//修改会员
int modifymember(void)
{
	cout << "修改会员" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'N';
	do {
		cout << "请输入姓名：";
		cin >> name;
		member=findmember(name);
		if (member.borrow == -1)
			cout << "没有找到" << endl;
		else
		{
			cout << "姓名---" << member.name << endl;
			cout << "地址---" << member.address << endl;
			cout << "借阅数---" << member.borrow << endl;
			cout << "isbn1---" << member.isbn1 << endl;
			cout << "isbn2---" << member.isbn2 << endl;
			cout << "isbn3---" << member.isbn3 << endl;
			cout << "修改吗？（Y/N）：";
			cin >> check;
			if (check == 'Y')
			{
				removebook(name);//删除
				inputmember();//录入一条新数据覆盖原数据
			}
		}
		cout << "继续吗？（Y/N）：";
		cin >> check;
	} while (check != 'N');
	return rtn;
}

//根据姓名查找会员
MEMBER findmember(char *name)
{
	MEMBER member;
	bool found = false;
	FILE *fp;
	fp = fopen(_MEMBER_FILE_, "rb");//读方式打开文件
	if (fp != NULL)
	{
		fread(&member, sizeof(member), 1, fp);
		while (!feof(fp))
		{
			if (!strcmp(member.name, name))
			{
				found = true;
				break;
			}
			fread(&member, sizeof(member), 1, fp);
		}
		if (!found)
			member.borrow = -1;//没有找到
		fclose(fp);

	}
	return member;
}
//根据姓名移除会员
int removemember(char *name)
{
	MEMBER member;
	FILE *fp;
	FILE *temp;
	temp = fopen(_TEMP_FILE_, "w");//写方式打开文件
	fp = fopen(_MEMBER_FILE_, "rb");
	if (fp != NULL)
	{
		fread(&member, sizeof(member), 1, fp);
		while (!feof(fp))
		{
			if (strcmp(member.name,name))
				fwrite(&member, sizeof(member), 1, temp);
			fread(&member, sizeof(member), 1, fp);
		}
		fclose(fp);
		fclose(temp);
		remove(_MEMBER_FILE_);//删除原数据文件
		rename(_TEMP_FILE_, _MEMBER_FILE_);//重命名临时文件为图书信息文件
	}
	return 1;
}

//记录借阅人员信息
int memberborrow(MEMBER member)
{
	int rtn = 1;
	FILE *fp;
	fp = fopen(_MEMBER_FILE_,"ab");
	if (fp == NULL)
		fp = fopen(_MEMBER_FILE_,"wb");
	if (fp == NULL)
		rtn = 0;
	else
	{
		fwrite(&member,sizeof(member),1,fp);
	}
	fclose(fp);
	return rtn;
}
