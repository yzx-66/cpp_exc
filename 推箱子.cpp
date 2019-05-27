#include<stdio.h>
//#include"gotoxy.h"
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#define WIDE 39
#define HIGH 18

typedef struct 
{
	int x;
	int y;
}MEN,BOX,WALL,GOAL;

WALL wall[50];
MEN men;
BOX box[3];
GOAL goal[3];

void gotoxy(int x,int y);
void Creatmenu();
void Creatmap();
void Getkeydown();
void Move(MEN del,MEN next,int chose);
bool Isgoal(MEN del); 
bool Iswall(MEN next);
int Isbox(MEN next);
void Movebox(char key,MEN del,int i);
bool checkwin();

int main()
{
	while(1){
	  Creatmenu();
	  Creatmap();
	  Getkeydown(); 
	  if(getchar()=='n'){
	     printf("\n\n\n\t\t\t\t\t\t再见\n\n\n");
	     break;
	   }
	   system("CLS");
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
 
 bool checkwin()
 {
 	int socer=0;
 	for(int i=0;i<3;i++)
 	  for(int j=0;j<3;j++)
 	  	if(box[i].x==goal[j].x && box[i].y==goal[j].y)
 	  	   socer++;
 	Sleep(10);
 	gotoxy(50,14);
 	if(socer==3){
 		printf("恭喜获胜  ");
 		gotoxy(50,15);
 		system("pause");
 		fflush(stdin);
 		system("CLS");
 		printf("\n\n\n\n\n\t\t\t\t\t要继续吗<y or n>:");
 		return true;
 	}
	 else{
	    printf("还剩%d个目标",3-socer);
	    return false;
	}
 }
 
 void Creatmenu()
 {
 		gotoxy(50,4);
 		printf("欢迎来到简易推箱子");
 		gotoxy(50,7);
 		printf("操作方法:");
		gotoxy(50,8);
		printf("w:向上 s:向下 a:向左 d:向右");
		gotoxy(50,9);
		printf("<>:推手 ⊙:箱子 !$:目标"); 
		gotoxy(50,11);
		printf("(注:因随机生成位置 所以极小概率存在bug)");
 }
 
 void Creatmap()
 {
 	//制造围墙 
 	for(int i=0;i<WIDE-2;i+=2){
 		gotoxy(i,0);
 		printf("■");
 		gotoxy(i,HIGH-2);
 		printf("■");
	 }
	for(int i=0;i<HIGH-1;i++){
		gotoxy(0,i);
		printf("■");
		gotoxy(WIDE-3,i);
		printf("■");
	}
	int j;
	for(int i=1,j=0;j<5;j++,i++){
		gotoxy(WIDE/3-1,i);
		wall[j].x=WIDE/3-1;
		wall[j].y=i;
		printf("■"); 
	}
	for(int i=WIDE-2-1,j=0;j<5;j++,i-=2){
		gotoxy(i,HIGH/3*2);
		wall[5+j].x=i;
		wall[5+j].y=HIGH/3*2;
		printf("■");
	}
	srand(time(NULL));
	for(int i=10;i<50;i++){
		while(1){
			strat_1:
			int x=rand()%(WIDE-2-2)+2;
			int y=rand()%(HIGH-1-1)+1;
			for(int n=0;n<10;n++)
				if(wall[n].x==x && wall[n].y==y)
				   goto strat_1;
			if(x%2!=0)  continue;
			wall[i].x=x;
			wall[i].y=y;
			gotoxy(x,y);
			printf("■");
			break;
		}
	}
	
	//制造箱子 
	for(int i=0;i<3;i++){
		while(1){
			strat_2:
			int x=rand()%(WIDE-2-2-2-2-2)+4;
			int y=rand()%(HIGH-1-1-1-1-1)+2;
			for(int n=0;n<50;n++)
				if(x==wall[n].x && y==wall[n].y)
				   goto strat_2;
			if(x%2!=0)
			  continue;
			box[i].x=x;
			box[i].y=y;
			gotoxy(x,y);
			printf("⊙");
			break;
		}
	}
	
	//制造小人 
	while(1){
		strat_3:
		int x=rand()%(WIDE-2-2-2)+2;
		int y=rand()%(HIGH-1-1-1)+1;
		for(int i=0;i<50;i++)
		  if(x==wall[i].x && y==wall[i].y)
		    goto strat_3;
		for(int i=0;i<3;i++)
		  if(x==box[i].x && y==box[i].y)
		     goto strat_3;
		if(x%2!=0)
		     continue;
	    men.x=x;
	    men.y=y;
	    gotoxy(x,y);
	    printf("<>");
	    break;
	}
	
	//制造目标
	for(int i=0;i<3;i++){
		while(1){
			strat_4:
			int x=rand()%(WIDE-2-2-2)+2;
			int y=rand()%(HIGH-1-1-1)+1;
		    for(int n=0;n<50;n++)
		       if(x==wall[n].x && y==wall[n].y)
		           goto strat_4;
	        for(int n=0;n<3;n++)
	            if(x==box[n].x && y==box[y].y)
	               goto strat_4;
	        if(x==men.x && y==men.y)
	            continue;
	        if(x%2!=0)
	            continue;
	        goal[i].x=x;
	        goal[i].y=y;
	        gotoxy(x,y);
	        printf("!$"); 
		    break;
	    }
	} 
	gotoxy(men.x,men.y);
 }
 
 void Getkeydown()
 {
 	char key;
 	int i;
 	while(1){
 	   if(checkwin()) return;
 	   gotoxy(men.x,men.y);
 	   MEN del=men;
 	   
 	   if(_kbhit()){
 		   key=getch();
 		   
 		   switch(key){
 		   	case 'w':
 		   		    men.y--;
 		   		    
 		   		    if(Iswall(men)){
						  men.y++;
						  break;
					}
					   
					if( (i=Isbox(men)) >=0){
						Movebox(key,del,i);
						if(Isgoal(del))
					   	    Move(del,men,2);
						break;
					}
					
					if(Isgoal(del)){
					   	  Move(del,men,2);
					   	  break;
					   } 
					   
					Move(del,men,1);
					
		   		    break;
 		   		    
 		   	case 's':
 		   		    men.y++;
 		   		    
 		   		     if(Iswall(men)){
						  men.y--;
						  break;
					}
					   
					if( (i=Isbox(men)) >=0){
						Movebox(key,del,i);
						if(Isgoal(del))
					   	    Move(del,men,2);
						break;
					}
					
					if(Isgoal(del)){
					   	  Move(del,men,2);
					   	  break;
					   } 
					   
					Move(del,men,1);
					
		   		    break;
		   		    
 		   	case 'a':
 		   		    men.x-=2;
 		   		    
 		   		    if(Iswall(men)){
						  men.x+=2;
						  break;
					}
					   
					if( (i=Isbox(men)) >=0){
						Movebox(key,del,i);
						if(Isgoal(del))
					   	    Move(del,men,2);
						break;
					}
					
					if(Isgoal(del)){
					   	  Move(del,men,2);
					   	  break;
					   } 
					   
					Move(del,men,1);
					
		   		    break;
		   		    
 		   	case 'd':
 		   		    men.x+=2;
 		   		    
 		   		    if(Iswall(men)){
						  men.x-=2;
						  break;
					}
					   
					if( (i=Isbox(men)) >=0){
						Movebox(key,del,i);
						if(Isgoal(del))
					   	    Move(del,men,2);
						break;
					}
					
					if(Isgoal(del)){
					   	  Move(del,men,2);
					   	  break;
					   } 
					   
					Move(del,men,1);
					
		   		    break;
			}
	    }
	}
 }
 
 void Move(MEN del,MEN next,int chose)
 {
 	switch(chose){
 		case 1:
 			gotoxy(del.x,del.y);
 	        printf("  ");
 	        break;
 	    case 2:
 	    	gotoxy(del.x,del.y);
 	        printf("!$");
 	        break;
 	    case 3:
 	    	gotoxy(del.x,del.y);
 	        printf("<>");
 	        break;
    }
    
    gotoxy(next.x,next.y);
    
    switch(chose){
    	case 1:
    	case 2:
 	        printf("<>");
 	        break;
 	    case 3:
		    printf("⊙");
		    break;
	}
 	            
 }
 
 bool Iswall(MEN next)
 {
 	 for(int i=0;i<50;i++)
 		if(next.x==wall[i].x && next.y==wall[i].y || next.x<=0 || next.x>=WIDE-2-1 || next.y<=0 || next.y>=HIGH-1-1)  
 		    return true;
 	 return false;
 }
 
 bool Isgoal(MEN del)
 {
 	 for(int i=0;i<3;i++)
		if(del.x==goal[i].x && del.y==goal[i].y){
			Move(del,men,2);
			return true;
		}
	 return false;
 }
 
 int Isbox(MEN next)
 {
 	for(int i=0;i<3;i++)
 	  if(next.x==box[i].x && next.y==box[i].y)
 	    return i;
 	return -1;
 }
 
 void Movebox(char key,MEN del,int i)
 {
 	BOX next_box=men;
 	switch(key){
 		case 'w':
 			next_box.y--;
 			
 			if(Iswall(next_box) || Isbox(next_box)>=0 ){
			    men.y++;
			    return;
 		    }
			Move(men,next_box,3);
 			Move(del,men,1);
 			box[i].y--;
 			
			 break;
			 
		case 's':
 			next_box.y++;
 			
 			if(Iswall(next_box) || Isbox(next_box)>=0 ){
			    men.y--;
			    return;
			}
 			Move(men,next_box,3);
 			Move(del,men,1);
 			box[i].y++;
			 break;
			 
		case 'a':
 			next_box.x-=2;
 			
 			if(Iswall(next_box) || Isbox(next_box)>=0 ){
 			    men.x+=2;
			    return;
			}
 			Move(men,next_box,3);
 			Move(del,men,1);
 			box[i].x-=2;
			 
			 break;
			 
		case 'd':
 			next_box.x+=2;
 			
 			if(Iswall(next_box) || Isbox(next_box)>=0 ){
 			    men.x-=2;
			    return;
			}
 			Move(men,next_box,3);
 			Move(del,men,1);
 			box[i].x+=2;
			 
			 break;
	 }
 }
