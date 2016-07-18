#include<bits/stdc++.h>
using namespace std;


const int maxn = 100;
int n,G[maxn][maxn],degree[maxn];

void init()
{
    memset(degree,0,sizeof(degree));
    memset(G,0,sizeof(G));
}

struct Edge
{
    int from,to;
    Edge(int from = 0,int to = 0):from(from),to(to) {}
};

vector<Edge> res;

int back_judge;
void dfs(int u){
    for(int i = 0;i < n;++i)
        if(G[u][i])
        {
            G[u][i]--,G[i][u]--;
            dfs(i);
            back_judge++;
            res.push_back(Edge(u,i));
        }
}

bool solve()
{
    int cnt = 0,u = -1;
    for(int i = 0;i < n;++i)
    {
        if(degree[i] & 1){
            cnt++;
            u=i;
        }
        else if(degree[i] && u==-1) u=i;
    }
    if(cnt>2) //如果是欧拉回路的问题，只需要改成cnt != 0
    {
        printf("No solution\n");
        return false;
    }
    back_judge = 0;
    dfs(u);
    if(back_judge < n)
    {
        printf("No solution\n");
        return false;
    }
    return true;

}

int main()
{
    //freopen("test","r",stdin);

}
