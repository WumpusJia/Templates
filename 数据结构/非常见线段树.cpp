////////////区间add + 求和/////////////////

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


/////////////区间add + 区间最值修改//////////////
struct Node
{
    LL add,Max,Min;
};

Node p[maxn<<2];


LL A[maxn];

void pushup(int u)
{
    p[u].Max = max(p[u<<1].Max,p[u<<1|1].Max);
    p[u].Min = min(p[u<<1].Min,p[u<<1|1].Min);
}


void pushdown(int u)
{
    if(p[u].add)
    {
        p[u<<1].Max += p[u].add;
        p[u<<1].Min += p[u].add;
        p[u<<1].add += p[u].add;

        p[u<<1|1].Max += p[u].add;
        p[u<<1|1].Min += p[u].add;
        p[u<<1|1].add += p[u].add;
        p[u].add = 0;
    }

    p[u<<1].Max = min(p[u<<1].Max,p[u].Max);
    p[u<<1].Max = max(p[u<<1].Max,p[u].Min);
    p[u<<1].Min = max(p[u<<1].Min,p[u].Min);
    p[u<<1].Min = min(p[u<<1].Min,p[u].Max);

    p[u<<1|1].Max = min(p[u<<1|1].Max,p[u].Max);
    p[u<<1|1].Max = max(p[u<<1|1].Max,p[u].Min);
    p[u<<1|1].Min = max(p[u<<1|1].Min,p[u].Min);
    p[u<<1|1].Min = min(p[u<<1|1].Min,p[u].Max);

}

void build(int L,int R,int u)
{
    p[u].add = 0;
    if(L == R)
    {
        p[u].Max = p[u].Min = A[L];
    }
    else
    {
        int m = (L+R)/2;
        build(L,m,u<<1);
        build(m+1,R,u<<1|1);
        pushup(u);
    }
}


void segadd(int cL,int cR,LL val,int L,int R,int u)
{
    if(cL <= L && R <= cR)
    {
        p[u].add += val;
        p[u].Max += val;
        p[u].Min += val;
    }
    else
    {
        pushdown(u);
        int m = (L+R)/2;
        if(cL <= m)
            segadd(cL,cR,val,L,m,u<<1);
        if(cR > m)
            segadd(cL,cR,val,m+1,R,u<<1|1);
        pushup(u);
    }
}

void segmin(int cL,int cR,LL val,int L,int R,int u)
{
    if(cL <= L && R <= cR)
    {
        p[u].Max = min(p[u].Max,val);
        p[u].Min = min(p[u].Min,val);
    }
    else
    {
        pushdown(u);
        int m = (L+R)/2;
        if(cL <= m)
            segmin(cL,cR,val,L,m,u<<1);
        if(cR > m)
            segmin(cL,cR,val,m+1,R,u<<1|1);
        pushup(u);
    }
}

void segmax(int cL,int cR,LL val,int L,int R,int u)
{
    if(cL <= L && R <= cR)
    {
        p[u].Max = max(p[u].Max,val);
        p[u].Min = max(p[u].Min,val);
    }
    else
    {
        pushdown(u);
        int m = (L+R)/2;
        if(cL <= m)
            segmax(cL,cR,val,L,m,u<<1);
        if(cR > m)
            segmax(cL,cR,val,m+1,R,u<<1|1);
        pushup(u);
    }
}

Node cal(const Node& A,const Node& B)
{
    Node C;
    C.Max = max(A.Max,B.Max);
    C.Min = min(A.Min,B.Min);
    return C;
}

Node query(int cL,int cR,int L,int R,int u)
{
    if(cL <= L && R <= cR)
        return p[u];
    else
    {
        pushdown(u);
        int m = (L+R)/2;
        if(cR <= m) return query(cL,cR,L,m,u<<1);
        else if(cL > m) return query(cL,cR,m+1,R,u<<1|1);
        else return cal(query(cL,cR,L,m,u<<1),
                    query(cL,cR,m+1,R,u<<1|1));
    }
}


///////区间max + 求和///////////////////
struct Node
{
    int tag,maxtag;
    int len,cover;
    int Max;
    LL Sum;
};

Node p[maxn<<4];

Node gao(Node c,int tag)
{
    if(tag != -1)
    {
        if(c.len != c.cover) c.Max = tag;
        c.maxtag = tag;
        c.Sum += (LL)(c.len-c.cover)*tag;
        c.cover = c.len;
    }
    return c;
}

Node merge(Node a,Node b,int tag)
{
    Node c;
    c.tag = tag;
    c.maxtag = max(a.maxtag,b.maxtag);
    c.len = a.len+b.len;
    c.cover = a.cover+b.cover;
    c.Max = max(a.Max,b.Max);
    c.Sum = a.Sum + b.Sum;
    return gao(c,tag);
}

void build(int L,int R,int u)
{
    p[u].tag = -1;
    p[u].len = R-L+1;
    if(L == R)
    {
        int t;
        scanf("%d",&t);
       // read(t);
        p[u].tag = p[u].maxtag = p[u].Max = p[u].Sum = t;
        p[u].cover = 1;
    }
    else
    {
        int m = (L+R)/2;
        build(L,m,u<<1);
        build(m+1,R,u<<1|1);
        p[u] = merge(p[u<<1],p[u<<1|1],-1);
    }
}


Node query(int cL,int cR,int L,int R,int u)
{
    if(cL <= L && R <= cR)
        return p[u];
    else
    {
        int m = (L+R)/2;
        if(cR <= m)
            return gao(query(cL,cR,L,m,u<<1),p[u].tag);
        if(cL > m)
            return gao(query(cL,cR,m+1,R,u<<1|1),p[u].tag);
        else
            return merge(query(cL,cR,L,m,u<<1),
                        query(cL,cR,m+1,R,u<<1|1),p[u].tag);
    }
}


void Clear(int u,int tag)
{
    if(tag > p[u].maxtag) return;
    if(p[u].tag >= tag)
        p[u].tag = -1;

    if(p[u].len > 1)
    {
        Clear(u<<1,tag);
        Clear(u<<1|1,tag);
    }

    if(p[u].len == 1)
    {
        int t = (p[u].tag == -1)?0:p[u].tag;
        p[u].maxtag = p[u].Max = p[u].Sum = t;
        p[u].cover = (p[u].tag != -1);
    }
    else
        p[u] = merge(p[u<<1],p[u<<1|1],p[u].tag);
}


void update(int cL,int cR,int val,int L,int R,int u)
{
    if(p[u].tag != -1 && val >= p[u].tag) return;
    if(cL <= L && R <= cR)
    {
        Clear(u,val);
        p[u].tag = val;
        if(L == R)
        {
            p[u].tag = p[u].maxtag = p[u].Max = p[u].Sum = val;
            p[u].cover = (p[u].tag != -1);
        }
        else
            p[u] = merge(p[u<<1],p[u<<1|1],p[u].tag);
    }
    else
    {
        int m = (L+R)/2;
        if(cL <= m)
            update(cL,cR,val,L,m,u<<1);
        if(cR > m)
            update(cL,cR,val,m+1,R,u<<1|1);
        p[u] = merge(p[u<<1],p[u<<1|1],p[u].tag);
    }
}
