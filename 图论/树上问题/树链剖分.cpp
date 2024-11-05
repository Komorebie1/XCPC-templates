struct HLD {
    int n, idx;
    vector<vector<int>> G;
    vector<int> sz, dep, top, son, parent;
    HLD(int n)
    {
        this->n = n;
        G.resize(n + 1);
        sz.resize(n + 1);
        dep.resize(n + 1);
        top.resize(n + 1);
        son.resize(n + 1);
        parent.resize(n + 1);
    }
    void dfs1(int u)  // 处理出深度和重儿子
    {
        sz[u] = 1;
        dep[u] = dep[parent[u]] + 1;
        for (auto v : G[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            dfs1(v);
            sz[u] += sz[v];
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }
    void dfs2(int u, int up)
    {
        top[u] = up;
        if (son[u]) dfs2(son[u], up);
        for (int v : G[u]) {
            if (v == parent[u] || v == son[u]) continue;
            dfs2(v, v);
        }
    }
    int lca(int x, int y)
    {
        while (top[x] != top[y]) {
            if (dep[top[x]] > dep[top[y]]) {
                x = parent[top[x]];
            }
            else {
                y = parent[top[y]];
            }
        }
        return dep[x] < dep[y] ? x : y;
    }
    
    int calc(int x, int y) { return dep[x] + dep[y] - 2 * dep[lca(x, y)]; } // 查询两点距离
};