//uncheck
#include<bits/stdc++.h>
using namespace std;

const int maxn = 100+10;

const double eps = 1e-10;
const double INF = 1e100;

double a[maxn][maxn];
double b[maxn];
double c[maxn];
double x[maxn];
double v;

bool has_col[maxn];
bool has_row[maxn];

int n,m; //n个变量,m个约束

int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return x > 0?1:-1;
}

void pivot(double c[],int l,int e)
{
    b[e] = b[l]/a[l][e];
    for(int j = 0;j <= m+n;++j)
        if(j != e && has_col[j]) a[e][j] = a[l][j]/a[l][e];
    a[e][l] = 1/a[l][e];

    for(int i = 0;i <= m+n;++i)
        if(i != l && has_row[i])
        {
            b[i] -= a[i][e]*b[e];
            for(int j = 0;j <= m+n;++j)
                if(j != e && has_col[j])
                    a[i][j] -= a[i][e]*a[e][j];
            a[i][l] = -a[i][e]*a[e][l];
        }

    v += (c[e]*b[e]);
    for(int j = 0;j <= m+n;++j)
        if(j != e && has_col[j]) c[j] -= c[e]*a[e][j];
    c[l] = -c[e]*a[e][l];

    has_row[l] = false;
    has_row[e] = true;
    has_col[l] = true;
    has_col[e] = false;
}


bool simplex(double c[])
{
    while(1)
    {
        int p = -1;
        for(int j = 0;j <= m+n;++j)
            if(has_col[j] && dcmp(c[j]) > 0)
            {
                p = j;
                break;
            }
        if(p == -1) break;

        double data = INF;
        int e = p,l;

        for(int i = 0;i <= m+n;++i)
        {
            if(has_row[i] && dcmp(a[i][e]) > 0)
            {
                double tmp = b[i]/a[i][e];
                if(data > tmp) //l,e已经遵循bland原则
                {
                    data = tmp;
                    l = i;
                }

            }
        }
        if(data == INF) return false; //无穷大的v
        else pivot(c,l,e);
    }


    for(int j = 0;j <= n+m;++j)
        if(has_col[j])
            x[j] = 0;
        else
            x[j] = b[j];

    return true;
}


bool init()
{
    double Min = INF;

    int l;

    for(int i = n;i <= m+n;++i)
    {
        if(Min > b[i])
        {
            Min = b[i];
            l = i;
        }
    }
    v = 0;
    memset(has_col,0,sizeof(has_col));
    memset(has_row,0,sizeof(has_row));
    for(int j = 1;j <= n;++j) has_col[j] = true;
    for(int i = 1;i <= m;++i) has_row[n+i] = true;

    if(dcmp(Min) < 0)
    {

        double tmpc[maxn];
        memset(tmpc,0,sizeof(tmpc));
        tmpc[0] = -1;

        for(int i = 1;i <= m;++i)
            a[n+i][0] = -1;

        pivot(tmpc,l,0);
        if(!simplex(tmpc)) return false;

        if(dcmp(v) != 0) return false;  //无法求解

        if(has_row[0])//not check
        {
            int pos = -1;
            for(int j = 0;j <= m+n;++j)
                if(has_col[j] && dcmp(a[0][j]) != 0)
                {
                    pos = j;
                    break;
                }
            assert(pos != -1);
            pivot(tmpc,0,pos);

        }

        has_row[0] = has_col[0] = false;

        for(int i = 0;i <= m+n;++i)
        {
            if(dcmp(c[i]) != 0 && has_row[i])
            {
                v += c[i]*b[i];
                for(int j = 0;j <= m+n;++j)
                    if(has_col[j])
                        c[j] -= a[i][j]*c[i];
                c[i] = 0;
            }
        }


    }
    return true;
}

/*
注意对于线性规划，先需要转换成标准形式:
A*x <= b
最大化 c*x
注意要保证x >= 0,否则见备注转化

假设有n个变量x和m个约束
那么初始下另 a[n+1]-a[n+m]的第i个数组第j列为系数A[i][j]
b[n+1] - b[n+m]的第i个数组为bi



备注:
1. 如果要最小化c*x,那么把c变成-c,就是最大化了
2. 如果是 >=的约束，那么左右乘上-1
3.如果是==的约束，那么拆成 >= 和 <=
4.如果有的x变量没有 >= 0的约束，那么拆成两个新变量即x用xp-xq
来替代,xp,xq>=0


对偶:
原问题都是 >= ,要最小化

对偶问题为   将b数组和c数组交换，并且将a数组转置(aT[1][2] = a[2][1])

*/

int main()
{
//    m = n = 3;
//    c[1] = 3; c[2] = 1; c[3] = 2;
//    b[4] = 30; b[5] = 24; b[6] = 36;
//    a[4][1] = 1; a[4][2] = 1; a[4][3] = 3;
//    a[5][1] = 2; a[5][2] = 2; a[5][3] = 5;
//    a[6][1] = 4; a[6][2] = 1; a[6][3] = 2;

    m = n = 2;
    c[1] = 2; c[2] = -1;
    b[3] = 2; b[4] = -4;;
    a[3][1] = 2; a[3][2] = -1;
    a[4][1] = 1; a[4][2] = -5;

    if(!init())
    {
        puts("No Answer");
        return 0;
    }

    if(!simplex(c))
    {
        puts("INF");
        return 0;
    }

    printf("%f\n",v);
}

