/*
首先对整个树进行LCA预处理
然后从1-n依次把i加入,设原直径为a--b
则现在的直径为max(a--b,a--i,b--i)


*/


int cal(int a,int b) //计算a-b这条链上的点的个数
{
    int t = LCA(a,b);
    return deep[a]+deep[b]-2*deep[t]+1;
}


