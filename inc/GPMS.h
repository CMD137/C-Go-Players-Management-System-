#pragma once
#include<windows.h> 
#include <stdlib.h>
#include<stdio.h>
#include <dirent.h>
#include"GPtable.h"
#include<string.h>
/////////////////////////////////////////////////////////////////////
//GPMS.h主要用于写main函数中的10个功能函数 
////////////////////////////////////////////////////////////////////


//主菜单界面：
void ShowMenu(){
	printf("+--------------------------------------------------+\n");
	printf("|             欢迎使用围棋棋手管理系统             |\n");
	printf("+--------------------------------------------------+\n");
	printf("|****        1. 新建棋手信息表                 ****|\n");
	printf("|****        2. 选择并导入棋手信息表           ****|\n");
	printf("|****        3. 显示棋手信息                   ****|\n");
	printf("|****        4. 查询棋手信息                   ****|\n");
	printf("|****        5. 增加棋手信息                   ****|\n");
	printf("|****        6. 删除棋手信息                   ****|\n");
	printf("|****        7. 修改棋手信息                   ****|\n");
	printf("|****        8. 统计棋手信息                   ****|\n");
	printf("|****        9. 对棋手信息进行排序             ****|\n");
	printf("|****        10. 退出系统                      ****|\n");
	printf("+--------------------------------------------------+\n");
	printf("请选择功能（输入1-10）：\n"); 
	printf("*温馨提示：*使用信息前请先使用功能2导入数据*\n");
	return;
} 

//1.新建棋手信息表
void CreateTable(){
	//查看目录： 
	struct dirent *de;  // 目录项指针
    DIR *dr = opendir("./datafiles");  // 打开当前目录

    if (dr == NULL) {
        printf("无法打开当前目录\n");
        return ;
    }
	printf("已存在以下表,请勿重复建表：\n"); 
    while ((de = readdir(dr)) != NULL) {  // 读取目录中的文件
        printf("%s\n", de->d_name);
    }
    closedir(dr);  // 关闭目录
	printf("请输入要新建的表名称(使用.dat文件，即新表名称:XXX.dat)\n"); 
	char tname[50]="./datafiles/";
	char in[30]={0};
	scanf("%s",in);
	strcat(tname,in);
	
	//新建表 
	FILE * tfp; 
	if ((tfp = fopen(tname, "wb")) == NULL) {
		printf("文件新建失败!\n"); 
		system("pause");
		return;
	}else
	{
		printf("新建信息表成功!\n");
		system("pause");

	}
	fclose(tfp);

}

//2.选择并导入棋手信息表
void LoadTable(char * filename){
	//查看目录： 
	struct dirent *de;  // 目录项指针
    DIR *dr = opendir("./datafiles");  // 打开当前目录

    if (dr == NULL) {
        printf("无法打开当前目录\n");
        return ;
    }
	printf("已存在以下表：\n"); 
    while ((de = readdir(dr)) != NULL) {  // 读取目录中的文件
        printf("%s\n", de->d_name);
    }
    closedir(dr);  // 关闭目录
    
	printf("请输入要打开的表名称\n"); 
	char fname[50]="./datafiles/";
	char in[30]={0};
	scanf("%s",in);
	strcat(fname,in);//组合为完整路径 
	strcpy(filename,fname);//将要打开的文件名传输到主函数以供其他文件使用
	
	//检验输入的文件是否存在:
	FILE* tfp;
	if((tfp=fopen(filename,"rb"))==NULL)
	{
	   	printf("文件不存在！返回后请重新输入!\n");
	   	system("pause");
	  	return;
    }else{
    	printf("文件%s已成功打开\n",in);
    	fclose(tfp);
    	system("pause");
	  	return;
	}
}

//3.显示棋手信息
void ShowData(char* filename){
	struct GoPlayerType players[1000];//编号最大999，最多999人
	//文件不存在或没打开,则返回。
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
		printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	  	return;
	}
	//count得到该表棋手的数量。
	int count=0;
	while(!feof(fp))
	{
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)//必须对fread的返回值进行判断，否则可能会将最后一条数据读2遍 
			count++;
	}
	fclose(fp);
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("该表内棋手人数：%-34d",count);
	printf("|\n"); 
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n"); 
	for(int i=0;i<count;i++){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level); // 释放函数中分配的内存
	}
	if(count==0){
		printf("\n");
		printf("     **      该表内暂无任何棋手信息       **\n");
	}
	system("pause");	
}

//4.查询棋手信息 
void QuaryData(char* filename){
	void NameQuary(char* filename); 
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
		printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	fclose(fp);
	printf("1.按棋手姓名查询(可模糊查询)\n");
	printf("2.按棋手身份查询\n");
	printf("3.按棋手段位查询\n");
	printf("0.返回上级菜单\n");
	printf("\n请输入0~3\n");
	int select;
	while(1){
		scanf("%d",&select);
		if(select==1){
			NameQuary(filename);
			break; 
		}else if(select==2){
			classificationQuary(filename);
			break;
		}else if(select==3){
			LevelQuary(filename);
			break;
		}else if(select==0){
			return ;
		}
	}
}

//5.增加棋手信息
void AddData(char* filename){
	struct GoPlayerType players[1000];//编号最大999，最多999人 
	//文件不存在或没打开,则返回。
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
	   	printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
    }
    //count得到该表棋手的数量。
    int count=0;	
	while(!feof(fp))
	{
	  	if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)//必须对fread的返回值进行判断，否则可能会将最后一条数据读2遍 
	 	{
		 	count++;
		}
	}
	fclose(fp);
	
	// 新增棋手信息
	struct GoPlayerType newPlayer;
	printf("请输入新增棋手的编号,格式为PXXX,如P042(不可与已有编号重复):\n");
	
	do{
		scanf("%s", newPlayer.id);
	}while(IdIsLegal(newPlayer.id));	//检验棋手id输入是否合法 
	
	for (int i = 0; i < count; i++) {
		if (strcmp(players[i].id, newPlayer.id) == 0) {
			printf("该编号已存在，请核对后再添加棋手！\n");
			system("pause");
			return;
		}
	}
	
	do{
	printf("请输入新增棋手的姓名：\n");
	scanf("%s", newPlayer.name);
	printf("请输入新增棋手的类型（0表示业余，1表示职业）：\n");
	scanf("%d", &newPlayer.classification);
	printf("请输入新增棋手的级别（1-27）：\n");
	printf("级别匹配如下：\n");
	printf("业余10级->1\t");printf("业余9级->2\t");printf("业余8级->3\t");printf("业余7级->4\n");
	printf("业余6级->5\t");printf("业余5级->6\t");printf("业余4级->7\t");printf("业余3级->8\n");
	printf("业余2级->9\t");printf("业余1级->10\t");printf("业余初段->11\t");printf("业余二段->12\n");
	printf("业余三段->13\t");printf("业余四段->14\t");printf("业余五段->15\t");printf("业余六段->16\n");
	printf("业余七段->17\t");printf("业余八段->18\t");printf("职业初段->19\t");printf("职业二段->20\n");
	printf("职业三段->21\t");printf("职业四段->22\t");printf("职业五段->23\t");printf("职业六段->24\n");
	printf("职业七段->25\t");printf("职业八段->26\t");printf("职业九段->27\n");
	scanf("%d", &newPlayer.level);
	printf("请输入新增棋手的等级分：\n");
	scanf("%d", &newPlayer.grade);
	}while(IsLegal(newPlayer.name,newPlayer.classification,newPlayer.level,newPlayer.grade));
	
	
	// 加入到 players 数组中
	players[count] = newPlayer;
	count++;
	
	// 将整个 players 数组写回到文件中
	fp=fopen(filename,"wb");//用wb打开而不是ab，是因为要重写整个文件，使用ab会导致数据重复！！ 
	fseek(fp, 0, SEEK_SET);
	fwrite(players, sizeof(struct GoPlayerType), count, fp);

	// 关闭文件
	fclose(fp);
	system("cls");
	printf("添加棋手成功！当前所有棋手信息如下：\n");
	ShowData(filename); 

}
	
//6.删除棋手信息 
void DeleteData(char* filename){
	struct GoPlayerType players[1000];//编号最大999，最多999人 
	//文件不存在或没打开,则返回。
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
	   	printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
    }
    //count得到该表棋手的数量。
    int count=0;	
	while(!feof(fp))
	{
	  	if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)//必须对fread的返回值进行判断，否则可能会将最后一条数据读2遍 
	 	{
		 	count++;
		}
	}
	fclose(fp);
	char tid[5];int flag=0;int find=0;
	printf("请输入要删除棋手的编号：\n");
	scanf("%s",tid);
	printf("该棋手信息如下，确定要删除吗？（输入1确认删除；输入0返回）\n");
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(strcmp(tid,players[i].id)==0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		find=1;//标记找到了 
		flag=i;//标记这个棋手在数组中的位置 
		}
	}
	if(find==0){
		printf("%-50|     没有找到您要删除的棋手信息，请核对后再试!");
		printf("    |\n");
		printf("+--------------------------------------------------+\n");
		system("pause");
		return ; 
	}
		
	int s;
	scanf("%d",&s);//输入1确认删除；输入0返回
	if(s!=1){
		return ;
	}else{
		for(int i=flag;i<count;i++){
			players[i]=players[i+1];
		}
	}
	count--;//总人数减一 
	
	fp=fopen(filename,"wb");
	fseek(fp,0,SEEK_SET);
	fwrite(players,sizeof(struct GoPlayerType),count,fp);
	fclose(fp);
	system("cls");
	printf("删除棋手信息成功！当前所有棋手信息如下：\n");
	ShowData(filename); 

}

//7.修改棋手信息
void ChangeData(char* filename){
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
	   	printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	
	struct GoPlayerType players[999];
	int count=0;	
	while(!feof(fp))
	{
	  	if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)
	 	{
		 	count++;
		}
	}	
	fclose(fp);
	
	char tid[5];int flag=0;int find=0;
	printf("请输入要修改棋手的编号：\n");
	scanf("%s",tid);
	printf("该棋手信息如下:\n");
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(strcmp(tid,players[i].id)==0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		find=1;//标记找到了 
		flag=i;//标记这个棋手在数组中的位置 
		}
	}
	if(find==0){
		printf("%-50|     没有找到您要删除的棋手信息，请核对后再试!");
		printf("    |\n");
		printf("+--------------------------------------------------+\n");
		system("pause");
		return ; 
	}
	
	// 新建一个棋手，替换原来的信息，不造轮子了，直接拿5的代码 
	printf("请输入棋手的新信息：\n");
	struct GoPlayerType newPlayer;
	printf("请输入新增棋手的编号,格式为PXXX,如P042(不可与已有编号重复):\n");
	
	strcpy(players[flag].id,"00000");//修改原来棋手的id，检验棋手id输入是否已经存在时就可以输入原来的id； 
	
	do{
		scanf("%s", newPlayer.id);
	}while(IdIsLegal(newPlayer.id));	//检验棋手id输入是否合法 
	
	for (int i = 0; i < count; i++) {
		if (strcmp(players[i].id, newPlayer.id) == 0) {
			printf("该编号已存在，请核对后再输入！\n");
			system("pause");
			return;
		}
	}
	
	do{
	printf("请输入新增棋手的姓名：\n");
	scanf("%s", newPlayer.name);
	printf("请输入新增棋手的类型（0表示业余，1表示职业）：\n");
	scanf("%d", &newPlayer.classification);
	printf("请输入新增棋手的级别（1-27）：\n");
	printf("级别匹配如下：\n");
	printf("业余10级->1\t");printf("业余9级->2\t");printf("业余8级->3\t");printf("业余7级->4\n");
	printf("业余6级->5\t");printf("业余5级->6\t");printf("业余4级->7\t");printf("业余3级->8\n");
	printf("业余2级->9\t");printf("业余1级->10\t");printf("业余初段->11\t");printf("业余二段->12\n");
	printf("业余三段->13\t");printf("业余四段->14\t");printf("业余五段->15\t");printf("业余六段->16\n");
	printf("业余七段->17\t");printf("业余八段->18\t");printf("职业初段->19\t");printf("职业二段->20\n");
	printf("职业三段->21\t");printf("职业四段->22\t");printf("职业五段->23\t");printf("职业六段->24\n");
	printf("职业七段->25\t");printf("职业八段->26\t");printf("职业九段->27\n");
	scanf("%d", &newPlayer.level);
	printf("请输入新增棋手的等级分：\n");
	scanf("%d", &newPlayer.grade);
	}while(IsLegal(newPlayer.name,newPlayer.classification,newPlayer.level,newPlayer.grade));
	
	players[flag]=newPlayer;//替换原来的信息
	 
	// 将整个 players 数组写回到文件中
	fp=fopen(filename,"wb");//用wb打开而不是ab，是因为要重写整个文件，使用ab会导致数据重复！！ 
	fseek(fp, 0, SEEK_SET);
	fwrite(players, sizeof(struct GoPlayerType), count, fp);

	// 关闭文件	
	fclose(fp); 
	system("cls");
	printf("修改棋手信息成功！当前所有棋手信息如下：\n");
	ShowData(filename);  
} 

//8.统计棋手信息
void CountData(char* filename){
	void NameQuary(char* filename); 
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
		printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	fclose(fp);
	
	printf("当前可按照以下三种方式进行统计:\n");
	printf("1.统计职业棋手人数\n");
	printf("2.统计业余棋手人数\n");
	printf("3.统计x等级分以上的人数\n");
	printf("0.返回主菜单\n");
	printf("\n请输入0~3\n");
	int select;
	while(1){
		scanf("%d",&select);
		if(select==1){
			CountPro(filename);
			break; 
		}else if(select==2){
			CountAma(filename);
			break;
		}else if(select==3){
			CountGrade(filename);
			break;
		}else if(select==0){
			return ;
		}
	}
}

//9.对棋手信息进行排序：
void SortData(char* filename){
	void NameQuary(char* filename); 
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
		printf("无数据，请使用功能2正确选择并导入棋手信息表！\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	fclose(fp);
	
	printf("1.所有棋手按等级分进行降序排序\n");
	printf("2.所有棋手按段位进行降序排序\n");
	printf("0.返回主菜单\n");
	printf("\n请输入0~2\n"); 
	int select;
	while(1){
		scanf("%d",&select);
		if(select==1){
			GradeSort(filename);
			break; 
		}else if(select==2){
			LevelSort(filename);
			break;
		}else if(select==0){
			return ;
		}
	}
	
} 

//10.退出 
void Exit(){
	int Ecmd;
	printf("是否确认退出系统？\n");
	printf("退出请输入1   返回主菜单请输入0;\n");
	scanf("%d",&Ecmd);
	if(Ecmd==1)
		exit(0);
	else{
		
		return;
	}
		
}

