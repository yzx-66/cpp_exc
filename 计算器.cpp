#include<stdio.h>
#include<conio.h>
#include<math.h>

float yunsuan(float front,char p,float next);

int main()
{
     float num[30]={0};
     char p[30];
     int n=0;
     float sum=0;
     printf("\t\t������");
     printf("\n\n\n\t ��Ԥ����������������:");
     scanf("%d",&n); 
     printf("\n\t ������(��[Enter]����):");
    
     for(int i=0;i<n;i++){
     	char a;
     	int b[30];
     	int c=0;
     	
     	while(1){
     		a=getch();
     		if(a>57 || a<48) break;
     		b[c]=a-48;
     		printf("%d",b[c]);
     		c++;
		    }
		 
		 for(int j=0;j<c;j++)
		 	num[i]=num[i]+b[j]*pow(10,(c-j-1));
		 
		 if(a=='.'){
		 	 c=0;
		 	 printf(".");
		 	
		     while(1){
     		     a=getch();
     		     if(a>57 || a<48) break;
     		     b[c]=a-48;
     		     printf("%d",b[c]);
     		     c++;
		        }
		 
		     for(int j=0;j<c;j++)
		        num[i]=num[i]+b[j]*pow(10,-(j+1));
		    }
		    
		p[i]=a;
		printf("%c",p[i]);
	 }
	
	for(int i=0;i<n;i++){
		if(i==0){
		  sum=num[i];
		  continue;
	    }
	    if((p[i-1]=='+' || p[i-1]=='-') && (p[i]=='*' || p[i]=='/')){
	    	num[i+1]=yunsuan(num[i],p[i],num[i+1]);
	    	p[i]=p[i-1];
	    	continue;
	    	
		}
		sum=yunsuan(sum,p[i-1],num[i]);
	}
	
	printf("\n\n\n\t������Ϊ��%f\n\n",sum);
	 return 0;
 } 
 
 float yunsuan(float front,char p,float next)
 {
 	switch(p){
	 	case '+':
	 	    return front+next;
	 		break;
	 	case '-':
	 	    return front-next;
	 		break;
	 	case '*':
	 		return front*next;
	 		break;
	 	case '/':
	 		return front/next;
	 		break;
	 	default :
		    return front;
		    break;
    }
}
