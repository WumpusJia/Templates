const int maxn = 1000+100;
typedef long long LL;
const int INF = 0x3f3f3f3f;


struct HeapNode
{
    int u,w;
    HeapNode(int u = 0,int w = 0):u(u),w(w) {}
    bool operator < (const HeapNode& rhs) const {
        return w > rhs.w;
    }
};

struct Edge
{
    int from,to,w;
    Edge(int u = 0,int v = 0,int w = 0):from(u),to(v),w(w) {}
};

struct Dijkstra
{
    vector<Edge> edges;
    vector<int> G[maxn];
    int d[maxn];
    bool done[maxn];


    void init()
    {
        for(int i = 0;i < maxn;++i)
            G[i].clear();
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
        memset(d,INF,sizeof(d));
        memset(done,0,sizeof(done));
        priority_queue<HeapNode> Q;
        Q.push(HeapNode(s,0));
        d[s] = 0;
        while(!Q.empty())
        {
            HeapNode now = Q.top(); Q.pop();

            int u  = now.u;
            if(done[u]) continue;
            done[u] = 1;
            for(int i = 0;i < G[u].size();++i)
            {
                Edge& e = edges[G[u][i]];
                if(d[e.to] > d[u] + e.w)
                {
                    d[e.to] = d[u] + e.w;
                    Q.push(HeapNode(e.to,d[e.to]));
                }
            }
        }
    }
};

Dijkstra D;
