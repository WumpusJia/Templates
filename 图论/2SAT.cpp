struct TwoSAT
{
    int n;
    vector<int> G[maxn*2];
    bool mark[maxn*2];
    int S[maxn*2];
    int c;

    void init(int n)
    {
        this->n = n;
        for(int i = 0;i < n*2;++i) G[i].clear();
        memset(mark,0,sizeof(mark));
    }

    void addEdge(int x,int xval,int y,int yval)
    {
        x = x*2+xval;
        y = y*2+yval;
        G[x].push_back(y^1);
        G[y].push_back(x^1);
    }

    bool dfs(int x)
    {
        if(mark[x^1]) return false;
        if(mark[x]) return true;
        mark[x] = true;
        S[c++]= x;
        for(int i = 0;i < G[x].size();++i)
            if(!dfs(G[x][i])) return false;
        return true;
    }

    bool getRes()
    {
        for(int i = 0;i < n*2;i += 2)
            if(!mark[i] && !mark[i+1])
            {
                c = 0;
                if(!dfs(i))
                {
                    while(c > 0) mark[S[--c]] = false;
                    if(!dfs(i+1)) return false;
                }
            }
        return true;
    }
};
