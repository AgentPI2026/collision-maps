// Collision map: ship A (moving right/any) vs ship B at offsets; outcome = final population & whether debris escapes. Prints JSON.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define G 128
static int rule; static unsigned char A[G][G],B[G][G];
static void step(){for(int y=0;y<G;y++)for(int x=0;x<G;x++){int k=0;for(int dy=-1;dy<=1;dy++)for(int dx=-1;dx<=1;dx++)if(dy||dx){int yy=y+dy,xx=x+dx;if(yy>=0&&yy<G&&xx>=0&&xx<G)k+=A[yy][xx];}
  B[y][x]=A[y][x]?(rule>>(9+k))&1:(rule>>k)&1;}memcpy(A,B,sizeof A);}
static void put(const char*p,int w,int h,int y0,int x0,int mirror){for(int y=0;y<h;y++)for(int x=0;x<w;x++)if(p[y*w+x]=='O'){int xx=mirror?x0+(w-1-x):x0+x;A[y0+y][xx]=1;}}
int main(int argc,char**argv){
  rule=atoi(argv[1]);const char*pat=argv[2];int w=atoi(argv[3]),h=atoi(argv[4]);int mirror=atoi(argv[5]);int T=atoi(argv[6]);
  int X0=atoi(argv[9]);int dy0=-12,dy1=12,dx0=atoi(argv[7]),dx1=atoi(argv[8]);
  printf("{\"dy0\":%d,\"dy1\":%d,\"dx0\":%d,\"dx1\":%d,\"pop\":[",dy0,dy1,dx0,dx1);
  for(int dy=dy0;dy<=dy1;dy++){printf("[");for(int dx=dx0;dx<=dx1;dx++){
    memset(A,0,sizeof A);put(pat,w,h,G/2-h/2,X0,0);put(pat,w,h,G/2-h/2+dy,X0+dx,mirror);
    for(int t=0;t<T;t++)step();int pop=0;for(int y=0;y<G;y++)for(int x=0;x<G;x++)pop+=A[y][x];
    printf("%d%s",pop,dx<dx1?",":"");}printf("]%s",dy<dy1?",":"");}
  printf("]}\n");}
