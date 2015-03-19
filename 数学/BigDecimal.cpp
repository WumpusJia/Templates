#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#define INF 1E9
using namespace std;
struct BigNum
{
    int len;
    int num[10000];
    int point;
    BigNum()
    {
        len=1;
        point=0;
        memset(num,0,sizeof(num));
    }
};
bool input(BigNum &a)//输入
{
    string s;
    if(cin>>s)
    {
        memset(a.num,0,sizeof(a.num));
        int t=0,i;
        a.len=s.size();
        a.point=0;
        for(i=s.size()-1;i>=0;i--)
        {
            if(s[i]=='.'){a.len--;a.point=t;continue;}
            a.num[t++]=s[i]-'0';
        }
        return 1;
    }
    else return 0;
}
void output(BigNum &a)//输出
{
    int i,j=0,flag;
    for(i=0;i<a.point&&a.num[i]==0;i++);
    flag=i;
    if(a.point==a.len)
    {
        if(flag==a.point){cout<<"0"<<endl;return;}
        else cout<<".";
    }
   // cout<<a.point<<" "<<flag<<endl;
    for(i=a.len-1;i>=0;i--)
    {
        cout<<a.num[i];
        if(i==flag)break;
        if(i==a.point)cout<<".";
    }
    cout<<endl;
}
BigNum Mul(BigNum &a, BigNum &b)
{
    int i, j, len = 0;
    BigNum c;
    for(i = 0; i < a.len; i++)
        for(j = 0; j < b.len; j++)
        {
            c.num[i+j] += (a.num[i]*b.num[j]);
            if(c.num[i+j] >= 10)
            {
                c.num[i+j+1] += (int)c.num[i+j]/10;
                c.num[i+j] %= 10;
            }
        }
    c.point=a.point+b.point;
    len = a.len+b.len;
    while(c.num[len-1] == 0 && len > 1&&len>c.point) len--;
    if(c.num[len]) len++;
    c.len = len;
    return c;
}
BigNum a;
int b;
int main()
{
    while(input(a)&&~scanf("%d",&b))
    {
        BigNum ans;
        if(b==0){cout<<1<<endl;continue;}
        ans.num[0]=1;
        while(b--)
        {
            ans=Mul(ans,a);
        }
        output(ans);
    }
}
