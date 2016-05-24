/*

类似最小乘积生成树

*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<cassert>
#include<cmath>
using namespace std;
typedef long long LL;

const LL INF = 0x3f3f3f3f3f3f3f3f;

const int maxn = 400+10;
const int maxa = 800+10;

int sa[maxn];
int sb[maxn];
int sc[maxn];
int n,m;
int suma;
struct Point
{
    LL x,y;
    Point(LL x = 0,LL y = 0):x(x),y(y) {}

};

typedef Point Vector;
Vector operator - (const Point& A,const Point& B)
{
    return Vector(A.x-B.x,A.y-B.y);
}

LL Cross(const Vector& A,const Vector& B)
{
    return A.x*B.y-A.y*B.x;
}
// x : \sum b   y : \sum c






/*
由于C离AB最远，所以S△ABC面积最大。
向量AB=（B.x - A.x , B.y - A.y）
向量AC= (C.x - A.x , C.y - A.y)

最小化：(B.x-A.x)*(C.y-A.y)-(B.y-A.y)*(C.x-A.x)

=(B.x-A.x)*C.y+(A.y-B.y)*C.x  -  A.y*(B.x-A.x)+A.x*(B.y-A.y)

每个点的权值修改为 (A.y-B.y)*x[i] + (B.x-A.x)*y[i]
*/

LL dp[maxn][maxa];
LL num1[maxn][maxa];
LL num2[maxn][maxa];

Point getC(const Point& A,const Point& B,int x[],int y[])
{
    //start 这里是求使 y[i]*(B.x-A.x)+(A.y-B.y)*x[i]最小的原问题
    memset(dp,INF,sizeof(dp));
    dp[0][0] = 0;
    num1[0][0] = 0;
    num2[0][0] = 0;
    for(int i = 1;i <= n;++i)
    {
        LL c = (LL)(A.y-B.y)*x[i] + (LL)y[i]*(B.x-A.x);
        for(int j = 0;j <= suma;++j)
            if(dp[i-1][j] != INF)
            {
                if(dp[i][j+sa[i]] > dp[i-1][j] + c)
                {
                    dp[i][j+sa[i]] = dp[i-1][j] + c;
                    num1[i][j+sa[i]] = num1[i-1][j] + x[i];
                    num2[i][j+sa[i]] = num2[i-1][j] + y[i];
                }
                if(dp[i][j] > dp[i-1][j])
                {
                    dp[i][j] = dp[i-1][j];
                    num1[i][j] = num1[i-1][j];
                    num2[i][j] = num2[i-1][j];
                }
            }
    }

    LL t = INF;
    LL X,Y;

    for(int i = m;i <= suma;++i)
        if(dp[n][i] < t)
        {
            t = dp[n][i];
            X = num1[n][i];
            Y = num2[n][i];
        }

    //end
    return Point(X,Y);
}



LL res;

void solve(Point A,Point B)
{
    Point C = getC(A,B,sb,sc);

    res = min(res,(LL)C.x*C.y);

    if(Cross(C-A,B-A) != 0)
    {
        solve(A,C);
        solve(C,B);
    }
}

int main()
{
   // freopen("./test.txt","r",stdin);
    while(scanf("%d %d",&n,&m) == 2)
    {
        suma = 0;
        for(int i = 1;i <= n;++i)
        {
            scanf("%d %d %d",&sa[i],&sb[i],&sc[i]);
            suma += sa[i];
        }

        res = INF;
        Point A = getC(Point(0,1),Point(0,0),sb,sc);
        res = min(res,A.x*A.y);  //这里注意 不可缺少!!
        Point B = getC(Point(0,0),Point(1,0),sb,sc);
        res = min(res,B.x*B.y); //这里注意,不可缺少!!

        solve(A,B);
        printf("%lld\n",res);

    }

    return 0;
}


