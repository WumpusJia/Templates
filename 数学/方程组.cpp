void exgcd(LL a,LL b,LL& d,LL &x,LL &y)
{
    if(!b)  d = a,x = 1,y = 0;
    else  { exgcd(b,a%b,d,y,x); y -= (a/b)*x; }
}




//求解线性模方程ax = b(mod n),解为x,x+m0,x+2*m0......
bool line_mod(LL a,LL b,LL m,LL& x,LL& m0)
{
    LL d,y;
    exgcd(a,m,d,x,y);
    if(b % d) return false;
    else
    {
       x = x*b/d;
       m0 = m/d;
       x = ((x%m0)+m0)%m0;//x 为最小正数解
        return true;
    }

}

//中国剩余定理解线性模方程组x = a[i](mod m[i])
LL china(LL n, LL a[], LL m[]) //m都互质
{
    LL M = 1, d, y, x = 0;
    for(int i = 0; i < n; i++) M *= m[i];
    for(int i = 0; i < n; i++)
    {
        LL w = M / m[i];
        exgcd(m[i], w, d, d, y);
        x = (x + y*w*a[i]) % M;
    }
    return (x+M) % M;
}

/*我们先可以先找两个同余方程 设通解为N,N=r1(mod(m1)),N=r2(mod(m2)),
显然可以化为k1*m1+r1=k2*m2+r2;--->k1*m1+(-k2*m2)=r2-r1;
设a=m1,b=m2,x=k1,y=(-k2),c=r2-r1方程可写为ax+by=c;
由欧几里得解得x即可,那么将x化为原方程的最小正整数解，
x*(c/d)%(b/d)+(b/d))%(b/d);
这里看不懂的去看解模线性方程。那么这个x就是原方程的最小整数解。
所以N=a*（x+n*（b/d））+r1====N=(a*b/d)*n+(a*x+r1),
这里只有n为未知数所以又是一个N=(a*x+r1)(mod(a*b/d))的式子，
然后只要不断的将两个式变成一个式子，最后就能解出这个方程组的解。 */
LL china(LL n,LL A[],LL M[]) //m不互质的情况，求最小x
{
    LL a = M[0],c1 = A[0];
    for(int i = 1;i < n;++i)
    {
        LL b = M[i],c2 = A[i];
        LL x,y,d;
        exgcd(a,b,d,x,y);
        LL c = c2-c1;
        if(c % d) return -1;
        LL b1 = b/d;
        x = ( (c/d*x)%b1 + b1)%b1;
        c1 = a*x+c1;
        a = a*b1;
    }
    if(c1 == 0) //当余数都为0,那么取最小公倍数
    {
        c1 = 1;
        for(int i = 0;i < n;++i)
            c1 = M[i]/gcd(c1,M[i])*c1;
    }
    return c1;
}


//解模方程a^x = b mod(n) 无解返回-1 （对于n是素数的情况)
LL log_mod(LL a,LL b,LL n)
{
    LL m = (LL)sqrt(n+0.5);
    LL v = inv(pow_mod(a,m,n),n);
    LL e = 1;
    map<LL,LL> x;
    x[1] = 0;
    for(int i = 1;i < m;++i)
    {
        e = mul_mod(e,a,n);
        if(!x.count(e)) x[e] = i;
    }
    for(int i = 0;i < m;++i)
    {
        if(x.count(b)) return i*m+x[b];
        b = mul_mod(b,v,n);
    }
    return -1;
}


//扩展Baby step Gaint step (对于任意n）
/*
 方法：
    初始d=1,c=0,i=0;
    1.令g=gcd(a,n),若g==1则执行下一步。否则由于a^x=k*n+b;(k为某一整数),
    则(a/g)*a^k=k*(n/g)+b/g,(b/g为整除，若不成立则无解)
令n=n/g，d=d*a/g，b=b/g,c++则d*a^(x-c)=b(mod n),接着重复1步骤。
    2.通过1步骤后，保证了a和d都与n互质，方程转换为d*a^(x-c)=b(mod n)。
    由于a和n互质，所以由欧拉定理a^phi(n)==1(mod n),(a,n互质)
可知，phi(n)<=n,a^0==1(mod n),所以构成循环，且循环节不大于n。
从而推出如果存在解，则必定1<=x<n。(在此基础上我们就可以用
Baby Step Giant Step方法了)
    3.令m=ceil(sqrt(n)),则m*m>=n。用哈希表存储a^0,a^1,..,a^(m-1)，
    接着判断1~m*m-1中是否存在解。
    4.为了减少时间，所以用哈希表缩减复杂度。分成m次遍历，每次遍历a^m长度。
    由于a和d都与n互质，所以gcd(d,n)=1，
所以用拓展的欧几里德定理求得d*x+n*y=gcd(d,n)=1,的一组整数解(x,y)。
则d*x+n*y=1-->d*x%n=(d*x+n*y)%n=1-->d*(x*b)%n=((d*x)%n*b%n)%n=b。
所以若x*b在哈希表中存在，值为k，则a^k*d=b(mod n),答案就是ans=k+c+i*m。
如果不存在，则令d=d*a^m,i++后遍历下一个a^m，直到遍历a^0到a^(m-1)还未找到，
则说明不解并退出。
*/
LL log_mod (LL a,LL b,LL n,LL c,LL d)
{
    LL m,v,e=1,i,x,y,dd;
    m=(LL)(sqrt(n+0.5));     //x=i*m+j
    map<LL,LL>f;
    f[1]=m;
    for(i=1;i<m;i++)  //建哈希表，保存a^0,a^1,...,a^m-1
    {
        e=(e*a)%n;
        if(!f[e])f[e]=i;
    }
    e=(e*a)%n;//e=a^m
    for(i=0;i<m;i++)//每次增加m次方，遍历所有1<=f<=n
    {
        exgcd(d,n,dd,x,y);//d*x+n*y=1-->(d*x)%n=1-->d*(x*b)%n==b
        x=(x*b%n+n)%n;
        if(f[x])
        {
            LL num=f[x];
            f.clear();//需要清空，不然会爆内存
            return c+i*m+(num==m?0:num);
        }
        d=(d*e)%n;
    }

    return -1;
}

int main()
{
    LL a,b,n;
    while(scanf("%lld %lld %lld",&a,&n,&b) == 3)
    {
        if(b >= n)
        {
            puts("Orz,I can’t find D!");
            continue;
        }
        if(b == 0)
        {
            printf("0");
            continue;
        }
        LL ans = 0,c = 0,d = 1,t;
        while((t = gcd(a,n)) != 1)
        {
            if(b % t) { ans = -1; break; }
            c++;
            n /= t;
            b /= t;
            d = d*a/t%n;
            if(d == b) { ans = c;break; }
        }
        if(ans != 0)
        {
            if(ans == -1)  puts("Orz,I can’t find D!");
            else printf("%lld\n",ans);
        }
        else
        {
            ans = log_mod(a,b,n,c,d);
            if(ans == -1) puts("Orz,I can’t find D!");
            else printf("%lld\n",ans);
        }
    }
    return 0;
}
