struct MDST
{
    int n;
    int w[maxn][maxn];
    int vis[maxn];
    int res;
    int removed[maxn];
    int cid[maxn];
    int pre[maxn];
    int in[maxn];
    int max_cid;

    void init(int n)
    {
        this->n = n;
        memset(w,INF,sizeof(w));
    }

    void addEdge(int u,int v,int cost)
    {
        w[u][v] = min(w[u][v],cost);
    }

    int dfs(int u)
    {
        vis[u] = 1;
        int cnt = 1;
        for(int i = 1;i <= n;++i)
            if(!vis[i] && w[u][i] < INF) cnt += dfs(i);
        return cnt;
    }

    bool cycle(int u)
    {
        max_cid++;
        int v = u;
        while(cid[v] != max_cid) { cid[v] = max_cid; v = pre[v]; }
        return v == u;
    }

    void update(int u)
    {
        in[u] = INF;
        for(int i = 1;i <= n;++i)
            if(!removed[i] && w[i][u] < in[u])
            {
                in[u]= w[i][u];
                pre[u] = i;
            }
    }


    bool getRes(int s)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(s) != n) return false;

        memset(removed,0,sizeof(removed));
        memset(cid,0,sizeof(cid));
        for(int i = 1;i <= n;++i) update(i);
        pre[s] = s,in[s] = 0;
        res = max_cid = 0;
        while(1)
        {
            bool have_cycle = false;
            for(int u = 1;u <= n;++u)
                if(u != s && !removed[u] && cycle(u))
                {
                    have_cycle = true;
                    int v = u;
                    do
                    {
                        if(v != u) removed[v] = 1;
                        res += in[v];

                        for(int i = 1;i <= n;++i)
                            if(cid[i] != cid[u] && !removed[i])
                            {
                                if(w[i][v] < INF) w[i][u] =
                                    min(w[i][u],w[i][v]-in[v]);
                                w[u][i] = min(w[u][i],w[v][i]);
                                if(pre[i] == v) pre[i] = u;
                            }
                        v = pre[v];
                    }while(v != u);
                    update(u);
                    break;
                }
                if(!have_cycle) break;
        }
        for(int i = 1;i <= n;++i)
            if(!removed[i]) res += in[i];
        return true;
    }
};






/////////////////////////////////////////////////
typedef double type;

struct Edge
{
    int u,v;
    type w;
}edge[maxn*maxn];
int pre[maxn], id[maxn], vis[maxn];
type in[maxn];

//加边时，如果自环，把w搞成INF

type Directed_MST(int root, int V, int E)
{
    type ret = 0;
    while(true)
    {
        //1.找最小入边
        for(int i = 0; i < V; i++)
           in[i] = INF;
        for(int i = 0; i < E; i++)
        {
            int u = edge[i].u;
            int v = edge[i].v;
            if(edge[i].w < in[v] && u != v)
              {pre[v] = u; in[v] = edge[i].w;}
        }
        for(int i = 0; i < V; i++)
        {
            if(i == root) continue;
            //除了根以外有点没有入边,则根无法到达它
            if(in[i] == INF) return -1;
        }
        //2.找环
        int cnt = 0;
        memset(id, -1, sizeof(id));
        memset(vis, -1, sizeof(vis));
        in[root] = 0;
        for(int i = 0; i < V; i++) //标记每个环
        {
            ret += in[i];
            int v = i;
            //每个点寻找其前序点，要么最终寻找至根部，要么找到一个环
            while(vis[v] != i && id[v] == -1 && v != root)
            {
                vis[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)//缩点
            {
                for(int u = pre[v]; u != v; u = pre[u])
                    id[u] = cnt;
                id[v] = cnt++;
            }
        }
        if(cnt == 0) break; //无环   则break
        for(int i = 0; i < V; i++)
            if(id[i] == -1) id[i] = cnt++;
        //3.建立新图
        for(int i = 0; i < E; i++)
        {
            int u = edge[i].u;
            int v = edge[i].v;
            edge[i].u = id[u];
            edge[i].v = id[v];
            if(id[u] != id[v]) edge[i].w -= in[v];
        }
        V = cnt;
        root = id[root];
    }
    return ret;
}
