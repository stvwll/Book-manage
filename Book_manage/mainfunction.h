#pragma once
#ifndef MAINFUNCTION_H_INCLUDE
#define MAINFUNCTION_H_INCLUDE


#define _QUIT_ 0
//��ʾ��ӭ��Ϣ
void showwelcome(void);
short showmenu(void);
short showsubmenu(short menu);
void callsubtask(short selected);
#endif