void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++tim;
    int son = 0;
    for (int v : G[u]) {
        if (!dfn[v]) {
            son++;
            tarjan2(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])  // 找割边
            {
                cnt_bridge++;
                es[mp[hh(u, v)]].tag = 1;
            }
        }
        else if (v != fa) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}