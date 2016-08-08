
//度数限制的树的计数
/*
sz表示限制点个数
cnt[i]表示限制的度数
fac为阶乘


一棵树可以由 \sum indegree[u]-1　的序列表示
把限制的度数个数 sum =　\sum cnt[i]-1 先放到这里面，剩下的随便放无限制的点就是答案

即C(n-2,sum)* sum!/ ( (cnt[1]-1)*(cnt[2]-1)*... ) * (n-sz)^(n-2-sum)

化简就是:
(n-2)! / ( (n-2-sum)! * ((cnt[1]-1)*(cnt[2]-1)*... ) ) * (n-sz)^(n-2-sum)

*/

LL cal() //注意!!　　只对n >= 2且　cnt[i]限制的点不重复时候计算
{

    LL sum = 0;
    for(int i = 0;i < sz;++i)
    {
        if(cnt[i] <= 0 || cnt[i] > n-1) return 0;
        sum += cnt[i]-1;
    }
    if(sum > n-2) return 0;

    LL res = pow_mod(n-sz,n-2-sum);

    res = res*fac[n-2]%mod;



    LL t = 1;
    for(int i = 0;i < sz;++i)
        t = t*fac[cnt[i]-1]%mod;
    t = t*fac[n-2-sum]%mod;

    res = res*inv(t)%mod;

    return res;


}
////////////////////////////////////////

//生成树的计数
/*
对于没有重边和自环的图
构造n*n的行列式A
A[i][i] = i点的度数
A[i][j] = ——　(i是否能到j)

当有重边时候(可能是这样)
A[i][i] = i点的度数
A[i][j] = ——　(i->j的边数)


*/
