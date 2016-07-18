memset(vis,0,sizeof(vis));
memset(d,INF,sizeof(d));
vis[0] = 1;
for(int i = 0;i < n;++i)
    d[i] = cal(0,i);

int res = 0;
for(int i = 1;i < n;++i)
{
    int Min = INF,v;
    for(int j = 1;j < n;++j)
        if(!vis[j] && d[j] < Min)
            Min = d[j],v = j;
    vis[v] = 1;
    res += Min;
    for(int j = 0;j < n;++j)
    {
        int t = cal(v,j);
        if(!vis[j] && d[j] > t)
            d[j] = t;
    }
}

//////////////////堆优化////////////
struct Edge
{
    int from,to,w;
    Edge(int u,int v,int w):from(u),to(v),w(w) {}
    bool operator < (const Edge& rhs) const {
        return w > rhs.w;
    }
};



struct Prim
{
    int n;
    vector<int> G[maxn];
    vector<Edge> edges;
    bool vis[maxn];


    void init(int n)
    {
        this->n = n;
        for(int i = 1;i <= n;++i) G[i].clear();
        edges.clear();
    }

    void addEdge(int from,int to,int w)
    {
        edges.push_back(Edge(from,to,w));
        int m = edges.size();
        G[from].push_back(m-1);
    }

    int getRes(int s)
    {
        priority_queue<Edge> Q;
        memset(vis,0,sizeof(vis));
        vis[s] = 1;
        for(int i = 0;i < G[s].size();++i)
            Q.push(edges[G[s][i]]);
        int remain = n-1;
        int res = 0;
        while(!Q.empty() && remain)
        {
            Edge now = Q.top(); Q.pop();
            int u = now.to;
            if(vis[u]) continue;
            res += now.w;
            remain--;
            vis[u] = 1;
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(!vis[e.to])
                    Q.push(edges[G[u][i]]);
            }
        }
        return res;
    }

};
