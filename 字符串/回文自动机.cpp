#include<bits/stdc++.h>
using namespace std;

const int SIGMA_SIZE = 26;
const int maxn = 1000+100;




struct Node
{
    Node* go[SIGMA_SIZE+5];
    Node* fail;
    int len;
    int cnt;
}pool[maxn << 1];
Node* cur;
Node *root,*last;

Node* newnode(int len)
{
    memset(cur->go,NULL,sizeof(cur->go));
    cur->len = len;
    cur->fail = NULL;
    cur->cnt = 0;
    return cur++;
}

void init()
{
    cur = pool;
    root = newnode(0);
    root->fail = newnode(-1);
    root->fail->fail = root->fail;
    last = root;
}

int idx(char c)
{
    return c-'a';
}

void extend(char s[],int i)
{

    int w = idx(s[i]);
    Node* p = last;
    while( s[i] != s[i-p->len-1])
    {
        p = p->fail;
    }
    if(p->go[w] == NULL)
    {

        Node* np = newnode(p->len+2);
        Node* q = p->fail;

        while(s[i] != s[i-q->len-1])
            q = q->fail;

        if(q->go[w] == NULL) np->fail = root;
        else np->fail = q->go[w];

        p->go[w] = np;
    }
    last = p->go[w];
    last->cnt++;


}


void build(char s[])//注意字符串从1开始
{
    s[0] = '*'; //不在字符集出现的字符
    int len = strlen(s+1);
    for(int i = 1;i <= len;++i)
    {

        extend(s,i);
    }

}

void count() //统计当前节点有多少回文字串
{
    for(int i = cur-pool-1;i >= 0;--i)
    {
        Node* p = &pool[i];
        if(p->fail != NULL)
            p->fail->cnt += p->cnt;
    }
}
