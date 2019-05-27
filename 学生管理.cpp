#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#define MAX 100

typedef struct student
{
	char name[MAX];
	int xuehao;
	int age;
	int socer;
}STU;

typedef struct line
{
	STU stu;
	struct line * next;
}NODE,* PNODE;

int menu_start();//��ʼ�˵�
bool fr_fristnode();//���ļ���ȡͷ�ڵ�(���򷵻�) 
PNODE Creatfristnode();//����ͷ�ڵ�(�ļ�û��ʱ)
void inputSTU();//¼��
char * s_gets(char * s,int n);//¼������ 
void fw_stu(PNODE f_fristnode);//���ļ�д��¼��� 
void Insertlastnode(STU * p);//��ͷ����
PNODE Creatnode(STU * p);//�����ڵ� 

int menu_delete();//ɾ���˵�
void deleteSTU(int chose_delete);//�ж�ɾ���� ѧ��
void Deletenode_name(PNODE fristnode,char * ch);//ɾ������
void Deletenode_num(PNODE fristnode,int m);//ɾ��ѧ�� 
 
int menu_paixu();//�������˵�
void scanSTU(int chose_paixu);//���ļ�������ȶ�ȡ(��������ʽ)
void paixu(PNODE fristnode,int chose_paixu,int sum);//����ͬ��ʽ���� 
 
void modifySTU();//�����޸ĵ����� 
void Modifynode_socer(PNODE fristnode,char * p);

int main ()
{
 	bool fristnode;
 	fristnode=fr_fristnode();
 	
 	if(fristnode==false)
 	  fristnode=Creatfristnode();
 	while(1)
	 {
	      int chose_start=menu_start();
 	      int chose_delete;
 	      int chose_paixu; 
 	      switch (chose_start)
 	      {
 		     case 1: inputSTU(); 
		              break;
 		     case 2: chose_delete=menu_delete();
		             deleteSTU(chose_delete);
 		              break;
 		     case 3: chose_paixu=menu_paixu(); 
		              scanSTU(chose_paixu);
 		              break;
 		     case 4: modifySTU();   
		              break; 
		     default: printf("\n\n��лʹ��!");
					  exit(0); 
 	     }
 	     system("pause");
     }
 	return 0;
}
 
int menu_start()//��ʼ�˵� 
 {
 	system("CLS");
 	int chose;
 	printf(" *��ӭʹ��ѧ������ϵͳ*\n");
 	printf(" \n (1).����¼��ѧ����Ϣ\n (2).ɾ������ѧ����Ϣ\n (3).�������ѧ����Ϣ\n (4).�޸�����ѧ���ɼ�\n\n��ѡ��(����������˳�):");
	scanf("%d",&chose);
	getchar();
	return chose; 
 }
 
bool fr_fristnode()//���ļ���ȡͷ�ڵ�
{
 	FILE * fp;
 	if((fp=fopen("student.dat","a+b"))==NULL)
 	{
 		printf("�ļ���ʧ��\n");
		return false;
	 }
	 NODE fristnode;
	 if(fread(&fristnode,sizeof(NODE),1,fp)==0)
	 {
	 	//printf("��û�д�����Ϣ\n");
		 fclose(fp); 
	     return false;
	 }
	 fclose(fp);
	 return true;
}

PNODE Creatfristnode()//����ͷ�ڵ�(�ļ�û��ʱ) 
{
	PNODE fristnode;
	fristnode=(PNODE)malloc(sizeof(NODE));
	if(fristnode==NULL)
	{
		printf("��������ʧ��");
		system("pause");
		exit(0); 
    }
    fristnode->next=NULL;
    fw_stu(fristnode);
    return fristnode;
}

void inputSTU()//¼�� 
{
 	STU p;
 	system("CLS"); 
 	printf("�밴��ʾ����¼��\n\n");
 	printf("����������[��[Enter]�˳�]��");
	while(s_gets(p.name,MAX) != NULL && p.name[0] !='\0')
	{  
	    printf("���������䣺");
	    scanf("%d",&p.age);
	    printf("������ѧ�ţ�");
	    scanf("%d",&p.xuehao);
	    printf("������ɼ���");
	    scanf("%d",&p.socer);
	    fflush(stdin);
	  //  printf("00");
	    Insertlastnode(&p);
	    printf("\n����������(��[Enter]�˳�)��"); 
     }
     printf("\n\n¼��ɹ�\n\n"); 
}


char * s_gets(char * s,int n)
{
    char * p;
	char * find;
	p=fgets(s,n,stdin);
	if(p)
	{
		find=strchr(s,'\n');
		if(find)
		   *find='\0';
		else
		   while(getchar()!='\n')
		     continue;
	}	
	return p;
}

void fw_stu(PNODE f_fristnode)//���ļ�д��¼��� 
{
	FILE * fp;
	if((fp=fopen("student.dat","wb"))==NULL)
	{
		printf("����ʧ��");
		return; 
	}
	while(f_fristnode!=NULL)
	{
	//	printf("%d\t",f_fristnode->stu.age);
		fwrite(f_fristnode,sizeof(NODE),1,fp);
		f_fristnode=f_fristnode->next;
	}
	fclose(fp);
} 
 
 void Insertlastnode(STU * p)//��β���� 
{
     FILE * fp;
	if((fp=fopen("student.dat","a+b"))==NULL)
 	{
 		printf("�ļ���ʧ��");
		return ; 
	 }	 
	 PNODE fristnode,frontnode,tailnode;
	 NODE checknode;
	 fristnode=(PNODE)malloc(sizeof(NODE));
	 int sum=0;
	 while(fread(&checknode,sizeof(NODE),1,fp) != 0)
	   ++sum;
	 fseek(fp,0l,SEEK_SET);
	 fread(fristnode,sizeof(NODE),1,fp);
	 frontnode=fristnode;
	 for(int i=1;i<=sum-1;i++)
	 {
//	 	printf("%d\n",++i);
	 	tailnode=(PNODE)malloc(sizeof(NODE));
	 	fread(tailnode,sizeof(NODE),1,fp);
	 	tailnode->next=NULL;
		 frontnode->next=tailnode;
		 frontnode=tailnode;
	 }
	 fclose(fp);
	 if(sum==1)
	   frontnode->next=Creatnode(p);
	 else
	   tailnode->next=Creatnode(p);
	 fw_stu(fristnode);
} 
  
PNODE Creatnode(STU * p)//�����ڵ� 
{
	PNODE node; 
	node=(PNODE)malloc(sizeof(NODE));
	strcpy(node->stu.name,p->name);
	node->stu.xuehao=p->xuehao;
	node->stu.age=p->age;
	node->stu.socer=p->socer;
	node->next=NULL;
	return node;
}


int menu_delete()//ɾ���˵� 
{
	int chose;
	system("CLS");
 	printf("��ѡ��ɾ��ѧ����������ѧ��\n\n(1).����  (2).ѧ��\n\n��ѡ��");
	scanf("%d",&chose);
	getchar();
	printf("\n���������ѧ����Ϣ:\n"); 
	scanSTU(4);
	return chose; 
}

 void deleteSTU(int chose_delete)//�ж�ɾ���� ѧ�� 
 {
 	 FILE * fp;
	if((fp=fopen("student.dat","rb"))==NULL)
 	{
 		printf("�ļ���ʧ��");
		return ; 
	 }
	PNODE fristnode,frontnode,tailnode;
	NODE checknode;
	int sum;
	while(fread(&checknode,sizeof(NODE),1,fp)==1)
	  sum++;
	fseek(fp,0l,SEEK_SET);
	fristnode=(PNODE)malloc(sizeof(NODE));
	fread(fristnode,sizeof(NODE),1,fp);
	frontnode=fristnode;
	if(sum==1)
	{
		printf("��δ����");
		return; 
	}
	for(int i=1;i<=sum-1;i++)
	{
		tailnode=(PNODE)malloc(sizeof(NODE));
		fread(tailnode,sizeof(NODE),1,fp);
		tailnode->next=NULL;
		frontnode->next=tailnode;
		frontnode=tailnode;
	}
	
	 char ch[MAX];
	 int m;
	 switch (chose_delete)
	 {
	 	case 1:printf("������Ҫɾ����������");
	 	       scanf("%s",ch);
	 	       getchar();
	 	       Deletenode_name(fristnode,ch);
	 	       break;
	 	case 2:printf("������Ҫɾ����ѧ�ţ�"); 
	           scanf("%d",&m);
	           getchar(); 
	           Deletenode_num(fristnode,m);
	           break;
	    default : printf("�������");
	 }
//	 free(pnode); 
 }

 void Deletenode_name(PNODE fristnode,char * ch)//ɾ������ 
 {
 	PNODE frontnode=fristnode;
 	PNODE tailnode=fristnode->next;
 	while(strcmp(tailnode->stu.name,ch) != 0)
 	{
 		frontnode->next=tailnode;
 		frontnode=tailnode;
 		tailnode=tailnode->next;
 		if(tailnode==NULL)
 		{
 			printf("δ�ҵ������� ɾ��ʧ��\n\n");
			return; 
		 }
	 }
	 frontnode->next=tailnode->next;
//	 free(tailnode);
     fw_stu(fristnode);
     printf("\nɾ���ɹ�\n");
 }
 
 void Deletenode_num(PNODE fristnode,int m)//ɾ��ѧ�� 
 {
 	PNODE frontnode=fristnode;
 	PNODE tailnode=fristnode->next;
 	while(tailnode->stu.xuehao != m)
 	{
 		frontnode->next=tailnode;
 		frontnode=tailnode;
 		tailnode=tailnode->next;
 		if(tailnode==NULL)
 		{
 			printf("δ���ҵ���ѧ�� ɾ��ʧ��\n\n");
			 return; 
		 }
	 }
	 frontnode->next=tailnode->next;
//	 free(tailnode);
     fw_stu(fristnode);
     printf("\nɾ���ɹ�\n");
}


int menu_paixu()//�������˵� 
{
 	int chose;
 	system("CLS"); 
 	printf("���ʱ����ʽ:\n\n(1).��������\n(2).ѧ������\n(3).�ɼ�����\n(4).¼���Ⱥ�\n\n��ѡ��:");
 	scanf("%d",&chose);
 	getchar();
 	return chose;
}
 
void scanSTU(int chose_paixu)//���ļ�������ȶ�ȡ(��������ʽ) 
{
	 FILE * fp;
	if((fp=fopen("student.dat","rb"))==NULL)
 	{
 		printf("�ļ���ʧ��");
		return ; 
	 }
	PNODE fristnode,frontnode,tailnode;
	NODE checknode;
	int sum;
	while(fread(&checknode,sizeof(NODE),1,fp)==1)
	  sum++;
	fseek(fp,0l,SEEK_SET);
	fristnode=(PNODE)malloc(sizeof(NODE));
	fread(fristnode,sizeof(NODE),1,fp);
	frontnode=fristnode;
	if(sum==1)
	{
		printf("��δ����");
		return; 
	}
	for(int i=1;i<=sum-1;i++)
	{
		tailnode=(PNODE)malloc(sizeof(NODE));
		fread(tailnode,sizeof(NODE),1,fp);
		tailnode->next=NULL;
		frontnode->next=tailnode;
		frontnode=tailnode;
	}
	 paixu(fristnode,chose_paixu,sum); 
	  frontnode=fristnode->next; 
	  putchar('\n');
//	 while(frontnode!=NULL){
//	   printf("����:%-10s\t����:%-5d\tѧ��:%-10d\t�ɼ�:%d\n",frontnode->stu.name,frontnode->stu.age,frontnode->stu.xuehao,frontnode->stu.socer);
//	   frontnode=frontnode->next;
  //  }
	 fclose(fp);
//	 free(fristnode);
}
 
 void paixu(PNODE fristnode,int chose_paixu,int sum)//����ͬ��ʽ���� 
 {
    STU change,copy[sum-1];
  //  copy=(STU *)malloc(sizeof(copy) * (sum-1));
    PNODE node=fristnode->next;
    for(int i=0;i<sum-1;i++)
    {
    	copy[i].age=node->stu.age;
        strcpy(copy[i].name,node->stu.name);
		copy[i].socer=node->stu.socer;
    	copy[i].xuehao=node->stu.xuehao;
    	node=node->next;
    	if(node==NULL)
    	  break;
	}
    switch (chose_paixu)
	 {
	 	case 1: for(int i=0;i<sum-1;i++)
	 	        {
                  for(int j=0;j<sum-i-2;j++)
                  {
                  	if(copy[j].age>copy[j+1].age)
                  	{
                  		change=copy[j];
                  		copy[j]=copy[j+1];
                  		copy[j+1]=change;
					  }
				  }
			    }
				  break;
				  
		case 2: for(int i=0;i<sum-1;i++)
	 	        {
                  for(int j=0;j<sum-i-2;j++)
                  {
                  	if(copy[j].xuehao>copy[j+1].xuehao)
                  	{
                  		change=copy[j];
                  		copy[j]=copy[j+1];
                  		copy[j+1]=change;
					  }
				  }
			    }
				  break;
				  
		case 3: for(int i=0;i<sum-1;i++)
	 	        {
                  for(int j=0;j<sum-i-2;j++)
                  {
                  	if(copy[j].socer>copy[j+1].socer)
                  	{
                  		change=copy[j];
                  		copy[j]=copy[j+1];
                  		copy[j+1]=change;
					  }
				  }
			    }
				  break;
		case 4:   break;   
		default : printf("�������");		  
	 }
	 putchar('\n');
	 for(int i=0;i<sum-1;i++)
	   printf("����:%-15s\t����:%-8d\tѧ��:%-15d\t�ɼ�:%d\n",copy[i].name,copy[i].age,copy[i].xuehao,copy[i].socer);
     //free(copy);
 }
 
 
void modifySTU()//�����޸ĵ����� 
{
	FILE * fp;
	if((fp=fopen("student.dat","rb"))==NULL)
	{
		printf("�ļ���ʧ��");
		return; 
	}
	PNODE fristnode,frontnode,tailnode;
	NODE checknode;
	int sum=0;
	while(fread(&checknode,sizeof(NODE),1,fp))
	  sum++;
	if(sum==1)
	{
		printf("��δ�洢");
		return; 
	}
	fseek(fp,0l,SEEK_SET);
	fristnode=(PNODE)malloc(sizeof(NODE));
	fread(fristnode,sizeof(NODE),1,fp);
	frontnode=fristnode;
	for(int i=1;i<=sum-1;i++)
	{
		tailnode=(PNODE)malloc(sizeof(NODE));
		fread(tailnode,sizeof(NODE),1,fp);
		tailnode->next=NULL;
		frontnode->next=tailnode;
		frontnode=tailnode;
	}
	
 	char ch[MAX];
 	 system("CLS");
	 printf("���������ѧ���ɼ���\n");
	 scanSTU(3);
	 printf("\n����������:"); 
	 scanf("%s",ch);
	 getchar();
	 Modifynode_socer(fristnode,ch); 
}
 
void Modifynode_socer(PNODE fristnode,char * p)
{
 	PNODE node=fristnode->next;
 	while(strcmp(node->stu.name,p) !=0)
 	{
 		node=node->next;
 		if(node==NULL)
 		{
 		    printf("δ�ҵ���ѧ�� ɾ��ʧ��\n\n");
			return; 
		 }
	 }
	 int socer;
	 printf("���뽫�ɼ��޸�Ϊ���٣�");
	 scanf("%d",&socer);
	 getchar();
	 node->stu.socer=socer;
	 printf("\n�޸ĳɹ�,�������:\n");
	 printf("����:%-15s\t����:%-8d\tѧ��:%-15d\t�ɼ�:%d\n\n",node->stu.name,node->stu.age,node->stu.xuehao,node->stu.socer);
	 fw_stu(fristnode);
}
 

 
 
  
 



