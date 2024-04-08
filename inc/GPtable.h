#pragma once
#include<windows.h> 
#include <stdlib.h>
#include<stdio.h>

/////////////////////////////////////////////////////////////////////
//GPtable.h主要用于写有关棋手数据的结构与函数 
////////////////////////////////////////////////////////////////////
//枚举棋手类型 
enum Class{ama=0,Pro=1};
//围棋棋手数据结构:
struct GoPlayerType
{
	char id[5];//P+XXX,四位id一位\0； 
	char name[20];//姓名 
	enum Class classification;//0为业余，1为 职业 
	int level;//1-27对应业余10级->业余8段- >职业初段->职业九段 
	int grade;//存储等级分	
}; 

//检验棋手id输入是否合法 
int IdIsLegal(char* id){
	if(id[0]!='P'||strlen(id)!=4){
		printf("id输入不合法，请重新输入!\n");
		return 1;
	}
	else if(id[1] < '0' || id[1] > '9'|| id[2] < '0' || id[2] > '9'|| id[3] < '0' || id[3] > '9'){//后三位必须是数字 
		printf("id输入不合法，请重新输入!\n");
		return 1;
		}
    else {
    	//printf("id输入合法\n");
    	return 0; 
	}
			
}

//检验棋手其他信息输入是否合法 
int IsLegal( char* name, enum Class classification, int level, int grade) {
    if (strlen(name) == 0) {
    	printf("姓名不能为空，请重新输入!\n");
		return 1;  
    }
    if (classification != 0 && classification != 1) {
        printf("棋手类型输入不合法，请重新输入!\n");
		return 1;  // 类型只能是 0 或 1
    }
    if ((classification==0)&&(level < 1 || level > 18)) {
        printf("级别输入不合法，请重新输入!\n");
		return 1;  // 段位范围不正确
    }
    if ((classification==1)&&(level < 19 || level > 27)) {
        printf("级别输入不合法，请重新输入!\n");
		return 1;  // 段位范围不正确
    }
    if (grade < 0) {
        printf("等级分输入不合法，请重新输入!\n");
		return 1;  // 等级分不能小于 0
    }

    return 0;
}

//将段位的数字信息匹配为字符串:
char* Levelstr(int l){
	char* str = malloc(20);  // 分配足够的内存
	if(l==1){
		strcpy(str,"10级");			
	}else if(l==2){
		strcpy(str,"9级");	
	}else if(l==3){
		strcpy(str,"8级");	
	}else if(l==4){
		strcpy(str,"7级");	
	}else if(l==5){
		strcpy(str,"6级");	
	}else if(l==6){
		strcpy(str,"5级");	
	}else if(l==7){
		strcpy(str,"4级");	
	}else if(l==8){
		strcpy(str,"3级");	
	}else if(l==9){
		strcpy(str,"2级");
	}else if(l==10){
		strcpy(str,"1级");		
	}else if(l==11||l==19){
		strcpy(str,"初段");	
	}else if(l==12||l==20){
		strcpy(str,"二段");	
	}else if(l==13||l==21){
		strcpy(str,"三段");	
	}else if(l==14||l==22){
		strcpy(str,"四段");	
	}else if(l==15||l==23){
		strcpy(str,"五段");	
	}else if(l==16||l==24){
		strcpy(str,"六段");	
	}else if(l==17||l==25){
		strcpy(str,"七段");	
	}else if(l==18||l==26){
		strcpy(str,"八段");	
	}else if(l==27){
		strcpy(str,"九段");	
	}
	return str; 
} 

//4.1.按棋手姓名查询
void NameQuary(char* filename){
	struct GoPlayerType players[1000];//编号最大999，最多999人 
	FILE * fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp)){
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1){
			count++;
		}
	}
	fclose(fp);
	
	char qname[20];
	printf("请输入要查询棋手的姓名(或其中的部分汉字)：\n");
	scanf("%s",qname);
	
	//标注字符串匹配符，用flagcount数组记录对应棋手姓名匹配度
	int flagcount[1000]={0}; 
	int isize=strlen(qname);
	for(int i=0;i<count;i++){
		for(int j=0;j<isize;j+=2){
			int tsize=strlen(players[i].name);
			for(int k=0;k<tsize;k+=2){
				if(qname[j]==players[i].name[k]&&qname[j+1]==players[i].name[k+1])
					flagcount[i]++;
			}
		}
	}
	
	//根据匹配度对棋手进行降序排序，以防出现输入准确名字但是该棋手结果去排在后边的情况
	for(int i=0;i<count-1;i++){
		for(int j=0;j<count-1-i;j++){
			if(flagcount[j]<flagcount[j+1]){
				//交换对应棋手信息 
				struct GoPlayerType t=players[j];
				players[j]=players[j+1];
				players[j+1]=t;
				
				//交换对应匹配度 
				int temp=flagcount[j];
				flagcount[j]=flagcount[j+1];
				flagcount[j+1]=temp; 
			}
		}
	}

	//输出排序后的结果 ,输出条件为匹配度不为0 
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(flagcount[i]>0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		//printf("flagcount=%d\n",flagcount[i]);
		free(level);
		flag++;
		}
	}
	printf("查询记录共%d条\n",flag);
	system("pause");
}
//4.2.按棋手身份查询
void classificationQuary(char* filename){
	struct GoPlayerType players[999];
	
	FILE* fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp)){
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1){
			count++;
		}	
	}
	fclose(fp);
	
	int t;
	printf("请输入要查询棋手的类别(职业->1；业余->0)：\n");
	scanf("%d",&t);
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(t==players[i].classification){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("查询记录共%d条\n",flag);
	system("pause");
}
//4.3.按棋手段位查询
void LevelQuary(char * filename){
	struct GoPlayerType players[999];
	FILE* fp;
	fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp))
	{
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)
			count++;
	}
	fclose(fp);
	
	int l;
	printf("请输入要查询棋手的段位：\n");
	printf("级别匹配如下：\n");
	printf("业余10级->1\t");printf("业余9级->2\t");printf("业余8级->3\t");printf("业余7级->4\n");
	printf("业余6级->5\t");printf("业余5级->6\t");printf("业余4级->7\t");printf("业余3级->8\n");
	printf("业余2级->9\t");printf("业余1级->10\t");printf("业余初段->11\t");printf("业余二段->12\n");
	printf("业余三段->13\t");printf("业余四段->14\t");printf("业余五段->15\t");printf("业余六段->16\n");
	printf("业余七段->17\t");printf("业余八段->18\t");printf("职业初段->19\t");printf("职业二段->20\n");
	printf("职业三段->21\t");printf("职业四段->22\t");printf("职业五段->23\t");printf("职业六段->24\n");
	printf("职业七段->25\t");printf("职业八段->26\t");printf("职业九段->27\n");
	scanf("%d",&l);
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(l==players[i].level){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("查询记录共%d条\n",flag);
	system("pause");
}

//8.1统计职业棋手人数：
void CountPro(char* filename){
	struct GoPlayerType players[999];
	
	FILE* fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp)){
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1){
			count++;
		}	
	}
	fclose(fp);
	
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(players[i].classification==1){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("\n"); 
	printf("     **  统计结果：职业棋手人数：%d人 !   **",flag);
	printf("\n");
	printf("\n");
	system("pause");
}
//8.2统计业余棋手人数:
void CountAma(char* filename){
	struct GoPlayerType players[999];
	
	FILE* fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp)){
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1){
			count++;
		}	
	}
	fclose(fp);
	
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(players[i].classification==0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("\n"); 
	printf("     **  统计结果：业余棋手人数：%d人 !   **",flag);
	printf("\n");
	printf("\n");
	system("pause");
}
//8.3统计x等级分以上的人数:
void CountGrade(char* filename){
	struct GoPlayerType players[999];
	
	FILE* fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp)){
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1){
			count++;
		}	
	}
	fclose(fp);
	
	int gra;
	printf("请输入等级分x，将为你统计x分以上的棋手:\n");
	scanf("%d",&gra);
	
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  编号","  姓名","  类别","  段位","  等级分");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(players[i].grade>gra){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"职业":"业余");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("\n"); 
	printf("     **  统计结果：%d分以上的棋手：%d人 !   **",gra,flag);
	printf("\n");
	printf("\n");
	system("pause");
}

//9.1所有棋手按等级分进行降序排序:

void GetIdNum(char* num, struct GoPlayerType* p){ //使用了结构体指针传参已获得ID字符串的后三位数字，以此进行大小比较 
    num[0] = p->id[1];
    num[1] = p->id[2];
    num[2] = p->id[3];
    num[3] = p->id[4];
}

void GradeSort(char* filename){
	struct GoPlayerType players[1000];
	FILE *fp;
	fp=fopen(filename,"rb");
	int count=0;
	while(!feof(fp))
	{
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)
			count++;
	}
	fclose(fp);
	
	for(int i=0;i<count-1;i++){
		for(int j =0;j<count-1-i;j++){
			if(players[j].grade<players[j+1].grade){
				struct GoPlayerType t=players[j];
				players[j]=players[j+1];
				players[j+1]=t;
			}else if(players[j].level==players[j+1].level){
				//取出棋手编号的后三位数字 
				char num1[4],num2[4];
				GetIdNum(num1,&players[j]);
				GetIdNum(num2,&players[j+1]);
				
				if(strcmp(num1,num2)>0){
					struct GoPlayerType t=players[j];
					players[j]=players[j+1];
					players[j+1]=t;
				}
			}
		}
	}
	
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
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
		free(level);
	}
	system("pause");
}
	
//9.2.所有棋手按段位进行降序排序:
void LevelSort(char* filename){
	struct GoPlayerType players[1000];
	FILE *fp;
	fp=fopen(filename,"rb");
	int count=0;
	while(!feof(fp))
	{
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)
			count++;
	}
	fclose(fp);
	
	for(int i=0;i<count-1;i++){
		for(int j =0;j<count-1-i;j++){
			if(players[j].level<players[j+1].level){
				struct GoPlayerType t=players[j];
				players[j]=players[j+1];
				players[j+1]=t;
			}else if(players[j].level==players[j+1].level){
				//取出棋手编号的后三位数字  
				char num1[4],num2[4];
				GetIdNum(num1,&players[j]);
				GetIdNum(num2,&players[j+1]);
				if(strcmp(num1,num2)>0){
					struct GoPlayerType t=players[j];
					players[j]=players[j+1];
					players[j+1]=t;
				}
			}
		}
	}
	
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
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
		free(level);
	}
	system("pause");
}


