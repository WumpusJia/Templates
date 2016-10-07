//KMP
//失配函数(从1--->n): 如果P[j] 能匹配到P[i],那么f[j] = i
void getFail(char *P,int f[])
{
    int m = strlen(P);
    f[0] = 0,f[1] = 0;
    for(int i = 1;i < m;++i)
    {
        int j = f[i];
        while(j && P[i] != P[j]) j = f[j];
        f[i+1] = P[i] == P[j] ?j+1:0;
    }
}

void find(char* T,char *P,int f[])
{
    int n = strlen(T),m = strlen(P);
    getFail(P,f);

    //千万注意!!  如果P是整数串，P[m]要为一个不可能出现的数
    int j = 0;
    for(int i = 0;i < n;++i)
    {
        while(j && P[j] != T[i]) j = f[j];
        if(P[j] == T[i]) j++;
        if(j == m) printf("%d\n",i-m+1);
    }
}


//获得字符串循环节所有长度
    for(int i = 1;i <= m;++i)
    {
        int now = i;
        while(now)
        {
            now = f[now];
            if(i % (i-now) == 0)
            {
                int t = i/(i-now);
                res[t] = max(res[t],i);
            }
        }

    }

//判断每个前缀是否有循环节(求后缀只要reverse原串)
void check(bool good[],int f[],int n)
{
    good[1] = 1;
    for(int i = 2;i <= n;++i)
    {
        if(f[i] > 0 && i % (i-f[i]) == 0)
        {
            int t = i/(i-f[i]);
            if(t >= 2)
                good[i] = 0;
            else
                good[i] = 1;
        }
        else
            good[i] = 1;
    }

}


//EKMP
int Next[maxn];
int ret[maxn]; //S的每个后缀与T的前缀的最长匹配××长度××

void EKMP(char T[],char S[])
{
    int lenT = strlen(T);
    int lenS = strlen(S);

    int j = 0;
    while(1 + j < lenT && T[j] == T[1+j]) ++j;
    Next[0] = lenT;
    Next[1] = j;
    int k = 1;
    for(int i = 2;i < lenT;++i)
    {
        int Len = k+Next[k],L = Next[i-k];
        if(L < Len-i)
            Next[i] = L;
        else
        {
            j = max(0,Len-i);
            while(i+j < lenT && T[j] == T[i+j]) ++j;
            Next[i] = j;
            k = i;
        }
    }

    j = 0;
    while(j < lenS && j < lenT && T[j] == S[j]) j++;
    ret[0] = j;
    k = 0;
    for(int i = 1;i < lenS;++i)
    {
        int Len = k+ret[k],L = Next[i-k];
        if(L < Len-i)
            ret[i] = L;
        else
        {

            j = max(0,Len-i);
            while(j < lenT && i+j < lenS && T[j] == S[i+j]) ++j;
            ret[i] = j;
            k = i;
        }
    }
}


