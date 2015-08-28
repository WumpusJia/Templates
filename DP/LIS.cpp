int LIS(int n)
{
    for(int i = 1;i <= n;++i) g[i] = INF;
    a[n] = INF-1;
    for(int i = 0;i <= n;++i)
    {
        int k = lower_bound(g+1,g+n+1,a[i]) - g;    // find in g[1..n],not find k=1; 若非严格递增，find中a[i]改为a[i]+1
        d[i] = k;
        g[k] = a[i];    //entrue a[i]<=g[k]
    }
    return d[n]-1;
}
