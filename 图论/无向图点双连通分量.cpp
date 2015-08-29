int pre[maxn], iscut[maxn], bccno[maxn], dfs_clock,bcc_cnt;
vector<int> G[maxn], bcc[maxn];
//bcc_nct 从1开始
//vector bcc存储了每个连通分量中的所有点
//bccno[u] 表示u所属的双连通分量号
//(由于存在点处于多个双连通分量，所以每次使用bccno时,需要对bcc中所有点
//更新其bbcno
struct Edge
{
    int u,v;
    Edge(int u = 0,int v = 0):u(u),v(v) {}
};

stack<Edge> S;

int dfs(int u,int fa)
{
    int lowu = pre[u] = ++dfs_clock;
    int child = 0;
    for(int i = 0;i < G[u].size(); ++i)
    {
        int v = G[u][i];
        Edge e = Edge(u,v);
        if(!pre[v])
        {
            S.push(e);
            child++;
            int lowv = dfs(v,u);
            lowu = min(lowu,lowv);
            if(lowv >= pre[u])
            {
                iscut[u] = true;
                bcc_cnt++; bcc[bcc_cnt].clear();
                for(;;)
                {
                    Edge x = S.top(); S.pop();
                    if(bccno[x.u] != bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(x.u);
                        bccno[x.u] = bcc_cnt;
                    }
                    if(bccno[x.v] != bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(x.v);
                        bccno[x.v] = bcc_cnt;
                    }
                    if(x.u == u && x.v == v) break;
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa)
        {
            S.push(e);
            lowu = min(lowu,pre[v]);
        }
    }
    if(fa < 0 && child == -1) iscut[u] = false;
    return lowu;
}

void find_bcc(int n)
{
    memset(pre,0,sizeof(pre));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    dfs_clock = bcc_cnt = 0;
    for(int i = 0;i < n;++i)
        if(!pre[i]) dfs(i,-1);
}
