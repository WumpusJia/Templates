/// /O(nClogm)
void MultiplePack(int d[],int w,int v,int m)
{

    if(w*m >= C)
	{
        CompletePack(d,w,v);
        return;
    }
    int k = 1;
    while(k < m)
	{
        ZeroOnePack(d,k*c,k*w)
        m -= k;
        k *= 2;    
    }
    ZeorOnePack(d,w*m,v*m);
}


////O(nC)

struct Queue
{
    int num,value;
} que[maxn];
int back,front;
int d[maxn];

void Insert(int n,int v)	//单调队列，保证队首元素为最大值
{
	while(que[back].value < v && front <= back) --back;
    que[++back].num = n;
    que[back].value = v;
}

memset(d,0,sizeof d);
for(int i = 0;i < n;++i)
{
    for(int j = 0;j < w[i];++j)	 //枚举余数j
	{
		front = 1,back = 0;            //清空队列
        for(int k = 0;k <= (C-j)/w[i];++k)  //k*w[i]+j 枚举相同余数的体积
		{
			Insert(k,d[k*w[i]+j]-k*v[i]);    	//入队
            if(que[front].num < k-m[i]) ++front;  //队首元素失效
            d[k*w[i]+j] = que[front].value+k*v[i];//更新当前元素
        }
    }
}
