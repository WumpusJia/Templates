LL dfs(int x,int pre,int ok,int limit)
{
	if(x<0) return ok;
	int &ans = d[x][pre][ye];
	if(!limit && ans!=-1) return ans;
	LL res = 0;
	int last = limit?dig[x]:9;
	for(int i=0;i<=last;++i)
        if(check(i)) //i是否可以选
            res += dfs(x-1,i,ok || (当前数满足条件),limit && i==last)
	if(!limit) ans =res;
	return res;
}
