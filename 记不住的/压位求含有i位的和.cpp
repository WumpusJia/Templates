//注意　　对位的枚举必须在外面
for(int j = 0;j < n;++j)
    for(int i = (1 << n)-1;i >= 0;--i)
        if(! (i & (1 << j)))
        {
            int t = i | (1 << j);
            cnt[i] += cnt[t];
        }
