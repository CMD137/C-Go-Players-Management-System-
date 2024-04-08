#include <stdio.h>
#include<windows.h> 
#include <stdlib.h>
#include"./inc/GPMS.h"

int main()
{	
	char filename[50]={0};
	int select;
    while(1)
    {	
    	system("cls");
    	ShowMenu();
    	scanf("%d",&select);
    	switch(select)
    	{
    		case 1://新建棋手信息表 
    			system("cls");
    			CreateTable();
    			break;
    		case 2://选择并导入棋手信息表
    			system("cls");
    	 		LoadTable(filename);
    			break;
    		case 3://显示棋手信息
    			system("cls");
    			ShowData(filename);
				break;
    		case 4://查询棋手信息
    			system("cls");
    			QuaryData(filename);
				break;
    		case 5://增加棋手信息
    			system("cls");
    			AddData(filename); 
				break;
    		case 6://删除棋手信息
    			system("cls");
    			DeleteData(filename);
				break;
    		case 7://修改棋手信息
    			system("cls");
    			ChangeData(filename);
				break;
    		case 8://统计棋手信息
    			system("cls");
    			CountData(filename);
				break;
    		case 9://对棋手信息进行排序
    			system("cls");
    			SortData(filename);
				break;
    		case 10://提示用户是否退出该系统
    			system("cls");
    			Exit();
				break;
		}
	}
	return 0;
}

