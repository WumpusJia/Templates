#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000+10;
int G[maxn][maxn];
int Prev[maxn],Next[maxn];
int n;


/*
1包含个顶点的图, 如果任意两个顶点的度数之和都不小于n-1（即大于等于n-1）,
则存在哈密尔顿通路。
2包含个顶点的图, 如果任意两个顶点的度数之和都不小于n（即大于等于n）,
则存在哈密尔顿回路。
*/

int main()
{
 //   freopen("./test.txt","r",stdin);
    scanf("%d",&n);
    for(int i = 0;i < n;++i)
    {
        int t;
        while(1)
        {
            scanf("%d",&t);
            G[i][t-1] = 1;
            char ch = getchar();
            if(ch == '\n' || ch == EOF) break;
        }
    }

    for(int i = 0;i < n;++i) Next[i] = (i+1)%n;
    for(int i = 0;i < n;++i) Prev[i] = (i-1+n)%n;

    bool inok = true;
    while(inok)
    {
        inok = false;
        int x = 0;
        while(1)
        {
            if(G[x][Next[x]] == 0)
            {
                inok = true;
                int y = 0;
                while(1)
                {
                    int u = x,v = Next[x];
                    int p = y,q = Next[y];
                    if(v != p && u != p && u != q)
                    {
                        if(G[u][p] && G[v][q])
                        {
                            Next[u] = Prev[u],Prev[u] = p;
                            Next[v] = Next[v],Prev[v] = q;
                            Prev[p] = Prev[p],Next[p] = u;
                            Prev[q] = Next[q],Next[q] = v;
                            for(int z = Next[u];z != q;z = Next[z])
                                swap(Next[z],Prev[z]);
                            break;
                        }
                    }
                    y = Next[y];
                    if(y == 0) break;
                }
                break;
            }
            x = Next[x];
            if(x == 0) break;
        }
    }

    int x = 0;
    while(1)
    {
        printf("%d ",x+1);
        x = Next[x];
        if(x == 0) break;
    }
    puts("1");

    return 0;
}
