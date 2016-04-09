LL lowbit(LL x)
{
    return x & (-x);
}

struct Bit
{
    LL p[maxn/64+5];
    int n;
    int len;
    Bit(int n = 0):n(n)
    {
        memset(p,0,sizeof(p));
        len = n/64 + (n%64 != 0);
    }

    void setbit(int o)
    {
        int id = o/64;
        int tid = o%64;
        p[id] |= (1ULL << tid);
        //printf("**** %d %d\n",id,tid);
    }

    void clearbit(int o)
    {
        int id = o/64;
        int tid = o%64;
        p[id] &= ~(1ULL << tid);
    }

    vector<int> getbit()
    {
        vector<int> V;
        for(int i = 0;i < len;++i)
        {

            LL num = p[i];

            while(num)
            {
                LL t = lowbit(num);
                num -= t;
                int x = (int)log2(t+0.5);

                V.push_back(x + i*64);
            }
        }
        return V;
    }


};

Bit andbit(Bit A,Bit B)
{
    Bit C(A.n);
    for(int i = 0;i < C.len;++i)
        C.p[i] = A.p[i] & B.p[i];
    return C;
}
