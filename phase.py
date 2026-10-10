import numpy as np
rule=71880
Bt=np.array([(rule>>i)&1 for i in range(9)]);St=np.array([(rule>>(9+i))&1 for i in range(9)])
def step(g):
    n=sum(np.roll(np.roll(g,a,0),b,1) for a in(-1,0,1) for b in(-1,0,1) if a or b)
    return np.where(g==1,St[n],Bt[n]).astype(np.uint8)
pat=[".O..","O.O.","..OO","OOO."]
def ship_at_phase(k,N=24):
    g=np.zeros((N,N),np.uint8)
    for y,r in enumerate(pat):
        for x,c in enumerate(r):
            if c=='O':g[10+y,10+x]=1
    for _ in range(k):g=step(g)
    ys,xs=np.nonzero(g);return g[ys.min():ys.max()+1,xs.min():xs.max()+1].copy()
def collide(dy,dx,kB,T=140,N=128):
    a=ship_at_phase(0);b=ship_at_phase(kB)[:,::-1]
    g=np.zeros((N,N),np.uint8);y0=N//2-2
    g[y0:y0+a.shape[0],10:10+a.shape[1]]|=a
    g[y0+dy:y0+dy+b.shape[0],10+dx:10+dx+b.shape[1]]|=b
    for _ in range(T):g=step(g)
    return int(g.sum())
for dy in (-3,0):
  print("dy",dy)
  for kB in range(0,8):
    print(" phase",kB,[collide(dy,dx,kB) for dx in range(14,22)])
