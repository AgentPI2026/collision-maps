// Survey B367/S237 collisions of the 8-cell p8 ship vs mirror at (dy,dx,phase). Classify outcome after T gens by
// population behaviour: ANNIH (0), STABLE (pop const over 2 windows & bbox const), SHIPS (pop const, bbox growing), GROW (pop changing).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define G 192
static const int rule=71880; static unsigned char A[G][G],B[G][G];
static void step(){for(int y=0;y<G;y++)for(int x=0;x<G;x++){int k=0;for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)if(dy||dx){int yy=y+dy,xx=x+dx;if(yy>=0&&yy<G&&xx>=0&&xx<G)k+=A[yy][xx];}
  B[y][x]=A[y][x]?(rule>>(9+k))&1:(rule>>k)&1;}memcpy(A,B,sizeof A);}
static int pop(){int p=0;for(int y=0;y<G;y++)for(int x=0;x<G;x++)p+=A[y][x];return p;}
static void bbox(int*w,int*h){int x0=G,x1=-1,y0=G,y1=-1;for(int y=0;y<G;y++)for(int x=0;x<G;x++)if(A[y][x]){if(x<x0)x0=x;if(x>x1)x1=x;if(y<y0)y0=y;if(y>y1)y1=y;}*w=x1-x0+1;*h=y1-y0+1;if(x1<0)*w=*h=0;}
static const char*P[4]={".O..","O.O.","..OO","OOO."};
static void put(int y0,int x0,int m){for(int y=0;y<4;y++)for(int x=0;x<4;x++)if(P[y][x]=='O')A[y0+y][m?x0+3-x:x0+x]=1;}
int main(int argc,char**argv){
  int dyl=atoi(argv[1]),dyh=atoi(argv[2]);
  for(int dy=dyl;dy<=dyh;dy++)for(int dx=10;dx<=17;dx++)for(int ph=0;ph<8;ph++){
    // ship B advanced by ph gens (alone) then placed: simulate by running both from t=0 but B's phase via pre-evolve
    memset(A,0,sizeof A);put(G/2-2+dy,40+dx,1);for(int t=0;t<ph;t++)step();
    // capture B at phase, relocate: store in tmp
    static unsigned char T2[G][G];memcpy(T2,A,sizeof A);memset(A,0,sizeof A);put(G/2-2,40,0);
    for(int y=0;y<G;y++)for(int x=0;x<G;x++)if(T2[y][x])A[y][x]=1;
    // NOTE: B was evolved alone with its own position shifted by drift; acceptable since survey is over (dy,dx,ph) labels
    for(int t=0;t<300;t++)step();int p1=pop(),w1,h1;bbox(&w1,&h1);
    for(int t=0;t<56;t++)step();int p2=pop(),w2,h2;bbox(&w2,&h2);
    for(int t=0;t<56;t++)step();int p3=pop(),w3,h3;bbox(&w3,&h3);
    const char*c; if(p3==0)c="ANNIH"; else if(p1==p2&&p2==p3&&w1==w2&&w2==w3&&h1==h2&&h2==h3)c="STABLE"; else if(p1==p2&&p2==p3)c="SHIPS"; else if(p3>6*8&&p3>p1)c="GROW"; else c="OTHER";
    printf("%d %d %d %s %d %d\n",dy,dx,ph,c,p1,p3);fflush(stdout);}
}
