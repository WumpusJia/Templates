#include<bits/stdc++.h>
using namespace std;

const int maxn = 20;
int seq[maxn];
int Xor[maxn][maxn];
int fa[maxn];

int n;

//代码未检验！！！！！！！！！！！！！

vector<pair<int,int> > V;

bool solve(int f,int idx,int mask)
{
    if(f == n)
    {

        if(judge())
        {
            for(int i = 1;i < n;++i)
            {
                int u = seq[i];
                int f = seq[fa[i]];
                V.push_back(make_pair(f,u));
            }
            return true;

        }
        return false;
    }
    else if(f < idx)
    {
        int t = idx;
        for(int i = mask;;i = (i-1)&mask)
        {
            for(int j = 1;j < n;++j)
                if(i & (1 << j))
                {
                    seq[idx] = j+1;
                    fa[idx++] = f;
                }

            if(solve(f+1,idx,mask ^ i)) return true;

            idx = t;
            if(i == 0) break;
        }
    }

    return false;
}



int main()
{

    scanf("%d",&n);
    seq[0] = 1;
    bool has = solve(0,1,(1 << n)-2);

    for(int i = 0;i < V.size();++i)
        printf("%d  %d\n",V[i].first,V[i].second);

}
