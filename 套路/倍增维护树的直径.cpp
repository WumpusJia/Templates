/*
首先对整个树进行LCA预处理
然后1-n依次加入
如果原直径是a-b,则现在直径为max(a-b,a-i,b-i)
*/


int cal(int a,int b)//计算a-b链上的点数
{
    int t = LCA(a,b);
    return deep[a]+deep[b]-2*deep[t]+1;
}


