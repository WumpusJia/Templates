struct Node
{
    Node* ch[2];
    int r;
    int v;
    int s;
    Node(int v):v(v) { ch[0] = ch[1] = NULL; r = rand();s = 1; }
    int cmp(int x) const
    {
        if(x == v) return -1;
        return x < v?0:1;
    }
    void maintain()
    {
        s = 1;
        if(ch[0] != NULL) s += ch[0]->s;
        if(ch[1] != NULL) s += ch[1]->s;
    }

};

void rotate(Node* &o,int d)
{
    Node* k = o->ch[d^1]; o->ch[d^1] = k->ch[d]; k->ch[d] = o;
    o->maintain(); k->maintain(); o = k;
}

void insert(Node* &o,int x)
{
    if(o == NULL) o = new Node(x);
    else
    {
        int d = (x < o->v ?0:1); //不能用cmp,因为可能会有相同节点
        insert(o->ch[d],x);
        if(o->ch[d]->r > o->r ) rotate(o,d^1);
    }
    o->maintain();
}

void remove(Node* &o,int x)
{
    int d = o->cmp(x);
    if(d == -1)
    {
        Node* u= o;
        if(o->ch[0] != NULL && o->ch[1] != NULL)
        {
            int d2 = (o->ch[0]->r > o->ch[1]->r? 1:0);
            rotate(o,d2); remove(o->ch[d2],x);
        }
        else
        {
            if(o->ch[0] == NULL) o = o->ch[1];
            else o = o->ch[0];
            delete u;
        }
    }
    else
        remove(o->ch[d],x);
    if(o != NULL) o->maintain();
}

void splay(Node*& o,int x)
{
    int d = o->cmp(x);
    if(d != -1 && o->ch[d] != NULL)
    {
        Node*p = o->ch[d];
        int d2 =p->cmp(x);
        if(d2 != -1 && p->ch[d2] != NULL)
        {

            splay(p->ch[d2],x);
            if(d == d2) rotate(o,d^1);
            else
                rotate(o->ch[d],d);

        }
        rotate(o,d^1);
    }
}


int kth(Node* o,int k) //第k大
{
    if(o == NULL || k <= 0 || k > o->s) return 0; //不存在
    int s = (o->ch[1] == NULL? 0:o->ch[1]->s);
    if(k == s+1) return o->v;
    else if(k <= s) return kth(o->ch[1],k);
    else return kth(o->ch[0],k-s-1);
}

int find(Node* o,int x)  //获得x在区间中的名次 (第几大)
{
    if(o == NULL) return 0; //不存在
    int d = o->cmp(x);
    if(d == -1)
    {
        int t = 1;
        if(o->ch[1] != NULL)
            t += o->ch[1]->s;
        return t;
    }
    else if(d == 1) return find(o->ch[1],x);
    else
    {
        int t = find(o->ch[0],x);
        if(t == 0) return t;
        t += 1;
        if(o->ch[1] != NULL)
            t += o->ch[1]->s;
        return t;
    }
}


int count(Node* o,int x) // <= x的个数 (x不一定需要存在)
{
    if(o == NULL) return 0;
    if(x < o->v) return count(o->ch[0],x);
    else
    {
        int res = 1;
        if(o->ch[0] != NULL)
            res += o->ch[0]->s;
        return res + count(o->ch[1],x);
    }
}



void mergeto(Node*& src,Node*& dest)
{
    if(src->ch[0] != NULL) mergeto(src->ch[0],dest);
    if(src->ch[1] != NULL) mergeto(src->ch[1],dest);
    insert(dest,src->v);
    delete src;
    src = NULL;
}

void removetree(Node*& x)
{
    if(x->ch[0] != NULL) removetree(x->ch[0]);
    if(x->ch[1] != NULL) removetree(x->ch[1]);
    delete x;
    x = NULL;
}


