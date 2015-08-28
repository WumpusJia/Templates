//集合dp
//先把相互包含的串去掉，这样不会影响最终结果。
//然后建图，权值为前面串的后缀和后面串的后缀的公共长度。
//d[i][S] 表示以第i个串开头，已选状态为S的最大值
//d[j][S|j] = max(G[i][S]) + G[j][i]  ((S&j) == 0)
//最后答案为( 总长 - max(d[i][1<<(n-1)] )
//题目要求输出字典序最小的一个串,dfs打印即可
//注意每次比较字典序大小是减去公共前缀的，而不是直接比较两个串
#include<cstdio>
#include<cstring>
#include<string>
#include<map>
#include<vector>

using namespace std;

const int maxn = 20;

vector<int> rec;
int d[maxn][1<<15],pos[maxn],vis[maxn];
int G[maxn][maxn];
int n;
char s[maxn][105];

inline int check(char *s1,char *s2)
{
	int n1 = strlen(s1),n2 = strlen(s2);
	if(n1<n2) swap(s1,s2),swap(n1,n2);
	for(int i=0;i+n2-1<n1;++i)
	{
		bool flag = true;
		for(int j=0;j<n2;++j)
			if(s1[i+j]!=s2[j]){
				flag = false;
			   	break;
			}
		if(flag) return true;
	}
	return false;
}

inline int cal(char *s1,char *s2)
{
	int n1 = strlen(s1),n2 = strlen(s2);
	int mx = 0;
	for(int i=max(0,n1-n2);i<n1;++i)
	{
		int cnt = 0;
		for(int j=0;j<n2 && i+j<n1; ++j)
			if(s1[i+j]!=s2[j])
			{
				cnt = 0;
				break;
			}
			else ++cnt;
		mx = max(mx,cnt);
	}
	return mx;
}

inline void gao()
{
	map<string,int> id;
	int cnt=0;
	for(int i=0;i<n;++i)
		for(int j=i+1;j<n;++j)
			if(check(s[i],s[j]))
			{
				int n1 = strlen(s[i]),n2 = strlen(s[j]);
				if(n1>=n2)
				{
					id[string(s[j])] = -1;
				}
				else
				{
					id[string(s[i])] = -1;
					break;
				}
			}

	for(int i=0;i<n;++i)
	{
		if(!id[string(s[i])]==-1) continue;
		if(!id[string(s[i])])
		id[string(s[i])] = ++cnt, pos[cnt-1] = i;
		for(int j=0;j<n;++j)
		{
			if(i==j || id[string(s[j])]==-1) continue;
			if(!id[string(s[j])])
                id[string(s[j])] = ++cnt, pos[cnt-1] = j;
			G[id[string(s[i])]-1][id[string(s[j])]-1] = cal(s[i],s[j]);
			G[id[string(s[j])]-1][id[string(s[i])]-1] = cal(s[j],s[i]);
		}
	}
	n = cnt;
}

void dfs(int u,int S,int ans)
{
	vis[u] = 1;
	int id = -1;
	for(int i=0;i<n;++i)
	{
		if(vis[i]) continue;
		if(ans - G[u][i] == d[i][S])
		{
			if(id==-1) id = i;
			else
			if(strcmp(s[pos[i]]+G[u][i],s[pos[id]]+G[u][id])<0)
                id = i;
		}
	}
	if(id==-1) return;
	rec.push_back(id);
	dfs(id,S^(1<<id),ans - G[u][id]);
}

inline void dp()
{
	memset(d,-1,sizeof d);
	for(int i=0;i<n;++i) d[i][1<<i] = 0;
	for(int S=0;S<(1<<n);++S)
	{
		for(int i=0;i<n;++i)
		{
			if(d[i][S]==-1) continue;
			if(d[i][S]==-1) d[i][S] = 0;
			for(int j=0;j<n;++j)
			{
				if(i == j) continue;
				if(!(S&(1<<j)))
				{
					d[j][S|(1<<j)] =
					max(d[j][S|(1<<j)],d[i][S] + G[j][i]);
				}
			}
		}
	}
	int ans = -1,id = 0;
	for(int i=0;i<n;++i)
	{
		if(ans<=d[i][(1<<n)-1])
		{
			if(ans<d[i][(1<<n)-1])
			{
				ans = d[i][(1<<n)-1];
				id = i;
			}
			if(strcmp(s[pos[i]],s[pos[id]])<0) id = i;
		}
	}
	rec.clear();
	rec.push_back(id);

	memset(vis,0,sizeof vis);
	dfs(id,((1<<n)-1)^(1<<id),ans);
	for(int i=0;i<rec.size()-1;++i)
	{
//		printf("%d -- ",rec[i]);
		int t = G[rec[i]][rec[i+1]];
//		printf("%d\n",t);
		for(int j=0;j<strlen(s[pos[rec[i]]])-t;++j)
            putchar(s[pos[rec[i]]][j]);
	}
//	printf("%d\n",rec[rec.size()-1]);
	printf("%s\n\n",s[pos[rec[rec.size()-1]]]);
}

int main()
{
//	freopen("test.txt","r",stdin);
//	freopen("out.txt","w",stdout);
	int T;
	scanf("%d",&T);
	for(int z = 1;z<=T;++z)
	{
		printf("Scenario #%d:\n",z);
		scanf("%d",&n);
		for(int i=0;i<n;++i) scanf("%s",s[i]);
		gao();
		dp();
	}
	return 0;
}

