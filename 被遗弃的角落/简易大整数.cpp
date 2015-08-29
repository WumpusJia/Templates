#include<cstdio>
#include<cstring>
#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
const int MAX_LEN = 200;
const int BASE = 10000;
const int WIDTH = 4;

struct BigInteger
{
    int A[MAX_LEN];

    BigInteger(const char* num)
    {
        memset(A,0,sizeof(A));
        int len = strlen(num);
        int time = (len-1)/WIDTH+1;
        for(int i = 0;i < time;++i)
        {
            int end = len - i*WIDTH;
            int start = max(end-WIDTH,0);
            int t = 0;
            for(int j = start;j < end;++j)
                t = t*10 + (num[j]-'0');
            A[MAX_LEN-i-1] = t;
        }
    }


    BigInteger(long long num = 0)
    {
        memset(A,0,sizeof(A));
        for(int i = MAX_LEN-1;i >= 0;--i)
        {
            A[i] = num % BASE;
            num /= BASE;
        }
    }

    BigInteger(const BigInteger& num)
    {
        memcpy(A,num.A,MAX_LEN*sizeof(int));
    }

    void print()
    {
        int i = 0;
        while(i < MAX_LEN && !A[i]) i++;
        printf("%d",A[i++]);
        while(i < MAX_LEN)
            printf("%04d",A[i++]);   //如果改变WIDTH,这里也需要更改
    }

};


bool operator > (const BigInteger& a,const BigInteger& b)
{
    for(int i = 0;i < MAX_LEN;++i)
        if(a.A[i] != b.A[i])
            return a.A[i] > b.A[i];
    return false;
}

bool operator == (const BigInteger& a,const BigInteger& b)
{
    for(int i = 0;i < MAX_LEN;++i)
        if(a.A[i] != b.A[i])
            return false;
    return true;
}

bool operator < (const BigInteger& a,const BigInteger& b)
{
    return !(a > b && a == b);
}

bool operator >= (const BigInteger& a,const BigInteger& b)
{
    return a > b || a == b;
}

BigInteger operator + (const BigInteger& a,const BigInteger& b)
{
    BigInteger res;
    int g = 0;
    for(int i = MAX_LEN-1;i >= 0;--i)
    {
        g += a.A[i] + b.A[i];
        res.A[i] = g % BASE;
        g /= BASE;
    }
    return res;
}

BigInteger operator - (const BigInteger& a,const BigInteger& b)
{
    BigInteger res = a;
    for(int i = MAX_LEN-1;i >= 0;--i)
    {
        res.A[i] -= b.A[i];
        if(res.A[i] < 0)
        {
            res.A[i-1]--;
            res.A[i] = BASE + res.A[i];
        }
    }
    return res;
}


BigInteger operator * (const BigInteger& a,const BigInteger& b)
{
    BigInteger res;
    for(int i = 0;i < MAX_LEN/2;++i)
        for(int j = 0;j < MAX_LEN/2;++j)
        {
            int t = a.A[MAX_LEN-1-i]*b.A[MAX_LEN-1-j];
            res.A[MAX_LEN-1-(i+j+1)] +=
             (res.A[MAX_LEN-1-(i+j)] + t)/BASE;
            res.A[MAX_LEN-1-(i+j)] =
                (res.A[MAX_LEN-1-(i+j)] + t)%BASE;
        }
    return res;
}

BigInteger operator >> (const BigInteger& a,int k)
{
    int p = (int)pow(2,k);
    int g = 0;
    BigInteger res = a;
    for(int i = 0;i < MAX_LEN;++i)
    {
        g = g*BASE+res.A[i];
        res.A[i] = g/p;
        g %= p;
    }
    return res;
}


BigInteger operator / (const BigInteger& a,const BigInteger& b)
{
    BigInteger L(1);
    BigInteger R(a);

    while(R>=L)
    {
        BigInteger mid = (L+R)>>1;
        if(b*mid > a ) R = mid-1;
        else
            L = mid+1;

    }
    return R;
}



int main()
{
    BigInteger A("100");
  //  BigInteger B("518516670000");
    BigInteger B = A/BigInteger(2);
    B.print();
}



