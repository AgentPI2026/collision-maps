import numpy as np,sys
rule=71880
Bt=np.array([(rule>>i)&1 for i in range(9)]);St=np.array([(rule>>(9+i))&1 for i in range(9)])
def step(g):
    n=sum(np.roll(np.roll(g,a,0),b,1) for a in(-1,0,1) for b in(-1,0,1) if a or b)
    return np.where(g==1,St[n],Bt[n]).astype(np.uint8)
pat=[".O..","O.O.","..OO","OOO."];N=192
def setup(dy,dx,ph):
    g=np.zeros((N,N),np.uint8)
    for y,r in enumerate(pat):
        for x,c in enumerate(r):
            if c=='O': g[N//2-2+dy+y,40+dx+3-x]=1
    for _ in range(ph):g=step(g)
    for y,r in enumerate(pat):
        for x,c in enumerate(r):
            if c=='O': g[N//2-2+y,40+x]=1
    return g
def comps(g):
    from scipy import ndimage
    lab,n=ndimage.label(g,structure=np.ones((3,3)))
    return [(lab==i) for i in range(1,n+1)]
def describe(dy,dx,ph):
    g=setup(dy,dx,ph)
    for _ in range(412):g=step(g)
    from scipy import ndimage
    d=ndimage.binary_dilation(g,structure=np.ones((3,3)),iterations=2)
    lab,n=ndimage.label(d);out=[]
    for i in range(1,n+1):
        m=(lab==i)&(g==1);ys,xs=np.nonzero(m)
        # displacement over 8 gens
        h=g.copy()
        for _ in range(8):h=step(h)
        m2=(lab==i)
        out.append((int(m.sum()),(ys.min(),ys.max(),xs.min(),xs.max())))
    return out
if __name__=="__main__":
    for t in [(-3,13,1),(-3,13,2),(-2,13,2)]: print(t,describe(*t))
