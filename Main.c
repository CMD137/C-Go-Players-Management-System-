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
    		case 1://�½�������Ϣ�� 
    			system("cls");
    			CreateTable();
    			break;
    		case 2://ѡ�񲢵���������Ϣ��
    			system("cls");
    	 		LoadTable(filename);
    			break;
    		case 3://��ʾ������Ϣ
    			system("cls");
    			ShowData(filename);
				break;
    		case 4://��ѯ������Ϣ
    			system("cls");
    			QuaryData(filename);
				break;
    		case 5://����������Ϣ
    			system("cls");
    			AddData(filename); 
				break;
    		case 6://ɾ��������Ϣ
    			system("cls");
    			DeleteData(filename);
				break;
    		case 7://�޸�������Ϣ
    			system("cls");
    			ChangeData(filename);
				break;
    		case 8://ͳ��������Ϣ
    			system("cls");
    			CountData(filename);
				break;
    		case 9://��������Ϣ��������
    			system("cls");
    			SortData(filename);
				break;
    		case 10://��ʾ�û��Ƿ��˳���ϵͳ
    			system("cls");
    			Exit();
				break;
		}
	}
	return 0;
}

