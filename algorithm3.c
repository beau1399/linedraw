#include <stdio.h>

#define _ABS(a) ((absval=(a))<0?(-absval):(absval))

void HLIN(int x, int y, int w, int c){ 
 printf( 
  "Pixel row of width %d at (%d,%d) of color %d\n", 
    w,x,y,c 
 ); 
} 
 
void VLIN(int x, int y, int w, int c){ 
 printf( 
  "Pixel col. of height %d at (%d,%d) of color %d\n", 
   w,x,y,c 
 ); 
} 

void alg3(int X1, int Y1, int X2, int Y2, int C){

 int temp,W,DY,DX,s2W,S,absval;

 int s1w,SignY1,SignY2,s1,s2,E;

 if(X2==X1)X2++;
 if(Y2==Y1)Y2++;

 if(X2<X1)
 {
  alg3(X2,Y2,X1,Y1,C);
  return;
 }

 X2--;

 if((Y2-Y1)<0){
  s2=-1;
  Y1--;
  DY=Y1-Y2+1;
 }else{
  s2=1;
  Y2--;
  DY=Y2-Y1+1;
 }

 s1=(X2-X1)<0?-1:1;
 DX=_ABS(X2-X1)+1;

 if(DY>DX){
  temp=DX;
  DX=DY;
  DY=temp;
  W=DX / DY;
  s2W=s2*W;
  S=0;
  E=2*DX;

  if(s2>0){
   SignY1=0;
   SignY2=0;
  }else{
   SignY1=W;
   SignY2=W-1;
  }

  while(S<DY){
   E-=2*W*DY;
   if(E>DY){
    E-=2*DY;
    VLIN(X1,Y1-(SignY1),W+1,C);
    Y1+=(s2W+s2);
   }else{
    VLIN(X1,Y1-(SignY2),W,C);
    Y1+=s2W;
   }

   E+=2*DX;
   S++;
   X1+=s1;
  }

 }else{

  W=DX / DY;
  s1w=s1*W;
  S=0;
  E=2*DX;

  while(S<DY){
   E-=2*W*DY;
   if(E>DY){
    E-=(2*DY);
    HLIN(X1,Y1,W+1,C);
    X1+=(s1w+s1);
   }else{
    HLIN(X1,Y1,W,C);
    X1+=s1w;
   }
 
   E+=2*DX;
   S++;
   Y1+=s2;
  }
 }
}

int main(){
 alg3(1,1,6,23,1);
 return 0;
} 