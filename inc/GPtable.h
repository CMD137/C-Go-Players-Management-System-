#pragma once
#include<windows.h> 
#include <stdlib.h>
#include<stdio.h>

/////////////////////////////////////////////////////////////////////
//GPtable.h��Ҫ����д�й��������ݵĽṹ�뺯�� 
////////////////////////////////////////////////////////////////////
//ö���������� 
enum Class{ama=0,Pro=1};
//Χ���������ݽṹ:
struct GoPlayerType
{
	char id[5];//P+XXX,��λidһλ\0�� 
	char name[20];//���� 
	enum Class classification;//0Ϊҵ�࣬1Ϊ ְҵ 
	int level;//1-27��Ӧҵ��10��->ҵ��8��- >ְҵ����->ְҵ�Ŷ� 
	int grade;//�洢�ȼ���	
}; 

//��������id�����Ƿ�Ϸ� 
int IdIsLegal(char* id){
	if(id[0]!='P'||strlen(id)!=4){
		printf("id���벻�Ϸ�������������!\n");
		return 1;
	}
	else if(id[1] < '0' || id[1] > '9'|| id[2] < '0' || id[2] > '9'|| id[3] < '0' || id[3] > '9'){//����λ���������� 
		printf("id���벻�Ϸ�������������!\n");
		return 1;
		}
    else {
    	//printf("id����Ϸ�\n");
    	return 0; 
	}
			
}

//��������������Ϣ�����Ƿ�Ϸ� 
int IsLegal( char* name, enum Class classification, int level, int grade) {
    if (strlen(name) == 0) {
    	printf("��������Ϊ�գ�����������!\n");
		return 1;  
    }
    if (classification != 0 && classification != 1) {
        printf("�����������벻�Ϸ�������������!\n");
		return 1;  // ����ֻ���� 0 �� 1
    }
    if ((classification==0)&&(level < 1 || level > 18)) {
        printf("�������벻�Ϸ�������������!\n");
		return 1;  // ��λ��Χ����ȷ
    }
    if ((classification==1)&&(level < 19 || level > 27)) {
        printf("�������벻�Ϸ�������������!\n");
		return 1;  // ��λ��Χ����ȷ
    }
    if (grade < 0) {
        printf("�ȼ������벻�Ϸ�������������!\n");
		return 1;  // �ȼ��ֲ���С�� 0
    }

    return 0;
}

//����λ��������Ϣƥ��Ϊ�ַ���:
char* Levelstr(int l){
	char* str = malloc(20);  // �����㹻���ڴ�
	if(l==1){
		strcpy(str,"10��");			
	}else if(l==2){
		strcpy(str,"9��");	
	}else if(l==3){
		strcpy(str,"8��");	
	}else if(l==4){
		strcpy(str,"7��");	
	}else if(l==5){
		strcpy(str,"6��");	
	}else if(l==6){
		strcpy(str,"5��");	
	}else if(l==7){
		strcpy(str,"4��");	
	}else if(l==8){
		strcpy(str,"3��");	
	}else if(l==9){
		strcpy(str,"2��");
	}else if(l==10){
		strcpy(str,"1��");		
	}else if(l==11||l==19){
		strcpy(str,"����");	
	}else if(l==12||l==20){
		strcpy(str,"����");	
	}else if(l==13||l==21){
		strcpy(str,"����");	
	}else if(l==14||l==22){
		strcpy(str,"�Ķ�");	
	}else if(l==15||l==23){
		strcpy(str,"���");	
	}else if(l==16||l==24){
		strcpy(str,"����");	
	}else if(l==17||l==25){
		strcpy(str,"�߶�");	
	}else if(l==18||l==26){
		strcpy(str,"�˶�");	
	}else if(l==27){
		strcpy(str,"�Ŷ�");	
	}
	return str; 
} 

//4.1.������������ѯ
void NameQuary(char* filename){
	struct GoPlayerType players[1000];//������999�����999�� 
	FILE * fp=fopen(filename,"rb");
	int count=0;int flag=0;
	while(!feof(fp)){
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1){
			count++;
		}
	}
	fclose(fp);
	
	char qname[20];
	printf("������Ҫ��ѯ���ֵ�����(�����еĲ��ֺ���)��\n");
	scanf("%s",qname);
	
	//��ע�ַ���ƥ�������flagcount�����¼��Ӧ��������ƥ���
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
	
	//����ƥ��ȶ����ֽ��н��������Է���������׼ȷ���ֵ��Ǹ����ֽ��ȥ���ں�ߵ����
	for(int i=0;i<count-1;i++){
		for(int j=0;j<count-1-i;j++){
			if(flagcount[j]<flagcount[j+1]){
				//������Ӧ������Ϣ 
				struct GoPlayerType t=players[j];
				players[j]=players[j+1];
				players[j+1]=t;
				
				//������Ӧƥ��� 
				int temp=flagcount[j];
				flagcount[j]=flagcount[j+1];
				flagcount[j+1]=temp; 
			}
		}
	}

	//��������Ľ�� ,�������Ϊƥ��Ȳ�Ϊ0 
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(flagcount[i]>0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		//printf("flagcount=%d\n",flagcount[i]);
		free(level);
		flag++;
		}
	}
	printf("��ѯ��¼��%d��\n",flag);
	system("pause");
}
//4.2.��������ݲ�ѯ
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
	printf("������Ҫ��ѯ���ֵ����(ְҵ->1��ҵ��->0)��\n");
	scanf("%d",&t);
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(t==players[i].classification){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("��ѯ��¼��%d��\n",flag);
	system("pause");
}
//4.3.�����ֶ�λ��ѯ
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
	printf("������Ҫ��ѯ���ֵĶ�λ��\n");
	printf("����ƥ�����£�\n");
	printf("ҵ��10��->1\t");printf("ҵ��9��->2\t");printf("ҵ��8��->3\t");printf("ҵ��7��->4\n");
	printf("ҵ��6��->5\t");printf("ҵ��5��->6\t");printf("ҵ��4��->7\t");printf("ҵ��3��->8\n");
	printf("ҵ��2��->9\t");printf("ҵ��1��->10\t");printf("ҵ�����->11\t");printf("ҵ�����->12\n");
	printf("ҵ������->13\t");printf("ҵ���Ķ�->14\t");printf("ҵ�����->15\t");printf("ҵ������->16\n");
	printf("ҵ���߶�->17\t");printf("ҵ��˶�->18\t");printf("ְҵ����->19\t");printf("ְҵ����->20\n");
	printf("ְҵ����->21\t");printf("ְҵ�Ķ�->22\t");printf("ְҵ���->23\t");printf("ְҵ����->24\n");
	printf("ְҵ�߶�->25\t");printf("ְҵ�˶�->26\t");printf("ְҵ�Ŷ�->27\n");
	scanf("%d",&l);
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(l==players[i].level){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("��ѯ��¼��%d��\n",flag);
	system("pause");
}

//8.1ͳ��ְҵ����������
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
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(players[i].classification==1){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("\n"); 
	printf("     **  ͳ�ƽ����ְҵ����������%d�� !   **",flag);
	printf("\n");
	printf("\n");
	system("pause");
}
//8.2ͳ��ҵ����������:
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
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(players[i].classification==0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("\n"); 
	printf("     **  ͳ�ƽ����ҵ������������%d�� !   **",flag);
	printf("\n");
	printf("\n");
	system("pause");
}
//8.3ͳ��x�ȼ������ϵ�����:
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
	printf("������ȼ���x����Ϊ��ͳ��x�����ϵ�����:\n");
	scanf("%d",&gra);
	
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(players[i].grade>gra){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		flag++;
		}
	}
	printf("\n"); 
	printf("     **  ͳ�ƽ����%d�����ϵ����֣�%d�� !   **",gra,flag);
	printf("\n");
	printf("\n");
	system("pause");
}

//9.1�������ְ��ȼ��ֽ��н�������:

void GetIdNum(char* num, struct GoPlayerType* p){ //ʹ���˽ṹ��ָ�봫���ѻ��ID�ַ����ĺ���λ���֣��Դ˽��д�С�Ƚ� 
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
				//ȡ�����ֱ�ŵĺ���λ���� 
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
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
	}
	system("pause");
}
	
//9.2.�������ְ���λ���н�������:
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
				//ȡ�����ֱ�ŵĺ���λ����  
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
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
	}
	system("pause");
}


