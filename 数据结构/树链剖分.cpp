void dfs1(int u, int fa)  // 先处理出重儿子和深度
{
    dep[u] = dep[fa] + 1;
    siz[u] = 1;
    father[u] = fa;
    int max_size = -1;
    for (int v : G[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        siz[u] += siz[v];
        if (siz[v] > max_size) {
            heave_son[u] = v;
            max_size = siz[heave_son[u]];
        }
    }
}
void dfs2(int u, int t)  // 处理出对应的链头和dfn序
{
    dfn[u] = ++tim;
    top[u] = t;
    w[tim] = a[u];
    if (!heave_son[u]) return;
    dfs2(heave_son[u], t);
    for (int v : G[u]) {
        if (v == father[u] || v == heave_son[u]) continue;
        dfs2(v, v);
    }
}
int lca(int u, int v)  // 利用链头往上跳，在同一个链上时深度小的即为祖先
{
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = father[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}