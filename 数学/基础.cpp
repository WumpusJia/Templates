LL gcd(LL a,LL b)
{
    return !b? a : gcd(b,a%b);
}

LL lcm(LL a,LL b)
{
    return a/gcd(a,b)*b;
}


LL mul_mod(LL a,LL b)
{
    return a*b%mod;
}


LL pow_mod(LL a,LL p)
{
    LL res = 1;
    while(p)
    {
        if(p&1) res = res*a%mod;
        a = a*a%mod;
        p >>= 1;
    }
    return res;
}



void exgcd(LL a,LL b,LL& d,LL &x,LL &y)
{
    if(!b)  d = a,x = 1,y = 0;
    else  { exgcd(b,a%b,d,y,x); y -= (a/b)*x; }
}


LL inv(LL a)
{
    LL d,x,y;
    exgcd(a,mod,d,x,y);
    return d==1 ? (x+mod) % mod : -1;
}

//或者
LL inv(LL a)
{
    return pow_mod(a,mod-2);
}

LL INV[maxn];

//预处理每个数的逆元
void initINV()
{
    INV[1] = 1;
    for(int i = 2;i < maxn;++i)
        INV[i] = (mod-mod/i)*INV[mod%i]%mod;
}


LL sum(LL p,LL n) //二分等比求和
{
	if(n==0) return 1;
	if(n&1) return (1+pow_mod(p,(n>>1)+1))*sum(p,n>>1)%mod;
	else return ((1+pow_mod(p,(n>>1)+1))*sum(p,(n-1)>>1)%mod
            +pow_mod(p,n>>1))%mod;
}


//放防止爆LL 乘法
LL mul( LL a, LL b )
{
	LL k = (long double)a * b / mod;
	LL r = a * b - mod * k;
	while (r < 0) r += mod;
	while (r >= mod) r -= mod;
	return r;
}


