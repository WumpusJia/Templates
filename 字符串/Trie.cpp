//Trie
const int maxnode = 4000*100+10;
const int sigma_size = 26;

struct Trie
{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;
    void clear() { sz = 1;memset(ch[0],0,sizeof(ch[0])); }
    int idx(char c) { return c - 'a'; }

    void insert(const char *s,int v)
    {
        int u = 0,n = strlen(s);
        for(int i = 0;i < n;++i)
        {
            int c = idx(s[i]);
            if(!ch[u][c])
            {
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void find_prefixes(const char* s,int len,vector<int>& ans)
    {
        int u = 0;
        for(int i = 0;i < len;++i)
        {
            if(s[i] == 0) break;
            int c = idx(s[i]);
            if(!ch[u][c]) break;
            u = ch[u][c];
            if(val[u] != 0)  ans.push_back(val[u]);
        }
    }
};

