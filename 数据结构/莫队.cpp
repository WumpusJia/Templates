#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef long long LL;
const int maxn = 10000+10;

int n,m;
int ppos[maxn];

struct Node
{
    int L,R,id;
    Node(int L = 0,int R = 0,int id = 0):L(L),R(R),id(id) {}
    bool operator < (const Node& rhs) const {
        return ppos[L] < ppos[rhs.L] || (ppos[L] == ppos[rhs.L] && R < rhs.R);
    }
};

Node p[maxn];
int A[maxn];
int pn;
int temp[maxn];
int pos[maxn];
LL res[maxn];

int gcd(int a,int b)
{
    return !b?a : gcd(b,a%b);
}


void gao()
{
    int idx = 0,prv = -1;
    for(int i = 0;i < pn;++i)
        if(temp[i] != prv)
        {
            prv = temp[i];
            temp[idx] = temp[i];
            pos[idx] = pos[i];
            idx++;
        }
    pn = idx;
}


int numr[maxn][105];
int posr[maxn][105];
int sizer[maxn];

int numl[maxn][105];
int posl[maxn][105];
int sizel[maxn];

void init()
{
    pn = 0;
    for(int i = n;i >= 1;--i)
    {
        for(int j = 0;j < pn;++j) temp[j] = gcd(A[i],temp[j]);
        temp[pn] = A[i];
        pos[pn++] = i;
        gao();
        for(int j = pn-1;j >= 0;--j)
        {
            numr[i][pn-1-j] = temp[j];
            posr[i][pn-1-j] = pos[j];
        }
        sizer[i] = pn;
    }

    pn = 0;
    for(int i = 1;i <= n;++i)
    {
        for(int j = 0;j < pn;++j) temp[j] = gcd(A[i],temp[j]);
        temp[pn] = A[i];
        pos[pn++] = i;
        gao();
        for(int j = pn-1;j >= 0;--j)
        {
            numl[i][pn-1-j] = temp[j];
            posl[i][pn-1-j] = pos[j];
        }
        sizel[i] = pn;
    }
}
/////////////////////////////////

LL sum;
int L,R;


void addl(int sign)
{
    LL now = 0;
    int prv = L;
    for(int i = 0;i < sizer[L];++i)
    {
        if(posr[L][i] < L) continue;

        if(posr[L][i] > R)
            now += (LL)(R-prv+1)*numr[L][i];
        else
        {
            now += (LL)(posr[L][i]-prv+1)*numr[L][i];
            prv = posr[L][i]+1;
        }
        if(posr[L][i] >= R) break;
    }
    sum += sign*now;
}

void addr(int sign)
{
    LL now = 0;
    int prv = R;
    for(int i = 0;i < sizel[R];++i)
    {
        if(posl[R][i] > R) continue;

        if(posl[R][i] < L)
            now += (LL)(prv-L+1)*numl[R][i];
        else
        {
            now += (LL)(prv-posl[R][i]+1)*numl[R][i];
            prv = posl[R][i]-1;
        }
        if(posl[R][i] <= L) break;
    }
    sum += sign*now;
}


int main()
{
   // freopen("./test.txt","r",stdin);
    int kase;
    scanf("%d",&kase);
    while(kase--)
    {
        scanf("%d",&n);
        int BLOCK = (int)sqrt(n+0.5);
        for(int i = 1;i <= n;++i)
        {
            ppos[i] = i/BLOCK;
            scanf("%d",&A[i]);
        }
        init();

        scanf("%d",&m);
        for(int i = 0;i < m;++i)
        {
            scanf("%d %d",&p[i].L,&p[i].R);
            p[i].id = i;
        }
        sort(p,p+m);
        sum = 0;
        L = 1,R = 0;
        for(int i = 0;i < m;++i)
        {
            if(R < p[i].R)
            {
                for(R = R+1;R <= p[i].R;++R)
                    addr(1);
                R--;
            }
            if(R > p[i].R)
            {
                for(;R > p[i].R;--R)
                    addr(-1);
            }
            if(L > p[i].L)
            {
                for(L = L-1;L >= p[i].L;--L)
                    addl(1);
                L++;
            }
            if(L < p[i].L)
            {
                for(;L < p[i].L;++L)
                    addl(-1);
            }
            res[p[i].id] = sum;
        }
        for(int i = 0;i < m;++i)
            printf("%lld\n",res[i]);
    }
    return 0;
}


