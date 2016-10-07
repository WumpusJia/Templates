//    C++
#pragma comment(linker, "/STACK:1024000000,1024000000")

//32位G++
__asm__("movl %0, %%esp\n" :: "r"((char*)malloc(256<<20)+(256<<20)));


//Linux 64位g++ 4.8.1
#include <cstdio>
#include <cstring>
#include <cstdlib>
/*使用时把main2当作main用即可，注意非return 0;而是main2 */
extern int main2(void) __asm__("main2");

int main2() {
	char test[255 << 20];
	memset(test, 42, sizeof(test));
	printf(":)\n");
	exit(0);
}

int main() {
	int size = 256 << 20;  // 256Mb
	char *p = (char *)malloc(size) + size;
	__asm__ __volatile__(
		"movq  %0, %%rsp\n"
		"pushq $exit\n"
		"jmp main2\n"
		:: "r"(p));
}

///////////////////////////
void RI (int& x){
	x = 0;
	char c = getchar ();
	while (!(c>='0' && c<='9' || c=='-'))     c = getchar ();
	bool flag = 1;
	if (c == '-'){
		flag = 0;
		c = getchar ();
	}
	while (c >= '0' && c <= '9'){
		x = x * 10 + c - '0';
		c = getchar ();
	}
	if (!flag)      x = -x;
}
//fread 读取字符串，然后解析


////////////////读入挂///////////////////////


inline bool read(int &x) 	//看情况可去掉负数部分
{
	int t = 1;
	int ch = getchar();
	if(ch == -1) return false;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar();}
	x = 0;
	while(ch >= '0' && ch <= '9'){ x=x*10+ch-'0'; ch = getchar(); }
	x*=t;
	return true;
}



////////////////
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

char *ch, *ch1, buf[40*1024000+5], buf1[40*1024000+5];

bool read(int &x) {
	for (++ch; (*ch) &&
        !(((*ch) >= '0' && (*ch) <= '9') || (*ch) == '-' ); ++ch);
	if(!(*ch)) return false;
	bool sign = 0;
	if((*ch) == '-') { sign = 1; ++ch; }
	for (x = 0; '0' <= *ch; ch++)	x = x * 10 + *ch - '0';
	if(sign) x = -x;
	return true;
}

void out(int x)
{
	if (!x)	*(++ch1) = '0';
	else
    {
		char *ch0 = ch1, *ch = ch1 + 1;
        bool sign = 0;
        if(x < 0) { sign = 1; x = -x; }
		while (x)
		{
			*(++ch0) = x % 10 + '0';
			x /= 10;
		}
		if(sign)
            *(++ch0) = '-';
		ch1 = ch0;
		while (ch <= ch0)	swap(*(ch++), *(ch0--));
	}
	*(++ch1) = '\n';
}


int main()
{
  //  freopen("./test.txt","r",stdin);
    ch = buf - 1;
	ch1 = buf1 - 1;
	fread(buf, 1, 1000 * 35 * 1024, stdin);
    int n;
    while(read(n))
    {
        out(n);
    }
    printf("%s",buf1);

}
///////////////////////////////////



