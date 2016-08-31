#include<stdio.h>
#include<string.h>
const int BASE = 10000;
const int maxn = 200;
int Cat[105][maxn];

void multiply(int A[],int k)
{
    int g = 0;
    for(int i = maxn-1;i >= 0;--i)
    {
        g += k*A[i];
        A[i] = g%BASE;
        g /= BASE;
    }
}

void divide(int A[],int k)
{
    int g = 0;
    for(int i = 0;i < maxn;++i)
    {
        g = g*BASE + A[i];
        A[i] = g/k;
        g %= k;
    }
}

void init()
{

    Cat[1][maxn-1] = 1;
    for(int i = 2;i <= 100;++i)
    {
        memcpy(Cat[i],Cat[i-1],maxn*sizeof(int));
        multiply(Cat[i],4*i-2);
        divide(Cat[i],i+1);
    }
}


void output(int A[])
{
    int i = 0;
    while(i < maxn && !A[i]) i++;
    printf("%d",A[i++]);
    while(i < maxn)
        printf("%04d",A[i++]);
    putchar('\n');
}

int main()
{
    init();
    int n;
    while(scanf("%d",&n) == 1 && n != -1)
        output(Cat[n]);
    return 0;
}



