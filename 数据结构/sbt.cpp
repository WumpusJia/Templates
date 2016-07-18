///////////内存池版/////////////
const int maxn = 200000+10;
const int INF = 0x3f3f3f3f;

struct Node
{
    Node* ch[2];
    int v,s,c;
    int cmp(int x)
    {
        if(x == v) return -1;
        return x < v?0:1;
    }
    void maintain()
    {
        s = c;
        s += ch[0]->s;
        s += ch[1]->s;
    }
};
int sz = 0;
Node* null,Stack[maxn*20];

void init()
{

    null = &Stack[sz++];
    null->v = null->s = null->c = 0;
}

Node* newnode(int v)
{
    Node* t = &Stack[sz++];
    t->ch[0] = t->ch[1] = null;
    t->v = v; t->s = 1; t->c = 1;
    return t;
}

void rotate(Node*& o,int d)
{
    Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k;
}

void balance(Node*& o,int d)
{
    if(o->ch[d] == null) return;
    if(o->ch[d]->ch[d]->s > o->ch[d^1]->s)
        rotate(o,d^1);
    else if(o->ch[d]->ch[d^1]->s > o->ch[d^1]->s)
    {
        rotate(o->ch[d],d); rotate(o,d^1);
    }
    else return;
    balance(o,0); balance(o,1);
}

void insert(Node*& o,int x)
{
    if(o == null) o = newnode(x);
    else
    {
        int d = o->cmp(x);
        o->s++;
        if(d == -1) { o->c++; return; }
        insert(o->ch[d],x);
        o->maintain();
        balance(o,d);
    }
}

void remove(Node*& o,int x)
{
    if(o == null) return;
    int d = o->cmp(x);
    o->s--;
    if(d == -1)
    {
        Node* u = o;
        if(o->c > 1) o->c--;
        else if(o->ch[0] != null && o->ch[1] != null)
        {
            Node* ret = o->ch[1];
            while(ret->ch[0] != null) ret = ret->ch[0];
            remove(o->ch[1],o->v = ret->v);
        }
        else
        {
            if(o->ch[0] == null) o = o->ch[1];
            else o = o->ch[0];
        }
    }
    else remove(o->ch[d],x);
    if(o != null) o->maintain();
}


int find(Node* o,int x)
{
    if(o == null) return 0;
    int d = o->cmp(x);
    if(d == -1)
    {
        int t = o->c + o->ch[0]->s;
        return t;
    }
    else if(d == 0) return find(o->ch[0],x);
    else
    {
        int t = find(o->ch[1],x);
        t += o->c + o->ch[0]->s;
        return t;
    }
}

int main()
{
    while(....)
    { //！！！！！！！！！！！！！！！！初始化
        sz = 0;init();
        fill(p,p+n,null);
        ....
    }
}

/////////////非内存池版/////////////////////
const int maxn = 200000+10;
const int INF = 0x3f3f3f3f;

struct Node
{
    Node* ch[2];
    int v,s,c;
    Node(int x = 0) { v = x; s = 1; c = 1; }
    int cmp(int x)
    {
        if(x == v) return -1;
        return x < v?0:1;
    }
    void maintain()
    {
        s = c;
        s += ch[0]->s;
        s += ch[1]->s;
    }
};
Node* null;

void init()
{
    null = new Node(0);
    null->c = 0;
    null->v = null->s = null->c = 0;
}

Node* newnode(int v)
{
    Node* t = new Node(v);
    t->ch[0] = t->ch[1] = null;
    return t;
}

void rotate(Node*& o,int d)
{
    Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k;
}

void balance(Node*& o,int d)
{
    if(o->ch[d] == null) return;
    if(o->ch[d]->ch[d]->s > o->ch[d^1]->s)
        rotate(o,d^1);
    else if(o->ch[d]->ch[d^1]->s > o->ch[d^1]->s)
    {
        rotate(o->ch[d],d); rotate(o,d^1);
    }
    else return;
    balance(o,0); balance(o,1);
}

void insert(Node*& o,int x)
{

    if(o == null) o = newnode(x);
    else
    {
        int d = o->cmp(x);
        o->s++;
        if(d == -1) { o->c++; return; }
        insert(o->ch[d],x);
        o->maintain();
        balance(o,d);
    }
}

void remove(Node*& o,int x)
{
    if(o == null) return;
    int d = o->cmp(x);
    o->s--;
    if(d == -1)
    {
        Node* u = o;
        if(o->c > 1) o->c--;
        else if(o->ch[0] != null && o->ch[1] != null)
        {
            Node* ret = o->ch[1];
            while(ret->ch[0] != null) ret = ret->ch[0];
            remove(o->ch[1],o->v = ret->v);
        }
        else
        {
            if(o->ch[0] == null) o = o->ch[1];
            else o = o->ch[0];
            delete u;
        }
    }
    else remove(o->ch[d],x);
    if(o != null) o->maintain();
}

int main()
{
    init();
    while(...)
    {
        //对指针执行removetree!!!!
    }
}

