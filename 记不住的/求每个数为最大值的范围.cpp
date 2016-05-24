//最小
L[1] = 1;
int top = 1;
pstack[top] = 1;
for(int i = 2;i <= n;++i)
{
    L[i] = i;
    while(top >= 1 && save[i] < save[pstack[top]])  //改成 > 就是求最大
    {
        L[i] = L[pstack[top]];
        R[pstack[top]] = i-1;
        top--;
    }
    pstack[++top] = i;
}
for(int i = 1;i <= top;++i)
    R[pstack[i]] = n;
