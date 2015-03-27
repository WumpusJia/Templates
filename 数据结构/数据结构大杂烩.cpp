//树状数组
void add(int x,int v)
{
    for(int i = x;i < maxm;i += lowbit(i))
        sum[i] += v;
}

int query(int x)
{
    int res = 0;
    for(int i = x;i > 0;i -= lowbit(i))
        res += sum[i];
    return res;
}

/*使用时先给a１－aｎ调用add,查询用sum*/


//RMQ
//一维 0-----n-1
void RMQ_init(const vector<int>& A)
{
    int n = A.size();
    for(int i = 0;i < n;++i)
        d[i][0] = A[i];
    for(int j = 1;(1 << j) <= n;++j)
        for(int i = 0;i+(1<<j)-1 < n;++i)
            d[i][j] = max(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}

int query(int L,int R)
{
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    return max(d[L][k],d[R-(1<<k)+1][k]);
}

//二维 1---n
void RMQ_init()
{
    for(int r = 1;r <= R;++r)
        for(int c = 1;c <= C;++c)
            d[r][c][0][0] = A[r][c];

    for(int i = 0;i <= power[R];++i)
        for(int j = 0;j <= power[C];++j)
        {
            if(i == 0 && j == 0) continue;
            int limitR = R+1-(1<<i);
            int limitC = C+1-(1<<j);
            for(int r = 1;r <= limitR;++r)
                for(int c = 1;c <= limitC;++c)
                {
                    if(i == 0)
                        d[r][c][i][j] = max(d[r][c][i][j-1],d[r][c+(1<<(j-1))][i][j-1]);
                    else
                        d[r][c][i][j] = max(d[r][c][i-1][j],d[r+(1<<(i-1))][c][i-1][j]);
                }
        }
}


int query(int r1,int c1,int r2,int c2)
{
    int res = -1;
    int k1 = power[r2-r1+1],k2 = power[c2-c1+1];
    res = max(res,d[r1][c1][k1][k2]);
    res = max(res,d[r1][c2-(1<<k2)+1][k1][k2]);
    res = max(res,d[r2-(1<<k1)+1][c1][k1][k2]);
    res = max(res,d[r2-(1<<k1)+1][c2-(1<<k2)+1][k1][k2]);
    return res;
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



//线段树
//单点修改
const int maxn = 50000+10;
int sum[maxn<<2];

void pushup(int u)
{
    sum[u] = sum[u << 1] + sum[u << 1 | 1];
}

void build(int L,int R,int u) //自底向上建树
{
    if(L == R)
    {
        scanf("%d",&sum[u]);
     //   puts("OK");
        return;
    }
    int m = (L + R) >> 1;
    build(L,m,u << 1);
    build(m+1,R,u << 1 | 1);
    pushup(u);
}

void update(int p,int v,int L,int R,int u)
{
    if(L == R)
    {
        sum[u] += v;
        return;
    }
    int m = (L+R) >> 1;
    if(p <= m) update(p,v,L,m,u << 1);
    else update(p,v,m+1,R,u << 1 | 1);
    pushup(u);
}

int query(int qL,int qR,int L,int R,int u)
{
    if(qL <= L && R <= qR) return sum[u];
    int m = (L+R) >> 1;
    int res = 0;
    if(qL <= m) res += query(qL,qR,L,m,u << 1);
    if(qR > m) res += query(qL,qR,m+1,R,u << 1 | 1);
    return res;
}

