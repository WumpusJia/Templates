#include<bits/stdc++.h>
using namespace std;

#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define Fd(i,a,b) for(int i=(a);i>=(b);--i)

const int maxn=7+3;
int n,cur,G[maxn][maxn],degree[maxn];

void init()
{
    memset(degree,0,sizeof(degree));
    memset(G,0,sizeof(G));
}

struct edge{
    int a,b;
}e[110],ans[110];

void dfs(int u){
    F(i,0,6)
        if(G[u][i]){
            G[u][i]--,G[i][u]--;
            dfs(i);
            cur++;
            ans[cur].a=u,ans[cur].b=i;
        }
}

void solve()
{
    int cnt=0,u=-1;
    F(i,0,6){
        //cerr<<i<<" "<<degree[i]<<endl;
        if(degree[i] & 1){
            cnt++;
            u=i;
        }
        else if(degree[i] && u==-1) u=i;
    }
    if(cnt>2){
        printf("No solution\n");
        return;
    }
    cur=0;
    //cerr<<u<<endl;
    dfs(u);
    //cerr<<cur<<endl;
    if(cur<n){
        printf("No solution\n");
        return;
    }
    bool vis[110];
    memset(vis,0,sizeof(vis));
    Fd(i,n,1)
        F(j,1,n)
        if(!vis[j] && ans[i].a==e[j].a && ans[i].b==e[j].b){
            vis[j]=1;
            printf("%d +\n",j);
            break;
        }
        else if(!vis[j] && ans[i].a==e[j].b && ans[i].b==e[j].a){
            vis[j]=1;
            printf("%d -\n",j);
            break;
        }

}

int main()
{
    //freopen("test","r",stdin);
    init();
    cin>>n;
    F(i,1,n){
        int a,b;
        cin>>a>>b;
        e[i].a=a;
        e[i].b=b;
        G[a][b]++;
        G[b][a]++;
        degree[a]++;
        degree[b]++;
    }
    solve();
    return 0;
}
