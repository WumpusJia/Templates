#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;


/*
如果想要指数a-b减,那么把x2 reverse

*/

const double pi = acos(-1.0);
const int maxn = 500000+10;

struct Complex
{
    double real,imag;
    Complex(double r = 0,double i = 0):real(r),imag(i) {}

    Complex operator + (const Complex& A)
    {
        return Complex(real+A.real,imag+A.imag);
    }
    Complex operator - (const Complex& A)
    {
        return Complex(real-A.real,imag-A.imag);
    }
    Complex operator * (const Complex& A)
    {
        return Complex(real*A.real-imag*A.imag,imag*A.real+real*A.imag);
    }
};
Complex x1[maxn],x2[maxn];


void rader(Complex F[],int len)
{
    int j = len/2;
    for(int i = 1;i < len-1;++i)
    {
        if(i < j) swap(F[i],F[j]);
        int k = len/2;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}


void FFT(Complex F[],int len,int op) //op = -1为IDFT
{
    rader(F,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        Complex wn(cos(op*2*pi/h),sin(op*2*pi/h));
        for(int j = 0;j < len;j += h)
        {
            Complex E(1,0);
            for(int k = j;k < j+h/2;++k)
            {
                Complex u = F[k];
                Complex v = E*F[k+h/2];
                F[k] = u+v;
                F[k+h/2] = u-v;
                E = E*wn;
            }
        }
    }
    if(op == -1)
        for(int i = 0;i < len;++i)
            F[i].real /= len;
}


char a[maxn],b[maxn];
int res[maxn];

int main()
{
    //freopen("./test.txt","r",stdin);
    while(scanf("%s %s",a,b) == 2)
    {
        int lena = strlen(a);
        int lenb = strlen(b);
        int len = 1;
        while(len < lena*2 || len < lenb*2) len <<= 1;

        for(int i = 0;i < lena;++i)
        {
            x1[i].real = a[lena-i-1] - '0';
            x1[i].imag = 0.0;
        }
        for(int i = lena;i < len;++i)
        {
            x1[i].real = 0.0;
            x1[i].imag = 0.0;
        }

        for(int i = 0;i < lenb;++i)
        {
            x2[i].real = b[lenb-i-1] - '0';
            x2[i].imag = 0.0;
        }
        for(int i = lenb;i < len;++i)
        {
            x2[i].real = 0.0;
            x2[i].imag = 0.0;
        }

        FFT(x1,len,1);
        FFT(x2,len,1);

        for(int i = 0;i < len;++i) x1[i] = x1[i]*x2[i];

        FFT(x1,len,-1);
        for(int i = 0;i < len;++i)
            res[i] = (int)(x1[i].real+0.5);

        for(int i = 0;i < len;++i)
        {
            res[i+1] += res[i]/10;
            res[i] %= 10;
        }
        len = lena+lenb-1;
        while(res[len] <= 0 && len > 0) len--;
        for(int i = len;i >= 0;--i) printf("%c",res[i]+'0');
        printf("\n");
    }
    return 0;
}


/////////////////////////////NTT版本////////////////////////////
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500000+10;
typedef long long LL;
const LL MOD = (479 << 21)+1;
const int G = 3;


LL x1[maxn],x2[maxn],wn[30];

void rader(LL F[],int len)
{
    int j = len/2;
    for(int i = 1;i < len-1;++i)
    {
        if(i < j) swap(F[i],F[j]);
        int k = len/2;
        while(j >= k)
        {
            j -= k;
            k >>= 1;
        }
        if(j < k) j += k;
    }
}


LL Pow(LL a,LL n,LL mod)
{
    LL res = 1;
    a %= mod;
    while(n)
    {
        if(n&1)
            res = res*a%mod;
        n >>= 1;
        a = a*a%mod;
    }
    return res;
}

void NTT(LL F[],int len,int op)
{
    int id = 0;
    rader(F,len);
    for(int h = 2;h <= len;h <<= 1)
    {
        id++;
        for(int j = 0;j < len;j += h)
        {
            LL E = 1;
            for(int k = j;k < j+h/2;++k)
            {
                LL u = F[k]%MOD;
                LL v = E*(F[k+h/2]%MOD)%MOD;
                F[k] = (u+v)%MOD;
                F[k+h/2] = ((u-v)%MOD+MOD)%MOD;
                E = (E*wn[id])%MOD;
            }
        }
    }
    if(op == -1)
    {
        for(int i = 1;i < len/2;++i)
            swap(F[i],F[len-i]);
        LL inv = Pow(len,MOD-2,MOD);
        for(int i = 0;i < len;++i)
            F[i] = (F[i]%MOD*inv)%MOD;
    }
}


void init()
{
    for(int i = 0;i < 21;++i)
    {
        int t = 1 << i;
        wn[i] = Pow(G,(MOD-1)/t,MOD);
    }
}

char a[maxn],b[maxn];
LL res[maxn];


int main()
{
    init();
    while(scanf("%s %s",a,b) == 2)
    {
        int lena = strlen(a);
        int lenb = strlen(b);
        int len = 1;
        while(len < lena*2 || len < lenb*2) len <<= 1;

        for(int i = 0;i < lena;++i)
          x1[i] = a[i]-'0';
          //  x1[lena-i-1] = a[i]-'0'; //?
        for(int i = lena;i < len;++i) x1[i] = 0;

        for(int i = 0;i < lenb;++i)
            x2[i] = b[i]-'0';
            //x2[lenb-i-1] = b[i]-'0';
        for(int i = lenb;i < len;++i) x2[i] = 0;

        NTT(x1,len,1);
        NTT(x2,len,1);

        for(int i = 0;i < len;++i)
            x1[i] = (x1[i]*x2[i])%MOD;

        NTT(x1,len,-1);
        for(int i = 0;i < len;++i)
            res[i] = x1[i];

        for(int i = 0;i < len;++i)
        {
            res[i+1] += res[i]/10;
            res[i] %= 10;
        }
        len = lena+lenb-1;
        while(res[len] <= 0 && len > 0) len--;
        for(int i = len;i >= 0;--i) printf("%c",res[i]+'0');
        printf("\n");
    }
    return 0;
}


////////////////母函数//////////////////////////
memset(c1,0,sizeof(c1));
memset(c2,0,sizeof(c2));
memset(num,0,sizeof(num));
int sum = 0;
for(int i = 0;i < n;++i)
{
    scanf("%d",&A[i]);
    sum += A[i];
    num[i] = 1;
}

for(int i = 0;i <= num[0]*A[0];i += A[0])
    c1[i] = 1;
for(int i = 1;i < n;++i)
{
    for(int j = 0;j <= sum;++j)
        for(int k = 0;k <= num[i]*A[i] && j + k <= sum; k += A[i])
        {
            c2[j+k] += c1[j];
            c2[abs(j-k)] += c1[j];
        }
    for(int j = 0;j <= sum;++j)
    {
        c1[j] = c2[j];
        c2[j] = 0;
    }
}

/*

如果NTT的结果为LL,那么需要取2个MOD,然后CRT合并

r*2^k+1  r⋅2k+1	r	k	g
3	1	1	2
5	1	2	2
17	1	4	3
97	3	5	5
193	3	6	5
257	1	8	3
7681	15	9	17
12289	3	12	11
40961	5	13	3
65537	1	16	3
786433	3	18	10
5767169	11	19	3
7340033	7	20	3
23068673	11	21	3
104857601	25	22	3
167772161	5	25	3
469762049	7	26	3
1004535809	479	21	3
2013265921	15	27	31
2281701377	17	27	3
3221225473	3	30	5
75161927681	35	31	3
77309411329	9	33	7
206158430209	3	36	22
2061584302081	15	37	7
2748779069441	5	39	3
6597069766657	3	41	5
39582418599937	9	42	5
79164837199873	9	43	5
263882790666241	15	44	7
1231453023109121	35	45	3
1337006139375617	19	46	3
3799912185593857	27	47	5
4222124650659841	15	48	19
7881299347898369	7	50	6
31525197391593473	7	52	3
180143985094819841	5	55	6
1945555039024054273	27	56	5
4179340454199820289	29	57	3

*/
