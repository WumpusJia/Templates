typedef unsigned int uint;

int bitCount(uint x)  //统计x中1的个数　O(1)
{
    x-= ((x & 0xAAAAAAAAu) >> 1);
    x = ((x & 0xCCCCCCCCu) >> 2) + (x & 0x33333333u);
    x = ((x >> 4) + x) & 0x0F0F0F0Fu;
    x = (x * 0x01010101u) >> 24;
    return x;
}

//查询0-2^32的所有x中1的个数
int cnt_tbl[65537];
void bitCountPre() //预处理
{
    cnt_tbl[0] = 0;
    for (int i=1; i<65536; ++i)
    cnt_tbl[i] = cnt_tbl[i >> 1] + (i & 1);
}

int bitCount(uint x)　//查询
{
    return cnt_tbl[x >> 16] + cnt_tbl[x & 65535u];
}


uint bitRev(uint x) //翻转uint的位序, 0位和31位交换
{
    x = ((x & 0xAAAAAAAAu) >> 1) | ((x & 0x55555555u) << 1);
    x = ((x & 0xCCCCCCCCu) >> 2) | ((x & 0x33333333u) << 2);
    x = ((x & 0xF0F0F0F0u) >> 4) | ((x & 0x0F0F0F0Fu) << 4);
    x = ((x & 0xFF00FF00u) >> 8) | ((x & 0x00FF00FFu) << 8);
    x = ((x & 0xFFFF0000u) >> 16) | ((x & 0x0000FFFFu) << 16);
    return x;
}

//查询0-2^32的所有x的位翻转
uint rev_tbl[65537];
void bitRevPre()
{
    rev_tbl[0] = 0;
    for (int i=1; i<65536; ++i)
    rev_tbl[i] = (rev_tbl[i>>1]>>1) | ((i&1)<<15);
}

uint bitRev(uint x)
{
    return (rev_tbl[x & 65535] << 16) | rev_tbl[x >> 16];
}


int countLeadingZeros(uint x)  //求x前缀（高位)0个数
{
    int ans = 0;
    if (x >> 16) x >>= 16; else ans |= 16;
    if (x >> 8) x >>= 8; else ans |= 8;
    if (x >> 4) x >>= 4; else ans |= 4;
    if (x >> 2) x >>= 2; else ans |= 2;
    if (x >> 1) x >>= 1; else ans |= 1;
    return ans + !x;;
}

int countTrailingZeros(uint x)  //求x后缀(低位)0个数
{
    int ans = 0;
    if (!(x & 65535u)) x >>= 16, ans |= 16;
    if (!(x & 255u )) x >>= 8, ans |= 8;
    if (!(x & 15u )) x >>= 4, ans |= 4;
    if (!(x & 3u )) x >>= 2, ans |= 2;
    if (!(x & 1u )) x >>= 1, ans |= 1;
    return ans + !x;
}


//查询0-2^32的所有x的前缀0个数
int clz_tbl[65537];
void countLeadingZerosPre()
{
    clz_tbl[0] = 16;
    for (int i=1; i<65536; ++i)
    clz_tbl[i] = clz_tbl[i >> 1] - 1;
}

int countLeadingZeros_2(uint x)
{
    if (x >> 16)
    return clz_tbl[x >> 16]; else
    return clz_tbl[x & 65535u] + 16;
}


int kthBit(uint x, int k)　//返回x第k个１的位次 (从低到高,0-31)
{
    int s[5], ans = 0, t;
    s[0] = x;
    s[1] = x - ((x & 0xAAAAAAAAu) >> 1);
    s[2] = ((s[1] & 0xCCCCCCCCu) >> 2) + (s[1] & 0x33333333u);
    s[3] = ((s[2] >> 4) + s[2]) & 0x0F0F0F0Fu;
    s[4] = ((s[3] >> 8) + s[3]) & 0x00FF00FFu;
    t = s[4] & 65535u;
    if (t < k) k -= t, ans |=16, x >>=16;
    t = (s[3] >> ans) & 255u;
    if (t < k) k -= t, ans |= 8, x >>= 8;
    t = (s[2] >> ans) & 15u;
    if (t < k) k -= t, ans |= 4, x >>= 4;
    t = (s[1] >> ans) & 3u;
    if (t < k) k -= t, ans |= 2, x >>= 2;
    t = (s[0] >> ans) & 1u;
    if (t < k) k -= t, ans |= 1, x >>= 1;
    return ans;
}

uint continuous1(uint x) //统计x低位开始连续的１，例如7返回7
{
    return x & (x^(x + 1));
}

//遍历所有x中的1: 只需要不断求lowbit,然后置0即可



uint nextComb(uint x)//获得当前x(x中有k个１)的字典序下一位
{
    uint l = x & -x, y = x + l;
    return y | (((x^y) / l) >> 2);
}



for(int i = S;i;i = (i-1)&S)  //枚举S的子集
