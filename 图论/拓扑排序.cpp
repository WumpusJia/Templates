//拓扑排序
bool dfs(int u)
{
    c[u] = -1;
    for(int v = 0;v <= n;++v) if(G[u][v]) {
        if(c[v] < 0) return false; //错误，无法拓扑
        else if(!c[v])  dfs(v);
    }
    c[u] = 1;
    topo.push_back(u);
    return true;
}


bool toposort()
{
    topo.clear();
    memset(c,0,sizeof(c));
    for(int u = 0;u <= n;++u)
        if(!c[u])
        {
            if(!dfs(u))
                return false; //此时结束为从大到小排序
        }
    reverse(topo.begin(),topo.end()); //为了得到从小到大的顺序，逆转
    return true;
}
