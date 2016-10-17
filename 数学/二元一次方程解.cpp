#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;




typedef long double Double;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
LL a1,b1,a2,b2,L,R;

void exgcd(LL a,LL b,LL& d,LL &x,LL &y)
{
    if(!b)  d = a,x = 1,y = 0;
    else  { exgcd(b,a%b,d,y,x); y -= (a/b)*x; }
}

//求解ax+by+c = 0 x,y在[x1,x2],[y1,y2]之间的解的个数
LL solve(LL a,LL b,LL c,LL x1,LL x2,LL y1,LL y2)
{

    if(c < 0) a = -a,b = -b,c = -c;
    if(a < 0) { a = -a; swap(x1,x2); x1 = -x1,x2 = -x2; }
    if(b < 0) { b = -b; swap(y1,y2); y1 = -y1,y2 = -y2; }



    if(a == 0 && b == 0)
    {
        if(c == 0)
            return (x2-x1+1)*(y2-y1+1);
        else
            return 0;
    }
    else if(a == 0)
    {
        if(c % b == 0 && c/b >= y1 && c/b <= y2)
            return x2-x1+1;
        else
            return 0;
    }
    else if(b == 0)
    {
        if(c%a == 0 && c/a >= x1 && c/a <= x2)
            return y2-y1+1;
        else
            return 0;
    }
    else
    {
        LL x0,y0,d;
        exgcd(a,b,d,x0,y0);
        if(c % d)
            return 0;
        else
        {

            x0 = c/d*x0,y0 = c/d*y0;
            Double tx2 = x2,tx1 = x1,ty1 = y1,
            ty2 = y2,tx0 = x0,ty0 = y0,ta = a/d,tb = b/d,tc = c/d;
            LL down1 = floor((tx2 - tx0)/tb);
            LL down2 = floor((ty0 - ty1)/ta);
            LL r = min(down1,down2);
            LL up1 = ceil((tx1 - tx0)/tb),up2 = ceil((ty0 - ty2)/ta);
            LL l = max(up1,up2);

            if(r < l) return 0;
            else
                return r-l+1;
        }
    }
}



//　ax + by = c 有解　　==>  c % g = 0
// (x*c/g,y*c/g) ==> (x0,y0)
// a'= a/g   b'= b/g
// 解 (x0+kb',y0-ka') k为任意整数
//求解ax+by+c = 0 x,y在[x1,x2],[y1,y2]之间的最小整数解(uncheck)
bool solve(LL a,LL b,LL c,LL x1,LL x2,LL y1,LL y2,LL& resx,LL& resy)
{

    if(c < 0) a = -a,b = -b,c = -c;
    bool negx = false; bool negy = false;
    if(a < 0) { a = -a; swap(x1,x2); x1 = -x1,x2 = -x2;negx = true; }
    if(b < 0) { b = -b; swap(y1,y2); y1 = -y1,y2 = -y2;negy = true; }



    if(a == 0 && b == 0)
    {
        if(c == 0)
        {
            if(!negx)
                resx = x1;
            else
                resx = -x2;
            if(!negy)
                resy = y1;
            else
                resy = -y2;
            return true;
            //return (x2-x1+1)*(y2-y1+1);
        }
        else
            return false;
    }
    else if(a == 0)
    {
        if(c % b == 0 && c/b >= y1 && c/b <= y2)
        {
            if(!negx)
                resx = x1;
            else
                resy = -x2;

            if(!negy)
                resy = c/b;
            else
                negy = -c/b;
            return true;
            //return x2-x1+1;
        }
        else
            return false;
    }
    else if(b == 0)
    {
        if(c%a == 0 && c/a >= x1 && c/a <= x2)
        {
            if(!negx)
                resx = c/a;
            else
                resx = -c/a;
            if(!negy)
                resy = y1;
            else
                resy = -y2;
            return true;
        }
        else
            return false;
    }
    else
    {
        LL x0,y0,d;
        exgcd(a,b,d,x0,y0);
        if(c % d)
            return false;
        else
        {

            x0 = c/d*x0,y0 = c/d*y0;
            Double tx2 = x2,tx1 = x1,ty1 = y1,
            ty2 = y2,tx0 = x0,ty0 = y0,ta = a/d,tb = b/d,tc = c/d;
            LL down1 = floor((tx2 - tx0)/tb);
            LL down2 = floor((ty0 - ty1)/ta);
            LL r = min(down1,down2);
            LL up1 = ceil((tx1 - tx0)/tb),up2 = ceil((ty0 - ty2)/ta);
            LL l = max(up1,up2);

            if(r < l) return false;
            else
            {
                //l,r is Min and Max k.
                int k;
                if(!negx)
                    k = l;
                else
                    k = r;

                if(!negx)
                    resx = x0+k*tb;
                else
                    resx = -(x0+k*tb);
                if(!negy)
                    resy = y0-k*ta;
                else
                    resy = -(y0-k*ta);
                return true;
            }
        }
    }
}

