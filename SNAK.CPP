#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <iostream.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>
int first=0;
int last=1;
int score;
int direction[1000]={75};
int bend[1000];
int body[4]={150,183,310,183};
int borderX[2]={5,450};
int borderY[2]={360,5};
int foodX;
int foodY;
int delay_cons=15;
void food(int x,int y){
	for(int k=-3;k<=3;k++){
		line(x-3,y+k,x+3,y+k);
	}
}
int collapse(int x,int array[],int size){
	for(int i=0;i<size;i++){
		if(x==array[i]){
			return 1;
		}
	}
	return 0;
}
int bodyCollapse(int position[]){
	for(int w=0; w<last-first-1;w++){
	       //	printf("wwww%d",w);
		double  x1=position[2*w];
		double  y1=position[2*w+1];
		double  x2=position[2*w+2];
		double  y2=position[2*w+3];
	       //	printf("%d %d %d %d\n",x1,y1,x2,y2);
	       for(int e=-3;e<=3;e++){
		if (x1==x2 & x2==body[0] & (body[1]==y1+e | body[1]==y2+e)){
			return 1;
		}
		if((y1-body[1]+e)/(y2-body[1]+e)<0 & x1==x2 & x2==body[0]){
			return 1;
		}
		if(y1==y2 & y2==body[1] & (body[0]==x1+e | body[0]==x2+e)){
			return 1;
		}
		if (((x1-body[0]+e)/(x2-body[0]+e))<0 & y1==y2 & y2==body[1]){
			return 1;
		}
		  }
	}
	 return 0;
	}
void border(){
	line(5,5,450,5);
	line(450,5,450,360);
	line(450,360,5,360);
	line(5,360,5,5);
	settextstyle(2,HORIZ_DIR,5);
	char sco[50];
	sprintf(sco,"Score:%d",score);
	outtextxy(370,10,sco);
}

void wholeBodyLeft(int z){
	if (z==last-1 && first==last-1){
		for(int i=-3;i<=3;i++){
			line(body[0],body[1]+i,body[2],body[3]+i);
			}
		body[2]=body[2]-1;
		body[0]=body[0]-1;
	}else if (z==last-1){
		//printf("Y");
		for(int i=-3;i<=3;i++){
			line(body[0],body[1]+i,bend[2*z-2]+3,bend[2*z-1]+i);
			//	printf("%d %d",(bend[2*z-2],bend[2*z-1]));
			}
		body[0]=body[0]-1 ;
	}else if (z==first){
		//printf("q");
		for(int i=-3;i<=3;i++){
			line(bend[2*z]-3,bend[2*z+1]+i,body[2],body[3]+i);
			}
		body[2]=body[2]-1;
		if(body[2]==bend[2*z] && body[3]==bend[2*z+1]){
			//printf("%d,%d ",(body[2],body[2*z]));
			first=first+1;
		   //	printf("%d",first);
		 //	printf("xxxxx %d",first);
		}
	}else{
		for(int i=-3;i<=3;i++){
			line(bend[2*z-2]+3,bend[2*z-1]+i,bend[2*z]-3,bend[2*z+1]+i);
		}
	}
}
void wholeBodyRight(int z){
	if (z==last-1 && first==last-1){
		for(int i=-3;i<=3;i++){
			line(body[0],body[1]+i,body[2],body[3]+i);
			}
		body[0]=body[0]+1;
		body[2]=body[2]+1;
	}else if (z==last-1){
	       //	printf("Y");
		for(int i=-3;i<=3;i++){
			line(body[0],body[1]+i,bend[2*z-2]-3,bend[2*z-1]+i);
			}
		body[0]=body[0]+1 ;
	}else if (z==first){
	       //	printf("q");
		for(int i=-3;i<=3;i++){
			line(bend[2*z],bend[2*z+1]+i,body[2]+3,body[3]+i);
			}
		body[2]=body[2]+1;
		if(body[2]==bend[2*z] && bend[2*z+1]==body[3]){
			first=first+1;
		       //	printf("xxxxx %d",first);
		}
	}else{
		for(int i=-3;i<=3;i++){
			line(bend[2*z-2]-3,bend[2*z-1]+i,bend[2*z]+3,bend[2*z+1]+i);
		}
	       //	printf("w");
	}
}
void wholeBodyDown(int z){
	if (z==last-1 && first==last-1){
	  //	printf("z");
		for(int i=-3;i<=3;i++){
			line(body[0]+i,body[1],body[2]+i,body[3]);
			}
		body[1]=body[1]+1;
		body[3]=body[3]+1;
	}else if (z==last-1){
	       //	printf("Y");
		for(int i=-3;i<=3;i++){
			line(body[0]+i,body[1],bend[2*z-2]+i,bend[2*z-1]-3);
			}
		body[1]=body[1]+1 ;
	}else if (z==first){
	       //	printf("q");
		for(int i=-3;i<=3;i++){
			line(bend[2*z]+i,bend[2*z+1]+3,body[2]+i,body[3]);
			}
		body[3]=body[3]+1;
		if(body[3]==bend[2*z+1] && body[2]==bend[2*z]){
			first=first+1;
		 //	printf("xxxxx %d",first);
		}
	}else{
		for(int i=-3;i<=3;i++){
			line(bend[2*z-2]+i,bend[2*z-1]-3,bend[2*z]+i,bend[2*z+1]+3);
		}
	       //	printf("w");
	}
}
void wholeBodyUp(int z){
	if (z==last-1 && first==last-1){
	  //	printf("z");
		for(int i=-3;i<=3;i++){
			line(body[0]+i,body[1],body[2]+i,body[3]);
			}
		body[1]=body[1]-1;
		body[3]=body[3]-1;
	}else if (z==last-1){
	       //	printf("Y");
		for(int i=-3;i<=3;i++){
			line(body[0]+i,body[1],bend[2*z-2]+i,bend[2*z-1]+3);
			}
		body[1]=body[1]-1 ;
	}else if (z==first){
	       //	printf("q");
		for(int i=-3;i<=3;i++){
			line(bend[2*z]+i,bend[2*z+1]-3,body[2]+i,body[3]);
			}
		body[3]=body[3]-1;
		if(body[3]==bend[2*z+1] && bend[2*z]==body[2]){
			first=first+1;
		       //	printf("xxytyteuitxxx %d",first);
		}
	}else{
		for(int i=-3;i<=3;i++){
			line(bend[2*z-2]+i,bend[2*z-1]+3,bend[2*z]+i,bend[2*z+1]-3);
		}
	       //	printf("w");
	}
}
void main(){
	int a;
	time_t t;
	a=time(&t);
	srand(a);
	foodX=random(445-10+1)+10;
	foodY=random(355-10+1)+10;
	int dir=0;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"c:\\turboc3\\bgi");
	while(1){
		food(foodX,foodY);
		border();
		if (kbhit()){
			dir=getch();
		       if (dir==72 && direction[last-1]!=72 && direction[last-1]!=80){
				direction[last]=72;
				bend[2*last-2]=body[0];
				bend[2*last-1]=body[1];
				last=last+1;
		       }
		       if (dir==75 && direction[last-1]!=75 && direction[last-1]!=77){
				direction[last]=75;
				bend[2*last-2]=body[0];
				bend[2*last-1]=body[1];
				last=last+1;
		       }
		       if (dir==80 && direction[last-1]!=80 && direction[last-1]!=72){
				direction[last]=80;
				bend[2*last-2]=body[0];
				bend[2*last-1]=body[1];
				last=last+1;
		       }
		       if (dir==77 && direction[last-1]!=77 && direction[last-1]!=75){
				direction[last]=77;
				bend[2*last-2]=body[0];
				bend[2*last-1]=body[1];
				last=last+1;
		       }
		}
		for(int r=last -1;r>=first;r--){
		      //	printf("%d ",r);
		       //	printf("%d %d",first);
		       int dir=direction[r];
		       if(dir==72){
				wholeBodyUp(r);
		       }else if(dir ==80){
				wholeBodyDown(r);
		       }else if(dir ==75){
				wholeBodyLeft(r);
		       }else{
				wholeBodyRight(r);
		       }
		}
		delay(delay_cons);
		int jun[50];
		for(int q=2*last-3;q>=2*first;q--){
			if (q%2==1){
				jun[2*last-3-q+1]=bend[q];

			}else{
				jun[2*last-3-q-1]=bend[q];
			}
		}
		jun[2*(last-first-1)]=body[2];
		jun[2*(last-1-first)+1]=body[3];
		//printf("%d",bodyCollapse(jun));
		if (bodyCollapse(jun) |collapse(body[0],borderX,2)|collapse(body[1],borderY,2)){
			break;
		}
	       //	getch();
	       if (-3<=body[0]-foodX & body[0]-foodX<=3 & body[1]-foodY<=3 & -3<=body[1]-foodY){
			time_t t;
			a=time(&t);
			srand(a);
			foodX=random(444-11+1)+11;
			foodY=random(354-11+1)+11;
			score=score+1;
			if (direction[last-1]==75){
				body[0]=body[0]-5;
			}else if( direction[last -1]==77){
				body[0]=body[0] +5;
			}else if(direction[last-1]==72){
				body[1]=body[1]-5;
			}else{
				body[1]=body[1]+5;
			}
	       if (score%5==0 & delay_cons>=6){
			delay_cons=delay_cons-2;
	       }
	       }
	       cleardevice();
	}
	settextstyle(10,HORIZ_DIR,7);
	outtextxy(50,50,"Game Over");
	getch();

}
