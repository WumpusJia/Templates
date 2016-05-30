/*
dp(i,j) = min{ dp(i,k) + dp(k+1,j) + S }
显然S满足凸性.可是因为这是在树上，如果子节点很多的情况下
直接使用四边形不等式会退化到n^3的复杂度

如果此时固定一维i，方程变成dp[j] = min{dp[k] + w(k+1,j)}  ,w(k+1,j) = dp[k+1][j] + S
这是典型1D1D的方程，正好这里的w也满足凸性，所以可以使用决策单调性:
首先 对于固定的i来说,假设dp[x]最优决策点k为a,辣么由于凸性，dp[x+1]的最优决策点可以从a开始枚举
可是这样的复杂度还是n^3

反过来，我们考虑每个x对后面x+1,x+2,x+..的影响.
显然，最有决策点必然呈一段一段的形式，因此用一个栈来维护这些区间
对于当前x来说，找到x所在的区间，就可以得到x的最优决策点
然后用x的最有决策点更新栈：
    从栈顶往下，对每一个区间二分查找
    老决策点（区间左端点)和新决策点x 的分界点（第一个新决策点比老的优的x')
    然后更新区间(删除老区间或者缩小老区间)

    这里优化是，不维护区间的右断点，这样就不用修改区间右端点了


*/


void dfs(int u,int fa,int cur)
{
    seq[cur] = u;
    dp[cur][cur] = A[u];
    int head = 0;
    int tail = 0;
    Stack[tail++] = Node(cur,cur);
    LL sum = A[seq[cur]];
    for(int i = cur+1;i <= n;++i)
    {
        sum += A[seq[i]];
        while(head + 1 < tail && Stack[head+1].L <= i)
            head++;
        dp[cur][i] = cal(cur,Stack[head].pos,i) + sum;
        while(true)
        {
            int L = max(i+1,Stack[tail-1].L);
            int R = n;
            while( L <= R)
            {
                int mid = (L+R) >> 1;
                if(cal(cur,Stack[tail-1].pos,mid) < cal(cur,i,mid)) //老决策更优
                    L = mid+1;
                else
                    R = mid-1;
            }
            int p = L;
            if(p <= Stack[tail-1].L)
                tail--;
            else
            {
                Stack[tail++] = Node(p,i);
                break;
            }

        }
    }
    res[u] = dp[cur][n];
    for(int i = 0;i < G[u].size();++i)
    {
        int v = G[u][i];
        if(v != fa)
            dfs(v,u,cur-1);
    }

}
