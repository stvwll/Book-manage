#pragma once
#ifndef SUBFUNCTION_H_INCLUDE
#define SUBFUNCTION_H_INCLUDE
#include "datainfo.h"
void listbook(void);//列举图书信息
int inputbook(void);//1.录入图书
int deletebook(void);//2.删除图书
int searchbook(void);//3.查询图书
int modifybook(void);//4.修改图书

BOOK findbook(char *ISBN); //11.根据ISBN号查找图书
int removebook(char *ISBN);//12.根据ISBN号删除图书
int lendbookAct(BOOK book);//16.记录借书信息

int lendbook(void);//5.借阅图书
int returnbook(void);//6.归还图书

void listmember(void);
int inputmember(void);//7.注册会员
int deletemember(void);//8.注销会员
int searchmember(void);//9.查询会员
int modifymember(void);//10.修改会员

MEMBER findmember(char *name);//13.根据姓名查找会员
int removemember(char *name);//14.根据姓名查找会员
int memberborrow(MEMBER member);//15.记录借阅人员信息



#endif