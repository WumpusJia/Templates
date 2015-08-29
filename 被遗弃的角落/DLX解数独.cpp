#include<bits/stdc++.h>
using namespace std;
//解 16*16 数独
const int maxnode = 4096*4+100;
const int maxc = 1024+100;
const int maxr = 4096+100;

struct DLX
{
    int n,sz;   //列数，节点总数
    int S[maxc]; //各列节点数

    int row[maxnode],col[maxnode]; //各界点行列编号
    int L[maxnode],R[maxnode],U[maxnode],D[maxnode]; //十字链表

    int ansd,ans[maxr];

    void init(int n)
    {
        this-> n = n;

        for(int i = 0;i <= n;++i)
        {
            U[i] = i,D[i] = i;
            L[i] = i-1,R[i] = i+1;
        }
        L[0] = n;
        R[n] = 0;
        sz = n+1;
        memset(S,0,sizeof(S));
    }

    void addRow(int r,vector<int> columns)
    {
        int first = sz;
        for(int i = 0;i < columns.size();++i)
        {
            int c = columns[i];
            L[sz] = sz-1; R[sz] = sz+1; D[sz] = c; U[sz] = U[c];
            D[U[c]] = sz; U[c] = sz;
            row[sz] = r,col[sz] = c;
            S[c]++; sz++;
        }
        R[sz-1] = first; L[first] = sz-1;
    }

    #define FOR(i,A,s) for(int i = A[s]; i != s; i = A[i])

    void remove(int c) //删除第c列,和c列中覆盖到的行
    {
        L[R[c]] = L[c];
        R[L[c]] = R[c];
        FOR(i,D,c)
            FOR(j,R,i)
            {
                U[D[j]] = U[j];
                D[U[j]] = D[j];
                --S[col[j]];
            }
    }

    void restore(int c)
    {
        FOR(i,U,c)
            FOR(j,L,i)
            {
                ++S[col[j]];
                U[D[j]] = j;
                D[U[j]] = j;
            }
        L[R[c]] = c;
        R[L[c]] = c;
    }

    bool dfs(int d)
    {
        if(R[0] == 0)  //所有列都被删除
        {
            ansd = d;
            return true;
        }

        int c = R[0];
        FOR(i,R,0) if(S[i] < S[c]) c = i;

        remove(c);  //删除第c列
        FOR(i,D,c)
        {
            ans[d] = row[i];
            FOR(j,R,i) remove(col[j]);  //删除c列的行i所能覆盖的列j
            if(dfs(d+1)) return true;
            FOR(j,L,i) restore(col[j]);
        }
        restore(c);

        return false;
    }

    bool solve(vector<int>& v)
    {
        v.clear();
        if(!dfs(0)) return false;
        for(int i = 0;i < ansd;++i)
            v.push_back(ans[i]);
        return true;
    }
};

DLX solver;

const int SLOT = 0;
const int ROW = 1;
const int COL = 2;
const int SUB = 3;

int encode(int a,int b,int c)
{
    return a*256+b*16+c+1;
}

void decode(int code,int& a,int& b,int& c)
{
    code--;
    c = code%16; code /= 16;
    b = code%16; code /= 16;
    a = code;
}

char puzzle[16][20];

bool read()
{
    for(int i = 0;i < 16;++i)
        if(scanf("%s",puzzle[i]) != 1) return false;
    return true;
}

int main()
{
  //  freopen("./test.txt","r",stdin);
    int kase = 0;
    while(read())
    {
        if(kase++) putchar('\n');

        solver.init(1024);  //16*16*4列
        for(int r = 0;r < 16;++r)
            for(int c = 0;c < 16;++c)
                for(int v = 0;v < 16;++v)
                    if(puzzle[r][c] == '-' || puzzle[r][c] == 'A'+v)
                    {
                        vector<int> columns;
                        columns.push_back(encode(SLOT,r,c));
                        columns.push_back(encode(ROW,r,v));
                        columns.push_back(encode(COL,c,v));
                        columns.push_back(encode(SUB,(r/4)*4+c/4,v));
                        solver.addRow(encode(r,c,v),columns);
                    }
        vector<int> ans;
        solver.solve(ans);

        for(int i = 0;i < ans.size();++i)
        {
            int r,c,v;
            decode(ans[i],r,c,v);
            puzzle[r][c] = 'A'+v;
        }
        for(int i = 0;i < 16;++i)
            printf("%s\n",puzzle[i]);
    }
    return 0;
}

