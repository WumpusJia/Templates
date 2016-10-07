#include<bits/stdc++.h>
using namespace std;


const int maxn = 1e4+1000;
const int INF = 0x3f3f3f3f;
int n,k;
vector<int> G[maxn];

bool vis[maxn];


int sz[maxn];
int Maxchildsz[maxn];

void getsize(int u,int fa)
{
    sz[u] = 1;
    Maxchildsz[u] = 0;
    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != fa && !vis[v])
        {
            getsize(v,u);
            sz[u] += sz[v];
            Maxchildsz[u] = max(Maxchildsz[u],sz[v]);
        }
    }

}

int root;
int Minmax;
void getroot(int u,int fa,int tot)
{
    Maxchildsz[u] = max(Maxchildsz[u],tot-sz[u]);
    if(Maxchildsz[u] < Minmax)
    {
        Minmax = Maxchildsz[u];
        root = u;
    }
    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != fa && !vis[v])
            getroot(v,u,tot);
    }
}

////////////////////////////
//int cur;
//int dist[maxn];
//
//void getdist(int u,int fa,int sum)
//{
//    dist[cur++] = sum;
//    for(int i = 0;i < G[u].size();++i)
//    {
//        int v = G[u][i];
//        if(v != fa && !vis[v])
//            getdist(v,u,sum+W[u][i]);
//    }
//}

int res;
void dfs(int u)
{
    getsize(u,-1);
    Minmax = INF;
    getroot(u,-1,sz[u]);
    vis[root] = 1;
    int nowroot = root; //注意!!root是全局变量，需要保存


    ////////////////////////////////////////////////
    //cal
    /*
    满足 Dept h ( i )  Dept h ( j )  K
     且 Belong ( i )  Belong ( j ) 的 ( i , j ) 个
数
= 满足 Depth ( i )  Depth ( j )  K 的 ( i , j ) 个数
–
满足 Depth ( i )  Depth ( j )  K 且
    Belong ( i )  Belong ( j ) 的 ( i , j ) 个数

    */

    for(int i = 0;i < G[nowroot].size();++i)
    {
        int v = G[nowroot][i];
        if(!vis[v])
        {
            //cal
            dfs(v);
        }
    }
}



void solve()
{
    memset(vis,0,sizeof(vis));
    res = 0;
    dfs(1);
}



