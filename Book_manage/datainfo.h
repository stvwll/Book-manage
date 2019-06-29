#pragma once
#ifndef DATAINFO_H_INCLUDE
#define DATAINFO_H_INCLUDE
typedef struct tagBook {
	char isbn[12];
	char name[20];
	char publisher[20];
	char author[20];
	short ver;
	float price;
	short count;
}BOOK;
typedef struct tagMEMBER {
	char name[20];
	char address[20];
	short borrow;
	char isbn1[12];
	char isbn2[12];
	char isbn3[12];
}MEMBER;
#endif
