#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;
typedef long long LL;
const double t1 = 5+2*sqrt(6),t2 = 5-2*sqrt(6);

void init()
{
	for(int i=1;i<=10;++i)
		printf("%lf\n",pow(t1,i) + pow(t2,i));
}

int main()
{
	int T;
	LL x,m;
	scanf("%d",&T);
	init();
	return 0;
	for(int z=1;z<=T;++z)
	{
		scanf("%lld %lld",&x,&m);
	}
	return 0;
}
