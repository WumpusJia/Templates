LL dfs(int x,int pre,int ye,int limit)    
{
	if(x < 0) return ye;
	int &ans = d[x][pre][ye];
	if(ans != -1) return ans;
	LL res = 0;
	int last = limit?dig[x]:9;
	for(int i = 0;i <= last;++i)
		res += dfs(x-1,i,ye || (当前数满足条件),limit && i == last)
			if(!limit) ans = res;
	return res;
}
