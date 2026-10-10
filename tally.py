import numpy as np,collections
from insp import step,setup,N
from scipy import ndimage
def final(dy,dx,ph,T=412):
    g=setup(dy,dx,ph)
    for _ in range(T):g=step(g)
    return g
def objects(g):
    d=ndimage.binary_dilation(g,structure=np.ones((3,3)),iterations=2)
    lab,n=ndimage.label(d);res=[]
    for i in range(1,n+1):
        m=(lab==i)&(g==1)
        if m.sum()==0:continue
        ys,xs=np.nonzero(m);sub=m[ys.min():ys.max()+1,xs.min():xs.max()+1]
        # motion test: same object 56 gens later (56=lcm(8,4,7..)) shifted?
        res.append((int(m.sum()),sub.shape,m.sum()))
    return res
import sys
rows=[l.split() for f in __import__('glob').glob('survey_*_*.txt') for l in open(f)]
cls=collections.Counter()
for dy,dx,ph,c,p1,p3 in rows:
    if c not in("STABLE","SHIPS") or int(p3)==8: continue
    g=final(int(dy),int(dx),int(ph));h=g.copy()
    for _ in range(56):h=step(h)
    # moving if sum of cells differs in position
    moved=not np.array_equal(g,h)
    cls[(int(p3),moved)]+=1
for k,v in sorted(cls.items()):print("pop",k[0],"moving" if k[1] else "static",v)
