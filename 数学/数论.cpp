#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

typedef long long LL;
const double eps = 1e-6;
const int maxn = 10000;



//V + F-2 = E 顶点数＋面数-2 = 边数
//斐波那且O(1) = ( ( (1+sqrt(5))/2 ) - ( (1-sqrt(5))/2 ) ) / sqrt(5)

LL gcd(LL a,LL b)
{
    return !b? a : gcd(b,a%b);
}

LL lcm(LL a,LL b)
{
    return a/gcd(a,b)*b;
}


/////////////////////////////////////组合数//////////////////////////////////

LL C[maxn+10][maxn+10];

void GetAllC(int n) //计算所有C
{
    for(int i = 0;i <= n;++i)
    {
        C[i][0] = 1;
        for(int j = 1;j <= i;++j) C[i][j] = C[i-1][j] + C[i-1][j-1];
    }
}

LL GetC(int n,int m)//计算C(n,m)
{
    LL res = 1;
    for(int i = 1; i <= n-m ; i++)
    {
        res *= (m + i);
        res /= i;
    }
    return res;
}


////////////////////////////////素数//////////////////////////////////////////
bool isprm[maxn+10]; //0表示是prm
int prm[maxn];
int pn;

void GetPrm(int n) //获取素数表
{
    memset(isprm,0,sizeof(isprm));
    pn = 0;
    for(int i = 2;i <= n;++i)
        if(!isprm[i])
        {
            prm[pn++] = i;
            for(int j = i*i;j <= n;j += i) isprm[j] = 1;
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

LL phi[maxn];

LL GetAllPhi(int n)
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

/////////////////////////////模////////////////////////////////////////

LL mul_mod(LL a,LL b,LL m)
{
    return a*b%m;
}


LL pow_mod(LL a,LL p,LL m)
{
    if(p==0) return 1;
    LL x=pow_mod(a,p/2,m);
    x=x*x % m;
    if(p % 2) x*=x % m;
    return x;
}


void exgcd(LL a,LL b,LL& d,LL &x,LL &y); //前向声明
// 求模m下a的逆. 需要a,m互素，否则返回-1
LL inv(LL a,LL m)
{
    LL d,x,y;
    exgcd(a,m,d,x,y);
    return d==1 ? (x+m) % m : -1;
}



//////////////////////////////////解方程组//////////////////////////////////////////////


// ax + by = gcd(a,b)  解(x,y) g=gcd(a,b)

void exgcd(LL a,LL b,LL& d,LL &x,LL &y)
{
    if(!b)  d = a,x = 1,y = 0;
    else  { exgcd(b,a%b,d,y,x); y -= (a/b)*x; }
}


//　ax + by = c 有解　　==>  c % g = 0
// (x*c/g,y*c/g) ==> (x0,y0)
// a'= a/g   b'= b/g
// 解 (x0+kb',y0-ka') k为任意整数
bool exgcd_res(LL& a,LL& b,LL c,LL& x0,LL& y0)
{
    LL d;
    exgcd(a,b,d,x0,y0);
    if(c % d) return false;
    else
    {
        a=a%d;
        b=b%d;
        x0=x0/d*c;
        y0=y0/d*c;
         return true;
    }
}

//求解线性模方程ax = b(mod n),解为x,x+m0,x+2*m0......
bool line_mod(int a,int b,int m,int& x,int& m0)
{
    int d = gcd(a,m);
    if(b % d) return false;
    else
    {
        int a0 = a/d,b0 = b/d;
        m0 = m/d;
        x = inv(a0,m)*b0;
        return true;
    }
}

//中国剩余定理解线性模方程组x = a[i](mod m[i])
LL china(LL n, LL a[], LL m[])
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

//解模方程a^x = b mod(n) 无解返回-1
int log_mod(int a, int b, int n)
{
    int m, v, e =1, i;
    m = (int) sqrt(n+0.5);
    v = inv(pow_mod(a, m, n), n);
    map<int, int> x;
    x[1] = 0;
    for(i = 1; i < m; i++)
    {
        e = mul_mod(e, a, n);
        if (!x.count(e)) x[e] = i;
    }
    for(i = 0; i < m; i++)
    {
        if(x.count(b)) return i*m + x[b];
        b = mul_mod(b, v, n);
    }
    return -1;
}


///////////////////////矩阵////////////////////////////

typedef int Matrix[maxn][maxn];

void gauss_jordan(Matrix A,int n)
{
    for(int i = 0;i < n;++i)
    {
        int r = i;
        for(int j = i+1;j < n;++j)
            if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
        if(fabs(A[r][i]) < eps) continue;
        if(r != i) for(int j = 0;j <= n;++j) swap(A[r][j],A[i][j]);

        for(int k = 0;k < n;++k)
            if(k != i)
                for(int j = n;j >= i;--j)
                    A[k][j] -= A[k][i]/A[i][i] * A[i][j];
    }
}



int sz; //矩阵大小
int mod; //模
void matrix_mul(Matrix A,Matrix B,Matrix res)
{
    Matrix C;
    memset(C,0,sizeof(C));
    for(int i = 0;i < sz;++i)
        for(int j = 0;j < sz;++j)
            for(int k = 0;k < sz;++k)
                C[i][j] = (C[i][j]  + A[i][k] * B[k][j]) % mod;
    memcpy(res,C,sizeof(C));
}

void matrix_pow(Matrix A,int n,Matrix res)
{
    Matrix a,r;
    memcpy(a,A,sizeof(a));
    memset(r,0,sizeof(r));
    for(int i = 0;i < sz;++i) r[i][i] = 1;
    while(n)
    {
        if(n&1) matrix_mul(r,a,r);
        n >>= 1;
        matrix_mul(a,a,a);
    }
    memcpy(res,r,sizeof(r));
}


//求逆矩阵．．．．．will done

int main()
{
}
