struct Node
{
    Node* ch[2];
    int v,s,c;
    Node(int v):v(v) { ch[0] = ch[1] = NULL; s = 0;c = 1; }
    int cmp(int x) const
    {
        if(x == v) return -1;
        return x < v?0:1;
    }

    void maintain()
    {
        s = c;
        if(ch[0] != NULL) s += ch[0]->s;
        if(ch[1] != NULL) s += ch[1]->s;
    }
};

void rotate(Node*& o,int d)
{
    Node*k = o->ch[d^1]; o->ch[d^1] = k->ch[d];k->ch[d] = o;
    o->maintain(); k->maintain(); o = k;
}

void insert(Node* &o,int x)
{
    if(o == NULL) o = new Node(x);
    else
    {
      //  int d = (x < o->v?0:1);
        int d = o->cmp(x);
        if(d == -1) o->c++;
        else insert(o->ch[d],x);
    }
    o->maintain();
}

void splay(Node*& o,int x)
{
    int d = o->cmp(x);
    if(d != -1 && o->ch[d] != NULL)
    {
        Node*p = o->ch[d];
        int d2 = p->cmp(x);
        if(d2 != -1 && p->ch[d2] != NULL)
        {
            splay(p->ch[d2],x);
            if(d == d2) rotate(o,d^1);
            else rotate(o->ch[d],d);
        }
        rotate(o,d^1);
    }
}

void removetree(Node*& x)
{
    if(x->ch[0] != NULL) removetree(x->ch[0]);
    if(x->ch[1] != NULL) removetree(x->ch[1]);
    delete x;
    x = NULL;
}

int kth(Node* o,int k)
{
    if(o == NULL || k <= 0 || k > o->s) return INF;
    int s = (o->ch[1] == NULL?0:o->ch[1]->s);
    if(k > s && k <= s+o->c) return o->v;
    else if(k <= s) return kth(o->ch[1],k);
    else return kth(o->ch[0],k-s-o->c);
}
