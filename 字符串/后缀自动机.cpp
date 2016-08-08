
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int SIGMA_SIZE = 26;
const int maxn = 20000+100;


struct Node
{
    Node* go[SIGMA_SIZE+5];
    Node* fa;
    int Max; //当前状态的字符串可以达到的最大长度

    int getMin() //最小长度
    {
        if(fa == NULL) return 0;
        else return fa->Max + 1;
    }

}pool[maxn << 1];
Node* cur;
Node *root,*last;


Node* newnode(int Max)
{
    memset(cur->go,NULL,sizeof(cur->go));
    cur->Max = Max;
    cur->fa = NULL;
    return cur++;
}

void init()
{
    cur = pool;
    root = newnode(0);
    last = root;
}

void extend(int w)
{
    Node* p = last;
    Node* np = newnode(p->Max + 1);

    while(p != NULL && p->go[w] == NULL)
        p->go[w] = np,p = p->fa;

    if(p == NULL)
        np->fa = root;
    else
    {
        Node* q = p->go[w];
        if(p->Max + 1 == q->Max)
            np->fa = q;
        else
        {
            Node* nq = newnode(p->Max+1);
            memcpy(nq->go,q->go,sizeof(q->go));
            nq->fa = q->fa;
            q->fa = nq;
            np->fa = nq;
            while(p != NULL && p->go[w] == q)
                p->go[w] = nq,p = p->fa;
        }
    }
    last = np;
}

int idx(char c)
{
    return c-'a';
}

void build(char s[])
{
    int len = strlen(s);
    for(int i = 0;i < len;++i)
        extend(idx(s[i]));
}



/*......  add function .....*/

//按parent树从子节点向上，进行topo排序
int topocnt[maxn];
int seq[maxn];

void toposort(int n)
{
    memset(topocnt,0,sizeof(topocnt));
    for(int i = cur-pool-1;i >= 0;--i)
        topocnt[pool[i].Max]++;
    for(int i = 1;i <= n;++i)
        topocnt[i] += topocnt[i-1];

    for(int i = cur-pool-1;i >= 0;--i)
        seq[--topocnt[pool[i].Max]] = i;
}

//统计每个节点的right个数
Node * t = root;
for(int i = 0;i < len;++i)//！！对字符串上的节点先置1
{
    int w = idx(s[i]);
    t = t->go[w];
    t->cnt++;
}

for(int i = cur-pool-1;i >= 0;--i)
{
    Node* p = &pool[seq[i]];
    if(p->fa != NULL)
        p->fa->cnt += p->cnt;
}



//求B的每个后缀和A的最长匹配长度
// 对A,B都reverse，然后对rev(A)建立sam
// 可以对rev(B)进行递推，得到以rev(B)[i]结尾的字串和A的最大匹配长度
//最后对这个数组进行reverse,就可以得到所求

reverse(A);
reverse(B);

int f[maxn];

init();
build(A);
memset(f,0,sizeof(f));
Node* p = root;
int len = 0;
for(int i = 0;i < strlen(B);++i)
{
    int w = idx(B[i]);
    if(p->go[w] != NULL)
    {
        len++;
        p = p->go[w];
    }
    else
    {
        while(p != NULL && p->go[w] == NULL) p = p->fa;
        if(p == NULL) p = root,len = 0;
        else len = p->Max + 1, p = p->go[w];
    }
    f[i] = max(f[i],len);
}
reverse(f,f+strlen(B));
