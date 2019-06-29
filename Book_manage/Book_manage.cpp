
#include "pch.h"
#include "mainfunction.h"
#include <iostream>
//程序运行入口
int main()
{
	short selected = 0;
	short selectedsub = 0;
	
	showwelcome();
	
	do
	{
		selected = showmenu();
		do {
			selectedsub = showsubmenu(selected);
			callsubtask(selectedsub);
		} while (selectedsub != _QUIT_);
	} while (selected!=_QUIT_);
	return 0;
    
}

