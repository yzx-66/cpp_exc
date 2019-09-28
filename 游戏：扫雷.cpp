#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Creattruemap(int truemap[][9]);
void showmap(int map[][9],int socer);
void show1map(int map[][9],int socer);

int main()
{
	while(1){
	   int seemap[9][9]={0};
	   int truemap[9][9]={0};
	   int x,y,socer=0; 
	   Creattruemap(truemap);
	   while (1){
	     showmap(seemap,socer);
	     printf("\n\n\t请输入你想点的坐标:");
	     printf("\tx=");
	     scanf("%d",&x);
	     getchar();
	     printf("\t\t\t\ty=");
	     scanf("%d",&y);
	     getchar();
	     if(x>9 || x<1 || y>9 || y<1){
		     printf("\n\t输入错误,");
		     system("\tpause");
		     system("CLS");
		     continue;
	        }
	     else{
	         if(truemap[x-1][y-1]==88){
	     	     system("CLS");
		         show1map(truemap,socer);
		         printf("\n\n\tgame over!\n\n");
		         break;
	            }
	         else{
	         	 socer=socer+2+truemap[x-1][y-1];
	             seemap[x-1][y-1]=truemap[x-1][y-1];
	             system("CLS");
                }
            }
        }
        printf("\t继续吗<y or n>:");
        if(getchar()=='n')
           break;
    }
    printf("\n\t感谢使用 再见！");
    return 0;
 } 
 
 void showmap(int map[][9],int socer)
 { 
     printf("\t\t/***简易扫雷***/\n\n");
     printf("   | ");
     for(int n=0;n<9;n++)
       printf("(%d)  ",n+1);
     putchar('\n');
     printf("   |");
     for(int n=0;n<46;n++)
       printf("_");
     printf("\n   |\n");
     printf("   | "); 
     for(int n=0;n<45;n++)
           printf("*");
     putchar('\n');

     for(int i=0;i<9;i++){
    	printf("(%d)|",i+1);
    	for(int j=0;j<9;j++){
    	   if(map[i][j]==0){
    	   	printf("  #  ");
    	   	continue;
		   }
		   printf("  %-2d ",map[i][j]);
	    }
		putchar('\n');
		 printf("   | ");
        for(int n=0;n<45;n++)
           printf("*");
        putchar('\n');
	 }
	 printf("\n\t分数:%d",socer);
 }
 
 void show1map(int map[][9],int socer)
 { 
     printf("\t\t/***简易扫雷***/\n\n");
     printf("   | ");
     for(int n=0;n<9;n++)
       printf("(%d)  ",n+1);
     putchar('\n');
     printf("   |");
     for(int n=0;n<46;n++)
       printf("_");
     printf("\n   |\n");
     printf("   | "); 
     for(int n=0;n<45;n++)
           printf("*");
     putchar('\n');

     for(int i=0;i<9;i++){
    	printf("(%d)|",i+1);
    	for(int j=0;j<9;j++){
		   if(map[i][j]==88){
    	   	printf(" <$> ");
    	   	continue;
		   }
		   printf("  %-2d ",map[i][j]);
	    }
		putchar('\n');
		 printf("   | ");
        for(int n=0;n<45;n++)
           printf("*");
        putchar('\n');
	 }
	 printf("\n\t分数:%d",socer);
 }
 
 void Creattruemap(int truemap[][9])
 {
 	 int num;
 	 system("CLS");
 	  printf("\t\t/***简易扫雷***/\n\n");
	 printf("\n\t请选择难度：\n\n\t(1).简单\t(2).普通\t(3).困难\n\n\t请选择:");
 	 scanf("%d",&num);
 	 switch (num){
 	 	case 1:num=15; break;
 	 	case 2:num=27; break;
	    case 3:num=36; break;
	  }
	  system("CLS");
	  
 	srand(time(NULL));
 	for(int n=0;n<num;n++){
 		int i=rand()%9;
 		int j=rand()%9;
 		truemap[i][j]=88;
	 }
	
	for(int i=1;i<8;i++){
		for(int j=1;j<8;j++){
			if(truemap[i][j]==88)
			   continue;
			if(truemap[i-1][j+1]==88)
			   truemap[i][j]++;   
			if(truemap[i-1][j]==88)
			   truemap[i][j]++;  
			if(truemap[i-1][j-1]==88)
			   truemap[i][j]++;     
			if(truemap[i][j+1]==88)
			   truemap[i][j]++;   
			if(truemap[i][j-1]==88)
			   truemap[i][j]++; 
			if(truemap[i+1][j+1]==88)
			   truemap[i][j]++;   
			if(truemap[i+1][j]==88)
			   truemap[i][j]++;   
			if(truemap[i+1][j-1]==88)
			   truemap[i][j]++;
		}
	}
	
	for(int i=1;i<8;i++){
		if(truemap[i][0]==88)
		  continue;
		if(truemap[i-1][0]==88)
		   truemap[i][0]++;
		if(truemap[i+1][0]==88)
		   truemap[i][0]++;
		if(truemap[i+1][1]==88)
		   truemap[i][0]++;
		if(truemap[i][1]==88)
		   truemap[i][0]++;
		if(truemap[i-1][1]==88)
		   truemap[i][0]++;
	}
	for(int i=1;i<8;i++){
		if(truemap[i][8]==88)
		  continue;
		if(truemap[i-1][8]==88)
		  truemap[i][8]++;
		if(truemap[i+1][8]==88)
		  truemap[i][8]++;
		if(truemap[i+1][7]==88)
		  truemap[i][8]++;
		if(truemap[i][7]==88)
		  truemap[i][8]++;
		if(truemap[i-1][7]==88)
		  truemap[i][8]++;
	}
	for(int j=1;j<8;j++){
		if(truemap[0][j]==88)
		   continue;
		if(truemap[0][j+1]==88)
		   truemap[0][j]++;
		if(truemap[0][j-1]==88)
		   truemap[0][j]++;
		if(truemap[1][j+1]==88)
		   truemap[0][j]++;
		if(truemap[1][j]==88)
		   truemap[0][j]++;
		if(truemap[1][j-1]==88)
		   truemap[0][j]++;
	}
	for(int j=1;j<8;j++){
		if(truemap[8][j]==88)
	        continue;
	    if(truemap[8][j+1]==88)
	        truemap[8][j]++;
	    if(truemap[8][j-1]==88)
	        truemap[8][j]++;
	    if(truemap[7][j+1]==88)
	        truemap[8][j]++;
	    if(truemap[7][j]==88)
	        truemap[8][j]++;
	    if(truemap[7][j-1]==88)
	        truemap[8][j]++;
	}
	
	if(truemap[0][0]!=88){
		if(truemap[0][1]==88)
		   truemap[0][0]++;
		if(truemap[1][0]==88)
		   truemap[0][0]++;
		if(truemap[1][1]==88)
		   truemap[0][0]++;
	}
	if(truemap[8][0]!=88){
		if(truemap[8][1]==88)
		   truemap[8][0]++;
		if(truemap[7][0]==88)
		   truemap[8][0]++;
		if(truemap[7][1]==88)
		   truemap[8][0]++;
	}
	if(truemap[0][8]!=88){
		if(truemap[0][7]==88)
		   truemap[0][8]++;
		if(truemap[1][8]==88)
		   truemap[0][8]++;
		if(truemap[1][7]==88)
		   truemap[0][8]++;
	}
	if(truemap[8][8]!=88){
		if(truemap[8][7]==88)
		   truemap[8][8]++;
		if(truemap[7][8]==88)
		   truemap[8][8]++;
		if(truemap[7][7]==88)
		   truemap[8][8]++;
	}
 }
