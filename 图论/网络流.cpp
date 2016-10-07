struct SAP
{
    int n,s,t;
    vector<int> G[maxn];
    vector<Edge> edges;
    int a[maxn];
    int p[maxn];


    void init(int n)
    {
        this->n = n;
        for(int i = 0;i <= n;++i) G[i].clear();
        edges.clear();
    }

    void addEdge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        int m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    int getRes(int s,int t)
    {
        int flow = 0;
        for(;;)
        {
            memset(a,0,sizeof(a));
            queue<int> Q;
            Q.push(s);
            a[s] = INF;
            while(!Q.empty())
            {
                int x = Q.front(); Q.pop();
                for(int i = 0;i < G[x].size();++i)
                {
                    Edge& e = edges[G[x][i]];
                    if(!a[e.to] && e.cap > e.flow)
                    {
                        p[e.to] = G[x][i];
                        a[e.to] = min(a[x],e.cap-e.flow);
                        Q.push(e.to);
                    }
                }
                if(a[t]) break;
            }
            if(!a[t]) break;
            for(int u = t;u != s;u = edges[p[u]].from)
            {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
};



//////////////////////////////
struct Edge
{
    int from,to,cap,flow;
    Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f) {}
};


struct Dinic
{
    int s,t;
    vector<int> G[maxn];
    vector<Edge> edges;
    bool vis[maxn];
    int d[maxn];
    int cur[maxn];


    void init()
    {
        for(int i = 0;i <= maxn;++i) G[i].clear();
        edges.clear();
    }

    void addEdge(int from,int to,int cap)
    {
        edges.push_back(Edge(from,to,cap,0));
        edges.push_back(Edge(to,from,0,0));
        int m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis,0,sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x,int a)
    {
        if(x == t || a == 0) return a;
        int flow = 0,f;
        for(int& i = cur[x];i < G[x].size();++i)
        {
            Edge&e = edges[G[x][i]];
            if(d[x] +1 == d[e.to] &&
                (f = DFS(e.to,min(a,e.cap-e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }

    int getRes(int s,int t)
    {
        this-> s = s; this->t = t;
        int flow = 0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            flow += DFS(s,INF);
        }
        return flow;
    }
};







/////////////////////////////////////////////

int source;         // 源点
int sink;           // 汇点
int p[max_nodes];   // 可增广路上的上一条弧的编号
int num[max_nodes]; // 和 t 的最短距离等于 i 的节点数量
int cur[max_nodes]; // 当前弧下标
int d[max_nodes];   // 残量网络中节点 i 到汇点 t 的最短距离
bool visited[max_nodes];

// 预处理, 反向 BFS 构造 d 数组
bool bfs()
{
    memset(visited, 0, sizeof(visited));
    queue<int> Q;
    Q.push(sink);
    visited[sink] = 1;
    d[sink] = 0;
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();
        for (iterator_t ix = G[u].begin(); ix != G[u].end(); ++ix)
        {
            Edge &e = edges[(*ix)^1];
            if (!visited[e.from] && e.capacity > e.flow)
            {
                visited[e.from] = true;
                d[e.from] = d[u] + 1;
                Q.push(e.from);
            }
        }
    }
    return visited[source];
}

// 增广
int augment()
{
    int u = sink, df = __inf;
    // 从汇点到源点通过 p 追踪增广路径, df 为一路上最小的残量
    while (u != source)
    {
        Edge &e = edges[p[u]];
        df = min(df, e.capacity - e.flow);
        u = edges[p[u]].from;
    }
    u = sink;
    // 从汇点到源点更新流量
    while (u != source)
    {
        edges[p[u]].flow += df;
        edges[p[u]^1].flow -= df;
        u = edges[p[u]].from;
    }
    return df;
}

int max_flow()
{
    int flow = 0;
    bfs();
    memset(num, 0, sizeof(num));
    for (int i = 0; i < num_nodes; i++) num[d[i]]++;
    int u = source;
    memset(cur, 0, sizeof(cur));
    while (d[source] < num_nodes)
    {
        if (u == sink) {
            flow += augment();
            u = source;
        }
        bool advanced = false;
        for (int i = cur[u]; i < G[u].size(); i++)
        {
            Edge& e = edges[G[u][i]];
            if (e.capacity > e.flow && d[u] == d[e.to] + 1)
            {
                advanced = true;
                p[e.to] = G[u][i];
                cur[u] = i;
                u = e.to;
                break;
            }
        }
        if (!advanced)
        { // retreat
            int m = num_nodes - 1;
            for (iterator_t ix = G[u].begin(); ix != G[u].end(); ++ix)
                if (edges[*ix].capacity > edges[*ix].flow)
                    m = min(m, d[edges[*ix].to]);
            if (--num[d[u]] == 0) break; // gap 优化
            num[d[u] = m+1]++;
            cur[u] = 0;
            if (u != source)
                u = edges[p[u]].from;
        }
    }
    return flow;
}


//////////////////////////
//最小费用

struct Edge
{
    int from,to,cap,flow,cost;
    Edge(int u,int v,int c,int f,int w):
        from(u),to(v),cap(c),flow(f),cost(w) {}
};

struct MCMF
{
    int n;
    vector<Edge> edges;
    vector<int> G[maxn];
    int inq[maxn];
    int d[maxn];
    int p[maxn];
    int a[maxn];

    void init(int n)
    {
        this-> n = n;
        for(int i = 0;i <= n;++i) G[i].clear();
        edges.clear();
    }

    void addEdge(int from,int to,int cap,int cost)
    {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        int m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BellmanFord(int s,int t,int& flow,int& cost)
    {
        memset(d,INF,sizeof(d));
        memset(inq,0,sizeof(inq));
        d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;

        queue<int> Q;
        Q.push(s);
        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();
            inq[u] = 0;
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(e.cap > e.flow && d[e.to] > d[u] + e.cost)
                {
                    d[e.to] = d[u] + e.cost;
                    p[e.to] = G[u][i];
                    a[e.to] = min(a[u],e.cap-e.flow);
                    if(!inq[e.to])
                    {
                        Q.push(e.to);
                        inq[e.to] = 1;
                    }
                }
            }
        }
        if(d[t] == INF) return false;
        flow += a[t];
        cost += d[t]*a[t];
        int u = t;
        while(u != s)
        {
            edges[p[u]].flow += a[t];
            edges[p[u]^1].flow -= a[t];
            u = edges[p[u]].from;
        }
        return true;
    }

    int getRes(int s,int t)
    {
        int flow = 0,cost = 0;
        while(BellmanFord(s,t,flow,cost));
        return cost;
    }
};


///////////////////////////////////////////////
//费用流消圈  ，但是解允许孤立环的存在


struct Edge
{
    int from,to,cap,flow,cost;
    Edge(int u,int v,int c,int f,int w):from(u),to(v),
        cap(c),flow(f),cost(w) {}
};


struct Dinic
{
    int n,s,t;
    vector<int> G[maxn];
    vector<Edge> edges;
    bool vis[maxn];
    int d[maxn];
    int cnt[maxn];
    bool inq[maxn];
    int p[maxn];
    int cur[maxn];


    void init(int n)
    {
        this->n = n;
        for(int i = 0;i <= n;++i) G[i].clear();
        edges.clear();
    }

    void addEdge(int from,int to,int cap,int cost)
    {
        edges.push_back(Edge(from,to,cap,0,cost));
        edges.push_back(Edge(to,from,0,0,-cost));
        int m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }

    bool BFS()
    {
        memset(vis,0,sizeof(vis));
        queue<int> Q;
        Q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[u] + 1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }

    int DFS(int x,int a)
    {
        if(x == t || a == 0) return a;
        int flow = 0,f;
        for(int& i = cur[x];i < G[x].size();++i)
        {
            Edge&e = edges[G[x][i]];
            if(d[x] +1 == d[e.to] &&
                (f = DFS(e.to,min(a,e.cap-e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i]^1].flow -= f;
                flow += f;
                a -= f;
                if(a == 0) break;
            }
        }
       // printf("**** %d\n",flow);
        return flow;
    }

    int getRes(int s,int t)
    {
        this-> s = s; this->t = t;
        int flow = 0;
        while(BFS())
        {
            memset(cur,0,sizeof(cur));
            flow += DFS(s,INF);
        }
        return flow;
    }


    void clearCicle()
    {
        int x;
        while((x = findCicle()) != -1)
        {
            puts("OK");
            int now = x;
            int a = INF;
            do
            {
                printf("***** %d\n",now);
                Edge& e = edges[p[now]];
                now = e.from;
                a = min(a,e.cap-e.flow);

            }while(now != x);
            if(a > 0)
            {
                now = x;
                do
                {
                    Edge& e = edges[p[now]];
                    now = e.from;
                    e.flow += a;
                    edges[p[now]^1].flow -= a;

                }while(now != x);
            }


        }
    }

    int findCicle()
    {
        for(int i = 0;i <= n;++i)
        {
            int t = bellman_ford(i);
            if(t != -1) return t;
        }
        return -1;
    }

    int bellman_ford(int s)
    {
        queue<int> Q;
        memset(inq,0,sizeof(inq));
        memset(cnt,0,sizeof(cnt));
        memset(d,INF,sizeof(d));
        d[s] = 0;
        inq[s] = true;
        Q.push(s);

        while(!Q.empty())
        {
            int u = Q.front(); Q.pop();
            inq[u] = false;
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(e.flow < e.cap)
                {
                    if(d[e.to] > d[u] + e.cost)
                    {
                        d[e.to] = d[u] + e.cost;
                        p[e.to] = G[u][i];
                        if(!inq[e.to])
                        {
                            Q.push(e.to);
                            inq[e.to] = true;
                            cnt[e.to]++;
                            if(cnt[e.to] > n)
                                return u;
                        }
                    }
                }
            }
        }
        return -1;
    }


    vector<int> solve(int s,int t)
    {
        vector<int> V;
        V.push_back(s);
        int u = s;
        while(u != t)
        {
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(e.flow > 0)
                {
                    u = e.to;
                    V.push_back(u);
                    break;
                }
            }
        }
        return V;
    }


};

