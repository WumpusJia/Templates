/*
    dp[i][j] 为总共要放i个,共用j种颜色的方案数 每种颜色至少为1
*/

void init()
{
    memset(d,0,sizeof d);
    d[1][1] = 1;
    for(int i=1;i<maxn;++i)
    {
        for(int j=1;j<=i;++j)
        {
            d[i+1][j] += d[i][j]*j %mod;
            d[i+1][j+1] += d[i][j]*(j+1) %mod;
        }
    }
}
