1
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

const int maxn = 10000+100;
const int BASE = 10000;
typedef long long LL;

struct Edge
{
    int x;
    int y1,y2;
    int flag;
    Edge(int x,int y1,int y2,int flag):x(x),y1(y1),y2(y2),flag(flag) {}
    bool operator < (const Edge& rhs) const {
        return x < rhs.x || (x == rhs.x && flag == 1);
    }
};

vector<Edge> save;
vector<int> point;
int ori[maxn];
int id[maxn*2];
int n;
int pn;


struct Node
{
    int cnt;
    int sum;
    bool l,r;
    int line;
    Node(int cnt = 0,int sum = 0,bool l = 0,bool r = 0,int line = 0):
        cnt(cnt),sum(sum),l(l),r(r),line(line) {}
};

Node p[maxn<<2];

void build(int L,int R,int u)
{
    p[u].cnt = p[u].sum = 0;
    p[u].l = p[u].r = p[u].line = 0;
    if(L < R)
    {
        int m = (L+R)/2;
        build(L,m,u<<1);
        build(m+1,R,u<<1|1);
    }
}


void maintain(int u,int L,int R)
{
    p[u].sum = 0;
    p[u].l = p[u].r = p[u].line = 0;
    if(L < R)
    {
        p[u].sum += p[u<<1].sum + p[u<<1|1].sum;
        p[u].l = p[u<<1].l;
        p[u].r = p[u<<1|1].r;
        p[u].line += p[u<<1].line + p[u<<1|1].line -
            (p[u<<1].r && p[u<<1|1].l);
    }
    if(p[u].cnt)
    {
        p[u].l = p[u].r = p[u].line = 1;
        p[u].sum = ori[R]-ori[L-1];
    }
}


void update(int cL,int cR,int val,int L,int R,int u)
{
    if(cL <= L && R <= cR)
    {
        p[u].cnt += val;
    }
    else
    {
        int m = (L+R)/2;
        if(cL <= m)
            update(cL,cR,val,L,m,u<<1);
        if(cR > m)
            update(cL,cR,val,m+1,R,u<<1|1);
    }
    maintain(u,L,R);
}


Node query(int cL,int cR,int L,int R,int u,int add)
{
    if(cL <= L && R <= cR)
    {
        Node res = p[u];
        return res;
    }
    else
    {
        int m = (L+R)/2;
        Node res;
        if(cL <= m && cR <= m)
        {
            res = query(cL,cR,L,m,u<<1,add+p[u].cnt);
        }
        else if(cL > m && cR > m)
        {
            res = query(cL,cR,m+1,R,u<<1|1,add+p[u].cnt);
        }
        else
        {
            Node a = query(cL,cR,L,m,u<<1,add+p[u].cnt);
            Node b = query(cL,cR,m+1,R,u<<1|1,add+p[u].cnt);
            res.l = a.l; res.r = b.r;
            res.line = a.line + b.line - (a.r && b.l);
            res.sum = a.sum + b.sum;
        }
        if(p[u].cnt)
        {
            res.l = res.r = res.line = 1;
            res.sum = ori[R]-ori[L-1];
        }
        return res;
    }
}






int main()
{
 //   freopen("./test.txt","r",stdin);
    while(scanf("%d",&n) == 1)
    {
        save.clear();
        point.clear();
        for(int i = 0;i < n;++i)
        {
            int x1,y1,x2,y2;
            scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
            x1 += BASE,y1 += BASE,x2 += BASE,y2 += BASE;
            save.push_back(Edge(x1,y1,y2,1));
            save.push_back(Edge(x2,y1,y2,-1));
            point.push_back(y1);
            point.push_back(y2);
        }
        sort(save.begin(),save.end());
        sort(point.begin(),point.end());
        pn = unique(point.begin(),point.end())-point.begin();
        for(int i = 0;i < pn;++i)
        {
            id[point[i]] = i;
            if(i == 0) ori[i] = 0;
            else
                ori[i] = ori[i-1] + point[i]-point[i-1];
        }

        build(0,pn-1,1);

        for(int i = 0;i < 2*n;++i)
            int L = id[save[i].y1],R = id[save[i].y2];

        LL res = 0;
        for(int i = 0;i < 2*n;++i)
        {
            int L = id[save[i].y1],R = id[save[i].y2];
            L++;
            Node prev = query(L,R,0,pn-1,1,0);
            int line = query(0,pn-1,0,pn-1,1,0).line;
            update(L,R,save[i].flag,0,pn-1,1);
            Node now = query(L,R,0,pn-1,1,0);

            res += 2*line*( (i == 0)?0:save[i].x-save[i-1].x );
            res += abs(now.sum-prev.sum);
        }
        printf("%lld\n",res);
    }
    return 0;
}
