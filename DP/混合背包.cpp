for(int i = 0;i < n;++i)
{
	if(ZeroOne) ZeroOnePack(d,w[i],v[i]);
	else if(Complete) CompletePack(d,w[i],v[i]);
	else if(Multiple) MultiplePack(d,w[i],v[i]);
}
