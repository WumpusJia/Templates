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


//Hash容错表
void init()
{
    memset(head,-1,sizeof(head));
}

int modhash(int x)
{
    int sum = 0;
    for(int i = 0;i < 6;++i)
        sum += save[x][i];
    return sum%hashsize;
}

bool insert(int x)
{
    int h = modhash(x);
    int u = head[h];
    while(u != -1)
    {
        if(judge(u,x)) return false;
        u = nxt[u];
    }
    nxt[x] = head[h];
    head[h] = x;
    return true;
}


///////////////////分块暴力/////////////////////
 for(int i = L;i <= R;)
    {
        if(i%BLOCK == 0 && i + BLOCK -1 <= R)
        {
            diff[i/BLOCK] += x;
            i += BLOCK;
        }
        else
        {
            save[i] += x;
            i++;
        }
    }
