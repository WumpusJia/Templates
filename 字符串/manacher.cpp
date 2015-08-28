//manacher
char s[maxn*2];
int p[maxn*2];
//p[i]为改造后的回文半径,例如y#a#b#a#x的回文半径为4,原串回文长度为p[i]-1

int len=strlen(s);
int id = 0,maxlen = 0;
for(int i=len;i>=0;--i)
{//插入''#''
    s[i+i+2]=s[i];
    s[i+i+1]=''#'';
}
//插入了len+1个''#'',最终的s长度是1~len+len+1即2*len+1,
//首尾s[0]和s[2*len+2]要插入不同的字符
s[0]=''*'';//s[0]=''*'',s[len+len+2]=''\0'',防止在while时p[i]越界
for(int i=2;i<2*len+1;++i)
{
    if(p[id]+id>i)p[i]=min(p[2*id-i],p[id]+id-i);
    else p[i]=1;
    while(s[i-p[i]] == s[i+p[i]])++p[i];
    if(id+p[id]<i+p[i])id=i;
    if(maxlen<p[i])maxlen=p[i]-1;
}

