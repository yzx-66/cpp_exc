#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"gotoxy.h"
#define WIDE 16

void Show();
void Getkeydown();
bool Isdie();
void Check();

int map[4][4]={0}; 

int main()
{
//	map[3][3]=2;
	Show();
	while(1)
	{
		if(Isdie())  break;
		else  Getkeydown();
	}
    gotoxy(0,15);
	return 0;
}

void Show()
{
	system("CLS");
	srand(time(NULL));
	int x,y;
    while(1)
    {
	  x=rand()%4;
	  y=rand()%4;
	  if(map[x][y]==0)  break;
    }
//	map[0][1]=2;
//	map[0][2]=4;
    map[x][y]=2;
	for(int i=1;i<=7;i+=2)
	{
		gotoxy(0,i);
		for(int j=0;j<20;j++)
		  printf("-");
	}
	gotoxy(0,0);
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<4;j++)
      {
      	if(map[i][j]==0)
		{
		    printf("    |");
			continue;  
		} 
		printf(" %2d |",map[i][j]);
	  }
	  puts("\n");
    }
}

void Check()
{
	puts("\n\n");
    for(int i=0;i<4;i++)
    {
      for(int j=0;j<4;j++)
      {
      	if(map[i][j]==0)
		{
		    printf("  _  ");
			continue;  
		} 
		printf(" %2d ",map[i][j]);
	  }
	  puts("\n");
    }
}

void Getkeydown()
{
	if(kbhit())
	{
		char key,ch=getch();
		if(ch=='w'||ch=='s'||ch=='a'||ch=='d')   key=ch;
		switch(key)
		{
			case 'w':
			{
		    	int * p[4],front[4],front_num[4],position_0[4],position_num[4]={-1},position_now[4];
				
				for(int i=0;i<4;i++)
				   p[i]=map[0]+i;
				   
				for(int i=0;i<4;i++)
				{
					if(*p[i]==0)  position_0[i]=0;
					else   
					{
						front_num[i]=*p[i];
					    position_num[i]=0;
				    }
					front[i]=*p[i];
					p[i]+=4;
					position_now[i]=1;
					
					for(int j=1;j<=3;j++)
					{
						if(front[i]==0 && *p[i]==0);
						
						else if(front[i]==0 && *p[i]!=0)
						{
							if(position_num[i]<0)
							{
							   int * q=p[i]-(position_now[i]-position_0[i])*4;
							   *q=*p[i];
							   position_num[i]=position_0[i];
							   front_num[i]=*p[i];
							   position_0[i]++;
						    }
						    else
						    {
						    	if(front_num[i]==*p[i])
						    	{
						    		int * q=p[i]-(position_now[i]-position_num[i])*4;
						    		*q=(*q)*2;
						    		position_0[i]=j;
						    		position_num[i]=-1;
								}
								else
								{
									int * q=p[i]-(position_now[i]-position_0[i])*4;
									*q=*p[i];
									position_num[i]=position_0[i];
									position_0[i]++;
									front_num[i]=*p[i];
								}
							}
							*p[i]=0;
							front[i]=0;
						}
						
					    else if(front[i]!=0 && *p[i]==0)
					    {
					    	front[i]=*p[i];
					    	position_0[i]=j;
						}
						
						else 
						{
							if(front[i]==*p[i])
							{
								int * q=p[i]-4;
								*q=(*q)*2;
								*p[i]=0;
								position_0[i]=j;
								position_num[i]=-1;
								front[i]=0;
							}
							else
							{
								front_num[i]=*p[i];
								position_num[i]=j;
								front[i]=*p[i];
							}
						}
						if(j!=3)
						{
						  p[i]+=4;
						  position_now[i]=j+1;
					    }
					//	Check();
					}
					
				}
				break;
		    }
		    
			case 's':
			{
				int * p[4],front[4],front_num[4],position_0[4],position_num[4]={-1},position_now[4];
				
				for(int i=0;i<4;i++)
				   p[i]=map[3]+i;
				   
				for(int i=0;i<4;i++)
				{
					if(*p[i]==0)  position_0[i]=0;
					else   
					{
						front_num[i]=*p[i];
					    position_num[i]=0;
				    }
					front[i]=*p[i];
					p[i]-=4;
					position_now[i]=1;
					
					for(int j=1;j<=3;j++)
					{
						if(front[i]==0 && *p[i]==0);
						
						else if(front[i]==0 && *p[i]!=0)
						{
							if(position_num[i]<0)
							{
							   int * q=p[i]+(position_now[i]-position_0[i])*4;
							   *q=*p[i];
							   position_num[i]=position_0[i];
							   front_num[i]=*p[i];
							   position_0[i]++;
						    }
						     else
						    {
						    	if(front_num[i]==*p[i])
						    	{
						    		int * q=p[i]+(position_now[i]-position_num[i])*4;
						    		*q=(*q)*2;
						    		position_0[i]=j;
						    		position_num[i]=-1;
								}
								else
								{
									int * q=p[i]+(position_now[i]-position_0[i])*4;
									*q=*p[i];
									position_num[i]=position_0[i];
									position_0[i]++;
									front_num[i]=*p[i];
								}
							}
							*p[i]=0;
							front[i]=0;
						}
						
					    else if(front[i]!=0 && *p[i]==0)
					    {
					    	front[i]=*p[i];
					    	position_0[i]=j;
						}
						
						else 
						{
							if(front[i]==*p[i])
							{
								int * q=p[i]+4;
								*q=(*q)*2;
								*p[i]=0;
								position_0[i]=j;
								position_num[i]=-1;
								front[i]=0;
							}
							else
							{
								front_num[i]=*p[i];
								position_num[i]=j;
								front[i]=*p[i];
							}
						}
						if(j!=3)
						{
						   p[i]-=4;
						   position_now[i]=j+1;
					    }
					//	Check();
					}
					
				}
				break;
		    }
				
			case 'd':
			{
				int * p[4],front[4],front_num[4],position_0[4],position_num[4]={-1},position_now[4];
				
				for(int i=0;i<4;i++)
				   p[i]=*(map+i)+3;
				   
				for(int i=0;i<4;i++)
				{
					if(*p[i]==0)  position_0[i]=0;
					else   
					{
						front_num[i]=*p[i];
					    position_num[i]=0;
				    }
					front[i]=*p[i];
					p[i]--;
					position_now[i]=1;
					
					for(int j=1;j<=3;j++)
					{
						if(front[i]==0 && *p[i]==0);
						
						else if(front[i]==0 && *p[i]!=0)
						{
							if(position_num[i]<0)
							{
							   int * q=p[i]+(position_now[i]-position_0[i]);
							   *q=*p[i];
							   position_num[i]=position_0[i];
							   front_num[i]=*p[i];
							   position_0[i]++;
						    }
						     else
						    {
						    	if(front_num[i]==*p[i])
						    	{
						    		int * q=p[i]+(position_now[i]-position_num[i]);
						    		*q=(*q)*2;
						    		position_0[i]=j;
						    		position_num[i]=-1;
								}
								else
								{
									int * q=p[i]+(position_now[i]-position_0[i]);
									*q=*p[i];
									position_num[i]=position_0[i];
									position_0[i]++;
									front_num[i]=*p[i];
								}
							}
							*p[i]=0;
							front[i]=0;
						}
						
					    else if(front[i]!=0 && *p[i]==0)
					    {
					    	front[i]=*p[i];
					    	position_0[i]=j;
						}
						
						else 
						{
							if(front[i]==*p[i])
							{
								int * q=p[i]+1;
								*q=(*q)*2;
								*p[i]=0;
								position_0[i]=j;
								position_num[i]=-1;
								front[i]=0;
							}
							else
							{
								front_num[i]=*p[i];
								position_num[i]=j;
								front[i]=*p[i];
							}
						}
						if(j!=3)
						{
						   p[i]--;
						   position_now[i]=j+1;
					    }
					//	Check();
					}
					
				}
				break;
		    }   
		    
		case 'a':
			{
				int * p[4],front[4],front_num[4],position_0[4],position_num[4]={-1},position_now[4];
				
				for(int i=0;i<4;i++)
				   p[i]=*(map+i);
				   
				for(int i=0;i<4;i++)
				{
					if(*p[i]==0)  position_0[i]=0;
					else   
					{
						front_num[i]=*p[i];
					    position_num[i]=0;
				    }
					front[i]=*p[i];
					p[i]++;
					position_now[i]=1;
					
					for(int j=1;j<=3;j++)
					{
						if(front[i]==0 && *p[i]==0);
						
						else if(front[i]==0 && *p[i]!=0)
						{
							if(position_num[i]<0)
							{
							   int * q=p[i]-(position_now[i]-position_0[i]);
							   *q=*p[i];
							   position_num[i]=position_0[i];
							   front_num[i]=*p[i];
							   position_0[i]++;
						    }
						     else
						    {
						    	if(front_num[i]==*p[i])
						    	{
						    		int * q=p[i]-(position_now[i]-position_num[i]);
						    		*q=(*q)*2;
						    		position_0[i]=j;
						    		position_num[i]=-1;
								}
								else
								{
									int * q=p[i]-(position_now[i]-position_0[i]);
									*q=*p[i];
									position_num[i]=position_0[i];
									position_0[i]++;
									front_num[i]=*p[i];
								}
							}
							*p[i]=0;
							front[i]=0;
						}
						
					    else if(front[i]!=0 && *p[i]==0)
					    {
					    	front[i]=*p[i];
					    	position_0[i]=j;
						}
						
						else 
						{
							if(front[i]==*p[i])
							{
								int * q=p[i]-1;
								*q=(*q)*2;
								*p[i]=0;
								position_0[i]=j;
								position_num[i]=-1;
								front[i]=0;
							}
							else
							{
								front_num[i]=*p[i];
								position_num[i]=j;
								front[i]=*p[i];
							}
						}
						if(j!=3)
						{
						   p[i]++;
						   position_now[i]=j+1;
					    }
					//	Check();
					}
					
				}
				break;
			}
	    }
	    Show();
	}
}

bool Isdie()
{
	for(int i=0;i<4;i++)
	   for(int j=0;j<4;j++)
	      if(map[i][j]==0)  return false;
	return true; 
}
