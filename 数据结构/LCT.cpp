#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

typedef unsigned int uint;
const int maxn = 202000;
const uint mod = 51061;

struct Node* null;
struct Node
{
    Node* ch[2];
    Node* fa;
    bool flip;
    uint mul,add,val,sum,s;
    bool dir() { return fa->ch[1] == this; }
    bool isroot() { return fa == null || (fa->ch[0] != this &&
                        fa->ch[1] != this); }
    void rev()
    {
        if(this == null) return;
        swap(ch[0],ch[1]);
        flip ^= 1;
    }

    void update(uint add_opr,uint mul_opr)
    {
        if(this == null) return;
        sum = (sum*mul_opr + s*add_opr)%mod;
        val = (val*mul_opr + add_opr)%mod;
        add = (add*mul_opr + add_opr)%mod;
        mul = (mul*mul_opr)%mod;
    }

    void pushup()
    {
        if(this == null) return;
        s = (ch[0]->s + ch[1]->s +1) %mod;
        sum = (ch[0]->sum + ch[1]->sum + val)%mod;
    }


    void pushdown()
    {
        if(this == null) return;
        if(flip)
        {
            ch[0]->rev();
            ch[1]->rev();
            flip = 0;
        }
        if(mul != 1 || add != 0)
        {
            ch[0]->update(add,mul);
            ch[1]->update(add,mul);
            add = 0,mul = 1;
        }
    }

    void signdown()
    {
        if(!isroot()) fa->signdown();
        pushdown();
    }

    void setc(Node* o,int d)
    {
        ch[d] = o;
        o->fa = this;
        pushup();
    }

    void rotate()
    {
        int d = dir();
        Node* temp = fa;
        temp->setc(ch[d^1],d);
        if(temp->isroot()) fa = temp->fa;
        else temp->fa->setc(this,temp->dir());
        setc(temp,d^1);
        fa->pushup();
    }

    void splay()
    {
        signdown();
        while(!isroot())
        {
            if(!fa->isroot())
            {
                if(fa->dir() == dir()) fa->rotate();
                else rotate();
            }
            rotate();
        }
    }

    void access()
    {
        Node* p = this,*q = null;
        while(p != null)
        {
            p->splay();
            p->setc(q,1);
            q = p;
            p = p->fa;
        }
        splay();
    }
};

int sz;
Node Stack[maxn*20];
Node* p[maxn];

void init()
{
    sz = 0;
    null = &Stack[sz++];
    null->flip = 0;
    null->mul = null->add = null->sum = null->val = 0;
    null->s = 0;
}

Node* newnode()
{
    Node* t = &Stack[sz++];
    t->ch[0] = t->ch[1] = t->fa = null;
    t->flip = 0;
    t->mul = 1; t->add = 0;
    t->s  = 1; t->sum = 0;
    t->val = 1;
    return t;
}

void makeroot(Node *o)
{
    o->access();
    o->rev();
}


void changeroot(Node* a,Node* b) //把a的根变成b
{
    a->splay();
    a->ch[0]->fa = a->fa;
    a->setc(null,0);
    a->fa = b;
}

Node* findroot(Node* o)
{
    Node* p = o;
    while(o->fa != null)
        o = o->fa;
    return o;
}

void link(Node* a,Node* b) //加入a到父亲b的边
{
    makeroot(a);
    a->fa = b;
}

void cut(Node* a,Node* b) //砍去a到父亲b的边
{
    makeroot(a);
    b->access();
    b->ch[0] = b->ch[0]->fa = null;
    b->pushup();
}





int n,q;

int main()
{
  //  freopen("./test.txt","r",stdin);
    while(scanf("%d %d",&n,&q) == 2)
    {
        init();
        for(int i = 1;i <= n;++i)
            p[i] = newnode();
        for(int i = 0;i < n-1;++i)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            link(p[a],p[b]);
        }
        char buf[5];
        while(q--)
        {
            scanf("%s",buf);
            if(buf[0] == '+')
            {
                int a,b,c;
                scanf("%d %d %d",&a,&b,&c);
                makeroot(p[b]);
                p[a]->access();
                p[a]->splay();
                p[a]->update(c,1);
            }
            else if(buf[0] == '-')
            {
                int a,b,c,d;
                scanf("%d %d %d %d",&a,&b,&c,&d);
                cut(p[a],p[b]);
                link(p[c],p[d]);
            }
            else if(buf[0] == '*')
            {
                int a,b,c;
                scanf("%d %d %d",&a,&b,&c);
                makeroot(p[b]);
                p[a]->access();
                p[a]->splay();
                p[a]->update(0,c);
            }
            else
            {
                int a,b;
                scanf("%d %d",&a,&b);
                makeroot(p[b]);
                p[a]->access();
                p[a]->splay();
                printf("%u\n",p[a]->sum);
            }
        }
    }

    return 0;
}


////////////维护生成树////////////////
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000+10;
const int maxm = 2000000+100;
typedef long long LL;
const int INF = 0x3f3f3f3f;

struct Node* null;
struct Node
{
    Node* ch[2];
    Node* fa;
    bool flip;
    int val,id;
    Node* mx;
    bool dir() { return fa->ch[1] == this; }
    bool isroot() { return fa == null || (fa->ch[0] != this &&
                        fa->ch[1] != this); }
    void rev()
    {
        if(this == null) return;
        swap(ch[0],ch[1]);
        flip ^= 1;
    }

    void pushup()
    {
        if(this == null) return;
        mx = this;
        if(ch[0]->mx->val < mx->val) mx = ch[0]->mx;
        if(ch[1]->mx->val < mx->val) mx = ch[1]->mx;
    }


    void pushdown()
    {
        if(this == null) return;
        if(flip)
        {
            ch[0]->rev();
            ch[1]->rev();
            flip = 0;
        }

    }

    void signdown()
    {
        if(!isroot()) fa->signdown();
        pushdown();
    }

    void setc(Node* o,int d)
    {
        ch[d] = o;
        o->fa = this;
        pushup();
    }

    void rotate()
    {
        int d = dir();
        Node* temp = fa;
        temp->setc(ch[d^1],d);
        if(temp->isroot()) fa = temp->fa;
        else temp->fa->setc(this,temp->dir());
        setc(temp,d^1);
        fa->pushup();
    }

    void splay()
    {
        signdown();
        while(!isroot())
        {
            if(!fa->isroot())
            {
                if(fa->dir() == dir()) fa->rotate();
                else rotate();
            }
            rotate();
        }
    }

    void access()
    {
        Node* p = this,*q = null;
        while(p != null)
        {
            p->splay();
            p->setc(q,1);
            q = p;
            p = p->fa;
        }
        splay();
    }
};

int sz;
Node Stack[maxn+maxm];
Node* p[maxn+maxm];

void init()
{
    sz = 0;
    null = &Stack[sz++];
    null->flip = 0;
    null->val = INF;
    null->mx = null;
    null->id = 0;
}

Node* newnode(int val,int id)
{
    Node* t = &Stack[sz++];
    t->ch[0] = t->ch[1] = t->fa = null;
    t->flip = 0;
    t->val = val;
    t->id = id;
    t->mx = t;
    return t;
}

void makeroot(Node *o)
{
    o->access();
    o->rev();
}


void changeroot(Node* a,Node* b) //把a的根变成b
{
    a->splay();
    a->ch[0]->fa = a->fa;
    a->setc(null,0);
    a->fa = b;
}

Node* findroot(Node* o)
{
    Node* p = o;
    while(o->fa != null)
        o = o->fa;
    return o;
}

void link(Node* a,Node* b) //加入a到父亲b的边
{
    makeroot(a);
    a->fa = b;
}

void cut(Node* a,Node* b) //砍去a到父亲b的边
{
    makeroot(a);
    b->access();
    b->ch[0] = b->ch[0]->fa = null;
    b->pushup();
}

Node* getmin(Node* a,Node* b)
{
    makeroot(b);
    a->access();
    a->splay();
    return a->mx;
}
//////////////////////////////

vector<int> G[maxn];

LL ans;
LL dp[maxn];
int U[maxm],V[maxm];
int idx;


void addEdge(int u,int v,int w)
{
    Node* t = getmin(p[u],p[v]);
    if(t->val >= w) return;

    p[idx] = newnode(w,idx);
    U[idx] = u;
    V[idx] = v;

    cut(t,p[U[t->id]]);
    cut(t,p[V[t->id]]);
    link(p[idx],p[U[idx]]);
    link(p[idx],p[V[idx]]);
    ans += w-t->val;
    idx++;
}


int main()
{
    int limit = 100000;
    for(int i = 2;i <= limit;++i)
        G[i].push_back(1);
    for(int i = 2;i <= limit;++i)
    {
        for(int j = i+i;j <= limit;j += i)
            G[j].push_back(i);
    }
    init();

    for(int i = 1;i <= limit;++i)
        p[i] = newnode(INF,0);

    ans = 0;
    idx = limit+1;
    for(int i = 2;i <= limit;++i)
    {
        int sz = G[i].size();
        U[idx] = G[i][sz-1];
        V[idx] = i;
        p[idx] = newnode(G[i][sz-1],idx);
        link(p[idx],p[U[idx]]);
        link(p[idx],p[V[idx]]);
        ans += G[i][sz-1];
        idx++;
        for(int j = sz-2;j >= 0;--j)
            addEdge(i,G[i][j],G[i][j]);
        dp[i] = ans;
    }

   int n;
   while(scanf("%d",&n) == 1)
    printf("%lld\n",dp[n]);

    return 0;



}






