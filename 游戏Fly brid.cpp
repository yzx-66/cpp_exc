#include<stdio.h>
#include<stdlib.h>
#include"gotoxy.h"
#include<windows.h>
#include<time.h> 
#define WIDE 46
#define HIGH 13

typedef struct
{
	int x;
	int y;
}WALL,BRID;

WALL wall[40];
BRID bird,del;

void menu();
void Creatmap();
bool Move();
bool Getkeydown();
bool Isdie();
bool Iswin();

int main()
{
	while(1){
	 menu();
	 Creatmap();
	
	 Getkeydown();
	 if(getchar()=='n')  break;
	
	 system("CLS");
   }
	gotoxy(0,HIGH+5);
	return 0;
}

void menu()
{
   gotoxy(60,4);
   printf("游戏名:Fly bird");
   gotoxy(60,6);
   printf("操作方法");
   gotoxy(60,7);
   printf("⊙:小鸟  ■:墙砖 ");
   gotoxy(60,8); 
   printf("w:向上 p:暂停");	
}

void Creatmap()
{
	for(int i=0;i<WIDE-2;i+=2){
		gotoxy(i,0);
		printf("■");
		gotoxy(i,HIGH-1);
		printf("■");
	}
	
	int wall_x1[5];
	int num_x1=0;
	int num_x2=0;
    srand(time(NULL));
    
	while(1){
		int x=rand()%32+8;
		if(x%2!=0) continue;
		wall_x1[0]=x;
		num_x1++;
		
		for(int i=0;i<5;i++){
			gotoxy(x,i+1);
			printf("■");
			wall[num_x2].x=x;
			wall[num_x2].y=i+1;
			num_x2++;
		}
		
		break;
	}
	
	for(int i=0;i<3;i++){
		while(1){
			strat_1:
			int x=rand()%32+8;
			if(x%2!=0) continue;
			
			for(int j=0;j<num_x1;j++)
				if(x==wall_x1[num_x1-1])
				  goto strat_1;
			
			wall_x1[num_x1]=x;
			num_x1++;
			
			for(int j=0;j<4;j++){
				gotoxy(x,j+1);
				printf("■");
				wall[num_x2].x=x;
				wall[num_x2].y=j+1;
				num_x2++;
			}
			break;
		}
	}
	
	while(1){
		strat_2:
		int x=rand()%32+8;
		if(x%2!=0) continue;
		
		for(int j=0;j<num_x1;j++)
				if(x==wall_x1[num_x1-1])
				  goto strat_2;
			
			wall_x1[num_x1]=x;
			num_x1++;
		
		for(int j=0;j<3;j++){
			gotoxy(x,j+1);
			printf("■");
			wall[num_x2].x=x;
			wall[num_x2].y=j+1;
			num_x2++;
		}
		break;
	}
	
	int high,wall_x2[5];
	num_x1=0;
	
	while(1){
		int x=rand()%32+8;
		if(x%2!=0) continue;
		wall_x2[0]=x;
		num_x1++;
		
		for(int i=0,high=HIGH-2;i<5;i++,high--){
			gotoxy(x,high);
			printf("■");
			wall[num_x2].x=x;
			wall[num_x2].y=high;
			num_x2++;
		}
		
		break;
	}
	
	for(int i=0;i<3;i++){
		while(1){
			strat_3:
			int x=rand()%32+8;
			if(x%2!=0) continue;
			
			for(int j=0;j<num_x1;j++)
				if(x==wall_x2[num_x1-1])
				  goto strat_3;
			
			wall_x2[num_x1]=x;
			num_x1++;
			
		    for(int i=0,high=HIGH-2;i<4;i++,high--){
			    gotoxy(x,high);
			    printf("■");
		     	wall[num_x2].x=x;
			    wall[num_x2].y=high;
			    num_x2++;
		}
			break;
		}
	}
	
	while(1){
		strat_4:
		int x=rand()%32+8;
		if(x%2!=0) continue;
		
		for(int i=0;i<num_x1;i++){
			if(x==wall_x2[num_x1-1])
			  goto strat_4;
		}
		
		wall_x2[num_x1]=x;
		num_x1++;
		
	    for(int i=0,high=HIGH-2;i<3;i++,high--){
			gotoxy(x,high);
			printf("■");
			wall[num_x2].x=x;
			wall[num_x2].y=high;
			num_x2++;
		}
		break;
	}
	
	bird.x=0;
	bird.y=6;
	gotoxy(bird.x,bird.y);
	printf("⊙");
	
}

bool Getkeydown()
{
	while(1){
		char key='a';
		del=bird;
		if(Iswin()) return  true;
		
		Sleep(400);
		
		if(_kbhit())
			key=getch();
			
		switch(key){
			case 'w':
				bird.x+=2;
				bird.y--;
				if(!Move()) return false;
				break;
			case 'p':
			    gotoxy(10,HIGH+2);
				system("pause");
			default:
				bird.x+=2;
				bird.y++;
				if(!Move()) return false;
				break;
	    }
	}
}

bool Move()
{
	if(Isdie())  return false;
	gotoxy(del.x,del.y);
	printf("  ");
	gotoxy(bird.x,bird.y);
	printf("⊙");
	return true;
}

bool Isdie()
{
	int flag=0;
	if(bird.y==0 || bird.y==HIGH-1)
	   flag=1;
	for(int i=0;i<40;i++)
		if(bird.x==wall[i].x && bird.y==wall[i].y)
		  flag=1;
	if(flag==1){
		gotoxy(10,HIGH+2);
		printf("游戏失败!");
		gotoxy(10,HIGH+4);
		fflush(stdin);
		printf("要继续吗<y or n>:");
		return true;
	}
	return false;
}

bool Iswin()
{
	int socer=(40-bird.x)/2;
	gotoxy(60,11);
	printf("距离获胜还有%d米",socer);
	if(bird.x==40){
		gotoxy(10,HIGH+2);
		printf("恭喜获胜！");
		gotoxy(10,HIGH+4);
		fflush(stdin);
		printf("要继续吗<y or n>:");
		return true; 
	}
	gotoxy(10,HIGH+2);
	printf("                     ");
	return false;
}
