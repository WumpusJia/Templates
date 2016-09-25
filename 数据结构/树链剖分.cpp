//对子树的查询和修改 可以dfs中记录In和Out

int fa[maxn],son[maxn],size[maxn],deep[maxn];
int id[maxn],top[maxn];
int idx;

////////DFS版本（极易爆栈，windows下n为几万就会爆...////

void dfs1(int u,int f,int d)
{
    fa[u] = f;
    deep[u] = d;
    size[u] = 1;

    int Max = 0;
    int ps = 0;

    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != f)
        {
            dfs1(v,u,d+1);
            size[u] += size[v];
            if(Max < size[v])
            {
                Max = size[v];
                ps = v;
            }
        }
    }

    son[u] = ps;
}


void dfs2(int u,int f,int tp)
{
    id[u] = idx++;
    top[u] = tp;
    if(son[u] != 0) dfs2(son[u],u,top[u]);

    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != f && v != son[u])
            dfs2(v,u,v);
    }
}

//////////////////////////////////////////////

////////////////////////BFS版本(较慢，防爆栈)////////////////////
int seq[maxn];

void bfs(int root)
{
    int prev = 0,rear = 1;
    seq[prev] = root;
    fa[root] = 0;
    deep[root] = 0;

    while(prev < rear)
    {
        int u = seq[prev++];
        size[u] = 1;
        for(int i = 0;i < G[u].size();++i)
        {
            int v = G[u][i];
            if(v != fa[u])
            {
                fa[v] = u;
                deep[v] = deep[u]+1;
                seq[rear++] = v;
            }
        }
    }

    size[0] = 0;
    memset(son,0,sizeof(son));
    for(int i = rear-1;i >= 0;--i)
    {
        int u = seq[i];
        if(fa[u] != 0)
        {
            size[fa[u]] += size[u];
            if(size[son[fa[u]]] < size[u])
                son[fa[u]] = u;
        }
    }

    top[root] = root;
    id[root] = idx;
    prev = 0,rear = 1;

    while(prev < rear)
    {
        int u = seq[prev++];
        int now = id[u];
        if(son[u] != 0)
        {
            id[son[u]] = now+1;
            now += size[son[u]];
            top[son[u]] = top[u];
            seq[rear++] = son[u];
        }

        for(int i = 0;i < G[u].size();++i)
        {
            int v = G[u][i];
            if(v != fa[u] && v != son[u])
            {
                id[v] = now+1;
                now += size[v];
                top[v] = v;
                seq[rear++] = v;
            }
        }
    }
}

////////////////////////////////////////////

int num[maxn<<2];

void update(int cL,int cR,int val,int L,int R,int u)
{
    if(cL <= L && R <= cR)
    {
        num[u] += val;
    }
    else
    {
        int m = (L+R)/2;
        if(cL <= m)
            update(cL,cR,val,L,m,u<<1);
        if(cR > m)
            update(cL,cR,val,m+1,R,u<<1|1);
    }
}

int query(int p,int L,int R,int u,int add)
{
    if(L == R)
        return num[u]+add;
    else
    {
        int m = (L+R)/2;
        if(p <= m)
            return query(p,L,m,u<<1,add+num[u]);
        else
            return query(p,m+1,R,u<<1|1,add+num[u]);
    }
}


void add(int u,int v,int val)
{
    int fu = top[u],fv = top[v];
    while(fu != fv)
    {
        if(deep[fu] < deep[fv])
        {
            swap(fu,fv);
            swap(u,v);
        }
        update(id[fu],id[u],val,1,n,1);
        u = fa[fu],fu = top[u];
    }
   // if(u == v) return;   //注意如果是求链上的点，不能加这句话
    if(deep[u] > deep[v]) swap(u,v);
    update(id[u],id[v],val,1,n,1);

    /*
    如果是将边权变成点权
    if(id[u]+1 <= id[v])
    {
        update(id[u]+1,id[v],val,1,n,1);
    }

    */
}

//如果区间查询(边权)　需要根据链的顺序进行计算

int solve(int u,int v)
{

    if(dfsid[u] > dfsid[v]) swap(u,v);　//dfsid为dfs的顺序

    Node ru,rv;
    bool hasu = false;
    bool hasv = false;

    int fu = top[u],fv = top[v];

    while(fu != fv)
    {
        if(deep[fu] >= deep[fv])
        {
                Node t = query(id[fu],id[u],1,n,1);
                swap(t.lft,t.right);
                if(!hasu)
                {
                    hasu = true;
                    ru = t;
                }
                else
                    ru = cal(ru,t);
            u = fa[fu],fu = top[u];
        }
        else
        {
                Node t = query(id[fv],id[v],1,n,1);
                if(!hasv)
                {
                    hasv = true;
                    rv = t;
                }
                else
                    rv = cal(t,rv);

            v = fa[fv],fv = top[v];
        }

    }

    if(u == v)
    {
        if(hasu && hasv)
            return cal(ru,rv).sum;
        else if(hasu)
            return ru.sum;
        else if(hasv)
            return rv.sum;
        else
            return 0;

    }   //注意如果是求链上的点，不能加这句话


    if(deep[u] >= deep[v])
    {
        if(id[v]+1 <= id[u])
        {
            Node t = query(id[v]+1,id[u],1,n,1);
            swap(t.lft,t.right);
            if(hasu)
                ru = cal(ru,t);
            else
            {
                hasu = 1;
                ru = t;
            }
        }
    }
    else
    {
        if(id[u]+1 <= id[v])
        {
            Node t = query(id[u]+1,id[v],1,n,1);
            if(hasu)
                ru = cal(ru,t);
            else
            {
                hasu = 1;
                ru = t;
            }
        }
    }

    if(hasu && hasv)
        return cal(ru,rv).sum;
    else if(hasu)
        return ru.sum;
    else if(hasv)
        return rv.sum;
    else
        return 0;
}



int get(int u)
{
    return query(id[u],1,n,1,0)+save[u];
}


void init()
{
   // dfs1(1,0,1);
    idx = 1;
    bfs(1);
 //   dfs2(1,0,1);
    memset(num,0,sizeof(num));
}

