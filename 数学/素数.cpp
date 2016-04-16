bool isprm[maxn+10]; //0表示是prm
int mu[maxn];  //莫比乌斯反演系数
int prm[maxn];
int pn;

void GetPrm(int n) //获取素数表
{
    memset(isprm,0,sizeof(isprm));
    isprm[1] = 1;
    pn = 0;
    for(LL i = 2;i <= n;++i)
        if(!isprm[i])
        {
            prm[pn++] = i;
            for(LL j = i*i;j <= n;j += i) isprm[j] = 1;
        }
}


void GetPrm(int n)  //线性筛
{
    memset(isprm,0,sizeof(isprm));
    isprm[1] = 1;
    pn = 0;
    for(int i = 2;i <=n;++i)
    {
        if(!isprm[i])
            prm[pn++] = i;
        for(int j = 0;j < pn;++j)
        {
            LL t = (LL)i*prm[j];
            if(t > n) break;
            isprm[t]=1;
            if(i%prm[j] == 0) break;
        }
    }
}


int fac_cnt[maxn];
void factorize(int num) //唯一分解定理分解num
{
    memset(fac_cnt,0,sizeof(fac_cnt));
    for(int i = 0;i < pn;++i)
    {
        while(num % prm[i] == 0)
        {
            fac_cnt[i]++;
            num /= prm[i];
        }
        if(num == 1)
            break;
    }
}

int cal(int pr,int n) //计算N!中分解到pr的幂
{
    int res = 0;
    while(n)
        n /= pr,res += n;
    return res;
}


LL phi[maxn];

void GetAllPhi(int n)
{
    for(int i = 2; i <= n; i++) phi[i] = 0;
    phi[1] = 1;
    for(int i = 2; i <= n; i++) if(!phi[i])
        for(int j = i; j <= n; j += i)
        {
            if(!phi[j]) phi[j] = j;
            phi[j] = phi[j] / i * (i-1);
        }
}

LL GetPhi(int n)
{
    int m = (int) sqrt(n+0.5);
    LL ans = n;
    for(int i = 2; i <= m; i++)
        if(n % i == 0)
        {
            ans = ans / i * (i-1);
            while(n % i == 0) n /= i;
        }
    if(n > 1) ans = ans / n * (n-1);
    return ans;
}
//莫比乌斯
int sum[maxn];

void GetMobius(int n)
{
    pn = 0;
    memset(isprm,0,sizeof(isprm));
    mu[1] = 1;
    for(LL i = 2;i <= n;++i)
    {
        if(!isprm[i])
        {
            prm[pn++] = i;
            mu[i] = -1;
        }
        for(LL j = 0;j < pn && i*prm[j] <= n;++j)
        {
            isprm[i*prm[j]] = 1;
            if(i%prm[j]) mu[i*prm[j]] = -mu[i];
            else
            {
                mu[i*prm[j]] = 0;
                break;
            }
        }
    }
    for(int i = 1;i <= n;++i)
        sum[i] = sum[i-1] + mu[i];
}

LL solve(int n,int m) //求1 <= x <= n,1 <= y <= m中 gcd(x,y) == 1的个数
{
    LL res = 0;
    if(n > m) swap(n,m);
    for(int i = 1,last = 0;i <= n;i = last+1)
    {
        last = min(n/(n/i),m/(m/i));
        res += (LL)(n/i)*(m/i)*(sum[last]-sum[i-1]);
    }
    return res;
}

