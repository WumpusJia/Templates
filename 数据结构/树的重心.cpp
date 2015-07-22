vector<int> G[maxn];


int num[maxn];
int rnum;
int res;

int dfs(int u,int fa)
{
    num[u] = 1;
    int t = 1;
    for(int i = 0;i < G[u].size();++i)
        if(G[u][i] != fa)
        {
            int temp = dfs(G[u][i],u);
            num[u] += temp;
            t = max(t,temp);
        }
    t = max(t,n-num[u]);
    if(t < rnum)
    {
        rnum = t;
        res = u;
    }
}

void solve()
{
    rnum = INF;
    dfs(1,-1);
    printf("%d\n",res);
}
