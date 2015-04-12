int n;
bool vis[maxn];
vector<int> G[maxn];
int match[maxn];

bool dfs(int u)
{
    for(int i = 0; i < G[u].size();++i)
    {
        int v = G[u][i];
        if(!vis[v])
        {
            vis[v] = 1;
            int t = match[v]; match[v] = u;
            if(t == -1 || dfs(t)) return true;
            match[v] = t;
        }
    }
    return false;
}

int solve()
{
    int ans = 0;
    memset(match,-1,sizeof(match));
    for(int i = 0;i < n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    return ans;
}
