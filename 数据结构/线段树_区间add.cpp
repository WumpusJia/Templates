Node p[maxn<<2];

void pushdown(int u)
{
    p[u<<1].cnt += p[u].cnt;
    p[u<<1|1].cnt += p[u].cnt;
    p[u].cnt = 0;
}

void pushup(int u,int L,int R)
{
    int m = (L+R)/2;
    p[u].sum = p[u<<1].cnt*(m-L+1)+p[u<<1].sum +
    p[u<<1|1].cnt*(R-m)+p[u<<1|1].sum;
}

void update(int cL,int cR,int val,int L,int R,int u)
{

    if(cL <= L && R <= cR)
    {
        p[u].cnt += val;
    }
    else
    {
        pushdown(u);
        int m = (L+R)/2;
        if(cL <= m)
            update(cL,cR,val,L,m,u<<1);
        if(cR > m)
            update(cL,cR,val,m+1,R,u<<1|1);
        pushup(u,L,R);
    }

}

int query(int cL,int cR,int L,int R,int u)
{
    if(cL <= L && R <= cR)
    {
        return p[u].sum + (R-L+1)*p[u].cnt;
    }
    else
    {
        pushdown(u);
        int m = (L+R)/2;
        int res = 0;
        if(cL <= m)
            res += query(cL,cR,L,m,u<<1);
        if(cR > m)
            res += query(cL,cR,m+1,R,u<<1|1);
        pushup(u,L,R);
        return res;
    }
}


