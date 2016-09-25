//树状数组
void add(int x,int v)
{
    for(int i = x;i < maxm;i += lowbit(i))
        sum[i] += v;
}

int query(int x)
{
    int res = 0;
    for(int i = x;i > 0;i -= lowbit(i))
        res += sum[i];
    return res;
}

//二维
int sum(int x,int y)
{
    int sum = 0;
    for(int i = x;i > 0;i -= lowbit(i))
        for(int j = y;j > 0;j -= lowbit(j))
            sum += C[i][j];
    return sum;
}
void add(int x,int y,int val)
{
    for(int i = x;i < maxn;i += lowbit(i))
        for(int j = y;j < maxn; j += lowbit(j))
            C[i][j] += val;
}

/*使用时先给a１－aｎ调用add,查询用sum*/


//RMQ
//一维 0-----n-1
void RMQ_init(const vector<int>& A)
{
    int n = A.size();
    for(int i = 0;i < n;++i)
        d[i][0] = A[i];
    for(int j = 1;(1 << j) <= n;++j)
        for(int i = 0;i+(1<<j)-1 < n;++i)
            d[i][j] = max(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}

int query(int L,int R)
{
    int k = 0;
    while((1<<(k+1)) <= R-L+1) k++;
    return max(d[L][k],d[R-(1<<k)+1][k]);
}

//二维 1---n
void RMQ_init()
{
    power[1] = 0;
    for(int i = 2;i < maxn;++i)
        power[i] = power[i/2] + 1;

    for(int r = 1;r <= R;++r)
        for(int c = 1;c <= C;++c)
            d[r][c][0][0] = A[r][c];

    for(int i = 0;i <= power[R];++i)
        for(int j = 0;j <= power[C];++j)
        {
            if(i == 0 && j == 0) continue;
            int limitR = R+1-(1<<i);
            int limitC = C+1-(1<<j);
            for(int r = 1;r <= limitR;++r)
                for(int c = 1;c <= limitC;++c)
                {
                    if(i == 0)
                        d[r][c][i][j] = max(d[r][c][i][j-1],
                            d[r][c+(1<<(j-1))][i][j-1]);
                    else
                        d[r][c][i][j] = max(d[r][c][i-1][j],
                            d[r+(1<<(i-1))][c][i-1][j]);
                }
        }
}


int query(int r1,int c1,int r2,int c2)
{
    int res = -1;
    int k1 = power[r2-r1+1],k2 = power[c2-c1+1];
    res = max(res,d[r1][c1][k1][k2]);
    res = max(res,d[r1][c2-(1<<k2)+1][k1][k2]);
    res = max(res,d[r2-(1<<k1)+1][c1][k1][k2]);
    res = max(res,d[r2-(1<<k1)+1][c2-(1<<k2)+1][k1][k2]);
    return res;
}



