memset(vis,0,sizeof(vis));
memset(d,INF,sizeof(d));
vis[0] = 1;
for(int i = 0;i < n;++i)
    d[i] = cal(0,i);

int res = 0;
for(int i = 1;i < n;++i)
{
    int Min = INF,v;
    for(int j = 1;j < n;++j)
        if(!vis[j] && d[j] < Min)
            Min = d[j],v = j;
    vis[v] = 1;
    res += Min;
    for(int j = 0;j < n;++j)
    {
        int t = cal(v,j);
        if(!vis[j] && d[j] > t)
            d[j] = t;
    }
}
