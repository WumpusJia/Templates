//AC自动机
struct ACAutomata
{
    int ch[MAXNODE][SIGMA_SIZE];
    int f[MAXNODE];    // fail函数
    int val[MAXNODE];  // 每个字符串的结尾结点都有一个非0的val
    int last[MAXNODE]; // 输出链表的下一个结点
    int sz;

    void init()
    {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
    }

    // 字符c的编号
    int idx(char c)
    {
        return c-'a';
    }

    // 插入字符串。v必须非0
    void insert(char *s, int v)
    {
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++)
        {
            int c = idx(s[i]);
            if(!ch[u][c])
            {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    // 递归打印以结点j结尾的所有字符串
        void report(int pos, int j)
        {
            if(j)
            {
                process_match(pos, val[j]);
                report(pos, last[j]);
            }
        }

    // 在T中找模板
    int find(char* T)
    {
        int n = strlen(T);
        int j = 0; // 当前结点编号，初始为根结点
        for(int i = 0; i < n; i++)
        {      // 文本串当前指针
              int c = idx(T[i]);
             // while(j && !ch[j][c]) j = f[j]; // 顺着细边走，直到可以匹配
              j = ch[j][c];
              if(val[j]) report(i, j);
              else if(last[j]) report(i, last[j]); // 找到了！
        }
    }

    // 计算fail函数
    void getFail()
    {
        queue<int> q;
        f[0] = 0;
        // 初始化队列
        for(int c = 0; c < SIGMA_SIZE; c++)
        {
            int u = ch[0][c];
            if(u) { f[u] = 0; q.push(u); last[u] = 0; }
        }
        // 按BFS顺序计算fail
        while(!q.empty())
        {
            int r = q.front(); q.pop();
            for(int c = 0; c < SIGMA_SIZE; c++)
            {
                int u = ch[r][c];
//                if(!u) continue;
                if(!u) {ch[r][c] = ch[f[r]][c]; continue; }
                q.push(u);
                int v = f[r];
                while(v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }

};

/* 用主席树优化的AC自动机，适用于字符种类比较多的时候
对失配加速*/
#include<bits/stdc++.h>
using namespace std;

const int maxn = 200000+100;

struct Node
{
    int ch[2];
    int v;
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
    tree[u].v = 0;
    if(L == R)  return u;
    else
    {
        int m = (L+R)/2;
        if(L <= m) tree[u].ch[0] = build(L,m);
        if(R > m) tree[u].ch[1] = build(m+1,R);
        return u;
    }
}

int insert(int L,int R,int x,int c,int v)
{
    int u = sz++;
    tree[u] = tree[x];
    if(L == R)
    {
        tree[u].v = v;
        return u;
    }
    else
    {
        int m = (L+R)/2;
        if(c <= m) tree[u].ch[0]  = insert(L,m,tree[u].ch[0],c,v);
        else tree[u].ch[1] = insert(m+1,R,tree[u].ch[1],c,v);
        return u;
    }
}


int find(int L,int R,int u,int k)
{
    if(L == R)
    {
        return tree[u].v;
    }
    else
    {
        int m = (L+R)/2;
        if(k <= m) return find(L,m,tree[u].ch[0],k);
        else return find(m+1,R,tree[u].ch[1],k);
    }
}




vector<int> G[maxn];
vector<int> ch[maxn];

int n;
int fa[maxn];

int f[maxn];

int update(int r,int u)
{

    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        int c = ch[u][i];
        r = insert(1,n,r,c,v);
    }
    return r;
}


int main()
{
  //  freopen("./test.txt","r",stdin);
    scanf("%d",&n);
    for(int i = 1;i <= n;++i)
    {
        int t;
        scanf("%d",&t);
        fa[i] = t;
        G[t].push_back(i);

    }
    for(int i = 1;i <= n;++i)
    {
        int t;
        scanf("%d",&t);
        ch[fa[i]].push_back(t);
    }

    root[0] = build(1,n);
    root[0] = update(root[0],0);
    f[0] = 0;
    queue<int> Q;

    for(int i = 0;i < G[0].size();++i)
    {
        int v = G[0][i];
        f[v] = 0;
        Q.push(v);
    }

    while(!Q.empty())
    {
        int u = Q.front(); Q.pop();

        root[u] = update(root[f[u]],u);
        for(int i = 0;i < G[u].size();++i)
        {
            int v = G[u][i];
            int c = ch[u][i];
            f[v] = find(1,n,root[f[u]],c);
            Q.push(v);
        }
    }

    for(int i = 1;i <= n;++i)
        printf("%d%c",f[i]," \n"[i == n]);
    return 0;
}







