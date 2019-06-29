#pragma once
#ifndef SUBFUNCTION_H_INCLUDE
#define SUBFUNCTION_H_INCLUDE
#include "datainfo.h"
void listbook(void);//�о�ͼ����Ϣ
int inputbook(void);//1.¼��ͼ��
int deletebook(void);//2.ɾ��ͼ��
int searchbook(void);//3.��ѯͼ��
int modifybook(void);//4.�޸�ͼ��

BOOK findbook(char *ISBN); //11.����ISBN�Ų���ͼ��
int removebook(char *ISBN);//12.����ISBN��ɾ��ͼ��
int lendbookAct(BOOK book);//16.��¼������Ϣ

int lendbook(void);//5.����ͼ��
int returnbook(void);//6.�黹ͼ��

void listmember(void);
int inputmember(void);//7.ע���Ա
int deletemember(void);//8.ע����Ա
int searchmember(void);//9.��ѯ��Ա
int modifymember(void);//10.�޸Ļ�Ա

MEMBER findmember(char *name);//13.�����������һ�Ա
int removemember(char *name);//14.�����������һ�Ա
int memberborrow(MEMBER member);//15.��¼������Ա��Ϣ



#endif