
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
                LL nh1 = ((h1 + pw1[len - 1 - j] *
                    (c - s[j])) % MOD + MOD) % MOD; //替换s[j]后的hash
                LL nh2 = ((h2 + pw2[len - 1 - j] *
                    (c - s[j])) % MOD + MOD) % MOD;
                if(was[len].find(make_pair(nh1,nh2))
                    != was[len].end())
                    ok = true;
            }
        if(ok)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}




//Hash容错表
void init()
{
    memset(head,-1,sizeof(head));
}

int modhash(int x)
{
    int sum = 0;
    for(int i = 0;i < 6;++i)
        sum += save[x][i];
    return sum%hashsize;
}

bool insert(int x)
{
    int h = modhash(x);
    int u = head[h];
    while(u != -1)
    {
        if(judge(u,x)) return false;
        u = nxt[u];
    }
    nxt[x] = head[h];
    head[h] = x;
    return true;
}

