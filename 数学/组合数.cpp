void GetBell(int n) //贝尔数----n个数非空划分的方法数
{
    B[0] = B[1] = 1;
    for(int i = 2;i <= n;++i)
    {
        B[i] = 0;
        for(int j = 0;j <= i-1;++j)
        {
            B[i] = (B[i] + C[i-1][j]*B[j]%mod)%mod;
        }
    }
}


void GetStirling2(int n)
{
    memset(S,0,sizeof(S));
    S[0][0] = 1;
    for(int i = 1;i <= n;++i)
    {
        S[i][0] = 0;
        for(int j = 1;j <= i;++j)
            S[i][j] = (j*S[i-1][j]%mod + S[i-1][j-1])%mod;
    }

}

//分组数
void getM(int n)
{
	memset(M,0,sizeof M);
	M[1][1] = 1;
	for(int i=2;i<=n;++i)
	{
		M[i][1] = 1;
		for(int j=2;j<=i;++j)
			M[i][j] = (M[i-j][j] + M[i-1][j-1])%mod;
	}
}

LL C[maxn+10][maxn+10];

void GetAllC(int n) //计算所有C
{
    for(int i = 0;i <= n;++i)
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;++j) C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
    }
}

LL GetC(LL n,LL m)
{
    m = m < (n-m)? m : (n-m);
    LL res = 1;
    for(int i = 1;i <= m;++i)
        res = res*(n-i+1)/i;
    return res;
}



LL fac[200000+100];

//如果计算次数较多，还可以预处理出invfac[n-m]和invfac[m],来减小常数
LL GetC(LL n,LL m) //预处理版本　fac[0] = 1;
{
    if(n < m) return 0;
    if(m > n-m) m = n-m;
    return fac[n]*pow_mod(fac[n-m]*fac[m]%mod,mod-2)%mod;
}

//！！！同理，当m较小时，也可以预处理出inv(m!)加速

//利用计算C(n,m) % p,p是素数的
LL GetC(LL n,LL m)
{
    if(n < m) return 0;
    if(m > n-m) m = n-m;
    LL s1 = 1,s2 = 1;
    for(LL i = 0;i < m;++i)
    {
        s1 = (s1*(n-i))%mod;
        s2 = (s2*(i+1))%mod;
    }
    return s1*pow_mod(s2,mod-2)%mod;//b在p为素数下的逆为b^(p-2)%p
}

//当C(n,m)非常大时候，需要利用lucas计算C(n,m)%p
LL lucas(LL n,LL m)
{
    if(m == 0) return 1;
    return GetC(n%mod,m%mod)*lucas(n/mod,m/mod)%mod;
}
