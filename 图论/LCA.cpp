/************离线*****************/
#include<cstdio>
#include<vector>
#include<cstring>
using namespace std;

const int maxn = 10000;

vector<int> G[maxn],que[maxn];
int n;
int fa[maxn],num[maxn],ans[maxn],indegree[maxn];
int vis[maxn];
void init()
{
    for(int i = 1;i <= n;++i)
    {
        G[i].clear();
        que[i].clear();
        num[i] = 1;
        fa[i] = i;
    }
    memset(vis,0,sizeof(vis));
    memset(indegree,0,sizeof(indegree));
    memset(ans,0,sizeof(ans));

}

int findfa(int x)
{
    return fa[x] == x?x: fa[x] = findfa(fa[x]);
}

void add(int x,int y)
{
    int a = findfa(x);
    int b = findfa(y);
    if(a != b)
    {
        fa[b] = a;
//        if(num[a] <= num[b])
//        {
//            fa[a] = b;
//            num[b] += num[a];
//        }
//        else
//        {
//            fa[b] = a;
//            num[a] += num[b];
//        }
    }
}

void LCA(int u)
{
    ans[u] = u;
    for(int i = 0; i < G[u].size();++i)
    {
        LCA(G[u][i]);
        add(u,G[u][i]);
        ans[findfa(G[u][i])] = u;
    }
    vis[u] = 1;
    for(int i = 0;i < que[u].size();++i)
        if(vis[que[u][i]])
        {
            printf("%d\n",ans[findfa(que[u][i])]);
            return;
        }
}

int main()
{
//    freopen("./test.txt","r",stdin);
    int kase;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d",&n);
        init();
        int a,b;
        for(int i = 0;i < n-1;++i)
        {
            scanf("%d %d",&a,&b);
            if(a != b)
            {
                G[a].push_back(b);
                indegree[b]++;
            }
        }
        scanf("%d %d",&a,&b);
        que[a].push_back(b);
        que[b].push_back(a);
        int u;
        for(u = 1;u <= n;++u)
            if(indegree[u] == 0)
                break;
        LCA(u);
    }
    return 0;
}

/**********************在线**************/
int deep[maxn];
int p[maxn][M];



void dfs(int u,int fa,int d)  //注意root的deeo必须为1
{
    p[u][0] = fa;
    deep[u] = d;

    for(int i = 1;i < M;++i)
       p[u][i] = p[p[u][i-1]][i-1];

    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != fa)
        {
            dfs(v,u,d+1);
        }
    }
}

int LCA(int a,int b)
{
    if(deep[a] < deep[b]) swap(a,b);
    for(int i = M-1;i >= 0;--i)
    {
        if(deep[p[a][i]] >= deep[b])
            a = p[a][i];
        if(a == b)
            return a;
    }
    for(int i = M-1;i >= 0;--i)
        if(p[a][i] != p[b][i])
        {
            a = p[a][i];
            b = p[b][i];
        }
    return p[a][0];
}
