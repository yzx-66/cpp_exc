#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>
//#include"gotoxy.h"
#define High 30
#define Wide 64

typedef struct snake
{
	int x;
	int y;
	snake * next;
	snake * front;
}SNAKE,* PSNAKE;

typedef struct                
{
	int x;
	int y;
}Food;

void gotoxy(int x,int y);
void Creatmap();//��ʼ����ͼ������ 
void Creatfood();//����ʳ�� 
void Getkeydown(char ch);//�����������(��ͷ��һ��λ��) 
void Move(SNAKE newhead);//���ƶ� 
bool judge();//�ߵ�״̬ 
PSNAKE Creatnode();//��ʼ��ʱ��������ڵ� 
void printsnake();//��ӡ�� 
void Delete();//�ƶ�ʱ�������һ�� 
void addnode();//����ʳ���������� 
char menu();
void show();
bool gameover();
void clean();//�ڶ��ο�ʼʱ��ʼ�� 

PSNAKE head;
Food food;
char key='a';
bool flag=true;
int socer=0;

int main()
{
	strat:
	 char ch=menu();
	 Creatmap();
	 
	 while(1){
		if(!judge())
		    break;
		show();
		if(flag){
		    Creatfood();
		    flag=false;
	    }
		Getkeydown(ch);
	 }
	 
	if(!gameover()) {
	  clean();
	  flag=true;
	  socer=0; 
	  goto strat;
    }
	return 0;
}

void gotoxy(int x,int y)
{
	COORD pos;
	HANDLE Output;
	pos.X=x;
	pos.Y=y;
	Output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(Output, pos);
}

char menu()
{
	printf("\n\n\t\t\t*��ӭ����̰���ߴ���ս*");
	char c;
	while(1){
	   printf("\n\n\t\t\t��ѡ���Ѷ�:\n\n\t\t\t(a).��ͨ\t(b).����\t(c).����\n\n\t\t\t��ѡ��:");
	   fflush(stdin);
	   c=getchar();
	   if(c=='a' || c=='A' || c=='b' || c=='B'|| c=='c'|| c=='C')
		  break;
		printf("\n\t\t\t�������! ������ѡ��"); 
	}
	printf("\n\n\t\t\t��Ϸ������Ӣ�Ŀ��� ���Ƚ����뷨Ӣ��\n\n\t\t\t׼��������");
	system("pause");
	system("CLS");
	return c;
}

void show()
{
	gotoxy(80,6); 
	printf("��ӭ����̰���ߴ���ս");
	gotoxy(80,12);
	printf("��������Ϊ:");
	gotoxy(80,13);
	printf("w:���� s:���� a:���� d:���� p:��ͣ");
	gotoxy(80,16); 
	printf("��ķ���Ϊ:%d",socer); 
	gotoxy(80,8);
	printf("                                        ");
}

bool gameover()
{
	gotoxy(80,16);
	printf("game ove������          ");
	gotoxy(80,18);
	printf("������յ÷�Ϊ:%d",socer);
	gotoxy(80,20);
	printf("�������:<y or n>:");
	fflush(stdin);
	if(getchar()!='n'){
	  system("CLS"); 
	  return false;
    }
	system("CLS");
	printf("\n\n\n\t\t\t��лʹ�� �ټ�!\n\n\n");
	return true; 
}

void clean()
{
	PSNAKE freenode=head;
	while(head){
		head=head->next;
		free(freenode);
		freenode=head;
	}
}

bool judge()
{
	PSNAKE node=head->next->next->next;
	if(head->next->x==0 || head->next->x==Wide-2 || head->next->y==0 || head->next->y==High-2)
	   return false;
	while(node){
	   if(head->next->x==node->x && head->next->y==node->y)
             return false;
        node=node->next;
	}
	return true;
}

void Creatmap()
{
	for(int i=0;i<Wide-2;i+=2){
		gotoxy(i,0);
		printf("��");
		gotoxy(i,High-2);
		printf("��");
	}
	for(int i=0;i<High-1;i++){
		gotoxy(0,i);
		printf("��");
		gotoxy(Wide-2,i);
		printf("��"); 
	}
	head=(PSNAKE)malloc(sizeof(SNAKE));
    PSNAKE headnode=(PSNAKE)malloc(sizeof(SNAKE));
	PSNAKE p,q;
	head->front=NULL;
	head->next=headnode;
	
	headnode->x=Wide/2;
	headnode->y=High/2;
	headnode->front=head;
	headnode->next=NULL;
	p=Creatnode();
	headnode->next=p;
	p->front=headnode;
	q=Creatnode();
	p->next=q;
	q->front=p;
	printsnake();
}

PSNAKE Creatnode()
{
	PSNAKE add=(PSNAKE)malloc(sizeof(SNAKE));
	PSNAKE frontnode=head;
	PSNAKE tailnode=frontnode->next;
	while(tailnode){
	  frontnode=tailnode;
	  tailnode=tailnode->next;
    }
    add->x=frontnode->x+2;
    add->y=frontnode->y;
    add->next=NULL;
    add->front=NULL;
    return add;
}

void printsnake()
{
	PSNAKE node=head->next;
	while(node){
		gotoxy(node->x,node->y);
		printf("��");
		node=node->next;
	}
}

void Creatfood()
{
	srand(time(NULL));
	int x,y;
	while(1){
		bool flag_2=true;
		PSNAKE node=head->next;
		x=rand()%(Wide-1-4)+2;
		y=rand()%(High-1-2)+1;
		if(x%2 != 0)
		   continue;
		while(node){
		   if(x==node->x && y==node->y){
			   flag_2=false;
			   break;
		    }
		    node=node->next;
		}
		if(flag_2==false)
		   continue;
		food.x=x;
		food.y=y;
		gotoxy(x,y);
		printf("��");
		break;
	}
}

void Getkeydown(char ch)
{
	SNAKE newhead;
	newhead.x=head->next->x;
	newhead.y=head->next->y;
	newhead.next=NULL;
	newhead.front=NULL;
	switch(ch){
		case 'a':
		case 'A':   Sleep(200); break;
		case 'b':
		case 'B':   Sleep(100); break;
		case 'c':
		case 'C':   Sleep(50); break;
	}
	if(_kbhit()){
	  char newkey;
	  newkey=getch();
	  if(newkey=='w'||newkey=='a'||newkey=='s'||newkey=='d'||newkey=='p'){
	      if( (key=='w'||key=='W') && (newkey=='s'||newkey=='S') )
	         newkey='w';
	      else if( (key=='s'||key=='S') && (newkey=='w'||newkey=='W') )
	         newkey='s';
	      else if( (key=='a'||key=='A') && (newkey=='d'||newkey=='D') )
	        newkey='a';
	      else if( (key=='d'||key=='D') && (newkey=='a'||newkey=='A') )
	         newkey='d';
	      if(newkey!='p') key=newkey;
	      if(newkey=='p'||newkey=='P'){
	      	gotoxy(80,8);
			printf("��Ϸ��ͣ�� ");
			system("pause");
		  }
	    }
    }
    
	switch(key){
		case 'w':
		case 'W':   newhead.y=head->next->y-1; break;
		case 's':
     	case 'S':   newhead.y=head->next->y+1; break;
		case 'a':
		case 'A':   newhead.x=head->next->x-2; break;
	    case 'd':
	    case 'D':   newhead.x=head->next->x+2; break;
	}
	Move(newhead);
}

void Move(SNAKE newhead)
{
	if(food.x==newhead.x && food.y==newhead.y){
	     addnode();
	     socer+=10;
	 }
    Delete();
	PSNAKE frontnode=head;
	PSNAKE tailnode=head->next;
	while(tailnode->next){
		frontnode=tailnode;
		tailnode=tailnode->next;
	}
	while(frontnode != head){
		tailnode->x=frontnode->x;
		tailnode->y=frontnode->y;
		tailnode=frontnode;
		frontnode=frontnode->front;
	}
	head->next->x=newhead.x;
	head->next->y=newhead.y;
	printsnake();
}

void Delete()
{
	PSNAKE frontnode=head;
	PSNAKE tailnode=frontnode->next;
	while(tailnode){
	  frontnode=tailnode;
	  tailnode=tailnode->next;
	}
	gotoxy(frontnode->x,frontnode->y);
	printf("  ");
}

void addnode()
{
	flag=true;
	PSNAKE node=head->next;
	PSNAKE newnode=(PSNAKE)malloc(sizeof(SNAKE));
	newnode->x=food.x;
	newnode->y=food.y;
	newnode->front=head;
	newnode->next=node;
	head->next=newnode;
	node->front=newnode;
}


