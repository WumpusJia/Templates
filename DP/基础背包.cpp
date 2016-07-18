void ZeroOnePack(int d[],int w,int v)
{
	for(int j = C;j >= w;--j)
		d[j] = max(d[j],d[j-w]+v);

}

void ConpletePack(int d[],int w,int v)
{
	for(int j = w;j <= C;++j)
		d[j] = max(d[j],d[j-w]+v);
}
