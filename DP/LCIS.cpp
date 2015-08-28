int LCIS(int n,int m)
{
    memset(f,0,sizeof(f));
    for(int i = 0;i < n;++i)
    {
        int k = 0,p = -1;
        for(int j = 0;j < m;++j)
        {
            if(a[i] > b[j])
                if(f[j] > k)
                    k = f[p = j];
            if(a[i] == b[j])
                if(f[j] < k+1)
                    f[j] = k+1,prev[j] = p;
        }
    }
    int k = 0,p = -1;
    for(int i = 0;i < m;++i)
        if(f[i] > k) k = f[p = i];

    for(int i = k-1;i >= 0;--i)
    {
        lcis[i] = b[p];
        p = prev[p];
    }

    return k;
}
