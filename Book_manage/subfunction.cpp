#include "pch.h"
#include <iostream>
#include "subfunction.h"
using namespace std;

const char *_DATA_FILE_ = "book.dat";//ͼ����Ϣ�ļ�
const char *_TEMP_FILE_ = "book.tmp";//��ʱ�ļ�
const char *_MEMBER_FILE_ = "member.dat";//��Ա��Ϣ�ļ�
//�б���Ϣ
void listbook(void)
{
	FILE *fp;
	BOOK bk;
	fp=fopen(_DATA_FILE_,"rb");//ֻ���ķ�ʽ��
	cout<< "ISBN    name    publisher    author    ver    price    count" << endl;
	fread(&bk, sizeof(bk), 1, fp);//�������ݵ��ڴ��ַ����ȡ��ÿ����������ֽ����������������������
	while (!feof(fp))//�ж��ļ��Ƿ����
	{
		cout << bk.isbn << " " << bk.name << " " << bk.publisher << " " << bk.author << " " << bk.ver << " " << bk.price << " " << bk.count << endl;
		fread(&bk, sizeof(bk), 1, fp);
	}
	fclose(fp);
}
//¼��ͼ��
int inputbook(void)
{
	int rtn = 1;
	BOOK book;
	char check = 'N';
	FILE *fp;
	fp = fopen(_DATA_FILE_, "ab");//׷�ӷ�ʽ���ļ�
	if (fp == NULL)
		fp = fopen(_DATA_FILE_,"wb");//д��ʽ���ļ�
	if (fp == NULL)
		rtn = 0;
	else
	{
		do {
			cout << "******¼��ͼ��******" << endl;
			cout << "******ISBN--******";
			cin >> book.isbn;
			cout << "******����--******";
			cin >> book.name;
			cout << "******������--******";
			cin >> book.publisher;
			cout << "******����--******";
			cin >> book.author;
			cout << "******���--******";
			cin >> book.ver;
			cout << "******�۸�--******";
			cin >> book.price;
			cout << "******���--******";
			cin >> book.count;
			cout << "******ȷ�ϱ��棨Y/N��:******";
			cin >> check;
			if (check == 'Y')
			{
				fwrite(&book,sizeof(book),1,fp);
			}
			cout << "******����¼���𣿣�Y/N��******:";
			cin >> check;
		} while (check!='N');
	}
	fclose(fp);
	return rtn;
}
//����ISBN�Ų���ͼ��
BOOK findbook(char *ISBN)
{
	BOOK book;
	bool found = false;
	FILE *fp;
	fp = fopen(_DATA_FILE_,"rb");//����ʽ���ļ�
	if (fp != NULL)//�ļ��򿪳ɹ�
	{
		fread(&book,sizeof(book),1,fp);
		while (!feof(fp))
		{
			if (!strcmp(book.isbn, ISBN))
			{
				found = true; //strcmp�ķ���ֵ��0����ʾ��ȣ�1��ʾ�����
				break;
			}
			fread(&book,sizeof(book),1,fp);
		}
		if (!found)
			book.count = -1;//û���ҵ�
		fclose(fp);

	}
	return book;
}
//����ISBN��ɾ��ͼ����Ϣ
int removebook(char *ISBN)
{
	BOOK book;
	FILE *fp;
	FILE *temp;
	temp = fopen(_TEMP_FILE_,"w");//д��ʽ���ļ�
	fp = fopen(_DATA_FILE_,"rb");
	if (fp != NULL)
	{
		fread(&book,sizeof(book),1,fp);
		while (!feof(fp))
		{
			if (strcmp(book.isbn, ISBN))//strcmp����ֵΪ��0ʱ���������
				fwrite(&book, sizeof(book), 1, temp);
			fread(&book, sizeof(book), 1, fp);
		}
		fclose(fp);
		fclose(temp);
		remove(_DATA_FILE_);//ɾ��ԭ�����ļ�
		rename(_TEMP_FILE_,_DATA_FILE_);//��������ʱ�ļ�Ϊͼ����Ϣ�ļ�
	}
	return 1;
}
//ɾ��ͼ��
int deletebook(void)
{
	char check = 'N';
	int rtn = 1;
	char ISBN[12];
	BOOK book;
	do {
		cout << "******������ISBN:******";
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
		{
			rtn = 0;
			cout << "******û���ҵ���******" << endl;
		}
		else
		{
			rtn = removebook(ISBN);
			if (rtn == 0)
				cout << "******ɾ��ʧ�ܣ�******" << endl;//�����ɾ��ʧ�ܵ������
		}
		cout << "******�����𣿣�Y/N��:******";
		cin >> check;
	} while (check!='N');
	return rtn;
}
//��ѯͼ��
int searchbook(void)
{
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'N';
	do {
		cout << "******������ISBN:******";
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
			cout << "******û�ҵ�******" << endl;
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
		cout << "******������ѯ�𣿣�Y/N��:******";
		cin >> check;
	} while (check!='N');
	return rtn;
}
//�޸�ͼ��
int modifybook(void)
{
	cout << "******�޸�ͼ��******" << endl;
	char ISBN[12];
	int rtn = 0;
	BOOK book;
	char check = 'N';
	do {
		cout << "******������ISBN��******";
		cin >> ISBN;
		book = findbook(ISBN);
		if (book.count == -1)
			cout << "******û���ҵ�******" << endl;
		else
		{
			cout << "******ISBN---" << book.isbn << endl;
			cout << "******name---" << book.name << endl;
			cout << "******publisher---" << book.publisher << endl;
			cout << "******author---" << book.author << endl;
			cout << "******ver---" << book.ver << endl;
			cout << "******price---" << book.price << endl;
			cout << "******count---" << book.count << endl;
			cout << "******�޸��𣿣�Y/N����******";
			cin >> check;
			if (check == 'Y')
			{
				removebook(ISBN);//ɾ��
				inputbook();//¼��һ�������ݸ���ԭ����
			}
		}
		cout << "******�����𣿣�Y/N����******";
		cin >> check;
	} while (check!= 'N');
	return rtn;
}

//��¼������Ϣ
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

//����ͼ��
int lendbook(void)
{
	cout << "******����ͼ��******" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	cout << "******����ͼ��ISBN��******";
	cin >> ISBN;
	cout << "******�������������:******";
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "******ͼ�鲻���ڣ�******" << endl;
	else
	{
		member = findmember(name);
		if(member.borrow==-1)
			cout << "******��Ա�����ڣ�******" << endl;
		else
		{
			if(member.borrow>3)
				cout << "******���ĳ��ޣ������ٽ裡******" << endl;
			else
			{
				if(book.count==0)
					cout << "******���ѽ��꣡******" << endl;
				else
				{
					member.borrow++;
					book.count--;
					if (member.isbn1[0] == '\0')//����ISBN�ŵ���Ա��Ϣ��
						strcpy(member.isbn1,book.isbn);
					else if (member.isbn2[0] == '\0')
						strcpy(member.isbn2, book.isbn);
					else
						strcpy(member.isbn3, book.isbn);
					removemember(member.name);//ɾ��ԭ��Ա��Ϣ
					memberborrow(member);//��¼���ĵĻ�Ա��Ϣ
					removebook(book.isbn);//ɾ��ԭͼ����Ϣ
					lendbookAct(book);//��¼���ĵ�ͼ����Ϣ 
				}
			}
		}

	}
	return 0;
}
//�黹ͼ��
int returnbook(void)
{
	cout << "******�黹ͼ��******" << endl;
	char ISBN[12];
	char name[20];
	MEMBER member;
	BOOK book;
	bool ok = false;
	cout << "******����ͼ��ISBN��******";
	cin >> ISBN;
	cout << "******�������������:******";
	cin >> name;
	book = findbook(ISBN);
	if (book.count == -1)
		cout << "******ͼ�鲻���ڣ�******" << endl;
	else
	{
		member = findmember(name);
		if (member.borrow == -1)
			cout << "******��Ա�����ڣ�******" << endl;
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
				cout << "******�û�Աû�н����******" << endl;
			if(ok)
			{
				member.borrow--;
				book.count++;
				removemember(member.name);//ɾ��ԭ��Ա��Ϣ
				memberborrow(member);//��¼���ĵĻ�Ա��Ϣ
				removebook(book.isbn);//ɾ��ԭͼ����Ϣ
				lendbookAct(book);//��¼���ĵ�ͼ����Ϣ
			}
		}
	}
	return 0;
}


//�о�ͼ���Ա��Ϣ
void listmember(void)
{
	FILE *fp;
	MEMBER member;
	fp = fopen(_MEMBER_FILE_, "rb");
	cout << "����    ��ַ    ������    isbn1     isbn2    isbn3" << endl;
	fread(&member, sizeof(member), 1, fp);
	while (!feof(fp))
	{
		cout << member.name << " " << member.address << " " << member .borrow<< " " << member .isbn1 << " " << member.isbn2 << " " << member.isbn3 <<  endl;
		fread(&member, sizeof(member), 1, fp);
	}
	fclose(fp);
}
//ע���Ա
int inputmember(void)
{
	cout << "ע���Ա" << endl;
	int rtn = 1;
	MEMBER member;
	char check = 'N';
	FILE *fp;
	fp = fopen(_MEMBER_FILE_, "ab");//׷�ӷ�ʽ���ļ�
	if (fp == NULL)
		fp = fopen(_MEMBER_FILE_, "wb");//д��ʽ���ļ�
	if (fp == NULL)
		rtn = 0;
	else
	{
		do {
			cout << "¼���Ա" << endl;
			cout << "����---";
			cin >> member.name;
			cout << "��ַ---";
			cin >> member.address;
			member.borrow = 0;//��ʼ����Ա��Ϣ
			member.isbn1[0] = '\0';
			member.isbn2[0] = '\0';
			member.isbn3[0] = '\0';
			cout << "ȷ�ϱ��棨Y/N��:";
			cin >> check;
			if (check == 'Y')
			{
				fwrite(&member, sizeof(member), 1, fp);
			}
			cout << "����¼���𣿣�Y/N��:";
			cin >> check;
		} while (check != 'N');
	}
	fclose(fp);
	return rtn;
}
//ע����Ա
int deletemember(void)
{
	cout << "ע����Ա" << endl;
	char check = 'N';
	int rtn = 1;
	char name[20];
	MEMBER member;
	do {
		cout << "����������:";
		cin >> name;
		member = findmember(name);
		if (member.borrow ==-1)
		{
			rtn = 0;
			cout << "û���ҵ���" << endl;
		}
		else
		{
			rtn = removemember(name);
			if (rtn == 0)
				cout << "ɾ��ʧ�ܣ�" << endl;
		}
		cout << "�����𣿣�Y/N��:";
		cin >> check;
	} while (check != 'N');
	return rtn;
}
//��ѯ��Ա
int searchmember(void)
{
	cout << "��ѯ��Ա" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'N';
	do {
		cout << "����������:";
		cin >> name;
		member = findmember(name);
		if (member.borrow == -1)
			cout << "û�ҵ�" << endl;
		else
		{
			cout << "����---" << member.name << endl;
			cout << "��ַ---" << member.address << endl;
			cout << "������---" << member.borrow << endl;
			cout << "isbn1---" << member.isbn1 << endl;
			cout << "isbn2---" << member.isbn2 << endl;
			cout << "isbn3---" << member.isbn3 << endl;
		}
		cout << "������ѯ�𣿣�Y/N��:";
		cin >> check;
	} while (check != 'N');
	return rtn;
}
//�޸Ļ�Ա
int modifymember(void)
{
	cout << "�޸Ļ�Ա" << endl;
	char name[20];
	int rtn = 0;
	MEMBER member;
	char check = 'N';
	do {
		cout << "������������";
		cin >> name;
		member=findmember(name);
		if (member.borrow == -1)
			cout << "û���ҵ�" << endl;
		else
		{
			cout << "����---" << member.name << endl;
			cout << "��ַ---" << member.address << endl;
			cout << "������---" << member.borrow << endl;
			cout << "isbn1---" << member.isbn1 << endl;
			cout << "isbn2---" << member.isbn2 << endl;
			cout << "isbn3---" << member.isbn3 << endl;
			cout << "�޸��𣿣�Y/N����";
			cin >> check;
			if (check == 'Y')
			{
				removebook(name);//ɾ��
				inputmember();//¼��һ�������ݸ���ԭ����
			}
		}
		cout << "�����𣿣�Y/N����";
		cin >> check;
	} while (check != 'N');
	return rtn;
}

//�����������һ�Ա
MEMBER findmember(char *name)
{
	MEMBER member;
	bool found = false;
	FILE *fp;
	fp = fopen(_MEMBER_FILE_, "rb");//����ʽ���ļ�
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
			member.borrow = -1;//û���ҵ�
		fclose(fp);

	}
	return member;
}
//���������Ƴ���Ա
int removemember(char *name)
{
	MEMBER member;
	FILE *fp;
	FILE *temp;
	temp = fopen(_TEMP_FILE_, "w");//д��ʽ���ļ�
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
		remove(_MEMBER_FILE_);//ɾ��ԭ�����ļ�
		rename(_TEMP_FILE_, _MEMBER_FILE_);//��������ʱ�ļ�Ϊͼ����Ϣ�ļ�
	}
	return 1;
}

//��¼������Ա��Ϣ
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
