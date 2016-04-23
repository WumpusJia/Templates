#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;


//求解ax+by+c = 0 x,y在[x1,x2],[y1,y2]之间的解的个数

typedef long long LL;

void gcd(LL a,LL b,LL&d,LL &x,LL&y)
{
    if(!b) d = a,x = 1,y = 0;
    else { gcd(b,a%b,d,y,x); y -= x*(a/b;}
}

int main()
{
  //  freopen("./test.txt","r",stdin);
    LL a,b,c,x1,x2,y1,y2;
    scanf("%lld %lld %lld %lld %lld %lld %lld",&a,&b,&c,&x1,&x2,&y1,&y2);
    c = -c;
    if(c < 0) a = -a,b = -b,c = -c;
    if(a < 0) { a = -a; swap(x1,x2); x1 = -x1,x2 = -x2; }
    if(b < 0) { b = -b; swap(y1,y2); y1 = -y1,y2 = -y2; }
    if(a == 0 && b == 0)
    {
        if(c == 0)
            printf("%lld\n",(x2-x1+1)*(y2-y1+1));
        else
            puts("0");
    }
    else if(a == 0)
    {
        if(c % b == 0 && c/b >= y1 && c/b <= y2)
            printf("%lld\n",x2-x1+1);
        else
            puts("0");
    }
    else if(b == 0)
    {
        if(c%a == 0 && c/a >= x1 && c/a <= x2)
            printf("%lld\n",y2-y1+1);
        else
            puts("0");
    }
    else
    {
        LL x0,y0,d;
        gcd(a,b,d,x0,y0);
        if(c % d)
            puts("0");
        else
        {
            x0 = c/d*x0,y0 = c/d*y0;
            double tx2 = x2,tx1 = x1,ty1 = y1,ty2 = y2,tx0 = x0,ty0 = y0,ta = a/d,tb = b/d,tc = c/d;
            LL down1 = floor((tx2 - tx0)/tb),down2 = floor((ty0 - ty1)/ta);
            LL r = min(down1,down2);
            LL up1 = ceil((tx1 - tx0)/tb),up2 = ceil((ty0 - ty2)/ta);
            LL l = max(up1,up2);
            if(r < l) puts("0");
            else
                printf("%lld\n",r-l+1);
        }
    }
    return 0;
}
