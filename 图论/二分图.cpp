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
    for(int i = 1;i <= n;++i)
    {
        memset(vis,0,sizeof(vis));
        if(dfs(i)) ans++;
    }
    return ans;
}


//////////////最佳完美匹配/////////////////
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

/////////nx个要匹配，有ny个可选////////////
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;


const int maxn = 3000+5;
const int INF = 0x3f3f3f3f;


struct KM
{
    int nx,ny;
    int W[100][maxn];
    int Lx[maxn],Ly[maxn];
    bool visx[maxn],visy[maxn];
    int slack[maxn];
    int link[maxn];

    void init(int nx,int ny)
    {
        this->nx = nx,this->ny = ny;
        memset(W,0,sizeof(W));
    }

    void addEdge(int u,int v,int w)
    {
        W[u][v] += w;
    }

    bool match(int x)
    {
        visx[x] = 1;
        for(int y = 0;y < ny;++y)
        {
            if(visy[y]) continue;
            int t = Lx[x] + Ly[y] - W[x][y];
            if(t == 0)
            {
                visy[y] = 1;
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
        for(int i = 0;i < ny;++i)
            if(!visy[i] && a > slack[i])
                a = slack[i];
        for(int i = 0;i < nx;++i)
            if(visx[i])
                Lx[i] -= a;
        for(int i = 0;i < ny;++i)
            if(visy[i])
                Ly[i] += a;
            else
                slack[i] -= a;

    }


    int getRes()
    {
        memset(link,-1,sizeof(link));
        memset(Ly,0,sizeof(Ly));
        for(int i = 0;i < nx;++i)
        {
            Lx[i] = -INF;
            for(int j = 0;j < ny;++j)
                Lx[i] = max(Lx[i],W[i][j]);
        }

        for(int i = 0;i < nx;++i)
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
        for(int i = 0;i < ny;++i)
            if(link[i] != -1)
                res += W[link[i]][i];
        return res;
    }
};

//左边n个点,右边m个点的联通的二分图计数
 memset(dp,0,sizeof(dp));
dp[1][0] = 1;

for(int i = 1;i <= n;++i)
    for(int j = 1;j <= m;++j)
    {
        LL sum = fac[i*j];//*W[i*j];

        for(int a = 1;a <= i;++a)
            for(int b = 0;b <= j;++b)
            {
                if(a == i && b == j) continue;

                LL cnt = (dp[a][b]*C[i-1][a-1]%mod)*C[j][b]%mod;
                LL t = cnt*fac[(i-a)*(j-b)]%mod;
                sum = (sum-t+mod)%mod;
            }
        dp[i][j] = sum;

    }
