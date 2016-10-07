memset(num,0,sizeof(num));

    int n = N;
    for(int m = 1;m <= N;++m)
    {
        memset(dp,0,sizeof(dp));
        int p = 0;
        dp[p][(1 << m)-1] = 1;


        for(int r = 1;r <= n;++r)
        {
            for(int c = 1;c <= m;++c)
            {
                memset(dp[p^1],0,sizeof(dp[p^1]));
                for(int msk = 0;msk < (1 << m);++msk)
                {
                    if(is1(msk,m-1)) //不放
                    {
                        int nxtmsk = (msk ^ (1 << (m-1))) << 1;
                        dp[p^1][nxtmsk] = (dp[p^1][nxtmsk] +
                            dp[p][msk])%mod;
                    }

                    if(r != 1 && !is1(msk,m-1))//竖放: (r,c)和(r-1,c)
                    {
                        int nxtmsk = (msk << 1) | 1;
                        dp[p^1][nxtmsk] = (dp[p^1][nxtmsk] +
                            dp[p][msk])%mod;
                    }

                    if(c != 1 && !is1(msk,0) && is1(msk,m-1))//横放: (r,c),(r,c-1)
                    {
                        int nxtmsk = ((msk ^ (1 << (m-1))) << 1) | 3;
                        dp[p^1][nxtmsk] = (dp[p^1][nxtmsk] +
                            dp[p][msk])%mod;

                    }

                }
                p ^= 1;

            }
            num[r][m] = (num[r][m] + dp[p][(1 << m)-1])%mod;

        }
    }
