vector<int> G[maxn],ebcc[maxn];
int pre[maxn],iscut[maxn],isbridge[maxn][maxn];
int ebccno[maxn],dfs_clock,ebcc_cnt;


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


void dfs2(int u,int idx)
{
    ebccno[u] = idx;
    ebcc[idx].push_back(u);
    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(!ebccno[v] && !isbridge[u][v])
            dfs2(v,idx);
    }
}


void find_ebcc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(isbridge,0,sizeof(isbridge));
    memset(ebccno,0,sizeof(ebccno));
    dfs_clock = ebcc_cnt = 0;
    for(int i = 0;i < n;++i)
        if(!pre[i]) dfs(i,-1);
    for(int i = 0;i < n;++i)
        if(!ebccno[i])
        {
            ebcc_cnt++;
            dfs2(i,ebcc_cnt);
        }
}
