#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;


const int maxn = 50005;
const int maxm = 45005;

struct Node
{
    int x,y,z,opr,id;
    Node(int x = 0,int y = 0,int z = 0,int opr = 0,int id = 0):
        x(x),y(y),z(z),
        opr(opr),id(id) {}
};

bool cmpx(const Node& A,const Node& B)
{
    return A.x < B.x || (A.x == B.x && A.id < B.id);
}

bool cmpy(const Node& A,const Node& B)
{
    return A.y < B.y || (A.y == B.y && A.id < B.id);
}

Node p[maxm*8],s[maxm*8];
Node s1[maxm*8],s2[maxm*8];

int res[maxn];
#define lowerbit(x) ((x)&(-x))
int C[maxn*2];
int sz;

void add(int x,int val)
{
    for(int i = x;i <= sz;i += lowerbit(i))
        C[i] += val;
}

int query(int x)
{
    int sum = 0;
    for(int i = x;i > 0;i -= lowerbit(i))
        sum += C[i];
    return sum;
}



void CDQ2(int L,int R)
{

    int m = (L+R)/2;
    if(L < R)
    {
        CDQ2(L,m);
        CDQ2(m+1,R);
    }
    int id1 = 0,id2 = 0;
    for(int i = L;i <= m;++i) if(s[i].opr == 0) s1[id1++] = s[i];
    for(int i = m+1;i <= R;++i) if(s[i].opr) s2[id2++] = s[i];
    sort(s1,s1+id1,cmpy);
    sort(s2,s2+id2,cmpy);

    int cur = 0;
    for(int i = 0;i < id2;++i)
    {
        while(cur < id1 && s1[cur].y <= s2[i].y)
        {
            add(s1[cur++].z,1);
        }
        res[s2[i].id] += s2[i].opr * query(s2[i].z);
    }
    for(int i = 0;i < cur;++i)
        add(s1[i].z,-1);
}



void CDQ1(int L,int R)
{
    int m = (L+R)/2;
    if(L < R)
    {
        CDQ1(L,m);
        CDQ1(m+1,R);
    };
    int id = 0;
    for(int i = L;i <= m;++i)  if(p[i].opr == 0) s[id++] = p[i];
    for(int i = m+1;i <= R;++i) if(p[i].opr) s[id++] = p[i];

    sort(s,s+id,cmpx);
    CDQ2(0,id-1);
}



int savez[maxn*2];

int hashz(int num)
{
    int L = 0,R = sz-1;
    while(L <= R)
    {
        int m = (L+R)/2;
        if(savez[m] >= num) R = m-1;
        else L = m+1;
    }
    return L+1;
}

int main()
{
   // freopen("./test.txt","r",stdin);
    int kase;
    scanf("%d",&kase);
    while(kase--)
    {
        memset(res,0,sizeof(res));
        memset(C,0,sizeof(C));

        int q;
        scanf("%d",&q);
        int cnt = 0;
        int m = 0;

        int qn = 0;
        for(int i = 0;i < q;++i)
        {
            int t;
            scanf("%d",&t);
            if(t == 1)
            {
                int x,y,z;
                scanf("%d %d %d",&x,&y,&z);
                p[m++] = Node(x,y,z,0,0);
                savez[cnt++] = z;
            }
            else
            {
                int x1,y1,z1,x2,y2,z2;
                scanf("%d %d %d",&x1,&y1,&z1);
                scanf("%d %d %d",&x2,&y2,&z2);

                p[m++] = Node(x2,y2,z2,1,qn);
                p[m++] = Node(x1-1,y2,z2,-1,qn);
                p[m++] = Node(x2,y1-1,z2,-1,qn);
                p[m++] = Node(x2,y2,z1-1,-1,qn);
                p[m++] = Node(x1-1,y1-1,z2,1,qn);
                p[m++] = Node(x1-1,y2,z1-1,1,qn);
                p[m++] = Node(x2,y1-1,z1-1,1,qn);
                p[m++] = Node(x1-1,y1-1,z1-1,-1,qn);
                savez[cnt++] = z2,
                savez[cnt++] = z1-1;
                qn++;
            }
        }

        sort(savez,savez+cnt);
        sz = unique(savez,savez+cnt)-savez;
        for(int i = 0;i < m;++i)
            p[i].z = hashz(p[i].z);


        CDQ1(0,m-1);

        for(int i = 0;i < qn;++i)
            printf("%d\n",res[i]);
    }
    return 0;
}
