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

int menu_start();//开始菜单
bool fr_fristnode();//从文件读取头节点(有则返回) 
PNODE Creatfristnode();//创建头节点(文件没有时)
void inputSTU();//录入
char * s_gets(char * s,int n);//录入姓名 
void fw_stu(PNODE f_fristnode);//给文件写入录入的 
void Insertlastnode(STU * p);//从头插入
PNODE Creatnode(STU * p);//创建节点 

int menu_delete();//删除菜单
void deleteSTU(int chose_delete);//判断删名字 学号
void Deletenode_name(PNODE fristnode,char * ch);//删除名字
void Deletenode_num(PNODE fristnode,int m);//删除学号 
 
int menu_paixu();//浏览排序菜单
void scanSTU(int chose_paixu);//将文件保存的先读取(传出排序方式)
void paixu(PNODE fristnode,int chose_paixu,int sum);//按不同方式排序 
 
void modifySTU();//输入修改的名字 
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
		     default: printf("\n\n感谢使用!");
					  exit(0); 
 	     }
 	     system("pause");
     }
 	return 0;
}
 
int menu_start()//开始菜单 
 {
 	system("CLS");
 	int chose;
 	printf(" *欢迎使用学生管理系统*\n");
 	printf(" \n (1).继续录入学生信息\n (2).删除现有学生信息\n (3).浏览现有学生信息\n (4).修改现有学生成绩\n\n请选择(其他任意键退出):");
	scanf("%d",&chose);
	getchar();
	return chose; 
 }
 
bool fr_fristnode()//从文件读取头节点
{
 	FILE * fp;
 	if((fp=fopen("student.dat","a+b"))==NULL)
 	{
 		printf("文件打开失败\n");
		return false;
	 }
	 NODE fristnode;
	 if(fread(&fristnode,sizeof(NODE),1,fp)==0)
	 {
	 	//printf("还没有储存信息\n");
		 fclose(fp); 
	     return false;
	 }
	 fclose(fp);
	 return true;
}

PNODE Creatfristnode()//创建头节点(文件没有时) 
{
	PNODE fristnode;
	fristnode=(PNODE)malloc(sizeof(NODE));
	if(fristnode==NULL)
	{
		printf("创建链表失败");
		system("pause");
		exit(0); 
    }
    fristnode->next=NULL;
    fw_stu(fristnode);
    return fristnode;
}

void inputSTU()//录入 
{
 	STU p;
 	system("CLS"); 
 	printf("请按提示进行录入\n\n");
 	printf("请输入姓名[按[Enter]退出]：");
	while(s_gets(p.name,MAX) != NULL && p.name[0] !='\0')
	{  
	    printf("请输入年龄：");
	    scanf("%d",&p.age);
	    printf("请输入学号：");
	    scanf("%d",&p.xuehao);
	    printf("请输入成绩：");
	    scanf("%d",&p.socer);
	    fflush(stdin);
	  //  printf("00");
	    Insertlastnode(&p);
	    printf("\n请输入姓名(按[Enter]退出)："); 
     }
     printf("\n\n录入成功\n\n"); 
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

void fw_stu(PNODE f_fristnode)//给文件写入录入的 
{
	FILE * fp;
	if((fp=fopen("student.dat","wb"))==NULL)
	{
		printf("保存失败");
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
 
 void Insertlastnode(STU * p)//从尾插入 
{
     FILE * fp;
	if((fp=fopen("student.dat","a+b"))==NULL)
 	{
 		printf("文件打开失败");
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
  
PNODE Creatnode(STU * p)//创建节点 
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


int menu_delete()//删除菜单 
{
	int chose;
	system("CLS");
 	printf("请选择删除学生的姓名或学号\n\n(1).姓名  (2).学号\n\n请选择：");
	scanf("%d",&chose);
	getchar();
	printf("\n请浏览所有学生信息:\n"); 
	scanSTU(4);
	return chose; 
}

 void deleteSTU(int chose_delete)//判断删名字 学号 
 {
 	 FILE * fp;
	if((fp=fopen("student.dat","rb"))==NULL)
 	{
 		printf("文件打开失败");
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
		printf("还未储存");
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
	 	case 1:printf("请输入要删除的姓名：");
	 	       scanf("%s",ch);
	 	       getchar();
	 	       Deletenode_name(fristnode,ch);
	 	       break;
	 	case 2:printf("请输入要删除的学号："); 
	           scanf("%d",&m);
	           getchar(); 
	           Deletenode_num(fristnode,m);
	           break;
	    default : printf("输入错误");
	 }
//	 free(pnode); 
 }

 void Deletenode_name(PNODE fristnode,char * ch)//删除名字 
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
 			printf("未找到该姓名 删除失败\n\n");
			return; 
		 }
	 }
	 frontnode->next=tailnode->next;
//	 free(tailnode);
     fw_stu(fristnode);
     printf("\n删除成功\n");
 }
 
 void Deletenode_num(PNODE fristnode,int m)//删除学号 
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
 			printf("未查找到该学号 删除失败\n\n");
			 return; 
		 }
	 }
	 frontnode->next=tailnode->next;
//	 free(tailnode);
     fw_stu(fristnode);
     printf("\n删除成功\n");
}


int menu_paixu()//浏览排序菜单 
{
 	int chose;
 	system("CLS"); 
 	printf("浏览时排序方式:\n\n(1).年龄增序\n(2).学号增序\n(3).成绩增序\n(4).录入先后\n\n请选择:");
 	scanf("%d",&chose);
 	getchar();
 	return chose;
}
 
void scanSTU(int chose_paixu)//将文件保存的先读取(传出排序方式) 
{
	 FILE * fp;
	if((fp=fopen("student.dat","rb"))==NULL)
 	{
 		printf("文件打开失败");
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
		printf("还未储存");
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
//	   printf("姓名:%-10s\t年龄:%-5d\t学号:%-10d\t成绩:%d\n",frontnode->stu.name,frontnode->stu.age,frontnode->stu.xuehao,frontnode->stu.socer);
//	   frontnode=frontnode->next;
  //  }
	 fclose(fp);
//	 free(fristnode);
}
 
 void paixu(PNODE fristnode,int chose_paixu,int sum)//按不同方式排序 
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
		default : printf("输入错误");		  
	 }
	 putchar('\n');
	 for(int i=0;i<sum-1;i++)
	   printf("姓名:%-15s\t年龄:%-8d\t学号:%-15d\t成绩:%d\n",copy[i].name,copy[i].age,copy[i].xuehao,copy[i].socer);
     //free(copy);
 }
 
 
void modifySTU()//输入修改的名字 
{
	FILE * fp;
	if((fp=fopen("student.dat","rb"))==NULL)
	{
		printf("文件打开失败");
		return; 
	}
	PNODE fristnode,frontnode,tailnode;
	NODE checknode;
	int sum=0;
	while(fread(&checknode,sizeof(NODE),1,fp))
	  sum++;
	if(sum==1)
	{
		printf("还未存储");
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
	 printf("请浏览所有学生成绩：\n");
	 scanSTU(3);
	 printf("\n请输入姓名:"); 
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
 		    printf("未找到该学生 删除失败\n\n");
			return; 
		 }
	 }
	 int socer;
	 printf("你想将成绩修改为多少：");
	 scanf("%d",&socer);
	 getchar();
	 node->stu.socer=socer;
	 printf("\n修改成功,结果如下:\n");
	 printf("姓名:%-15s\t年龄:%-8d\t学号:%-15d\t成绩:%d\n\n",node->stu.name,node->stu.age,node->stu.xuehao,node->stu.socer);
	 fw_stu(fristnode);
}
 

 
 
  
 



