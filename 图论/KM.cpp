#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;


const int maxn = 500+5;
const int INF = 0x3f3f3f3f;


struct KM
{
    int n;
    vector<int> G[maxn];
    int W[maxn][maxn];
    int Lx[maxn],Ly[maxn];
    bool visx[maxn],visy[maxn];
    int link[maxn];
    int slack[maxn];

    void init(int n)
    {
        this->n = n;
        for(int i = 0;i < n;++i) G[i].clear();
        memset(W,0,sizeof(W));
    }

    void addEdge(int u,int v,int w)
    {
        G[u].push_back(v);
        W[u][v] = w;
    }

    bool match(int x)
    {
        visx[x] = true;
        for(int i = 0;i < G[x].size();++i)
        {
            int y = G[x][i];
            if(visy[y]) continue;
            int t = Lx[x] + Ly[y] - W[x][y];
            if(t == 0)
            {
                visy[y] = true;
                if(link[y] == -1 || match(link[y]))
                {
                    link[y] = x;
                    return true;
                }
            }
            else if(slack[y] > t)
                slack[y] = t;
        }
        return false;
    }

    void update()
    {
        int a = INF;
        for(int i = 0;i < n;++i)
            if(!visy[i] && a > slack[i])
                a = slack[i];

        for(int i = 0;i < n;++i)
        {
            if(visx[i]) Lx[i] -= a;
            if(visy[i]) Ly[i] += a;
            else    slack[i] -= a;
        }
    }


    int getRes()
    {
        for(int i = 0;i < n;++i)
        {
            Lx[i] = -INF;
            for(int j = 0;j < G[i].size();++j)
                Lx[i] = max(Lx[i],W[i][G[i][j]]);
            Ly[i] = 0;
            link[i] = -1;
        }
        for(int i = 0;i < n;++i)
        {
            memset(slack,INF,sizeof(slack));
            while(1)
            {
                memset(visx,0,sizeof(visx));
                memset(visy,0,sizeof(visy));
                if(match(i)) break;
                else update();
            }
        }

        int res = 0;
        for(int i = 0;i < n;++i)
            if(link[i] != -1)
                res += W[link[i]][i];
        return res;
    }
};
