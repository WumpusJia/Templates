//KMP
void getFail(char *P,int f[]) //失配函数: 如果P[j] 能匹配到P[i],那么f[j] = i+1
{
    int m = strlen(P);
    f[0] = 0,f[1] = 0;
    for(int i = 1;i < m;++i)
    {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i+1] = P[i] == P[j] ?j+1:0;
    }
}

void find(char* T,char *P,int f[])
{
    int n = strlen(T),m = strlen(P);
    getFail(P,f);
    int j = 0;
    for(int i = 0;i < n;++i)
    {
        while(j && P[j] != T[i]) j = F[j];
        if(P[j] == T[i]) j++;
        if(j == m) printf("%d\n",i-m+1);
    }
}


//Trie
const int maxnode = 4000*100+10;
const int sigma_size = 26;

struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;
    void clear() { sz = 1;memset(ch[0],0,sizeof(ch[0])); }
    int idx(char c) { return c - 'a'; }

    void insert(const char *s,int v)
    {
        int u = 0,n = strlen(s);
        for(int i = 0;i < n;++i)
        {
            int c = idx(s[i]);
            if(!ch[u][c])
            {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void find_prefixes(const char* s,int len,vector<int>& ans)
    {
        int u = 0;
        for(int i = 0;i < len;++i)
        {
            if(s[i] == 0) break;
            int c = idx(s[i]);
            if(!ch[u][c]) break;
            u = ch[u][c];
            if(val[u] != 0)  ans.push_back(val[u]);
        }
    }
};


//后缀数组
int s[maxn];
int sa[maxn],t[maxn],t2[maxn],c[maxn]; //sa[i]是排序后第i个在原字符串中开始的下标
int srank[maxn],height[maxn]; //srank[i]是原字符串下标i所对应的排序后的名次
int n;
int ans;

void build_sa(int m)
{
    int *x = t,*y = t2;
    for(int i = 0;i < m;++i) c[i] = 0;
    for(int i = 0;i < n;++i) c[x[i] = s[i]]++;
    for(int i = 0;i < m;++i) c[i] += c[i-1];
    for(int i = n-1;i >= 0;--i) sa[--c[x[i]]] = i;
    for(int k = 1;k <= n;k <<= 1)
    {
        int p = 0;
        for(int i = n-k;i < n;++i) y[p++] = i;
        for(int i = 0;i < n;++i) if(sa[i] >= k) y[p++] = sa[i]-k;
        for(int i = 0;i < m;++i) c[i] = 0;
        for(int i = 0;i < n;++i) c[x[y[i]]]++;
        for(int i = 0;i < m;++i) c[i] += c[i-1];
        for(int i = n-1;i >= 0;--i) sa[--c[x[y[i]]]] = y[i];

        swap(x,y);
        p = 1,x[sa[0]] = 0;
        for(int i = 1;i < n;++i)
            x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
        if(p >= n) break;
        m = p;
    }
}

void getHeight()
{
    int k = 0;
    for(int i = 0;i < n;++i) srank[sa[i]] = i;
    height[srank[0]] = 0;
    for(int i = 0;i < n;++i)
    {
        if(k) k--;
        int j = sa[srank[i]-1];
        while(s[i+k] == s[j+k]) k++;
        height[srank[i]] = k;
    }
}
        scanf("%s",buf);
        n = strlen(save);
     //   memset(height,0,sizeof(height));
        for(int i = 0;i < n;++i) s[i] = save[i]-'a'+1; //原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
        s[n++] = 0;
        build_sa(27);
        getHeight();



//Hash
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int BASE1 = 313;
const int BASE2 = 31;
const LL MOD = 1000*1000*1000+7;

const int N = 600000+100;

LL pw1[N];
LL pw2[N];

set<pair<LL,LL>> was[N];

LL geth1(char* s)
{
    ULL hs = 0;  //此处高能，防止溢出
    while(*s)
        hs = (hs * BASE1 + *s++ - 'a' + 1)%MOD;
    return (LL)hs;
}

LL geth2(char* s)
{
    ULL hs = 0;
    while(*s)
        hs = (hs * BASE2 + *s++ - 'a' + 1)%MOD;
    return (LL)hs;
}

int main()
{
  //  freopen("./test.txt","r",stdin);
    pw1[0] = pw2[0] = 1;
    for(int i = 1;i < N;++i)
    {
        pw1[i] = pw1[i-1]*BASE1 % MOD;
        pw2[i] = pw2[i-1]*BASE2 % MOD;
    }
    int n,m;
    scanf("%d %d",&n,&m);
    char s[N];
    for(int i = 0;i < n;++i)
    {
        scanf("%s",s);
        was[strlen(s)].insert(make_pair(geth1(s),geth2(s)));
    }
    for(int i = 0;i < m;++i)
    {
        scanf("%s",s);
        int len = strlen(s);
        LL h1 = geth1(s);
        LL h2 = geth2(s);
        bool ok = false;
        for(int j = 0;j < len && !ok;++j)
            for(int c = 'a';c <= 'c' && !ok;++c)
            {
                if(c == s[j]) continue;
                LL nh1 = ((h1 + pw1[len - 1 - j] * (c - s[j])) % MOD + MOD) % MOD; //替换s[j]后的hash
                LL nh2 = ((h2 + pw2[len - 1 - j] * (c - s[j])) % MOD + MOD) % MOD;
                if(was[len].find(make_pair(nh1,nh2)) != was[len].end())
                    ok = true;
            }
        if(ok)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

