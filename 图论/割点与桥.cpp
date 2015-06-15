vector<int> G[maxn];
int pre[maxn],iscut[maxn],isbridge[maxn][maxn],dfs_clock;


int dfs(int u,int fa)
{
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(!pre[v])
        {
            child++;
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv >= pre[u])
                iscut[u] = true;
            if(lowv > pre[u])
                isbridge[u][v] = isbridge[v][u] = true;
        }
        else if(pre[v] < pre[u] && v != fa)
            lowu = min(lowu,pre[v]);
    }
    if(fa < 0 && child == 1) iscut[u] = 0;
  //  low[u] = lowu;
    return lowu;
}


void CutAndBridge(int n)
{
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(isbridge,0,sizeof(isbridge));
    dfs_clock = 0;
    for(int i = 0;i < n;++i)
        if(!pre[i]) dfs(i,-1);
}
