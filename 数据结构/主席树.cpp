#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000+100;

struct Node
{
    int ch[2];
    int sum;
}tree[maxn*25];

int sz;
int root[maxn];

void init()
{
    sz = 0;
}

int build(int L,int R)
{
    int u = sz++;
    tree[u].sum = 0;
    if(L == R)  return u;
    else
    {
        int m = (L+R)/2;
        if(L <= m) tree[u].ch[0] = build(L,m);
        if(R > m) tree[u].ch[1] = build(m+1,R);
        return u;
    }
}

int insert(int L,int R,int x,int v)
{
    int u = sz++;
    tree[u] = tree[x];
    tree[u].sum++;
    if(L == R) return u;
    else
    {
        int m = (L+R)/2;
        if(v <= m) tree[u].ch[0] = insert(L,m,tree[u].ch[0],v);
        else tree[u].ch[1] = insert(m+1,R,tree[u].ch[1],v);
        return u;
    }
}

int query(int a,int b,int L,int R,int val)
{
    if(R <= val) return tree[b].sum - tree[a].sum;
    if(L > val) return 0;
    int m = (L+R)/2;
    return query(tree[a].ch[0],tree[b].ch[0],L,m,val)
        + query(tree[a].ch[1],tree[b].ch[1],m+1,R,val);
}



int n,m;

int num[maxn];

int save[maxn*2];
int pn;


int que[maxn][3];

void solve()
{
    init();
    root[0] = build(1,pn);
    for(int i = 1;i <= n;++i)
    {
        root[i] = insert(1,pn,root[i-1],num[i]);
    }

    for(int i = 1;i <= m;++i)
    {
        int L = root[que[i][0]-1];
        int R = root[que[i][1]];
        int res = query(L,R,1,pn,que[i][2]);
        printf("%d\n",res);
    }


}



