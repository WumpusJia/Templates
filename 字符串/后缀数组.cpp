int s[maxn];
int sa[maxn],t[maxn],t2[maxn],c[maxn];
 //sa[i]是排序后第i个在原字符串中开始的下标
int srank[maxn],height[maxn];
//srank[i]是原字符串下标i所对应的排序后的名次
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
            x[sa[i]] = y[sa[i-1]] == y[sa[i]]
                && y[sa[i-1]+k] == y[sa[i]+k] ? p-1:p++;
        if(p >= n) break;
        m = p;
    }
}

int d[maxn][17];

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

    for(int i = 0;i < n;++i)
        d[i][0] = height[i];
    for(int j = 1;(1 << j) <= n;++j)
        for(int i = 0;i+(1<<j)-1 < n;++i)
            d[i][j] = min(d[i][j-1],d[i+(1<<(j-1))][j-1]);

}

int query(int L,int R)
{
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    return min(d[L][k],d[R-(1<<k)+1][k]);
}

int LCP(int a,int b)
{
    int L = srank[a],R = srank[b];
    if(L > R)
        swap(L,R);
    L++;
    return query(L,R);

}

        scanf("%s",buf);
        n = strlen(save);
     //   memset(height,0,sizeof(height));
     //原始字符数组（最后一个字符应必须是0，而前面的字符必须非0）
        for(int i = 0;i < n;++i) s[i] = save[i]-'a'+1;
        s[n++] = 0;
        build_sa(27);
        getHeight();
