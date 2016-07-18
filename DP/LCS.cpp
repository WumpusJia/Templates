int LCS(int n,int m)
{
    for(int i = 0;i <= n;++i) d[i][0] = 0;
    for(int i = 0;i <= m;++i) d[0][i] = 0;
    for(int i = 1;i <= n;++i)
        for(int j = 1;j <= m;++j)
            if(a[i] == b[j]) d[i][j] = d[i-1][j-1]+1;
            else d[i][j] = max(d[i-1][j],d[i][j-1]);
    return d[n][m];
}
