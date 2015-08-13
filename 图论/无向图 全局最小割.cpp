#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500+10;
const int INF = 0x3f3f3f3f;
bool combine[maxn];
bool vis[maxn];
int G[maxn][maxn];
int d[maxn];
int n,m;

///////////////割去最少的边使得图变成2个连通块/////////////

int StoerWagner()
{
    memset(combine,0,sizeof(combine));
    int res = INF;
    for(int i = 0;i < n-1;++i)
    {
        int MinCut = INF;
    //////////求最大生成树////////////
        memset(vis,0,sizeof(vis));
        memset(d,0,sizeof(d));
        int S = -1,T = -1;
        for(int i = 0;i < n;++i)
        {
            int Max = -INF,v;
            for(int j = 0;j < n;++j)
                if(!combine[j] && !vis[j] && d[j] > Max)
                {
                    Max = d[j];
                    v = j;
                }
            if(T == v) break;
            S = T,T = v;
            MinCut = Max;
            vis[v] = 1;
            for(int j = 0;j < n;++j)
                if(!combine[j] && !vis[j])
                    d[j] += G[v][j];
        }
        res = min(res,MinCut);
        if(res == 0) return 0;
        combine[T] = 1;
        for(int j = 0;j < n;++j)
            if(!combine[j])
            {
                G[S][j] += G[T][j];
                G[j][S] += G[j][T];
            }
    }
    return res;
}




int main()
{
 //   freopen("./test.txt","r",stdin);

    while(scanf("%d %d",&n,&m) == 2)
    {
        memset(G,0,sizeof(G));
        for(int i = 0;i < m;++i)
        {
            int a,b,w;
            scanf("%d %d %d",&a,&b,&w);
            G[a][b] += w;
            G[b][a] += w;
        }
        printf("%d\n",StoerWagner());
    }
    return 0;
}
