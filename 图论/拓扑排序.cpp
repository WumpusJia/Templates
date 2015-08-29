#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 1000;

bool G[maxn][maxn];
int indegree[maxn];
int n,m;
vector<int> res;

bool toposort()
{
    res.clear();
    bool unfinish = true;;
    while(unfinish)
    {
        unfinish = false;
        for(int i = 1;i <= n;++i)
            if(indegree[i] == 0)
            {
                unfinish = true;
                indegree[i]--;
                res.push_back(i);
                for(int j = 1;j <= n;++j)
                    if(i != j && G[i][j])
                        indegree[j]--;
                break;
            }
    }
    return res.size() == n;
}



int main()
{
  //  freopen("./test.txt","r",stdin);
    while(scanf("%d%d",&n,&m) == 2)
    {
        memset(G,0,sizeof(G));
        memset(indegree,0,sizeof(indegree));
        for(int i = 0;i < m;++i)
        {
            int a,b;
            scanf("%d%d",&a,&b);
            if(!G[a][b])
            {
                G[a][b] = 1;
                indegree[b]++;
            }
        }
        if(!toposort())
        {
            puts("NO");
            break;
        }
        for(int i = 0;i < n;++i)
            printf("%d%c",res[i],(i == n-1)?'\n':' ');
    }
    return 0;
}
