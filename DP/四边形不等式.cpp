for(int i = 0;i <= m;++i)
{
    dp[i][i] = 0;
    K[i][i] = i;
}

for(int len = 1;len <= n-m;++len)
{
    int j;
    dp[0][len] = INF;
    for(int i = 1;(j = i+len) <= n && i <= m;++i)
    {
        dp[i][j] = INF;
        if(i+1 > m) K[i+1][j] = j;
        for(int k = K[i][j-1];k <= K[i+1][j];++k)
        {
            int t = dp[i-1][k-1] + calw(k,j);
            if(dp[i][j] > t)
            {
                dp[i][j] = t;
                K[i][j] = k;
            }
        }
    }
}
