typedef LL Matrix[maxn][maxn];

//void gauss_jordan(Matrix A,int n) //
//{
//    for(int i = 0;i < n;++i)
//    {
//        int r = i;
//        for(int j = i+1;j < n;++j)
//            if(fabs(A[j][i]) > fabs(A[r][i])) r = j;
//        if(fabs(A[r][i]) < eps) continue;
//        if(r != i) for(int j = 0;j <= n;++j) swap(A[r][j],A[i][j]);
//
//        for(int k = 0;k < n;++k)
//            if(k != i)
//                for(int j = n;j >= i;--j)
//                    A[k][j] -= A[k][i]/A[i][i] * A[i][j];
//    }
//}

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

LL x[maxn]; //解的结果
//尤其注意如果mod不是素数，可能会导致无解
//解同余矩阵(这里模7)  返回值-1(无解),0(多解),1(仅有1解)
//typedef LL
int gauss_jordan(Matrix A,int n,int m)
{
    for(int c = 0,k = 0;c < n;++c)
    {
        if(A[k][c] == 0)
            for(int i = k+1;i < m;++i)
                if(A[i][c])
                    for(int j = c;j <= n;++j)
                        swap(A[i][j],A[k][j]);
        for(int i = k+1;i < m;++i)
            if(i != k)
                for(int j = n;j >= c;--j)
                {
                    A[i][j] = A[i][j]*A[k][c]-A[k][j]*A[i][c];
                    A[i][j] = (A[i][j]%mod+mod)%mod;
                }
                 //   A[i][j] -= A[i][c]/A[k][c]*A[k][j];
        k++;
    }

    bool flag = false;
    for(int i = 0;i < m;++i)
    {
        int j;
        for(j = 0;j < n;++j)  //attention!!
            if(A[i][j] != 0) break;
        if(j == n)
        {
            if(A[i][n] != 0) return -1;
            else if(i < n) flag = true;
        }
    }

    if(flag || m < n) return 0;

   // memset(x,0,sizeof(x));
    for(int i = n-1;i >= 0;--i)
    {
        LL t = 0;
        for(int j = i+1;j < n;++j)
            t = ( t+x[j]*A[i][j] )%mod;
        int j;
        for(j = 3;j <= 9;++j) //解的范围在[3,9]
        {
            if( (t + j*A[i][i])%7 == A[i][n])
            {
                x[i] = j;
                break;
            }
        }
        if(j > 9) return -1;
    }

    return 1;
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

