typedef LL Matrix[maxn][maxn];

void gauss_jordan(Matrix A,int n)
{
    for(int i = 0;i < n;++i)
    {
        int r = i;
        for(int j = i+1;j < n;++j)
            if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
        if(fabs(A[r][i]) < eps) continue;
        if(r != i) for(int j = 0;j <= n;++j) swap(A[r][j],A[i][j]);

        for(int k = 0;k < n;++k)
            if(k != i)
                for(int j = n;j >= i;--j)
                    A[k][j] -= A[k][i]/A[i][i] * A[i][j];
    }
}

//m行n列矩阵  typedef double Matrix
int gauss_jordan(Matrix A,int n,int m)
{
    for(int c = 0,k = 0;c < n;++c)
    {
        int r = k;
        for(int i = k+1;i < m;++i)
            if(fabs(A[i][c]) > fabs(A[r][c]) ) r = i;
        if(fabs(A[r][c]) < eps) continue;
        if(r != k) for(int j = 0;j <= n;++j) swap(A[r][j],A[k][j]);

        for(int i = 0;i < m;++i)
            if(i != k)
                for(int j = n;j >= c;--j)
                    A[i][j] -= A[i][c]/A[k][c]*A[k][j];
        k++;
    }
}

void gauss_jordan(Matrix A,int n)
{
    for(int c = 0,k = 0;c < n;++c)
    {
        if(A[k][c] == 0)
            for(int i = k+1;i < n;++i)
                if(A[i][c])
                    for(int j = c;j <= n;++j)
                        swap(A[i][j],A[k][j]);
        if(A[k][c] == 0) continue;

        for(int i = 0;i < n;++i)
            if(i != k)
                for(int j = n;j >= c;--j)
                {
                  //  A[i][j] = A[i][j]*A[k][c]-A[k][j]*A[i][c];
                    A[i][j] -= (A[i][c]*inv(A[k][c])%mod)*A[k][j];
                    A[i][j] = (A[i][j]%mod+mod)%mod;


                }
        k++;

    }


    for(int i = 0;i < n;++i)
    {
        A[i][n] = A[i][n] * inv(A[i][i])%mod;
        A[i][i] = 1;
    }


}



int sz; //矩阵大小
LL mod; //模
void matrix_mul(Matrix A,Matrix B,Matrix res)
{
    Matrix C;
    memset(C,0,sizeof(C));
    for(int i = 0;i < sz;++i)
        for(int j = 0;j < sz;++j)
            for(int k = 0;k < sz;++k)
                C[i][j] = (C[i][j]  + A[i][k] * B[k][j]) % mod;
    memcpy(res,C,sizeof(C));
}

void matrix_pow(Matrix A,LL n,Matrix res)
{
    Matrix a,r;
    memcpy(a,A,sizeof(a));
    memset(r,0,sizeof(r));
    for(int i = 0;i < sz;++i) r[i][i] = 1;
    while(n)
    {
        if(n&1) matrix_mul(r,a,r);
        n >>= 1;
        matrix_mul(a,a,a);
    }
    memcpy(res,r,sizeof(r));
}


//求逆矩阵．．．．．will done

//计算a^1+a^2+a^3...a^n; 注意这里Matrix需要写成结构体形式
Matrix sum(Matrix a,LL n)
{
    if(n == 1)
        return a;
    if(n&1)
        return (a^n) + sum(a,n-1);
    else
        return sum(a,n/2) * ((a^(n/2))+1);
}

