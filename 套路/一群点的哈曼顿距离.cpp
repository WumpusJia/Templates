/*
如果求一群点中2个点距离最大值 那就2^k枚举每个x,y,z...前面的符号，
然后最大的减最小的 ，这些里面取最大值

如果求一个点和其他点最小  那就2^k次 线段树:
把y作为key, 然后点按x排序。
查询也按x排序，这样滑窗的添加点



*/

#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 50000+100;

struct Node
{
    int x,y;
    int savey;
    int id;
    Node(int x = 0,int y = 0):x(x),y(y) {savey = y;}
    bool operator < (const Node& rhs) const {
        return x < rhs.x;
    }

};
Node T[maxn];
Node Q[maxn];


int savey[maxn*2];
int pn;

int caly(int y)
{
    int id = lower_bound(savey,savey+pn,y)-savey;
    return id+1;
}

int n,q;

struct Point
{
    LL Max,Min;
    bool has;
};

Point p[maxn<<2];

void build(int L,int R,int u)
{
    p[u].Max = -1;
    p[u].Min = -1;
    p[u].has = 0;

    if(L == R)
    {

    }
    else
    {
        int m = (L+R)/2;
        build(L,m,u<<1);
        build(m+1,R,u<<1|1);
    }

}


Point cal(const Point& A,const Point& B)
{
    Point now;
    if(A.has && B.has )
    {
        now.Max = max(A.Max,B.Max);
        now.Min = min(A.Min,B.Min);
        now.has = 1;
    }
    else if(A.has)
    {
        now.Max = A.Max;
        now.Min = A.Min;
        now.has = 1;
    }
    else if(B.has)
    {
        now.Max = B.Max;
        now.Min = B.Min;
        now.has = 1;
    }
    else
    {
        now.Max = now.Min = -1;
        now.has = 0;
    }
    return now;
}

void update(int x,int val,int L,int R,int u)
{
    if(L == R)
    {
        if(!p[u].has)
        {
            p[u].has = 1;
            p[u].Max = p[u].Min = val;
        }
        else
        {
            p[u].Max = max(p[u].Max,val);
            p[u].Min = min(p[u].Min,val);

        }
    }
    else
    {
        int m = (L+R)/2;
        if(x <= m)
            update(x,val,L,m,u<<1);
        else
            update(x,val,m+1,R,u<<1|1);
        p[u] = cal(p[u<<1],p[u<<1|1]);

    }

}

Point query(int cL,int cR,int L,int R,int u)
{
    if(cL <= L && R <= cR)
        return p[u];
    else
    {
        int m = (L+R)/2;
        if(cR <= m)
            return query(cL,cR,L,m,u<<1);
        else if(cL > m)
            return query(cL,cR,m+1,R,u<<1|1);
        else
            return cal(query(cL,cR,L,m,u<<1),query(cL,cR,m+1,R,u<<1|1));

    }

}

LL res[maxn];




int main()
{
    //freopen("./test.txt","r",stdin);
    //freopen("./out.txt","w",stdout);
    while(scanf("%d",&n) == 1 && n != -1)
    {
        int cur = 0;
        for(int i = 0;i < n;++i)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            T[i] = Node(x,y);
            savey[cur++] = y;
        }
        scanf("%d",&q);
        for(int i = 0;i < q;++i)
        {
            int x,y;
            scanf("%d %d",&x,&y);
            Q[i] = Node(x,y);
            Q[i].id = i;
            savey[cur++] = y;
        }


        sort(savey,savey+cur);
        pn = unique(savey,savey+cur)-savey;


        for(int i = 0;i < n;++i)
        {
            T[i].y = caly(T[i].y);
         //   printf("**** %d\n",T[i].y);
        }
        for(int i = 0;i < q;++i)
        {
            Q[i].y = caly(Q[i].y);
       //     printf("xx %d\n",Q[i].y);
        }
        sort(T,T+n);
        sort(Q,Q+q);

        cur = 0;
        memset(res,INF,sizeof(res));
        build(1,pn,1);

        for(int i = 0;i < q;++i) //x <= a && y <= b
        {

            while(cur < n && T[cur].x <= Q[i].x)
            {
                update(T[cur].y,(LL)T[cur].x+T[cur].savey,1,pn,1);
                cur++;
            }

            Point t = query(1,Q[i].y,1,pn,1);
            if(t.has)
            {

                int id = Q[i].id;
                res[id] = min(res[id],(LL)Q[i].x + Q[i].savey - t.Max);
            }

        }


        build(1,pn,1);
        cur = 0;
        for(int i = 0;i < q;++i)  //x <= a && y > b
        {
            while(cur < n && T[cur].x <= Q[i].x)
            {
                update(T[cur].y,(LL)T[cur].x-T[cur].savey,1,pn,1);
                cur++;
            }

            if(Q[i].y+1 <= pn)
            {
                Point t = query(Q[i].y+1,pn,1,pn,1);
                if(t.has)
                {


                    int id = Q[i].id;
                    res[id] = min(res[id],
                        (LL)Q[i].x - Q[i].savey - t.Max);
                }
            }

        }

        build(1,pn,1);
        cur = n-1;
        for(int i = q-1;i >= 0;--i) //x > a && y <= b
        {
            while(cur >= 0 && T[cur].x > Q[i].x)
            {
                update(T[cur].y,(LL)T[cur].x-T[cur].savey,1,pn,1);
                cur--;
            }

            Point t = query(1,Q[i].y,1,pn,1);
            if(t.has)
            {

                int id = Q[i].id;
                res[id] = min(res[id],(LL)t.Min-(Q[i].x - Q[i].savey));
            }

        }

        build(1,pn,1);
        cur = n-1;
        for(int i = q-1;i >= 0;--i) //x > a && y > b
        {
            while(cur >= 0 && T[cur].x > Q[i].x)
            {
                update(T[cur].y,(LL)T[cur].x+T[cur].savey,1,pn,1);
                cur--;
            }

            if(Q[i].y+1 <= pn)
            {
                Point t = query(Q[i].y+1,pn,1,pn,1);
                if(t.has)
                {

                    int id = Q[i].id;
                    res[id] = min(res[id],(LL)t.Min-(Q[i].x+Q[i].savey));
                }
            }

        }

        for(int i = 0;i < q;++i)
            printf("%lld\n",res[i]);
        putchar('\n');

    }
    return 0;
}
