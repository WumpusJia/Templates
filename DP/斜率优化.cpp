/*
类似:    k[i]*X[j] + Y[i] = Y[j],求Y[i]最小值
斜率为k[i],横坐标为X[i] ,k[i] > 0递增，且X[i] > 0递增

则可以维护下凸包,用单调队列优化

*/


struct Node
{
    LL x,y;
    Node(LL x = 0,LL y = 0):x(x),y(y) {}
};

Node operator - (const Node& A,const Node& B)
{
    return Node(A.x-B.x,A.y-B.y);
}


LL Cross(const Node& A,const Node& B)
{
    return A.x*B.y-A.y*B.x;

}

Node Q[maxn];

int main()
{

    int head = 0,tail = 0;
    for(int i = LEN;i <= n;++i)  //len为最小间距
    {
        int prv = i-LEN;
        Node now(X[prv],Y[prv]);

        while(head+1 < tail &&
        Cross(Q[tail-1]-Q[tail-2],now-Q[tail-2]) <= 0)
        //必须严格递增 等于号不能少
            tail--;
        Q[tail++] = now;


        while(head+1 < tail && (Q[head+1].y-Q[head].y)
         < (Q[head+1].x-Q[head].x)*k[i])
            head++;

        Y[i] = Q[head].y-Q[head].x*k[i];
    }


}






//////////////////////////////////
//横坐标不递增的情况

#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxn = 1e6+100;

LL dp[maxn];
int n;

LL A[maxn];
LL D[maxn];



struct Node
{
    LL x,y;
    Node(LL x = 0,LL y = 0):x(x),y(y) {}
    bool operator < (const Node& rhs) const {
        return x < rhs.x;
    }
};

Node operator - (const Node& A,const Node& B)
{
    return Node(A.x-B.x,A.y-B.y);
}

LL Cross(Node A,Node B) { return A.x*B.y - A.y*B.x; }


Node Stack[maxn];



LL cal(int id,int k)
{
    return Stack[id].y - Stack[id].x*k;
}


const double eps = 1e-8;

int dcmp(double a)
{
    if(fabs(a) < eps) return 0;
    else return a > 0?1:-1;
}

int cmp(const Node& A,const Node& B,LL k)
{
    if(A.x == B.x) return 1;
    double t1 = (double)(A.y-B.y)/(A.x-B.x);
    double t2 = k;
    return dcmp(t1-t2);
}

LL solve(int L,int R,int k)
{


    if(L >= R)
        return cal(L,k);
    else if(cmp(Stack[L],Stack[L+1],k) <= 0) // k >= xxx
        return cal(L,k);
    else if(cmp(Stack[R],Stack[R-1],k) >= 0) // k <= xx
        return cal(R,k);
    else
    {

        int tL = L,tR = R;
        while(L <= R)
        {
            int mid = (L+R)/2;
            if(mid == tR)
            {
                R = mid-1;
                continue;
            }
            if(mid == tL)
            {
                L = mid+1;
                continue;
            }

            int c1 = cmp(Stack[mid-1],Stack[mid],k);
            int c2 = cmp(Stack[mid+1],Stack[mid],k);
            if(c1 >= 0 && c2 <= 0)
                return cal(mid,k);
            else if(c2 >= 0)
                L = mid+1;
            else if(c1 <= 0)
                R = mid-1;
            else
                assert(false);
        }

    }

}

Node s[maxn];


void CDQ(int L,int R)
{
    int m = (L+R)/2;
    if(L < R)
    {
        CDQ(L,m);
    }
    int id = 0;
    for(int i = L;i <= m;++i)
        s[id++] = Node(D[i],dp[i]+i*D[i]);
    sort(s,s+id);

    int head = 0,tail = 0;
    for(int i = 0;i < id;++i)
    {
        Node now = s[i];
        if(tail-head >= 2 && now.y <= Stack[tail-1].y)
        {
        }
        else
        {
            while(tail-head >= 2 &&
            Cross(Stack[tail-1]-Stack[tail-2],now-Stack[tail-2]) >= 0)
                tail--;
            Stack[tail++] = now;
        }

    }


    for(int i = m+1;i <= R;++i)
    {
        LL t = solve(head,tail-1,i);
        dp[i] = max(dp[i],t+A[i]);
    }

    if(L < R)
    {
        CDQ(m+1,R);
    }



}

/*
    f[i] = min{ (i-j)*(-d[j]) + f[j] } + a[i];
    变换一下
        i*d[j] + (f[i]-a[i]) = j*d[j] + f[j]
    变成了 ax + b = y 的形式， a = i, b = f[i]-a[i]
    这样需要维护一个上凸壳,  对于i来说，
    只需要二分找到凸包上与斜率为i的直线的切点即可
    不过这里凸包上的点为(d[j]，j*d[j] + f[j]） ，
    横坐标不递增，所以需要splay维护凸壳或者这里的cdq分治

    复杂度为n*log^2(n)
    可以优化成nlogn(此代码未优化),
    把cdq中的sort归并了,由于斜率i是递增的，
    不用二分，而是每次加入点后，把head前移)

*/


int main()
{
  //  freopen("./test.txt","r",stdin);
    scanf("%d",&n);
    A[0] = 0,D[0] = 0;
    A[n+1] = 0,D[n+1] = 0;
    for(int i = 1;i <= n;++i)
        scanf("%lld %lld",&A[i],&D[i]);
    memset(dp,0,sizeof(dp));
    CDQ(0,n+1);
    printf("%lld\n",dp[n+1]);


    return 0;
}

