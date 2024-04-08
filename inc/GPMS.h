#pragma once
#include<windows.h> 
#include <stdlib.h>
#include<stdio.h>
#include <dirent.h>
#include"GPtable.h"
#include<string.h>
/////////////////////////////////////////////////////////////////////
//GPMS.h��Ҫ����дmain�����е�10�����ܺ��� 
////////////////////////////////////////////////////////////////////


//���˵����棺
void ShowMenu(){
	printf("+--------------------------------------------------+\n");
	printf("|             ��ӭʹ��Χ�����ֹ���ϵͳ             |\n");
	printf("+--------------------------------------------------+\n");
	printf("|****        1. �½�������Ϣ��                 ****|\n");
	printf("|****        2. ѡ�񲢵���������Ϣ��           ****|\n");
	printf("|****        3. ��ʾ������Ϣ                   ****|\n");
	printf("|****        4. ��ѯ������Ϣ                   ****|\n");
	printf("|****        5. ����������Ϣ                   ****|\n");
	printf("|****        6. ɾ��������Ϣ                   ****|\n");
	printf("|****        7. �޸�������Ϣ                   ****|\n");
	printf("|****        8. ͳ��������Ϣ                   ****|\n");
	printf("|****        9. ��������Ϣ��������             ****|\n");
	printf("|****        10. �˳�ϵͳ                      ****|\n");
	printf("+--------------------------------------------------+\n");
	printf("��ѡ���ܣ�����1-10����\n"); 
	printf("*��ܰ��ʾ��*ʹ����Ϣǰ����ʹ�ù���2��������*\n");
	return;
} 

//1.�½�������Ϣ��
void CreateTable(){
	//�鿴Ŀ¼�� 
	struct dirent *de;  // Ŀ¼��ָ��
    DIR *dr = opendir("./datafiles");  // �򿪵�ǰĿ¼

    if (dr == NULL) {
        printf("�޷��򿪵�ǰĿ¼\n");
        return ;
    }
	printf("�Ѵ������±�,�����ظ�����\n"); 
    while ((de = readdir(dr)) != NULL) {  // ��ȡĿ¼�е��ļ�
        printf("%s\n", de->d_name);
    }
    closedir(dr);  // �ر�Ŀ¼
	printf("������Ҫ�½��ı�����(ʹ��.dat�ļ������±�����:XXX.dat)\n"); 
	char tname[50]="./datafiles/";
	char in[30]={0};
	scanf("%s",in);
	strcat(tname,in);
	
	//�½��� 
	FILE * tfp; 
	if ((tfp = fopen(tname, "wb")) == NULL) {
		printf("�ļ��½�ʧ��!\n"); 
		system("pause");
		return;
	}else
	{
		printf("�½���Ϣ��ɹ�!\n");
		system("pause");

	}
	fclose(tfp);

}

//2.ѡ�񲢵���������Ϣ��
void LoadTable(char * filename){
	//�鿴Ŀ¼�� 
	struct dirent *de;  // Ŀ¼��ָ��
    DIR *dr = opendir("./datafiles");  // �򿪵�ǰĿ¼

    if (dr == NULL) {
        printf("�޷��򿪵�ǰĿ¼\n");
        return ;
    }
	printf("�Ѵ������±�\n"); 
    while ((de = readdir(dr)) != NULL) {  // ��ȡĿ¼�е��ļ�
        printf("%s\n", de->d_name);
    }
    closedir(dr);  // �ر�Ŀ¼
    
	printf("������Ҫ�򿪵ı�����\n"); 
	char fname[50]="./datafiles/";
	char in[30]={0};
	scanf("%s",in);
	strcat(fname,in);//���Ϊ����·�� 
	strcpy(filename,fname);//��Ҫ�򿪵��ļ������䵽�������Թ������ļ�ʹ��
	
	//����������ļ��Ƿ����:
	FILE* tfp;
	if((tfp=fopen(filename,"rb"))==NULL)
	{
	   	printf("�ļ������ڣ����غ�����������!\n");
	   	system("pause");
	  	return;
    }else{
    	printf("�ļ�%s�ѳɹ���\n",in);
    	fclose(tfp);
    	system("pause");
	  	return;
	}
}

//3.��ʾ������Ϣ
void ShowData(char* filename){
	struct GoPlayerType players[1000];//������999�����999��
	//�ļ������ڻ�û��,�򷵻ء�
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
		printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
	   	system("pause");
	  	return;
	}
	//count�õ��ñ����ֵ�������
	int count=0;
	while(!feof(fp))
	{
		if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)//�����fread�ķ���ֵ�����жϣ�������ܻὫ���һ�����ݶ�2�� 
			count++;
	}
	fclose(fp);
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("%-50s", filename);  
	printf("|\n");  
	printf("+--------------------------------------------------+\n"); 
	printf("|"); 
	printf("�ñ�������������%-34d",count);
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
		free(level); // �ͷź����з�����ڴ�
	}
	if(count==0){
		printf("\n");
		printf("     **      �ñ��������κ�������Ϣ       **\n");
	}
	system("pause");	
}

//4.��ѯ������Ϣ 
void QuaryData(char* filename){
	void NameQuary(char* filename); 
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
		printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	fclose(fp);
	printf("1.������������ѯ(��ģ����ѯ)\n");
	printf("2.��������ݲ�ѯ\n");
	printf("3.�����ֶ�λ��ѯ\n");
	printf("0.�����ϼ��˵�\n");
	printf("\n������0~3\n");
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

//5.����������Ϣ
void AddData(char* filename){
	struct GoPlayerType players[1000];//������999�����999�� 
	//�ļ������ڻ�û��,�򷵻ء�
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
	   	printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
    }
    //count�õ��ñ����ֵ�������
    int count=0;	
	while(!feof(fp))
	{
	  	if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)//�����fread�ķ���ֵ�����жϣ�������ܻὫ���һ�����ݶ�2�� 
	 	{
		 	count++;
		}
	}
	fclose(fp);
	
	// ����������Ϣ
	struct GoPlayerType newPlayer;
	printf("�������������ֵı��,��ʽΪPXXX,��P042(���������б���ظ�):\n");
	
	do{
		scanf("%s", newPlayer.id);
	}while(IdIsLegal(newPlayer.id));	//��������id�����Ƿ�Ϸ� 
	
	for (int i = 0; i < count; i++) {
		if (strcmp(players[i].id, newPlayer.id) == 0) {
			printf("�ñ���Ѵ��ڣ���˶Ժ���������֣�\n");
			system("pause");
			return;
		}
	}
	
	do{
	printf("�������������ֵ�������\n");
	scanf("%s", newPlayer.name);
	printf("�������������ֵ����ͣ�0��ʾҵ�࣬1��ʾְҵ����\n");
	scanf("%d", &newPlayer.classification);
	printf("�������������ֵļ���1-27����\n");
	printf("����ƥ�����£�\n");
	printf("ҵ��10��->1\t");printf("ҵ��9��->2\t");printf("ҵ��8��->3\t");printf("ҵ��7��->4\n");
	printf("ҵ��6��->5\t");printf("ҵ��5��->6\t");printf("ҵ��4��->7\t");printf("ҵ��3��->8\n");
	printf("ҵ��2��->9\t");printf("ҵ��1��->10\t");printf("ҵ�����->11\t");printf("ҵ�����->12\n");
	printf("ҵ������->13\t");printf("ҵ���Ķ�->14\t");printf("ҵ�����->15\t");printf("ҵ������->16\n");
	printf("ҵ���߶�->17\t");printf("ҵ��˶�->18\t");printf("ְҵ����->19\t");printf("ְҵ����->20\n");
	printf("ְҵ����->21\t");printf("ְҵ�Ķ�->22\t");printf("ְҵ���->23\t");printf("ְҵ����->24\n");
	printf("ְҵ�߶�->25\t");printf("ְҵ�˶�->26\t");printf("ְҵ�Ŷ�->27\n");
	scanf("%d", &newPlayer.level);
	printf("�������������ֵĵȼ��֣�\n");
	scanf("%d", &newPlayer.grade);
	}while(IsLegal(newPlayer.name,newPlayer.classification,newPlayer.level,newPlayer.grade));
	
	
	// ���뵽 players ������
	players[count] = newPlayer;
	count++;
	
	// ������ players ����д�ص��ļ���
	fp=fopen(filename,"wb");//��wb�򿪶�����ab������ΪҪ��д�����ļ���ʹ��ab�ᵼ�������ظ����� 
	fseek(fp, 0, SEEK_SET);
	fwrite(players, sizeof(struct GoPlayerType), count, fp);

	// �ر��ļ�
	fclose(fp);
	system("cls");
	printf("������ֳɹ�����ǰ����������Ϣ���£�\n");
	ShowData(filename); 

}
	
//6.ɾ��������Ϣ 
void DeleteData(char* filename){
	struct GoPlayerType players[1000];//������999�����999�� 
	//�ļ������ڻ�û��,�򷵻ء�
	FILE* fp;
	if((fp=fopen(filename,"rb"))==NULL)
	{
	   	printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
    }
    //count�õ��ñ����ֵ�������
    int count=0;	
	while(!feof(fp))
	{
	  	if(fread(&players[count],sizeof(struct GoPlayerType),1,fp)==1)//�����fread�ķ���ֵ�����жϣ�������ܻὫ���һ�����ݶ�2�� 
	 	{
		 	count++;
		}
	}
	fclose(fp);
	char tid[5];int flag=0;int find=0;
	printf("������Ҫɾ�����ֵı�ţ�\n");
	scanf("%s",tid);
	printf("��������Ϣ���£�ȷ��Ҫɾ���𣿣�����1ȷ��ɾ��������0���أ�\n");
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(strcmp(tid,players[i].id)==0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		find=1;//����ҵ��� 
		flag=i;//�����������������е�λ�� 
		}
	}
	if(find==0){
		printf("%-50|     û���ҵ���Ҫɾ����������Ϣ����˶Ժ�����!");
		printf("    |\n");
		printf("+--------------------------------------------------+\n");
		system("pause");
		return ; 
	}
		
	int s;
	scanf("%d",&s);//����1ȷ��ɾ��������0����
	if(s!=1){
		return ;
	}else{
		for(int i=flag;i<count;i++){
			players[i]=players[i+1];
		}
	}
	count--;//��������һ 
	
	fp=fopen(filename,"wb");
	fseek(fp,0,SEEK_SET);
	fwrite(players,sizeof(struct GoPlayerType),count,fp);
	fclose(fp);
	system("cls");
	printf("ɾ��������Ϣ�ɹ�����ǰ����������Ϣ���£�\n");
	ShowData(filename); 

}

//7.�޸�������Ϣ
void ChangeData(char* filename){
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
	   	printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
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
	printf("������Ҫ�޸����ֵı�ţ�\n");
	scanf("%s",tid);
	printf("��������Ϣ����:\n");
	printf("+--------------------------------------------------+\n"); 	
	printf("|%-9s|%-9s|%-9s|%-9s|%-10s|\n","  ���","  ����","  ���","  ��λ","  �ȼ���");
	printf("+--------------------------------------------------+\n");
	for(int i=0;i<count;i++){
		if(strcmp(tid,players[i].id)==0){
		char* level=Levelstr(players[i].level);
		printf("|%-9s",players[i].id);
		printf("|%-9s",players[i].name);	
		printf("|%-9s",players[i].classification==1?"ְҵ":"ҵ��");
		printf("|%-9s",level);
		printf("|%-10d|\n",players[i].grade);
		printf("+--------------------------------------------------+\n"); 
		free(level);
		find=1;//����ҵ��� 
		flag=i;//�����������������е�λ�� 
		}
	}
	if(find==0){
		printf("%-50|     û���ҵ���Ҫɾ����������Ϣ����˶Ժ�����!");
		printf("    |\n");
		printf("+--------------------------------------------------+\n");
		system("pause");
		return ; 
	}
	
	// �½�һ�����֣��滻ԭ������Ϣ�����������ˣ�ֱ����5�Ĵ��� 
	printf("���������ֵ�����Ϣ��\n");
	struct GoPlayerType newPlayer;
	printf("�������������ֵı��,��ʽΪPXXX,��P042(���������б���ظ�):\n");
	
	strcpy(players[flag].id,"00000");//�޸�ԭ�����ֵ�id����������id�����Ƿ��Ѿ�����ʱ�Ϳ�������ԭ����id�� 
	
	do{
		scanf("%s", newPlayer.id);
	}while(IdIsLegal(newPlayer.id));	//��������id�����Ƿ�Ϸ� 
	
	for (int i = 0; i < count; i++) {
		if (strcmp(players[i].id, newPlayer.id) == 0) {
			printf("�ñ���Ѵ��ڣ���˶Ժ������룡\n");
			system("pause");
			return;
		}
	}
	
	do{
	printf("�������������ֵ�������\n");
	scanf("%s", newPlayer.name);
	printf("�������������ֵ����ͣ�0��ʾҵ�࣬1��ʾְҵ����\n");
	scanf("%d", &newPlayer.classification);
	printf("�������������ֵļ���1-27����\n");
	printf("����ƥ�����£�\n");
	printf("ҵ��10��->1\t");printf("ҵ��9��->2\t");printf("ҵ��8��->3\t");printf("ҵ��7��->4\n");
	printf("ҵ��6��->5\t");printf("ҵ��5��->6\t");printf("ҵ��4��->7\t");printf("ҵ��3��->8\n");
	printf("ҵ��2��->9\t");printf("ҵ��1��->10\t");printf("ҵ�����->11\t");printf("ҵ�����->12\n");
	printf("ҵ������->13\t");printf("ҵ���Ķ�->14\t");printf("ҵ�����->15\t");printf("ҵ������->16\n");
	printf("ҵ���߶�->17\t");printf("ҵ��˶�->18\t");printf("ְҵ����->19\t");printf("ְҵ����->20\n");
	printf("ְҵ����->21\t");printf("ְҵ�Ķ�->22\t");printf("ְҵ���->23\t");printf("ְҵ����->24\n");
	printf("ְҵ�߶�->25\t");printf("ְҵ�˶�->26\t");printf("ְҵ�Ŷ�->27\n");
	scanf("%d", &newPlayer.level);
	printf("�������������ֵĵȼ��֣�\n");
	scanf("%d", &newPlayer.grade);
	}while(IsLegal(newPlayer.name,newPlayer.classification,newPlayer.level,newPlayer.grade));
	
	players[flag]=newPlayer;//�滻ԭ������Ϣ
	 
	// ������ players ����д�ص��ļ���
	fp=fopen(filename,"wb");//��wb�򿪶�����ab������ΪҪ��д�����ļ���ʹ��ab�ᵼ�������ظ����� 
	fseek(fp, 0, SEEK_SET);
	fwrite(players, sizeof(struct GoPlayerType), count, fp);

	// �ر��ļ�	
	fclose(fp); 
	system("cls");
	printf("�޸�������Ϣ�ɹ�����ǰ����������Ϣ���£�\n");
	ShowData(filename);  
} 

//8.ͳ��������Ϣ
void CountData(char* filename){
	void NameQuary(char* filename); 
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
		printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	fclose(fp);
	
	printf("��ǰ�ɰ����������ַ�ʽ����ͳ��:\n");
	printf("1.ͳ��ְҵ��������\n");
	printf("2.ͳ��ҵ����������\n");
	printf("3.ͳ��x�ȼ������ϵ�����\n");
	printf("0.�������˵�\n");
	printf("\n������0~3\n");
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

//9.��������Ϣ��������
void SortData(char* filename){
	void NameQuary(char* filename); 
	FILE * fp;
	if((fp=fopen(filename,"rb"))==NULL){
		printf("�����ݣ���ʹ�ù���2��ȷѡ�񲢵���������Ϣ��\n");
	   	system("pause");
	   	fclose(fp);
	  	return;
	}
	fclose(fp);
	
	printf("1.�������ְ��ȼ��ֽ��н�������\n");
	printf("2.�������ְ���λ���н�������\n");
	printf("0.�������˵�\n");
	printf("\n������0~2\n"); 
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

//10.�˳� 
void Exit(){
	int Ecmd;
	printf("�Ƿ�ȷ���˳�ϵͳ��\n");
	printf("�˳�������1   �������˵�������0;\n");
	scanf("%d",&Ecmd);
	if(Ecmd==1)
		exit(0);
	else{
		
		return;
	}
		
}

