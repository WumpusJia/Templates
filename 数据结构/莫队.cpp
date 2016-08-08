#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int maxn = 10000+10;

int n,m;
int ppos[maxn];

struct Node
{
    int L,R,id;
    Node(int L = 0,int R = 0,int id = 0):L(L),R(R),id(id) {}
    bool operator < (const Node& rhs) const {
        return ppos[L] < ppos[rhs.L] ||
            (ppos[L] == ppos[rhs.L] && R < rhs.R);
    }
};



int main()
{
   // freopen("./test.txt","r",stdin);
    int kase;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d",&n);
        int BLOCK = (int)sqrt(n+0.5);
        for(int i = 1;i <= n;++i)
        {
            ppos[i] = i/BLOCK;
        }

        scanf("%d",&m);
        for(int i = 0;i < m;++i)
        {
            scanf("%d %d",&p[i].L,&p[i].R);
            p[i].id = i;
        }
        sort(p,p+m);
        sum = 0;
        L = 1,R = 0;
        for(int i = 0;i < m;++i)
        {
            if(R < p[i].R)
            {
                for(R = R+1;R <= p[i].R;++R)
                    add(R,1);
                R--;
            }
            if(R > p[i].R)
            {
                for(;R > p[i].R;--R)
                    add(R,-1);
            }
            if(L > p[i].L)
            {
                for(L = L-1;L >= p[i].L;--L)
                    add(L,1);
                L++;
            }
            if(L < p[i].L)
            {
                for(;L < p[i].L;++L)
                    add(L,-1);
            }
            res[p[i].id] = sum;
        }
        for(int i = 0;i < m;++i)
            printf("%lld\n",res[i]);
    }
    return 0;
}


//////////////////////////////////////////
//如果是莫队查询子树，只需要dfs，转化成普通莫队
//树上莫队(链的形式)

int b_cnt;
int BLOCK;

int seqlink[maxn];
int szlink;
int fa[maxn];
int dep[maxn];

bool In[maxn];
int cross;

int dfs(int u,int f,int d)
{
    dep[u] = d;
    fa[u] = f;
    int sz = 0;
    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != f)
        {
            sz += dfs(v,u,d+1);
            if(sz > BLOCK)
            {
                while(sz--) ppos[seqlink[--szlink]] = b_cnt;
                b_cnt++;
            }
        }
    }
    seqlink[szlink++] = u;
    return sz+1;
}



inline void inv(int x)
{
    if(In[x])
    {
        In[x] = false;
        add(x,-1);
    }
    else
    {
        In[x] = true;
        add(x,1);
    }
}

inline void move_up(int& x)
{
    if(!cross)
    {
        if(In[x] && !In[fa[x]]) cross = x;
        else if(In[fa[x]] && !In[x]) cross = fa[x];
    }
    inv(x), x = fa[x];
}

void move(int a,int b)
{
    if(a == b) return;
    cross = 0;
    if(In[b]) cross = b;
    while(dep[a] > dep[b]) move_up(a);
    while(dep[b] > dep[a]) move_up(b);
    while(a != b) move_up(a),move_up(b);
    inv(a),inv(cross);
}

void solve() //注意树的下标是1开始
{
    memset(In,0,sizeof(In));

    int BLOCK = (int)sqrt(m+0.5);
    b_cnt = 0;
    szlink = 0;
    dfs(1,0,1);


    sort(q,q+m);
    int L = 1,R = 1;
    add(1,1);
    In[1] = true;
    for(int i = 0;i < lsz;++i)
    {
        move(L,q[i].L);
        move(R,q[i].R);

        L = q[i].L;
        R = q[i].R;

        res[q[i].id] = cal()...;
    }

}

