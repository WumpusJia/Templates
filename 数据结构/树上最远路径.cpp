#include<stdio.h>
#include<string.h>
#include<iostream>
#include<queue>
#include<vector>
using namespace std;

const int maxn=10000 + 10;
int n;
bool vis[maxn];
vector<int> G[maxn];
vector<int> dis[maxn];

void init()
{
    for(int i = 1;i <= n;++i) G[i].clear();
    for(int i = 1;i <= n;++i) dis[i].clear();
}

int bfs(int d[],int k)
{
    memset(vis,0,sizeof(vis));
    queue<int> q;
    int res = k,mx = 0;
    q.push(k);
    d[k] = 0;
    vis[k] = 1;
    while(!q.empty())
    {
        int u = q.front();q.pop();
        for(int i = 0;i < G[u].size();++i)
        {
            int v = G[u][i];
            if(vis[v]) continue;
            vis[v] = 1;
            d[v] = d[u]+dis[u][i];
            q.push(v);
            if (d[v]>mx)
            {
                mx = d[v];
                res = v;
            }
        }
    }
    return res;
}

int main()
{
    int v,w;
    while(scanf("%d",&n) == 1)
    {
        init();
        for(int u = 2;u<=n;++u) //2~n的结点，u,v,w,　u-v连通，权值为w
        {
            scanf("%d %d",&v,&w);
            G[u].push_back(v);
            G[v].push_back(u);
            dis[u].push_back(w);
            dis[v].push_back(w);
        }
        int ans1[maxn],ans2[maxn];
        int u = bfs(ans1,1);
        int v = bfs(ans1,u);
        bfs(ans2,v);
        for(int i = 1;i <= n;++i) printf("%d\n",max(ans1[i],ans2[i]));
    }
    return 0;
}

