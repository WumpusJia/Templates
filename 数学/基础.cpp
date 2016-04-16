LL gcd(LL a,LL b)
{
    return !b? a : gcd(b,a%b);
}

LL lcm(LL a,LL b)
{
    return a/gcd(a,b)*b;
}


LL mul_mod(LL a,LL b,LL m)
{
    return a*b%m;
}


LL pow_mod(LL a,LL p,LL m)
{
    LL res = 1;
    while(p)
    {
        if(p&1) res = res*a%m;
        a = a*a%m;
        p >>= 1;
    }
    return res;
}



void exgcd(LL a,LL b,LL& d,LL &x,LL &y)
{
    if(!b)  d = a,x = 1,y = 0;
    else  { exgcd(b,a%b,d,y,x); y -= (a/b)*x; }
}


LL inv(LL a,LL m)
{
    LL d,x,y;
    exgcd(a,m,d,x,y);
    return d==1 ? (x+m) % m : -1;
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


